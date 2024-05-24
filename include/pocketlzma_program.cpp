//
// Created by robin on 01.01.2021.
//

#define POCKETLZMA_LZMA_C_DEFINE
#include "pocketlzma.hpp"
#include <chrono>

//#include <cstdarg>  // For va_start, etc.

template<typename ... Args>
std::string fmt( const std::string& format, Args ... args )
{
    int size = snprintf( nullptr, 0, format.c_str(), args ... ) + 1; // Extra space for '\0'
    if( size <= 0 ){ throw std::runtime_error( "Error during formatting." ); }
    std::unique_ptr<char[]> buf( new char[ size ] );
    snprintf( buf.get(), size, format.c_str(), args ... );
    return std::string( buf.get(), buf.get() + size - 1 ); // We don't want the '\0' inside
}



const std::string VERSION = fmt("v%d.%d.%d", POCKETLZMA_VERSION_MAJOR, POCKETLZMA_VERSION_MINOR, POCKETLZMA_VERSION_PATCH);

void printHelp()
{
    std::cout << "Welcome to the PocketLzma program " << VERSION << "!\n"
              << "This program is intended to showcase how to use PocketLzma, but you can \n"
              << "also use it as a tool to compress/decompress files.\n\n"
              << "How to use: \n"
              << "<option> <input> <output>(optional for COMPRESSION - appending '.lzma' to <input> value when not used)\n"
              << "Example: -c ./file.json ./file.lzma\n\n"
              << "Example: -d ./file.lzma ./file.json\n\n"
              << "Options: \n"
              << "-h   | --help            - Print help \n"
              << "-d   | --decompress      - Decompress <input> LZMA file \n"
              << "-c   | --compress        - Compress with 'Default' preset \n"
              << "-cf+ | --fastest         - Compress with 'Fastest' preset \n"
              << "-cf  | --fast            - Compress with 'Fast' preset \n"
              << "-cg  | --good            - Compress with 'GoodCompression' preset \n"
              << "-cb  | --best            - Compress with 'BestCompression' preset \n\n";
}

int compress(const std::string &input, const std::string &output, plz::Preset preset)
{
    std::cout << "Compressing '" << input << "' to '" << output << "'...\n";
    plz::PocketLzma p {preset};
    std::vector<uint8_t> data;
    std::vector<uint8_t> compressedData;
    plz::FileStatus fileReadStatus = plz::File::FromFile(input, data);
    if(fileReadStatus.status() != plz::FileStatus::Code::Ok)
    {
        std::cout << "Error reading from file: '" << input << "'. Error - status:" <<
                     (int)fileReadStatus.status() << "message: " << fileReadStatus.message() << "\n\n";
        return 1;
    }

    auto start = std::chrono::steady_clock::now();
    plz::StatusCode status = p.compress(data, compressedData);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> ms = (end-start) * 1000;

    if(status != plz::StatusCode::Ok)
    {
        std::cout << "Error compressing data - StatusCode: " << (int)status << "\n\n";
        return 1;
    }

    plz::FileStatus fileWriteStatus = plz::File::ToFile(output, compressedData);
    if(fileWriteStatus.status() != plz::FileStatus::Code::Ok)
    {
        std::cout << "Error writing to file: '" << output << "'. Error - status:" <<
                  (int)fileWriteStatus.status() << "message: " << fileWriteStatus.message() << "\n\n";
        return 1;
    }

    std::cout << "Successfully compressed data to '" << output << "' in " << ms.count() << " milliseconds! \n\n";

    return 0;
}

int decompress(const std::string &input, const std::string &output)
{
    std::cout << "Decompressing '" << input << "' to '" << output << "'...\n";

    plz::PocketLzma p;
    std::vector<uint8_t> data;
    std::vector<uint8_t> decompressedData;
    plz::FileStatus fileReadStatus = plz::File::FromFile(input, data);
    if(fileReadStatus.status() != plz::FileStatus::Code::Ok)
    {
        std::cout << "Error reading file: " << input << ". Error - status:" <<
                  (int)fileReadStatus.status() << "message: " << fileReadStatus.message() << "\n\n";
        return 1;
    }

    auto start = std::chrono::steady_clock::now();
    plz::StatusCode status = p.decompress(data, decompressedData);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> ms = (end-start) * 1000;

    if(status != plz::StatusCode::Ok)
    {
        std::cout << "Error decompressing data - StatusCode: " << (int)status << "\n\n";
        return 1;
    }

    plz::FileStatus fileWriteStatus = plz::File::ToFile(output, decompressedData);
    if(fileWriteStatus.status() != plz::FileStatus::Code::Ok)
    {
        std::cout << "Error writing to file: '" << output << "'. Error - status:" <<
                  (int)fileWriteStatus.status() << "message: " << fileWriteStatus.message() << "\n\n";
        return 1;
    }

    std::cout << "Successfully decompressed data to '" << output << "' in " << ms.count() << " milliseconds! \n\n";

    return 0;
}

