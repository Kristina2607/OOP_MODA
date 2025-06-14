#include "StreamUtils.h"
#include "MyString.h"

bool StreamUtils::fileExists(const MyString& filename)
{
    std::ifstream file(filename.c_str(), std::ios::binary);
    bool isOpen = file.is_open();
    file.close();
    return isOpen;
}

void StreamUtils::createEmptyFile(const MyString& filename)
{
    std::ofstream file(filename.c_str(), std::ios::binary);
    file.close();
}

bool StreamUtils::isEmptyFile(const MyString& filename)
{
    std::ifstream file(filename.c_str(), std::ios::binary);
    if (!file.is_open()) 
    {
        throw std::logic_error("Couldn't open file!");
    }

    size_t current = file.tellg();
    file.seekg(0, std::ios::end);
    size_t end = file.tellg();

    return current == end;
}
