#include "AccountDatabase.h"

void AccountDatabase::loadFromFile()
{
	std::ifstream fin(filename);
	while(fin.good())
	{
		std::string username;
		std::string password;
		fin >> username >> password;
		UserAccount account(username, password);
		dataBase.insert(std::make_pair(username, account));
	}
}

void AccountDatabase::saveToFile()
{
	std::ofstream fout(filename);
	for (auto& pair : dataBase)
	{
		std::string toWrite="";
		UserAccount account = pair.second;
		toWrite += account.getUsername() + "\n" + account.getPassword()+"\n";
		fout << toWrite;
	}

}

void AccountDatabase::saveOneToFile(UserAccount account)
{
		std::ofstream fout;	
		fout.open(filename, std::ios_base::app);
		std::string toWrite = "";	
		toWrite += account.getUsername() + "\n" + account.getPassword() + "\n";
		fout << toWrite;
	
}

AccountDatabase::AccountDatabase()
{

}

AccountDatabase::AccountDatabase(std::string filename)
{
	this->filename = filename;
	loadFromFile();

}

void AccountDatabase::addAccount(UserAccount acc)
{
	//function that adds a UserAccount to the account database
	//it uses the account username as a key because the username
	//must be unique and each key in a map is unique
	dataBase.insert(std::make_pair(acc.getUsername(), acc));
	saveOneToFile(acc);
}

void AccountDatabase::deleteAccount(std::string username)
{
	dataBase.erase(username);
	std::cout << "The account has been deleted sucesfully";
	saveToFile();
}

bool AccountDatabase::accountExists(std::string username)
{
	if(dataBase.find(username) == dataBase.end()) // if the username is not inside the database return false
		return false;
	return true;
}

UserAccount AccountDatabase::createAccount()
{
	std::string username, password;
	std::cout << "Introduce username: ";
	std::cin >> username;
	if (accountExists(username) == false)
	{
		std::cout << std::endl << "Intorduce password: ";
		std::cin >> password;
		UserAccount newAccount(username, password);
		return newAccount;
	}
	else {
		std::cout << "Account already exist."<<std::endl;
		UserAccount nullAccount;
		return nullAccount;
	}

	
}

UserAccount AccountDatabase::getAccount(std::string username)
{
	return dataBase[username];
}

std::unordered_map<std::string, UserAccount> AccountDatabase::seeDataOfAccount()
{
	//TO BE REMADE
	return dataBase;
	
}
