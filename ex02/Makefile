
NAME		=	pmerge

CPP			=	c++

CXXFLAGS	=	-g -ggdb3 -Wall -Wextra -Werror -std=c++98 #-fsanitize=address

SRCS		=	PmergeMe.cpp

OBJS		=	$(SRCS:.cpp=.o)

RM			=	rm -rf

%.o:%.cpp PmergeMe.hpp
	$(CPP) $(CXXFLAGS) -c $< -o $@

all:	$(NAME)

$(NAME):	$(OBJS)
			$(CPP) $(CXXFLAGS) $(SRCS) -o $(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:	all clean fclean re
