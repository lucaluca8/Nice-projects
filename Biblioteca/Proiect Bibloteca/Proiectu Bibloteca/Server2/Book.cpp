#include "Book.h"

Book::Book()
{
	this->title = "";
	this->author = "";
	this->publisher = "";
	this->genre = "";
}

Book::Book(int id, std::string title, std::string author, std::string publisher, std::string genre)
{
	this->id = id;
	this->title = title;
	this->author = author;
	this->publisher = publisher;
	this->genre = genre;
}

void Book::setId(int id)
{
	this->id = id;
}

void Book::setTitle(std::string newTitle)
{
	this->title = newTitle;
}

void Book::setAuthor(std::string newAuthor)
{
	this->author = newAuthor;
}

void Book::setPublisher(std::string newPublisher)
{
	this->publisher = newPublisher;
}

void Book::setGenre(std::string newGenre)
{
	this->genre = newGenre;
}


const int& Book::getId() const
{
	return id;
}

const std::string& Book::getTitle() const
{
	return this->title;
}

const std::string& Book::getAuthor() const
{
	return this->author;
}

const std::string& Book::getPublisher() const
{
	return this->publisher;
}

const std::string& Book::getGenre() const
{
	return this->genre;
}


const void Book::printBook() const
{
	std::cout << "Book id is: " << this->id << std::endl;
	std::cout << "Book title is: " << this->title << std::endl;
	std::cout << "Book author is: " << this->author << std::endl;
	std::cout << "Book publisher is: " << this->publisher << std::endl;
	std::cout << "Book genre is: " << this->genre << std::endl;
}
