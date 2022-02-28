#pragma once
#include <unordered_map>
#include <string>
#include <fstream>
#include <vector>
#include "UserAccount.h"
#include <iostream>
#include <map>



class AccountDatabase
{

	std::unordered_map<std::string,UserAccount > dataBase;
	std::string filename,userBooksFile;
	void loadFromFile(); 	
	const void saveOneToFile(UserAccount account)const;
public:
	const void saveToFile()const;
	AccountDatabase(); 
	AccountDatabase(std::string filename,std::string userBooksFile);
	void addAccount(UserAccount& acc);
	void deleteAccount(std::string username);
	const bool accountExists(std::string username)const;
	bool createAccount(std::string username, std::string password);
	int numberOfAccounts();
	UserAccount getAccount(std::string username);
	const std::unordered_map<std::string, UserAccount>& getAccountDatabase()const;
	UserAccount& getAccountById(int id);

};

	
