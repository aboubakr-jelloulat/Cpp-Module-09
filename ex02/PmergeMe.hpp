#pragma once

# include <iostream>
# include <vector>
# include <deque>
# include <sstream>
# include <string>
# include <iomanip>
# include <algorithm>


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
    std::vector<int>    generateOrdersVec(size_t size);
    std::vector<int>    jacobsthalVec(size_t n);


    std::deque<int>    fordJohnsonDeq(std::deque<int> &seq);
    std::deque<int>    generateOrdersDeq(size_t size);
    std::deque<int>    jacobsthalDeq(size_t n);

public:

    PmergeMe();
    PmergeMe(const PmergeMe &other);
    PmergeMe &operator=(const PmergeMe &other);
    virtual ~PmergeMe();

    void   run(int ac, char **av);
};
