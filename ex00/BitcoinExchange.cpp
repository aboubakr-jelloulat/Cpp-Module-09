#include "BitcoinExchange.hpp"

std::map<std::string, float> BitcoinExchange::data;

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& src)
{
	*this = src;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& src)
{
	if (this != &src)
		this->data = src.data;
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}


void BitcoinExchange::InitData()
{
	std::string filename = "./database/data.csv";
	std::ifstream file;

	file.open(filename.c_str());
	if (!file.is_open())
		throw std::runtime_error("could not open file: " + filename);

	std::string line;
	std::getline(file, line); // skip 1st line

	while (std::getline(file, line))
	{
		if (line.empty())
			continue;

		size_t commaPos = line.find(',');
		if (commaPos != std::string::npos)
		{
			std::string date   = line.substr(0, commaPos);
			std::string valStr = line.substr(commaPos + 1);

			char* end;
			float value = std::strtof(valStr.c_str(), &end);
			if (*end == '\0')
				BitcoinExchange::data[date] = value;
		}
	}
	file.close();
}


static bool isAllDigits(const std::string& s)
{
	for (size_t i = 0; i < s.size(); i++)
		if (!std::isdigit(s[i]))
			return false;
	return true;
}

bool BitcoinExchange::IsValidDate(const std::string& date)
{
	// YYYY-MM-DD
	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
		return false;

	std::string year  = date.substr(0, 4);
	std::string month = date.substr(5, 2);
	std::string day   = date.substr(8, 2);

	if (!isAllDigits(year) || !isAllDigits(month) || !isAllDigits(day))
		return false;

	int yr   = std::atoi(year.c_str());
	int mnth = std::atoi(month.c_str());
	int dy   = std::atoi(day.c_str());

	if (mnth < 1 || mnth > 12 || dy < 1 || dy > 31)
		return false;

	// months with max 30 days
	if ((mnth == 4 || mnth == 6 || mnth == 9 || mnth == 11) && dy > 30)
		return false;

	// february
	bool leap = (yr % 4 == 0 && yr % 100 != 0) || (yr % 400 == 0);
	if (mnth == 2 && dy > (leap ? 29 : 28))
		return false;

	// check date is not in the future
	std::time_t now  = std::time(NULL);
	std::tm*    today = std::localtime(&now);

	int curYear  = today->tm_year + 1900;
	int curMonth = today->tm_mon + 1;
	int curDay   = today->tm_mday;

	if (yr > curYear) return false;
	if (yr == curYear && mnth > curMonth) return false;
	if (yr == curYear && mnth == curMonth && dy > curDay) return false;

	return true;
}

bool BitcoinExchange::ValidateValue(const std::string& valStr, const std::string& date)
{
	char* end;
	float val = std::strtof(valStr.c_str(), &end);

	if (*end != '\0' || valStr.empty())
	{
		std::cerr << "Error: bad input => " << date << " | " << valStr << std::endl;
		return false;
	}
	if (val < 0)
	{
		std::cerr << "Error: not a positive number." << std::endl;
		return false;
	}
	if (val > 1000)
	{
		std::cerr << "Error: too large a number." << std::endl;
		return false;
	}

	std::map<std::string, float>::iterator it = BitcoinExchange::data.lower_bound(date);
	if (it == BitcoinExchange::data.end() || it->first != date)
	{
		if (it == BitcoinExchange::data.begin())
		{
			std::cerr << "Error: too early date => " << date << std::endl;
			return false;
		}
		--it;
	}

	std::cout << date << " => " << val << " = " << val * it->second << std::endl;
	return true;
}

void BitcoinExchange::ParseAndValidateInput(const std::string& filename)
{
	std::ifstream file;
	file.open(filename.c_str());

	if (!file.is_open())
		throw std::runtime_error("could not open file: " + filename);

	std::string line;
	std::getline(file, line); // skip 1st line

	while (std::getline(file, line))
	{
		if (line.empty())
			continue;

		size_t sep = line.find(" | ");
		if (sep == std::string::npos)
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		std::string date   = line.substr(0, sep);
		std::string valStr = line.substr(sep + 3); // skip " | "

		if (!IsValidDate(date))
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		ValidateValue(valStr, date);
	}
	file.close();
}
