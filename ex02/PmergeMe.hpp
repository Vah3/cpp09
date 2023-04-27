# pragma once

# include <iostream>
# include <vector>
# include <list>
# include <sstream>
# include <ctime>
#include <sys/time.h>
# include <cstdlib>

# define macro_size 15

typedef std::vector<unsigned int>::iterator vecit;
typedef std::list<unsigned int>::iterator lstit;

class PmergeMe
{
	public:
		PmergeMe();
		~PmergeMe();
		PmergeMe(const PmergeMe &);
		PmergeMe &operator=(const PmergeMe &ob);
		void	sort(char **);
	private:
		std::vector<unsigned int> seq;
		std::list<unsigned int> lst;
		bool	check_input(char **);
		template <typename T>
			void	store_in_cont(char **, T &);
		std::string clear_odd_spaces(std::string );
		void	rec_divide(vecit beg, vecit end);
		void	rec_divide(lstit beg, lstit end);
		void	sortVector(char **arg);
		void	sortList(char **arg);
		void	bouble(vecit beg,vecit  end);
		void	insertion(vecit beg, size_t count);
		void	insertion(lstit beg, size_t count);
		double	ft_get_correct_mls_time(struct timeval &t1, struct timeval &t2);
};
