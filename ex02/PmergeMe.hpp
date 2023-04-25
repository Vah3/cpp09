# pragma once

# include <iostream>
# include <vector>
# include <sstream>
# include <ctime>

# define macro_size 15

typedef std::vector<unsigned int>::iterator vecit;

class PmergeMe
{
	public:
		PmergeMe();
		void	sort(char **);
	private:
		std::vector<unsigned int> seq;
		bool	check_input(char **);
		void	store_in_vec(char **);
		std::string clear_odd_spaces(std::string );
		void	rec_divide(vecit beg, vecit end);
		void	bouble(vecit beg, vecit end);
		void	insertion(vecit beg, size_t count);
};
