#include <iostream>
#include "Client.h"
#include "MainWindow.h"
#include <SFML/Graphics.hpp>
int main()
{
	Client c("commands.txt", "order.txt", "Requests.txt", "logIn.txt");
	MainWindow main;
	std::unordered_map<int, Book> avalabileBooks = c.makeAvalabileBooks();
	main.display(avalabileBooks);
	return 0;
}

