#pragma once
#include "Admin.h"
#include <string>

class InputOutputServer
{
private:
	std::string commandFilename; //input the commands for the server and writes responses
	std::string orderFilename; // input file from where we write order number
	//Admin admin;
public:
	InputOutputServer(std::string commandFilename,std::string orderFilename);
	void server();
	void wait();
	void announce();

};

