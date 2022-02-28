#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include "Button.h"
#include "InputBox.h"
#include "Client.h"
#include "LoginForm.h"
#include "RegisterForm.h"
#include "SearchBookScene.h"
#include "BookContent.h"
#include <vector>
class MainWindow
{
	sf::RenderWindow window;
	

public:
	MainWindow();
	int display(std::unordered_map<int, Book> &avalabileBooks);
};

