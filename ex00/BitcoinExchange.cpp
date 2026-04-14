
#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void)
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
    *this = other;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
    (void)other;
    return (*this);
}

BitcoinExchange::~BitcoinExchange(void)
{
}

bool is_valid_line_format(const std::string &line)
{
     std::stringstream line_stream;
     line_stream.str("");
     line_stream << line;
     std::string token;
     int token_count = 0;
     while (line_stream >> token)
        token_count++;
     if (token_count != 3)
        return false;
     
    unsigned int pipe_pos = line_stream.str().find('|');
    
    if (pipe_pos == std::string::npos || pipe_pos == 0 || pipe_pos == line.length() - 1)
        return false;
    return true;
    
}


std::string trim(const std::string& s)
{
    size_t start = 0;
    size_t end = s.length();

    while (start < end && (s[start] == ' ' || s[start] == '\t'))
        start++;

    while (end > start && (s[end - 1] == ' ' || s[end - 1] == '\t'))
        end--;

    return s.substr(start, end - start);
}

void status_message(input_status status)
{
    switch (status)
    {
        case INVALID_LINE_FORMAT:
            std::cout<<"invalid line format"<<std::endl;
            break;
        case INVALID_DATE_FORMAT:
            std::cout<<"invalid date format"<<std::endl;
            break;
        case INVALID_VALUE_FORMAT:
            std::cout<<"invalid value"<<std::endl;
            break;
        case VALID_LINE:
            std::cout<<"valid line"<<std::endl;
            break;
    }
}

bool isLeapYear(int year)
{
    if (year % 400 == 0)
        return true;
    if (year % 100 == 0)
        return false;
    if (year % 4 == 0)
        return true;
    return false;
}

input_status is_valid_date(const std::string &date_str)
{
    std::string trimmed_date = trim(date_str);
    if (trimmed_date[4] != '-' || trimmed_date[7] != '-' || trimmed_date.length() != 10)
    {
        std::cout<<"date_length: "<<trimmed_date.length()<<std::endl;
        return INVALID_DATE_FORMAT;
    }

    for (size_t i = 0; i < trimmed_date.length(); i++)
    {
        if (i == 4 || i == 7)
            continue;
        if (!std::isdigit(trimmed_date[i]))
        {
            return INVALID_DATE_FORMAT;
        }
    }
    
    std::string year_str = trimmed_date.substr(0, 4);
    std::string month_str = trimmed_date.substr(5, 2);
    std::string day_str = trimmed_date.substr(8, 2);
    int year, month, day;

       
    year = static_cast<int>(std::strtod(year_str.c_str(), NULL));
    month = static_cast<int>(std::strtod(month_str.c_str(), NULL));
    day = static_cast<int>(std::strtod(day_str.c_str(), NULL));   

    if (month < 1 || month > 12 || day < 1 || day > 31 || year < 0)
        return INVALID_DATE_FORMAT;

    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (isLeapYear(year))
        days_in_month[1] = 29;

    if (day > days_in_month[month - 1])
        return INVALID_DATE_FORMAT;

    return VALID_LINE;
    
}

input_status line_validation(std::string line)
{
        if (!is_valid_line_format(line))
            return INVALID_LINE_FORMAT;
       
        // Validate value format (float)

        size_t pipe_pos = line.find('|');
        std::string value_str = line.substr(pipe_pos + 1);
         float value = static_cast<float>(std::strtod(value_str.c_str(), NULL));
        if (value < 0 || value > 1000)
            return INVALID_VALUE_FORMAT;
        
        // Validate date format (YYYY-MM-DD)
        std::string date_str = line.substr(0, pipe_pos);
        return is_valid_date(date_str);
       




}
void is_valid_input(std::string input)
{
     std::ifstream inputFile(input.c_str());
     int line_counter;
     //std::map<std::string, float> exchange_rates;
     if (!inputFile)
     {
        std::cout<<"cant open the file"<<std::endl;
        return ;
     }

     line_counter = 0;
     std::string line;
     std::stringstream header_stream;
     std::stringstream line_stream;
     line_stream.str("");
     header_stream << "date | value";
     std::string header = header_stream.str();
     while (std::getline(inputFile, line))
     {
        if (line_counter == 0 && line != header)
        {

            std::cout<<"invalid header"<<std::endl;
            return ;
        }
        if (line_counter == 0)
        {
             line_counter++;
                continue;
        }
        
        if (line_validation(line) != VALID_LINE)
        {
            status_message(line_validation(line));
            continue;
        }
        

        std::cout<<line<<std::endl;
     


}
inputFile.close();
}
void BitcoinExchange::calculate_exchange(std::string input)
{
    is_valid_input(input);

     
}