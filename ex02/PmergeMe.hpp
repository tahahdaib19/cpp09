
#ifndef PMERGEME_HPP
#define PMERGEME_HPP
#include <vector>
#include <deque>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <iomanip>
#include <sys/time.h>
#include <set>

class PmergeMe
{
    
    private:
    PmergeMe(void);
    PmergeMe(const PmergeMe &other);
    PmergeMe &operator=(const PmergeMe &other);
    ~PmergeMe(void);
    public:
    static   void ApplyFordJohnson(std::string input);
};


#endif