#include <iostream>
#include "RPN.hpp"

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cerr << "Usage: ./RPN [expression]" << std::endl;
        return 0;
    }

    try
    {
        std::cout << RPN::evalRPN(av[1]) << std::endl;
    }
    catch(std::exception& ex)
    {
		std::cerr << "Error: " << ex.what() << std::endl;
    }


    return 0;
}
