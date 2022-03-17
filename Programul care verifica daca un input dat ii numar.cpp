#include<iostream>
#include <string.h>
#include <regex>

std::string DeCareNumarEste(std::string numar)
{
	bool eNatural = 0, eIntreg = 0, eReal = 0, eExponential = 0;

	if (std::regex_match(numar,std::regex("[1-9][0-9]*")) == true)
	{
		eNatural = 1;
	}
	else if(std::regex_match(numar, std::regex("-[1-9][0-9]*")) == true)
	{
		eIntreg = 1;
	}
	else if(std::regex_match(numar, std::regex("[-+]?[1-9][0-9]*.[0-9]*")) == true)
	{
		eReal = 1;
	}
	else if(std::regex_match(numar, std::regex("[-+]?[1-9][0-9]*\\.[0-9]*E-[1-9][0-9]*")) == true)
	{
		eExponential = 1;
	}
	if (eExponential == 1)
		return "E exponential";
	else if (eReal == 1)
		return "E real";
	else if (eIntreg == 1)
		return "E intreg";
	else if(eNatural == 1)
		return "E natural";
	return "Nu e numar";
}

int main()
{
	std::cout << DeCareNumarEste("+11112E-10");
}