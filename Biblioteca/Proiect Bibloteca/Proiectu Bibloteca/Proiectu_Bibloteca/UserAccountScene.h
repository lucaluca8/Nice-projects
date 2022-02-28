#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include "Button.h"
#include "InputBox.h"
#include "Client.h"
#include "UserAccount.h"
#include "MainWindow.h"
#include "SearchBookScene.h"
#include "AvailableBooksScene.h"
#include "UserAccountScene.h"
#include "BorrowedBooks.h"
#include "AccountDeletedSuccessfully.h"
class UserAccountScene
{
	sf::RenderWindow window;
public:
	UserAccountScene(UserAccount &acc, std::unordered_map<int, Book> &avalabileBooks);
};
