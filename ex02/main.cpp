#include "PmergeMe.hpp"

int main(int ac, char **av)
{
    if (ac < 2)
    {
        std::cerr << "Usage: ./PmergeMe [positive integer sequence] " << std::endl;
        return 1;
    }

    try
    {
        PmergeMe sorter;
        sorter.run(ac, av);
    }
    catch (const std::exception &ex)
    {
        std::cerr << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
