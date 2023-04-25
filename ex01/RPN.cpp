# include "RPN.hpp"

RPN::RPN(std::string line)
{
	this->_line = line;
}

bool RPN::check_input()
{
	int operands = 0 , operators = 0;
	for(size_t i = 0; i < _line.size(); i++)
	{
		if (!std::isdigit(_line[i]) && _line[i] != '-' && _line[i] != '+' && _line[i] != '*' && _line[i] != '/' && !std::isspace(_line[i]))
		{
			std::cout << "\033[1;31mError: Invalid character\033[0m" << std::endl;
			return false;
		}
		if (std::isdigit(_line[i]))
			operands++;
		else if (!std::isspace(_line[i]))
			operators++;
	}
	if (operators == 0 || operands == 0)
	{
		std::cout << "\033[1;31mError: empty line\033[0m" << std::endl;
		return false;
	}
	if (operands != operators + 1)
	{
		std::cout << "\033[1;31mError: Operands and operators count not matching\033[0m" << std::endl;
		return false;
	}

	return true;
}

void	RPN::rev_pol_not()
{
	double	oper1, oper2;
	for(size_t i = 0; i < _line.size(); i++)
	{
		if ( std::isdigit(_line[i]))
			store.push(_line[i] - 48);
		else if (!std::isspace(_line[i]))
		{
			if (store.size() < 2)
			{
				std::cout << "\033[1;31mError: incomplite reverse polish notation expression\033[0m" << std::endl;
				return ;
			}
			oper2 = store.top();
			store.pop();
			oper1 = store.top();
			store.pop();
			if ( _line[i] == '+')
				store.push(oper1 + oper2);
			else if ( _line[i] == '-')
				store.push(oper1 - oper2);
			else if ( _line[i] == '*')
				store.push(oper1 * oper2);	
			else if ( _line[i] == '/')
				store.push(oper1 / oper2);
		}
	}
	if ( store.top() == std::numeric_limits<double>::infinity())
		std::cout << "\033[1;31mError: inf number\033[0m" << std::endl;
	else
		std::cout << "worked => " << store.top() << std::endl;
}


void	RPN::run()
{
	if(!check_input())
		return ;
	rev_pol_not();
}
