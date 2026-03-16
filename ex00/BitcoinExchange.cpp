#include "BitcoinExchange.hpp"

std::map<std::string, float> BitcoinExchange::data;

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




void BitcoinExchange::InitData()
{
	std::string filename = "./database/data.csv";
	std::ifstream file;

	file.open(filename.c_str());
	if (!file.is_open())
		throw std::runtime_error("Could not open file: " + filename);
	
	std::string line;
	std::getline(file, line); 

	while (std::getline(file, line)) 
	{
		if (line.empty())
			continue;

		int commaPos = line.find(',');
		if (commaPos != std::string::npos) 
		{
			std::string date = line.substr(0, commaPos);
			std::string valStr = line.substr(commaPos + 1);
			
			float value = std::atof(valStr.c_str());

			BitcoinExchange::data[date] = value;
		}
	}
	file.close();
}


static bool isAllDigits(const std::string& s)
{
    for (int i = 0; i < s.size(); i++)
        if (!std::isdigit(s[i]))
            return false;
    return true;
}

bool IsValidDate(const std::string& date)
{
    // "YYYY-MM-DD"
    if (date.length() != 10 || date[4] != '-' || date[7] != '-')
        return false;

    std::string year  = date.substr(0, 4);
    std::string month = date.substr(5, 2);
    std::string day   = date.substr(8, 2);

    if (!isAllDigits(year) || !isAllDigits(month) || !isAllDigits(day))
        return false;

    int mnth = std::atoi(month.c_str());
    int dy = std::atoi(day.c_str());

    if (mnth < 1 || mnth > 12 || dy < 1 || dy > 31)
        return false;

    // months with max 30 days
    if ((mnth == 4 || mnth == 6 || mnth == 9 || mnth == 11) && dy > 30)
        return false;

    // february
    int yr = std::atoi(year.c_str());
    bool leap = (yr % 4 == 0 && yr % 100 != 0) || (yr % 400 == 0);
    if (mnth == 2 && dy > (leap ? 29 : 28))
        return false;

    return true;
}

bool ValidateValue(const std::string& valStr, const std::string& date)
{
    float val;
    std::stringstream stream(valStr);
    stream >> val;

    if (!stream.eof() || stream.fail())
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

    // find closest lower-or-equal date in DB
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

    std::cout << date << " => " << val << " = "
              << val * it->second << std::endl;
    return true;
}

void	ParseAndValidateInput(std::string filename)
{
	std::ifstream file;
	file.open(filename.c_str());

	if (!file.is_open())
		throw std::runtime_error("Could not open file: " + filename);
	
	std::string line;
	std::getline(file, line); 

	while (std::getline(file, line)) 
	{
		if (line.empty())
        	continue;

		int sep = line.find(" | ");
		if (sep == std::string::npos)
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			// continue;
			return ;
		}

		std::string date    = line.substr(0, sep);
		std::string valStr  = line.substr(sep + 3); // skip " | "

		if (!IsValidDate(date))
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			// continue;
			return ;
		}

		ValidateValue(valStr, date);
	}
	file.close();

}


