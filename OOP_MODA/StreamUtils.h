#pragma once
#include <fstream>
#include "MyString.h"

namespace StreamUtils
{
	bool fileExists(const MyString& filename);
	void createEmptyFile(const MyString& filename);
	bool isEmptyFile(const MyString& filename);
}