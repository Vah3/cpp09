# include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	BitcoinExchange ob;
	if (argc != 2 || (argv[1] && !argv[1][0]))
	{
		std::cerr << "Wrong argiment count" << std::endl;
		return (1);
	}
	try
	{
		ob.parse_files(std::string(argv[1]));
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return (0);
}
