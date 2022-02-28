#pragma once
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
class Button{
public:
	Button()=default;
	Button(sf::String t,sf::Vector2f size, sf::Color bgColor, sf::Color textColor,sf::Font &font, sf::Vector2f position);

	void setBackColor(sf::Color color);
	void setTextColor(sf::Color color);
	void setPosition(sf::Vector2f position);
	void drawTo(sf::RenderWindow& window);
	bool isMouseover(sf::RenderWindow& window);
	void setFont(sf::Font& font);
	void setString(sf::String t);
	void mouseHovered(sf::Color hoverColor, sf::Color TextHoverColor, sf::RenderWindow& window);
	void setCharacterSize(int size);
	void setSize(sf::Vector2f size);
private:
	sf::RectangleShape button;
	sf::Text text;
	sf::Color mainColor;
	sf::Color hoverColor;
	sf::Color TextColor;
	 

};

