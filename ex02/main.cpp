#include "PmergeMe.hpp"



int main (int ac ,char **av)
{
    // if (ac != 2)
    // {
    //     std::cerr<<"invalid input"<<std::endl;
    //     return 1 ;
    // }
    std::string input;
    for (int i = 1; i < ac; i++)
    {
        input += av[i];
        input += " ";
    }
    PmergeMe::ApplyFordJohnson(input);
    return 0;

}