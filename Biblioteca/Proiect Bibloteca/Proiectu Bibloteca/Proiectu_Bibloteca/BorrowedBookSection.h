#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include "Button.h"
#include "InputBox.h"
#include "Client.h"
#include "Book.h"
#include "BookContent.h"
using namespace std;
class BorrowedBookSection
{
public:
	BorrowedBookSection(Book& book, float y, sf::Font& font, int idul);
	void drawBookBlock(sf::RenderWindow& window);
	bool buttonClicked(sf::RenderWindow& window, UserAccount &acc, std::unordered_map<int, Book> &avalabileBooks,int id);
	Button burrowButton;
	Button readButton;
	Button returnButton;
	sf::Text title;
	sf::Text author;
	sf::Text genre;
	int id;
private:

};

