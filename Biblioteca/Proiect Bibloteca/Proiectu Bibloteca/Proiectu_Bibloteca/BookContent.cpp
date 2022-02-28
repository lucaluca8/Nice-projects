#include "BookContent.h"


BookContent::BookContent(UserAccount acc, std::unordered_map<int, Book> avalabileBooks,std:: string &path)
{
    window.create(sf::VideoMode(900, 900), "Content");

    sf::Font font;
    sf::Texture t;
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cout << "Nu";
    }
    font.loadFromFile("arial.ttf");
    if (!t.loadFromFile(path))
    {
        std::cout << "Nu";
    }
    t.loadFromFile(path);
  
    sf::Sprite s;
    s.setTexture(t);

    Button back("Back", { 110,50 }, sf::Color::White, sf::Color::Black, font, { 10,10 });

    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (event.type == sf::Event::MouseMoved)
        {
            back.mouseHovered(sf::Color::Black, sf::Color::White, window);
           
        }
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (back.isMouseover(window))
            {
                window.close();
            }
        }
        window.clear();
        window.draw(s);
        back.drawTo(window);
        window.display();
    }

}

