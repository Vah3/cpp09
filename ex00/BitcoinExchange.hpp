# pragma once

# include <iostream>
# include <map>
# include <fstream>
# include <sstream>

class BitcoinExchange
{
	public:
		BitcoinExchange();
		~BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &);
		BitcoinExchange &operator=(const BitcoinExchange &);
		void	parse_files(std::string );
	private:
		std::map<std::string, double> _data;
		void	check_file(std::string);
		void	clear_spaces(std::string &);
		void	store();
		struct my_expt: public std::exception
		{
			const char* what() const throw();
		};
		bool			check_string(std::string &);
		bool			valid_date(std::string &);
		bool			is_double(std::string &);
		bool			is_int(std::string &);
		bool			is_in_range(std::string &);
		void			parse_input_file(std::string );
		bool			check_for_spaces(std::string &);
};
