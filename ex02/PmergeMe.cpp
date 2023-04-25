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
			for (vecit it = beg; it != end + 1; it++)
			{
				std::cout << *it << " ";
			}
					std::cout << "\n-------------" << count << "-----------------" << std::endl;
					std::cout << std::endl;
			rec_divide(beg, beg + mid);
			rec_divide(end - sec_beg, end);
		}
		//	bouble(beg,end);
			insertion(beg, count);
		for (vecit it = beg; it != end + 1; it++)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << std::endl;
	}
	return ;
}


# include <unistd.h>

void	PmergeMe::sort(char **arg)
{
	time_t start_time;
	time_t end_time;

	if(!check_input(arg))
	{
		std::cout << "Error: something wrong" << std::endl;
		return ;
	}
	time(&start_time);
	store_in_vec(arg);
	for (size_t i = 0; i < seq.size(); i++)
		std::cout << seq[i] << " ";
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	rec_divide(seq.begin(),seq.end() - 1);
//	bouble(seq.begin(),seq.end());
	for (size_t i = 0; i < seq.size(); i++)
	std::cout << seq[i] << " ";

	sleep(1);
	time(&end_time);
	std::cout << "\nTime for sorting, using vector -> " << start_time << " - " << end_time << std::endl;
}


int main(int argc, char **argv)
{
	if (argc == 1)
		return 1;
	PmergeMe ob;
	ob.sort(argv);

}
