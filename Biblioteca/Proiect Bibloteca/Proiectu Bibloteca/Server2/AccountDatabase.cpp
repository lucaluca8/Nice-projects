#include "AccountDatabase.h"


void AccountDatabase::loadFromFile()
{
	std::ifstream fin(filename);
	std::ifstream uin(userBooksFile);
	std::map<int, std::vector<int>> userBooks;

	while (uin.good())
	{
		int uID,nrBooks;
		std::vector<int> booksID;
		uin >> uID >> nrBooks;
		if (uID >= 0)
		{
			for (int i = 0; i < nrBooks; i++)
			{
				int book;
				uin >> book;
				booksID.push_back(book);
			}
			userBooks.insert(std::make_pair(uID, booksID));
		}
	}
	uin.close();

	while (fin.good())
	{
		int id;
		std::string username;
		std::string password;
		fin >> id >> username >> password;
		UserAccount account;
		account.setUsername(username);
		account.setPassword(password);
		account.setUserID(id);
		for (auto& it : userBooks[id])
		{
			account.addBookByID(it);
		}
		dataBase.insert(std::make_pair(username, account));
	}
	fin.close();
}

const void AccountDatabase::saveToFile()const
{
	std::ofstream fout(filename);
	for (auto& pair : dataBase)
	{
		std::string toWrite = "";
		UserAccount account = pair.second;
		if (account.getUsername() != "")
		{
			fout << account.getUserID() << std::endl;
			toWrite += account.getUsername() + "\n" + account.getPassword() + "\n";
			fout << toWrite;
		}
	}
}

const void AccountDatabase::saveOneToFile(UserAccount account)const
{
	std::ofstream fout;
	fout.open(filename, std::ios_base::app);
	fout << account.getUserID()<<std::endl;
	std::string toWrite = "";
	toWrite +=account.getUsername() + "\n" + account.getPassword() + "\n";
	fout << toWrite;
	fout.close();
}

AccountDatabase::AccountDatabase()
{

}

AccountDatabase::AccountDatabase(std::string filename, std::string userBooksFile)
{
	this->filename = filename;
	this->userBooksFile = userBooksFile;
	loadFromFile();
}

void AccountDatabase::addAccount(UserAccount& acc)
{
	if (acc.getUserID() >= 0)
	{
		acc.setUserID(dataBase.size());
		dataBase.insert(std::make_pair(acc.getUsername(), acc));	
		saveOneToFile(acc);
	}
}

void AccountDatabase::deleteAccount(std::string username)
{
	dataBase.erase(username);
	std::cout << "The account has been deleted sucesfully";
	saveToFile();
}

const bool AccountDatabase::accountExists(std::string username)const
{
	if (dataBase.find(username) == dataBase.end()) // if the username is not inside the database return false
		return false;
	return true;
}

bool AccountDatabase::createAccount(std::string username,std::string password)
{
	if (accountExists(username) == false)
	{
		UserAccount acc;
		acc.setUsername(username);
		acc.setPassword(password);
		addAccount(acc);
		std::cout << "Account created succesfuly"<<std::endl;
		return true;
	}
	else {
		std::cout << "Account already exists"<<std::endl;
		return false;
	}
}

int AccountDatabase::numberOfAccounts()
{
	return dataBase.size();
}

UserAccount AccountDatabase::getAccount(std::string username)
{
	return dataBase[username];
}

const std::unordered_map<std::string, UserAccount>& AccountDatabase::getAccountDatabase()const
{
	return dataBase;
}

 UserAccount& AccountDatabase::getAccountById(int id)
{
	for (auto& acc : dataBase)
	{
		if (acc.second.getUserID() == id)
		{
			return acc.second;
		}
	}
}
