# include "BitcoinExchange.hpp"

const char *BitcoinExchange::my_expt::what() const throw()
{
	return "parse error";
}

bool	BitcoinExchange::check_for_spaces(std::string &line)
{
	size_t i = 0;

	while(line[i] && ::isspace(line[i]))
		i++;
	while(line[i] && !(::isspace(line[i])))
		i++;
	while(line[i] && (::isspace(line[i])))
		i++;
	if(line[i] && line[i] == '|')
		i++;
	else
		return false;
	while(line[i] && ::isspace(line[i]))
		i++;
	if(i == line.size())
		return false;
	while(line[i] && !(::isspace(line[i])))
		i++;
	if(i == line.size())
		return true;
	return false;
}

void	BitcoinExchange::clear_spaces(std::string &line)
{
	line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
}

bool	BitcoinExchange::is_in_range(std::string &line)
{
	double num = atof(line.c_str());
	if (!(num > 0 && num < 1000))
		return false;
	return true;
}

bool	BitcoinExchange::is_int(std::string &line)
{
	for(size_t i = 0; i < line.size(); i++)
	{
		if (isdigit(line[i]))
			continue;
		return false;
	}
	return true;
}

bool	BitcoinExchange::is_double(std::string &line)
{
	int flag = 0;
	for(size_t i = 0; i < line.size(); i++)
	{
		if (flag < 2 && isdigit(line[i]))
			continue;
		if (i > 0 && flag == 0 && line[i] == '.' && i < line.size() - 1) 
			flag++;
		else
			return false;
	}
	return true;
}

bool	BitcoinExchange::valid_date(std::string &line)
{
	if (line.compare(0,4,"2007") < 0 || line.compare(0,4,"2023") > 0)
		return false;
	if (line.compare(5,2,"12") > 0 || line.compare(5,2,"01") < 0)
		return false;
	int	mm = atoi(line.c_str() + 5);
	int	yy = atoi(line.c_str());
	std::string dd;
	if (mm == 2 && yy % 4 == 0) // in range 2007-2023, need more checks
		dd = "29";
	else if (mm == 2)
		dd = "28";
	else if ((mm <= 7 && mm % 2 == 1) || (mm > 7 && mm % 2 == 0))
		dd = "31";
	else
		dd = "30";
	 if (line.compare(8,2, dd) > 0 || line.compare(8,2,"01") < 0)
			return false;
	return true;
}


bool BitcoinExchange::check_string(std::string &line)
{
	size_t i = 0;
	size_t dig = 4;
	size_t len = line.size();
	if (len != 10)
		return false;
	for(int z = 0; z < 3; z++)
	{
		for ( ; i < len && i < dig; i++)
			{
			if(std::isdigit(line[i]))
				continue ;
			return true;
		}
		if(line[i] == '-')
			i++;
		else if (i < len)
			return false;
		dig  = i + 2;
	}
	if (!valid_date(line))
		return false;
	return true;
}


void	BitcoinExchange::store()
{
	std::string line, data;
	std::stringstream ss;
	std::string for_map;
	double val;

	std::getline(_file,line);
	if(line.empty())
		throw my_expt();
	clear_spaces(line);
	if(!line.compare("date,exchange_rate\n"))
		throw my_expt();
	while(std::getline(_file,line))
	{
		clear_spaces(line);
		if (line.find(',') == line.npos)
			continue ;
		ss << line;
		std::getline(ss,data,',');
		if ( check_string(data))
		{
			for_map.clear();
			for_map = data;
			data.clear();
			data = line;
			data.erase(0, data.find(',') + 1);
			if(is_double(data))
			{
				val = atof(data.c_str());
				_data.insert(std::pair<std::string, double>(for_map, val));
			}
			else
				std::cout << "\033[1;31m fail DOUBLE " << line << "\033[0m" <<  std::endl;
		}
		else
			std::cout << "\033[1;31m fail DATE " << line << "\033[0m" <<std::endl;
		ss.str(std::string()); //for stream clear
		data.clear();
	}
}


void	BitcoinExchange::check_file(std::string name, std::fstream &file)
{
	file.open(name, std::fstream::in);
	if (!(file.is_open()))
		throw my_expt();
}

void	BitcoinExchange::parse_files(std::string name)
{
	check_file(std::string("data.csv"), _file);
	store();
	parse_input_file(name);
}

void	BitcoinExchange::parse_input_file(std::string name)
{
	std::string line , data, find;
	std::stringstream ss;
	check_file(name, _inputf);
	std::getline(_inputf,line);
	if(line.empty())
		throw my_expt();
	clear_spaces(line);
	std::cout << line << std::endl;
	if(!line.compare("date|value\n"))
		throw my_expt();
	while(std::getline(_inputf,line))
	{
		if (line.empty())
		{
			std::cout << "\033[1;31m Error: empty line \033[0m" << std::endl;
			continue ;
		}
		if (!check_for_spaces(line))
		{
			std::cout << "\033[1;31m Error: bad format "  << line <<  "\033[0m" << std::endl;
			continue ;
		}
		clear_spaces(line);	
		ss << line;
		std::getline(ss,data,'|');
		if (check_string(data))
		{
			find = data;
			data.clear();
			data = line;
			data.erase(0, data.find('|') + 1);
			if((is_double(data) || !is_int(data)) && is_in_range(data))
			{
				std::map<std::string, double>::iterator it = _data.lower_bound(find);
				if (it != _data.begin() && it->first != find)
					it--;
				std::cout << " " << it->first << " => " << data << " = " << it->second * atof(data.c_str()) << std::endl;
			}
			else
				std::cout << "\033[1;31m Error value " << line << "\033[0m" <<  std::endl;
		}
		else
			std::cout << "\033[1;31m Error bad date -> " << line << "\033[0m" <<std::endl;
		ss.str(std::string(""));
	}
}
