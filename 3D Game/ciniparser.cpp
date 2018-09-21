//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: ciniparser.cpp
// Description	: INI parser implementation file
// Author		: Aleandro Valencia
// Mail			: aleandro.val6884@mediadesign.school.nz
//

#include "ciniparser.h"

/***********************
* CINIParser Constructor
* @author: Aleandro Valencia
* @parameter:
* @return:
********************/
CINIParser::CINIParser()
{

}

/***********************
* CINIParser Destructor
* @author: Aleandro Valencia
* @parameter:
* @return:
********************/
CINIParser::~CINIParser()
{

}

/***********************
* CINIParser LoadIniFile: Reads the ini file storing any variables in it.
* @author: Aleandro Valencia
* @parameter: const char* _pcFilename: The name of the ini file to open
* @return bool: if there is an INI file or not
********************/
bool CINIParser::LoadIniFile(const char* _pcFilename)
{
	std::ifstream readFile;
	std::string sLine = "";
	std::string sSection = "";
	std::string sKey = "";
	std::string sValue = "";
	int index = 0;
	const char* cpSection;
	const char* cpKey;
	const char* cpValue;

	readFile.open(_pcFilename);

	if (!readFile.is_open())
	{
		std::ofstream newFile(_pcFilename);
		newFile << "[" << _pcFilename << "]\n" << std::endl;
		return false;
	}
	else
	{
		while (!readFile.eof())
		{
			sKey = "";
			sValue = "";
			index = 0;

			getline(readFile, sLine);
			if (sLine[index] == '[')
			{
				sSection = "";
				++index;
				while (sLine[index] != ']')
				{
					sSection += sLine[index];
					++index;
				}
			}
			else if (sLine[index] == ';')
			{
				//this is a comment
			}
			else if (sLine[index] == '\0')
			{
				//this is whitespace 
			}
			else
			{
				while ((sLine[index] != '=') || ((sLine[index] != ' ')))
				{
					sKey += sLine[index];
					++index;
					if ((sLine[index] == '=') || (sLine[index] == ' '))
					{
						break;
					}
				}

				while ((sLine[index] == ' ') || (sLine[index] == '='))
				{
					++index;
				}

				while (!isspace(sLine[index]))
				{
					sValue += sLine[index];
					++index;
					if (sLine[index] == '\0')
					{
						break;
					}
				}

			}
			
			//std::cout << "sSection = " << sSection << std::endl;
			//std::cout << "sKey = " << sKey << " sValue = " << sValue << std::endl;
			cpSection = sSection.c_str();
			cpKey = sKey.c_str();
			cpValue = sValue.c_str();
			AddValue(cpSection, cpKey, cpValue);
		}

		readFile.close();
		return true;
	}
}

/***********************
* CINIParser AddValue: Assigns the value to it's name using a map and key
* @author: Aleandro Valencia
* @parameter const char* _pcSection: Which section in the INI file to access
* @parameter const char* _pcKey: The name of the variable
* @parameter const char* _pcValue: The value stored in the key
* @return bool: ran the function successfully
********************/
bool CINIParser::AddValue(const char* _pcSection, const char* _pcKey, const char* _pcValue)
{
	// add sKey and sValue to map
	std::string strMapsKey;
	std::string sSection(_pcSection);
	std::string sKey(_pcKey);

	strMapsKey = sSection + '|' + sKey;

	m_mapPairs[strMapsKey] = _pcValue;
	std::cout << strMapsKey << " = " << m_mapPairs[strMapsKey] << std::endl;

	return true;
}

/***********************
* CINIParser GetStringValue: Returns the string stored in the passed in section and key
* @author: Aleandro Valencia
* @parameter const char* _pcSection: Which section in the INI file to access
* @parameter const char* _pcKey: The name of the variable
* @parameter std::string& _rStrValue: The string value stored in the key
* @return bool: if the key was found
********************/
bool CINIParser::GetStringValue(const char* _pcSection, const char* _pcKey, std::string& _rStrValue)
{
	std::string sSection(_pcSection);
	std::string sKey(_pcKey);
	std::string strMapsKey = sSection + '|' + sKey;

	std::map<std::string, std::string>::const_iterator iter;

	for (iter = m_mapPairs.begin(); iter != m_mapPairs.end(); ++iter)
	{
		if (iter->first == strMapsKey)
		{
			_rStrValue = iter->second;
			//std::cout << iter->first << "=> " << iter->second << "\n";
			return true;
		}
	}

	//Couldn't find key
	return false;
}

/***********************
* CINIParser GetIntValue: Returns the integer stored in the passed in section and key
* @author: Aleandro Valencia
* @parameter const char* _pcSection: Which section in the INI file to access
* @parameter const char* _pcKey: The name of the variable
* @parameter int& _riValue: the integer value stored in the key
* @return bool: if the key was found
********************/
bool CINIParser::GetIntValue(const char* _pcSection, const char* _pcKey, int& _riValue)
{
	std::string sSection(_pcSection);
	std::string sKey(_pcKey);
	std::string strMapsKey = sSection + '|' + sKey;

	
	std::map<std::string, std::string>::const_iterator iter;

	for (iter = m_mapPairs.begin(); iter != m_mapPairs.end(); ++iter)
	{
		if (iter->first == strMapsKey)
		{
			std::stringstream sStream(iter->second);
			sStream >> _riValue;
			//std::cout << iter->first << "=> " << iter->second << "\n";
			return true;
		}
	}

	//Couldn't find key
	return false;
}

/***********************
* CINIParser GetFloatValue: Returns the float stored in the passed in section and key
* @author: Aleandro Valencia
* @parameter const char* _pcSection: Which section in the INI file to access
* @parameter const char* _pcKey: The name of the variable
* @parameter float& _rfValue: the float value stored in the key
* @return bool: if the key was found
********************/
bool CINIParser::GetFloatValue(const char* _pcSection, const char* _pcKey, float& _rfValue)
{
	std::string sSection(_pcSection);
	std::string sKey(_pcKey);
	std::string strMapsKey = sSection + '|' + sKey;


	std::map<std::string, std::string>::const_iterator iter;

	for (iter = m_mapPairs.begin(); iter != m_mapPairs.end(); ++iter)
	{
		if (iter->first == strMapsKey)
		{
			std::stringstream sStream(iter->second);
			sStream >> _rfValue;
			//std::cout << iter->first << "=> " << iter->second << "\n";
			return true;
		}
	}

	//Couldn't find key
	return false;
}

/***********************
* CINIParser GetBoolValue: Returns the boolean stored in the passed in section and key
* @author: Aleandro Valencia
* @parameter const char* _pcSection: Which section in the INI file to access
* @parameter const char* _pcKey: The name of the variable
* @parameter bool& _rbValue: the bool value stored in the key
* @return: if the key was found
********************/
bool CINIParser::GetBoolValue(const char* _pcSection, const char* _pcKey, bool& _rbValue)
{
	std::string sSection(_pcSection);
	std::string sKey(_pcKey);
	std::string strMapsKey = sSection + '|' + sKey;


	std::map<std::string, std::string>::const_iterator iter;

	for (iter = m_mapPairs.begin(); iter != m_mapPairs.end(); ++iter)
	{
		if (iter->first == strMapsKey)
		{
			std::stringstream sStream(iter->second);
			sStream >> _rbValue;
			//std::cout << iter->first << "=> " << iter->second << "\n";
			return true;
		}
	}

	//Couldn't find key
	return false;
}

/***********************
* CINIParser SetStringValue: Returns the string stored in the passed in section and key
* @author: Aleandro Valencia
* @parameter const char* _pcSection: Which section in the INI file to access
* @parameter const char* _pcKey: The name of the variable
* @parameter std::string& _rStrValue: The string value stored in the key
* @return bool: if the key was found
********************/
bool CINIParser::SetStringValue(const char* _pcSection, const char* _pcKey, std::string& _rStrValue)
{
	std::string sSection(_pcSection);
	std::string sKey(_pcKey);
	std::string strMapsKey = sSection + '|' + sKey;

	std::map<std::string, std::string>::const_iterator iter;

	for (iter = m_mapPairs.begin(); iter != m_mapPairs.end(); ++iter)
	{
		if (iter->first == strMapsKey)
		{
			_rStrValue = iter->second;
			//std::cout << iter->first << "=> " << iter->second << "\n";
			return true;
		}
	}

	//Couldn't find key
	return false;
}

/***********************
* CINIParser SetIntValue: Returns the integer stored in the passed in section and key
* @author: Aleandro Valencia
* @parameter const char* _pcSection: Which section in the INI file to access
* @parameter const char* _pcKey: The name of the variable
* @parameter int& _riValue: the integer value stored in the key
* @return bool: if the key was found
********************/
bool CINIParser::SetIntValue(const char* _pcSection, const char* _pcKey, int& _riValue)
{
	std::string sSection(_pcSection);
	std::string sKey(_pcKey);
	std::string strMapsKey = sSection + '|' + sKey;


	std::map<std::string, std::string>::const_iterator iter;

	for (iter = m_mapPairs.begin(); iter != m_mapPairs.end(); ++iter)
	{
		if (iter->first == strMapsKey)
		{
			std::stringstream sStream(iter->second);
			sStream >> _riValue;
			//std::cout << iter->first << "=> " << iter->second << "\n";
			return true;
		}
	}

	//Couldn't find key
	return false;
}

/***********************
* CINIParser SetFloatValue: Returns the float stored in the passed in section and key
* @author: Aleandro Valencia
* @parameter const char* _pcSection: Which section in the INI file to access
* @parameter const char* _pcKey: The name of the variable
* @parameter float& _rfValue: the float value stored in the key
* @return bool: if the key was found
********************/
bool CINIParser::SetFloatValue(const char* _pcSection, const char* _pcKey, float& _rfValue)
{
	std::string sSection(_pcSection);
	std::string sKey(_pcKey);
	std::string strMapsKey = sSection + '|' + sKey;


	std::map<std::string, std::string>::const_iterator iter;

	for (iter = m_mapPairs.begin(); iter != m_mapPairs.end(); ++iter)
	{
		if (iter->first == strMapsKey)
		{
			std::stringstream sStream(iter->second);
			sStream >> _rfValue;
			//std::cout << iter->first << "=> " << iter->second << "\n";
			return true;
		}
	}

	//Couldn't find key
	return false;
}

/***********************
* CINIParser SetBoolValue: Returns the boolean stored in the passed in section and key
* @author: Aleandro Valencia
* @parameter const char* _pcSection: Which section in the INI file to access
* @parameter const char* _pcKey: The name of the variable
* @parameter bool& _rbValue: the bool value stored in the key
* @return: if the key was found
********************/
bool CINIParser::SetBoolValue(const char* _pcSection, const char* _pcKey, bool& _rbValue)
{
	std::string sSection(_pcSection);
	std::string sKey(_pcKey);
	std::string strMapsKey = sSection + '|' + sKey;


	std::map<std::string, std::string>::const_iterator iter;

	for (iter = m_mapPairs.begin(); iter != m_mapPairs.end(); ++iter)
	{
		if (iter->first == strMapsKey)
		{
			std::stringstream sStream(iter->second);
			sStream >> _rbValue;
			//std::cout << iter->first << "=> " << iter->second << "\n";
			return true;
		}
	}

	//Couldn't find key
	return false;
}

/***********************
* CINIParser CombineSectionKey: Combines the section and key to form the mapkey
* @author: Aleandro Valencia
* @parameter const char* _pcSection: Which section in the INI file to access
* @parameter const char* _pcKey: The name of the variable
* @return string: the map of the key
********************/
std::string CINIParser::CombineSectionKey(const char* _pcSection, const char* _pcKey)
{
	std::string sSection(_pcSection);
	std::string sKey(_pcKey);
	std::string strMapKey = sSection + "|" + sKey;

	return strMapKey;
}