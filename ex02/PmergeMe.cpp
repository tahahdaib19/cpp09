#include "PmergeMe.hpp"
PmergeMe::PmergeMe(void)
{
}
PmergeMe::PmergeMe(const PmergeMe &other)
{
    *this = other;
}
PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    (void)other;
    return (*this);
}
PmergeMe::~PmergeMe(void)
{
}
template <typename container>
void FillContainer(container &my_container ,std::string input)
{
    my_container.clear();
    std::istringstream iss(input);
    int number;
    while (iss >> number)
    {      
          my_container.push_back(number);
    }
}
template <typename container>
void SortPairs(container &my_container)
{
    typename container::iterator it = my_container.begin();
    while (it != my_container.end())
    {
        typename container::iterator next_it = it;
        ++next_it;
        if (next_it == my_container.end())
            break;
        if (*it > *next_it)
            std::swap(*it, *next_it);
        it = next_it;
        ++it;
    }
}

template <typename container>
void beginSort(container &my_container)
{
   container larger_half;
   container smaller_half;
   typename container::iterator first = my_container.begin();
   typename container::iterator second ;
    while (first != my_container.end())
    {
        second = first;
        if (second != my_container.end())
            second++;
        if (second == my_container.end())
        {
            larger_half.push_back(*first);
            break;
        }
        if (*first > *second)
        {
            larger_half.push_back(*first);
            smaller_half.push_back(*second);
        }
        else
        {
            larger_half.push_back(*second);
            smaller_half.push_back(*first);
        }
         if (second == my_container.end())
            break;
        if (my_container.size() % 2 != 0 && second == my_container.end() - 1)
        {
            larger_half.push_back(*second);
                break;
        }
        first = second;
        ++first;
       
    }
    SortPairs(larger_half);
    std::cout<<"After sorting pairs : ";
    for (typename container::iterator it = larger_half.begin(); it != larger_half.end(); ++it)
    {        std::cout<<*it<<" ";
    }    std::cout<<std::endl;

}

void PmergeMe::ApplyFordJohnson(std::string input)
{
    std::vector<int> vec;
    std::deque<int> deq;
   
    FillContainer(vec, input);
    FillContainer(deq, input);
    beginSort(vec);
    beginSort(deq);


}


