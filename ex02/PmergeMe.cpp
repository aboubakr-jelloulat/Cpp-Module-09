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
void    PmergeMe::printSequence(const std::string &title, const Container &c) const
{
    std::cout << title;
    for (typename Container::const_iterator it = c.begin(); it != c.end(); ++it)
        std::cout << " " << *it;
    std::cout << "\n";
}

double  PmergeMe::elapsedMicros(clock_t start, clock_t end)
{
    return static_cast<double>(end - start) / CLOCKS_PER_SEC * 1e6;
}


/*parse Args*/

void    PmergeMe::parseArgs(int ac, char **av)
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

        if (value > 2147483647)
            throw std::invalid_argument("Error: integer overflow in [" + token + "].");

        _vec.push_back(static_cast<int>(value));
        _deq.push_back(static_cast<int>(value));
    }
}

/*  ********* vector ********* */


std::vector<int>  PmergeMe::fordJohnsonVec(std::vector<int> &seq)
{
    if (seq.size() <= 1)
        return seq;
    
    std::vector<int> a, b, sorted_nums;

    for (size_t i = 0; i < seq.size(); ++i, ++i)
    {
        if (i + 1 < seq.size())
        {
            int big = std::max(seq[i], seq[i + 1]);
            int small = std::min(seq[i], seq[i + 1]);

            a.push_back(big);
            b.push_back(small);
        }
        else
            a.push_back(seq[i]); // handle odd element stragler
    }

    sorted_nums = fordJohnsonVec(a);

    // std::vector<int> indexes = generateOrders(sorted_nums.size());

    return sorted_nums;
}


void    PmergeMe::run(int ac, char **av)
{
    parseArgs(ac, av);

    printSequence("Before:", _vec);

    clock_t vecStart = clock();
    std::vector<int> vect =  fordJohnsonVec(_vec);
    (void)vect; // to avoid unused variable warning

    clock_t vecEnd   = clock();

    clock_t deqStart = clock();
    // fordJohnsonDeq(_deq);
    clock_t deqEnd   = clock();

  
    printSequence("After: ", _vec);

    //  timings
    std::cout << std::fixed << std::setprecision(5);
    std::cout << "Time to process a range of " << _vec.size()
              << " elements with std::vector : "
              << elapsedMicros(vecStart, vecEnd) << " us\n";
    std::cout << "Time to process a range of " << _deq.size()
              << " elements with std::deque  : "
              << elapsedMicros(deqStart, deqEnd) << " us\n";
}

