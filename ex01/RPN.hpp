# pragma once

# include <iostream>
# include <stack>
# include <stdlib.h>

class RPN
{
	public:
		RPN(std::string);
		void	run();
	private:
		std::stack<double> store;
		std::string _line;
		bool	check_input();
		void	rev_pol_not();

};
