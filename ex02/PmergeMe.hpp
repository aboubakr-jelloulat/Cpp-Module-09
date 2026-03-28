#pragma once

# include <iostream>
# include <vector>
# include <deque>
# include <ctime>
# include <sstream>
# include <string>
# include <stdexcept>
# include <iomanip>


class PmergeMe
{
    std::vector<int>    _vec;
    std::deque<int>     _deq;

    /* utils */
    template <typename Container>
    void    printSequence(const std::string &title, const Container &c) const;

    static double elapsedMicros(clock_t start, clock_t end);

    /*parse Args*/
    void    parseArgs(int ac, char **av);

    /*sorting algorithme*/
    std::vector<int>    fordJohnsonVec(std::vector<int> &seq);

    void    fordJohnsonDeq(std::deque<int> &seq);

public:

    PmergeMe();
    PmergeMe(const PmergeMe &other);
    PmergeMe &operator=(const PmergeMe &other);
    virtual ~PmergeMe();

    void   run(int ac, char **av);
};
