#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include "Button.h"
#include "InputBox.h"
#include "Client.h"
#include "BorrowedBooks.h"
class BookContent
{
	sf::RenderWindow window;
public:
	BookContent(UserAccount acc, std::unordered_map<int, Book> avalabileBooks,std::string &path);
};
