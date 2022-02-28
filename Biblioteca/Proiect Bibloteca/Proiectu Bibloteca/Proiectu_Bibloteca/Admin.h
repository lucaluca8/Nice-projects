#pragma once
#include "Book.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

class Admin
{
private:
	std::vector<Book> allBooks;
	std::vector<Book> availableBooks;
	std::string filename;
	void loadFromFile(std::string filename); // loads books from file into allBooks database
	void saveToFile(); //saves every entity to file (empties file before that)
	void saveOneToFile(Book book); //saves one book to database

public:
	Admin();
	Admin(std::string filename);

	std::vector<Book> getAllBooks();
	std::vector<Book> getAvailableBooks();

	void setAllBooks(std::vector<Book>);
	void setAvailableBooks(std::vector<Book>);

	bool searchBook(std::string name);
};

