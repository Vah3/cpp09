# include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
}

PmergeMe::~PmergeMe()
{
}

PmergeMe &PmergeMe::operator=(const PmergeMe &ob)
{
	if (this == &ob)
		return *this;
	this->seq = ob.seq;
	this->lst = ob.lst;
	return *this;
}

PmergeMe::PmergeMe(const PmergeMe &ob)
{
	*this = ob;
}

bool PmergeMe::check_input(char **arg)
{
	size_t i = 1, j = 0;
	bool flag = false;
 	while (arg[i])
	{
		while(arg[i][j])
		{
			if (!std::isspace(arg[i][j]) && !std::isdigit(arg[i][j]))
				return false;
			if (flag == false && std::isdigit(arg[i][j]))
					flag = true;
			j++;
		}
		if (flag == false)
			return false;
		else
			flag = false;
		j = 0;
		i++;
	}
	return true;
}


template <typename T>
void	PmergeMe::store_in_cont(char **arg, T & container)
{
	size_t i = 1;
	std::string big_line;
 	while (arg[i])
	{
		big_line += " ";
		big_line += std::string(arg[i]);
		i++;
	}
	std::stringstream ss;
	ss << big_line;
	std::string single_num;
	while(std::getline(ss,single_num, ' '))
	{
		if (single_num.size() == 0)
			continue ;
		container.push_back(atoi(single_num.c_str()));
	}
}

void PmergeMe::bouble(vecit beg, vecit end)
{
	int for_sw;
	for (vecit it_ = beg; it_ != end; it_++)
	{
		for (vecit it = beg; it != end; it++)
		{
			if (*it > *(it + 1))
			{
				for_sw = *it;
				*it = *(it + 1);
				*(it + 1) = for_sw;
			}
		}
	}
}
void	PmergeMe::insertion(vecit beg, size_t count)
{
	unsigned int x;
	size_t j;
	for (size_t i = 1; i < count; i++)
	{
		x = *(beg + i);
		j = i;
		while (j > 0 && x < *(beg + j - 1))
			j--;
		seq.erase(beg + i);
		seq.insert(beg + j, x);
	}
}

void	PmergeMe::insertion(lstit beg, size_t count)
{
	unsigned int x;
	lstit next;
	lstit  curr = beg;;
	size_t for_range;
	for (size_t i = 1; i < count; i++)
	{
		for_range = i;
		next = beg;
		curr= beg;
		for (size_t k = 0; k < i; k++)
		{
			if ( k != i - 1)
				curr++;
			next++;
		}
		while ( *next < *curr)
		{
			x = *next;
			*next = *curr;
			*curr = x;
			if (for_range > 1)
			{
				--next;
				--curr;
				for_range--;
			}
			else
				break;
		}
	}
}

void	PmergeMe::rec_divide(vecit beg, vecit end)
{
	int count = end - beg + 1;

	int mid = 0;
	int sec_beg = 0;
	if (count >= macro_size) //macro_size is a macro
	{
		if (count != 1)
		{
			if (count % 2 == 0)
			{
				mid = count / 2 - 1;
				sec_beg = mid;
			}
			else
			{
				mid = count / 2;
				sec_beg = mid - 1;
			}
			rec_divide(beg, beg + mid);
			rec_divide(end - sec_beg, end);
		}
		//	bouble(beg,end);
	}
			insertion(beg, count);
	return ;
}

void	PmergeMe::rec_divide(lstit beg, lstit end)
{
	int count = 0;
	int mid = 0;
	lstit for_rec = beg;
	for (lstit it = beg; it != end; it++)
		count++;
	count++;
	
	if (count >= macro_size) //macro_size is a macro
	{
		if (count != 1)
		{
			if (count % 2 == 0)
				mid = count / 2 - 1;
			else
				mid = count / 2;
			while(mid)
			{
				for_rec++;
				--mid;
			}
			rec_divide(beg, for_rec);
			for_rec++;
			rec_divide(for_rec, end);
		}
	}
		//	bouble(beg,end);
			insertion(beg, count);
	return ;
}

double PmergeMe::ft_get_correct_mls_time(struct timeval &t1, struct timeval &t2)
{
	return ( (t2.tv_sec - t1.tv_sec) * 1000 + (t2.tv_usec - t1.tv_usec) / 1000.0);
}

void	PmergeMe::sortVector(char **arg)
{
	struct timeval start_time;
	struct timeval end_time;

	gettimeofday(&start_time, NULL);
	store_in_cont(arg,seq);
	std::cout << "\033[1;31mVector before sort -> \033[0m";
	for (size_t i = 0; i < seq.size(); i++)
	{
		std::cout << "\033[1;36m" <<  seq[i] << " \033[0m" ;
		if ( i == 7)
		{
			std::cout << "\033[1;33m[...]\033[0m";
			break ;
		}
	}
	std::cout << std::endl;
	rec_divide(seq.begin(),seq.end() - 1);
//	std::sort(seq.begin(),seq.end());
	gettimeofday(&end_time, NULL);
	std::cout << "\033[1;32m Vector after sort -> \033[0m";
	for (size_t i = 0; i < seq.size(); i++)
	{
		std::cout << "\033[1;36m" << seq[i] << " \033[0m" ;
		if ( i == 7)
		{
			std::cout << "\033[1;33m[...]\033[0m";
			break ;
		}
	}
	std::cout << std::endl;
	std::cout << "\033[1;21m Time for sorting, using vector -> " << ft_get_correct_mls_time(start_time, end_time) << "ms" << "\033[0m" << std::endl;
}

void	PmergeMe::sortList(char **arg)
{
	struct timeval start_time;
	struct timeval end_time;
	
	gettimeofday(&start_time, NULL); //stor in list
	std::cout << "\033[1;31mList before sort -> \033[0m";
	size_t i = 0;
	store_in_cont(arg, lst);
	for (std::list<unsigned int >::iterator it = lst.begin(); i < seq.size(); it++)
	{
		std::cout << "\033[1;36m" << *it << " \033[0m" ;
		if ( i == 7)
		{
			std::cout << "\033[1;33m[...]\033[0m";
			break ;
		}
		i++;
	}
	std::cout << std::endl;
	lstit last= lst.end();
	last--;
	rec_divide(lst.begin(),last);
	std::cout << "\033[1;32m List after sort -> \033[0m";
	i = 0;
	store_in_cont(arg, lst);
	for (std::list<unsigned int >::iterator it = lst.begin(); i < seq.size(); it++)
	{
		std::cout << "\033[1;36m" << *it << " \033[0m" ;
		if (i == 7)
		{
			std::cout << "\033[1;33m[...]\033[0m";
			break ;
		}
		i++;
	}
	std::cout << std::endl;
	gettimeofday(&end_time, NULL);
	std::cout << "\033[1;21m Time for sorting, using lst -> " << ft_get_correct_mls_time(start_time, end_time) << "ms" << "\033[0m" <<std::endl;
}
void	PmergeMe::sort(char **arg)
{
	if(!check_input(arg))
	{
		std::cout << "Error: something wrong" << std::endl;
		return ;
	}
	sortVector(arg);
	sortList(arg);
}


int main(int argc, char **argv)
{
	if (argc == 1)
	{
		std::cout << "Error: wrong argument count" << std::endl;
		return 1;
	}
	PmergeMe ob;
	ob.sort(argv);
	return 0;
}
