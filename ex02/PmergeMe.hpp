# pragma once

# include <iostream>
# include <vector>
# include <list>
# include <sstream>
# include <ctime>
#include <sys/time.h>

# define macro_size 15

typedef std::vector<unsigned int>::iterator vecit;
typedef std::list<unsigned int>::iterator lstit;

class PmergeMe
{
	public:
		PmergeMe();
		void	sort(char **);
	private:
		std::vector<unsigned int> seq;
		std::list<unsigned int> lst;
		bool	check_input(char **);
		void	store_in_vec(char **);
		std::string clear_odd_spaces(std::string );
		void	rec_divide(vecit beg, vecit end);
		void	rec_divide(lstit beg, lstit end);
		void	bouble(vecit beg,vecit  end);
		void	insertion(vecit beg, size_t count);
		void	insertion(lstit beg, size_t count);
};
