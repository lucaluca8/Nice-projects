#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include "Button.h"
#include "InputBox.h"
#include "Client.h"
#include "UserAccount.h"
#include "MainWindow.h"
#include "InputBox.h"
#include "UserAccountScene.h"
#include "BookSection.h"
class SearchBookScene
{
	sf::RenderWindow window;
public:
	SearchBookScene(UserAccount acc, std::unordered_map<int, Book> avalabileBooks);
};
