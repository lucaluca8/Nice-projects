#include "ErrorBorrowingBook.h"

ErrorBorrowingBook::ErrorBorrowingBook()
{
    window.create(sf::VideoMode(500, 160), "Error");

    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cout << "Nu";
    }
    font.loadFromFile("arial.ttf");

    sf::Text titlu;
    titlu.setFont(font);
    titlu.setCharacterSize(15);
    titlu.setPosition({ 100,10 });
    titlu.setString("Conditions to borrow a book not met");


    Button retryButton("RETRY", { 200,50 }, sf::Color::White, sf::Color::Black, font, { 150,100 });

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseMoved)
            {
                retryButton.mouseHovered(sf::Color::Black, sf::Color::White, window);
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (retryButton.isMouseover(window))
                {
                    window.close();
                }

            }
        }
        window.clear();

        retryButton.drawTo(window);
        window.draw(titlu);
        window.display();
    }

}
