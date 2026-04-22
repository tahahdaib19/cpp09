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

std::vector<size_t> generateJacobIndices(size_t n)
{
    std::vector<size_t> result;
    if (n == 0)
        return result;

    std::vector<size_t> jacob;
    jacob.push_back(1);
    jacob.push_back(3);

    while (jacob.back() < n)
        jacob.push_back(jacob[jacob.size() - 1] + 2 * jacob[jacob.size() - 2]);

    size_t prev = 1;

    for (size_t i = 0; i < jacob.size(); i++)
    {
        size_t curr = jacob[i];
        if (curr > n)
            curr = n;

        for (size_t j = curr; j > prev; j--)
            result.push_back(j - 1);

        prev = curr;
        if (curr == n)
            break;
    }

    return result;
}

template <typename container>
container beginSort(container &my_container)
{
   container larger_half;
   container smaller_half;
   int lastElement = 0;
    bool hasLastElement = false;
   typename container::iterator first = my_container.begin();
   typename container::iterator second ;
   if (my_container.size() < 2)
        return my_container;
    if (my_container.size() % 2 != 0) 																				// If there's an odd element, save it to add back later
    {
        lastElement = my_container.back();
        hasLastElement = true;
        my_container.pop_back();
    }
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
        first = second;
        ++first;
       
    }
   container newMainChain = beginSort(larger_half);
	container newPendingChain;
	for(size_t i = 0; i < newMainChain.size(); i++) 															// Reconstruct pending chain based on the order of the new main chain (to maintain the correct pairs)
	{
		size_t oldindex = std::find(larger_half.begin(), larger_half.end(), newMainChain[i]) - larger_half.begin();
		newPendingChain.push_back(smaller_half[oldindex]);
	}
	if (hasLastElement)
		newPendingChain.push_back(lastElement); 																// If there was an odd element, add it to the pending chain
			
	std::vector<int> finalMainChain = newMainChain; 															// Start with the new main chain as the base for the final sorted chain
	finalMainChain.insert(finalMainChain.begin(), newPendingChain.front()); 	

  
    return finalMainChain;


}

void PmergeMe::ApplyFordJohnson(std::string input)
{
    std::vector<int> vec;
    std::deque<int> deq;
   
    FillContainer(vec, input);
    FillContainer(deq, input);
   vec = beginSort(vec);
   std::cout << "Sorted vector: ";
    for (size_t i = 0; i < vec.size(); i++)
    {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
    //deq = beginSort(deq);


}


