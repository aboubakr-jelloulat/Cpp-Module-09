#include "BitcoinExchange.h"

// declare static member 
std::map<std::string, float> BitcoinExchange::data;

// oth
BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& src) 
{
	*this = src; 
}


BitcoinExchange& BitcoinExchange::operator=( const BitcoinExchange& src ) 
{
	if (this != &src)
		this->data = src.data;

	return *this;
}

BitcoinExchange::~BitcoinExchange() {}



// init data

// BitcoinExchange::InitData()
// {


// }


