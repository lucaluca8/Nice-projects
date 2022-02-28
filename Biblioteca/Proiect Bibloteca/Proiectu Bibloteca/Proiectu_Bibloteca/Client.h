#pragma once
#include "Admin.h"
#include <string>
#include "UserAccount.h"


class Client
{
private:
	std::string commandFilename; 
	std::string orderFilename; 
	std::string requestFile; 
	std::string logInFile;
public:
	Client(std::string commandFilename, std::string orderFilename,std::string requestFile, std::string logInFile);
	const void wait();
	const void announce();
	const UserAccount logIn(bool& login,std::string username,std::string password);
	const bool newAccount(std::string username,std::string password);
	const std::vector<Book> searchBook(std::unordered_map<int, Book> avalabileBooks, std::string bookTitle);
	const std::unordered_map<int, Book> makeAvalabileBooks();
	const void seeAvalabileBooks(std::unordered_map<int, Book>avalabileBooks);
	const bool burrowBook(UserAccount &acc, std::unordered_map<int, Book> avalabileBooks,int id);
	const void returnBook(UserAccount acc,int id);
	const void sendRequestType(int request);
	const void seeBurrowedBooks(UserAccount account);
	int levenstheinDistance(std::string s1, std::string s2);
	const std::vector<Book> seeSearchResults(std::unordered_map<int, Book> avalabileBooks, std::string bookTitle);
	const void deleteAccount(std::string username,int id);
};

