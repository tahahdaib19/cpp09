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
        if (number < 0)
        {
            throw std::invalid_argument("Negative numbers are not allowed.");
        }
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
   // result.push_back(prev_prev);
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
    // std::cout << "Jacobsthal sequence: ";
    // for (size_t i = 0; i < result.size(); i++)    {
    //     std::cout << result[i] << " ";
    // }
    // std::cout << std::endl;
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
  //  std::cout<< "first_it: " << *first_it << " second_it: " << *second_it << std::endl;

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


// template <typename container>
// container jacobsthal_to_index(container &jacobsthal, size_t n)
// {
//     container indices;

//     if (n == 0)
//         return indices;

//     indices.push_back(0);

//     typename container::iterator first_it = jacobsthal.begin();
//     if (first_it == jacobsthal.end())
//         return indices;

//     typename container::iterator second_it = first_it;
//     ++second_it;

//     while (second_it != jacobsthal.end())
//     {
//         size_t lower = *first_it;
//         size_t upper = *second_it;

//         // 🔥 قصّ الـ range حسب الحجم الحقيقي
//         if (lower >= n)
//             break;
//         if (upper > n)
//             upper = n;

//         // 🔥 reverse insertion داخل الـ range
//         for (size_t i = upper; i > lower; --i)
//         {
//             indices.push_back(i - 1);
//         }

//         first_it = second_it;
//         ++second_it;
//     }

//     return indices;
// }
// template <typename container>
// container generateInsertionIndices(size_t n)
// {
//     container result;
//     if (n == 0)
//         return result;

//     result.push_back(0); // b1

//     size_t j1 = 1;
//     size_t j2 = 3;

//     while (j1 < n)
//     {
//         size_t upper = std::min(j2, n);

//         for (size_t i = upper; i > j1; --i)
//             result.push_back(i - 1);

//         j2 = j2 + 2 * j1;
//         j1 = j2 - 2 * j1;
//     }

//     return result;
// }

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
	for(size_t i = 0; i < newMainChain.size(); i++) 															
	{
		size_t prev_idx = std::find(larger_half.begin(), larger_half.end(), newMainChain[i]) - larger_half.begin();
		newPendingChain.push_back(smaller_half[prev_idx]);
	}
	if (hasLastElement)
		newPendingChain.push_back(lastElement); 																
			
	container finalMainChain = newMainChain; 
    finalMainChain.insert(finalMainChain.begin(), newPendingChain[0]);															
//    container insertionIndices = generateInsertionIndices<container>(newPendingChain.size());
//    std::cout<<"Insertion indices by generateInsertionIndices: ";
//     for (size_t i = 0; i < insertionIndices.size(); i++)    {   
//         std::cout << insertionIndices[i] << " ";
//     }
//     std::cout << std::endl; 

 container jacobsthalSeq = jacobsthal<container>(newPendingChain.size());
  container insertionIndices = jacobsthal_to_index(jacobsthalSeq, newPendingChain.size());
// std::cout<<"Insertion indices by jacobsthal_to_index: ";
//     for (size_t i = 0; i < insertionIndices.size(); i++)    {   
//         std::cout << insertionIndices[i] << " ";
//     }
//     std::cout << std::endl; 
  //container insertionIndices = jacobsthal_to_index(jacobsthalSeq);
  //container insertionIndices = generateInsertionIndices<container>(newPendingChain.size());
   for (size_t k = 0; k < insertionIndices.size(); k++)
    {
        size_t idx = insertionIndices[k];

        if (idx == 0) 
            continue;

        if (idx >= newPendingChain.size())
            continue;

       int value = newPendingChain[idx];

typename container::iterator pos =
    std::lower_bound(finalMainChain.begin(),
                     finalMainChain.end(),
                     value);

finalMainChain.insert(pos, value);
}



   
    return finalMainChain;
}   


void PmergeMe::ApplyFordJohnson(std::string input)
{
    std::vector<int> vec;
    std::deque<int> deq;
   try
   {
    FillContainer(vec, input);
    FillContainer(deq, input);
   }
   catch(const std::exception& e)
   {
    std::cerr << e.what() << '\n';
    return;
   }
   
    std::cout << "Before: ";
   std::cout << input << std::endl;
    struct timeval start, end;
    gettimeofday(&start, NULL);
    vec = beginSort(vec);
    gettimeofday(&end, NULL);
    long seconds = end.tv_sec - start.tv_sec;
    long microseconds = end.tv_usec - start.tv_usec;
    long total = (seconds * 1000000) + microseconds;
    std::cout << " Time to process " << vec.size() << " elements: using vector: " << total << " us" << std::endl;
    std::cout << "Sorted vector: ";
    for (size_t i = 0; i < vec.size(); i++)
    {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
    gettimeofday(&start, NULL);
    deq = beginSort(deq);
    gettimeofday(&end, NULL);
    seconds = end.tv_sec - start.tv_sec;
    microseconds = end.tv_usec - start.tv_usec;
    total = (seconds * 1000000) + microseconds;

    std::cout << " Time to process " << deq.size() << " elements: using deque : " << total << " us" << std::endl; 
    std::cout << "Sorted deque: ";
    for (size_t i = 0; i < deq.size(); i++)
    {
        std::cout << deq[i] << " "; 
    }
    std::cout << std::endl;

}


