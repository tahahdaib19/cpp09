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
container jacobsthal(int n)
{
    container result;
    int prev = 1;
    int prev_prev = 0;
    int current = 0;
    if (n == 0)
        return result;
    //result.push_back(prev);
    for (int i = 0; i < n; i++)
    {
       
        current = prev + 2 *prev_prev;
        if (current >= 1)
            result.push_back(current);
        prev_prev = prev;
        prev = current;
    }
    return result;
}

template <typename container>
container jacobsthal_to_index (container &jacobsthal, size_t n)
{
    container indices;
    if (n == 0)
        return indices;
    indices.push_back(0);
   typename container::iterator first_it = jacobsthal.begin();
   if (first_it == jacobsthal.end())
        return indices;
    typename container::iterator second_it =first_it;
    ++second_it;

    while (second_it != jacobsthal.end())
    {
        size_t upper_bound = *second_it;
        size_t lower_bound = *first_it;
        if (lower_bound >= n)
            break;
        if (upper_bound > n)
            upper_bound = n;
         size_t range = upper_bound - lower_bound;
         size_t current_index = upper_bound;
         while (range--)
         {
            indices.push_back(current_index - 1);
            current_index--;
         }

        first_it = second_it;
        ++second_it;
        
    }
    return indices;
}


template <typename container>
container beginSort(container &my_container)
{
   container larger_half;
   container smaller_half;
   int lastElement = 0;
    bool container_is_odd = false;
   typename container::iterator first = my_container.begin();
   typename container::iterator second ;
   if (my_container.size() < 2)
        return my_container;
    if (my_container.size() % 2 != 0) 																				// If there's an odd element, save it to add back later
    {
        lastElement = my_container.back();
        container_is_odd = true;
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
	for(size_t i = 0; i < newMainChain.size(); i++) 															
	{
		size_t prev_index = std::find(larger_half.begin(), larger_half.end(), newMainChain[i]) - larger_half.begin();
		newPendingChain.push_back(smaller_half[prev_index]);
	}
	if (container_is_odd)
		newPendingChain.push_back(lastElement); 																
			
	container finalMainChain = newMainChain; 
    finalMainChain.insert(finalMainChain.begin(), newPendingChain[0]);															
    container jacobsthalSeq = jacobsthal<container>(newPendingChain.size());
    container insertionIndices = jacobsthal_to_index(jacobsthalSeq, newPendingChain.size());

   for (size_t i = 0; i < insertionIndices.size(); i++)
    {
        size_t index = insertionIndices[i];
        if (index == 0) 
            continue;

       int value = newPendingChain[index];
        typename container::iterator correct_pos =std::lower_bound(finalMainChain.begin(),finalMainChain.end(),value);
        finalMainChain.insert(correct_pos, value);
}
   
    return finalMainChain;
}   


void PmergeMe::ApplyFordJohnson(std::string input)
{
    std::vector<int> vec;
    std::deque<int> deq;
 
    FillContainer(vec, input);
    FillContainer(deq, input);

    std::cout << "Before: ";
   std::cout << input << std::endl;
   std::cout << "After: ";

    struct timeval start, end;
    gettimeofday(&start, NULL);
    vec = beginSort(vec);
    gettimeofday(&end, NULL);
    for (size_t i = 0; i < vec.size(); i++)
    {
        std::cout << vec[i] << " ";
    }
    //  std::cout << "Sorted deque: ";
    // for (size_t i = 0; i < deq.size(); i++)
    // {
    //     std::cout << deq[i] << " "; 
    // }
    std::cout << std::endl;
    long seconds = end.tv_sec - start.tv_sec;
    long microseconds = end.tv_usec - start.tv_usec;
    long total = (seconds * 1000000) + microseconds;
    std::cout << "Time to process " << vec.size() << " elements: using vector: " << total << " us" << std::endl;
    gettimeofday(&start, NULL);
    deq = beginSort(deq);
    gettimeofday(&end, NULL);
    seconds = end.tv_sec - start.tv_sec;
    microseconds = end.tv_usec - start.tv_usec;
    total = (seconds * 1000000) + microseconds;

    std::cout << "Time to process " << deq.size() << " elements: using deque : " << total << " us" << std::endl; 
   

}


