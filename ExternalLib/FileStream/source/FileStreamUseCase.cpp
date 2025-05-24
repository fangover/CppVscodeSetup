
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

#include "../include/FileStreamUseCase.h"

using namespace FileStream;

FileHandle::FileHandle(const std::string &cstrName, std::ios::openmode mode)
    : m_strFileName(cstrName)
{
    std::filesystem::path oFilePath(cstrName);
    auto oParentDir = oFilePath.parent_path();

    // Ensure diretory existed
    if (!oParentDir.empty() && !std::filesystem::exists(oParentDir))
    {
        std::filesystem::create_directories(oParentDir);
    }

    m_ofsFile.open(cstrName, mode);
    if (!m_ofsFile.is_open())
    {
        std::cerr << "Error opening file: " << cstrName << std::endl;
    }
}

FileHandle::~FileHandle()
{

    if (m_ofsFile)
        m_ofsFile.close();
}

void FileHandle::readFile() const
{
    if (m_ofsFile.is_open())
    {
        m_ofsFile.flush(); // Ensure all buffered data is written
    }

    std::ifstream inFile(m_strFileName);
    if (!inFile.is_open())
    {
        std::cerr << "Error opening file for reading!" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(inFile, line))
    {
        std::cout << line << std::endl;
    }
    inFile.close();
}

void FileHandle::clearFile() const
{
    std::ofstream ofs;
    ofs.open(m_strFileName, std::ofstream::out | std::ofstream::trunc);
    ofs.close();
}
