#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include "Button.h"
#include "InputBox.h"
#include "Client.h"
#include "borrowedBookSection.h"
#include "UserAccountScene.h"
#include "BookContent.h"
#include "BorrowedSuccesfully.h"
class BorrowedBooks
{
	sf::RenderWindow window;
public:
	BorrowedBooks(UserAccount &acc, std::unordered_map<int, Book>& avalabileBooks);
};
