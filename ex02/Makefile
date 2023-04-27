
NAME	=	pmerge
ifeq ($(OS), Windows_NT)
	NAME	=	pmerge.exe
endif
CPP			=	c++

CXXFLAGS	=	-Wall -Wextra -Werror -std=c++98

SRCS		=	PmergeMe.cpp

OBJS		=	$(SRCS:.cpp=.o)

ifeq ($(OS),Windows_NT)
	RM		=   del
else
	RM		=	rm -rf
endif
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
