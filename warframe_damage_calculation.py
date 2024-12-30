#CTRL+B  : Build
import math
import argparse
from weapon_data import Weapon_Base_Stats_Dict
from modding_data import Modding_Stats_Dict
from enemy_data import Enemy_Stats_Dict
from truc import Parametres

#Les trucs imprécis:
#Ya des ~5% erreur sur XATA
#La mechanique de refresh des stacks multiples de Heat n'est pas pris en compte dans le dps

## Bool Environement
moreLog = 0
critCalculationMethod = "average"     #average / lowest crit tier (lct) / highest crit tier (hct) / no crit (nc)
statusCalculationMethod = "average"    #average / manual / ns
isSP = 0
isPrimary = 1
isSecondary = 0
isMelee = 0



#------------------------------------------------------------------

def modApplication(base_stat, mod):
	return base_stat * (1 + mod/100)
def quantization1(dmg, scale):
	return (round(dmg / scale) * scale)
def quantization(base_dmg, mod, scale):
	return round(base_dmg * mod/100 / scale) * scale

#Armor & Others Enemy DR
def Step_DR(dmg, enemy_DR, other_enemy_DR):
	return dmg * (1 + enemy_DR / 100) * (1 + other_enemy_DR / 100)

#Weapons Damage Mods
def Step_DMG(dmg, dmg_mod):
	return dmg * (1 + dmg_mod / 100)

#Faction
def Step_FACTION(dmg, faction_mod):
	return dmg * faction_mod

#Critical & Headshot are tied
def Step_CRITICAL(dmg, final_critical_chance, final_critical_multiplier, head_vulnerability_multiplier, total_other_headshot_bonus, crit_calculation_method, isHeadshot):
	if (crit_calculation_method == "average"):
		Critical_Tier = final_critical_chance / 100
		if (isHeadshot):
			return dmg * head_vulnerability_multiplier * (1 + Critical_Tier * (2 * final_critical_multiplier - 1)) * (1 + total_other_headshot_bonus/100)
		else:
			return dmg * final_critical_multiplier * Critical_Tier

	elif (crit_calculation_method == "lct"):
		Critical_Tier = math.floor(final_critical_chance / 100)
		if (Critical_Tier <= 0):
			if (isHeadshot):
				return dmg * head_vulnerability_multiplier * (1 + total_other_headshot_bonus/100)
			else:
				return dmg
		else:
			if (isHeadshot):
				return dmg * head_vulnerability_multiplier * (1 + Critical_Tier * (2 * final_critical_multiplier - 1)) * (1 + total_other_headshot_bonus/100)
			else:
				return dmg * final_critical_multiplier * Critical_Tier

	elif (crit_calculation_method == "hct"):
		Critical_Tier = math.ceil(final_critical_chance / 100)
		if (Critical_Tier <= 0):
			if (isHeadshot):
				return dmg * head_vulnerability_multiplier * (1 + total_other_headshot_bonus/100)
			else:
				return dmg
		else:
			if (isHeadshot):
				return dmg * head_vulnerability_multiplier * (1 + Critical_Tier * (2 * final_critical_multiplier - 1)) * (1 + total_other_headshot_bonus/100)
			else:
				return dmg * final_critical_multiplier * Critical_Tier

	elif (crit_calculation_method == "nc"):
		Critical_Tier = 0
		if (isHeadshot):
			return dmg * head_vulnerability_multiplier * (1 + total_other_headshot_bonus/100)
		else:
			return dmg

	else:
		print("ERROR: Wrong Critical Calculation Method Used\nUsing 'Average' per default")
		Critical_Tier = final_critical_chance / 100
		if (isHeadshot):
			return dmg * head_vulnerability_multiplier * (1 + Critical_Tier * (2 * final_critical_multiplier - 1)) * (1 + Total_Other_Headshot_Bonus/100)
		else:
			return dmg * final_critical_multiplier * Critical_Tier
	
#Multishot
def Step_MULTISHOT(dmg, multishot_mod):
	return dmg * multishot_mod

#Damage Ability Multipliers (Eclipse)
def Step_ECLIPSE(dmg, ability_strength, isEclipse, isEclipseSubsumed):
	if (isEclipse):
		return dmg * (1 + 200/100 * (ability_strength/100))
	elif (isEclipseSubsumed):
		return dmg * (1 + 30/100 * (ability_strength/100))
	else:
		return dmg

#Viral stacks
def Step_VIRAL(dmg, nbstacks):
	if (nbstacks != 0):
		return dmg * (2 + (0.25 * (nbstacks - 1)))
	else:
		return dmg

#------------------------------------------------------------------

def calculation(weapon_base_stats, modding_stats, enemy_stats, parametres):
	print("--- Start Of the Script ---")
	#------------------------------------------------------------------
	# Weapon Stat Calculation
	if (weapon_base_stats["Other"]["isExalted"]):
		Final_Base_Impact_Damage = modApplication(weapon_base_stats["IPS"]["Impact_Damage"], parametres["Warframe_Stats"]["Ability_Strength"])
		Final_Base_Puncture_Damage = modApplication(weapon_base_stats["IPS"]["Puncture_Damage"], parametres["Warframe_Stats"]["Ability_Strength"])
		Final_Base_Slash_Damage = modApplication(weapon_base_stats["IPS"]["Slash_Damage"], parametres["Warframe_Stats"]["Ability_Strength"])
	else:
		Final_Base_Impact_Damage = weapon_base_stats["IPS"]["Impact_Damage"]
		Final_Base_Puncture_Damage = weapon_base_stats["IPS"]["Puncture_Damage"]
		Final_Base_Slash_Damage = weapon_base_stats["IPS"]["Slash_Damage"]

	Final_Damage_Mult = modding_stats["Raw"]["Damage_Mod"]
	Final_Faction = modApplication(weapon_base_stats["Other"]["Base_Faction_Damage_Mult"], modding_stats["Raw"]["Faction_Mod"])

	Final_Critical_Chance = modApplication(weapon_base_stats["Critical"]["Base_Critical_Chance"], modding_stats["Critical"]["Critical_Chance_Mod"]) + modding_stats["Critical"]["Flat_Critical_Chance"]
	Final_Critical_Multiplier = modApplication(weapon_base_stats["Critical"]["Base_Critical_Multiplier"], modding_stats["Critical"]["Critical_Multiplier_Mod"] + (parametres["Buff"]["isIvaraQuiver"] * parametres["Warframe_Stats"]["Ability_Strength"])) + modding_stats["Critical"]["Flat_Critical_Damage"]

	Final_Status_Chance = modApplication(weapon_base_stats["Status"]["Base_Status_Chance"], modding_stats["Status"]["Status_Chance_Mod"])
	Final_Status_Duration = modApplication(weapon_base_stats["Status"]["Base_Duration_Status"], modding_stats["Status"]["Duration_Status_Mod"])
	Final_Status_Damage_Mult = modding_stats["Status"]["Status_Damage_Mod"]

	Final_Multishot = modApplication(weapon_base_stats["DPS"]["Base_Projectile_Number"], modding_stats["DPS"]["Multishot_Mod"])
	Final_Magazine_Size = modApplication(weapon_base_stats["DPS"]["Base_Magazine_Size"], modding_stats["DPS"]["Magazine_Size_Mod"])
	Final_Firerate = modApplication(weapon_base_stats["DPS"]["Base_Firerate"], modding_stats["DPS"]["Firerate_Mod"])
	Final_Reload_Time = modApplication(weapon_base_stats["DPS"]["Base_Reload_Time"], modding_stats["DPS"]["Reload_Time_Mod"])

	Final_Head_Mult = enemy_stats["Vulnerability"]["Head_Vulnerability_Multiplier"] + (modding_stats["Other"]["Weak_Point_Damage"]/100 * 1.5)

	#------------------------------------------------------------------
	# Buff Calculation
	#Araknee/VS/HA
	if (isMelee == 0):
		if (parametres["Buff"]["isAraknee"]):
			Final_Damage_Mult += 150
		if (parametres["Buff"]["isVigorousSwap"]):
			Final_Damage_Mult += 165
		if (parametres["Buff"]["isHolsterAmp"]):
			Final_Damage_Mult += 60
	#Ivara Prowl
	if (parametres["Buff"]["isIvaraProwl"]):
		Total_Other_Headshot_Bonus =  modding_stats["Other"]["Other_Headshot_Bonus"] + (40 * parametres["Warframe_Stats"]["Ability_Strength"]/100)
	else:
		Total_Other_Headshot_Bonus = modding_stats["Other"]["Other_Headshot_Bonus"]
	#Roar
	if (parametres["Buff"]["isRoar"]):
		Final_Faction += 50/100 * parametres["Warframe_Stats"]["Ability_Strength"]/100
	elif (parametres["Buff"]["isRoarSubsumed"]):
		Final_Faction += 30/100 * parametres["Warframe_Stats"]["Ability_Strength"]/100
	#Nourish
	if (parametres["Buff"]["isNourish"]):
		modding_stats["Secondary"]["Viral_Mod"] += 75 * parametres["Warframe_Stats"]["Ability_Strength"]/100
	elif (parametres["Buff"]["isNourishSubsumed"]):
		modding_stats["Secondary"]["Viral_Mod"] += 45 * parametres["Warframe_Stats"]["Ability_Strength"]/100
	#------------------------------------------------------------------
	# Enemy Stats Calculation
	if (1):
		#Armor Calculation
		# x = Ennemy_Current_Level
		S = 0
		T = (enemy_stats["Level"]["Enemy_Current_Level"] - enemy_stats["Level"]["Enemy_Base_Level"] - 70) / 10
		#Calcul de S(x), Fonction de transition
		if (enemy_stats["Level"]["Enemy_Current_Level"] - enemy_stats["Level"]["Enemy_Base_Level"]) < 70:
			S = 0
		elif (enemy_stats["Level"]["Enemy_Current_Level"] - enemy_stats["Level"]["Enemy_Base_Level"]) > 80:
			S = 1
		else:
			S = 3 * math.pow(T,2) - 2 * math.pow(T,3)

		#F1(x) (Enemy_Current_Level - Enemy_Base_Level) < 70
		F1 = 1 + 0.005 * math.pow((enemy_stats["Level"]["Enemy_Current_Level"] - enemy_stats["Level"]["Enemy_Base_Level"]),1.75)
		#F2(x) (Enemy_Current_Level - Enemy_Base_Level) > 80
		F2 = 1 + 0.4 * math.pow((enemy_stats["Level"]["Enemy_Current_Level"] - enemy_stats["Level"]["Enemy_Base_Level"]),0.75)

		Enemy_Base_Armor_Multiplier = F1 * (1 - S) + F2 * S
		Enemy_Armor = enemy_stats["Stats"]["Enemy_Base_Armor"] * Enemy_Base_Armor_Multiplier
		if Enemy_Armor > 2700:
			Enemy_Armor = 2700
		Enemy_DR = 90 * math.sqrt(Enemy_Armor/2700)
	#------------------------------------------------------------------
	#Sums of unmodded damages
	Total_Base_Damage = Final_Base_Impact_Damage \
					+ Final_Base_Puncture_Damage \
					+ Final_Base_Slash_Damage \
					+ weapon_base_stats["HCET"]["Cold_Damage"] \
					+ weapon_base_stats["HCET"]["Fire_Damage"] \
					+ weapon_base_stats["HCET"]["Toxin_Damage"] \
					+ weapon_base_stats["HCET"]["Electricity_Damage"] \
					+ weapon_base_stats["Secondary"]["Viral_Damage"] \
					+ weapon_base_stats["Secondary"]["Corrosiv_Damage"] \
					+ weapon_base_stats["Secondary"]["Magnetic_Damage"] \
					+ weapon_base_stats["Secondary"]["Radiation_Damage"] \
					+ weapon_base_stats["Secondary"]["Gaz_Damage"] \
					+ weapon_base_stats["Secondary"]["Blast_Damage"] \
					+ weapon_base_stats["Secondary"]["Void_Damage"]
	##Quantization
	#Scale
	Scale = Total_Base_Damage / 16 #Elemental and Physical bonuses do not affect the scale
	#Quantized Base Damages
	Quantized_Base_Impact_Damage = quantization1(Final_Base_Impact_Damage, Scale)
	Quantized_Base_Puncture_Damage = quantization1(Final_Base_Puncture_Damage, Scale)
	Quantized_Base_Slash_Damage = quantization1(Final_Base_Slash_Damage, Scale)
	Quantized_Base_Cold_Damage = quantization1(weapon_base_stats["HCET"]["Cold_Damage"], Scale)
	Quantized_Base_Fire_Damage = quantization1(weapon_base_stats["HCET"]["Fire_Damage"], Scale)
	Quantized_Base_Toxin_Damage = quantization1(weapon_base_stats["HCET"]["Toxin_Damage"], Scale)
	Quantized_Base_Electricity_Damage = quantization1(weapon_base_stats["HCET"]["Electricity_Damage"], Scale)
	Quantized_Base_Viral_Damage = quantization1(weapon_base_stats["Secondary"]["Viral_Damage"], Scale)
	Quantized_Base_Corrosiv_Damage = quantization1(weapon_base_stats["Secondary"]["Corrosiv_Damage"], Scale)
	Quantized_Base_Magnetic_Damage = quantization1(weapon_base_stats["Secondary"]["Magnetic_Damage"], Scale)
	Quantized_Base_Radiation_Damage = quantization1(weapon_base_stats["Secondary"]["Radiation_Damage"], Scale)
	Quantized_Base_Gaz_Damage = quantization1(weapon_base_stats["Secondary"]["Gaz_Damage"], Scale)
	Quantized_Base_Blast_Damage = quantization1(weapon_base_stats["Secondary"]["Blast_Damage"], Scale)
	Quantized_Base_Void_Damage = quantization1(weapon_base_stats["Secondary"]["Void_Damage"], Scale)
	if (moreLog):
		print("Q_Base_Impact_Dmg = {}".format(Quantized_Base_Impact_Damage))
		print("Q_Base_Puncture_Dmg = {}".format(Quantized_Base_Puncture_Damage))
		print("Q_Base_Slash_Dmg = {}".format(Quantized_Base_Slash_Damage))
		print("Q_Base_Cold_Dmg = {}".format(Quantized_Base_Cold_Damage))
		print("Q_Base_Fire_Dmg = {}".format(Quantized_Base_Fire_Damage))
		print("Q_Base_Toxin_Dmg = {}".format(Quantized_Base_Toxin_Damage))
		print("Q_Base_Electricity_Dmg = {}".format(Quantized_Base_Electricity_Damage))
		print("Q_Base_Viral_Dmg = {}".format(Quantized_Base_Viral_Damage))
		print("Q_Base_Corrosiv_Dmg = {}".format(Quantized_Base_Corrosiv_Damage))
		print("Q_Base_Magnetic_Dmg = {}".format(Quantized_Base_Magnetic_Damage))
		print("Q_Base_Radiation_Dmg = {}".format(Quantized_Base_Radiation_Damage))
		print("Q_Base_Gaz_Dmg = {}".format(Quantized_Base_Gaz_Damage))
		print("Q_Base_Blast_Dmg = {}".format(Quantized_Base_Blast_Damage))
		print("Q_Base_Void_Dmg = {}".format(Quantized_Base_Void_Damage))
		print("----------")
	#Quantized Modded Damages
	Quantized_Modded_Impact_Damage = quantization(Final_Base_Impact_Damage, modding_stats["IPS"]["Impact_Mod"], Scale)
	Quantized_Modded_Puncture_Damage = quantization(Final_Base_Puncture_Damage, modding_stats["IPS"]["Puncture_Mod"], Scale)
	Quantized_Modded_Slash_Damage = quantization(Final_Base_Slash_Damage, modding_stats["IPS"]["Slash_Mod"], Scale)
	Quantized_Modded_Cold_Damage = quantization(Total_Base_Damage, modding_stats["HCET"]["Cold_Mod"], Scale)
	Quantized_Modded_Fire_Damage = quantization(Total_Base_Damage, modding_stats["HCET"]["Fire_Mod"], Scale)
	Quantized_Modded_Toxin_Damage = quantization(Total_Base_Damage, modding_stats["HCET"]["Toxin_Mod"], Scale)
	Quantized_Modded_Electricity_Damage = quantization(Total_Base_Damage, modding_stats["HCET"]["Electricity_Mod"], Scale)
	Quantized_Modded_Viral_Damage = quantization(Total_Base_Damage, modding_stats["Secondary"]["Viral_Mod"], Scale)
	Quantized_Modded_Corrosiv_Damage = quantization(Total_Base_Damage, modding_stats["Secondary"]["Corrosiv_Mod"], Scale)
	Quantized_Modded_Magnetic_Damage = quantization(Total_Base_Damage, modding_stats["Secondary"]["Magnetic_Mod"], Scale)
	Quantized_Modded_Radiation_Damage = quantization(Total_Base_Damage, modding_stats["Secondary"]["Radiation_Mod"], Scale)
	Quantized_Modded_Gaz_Damage = quantization(Total_Base_Damage, modding_stats["Secondary"]["Gaz_Mod"], Scale)
	Quantized_Modded_Blast_Damage = quantization(Total_Base_Damage, modding_stats["Secondary"]["Blast_Mod"], Scale)
	Quantized_Modded_Void_Damage = quantization(Total_Base_Damage, modding_stats["Secondary"]["Void_Mod"], Scale)
	if (moreLog):
		print("Q_Modded_Impact_Dmg = {}".format(Quantized_Modded_Impact_Damage))
		print("Q_Modded_Puncture_Dmg = {}".format(Quantized_Modded_Puncture_Damage))
		print("Q_Modded_Slash_Dmg = {}".format(Quantized_Modded_Slash_Damage))
		print("Q_Modded_Cold_Dmg = {}".format(Quantized_Modded_Cold_Damage))
		print("Q_Modded_Fire_Dmg = {}".format(Quantized_Modded_Fire_Damage))
		print("Q_Modded_Toxin_Dmg = {}".format(Quantized_Modded_Toxin_Damage))
		print("Q_Modded_Electricity_Dmg = {}".format(Quantized_Modded_Electricity_Damage))
		print("Q_Modded_Viral_Dmg = {}".format(Quantized_Modded_Viral_Damage))
		print("Q_Modded_Corrosiv_Dmg = {}".format(Quantized_Modded_Corrosiv_Damage))
		print("Q_Modded_Magnetic_Dmg = {}".format(Quantized_Modded_Magnetic_Damage))
		print("Q_Modded_Radiation_Dmg = {}".format(Quantized_Modded_Radiation_Damage))
		print("Q_Modded_Gaz_Dmg = {}".format(Quantized_Modded_Gaz_Damage))
		print("Q_Modded_Blast_Dmg = {}".format(Quantized_Modded_Blast_Damage))
		print("Q_Modded_Void_Dmg = {}".format(Quantized_Modded_Void_Damage))
		print("----------")
	#Quantized
	#Sums of damages affected by resistances 
	Total_Quantized_Damage = (Quantized_Base_Impact_Damage + Quantized_Modded_Impact_Damage)                   * ( 1 + enemy_stats["Vulnerability"]["Impact_Vulnerabilities"] / 100 ) \
						   + (Quantized_Base_Puncture_Damage + Quantized_Modded_Puncture_Damage)               * ( 1 + enemy_stats["Vulnerability"]["Puncture_Vulnerabilities"] / 100 ) \
						   + (Quantized_Base_Slash_Damage + Quantized_Modded_Slash_Damage)                     * ( 1 + enemy_stats["Vulnerability"]["Slash_Vulnerabilities"] / 100 ) \
						   + (Quantized_Base_Cold_Damage + Quantized_Modded_Cold_Damage)                       * ( 1 + enemy_stats["Vulnerability"]["Cold_Vulnerabilities"] / 100 ) \
						   + (Quantized_Base_Fire_Damage + Quantized_Modded_Fire_Damage)                       * ( 1 + enemy_stats["Vulnerability"]["Fire_Vulnerabilities"] / 100 ) \
						   + (Quantized_Base_Toxin_Damage + Quantized_Modded_Toxin_Damage)                     * ( 1 + enemy_stats["Vulnerability"]["Toxin_Vulnerabilities"] / 100 ) \
						   + (Quantized_Base_Electricity_Damage + Quantized_Modded_Electricity_Damage)         * ( 1 + enemy_stats["Vulnerability"]["Electricity_Vulnerabilities"] / 100 ) \
						   + (Quantized_Base_Viral_Damage + Quantized_Modded_Viral_Damage)                     * ( 1 + enemy_stats["Vulnerability"]["Viral_Vulnerabilities"] / 100 ) \
						   + (Quantized_Base_Corrosiv_Damage + Quantized_Modded_Corrosiv_Damage)               * ( 1 + enemy_stats["Vulnerability"]["Corrosiv_Vulnerabilities"] / 100 ) \
						   + (Quantized_Base_Magnetic_Damage + Quantized_Modded_Magnetic_Damage)               * ( 1 + enemy_stats["Vulnerability"]["Magnetic_Vulnerabilities"] / 100 ) \
						   + (Quantized_Base_Radiation_Damage + Quantized_Modded_Radiation_Damage)             * ( 1 + enemy_stats["Vulnerability"]["Radiation_Vulnerabilities"] / 100 ) \
						   + (Quantized_Base_Gaz_Damage + Quantized_Modded_Gaz_Damage)                         * ( 1 + enemy_stats["Vulnerability"]["Gaz_Vulnerabilities"] / 100 ) \
						   + (Quantized_Base_Blast_Damage + Quantized_Modded_Blast_Damage)                     * ( 1 + enemy_stats["Vulnerability"]["Blast_Vulnerabilities"] / 100 ) \
						   + (Quantized_Base_Void_Damage + Quantized_Modded_Void_Damage)                       * ( 1 + enemy_stats["Vulnerability"]["Void_Vulnerabilities"] / 100 )
	Total_Quantized_Damage_DoT = Quantized_Base_Impact_Damage                      * ( 1 + enemy_stats["Vulnerability"]["Impact_Vulnerabilities"] / 100 ) \
							   + Quantized_Base_Puncture_Damage                    * ( 1 + enemy_stats["Vulnerability"]["Puncture_Vulnerabilities"] / 100 ) \
							   + Quantized_Base_Slash_Damage                       * ( 1 + enemy_stats["Vulnerability"]["Slash_Vulnerabilities"] / 100 ) \
							   + Quantized_Base_Cold_Damage                        * ( 1 + enemy_stats["Vulnerability"]["Cold_Vulnerabilities"] / 100 ) \
							   + Quantized_Base_Fire_Damage                        * ( 1 + enemy_stats["Vulnerability"]["Fire_Vulnerabilities"] / 100 ) \
							   + Quantized_Base_Toxin_Damage                       * ( 1 + enemy_stats["Vulnerability"]["Toxin_Vulnerabilities"] / 100 ) \
							   + Quantized_Base_Electricity_Damage                 * ( 1 + enemy_stats["Vulnerability"]["Electricity_Vulnerabilities"] / 100 ) \
							   + Quantized_Base_Viral_Damage                       * ( 1 + enemy_stats["Vulnerability"]["Viral_Vulnerabilities"] / 100 ) \
							   + Quantized_Base_Corrosiv_Damage                    * ( 1 + enemy_stats["Vulnerability"]["Corrosiv_Vulnerabilities"] / 100 ) \
							   + Quantized_Base_Magnetic_Damage                    * ( 1 + enemy_stats["Vulnerability"]["Magnetic_Vulnerabilities"] / 100 ) \
							   + Quantized_Base_Radiation_Damage                   * ( 1 + enemy_stats["Vulnerability"]["Radiation_Vulnerabilities"] / 100 ) \
							   + Quantized_Base_Gaz_Damage                         * ( 1 + enemy_stats["Vulnerability"]["Gaz_Vulnerabilities"] / 100 ) \
							   + Quantized_Base_Blast_Damage                       * ( 1 + enemy_stats["Vulnerability"]["Blast_Vulnerabilities"] / 100 ) \
							   + Quantized_Base_Void_Damage                        * ( 1 + enemy_stats["Vulnerability"]["Void_Vulnerabilities"] / 100 )
	#------------------------------------------------------------------
	#Application Multipliers
	Step1 = Step_DMG(Total_Quantized_Damage, Final_Damage_Mult)
	Step2 = Step_FACTION(Step1, Final_Faction)
	Step3 = Step_CRITICAL(Step2, Final_Critical_Chance, Final_Critical_Multiplier, Final_Head_Mult, Total_Other_Headshot_Bonus, critCalculationMethod, parametres["Other"]["isHeadshot"])
	Step4 = Step_MULTISHOT(Step3, Final_Multishot)
	Step5 = Step_ECLIPSE(Step4, parametres["Warframe_Stats"]["Ability_Strength"], parametres["Buff"]["isEclipse"], parametres["Buff"]["isEclipseSubsumed"])
	Step6 = Step_DR(Step5, Enemy_DR, enemy_stats["Stats"]["Other_Enemy_DR"])
	Step7 = Step_VIRAL(Step6, enemy_stats["Status"]["viral_Stacks"])

	Final_Original_Single_Hit_Damage_Instance = Step7
	#Warframe Unique Bonus (Garuda's passive/ect ...)
	#Stealh bonus
	#------------------------------------------------------------------
	#Status
	#Pondération elements
	i_Impact = modApplication(Final_Base_Impact_Damage , modding_stats["IPS"]["Impact_Mod"]/100)
	i_Puncture = modApplication(Final_Base_Puncture_Damage , modding_stats["IPS"]["Puncture_Mod"]/100)
	i_Slash = modApplication(Final_Base_Slash_Damage , modding_stats["IPS"]["Slash_Mod"]/100)
	i_Cold = modApplication(weapon_base_stats["HCET"]["Cold_Damage"] , modding_stats["HCET"]["Cold_Mod"]/100)
	i_Fire = modApplication(weapon_base_stats["HCET"]["Fire_Damage"] , modding_stats["HCET"]["Fire_Mod"]/100)
	i_Toxin = modApplication(weapon_base_stats["HCET"]["Toxin_Damage"] , modding_stats["HCET"]["Toxin_Mod"]/100)
	i_Electricity = modApplication(weapon_base_stats["HCET"]["Electricity_Damage"] , modding_stats["HCET"]["Electricity_Mod"]/100)
	i_Viral = modApplication(weapon_base_stats["Secondary"]["Viral_Damage"] , modding_stats["Secondary"]["Viral_Mod"]/100)
	i_Corrosiv = modApplication(weapon_base_stats["Secondary"]["Corrosiv_Damage"] , modding_stats["Secondary"]["Corrosiv_Mod"]/100)
	i_Magnetic = modApplication(weapon_base_stats["Secondary"]["Magnetic_Damage"] , modding_stats["Secondary"]["Magnetic_Mod"]/100)
	i_Radiation = modApplication(weapon_base_stats["Secondary"]["Radiation_Damage"] , modding_stats["Secondary"]["Radiation_Mod"]/100)
	i_Gaz = modApplication(weapon_base_stats["Secondary"]["Gaz_Damage"] , modding_stats["Secondary"]["Gaz_Mod"]/100)
	i_Blast = modApplication(weapon_base_stats["Secondary"]["Blast_Damage"] , modding_stats["Secondary"]["Blast_Mod"]/100)
	i_Void = modApplication(weapon_base_stats["Secondary"]["Void_Damage"] , modding_stats["Secondary"]["Void_Mod"]/100)

	E_E = i_Impact + i_Puncture + i_Slash + i_Cold + i_Fire + i_Toxin + i_Electricity + i_Viral + i_Corrosiv + i_Magnetic + i_Radiation + i_Gaz + i_Blast + i_Void

	poids_Impact = i_Impact / E_E
	poids_Puncture = i_Puncture / E_E
	poids_Slash = i_Slash / E_E
	poids_Cold = i_Cold / E_E
	poids_Fire = i_Fire / E_E
	poids_Toxin = i_Toxin / E_E
	poids_Electricity = i_Electricity / E_E
	poids_Viral = i_Viral / E_E
	poids_Corrosiv = i_Corrosiv / E_E
	poids_Magnetic = i_Magnetic / E_E
	poids_Radiation = i_Radiation / E_E
	poids_Gaz = i_Gaz / E_E
	poids_Blast = i_Blast / E_E
	poids_Void = i_Void / E_E

	if (moreLog):
		print("Poids Impact Status = {}".format(poids_Impact))
		print("Poids Puncture Status = {}".format(poids_Puncture))
		print("Poids Slash Status = {}".format(poids_Slash))
		print("Poids Cold Status = {}".format(poids_Cold))
		print("Poids Fire Status = {}".format(poids_Fire))
		print("Poids Toxin Status = {}".format(poids_Toxin))
		print("Poids Electricity Status = {}".format(poids_Electricity))
		print("Poids Viral Status = {}".format(poids_Viral))
		print("Poids Corrosiv Status = {}".format(poids_Corrosiv))
		print("Poids Magnetic Status = {}".format(poids_Magnetic))
		print("Poids Radiation Status = {}".format(poids_Radiation))
		print("Poids Gaz Status = {}".format(poids_Gaz))
		print("Poids Blast Status = {}".format(poids_Blast))
		print("Poids Void Status = {}".format(poids_Void))

	if (statusCalculationMethod == "average"):
		#Heat
		HEAT_Step1 = Step_DMG(Total_Quantized_Damage_DoT, Final_Damage_Mult)
		HEAT_Step2 = Step_FACTION(HEAT_Step1, Final_Faction)
		HEAT_Step3 = Step_CRITICAL(HEAT_Step2, Final_Critical_Chance, Final_Critical_Multiplier, Final_Head_Mult, Total_Other_Headshot_Bonus, critCalculationMethod, parametres["Other"]["isHeadshot"])
		Heat_Tick_Damage = HEAT_Step3 * 0.5 * (1 + modding_stats["HCET"]["Fire_Mod"]/100) * Final_Faction * (1 + Final_Status_Damage_Mult/100) * ( 1 + enemy_stats["Vulnerability"]["Fire_Vulnerabilities"] / 100 ) 
		Total_Heat_Proc_Damage = Heat_Tick_Damage * Final_Status_Duration
		#Toxic
		TOXIN_Step1 = Step_DMG(Total_Quantized_Damage_DoT, Final_Damage_Mult)
		TOXIN_Step2 = Step_FACTION(TOXIN_Step1, Final_Faction)
		TOXIN_Step3 = Step_CRITICAL(TOXIN_Step2, Final_Critical_Chance, Final_Critical_Multiplier, Final_Head_Mult, Total_Other_Headshot_Bonus, critCalculationMethod, parametres["Other"]["isHeadshot"])
		Toxin_Tick_Damage = TOXIN_Step3 * 0.5 * (1 + modding_stats["HCET"]["Toxin_Mod"]/100) * Final_Faction * (1 + Final_Status_Damage_Mult/100) * ( 1 + enemy_stats["Vulnerability"]["Toxin_Vulnerabilities"] / 100 ) 
		Total_Toxin_Proc_Damage = Toxin_Tick_Damage * Final_Status_Duration
		#Slash
		SLASH_Step1 = Step_DMG(Total_Quantized_Damage_DoT, Final_Damage_Mult)
		SLASH_Step2 = Step_FACTION(SLASH_Step1, Final_Faction)
		SLASH_Step3 = Step_CRITICAL(SLASH_Step2, Final_Critical_Chance, Final_Critical_Multiplier, Final_Head_Mult, Total_Other_Headshot_Bonus, critCalculationMethod, parametres["Other"]["isHeadshot"])
		Slash_Tick_Damage = SLASH_Step3 * 0.35 * Final_Faction * (1 + Final_Status_Damage_Mult/100) * ( 1 + enemy_stats["Vulnerability"]["Slash_Vulnerabilities"] / 100 ) 
		Total_Slash_Proc_Damage = Slash_Tick_Damage * Final_Status_Duration
		#Gas
		GAS_Step1 = Step_DMG(Total_Quantized_Damage_DoT, Final_Damage_Mult)
		GAS_Step2 = Step_FACTION(GAS_Step1, Final_Faction)
		GAS_Step3 = Step_CRITICAL(GAS_Step2, Final_Critical_Chance, Final_Critical_Multiplier, Final_Head_Mult, Total_Other_Headshot_Bonus, critCalculationMethod, parametres["Other"]["isHeadshot"])
		Gas_Tick_Damage = GAS_Step3 * 0.5 * Final_Faction * (1 + Final_Status_Damage_Mult/100) * ( 1 + enemy_stats["Vulnerability"]["Gaz_Vulnerabilities"] / 100 ) 
		Total_Gas_Proc_Damage = Gas_Tick_Damage * Final_Status_Duration
		#Electricity
		ELECTRICITY_Step1 = Step_DMG(Total_Quantized_Damage_DoT, Final_Damage_Mult)
		ELECTRICITY_Step2 = Step_FACTION(ELECTRICITY_Step1, Final_Faction)
		ELECTRICITY_Step3 = Step_CRITICAL(ELECTRICITY_Step2, Final_Critical_Chance, Final_Critical_Multiplier, Final_Head_Mult, Total_Other_Headshot_Bonus, critCalculationMethod, parametres["Other"]["isHeadshot"])
		Electricity_Tick_Damage = ELECTRICITY_Step3 * 0.5 * (1 + modding_stats["HCET"]["Electricity_Mod"]/100) * Final_Faction * (1 + Final_Status_Damage_Mult/100) * ( 1 + enemy_stats["Vulnerability"]["Electricity_Vulnerabilities"] / 100 ) 
		Total_Electricity_Proc_Damage = Electricity_Tick_Damage * Final_Status_Duration
		#Blast
		BLAST_Step1 = Step_DMG(Total_Quantized_Damage_DoT, Final_Damage_Mult)
		BLAST_Step2 = Step_FACTION(BLAST_Step1, Final_Faction)
		BLAST_Step3 = Step_CRITICAL(BLAST_Step2, Final_Critical_Chance, Final_Critical_Multiplier, Final_Head_Mult, Total_Other_Headshot_Bonus, critCalculationMethod, parametres["Other"]["isHeadshot"])
		Blast_Proc_Damage = BLAST_Step3 * 0.3 * Final_Faction * (1 + Final_Status_Damage_Mult/100) * ( 1 + enemy_stats["Vulnerability"]["Blast_Vulnerabilities"] / 100 )
		if enemy_stats["Status"]["blast_Stacks"] >= 10:
			Blast_Proc_Damage = Blast_Proc_Damage * 10

		#Represente les dmg theorique d'un unique hit qui trigger tout les elements de dmg ponderer par leur poids et la chance de status
		Total_Status_Proc_Damage = Final_Status_Chance/100 * (Total_Heat_Proc_Damage * poids_Fire \
													+ Total_Electricity_Proc_Damage * poids_Electricity \
													+ Total_Gas_Proc_Damage * poids_Gaz \
													+ Total_Toxin_Proc_Damage * poids_Toxin \
													+ Total_Slash_Proc_Damage * poids_Slash \
													+ Blast_Proc_Damage * poids_Blast)

	elif (statusCalculationMethod == "manual"):
		#Heat
		if (enemy_stats["Status"]["heat_Stacks"] > 0):
			HEAT_Step1 = Step_DMG(Total_Quantized_Damage_DoT, Final_Damage_Mult)
			HEAT_Step2 = Step_FACTION(HEAT_Step1, Final_Faction)
			HEAT_Step3 = Step_CRITICAL(HEAT_Step2, Final_Critical_Chance, Final_Critical_Multiplier, Final_Head_Mult, Total_Other_Headshot_Bonus, critCalculationMethod, parametres["Other"]["isHeadshot"])
			Heat_Tick_Damage = HEAT_Step3 * 0.5 * (1 + modding_stats["HCET"]["Fire_Mod"]/100) * Final_Faction * (1 + Final_Status_Damage_Mult/100) * ( 1 + enemy_stats["Vulnerability"]["Fire_Vulnerabilities"] / 100 ) 
			Total_Heat_Proc_Damage = Heat_Tick_Damage * Final_Status_Duration
		else:
			Heat_Tick_Damage = 0
			Total_Heat_Proc_Damage = 0
		#Toxic
		if (enemy_stats["Status"]["toxin_Stacks"] > 0):
			TOXIN_Step1 = Step_DMG(Total_Quantized_Damage_DoT, Final_Damage_Mult)
			TOXIN_Step2 = Step_FACTION(TOXIN_Step1, Final_Faction)
			TOXIN_Step3 = Step_CRITICAL(TOXIN_Step2, Final_Critical_Chance, Final_Critical_Multiplier, Final_Head_Mult, Total_Other_Headshot_Bonus, critCalculationMethod, parametres["Other"]["isHeadshot"])
			Toxin_Tick_Damage = TOXIN_Step3 * 0.5 * (1 + modding_stats["HCET"]["Toxin_Mod"]/100) * Final_Faction * (1 + Final_Status_Damage_Mult/100) * ( 1 + enemy_stats["Vulnerability"]["Toxin_Vulnerabilities"] / 100 ) 
			Total_Toxin_Proc_Damage = Toxin_Tick_Damage * Final_Status_Duration
		else:
			Toxin_Tick_Damage = 0
			Total_Toxin_Proc_Damage = 0
		#Slash
		if (enemy_stats["Status"]["slash_Stacks"] > 0):
			SLASH_Step1 = Step_DMG(Total_Quantized_Damage_DoT, Final_Damage_Mult)
			SLASH_Step2 = Step_FACTION(SLASH_Step1, Final_Faction)
			SLASH_Step3 = Step_CRITICAL(SLASH_Step2, Final_Critical_Chance, Final_Critical_Multiplier, Final_Head_Mult, Total_Other_Headshot_Bonus, critCalculationMethod, parametres["Other"]["isHeadshot"])
			Slash_Tick_Damage = SLASH_Step3 * 0.35 * Final_Faction * (1 + Final_Status_Damage_Mult/100) * ( 1 + enemy_stats["Vulnerability"]["Slash_Vulnerabilities"] / 100 ) 
			Total_Slash_Proc_Damage = Slash_Tick_Damage * Final_Status_Duration
		else:
			Slash_Tick_Damage = 0
			Total_Slash_Proc_Damage = 0
		#Gas
		if (enemy_stats["Status"]["gas_Stacks"] > 0):
			GAS_Step1 = Step_DMG(Total_Quantized_Damage_DoT, Final_Damage_Mult)
			GAS_Step2 = Step_FACTION(GAS_Step1, Final_Faction)
			GAS_Step3 = Step_CRITICAL(GAS_Step2, Final_Critical_Chance, Final_Critical_Multiplier, Final_Head_Mult, Total_Other_Headshot_Bonus, critCalculationMethod, parametres["Other"]["isHeadshot"])
			Gas_Tick_Damage = GAS_Step3 * 0.5 * Final_Faction * (1 + Final_Status_Damage_Mult/100) * ( 1 + enemy_stats["Vulnerability"]["Gaz_Vulnerabilities"] / 100 ) 
			Total_Gas_Proc_Damage = Gas_Tick_Damage * Final_Status_Duration
		else:
			Gas_Tick_Damage = 0
			Total_Gas_Proc_Damage = 0
		#Electricity
		if (enemy_stats["Status"]["eletricity_Stacks"] > 0):
			ELECTRICITY_Step1 = Step_DMG(Total_Quantized_Damage_DoT, Final_Damage_Mult)
			ELECTRICITY_Step2 = Step_FACTION(ELECTRICITY_Step1, Final_Faction)
			ELECTRICITY_Step3 = Step_CRITICAL(ELECTRICITY_Step2, Final_Critical_Chance, Final_Critical_Multiplier, Final_Head_Mult, Total_Other_Headshot_Bonus, critCalculationMethod, parametres["Other"]["isHeadshot"])
			Electricity_Tick_Damage = ELECTRICITY_Step3 * 0.5 * (1 + modding_stats["HCET"]["Electricity_Mod"]/100) * Final_Faction * (1 + Final_Status_Damage_Mult/100) * ( 1 + enemy_stats["Vulnerability"]["Electricity_Vulnerabilities"] / 100 ) 
			Total_Electricity_Proc_Damage = Electricity_Tick_Damage * Final_Status_Duration
		else:
			Electricity_Tick_Damage = 0
			Total_Electricity_Proc_Damage = 0
		#Blast
		if (enemy_stats["Status"]["blast_Stacks"] > 0):
			BLAST_Step1 = Step_DMG(Total_Quantized_Damage_DoT, Final_Damage_Mult)
			BLAST_Step2 = Step_FACTION(BLAST_Step1, Final_Faction)
			BLAST_Step3 = Step_CRITICAL(BLAST_Step2, Final_Critical_Chance, Final_Critical_Multiplier, Final_Head_Mult, Total_Other_Headshot_Bonus, critCalculationMethod, parametres["Other"]["isHeadshot"])
			Blast_Proc_Damage = BLAST_Step3 * 0.3 * Final_Faction * (1 + Final_Status_Damage_Mult/100) * ( 1 + enemy_stats["Vulnerability"]["Blast_Vulnerabilities"] / 100 )
			if enemy_stats["Status"]["blast_Stacks"] >= 10:
				Blast_Proc_Damage = Blast_Proc_Damage * 10
		else:
			Blast_Proc_Damage = 0

		#Represente les dmg theorique d'un hit qui applique un certain nombre de stacks predeterminer (n'est pas influencer pas la chance de status)
		Total_Status_Proc_Damage = Total_Heat_Proc_Damage * enemy_stats["Status"]["heat_Stacks"] \
					  + Total_Electricity_Proc_Damage * enemy_stats["Status"]["eletricity_Stacks"] \
					  + Total_Gas_Proc_Damage * enemy_stats["Status"]["gas_Stacks"] \
					  + Total_Slash_Proc_Damage * enemy_stats["Status"]["slash_Stacks"] \
					  + Total_Toxin_Proc_Damage * enemy_stats["Status"]["toxin_Stacks"] \
					  + Blast_Proc_Damage * enemy_stats["Status"]["blast_Stacks"]

	elif (statusCalculationMethod == "ns"):
		Total_Status_Proc_Damage = 0
		Heat_Tick_Damage = 0
		Total_Heat_Proc_Damage = 0
		Toxin_Tick_Damage = 0
		Total_Toxin_Proc_Damage = 0
		Slash_Tick_Damage = 0
		Total_Slash_Proc_Damage = 0
		Gas_Tick_Damage = 0
		Total_Gas_Proc_Damage = 0
		Electricity_Tick_Damage = 0
		Total_Electricity_Proc_Damage = 0
		Blast_Proc_Damage = 0

	else:
		print("ERROR: Wrong Status Calculation Method Used\nUsing 'No Status effects' per default")
		Total_Status_Proc_Damage = 0
		Heat_Tick_Damage = 0
		Total_Heat_Proc_Damage = 0
		Toxin_Tick_Damage = 0
		Total_Toxin_Proc_Damage = 0
		Slash_Tick_Damage = 0
		Total_Slash_Proc_Damage = 0
		Gas_Tick_Damage = 0
		Total_Gas_Proc_Damage = 0
		Electricity_Tick_Damage = 0
		Total_Electricity_Proc_Damage = 0
		Blast_Proc_Damage = 0

	#------------------------------------------------------------------
	#XATA Instance Calculation         étrange deviation de -5% à -1% quand on augmente le nombre
	#Xata's Whispers
	def Step_XATA(dmg, ability_strength, isXATA):
		if(isXATA):
			return dmg * (0.26 * ability_strength/100)
		else:
			return 0

	XATA_Initial_Hit = Step_XATA(Final_Original_Single_Hit_Damage_Instance, parametres["Warframe_Stats"]["Ability_Strength"], parametres["Buff"]["isXATA"])
	XATA_Step1 = Step_FACTION(XATA_Initial_Hit, Final_Faction)
	if (parametres["Other"]["isHeadshot"]):
		XATA_Step2 = XATA_Step1 * Final_Head_Mult * (1 + Total_Other_Headshot_Bonus/100)
	else:
		XATA_Step2 = XATA_Step1

	XATA_Final_Hit = XATA_Step2
	#------------------------------------------------------------------
	Total_Final_Damage = Final_Original_Single_Hit_Damage_Instance + XATA_Final_Hit + Total_Status_Proc_Damage
	#------------------------------------------------------------------
	#DPS Calculations
	Time_to_Empty_Magazine =  Final_Magazine_Size / Final_Firerate
	Time_Total_Magazine = Time_to_Empty_Magazine + Final_Reload_Time
	DPS_noReload = (Total_Final_Damage * Final_Magazine_Size) / Time_to_Empty_Magazine
	DPS_Reload = (Total_Final_Damage * Final_Magazine_Size) / Time_Total_Magazine

	#------------------------------------------------------------------
	print("[Debug]")
	print("----------")
	print("Enemy_Base_Armor_Multiplier = {}".format(Enemy_Base_Armor_Multiplier))
	print("Enemy_Armor = {}".format(round(Enemy_Armor, 2)))
	print("Enemy_DR = {}%".format(round(Enemy_DR, 2)))
	print("----------")
	print("Scale = {}".format(Scale))
	print("----------")
	print("Critical Calculation Method: {}".format(critCalculationMethod))
	print("Step 0: Quantized Base Damage = {}".format(Total_Quantized_Damage))
	print("Step 1: Damage Mod Application = {}".format(Step1))
	print("Step 2: Faction Mods & Roar Application = {}".format(Step2))
	print("Step 3: Critical Mods & Headshots Application = {}".format(Step3))
	print("Step 4: Multishot Mods Application = {}".format(Step4))
	print("Step 5: Eclipse Application = {}".format(Step5))
	print("Step 6: Enemy Damage Reduction Application = {}".format(Step6))
	print("Step 7: Viral Stacks Application = {}".format(Step7))
	print("Final Original Single Hit Damage = {} / {}".format(round(Final_Original_Single_Hit_Damage_Instance), Final_Original_Single_Hit_Damage_Instance))
	print("----------")
	print("Status Calculation Method: {}".format(statusCalculationMethod))
	print("Slash Tick Damage = {}".format(Slash_Tick_Damage))
	print("Slash Proc Damage = {}".format(Total_Slash_Proc_Damage))
	print("Heat Tick Damage = {}".format(Heat_Tick_Damage))
	print("Heat Proc Damage = {}".format(Total_Heat_Proc_Damage))
	print("Toxin Tick Damage = {}".format(Toxin_Tick_Damage))
	print("Toxin Proc Damage = {}".format(Total_Toxin_Proc_Damage))
	print("Electricity Tick Damage = {}".format(Electricity_Tick_Damage))
	print("Electricity Proc Damage = {}".format(Total_Electricity_Proc_Damage))
	print("Gas Tick Damage = {}".format(Gas_Tick_Damage))
	print("Gas Proc Damage = {}".format(Total_Gas_Proc_Damage))
	print("Blast Tick Damage = {}".format(Blast_Proc_Damage))
	print("Total Status Damage Proc = {}".format(Total_Status_Proc_Damage))
	print("----------")
	print("XATA Instance Damage = {}".format(XATA_Final_Hit))
	print("----------")
	print("DPS = {}".format(DPS_noReload))
	print("DPS (reload time accounted for) = {}".format(DPS_Reload))
	print("----------")
	print("Total Final Damage = {}".format(Total_Final_Damage))

	print("--- End of the Script ---")
	return(DPS_Reload)



if __name__ == "__main__":
	C1 = calculation(Weapon_Base_Stats_Dict["Artemis"], Modding_Stats_Dict["Artemis_Crepuscular_Growing"], Enemy_Stats_Dict["Corpus_Demolyst"], Parametres["XATA_Artemis_Crepuscular_Growing"])
	C2 = calculation(Weapon_Base_Stats_Dict["Artemis"], Modding_Stats_Dict["Artemis_Crepuscular_Comradery"], Enemy_Stats_Dict["Corpus_Demolyst"], Parametres["XATA_Artemis_Crepuscular_Comradery"])
	print("\n{} / {}".format(round(C1),round(C2)))
	if (C1 > C2):
		print("C1 > C2: Delta = {}".format(round(C1)-round(C2)))
		print("Diminution de {} %".format(round((round(C1)-round(C2))/C1*100)))
	else:
		print("C2 > C1: Delta = {}".format(round(C2)-round(C1)))
		print("Augmentation de {} %".format(round((round(C2)-round(C1))/C1*100)))

#	parser = argparse.ArgumentParser(description="Script that calculate/compare weapon damage output")
#	parser.add_argument("--weapon1Data", required=True, type=str)
#	parser.add_argument("--weapon2Data", required=False, type=str)
#	parser.add_argument("--moddingData", required=True, type=str)
#	parser.add_argument("--enemyData", required=True, type=str)
#	args = parser.parse_args()

#	num1 = args.weapon1Data
#	num2 = args.weapon2Data
#	num3 = args.moddingData
#	num4 = args.enemyData

#python tests.py --num1=1 --num2=2 --num3=3