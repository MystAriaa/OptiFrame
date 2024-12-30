from truc import Parametres
Weapon_Base_Stats_Dict = {
	"Karak" : {
		"IPS" : {"Impact_Damage" : 7.1, "Puncture_Damage" : 6.2, "Slash_Damage" : 9.7},
		"HCET" : {"Cold_Damage" : 0, "Fire_Damage" : 0, "Toxin_Damage" : 0, "Electricity_Damage" : 0},
		"Secondary" : {"Viral_Damage" : 0, "Corrosiv_Damage" : 0, "Magnetic_Damage" : 12.7, "Radiation_Damage" : 0, "Gaz_Damage" : 0, "Blast_Damage" : 0, "Void_Damage" : 0},
		"Critical" : {"Base_Critical_Chance" : 23, "Base_Critical_Multiplier" : 2.1},
		"Status" : {"Base_Status_Chance" : 31, "Base_Duration_Status" : 6},
		"DPS" : {"Base_Firerate" : 11.67, "Base_Projectile_Number" : 1, "Base_Magazine_Size" : 70, "Base_Reload_Time" : 1.7},
		"Other" : {"Base_Faction_Damage_Mult" : 1, "isExalted" : 0}
		},

	"Nagantaka" : {
		"IPS" : {"Impact_Damage" : 1.7, "Puncture_Damage" : 15.6, "Slash_Damage" : 155.7},
		"HCET" : {"Cold_Damage" : 0, "Fire_Damage" : 0, "Toxin_Damage" : 0, "Electricity_Damage" : 0},
		"Secondary" : {"Viral_Damage" : 0, "Corrosiv_Damage" : 0, "Magnetic_Damage" : 0, "Radiation_Damage" : 0, "Gaz_Damage" : 0, "Blast_Damage" : 0, "Void_Damage" : 0},
		"Critical" : {"Base_Critical_Chance" : 25, "Base_Critical_Multiplier" : 2.3},
		"Status" : {"Base_Status_Chance" : 39, "Base_Duration_Status" : 6},
		"DPS" : {"Base_Firerate" : 2.5, "Base_Projectile_Number" : 1, "Base_Magazine_Size" : 11, "Base_Reload_Time" : 2.3},
		"Other" : {"Base_Faction_Damage_Mult" : 1, "isExalted" : 0}
		},

	"Artemis" : {   #At 100% Strength
		"IPS" : {"Impact_Damage" : 33.6, "Puncture_Damage" : 192, "Slash_Damage" : 14.4},
		"HCET" : {"Cold_Damage" : 0, "Fire_Damage" : 0, "Toxin_Damage" : 0, "Electricity_Damage" : 0},
		"Secondary" : {"Viral_Damage" : 0, "Corrosiv_Damage" : 0, "Magnetic_Damage" : 0, "Radiation_Damage" : 0, "Gaz_Damage" : 0, "Blast_Damage" : 0, "Void_Damage" : 0},
		"Critical" : {"Base_Critical_Chance" : 25, "Base_Critical_Multiplier" : 2},
		"Status" : {"Base_Status_Chance" : 20, "Base_Duration_Status" : 6},
		"DPS" : {"Base_Firerate" : 1.25, "Base_Projectile_Number" : 7, "Base_Magazine_Size" : 1, "Base_Reload_Time" : 0.9},
		"Other" : {"Base_Faction_Damage_Mult" : 1, "isExalted" : 1}
		},
	}