#pragma once
#include <iostream>
#include <string>

class Book
{
private:
    int id;
    std::string title;
    std::string author;
    std::string publisher;
    std::string genre;
public:
    Book();
    Book(int id,std::string title,std::string author, std::string publisher,std::string genre);
    void setId(int id);
    void setTitle(std::string newTitle);
    void setAuthor(std::string newAuthor);
    void setPublisher(std::string newPublisher);
    void setGenre(std::string newGenre);
    const int& getId()const;
    const std::string& getTitle()const;
    const std::string& getAuthor()const;
    const std::string& getPublisher()const;
    const std::string& getGenre()const;
    const void printBook()const;

	
};

