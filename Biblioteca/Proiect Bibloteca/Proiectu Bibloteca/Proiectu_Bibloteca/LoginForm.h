#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include "Button.h"
#include "InputBox.h"
#include "Client.h"
#include "MainWindow.h"
#include "RegisterForm.h"
#include "UserAccountScene.h"
#include "Error.h"
#include "Client.h"
#include "UserAccount.h"
class LoginForm
{
	sf::RenderWindow window;
public:
	LoginForm(std::unordered_map<int, Book> &avalabileBooks);

};