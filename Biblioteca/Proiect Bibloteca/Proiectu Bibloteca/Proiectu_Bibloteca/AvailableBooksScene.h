#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include "Button.h"
#include "inputBox.h"
#include "Client.h"
#include "Book.h"
#include <map>
#include "MainWindow.h"
#include "InputBox.h"
#include "UserAccountScene.h"
#include "Book.h"
#include "BookSection.h"
#include "UserAccount.h"
class AvailableBooksScene
{
	sf::RenderWindow window;
public:
	AvailableBooksScene(std::unordered_map<int, Book>&avalabileBooks,UserAccount &acc);
};
