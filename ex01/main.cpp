# include "RPN.hpp"

int main(int argc, char ** argv)
{
	if (argc != 2 || (argv[1] && !argv[1][0]))
	{
		std::cout << "\033[1;31mWrong argument count\033[0m" << std::endl;
		return 1;
	}
	RPN ob(argv[1]);
	ob.run();
	return 0;
}
