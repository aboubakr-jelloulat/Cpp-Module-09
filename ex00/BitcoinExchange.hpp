#pragma once

#include <iostream>
#include <map>
#include <fstream>


class BitcoinExchange
{
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange& src);
	BitcoinExchange& operator=(const BitcoinExchange& src);
	virtual ~BitcoinExchange();


	static std::map<std::string, float> data;

public:
	static void	InitData();
	static void ParseAndValidateInput();



};
