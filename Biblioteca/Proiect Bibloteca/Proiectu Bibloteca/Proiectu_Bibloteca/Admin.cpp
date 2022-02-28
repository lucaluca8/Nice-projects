#include "Admin.h"


void Admin::loadFromFile(std::string filename)
{
	std::ifstream fin(filename);
	while (fin.good())
	{
		std::string title, author, publisher, genere;
		fin >> title>>author>>publisher>>genere;
		Book b(title, author, publisher, genere,"", 2, 0);
		allBooks.push_back(b);
		availableBooks.push_back(b);
		
	}
}

void Admin::saveToFile()
{
	std::ofstream fout(filename);
	for (auto& book : allBooks)
	{
		std::string toWrite = "";
		Book bok = book;
		toWrite += bok.getTitle() + "\n" + bok.getAuthor() + "\n" + bok.getPublisher()+"\n"+bok.getGenre()+"\n";
		fout << toWrite;
	}
}

void Admin::saveOneToFile(Book book)
{
	std::ofstream fout;
	fout.open(filename, std::ios_base::app);
	std::string toWrite = "";
	toWrite += book.getTitle() + "\n" + book.getAuthor() + "\n" + book.getPublisher() + "\n" + book.getGenre() + "\n";
	fout << toWrite;
}

Admin::Admin()
{
}

Admin::Admin(std::string filename)
{
	this->filename = filename;
	loadFromFile(filename);
}

std::vector<Book> Admin::getAllBooks()
{
	return allBooks;
}

std::vector<Book> Admin::getAvailableBooks()
{
	return availableBooks;
}

void Admin::setAllBooks(std::vector<Book> newAllBooks)
{
	this->allBooks = newAllBooks;
}

void Admin::setAvailableBooks(std::vector<Book> newAvailableBooks)
{
	this->availableBooks = newAvailableBooks;
}

bool Admin::searchBook(std::string name)
{
	for (auto& x : allBooks) {
		if (x.getTitle() == name)
			return true;
	}
	return false;
}
