
NAME		=	rpn

ifeq ($(OS),Windows_NT)
NAME		=	rpn.exe
endif

CPP			=	c++

CXXFLAGS	=	-Wall -Wextra -Werror -std=c++98

SRCS		=	RPN.cpp main.cpp

OBJS		=	$(SRCS:.cpp=.o)
ifeq ($(OS),Windows_NT)
RM			=	del
else
RM			=	rm -rf
endif

%.o:%.cpp RPN.hpp
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
