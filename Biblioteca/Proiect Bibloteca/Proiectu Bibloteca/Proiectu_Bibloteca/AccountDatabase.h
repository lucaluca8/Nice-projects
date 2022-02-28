#pragma once
#include <unordered_map>
#include "UserAccount.h"
#include <string>
#include <fstream>

class AccountDatabase
{
	//use unorderd_map because even tho they take up more space
	// their looku-retrival speed is much much better then a map
	std::unordered_map<std::string, UserAccount> dataBase;
	std::string filename;
	//load and save methods are private because we dont want the user to have access to them
	void loadFromFile(); // loads data from file into database
	void saveToFile(); // saves every entity to file (empties file before that)
	void saveOneToFile(UserAccount account); //write one user account to file
public:
	AccountDatabase(); //constructor with no parameters. used to be able to call createAccount in other classes
	AccountDatabase(std::string filename);
	void addAccount(UserAccount acc);
	void deleteAccount(std::string username);
	bool accountExists(std::string username); // method that checks if an account is already made
	UserAccount createAccount();
	UserAccount getAccount(std::string username);
	std::unordered_map<std::string, UserAccount> seeDataOfAccount();

};

