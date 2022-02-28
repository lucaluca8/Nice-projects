#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include "Button.h"
#include "InputBox.h"
#include "Client.h"
#include "MainWindow.h"
#include "LoginForm.h"
#include <fstream>
#include "RegisterError.h"
class RegisterForm
{
	sf::RenderWindow window;
public:
	RegisterForm(std::unordered_map<int, Book> avalabileBooks);
};
