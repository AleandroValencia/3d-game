//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: ciniparser.h
// Description	: INI parser declaration file
// Author		: Aleandro Valencia
// Mail			: aleandro.val6884@mediadesign.school.nz
//

#ifndef _CINIPARSER_H__
#define _CINIPARSER_H__

#include <stdlib.h>
#include <map>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

class CINIParser
{
public:

	CINIParser();
	~CINIParser();

	// Load an INI file.
	// Populates the map with keys and values using
	// the add value function.
	bool LoadIniFile(const char* _pcFilename);
	
	// Adds a value to the map.
	// Combines the _pcSection, with _pcKey to create a
	// key for the map.
	bool AddValue(const char* _pcSection, const char* _pcKey, const char* _pcValue);
	
	// GetStringValue
	// Returns true if the value was found.
	// _rStrValue will be populated with the correct data if // the key is found in the map.
	bool GetStringValue(const char* _pcSection, const char* _pcKey, std::string& _rStrValue);
	
	// GetIntValue
	// Returns true if the value was found.
	// _riValue will be populated with the correct data if
	// the key is found in the map.
	bool GetIntValue(const char* _pcSection, const char* _pcKey, int& _riValue);
	
	// GetFloatValue
	// Returns true if the value was found.
	// _rfValue will be populated with the correct data if
	// the key is found in the map.
	bool GetFloatValue(const char* _pcSection, const char* _pcKey, float& _rfValue);
	
	// GetBoolValue
	// Returns true if the value was found.
	// _rbValue will be populated with the correct data if
	// the key is found in the map.
	bool GetBoolValue(const char* _pcSection, const char* _pcKey, bool& _rbValue);

	// SetStringValue
	// Returns true if the value was found.
	// _rStrValue will be populated with the correct data if // the key is found in the map.
	bool SetStringValue(const char* _pcSection, const char* _pcKey, std::string& _rStrValue);

	// SetIntValue
	// Returns true if the value was found.
	// _riValue will be populated with the correct data if
	// the key is found in the map.
	bool SetIntValue(const char* _pcSection, const char* _pcKey, int& _riValue);

	// SetFloatValue
	// Returns true if the value was found.
	// _rfValue will be populated with the correct data if
	// the key is found in the map.
	bool SetFloatValue(const char* _pcSection, const char* _pcKey, float& _rfValue);

	// SetBoolValue
	// Returns true if the value was found.
	// _rbValue will be populated with the correct data if
	// the key is found in the map.
	bool SetBoolValue(const char* _pcSection, const char* _pcKey, bool& _rbValue);

	std::string CombineSectionKey(const char* _pcSection, const char* _pcKey);	

private:
	std::map<std::string, std::string> m_mapPairs;

};

#endif //_CINIPARSER_H__