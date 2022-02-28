#include "Button.h"

Button::Button(sf::String t, sf::Vector2f size, sf::Color bgColor, sf::Color textColor,sf::Font &font, sf::Vector2f position)
{
	text.setString(t);
	text.setFillColor(textColor);
	mainColor = bgColor;
	button.setSize(size);
	button.setFillColor(bgColor);
	TextColor = textColor;
	setFont(font);
	setPosition(position);
}

void Button::setBackColor(sf::Color color)
{
	button.setFillColor(color);
}

void Button::setTextColor(sf::Color color)
{
	text.setFillColor(color);
}

void Button::setPosition(sf::Vector2f position)
{
	button.setPosition(position);
	float xPos = (position.x + button.getGlobalBounds().width / 2) -( text.getGlobalBounds().width/2);
	float yPos= (position.y + button.getGlobalBounds().height / 2) - (text.getGlobalBounds().height / 2);
	text.setPosition({ xPos,yPos });
}

void Button::drawTo(sf::RenderWindow& window)
{
	window.draw(button);
	window.draw(text);
}

bool Button::isMouseover(sf::RenderWindow& window)
{

	sf::Vector2i pixelPos = sf::Mouse::getPosition(window);


	sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
	int mouseX = worldPos.x;
	int mouseY = worldPos.y;
	float btnPosX = button.getPosition().x;
	float btnPosY = button.getPosition().y;

	float btnxPosWidth = button.getPosition().x + button.getLocalBounds().width;
	float btnyPosHeight = button.getPosition().y + button.getLocalBounds().height;

	if (mouseX<btnxPosWidth && mouseX>btnPosX && mouseY<btnyPosHeight && mouseY>btnPosY)
	{
		return true;
	}
	return false;
}

void Button::setFont(sf::Font& font)
{
	text.setFont(font);
}

void Button::setString(sf::String t)
{
	text.setString(t);
}

void Button::mouseHovered(sf::Color hoverColor,sf::Color TextHoverColor, sf::RenderWindow& window)
{
	if (isMouseover(window)) {
		setBackColor(hoverColor);
		text.setFillColor(TextHoverColor);
	}
	else
	{
		setBackColor(sf::Color::White);
		text.setFillColor(sf::Color::Black);
	}
}

void Button::setCharacterSize(int size)
{
	text.setCharacterSize(size);
}

void Button::setSize(sf::Vector2f size)
{
	button.setSize(size);
}
