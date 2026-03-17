#pragma once

#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <ctime>
#include <stdexcept>

class BitcoinExchange
{
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange& src);
	BitcoinExchange& operator=(const BitcoinExchange& src);
	virtual ~BitcoinExchange();

	static bool IsValidDate(const std::string& date);
	static bool ValidateValue(const std::string& valStr, const std::string& date);

public:
	static std::map<std::string, float> data;
	static void InitData();
	static void ParseAndValidateInput(const std::string& filename);


};

