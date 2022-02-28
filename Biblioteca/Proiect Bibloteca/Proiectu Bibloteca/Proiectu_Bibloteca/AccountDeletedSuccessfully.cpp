#include "AccountDeletedSuccessfully.h"

AccountDeletedSuccessfully::AccountDeletedSuccessfully()
{
    window.create(sf::VideoMode(500, 160), "Account Deleted Successfully");

    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cout << "Nu";
    }
    font.loadFromFile("arial.ttf");

    sf::Text titlu;
    titlu.setFont(font);
    titlu.setCharacterSize(20);
    titlu.setPosition({ 100,10 });
    titlu.setString("Account deleted successfully");


    Button confirm("Confirm", { 200,50 }, sf::Color::White, sf::Color::Black, font, { 150,100 });

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseMoved)
            {

                confirm.mouseHovered(sf::Color::Black, sf::Color::White, window);
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (confirm.isMouseover(window))
                {
                    window.close();
                }

            }
        }
        window.clear();

        confirm.drawTo(window);
        window.draw(titlu);
        window.display();
    }
}
