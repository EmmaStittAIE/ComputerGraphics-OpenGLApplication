#pragma once
#include <sstream>
#include <fstream>

namespace Utils
{
	inline const std::string LoadFileToString(std::string filePath)
	{
		std::stringstream fileContent;

		std::ifstream file;
		file.open(filePath, file.in);

		if (file.fail())
		{
			// TODO: error reporting
			return "";
		}

		while (!(file.peek() == EOF))
		{
			fileContent << (char)file.get();
		}

		return fileContent.str();
	}
}