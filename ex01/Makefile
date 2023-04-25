
NAME		=	rpn

CPP			=	c++

CXXFLAGS	=	-Wall -Wextra -Werror -std=c++98

SRCS		=	RPN.cpp main.cpp

OBJS		=	$(SRCS:.cpp=.o)

RM			=	rm -rf

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
