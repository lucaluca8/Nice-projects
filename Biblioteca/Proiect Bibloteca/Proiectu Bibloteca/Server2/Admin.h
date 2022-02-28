#pragma once
#include "Book.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include "AccountDatabase.h"
#include <sstream>
#include <set>
#include <ctime>

class Admin
{
private:
	std::unordered_map<int,Book> allBooks;
	std::unordered_map<int,Book> availableBooks;
	std::string filename,accFile,userBooksFile;
	std::string burrowedTimeFile;
	std::map<int, std::set<int>> userBooks;
	std::map<int,int> burrowedTimeBooks;
	AccountDatabase accounts;
	void loadFromFile(std::string filename); 
	const void saveToFile()const;
	const void saveOneToFile(Book book)const;
	void makeAvalabileBooks();
	void loadUserBooks();
	void loadBurrowedTimeFile();
	void makeBurrowedTimeBooks();

public:
	Admin();
	Admin(std::string filename, std::string accFile, std::string userBooksFile,std::string burrowedTimeFile);
	const void saveUsersBooksToFile()const;
	const void saveBurrowedTimeBooks()const;
	void transformBookIdToBooks(UserAccount &acc);
	std::unordered_map<int, Book>& getAllBooks();
	std::unordered_map<int, Book>& getAvailableBooks();
	void setAllBooks(std::unordered_map<int, Book> allBooks);
	void setAvailableBooks(std::unordered_map<int, Book> avalabileBooks);
	bool searchBook(std::string name);
	AccountDatabase& getAccountDB();
	std::map<int, std::set<int>>& getUserBooks();
	void addBookToAvalabileBooks(Book b);
	std::map<int, int>& getBurrowedTimeBooks();
	void addBookToBurrowedBooksTime(int bId);

};

