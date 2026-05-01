#include "PmergeMe.hpp"

bool numbers_are_valid(std::string input)
{
    std::istringstream mystring_stream(input);
    std::string token;
    while (mystring_stream >> token)
    {
        for (size_t i = 0; i < token.length(); i++)
        {
            if (!std::isdigit(token[i]))
                return false;
        }
    }
    return true;
}

bool check_no_duplicates(const std::string &input)
{
   std::set<std::string> numbers_wihout_duplicates;
   
    std::istringstream mystring_stream(input);
    std::string number;
    while (mystring_stream >> number)
    {
        if (numbers_wihout_duplicates.find(number) != numbers_wihout_duplicates.end())
            return false;
        numbers_wihout_duplicates.insert(number);
    }
    return true;
}

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
    if (!numbers_are_valid(input))
    {
        std::cerr<<"invalid input: only positive numbers are allowed"<<std::endl;
        return 1 ;
    }
    if (!check_no_duplicates(input))
    {
        std::cerr<<"invalid input: no duplicates are allowed"<<std::endl;
        return 1 ;
    }
    PmergeMe::ApplyFordJohnson(input);
    return 0;

}