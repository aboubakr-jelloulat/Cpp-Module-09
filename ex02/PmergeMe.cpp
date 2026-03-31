#include "PmergeMe.hpp"

PmergeMe::PmergeMe() 
{
}

PmergeMe::PmergeMe(const PmergeMe &other) : _vec(other._vec), _deq(other._deq) 
{
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    if (this != &other)
    {
        _vec = other._vec;
        _deq = other._deq;
    }
    return *this;
}

PmergeMe::~PmergeMe() 
{
}

/* utils */

template <typename Container>
void PmergeMe::printSequence(const std::string &title, const Container &c) const
{
    std::cout << title;

    typename Container::const_iterator it;
    for (it = c.begin(); it != c.end(); ++it)
        std::cout << " " << *it;

    std::cout << "\n";
}

/*
    clock_t : CPU time used by your program
*/
double PmergeMe::elapsedMicros(clock_t start, clock_t end)
{
    return static_cast<double>(end - start) / CLOCKS_PER_SEC * 1e6;
}

/* parse Args */

void PmergeMe::parseArgs(int ac, char **av)
{
    for (int i = 1; i < ac; ++i)
    {
        std::string token(av[i]);

        if (token.empty())
            throw std::invalid_argument("Error: empty token.");
        
        for (size_t j = 0; j < token.size(); ++j)
            if (!isdigit(token[j]))
                throw std::invalid_argument("Error: invalid character [ " + token + " ] Enter a digit.");
        
        long value;
        std::istringstream iss(token);
        iss >> value;

        if (value <= 0)
            throw std::invalid_argument("Error: Enter only positive integers.");

        if (value > std::numeric_limits<int>::max())
            throw std::invalid_argument("Error: integer overflow in [" + token + "].");

        _vec.push_back(static_cast<int>(value));
        _deq.push_back(static_cast<int>(value));
    }
}

/* ********* vector ********* */

std::vector<int> PmergeMe::jacobsthalVec(size_t n)
{
    std::vector<int> indexes;

    // formula = J(n) = J(n-1) + 2 * J(n-2) => with J(0) = 0, J(1) = 1

    size_t j_n_minus_2 = 0;
    size_t j_n_minus_1 = 1;
    size_t j_n = 0;

    indexes.push_back(j_n_minus_2);

    if (n >= 1)
        indexes.push_back(j_n_minus_1);

    while (true)
    {
        j_n = j_n_minus_1 + 2 * j_n_minus_2;
        if (j_n > n)
            break;

        indexes.push_back(j_n);
        j_n_minus_2 = j_n_minus_1;
        j_n_minus_1 = j_n;
    }

    return indexes;
}

/*
    Full sequence : [0, 1, 1, 3, 5, 11, 21, 43]

    J(2) = J(1) + 2×J(0) = 1 + 2×0 = 1
    J(3) = J(2) + 2×J(1) = 1 + 2×1 = 3
    J(4) = J(3) + 2×J(2) = 3 + 2×1 = 5
    J(5) = J(4) + 2×J(3) = 5 + 2×3 = 11
    J(6) = J(5) + 2×J(4) = 11 + 2×5 = 21
    J(7) = J(6) + 2×J(5) = 21 + 2×11 = 43
*/

std::vector<int> PmergeMe::generateOrdersVec(size_t size)
{
    std::vector<int> indexes = jacobsthalVec(size);

    // convert to 0 based indexing
    for (std::vector<int>::iterator it = indexes.begin() + 1; it != indexes.end(); ++it)
        *it -= 1;

    std::vector<int> unique;

    // remove duplicates
    for (std::vector<int>::iterator it = indexes.begin(); it != indexes.end(); ++it)
    {
        if (*it >= 0 && *it < static_cast<int>(size) && std::find(unique.begin(), unique.end(), *it) == unique.end())
        {
            unique.push_back(*it);
        }
    }

    // add missing indexes
    for (size_t i = 0; i < size; ++i)
    {
        if (std::find(unique.begin(), unique.end(), i) == unique.end())
            unique.push_back(i);
    }

    return unique;
}

std::vector<int> PmergeMe::fordJohnsonVec(std::vector<int> &seq)
{
    if (seq.size() <= 1)
        return seq;

    std::vector<int> a, b, sorted_nums;

    // split into pairs
    for (size_t i = 0; i + 1 < seq.size(); i += 2)
    {
        int big = std::max(seq[i], seq[i + 1]);
        int small = std::min(seq[i], seq[i + 1]);

        a.push_back(big);
        b.push_back(small);
    }

    // handle odd element
    if (seq.size() % 2 != 0)
        a.push_back(seq.back());

    // recursive sort on "big" elements
    sorted_nums = fordJohnsonVec(a);

    // get insertion order
    std::vector<int> indexes = generateOrdersVec(b.size());

    // insert elements of b into sorted_nums
    for (size_t i = 0; i < indexes.size(); ++i)
    {
        int pos = indexes[i];
        int value = b[pos];

        std::vector<int>::iterator it = std::lower_bound(sorted_nums.begin(), sorted_nums.end(), value);

        sorted_nums.insert(it, value);
    }

    return sorted_nums;
}






/* ********* Deque ********* */

std::deque<int> PmergeMe::jacobsthalDeq(size_t n)
{
    std::deque<int> indexes;

    // formula = J(n) = J(n-1) + 2 * J(n-2) => with J(0) = 0, J(1) = 1

    size_t j_n_minus_2 = 0;
    size_t j_n_minus_1 = 1;
    size_t j_n = 0;

    indexes.push_back(j_n_minus_2);

    if (n >= 1)
        indexes.push_back(j_n_minus_1);

    while (true)
    {
        j_n = j_n_minus_1 + 2 * j_n_minus_2;
        if (j_n > n)
            break;

        indexes.push_back(j_n);
        j_n_minus_2 = j_n_minus_1;
        j_n_minus_1 = j_n;
    }

    return indexes;
}

/*
    Full sequence : [0, 1, 1, 3, 5, 11, 21, 43]

    J(2) = J(1) + 2×J(0) = 1 + 2×0 = 1
    J(3) = J(2) + 2×J(1) = 1 + 2×1 = 3
    J(4) = J(3) + 2×J(2) = 3 + 2×1 = 5
    J(5) = J(4) + 2×J(3) = 5 + 2×3 = 11
    J(6) = J(5) + 2×J(4) = 11 + 2×5 = 21
    J(7) = J(6) + 2×J(5) = 21 + 2×11 = 43
*/

std::deque<int> PmergeMe::generateOrdersDeq(size_t size)
{
    std::deque<int> indexes = jacobsthalDeq(size);

    // convert to 0 based indexing
    for (std::deque<int>::iterator it = indexes.begin() + 1; it != indexes.end(); ++it)
        *it -= 1;

    std::deque<int> unique;

    // remove duplicates
    for (std::deque<int>::iterator it = indexes.begin(); it != indexes.end(); ++it)
    {
        if (*it >= 0 && *it < static_cast<int>(size) && std::find(unique.begin(), unique.end(), *it) == unique.end())
        {
            unique.push_back(*it);
        }
    }

    // add missing indexes
    for (size_t i = 0; i < size; ++i)
    {
        if (std::find(unique.begin(), unique.end(), i) == unique.end())
            unique.push_back(i);
    }

    return unique;
}


std::deque<int> PmergeMe::fordJohnsonDeq(std::deque<int> &seq)
{
    if (seq.size() <= 1)
        return seq;
    
    std::deque<int> a, b, sorted_nums;

    // split into pairs
    for (size_t i = 0; i + 1 < seq.size(); i += 2)
    {
        int big = std::max(seq[i], seq[i + 1]);
        int small = std::min(seq[i], seq[i + 1]);

        a.push_back(big);
        b.push_back(small);
    }

    // handle odd element
    if (seq.size() % 2 != 0)
        a.push_back(seq.back());

    //recursive sort on "big" elements
    sorted_nums = fordJohnsonDeq(a);

    // get insertion order
    std::deque<int> indexes = generateOrdersDeq(b.size());

    //insert elements of b into sorted_nums
    for (size_t i = 0; i < indexes.size(); ++i)
    {
        int pos = indexes[i];
        int value = b[pos];  

        std::deque<int>::iterator it = std::lower_bound(sorted_nums.begin(), sorted_nums.end(), value);

        sorted_nums.insert(it, value);
    }

    return sorted_nums;


    return seq;
}



void PmergeMe::run(int ac, char **av)
{
    parseArgs(ac, av);

    printSequence("Before:", _vec);

    clock_t vecStart = clock();
    std::vector<int> vect = fordJohnsonVec(_vec);
    clock_t vecEnd = clock();

    clock_t deqStart = clock();
    std::deque<int> deq = fordJohnsonDeq(_deq);
    clock_t deqEnd = clock();

    printSequence("After: ", vect);

    std::cout << std::fixed << std::setprecision(5);

    std::cout << "Time to process a range of " << _vec.size() << " elements with std::vector : " << elapsedMicros(vecStart, vecEnd) << " us\n";

    std::cout << "Time to process a range of " << _deq.size() << " elements with std::deque  : " << elapsedMicros(deqStart, deqEnd) << " us" << std::endl;
}
