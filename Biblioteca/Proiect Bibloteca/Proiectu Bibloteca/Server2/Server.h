#pragma once
#include <string>
#include "Admin.h"
#include<fstream>
#include <iostream>
#include <string.h>
#include "UserAccount.h"
#include <ctime>
#include <chrono>
#include <stdlib.h>

class Server
{
private:
	std::string commandFilename; 
	std::string orderFilename; 
	std::string requestFile;
	std::string booksFile,accFile; 	
	std::string burrowedTimeFile; 
	std::string logInFile; 
	Admin admin;
public:
	Server(std::string commandFilename, std::string orderFilename, std::string booksFile, std::string accFile, std::string userBooksFile,std::string requestFile,std::string burrowedTimeFile,std::string logInFile);
	const void serve();
	const void wait();
	const void announce();
	const void addAccount();
	const void login();
	const int getRequestType();
	const void sendAvalabileBooks();
	const void removeBook();
	const void burrowBook();
	const void deleteAccount();
};

