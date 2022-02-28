#pragma once
#include <string>
#include <iostream>
#include "Book.h"
#include <set>
#include <vector>
#include "iostream"
#include <unordered_map>
#include <map>
#include <fstream>
#include <ctime>
class UserAccount
{
	std::string username;
	std::string password;
	std::unordered_map<int,Book> books;
	int user_id;
public:

	UserAccount();
	UserAccount(std::string username, std::string password);
	const std::string& getUsername()const;
	const std::string& getPassword()const;
	void setUsername(std::string username);
	void setPassword(std::string password);
	void setBooks(std::unordered_map<int, Book> books);
	void addBook(Book b);
	void setUserID(int ID);
	std::unordered_map<int, Book>& getBooks();
	const int& getUserID() const;
	void removeBook(int id);
	const bool checkBurrowBookEligibility(int bookId)const;


};

