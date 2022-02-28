#include "RegisterError.h"

RegisterError::RegisterError()
{
	window.create(sf::VideoMode(500, 160), "eroare");

	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		std::cout << "Nu";
	}
	font.loadFromFile("arial.ttf");

	sf::Text titlu;
	titlu.setFont(font);
	titlu.setCharacterSize(30);
	titlu.setPosition({ 100,10 });
	titlu.setString("Account already exists");


	Button retry("Try again", { 200,50 }, sf::Color::White, sf::Color::Black, font, { 150,100 });

	while (window.isOpen())
	{
		// loop where we keep the window open until close event is called
		sf::Event event;
		while (window.pollEvent(event))
		{
			// event that closes the window
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseMoved)
			{
				//retryhover
				retry.mouseHovered(sf::Color::Black, sf::Color::White, window);
			}

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (retry.isMouseover(window))
				{
					window.close();
				}

			}
		}
		window.clear();

		retry.drawTo(window);
		window.draw(titlu);
		window.display();
	}

}