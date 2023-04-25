# include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
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


void	PmergeMe::store_in_vec(char **arg)
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
		seq.push_back(atoi(single_num.c_str()));
		lst.push_back(atoi(single_num.c_str()));
	}
}

/*
void	PmergeMe::rec_divide(vecit beg, vecit end)
{
	int mid = end - beg + 1;
		std::cout << "count -> " << mid << std::endl;
		std::cout << "beg -> " << *beg << std::endl;
		std::cout << "end -> " << *end << std::endl;
	if (mid == 3)
		mid = 1;
	else
	mid = mid / 2 - 1;
		std::cout << "mid -> " << mid << std::endl;
		std::cout << "first end -> " << *(beg + mid) << std::endl;
		std::cout << "beg -> " << *(end - mid) << std::endl;
		std::cout << "end -> " << *end << std::endl;
}*/

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
	(void) count;
	(void) beg;
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
			std::cout << "midle -> " << *(end - sec_beg) << std::endl;
			rec_divide(beg, beg + mid);
			rec_divide(end - sec_beg, end);
		}
		//	bouble(beg,end);
			insertion(beg, count);
	}
	return ;
}

void	PmergeMe::rec_divide(lstit beg, lstit end)
{
	int count = 0;
	int mid = 0;
	int sec_beg = 0;
	lstit for_rec = beg;
	for (lstit it = beg; it != end; it++)
		count++;
	count++;
	for (lstit it = beg; it != end; it++)
	{
	 	std::cout << *it << "_";
	}

	 	std::cout << *end << "_";
	 	std::cout << "count -> " << count << std::endl;
	
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
			while(mid)
			{
				for_rec++;
				--mid;
			}

			std::cout << "midle -> " << *for_rec << std::endl;
			rec_divide(beg, for_rec);
			for_rec++;
			rec_divide(for_rec, end);
		}
		//	bouble(beg,end);
			insertion(beg, count);
	}
	return ;
}

double ft_get_correct_mls_time(struct timeval t1, struct timeval t2)
{
	return ( ((t2.tv_sec - t1.tv_sec) * 1000000 + t2.tv_usec - t1.tv_usec) / 1000000.0);
}

void	PmergeMe::sort(char **arg)
{
	struct timeval start_time;
	struct timeval end_time;
	if(!check_input(arg))
	{
		std::cout << "Error: something wrong" << std::endl;
		return ;
	}
	gettimeofday(&start_time, NULL);
	store_in_vec(arg);

	for (lstit it = lst.begin(); it != lst.end();it++)
	{
		std::cout << *it  << "_";
	}
	std::cout << std::endl;
	rec_divide(seq.begin(),seq.end() - 1);
//	bouble(seq.begin(),seq.end());
	gettimeofday(&end_time, NULL);
	std::cout << "\nTime for sorting, using vector -> " << ft_get_correct_mls_time(start_time, end_time) << std::endl;
	gettimeofday(&start_time, NULL);
	lstit last= lst.end();
	last--;
	rec_divide(lst.begin(),last);
	gettimeofday(&end_time, NULL);
	std::cout << "\nTime for sorting, using lst -> " << ft_get_correct_mls_time(start_time, end_time) << std::endl;
	for (size_t i = 0; i <  seq.size();i++)
	{
		std::cout << seq[i] << " ";
	}
	std::cout << std::endl;
	for (lstit it = lst.begin(); it !=  lst.end();it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}


int main(int argc, char **argv)
{
	if (argc == 1)
		return 1;
	PmergeMe ob;
	ob.sort(argv);
}
