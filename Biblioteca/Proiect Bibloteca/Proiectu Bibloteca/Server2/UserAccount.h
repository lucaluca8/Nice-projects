#pragma once
#include <string>
#include <iostream>
#include "Book.h"
#include <vector>
#include <unordered_map>
#include <set>
class UserAccount
{
	std::string username;
	std::string password;
	std::unordered_map<int, Book> books;
	std::vector<int> booksID;
	int user_id;
public:
	UserAccount();
	UserAccount(std::string username, std::string password);

	const std::string getUsername()const;
	const std::string getPassword()const;
	void setUsername(std::string username);
	void setPassword(std::string password);
	void setBooks(std::unordered_map<int, Book> books);
	void addBook(Book b);
	void addBookByID(int id);
	void setUserID(int ID);
	std::unordered_map<int, Book>&getBooks();
	int getUserID();
	std::vector<int>getBooksIDs();
	

};

