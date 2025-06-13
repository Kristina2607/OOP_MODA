#include "SerializeFunctions.h"
#include "Administrator.h"
#include "Client.h"
#include "Business.h"
#include <fstream>

size_t SerializeFunctions::getFileSize(std::ifstream& ifs)
{
	size_t currPos = ifs.tellg();
	ifs.seekg(0, std::ios::end);
	size_t size = ifs.tellg();
	ifs.seekg(currPos, std::ios::beg);
	return size;
}

void SerializeFunctions::loadUsersFromFile()
{
	std::ifstream ifs("users.dat", std::ios::binary);
	if (!ifs.is_open())
	{
		std::ofstream ofs("users.dat", std::ios::binary);
		ofs.close();
		return;
	}
	if (getFileSize(ifs) == 0)
	{
		return;
	}
	while (true)
	{

		if (ifs.eof())
		{
			break;
		}

		MyString name = readStringFromFile(ifs);
		MyString password = readStringFromFile(ifs);
		MyString EGN = readStringFromFile(ifs);
		MyString role = readStringFromFile(ifs);
	}

	ifs.close();
}

void SerializeFunctions::writeStringToFile(std::ofstream& ofs, const MyString& str)
{
	int len = str.getSize();
	ofs.write((const char*)&len, sizeof(int));
	ofs.write(str.c_str(), sizeof(char) * len);
}

MyString SerializeFunctions::readStringFromFile(std::ifstream& ifs)
{
	int len = 0;
	ifs.read((char*)&len, sizeof(len));

	char* buff = new char[len + 1];
	ifs.read(buff, sizeof(char) * len);

	buff[len] = '\0';

	MyString toReturn(buff);

	delete[] buff;

	return toReturn;
}
