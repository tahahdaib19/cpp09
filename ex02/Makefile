CXX = c++
CXXFLAGS = -std=c++98 -Wall -Wextra -Werror -g
SRCS = main.cpp PmergeMe.cpp
OBJS = $(SRCS:.cpp=.o)
NAME = PmergeMe
all: $(NAME)
$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)
clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)
re: fclean all
.PHONY: all clean fclean re