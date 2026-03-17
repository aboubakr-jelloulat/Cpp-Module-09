#include <iostream>
#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr << "Usage: ./btc [input.txt]" << std::endl;
		return 1;
	}

	try
	{
		BitcoinExchange::InitData();
		BitcoinExchange::ParseAndValidateInput(av[1]);
	}
	catch (const std::exception& ex)
	{
		std::cerr << "Error: " << ex.what() << std::endl;
		return 1;
	}

	return 0;
}
