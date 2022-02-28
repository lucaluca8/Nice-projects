#include "BorrowedBooks.h"

BorrowedBooks::BorrowedBooks(UserAccount &acc, std::unordered_map<int, Book>& avalabileBooks)
{
    window.create(sf::VideoMode(900, 900), "Borrowed books");

    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cout << "Nu";
    }
    font.loadFromFile("arial.ttf");

    sf::Text titlu;
    titlu.setFont(font);
    titlu.setCharacterSize(30);
    titlu.setPosition({ 250,10 });
    titlu.setString("This are your borrowed books");

    sf::Texture t;
    if (!t.loadFromFile("images/background.png"))
     {
        std::cout << "Nu";
     }
     t.loadFromFile("images/background.png");
    
        sf::Sprite s;
    s.setTexture(t);

    Button back("Back", { 110,50 }, sf::Color::White, sf::Color::Black, font, { 10,10 });

    sf::Text result;
    result.setFont(font);
    result.setPosition({ 300,350 });

    std::vector<sf::Text> results;
    sf::View scroll;
    int y = 0;
    scroll.setSize(sf::Vector2f(900.f, 900.f));
    scroll.setCenter(sf::Vector2f(450.f, 450.f));
    std::vector<BorrowedBookSection> carti;
    int height = 200;
    bool isBack = false;
    for (auto &book : acc.getBooks())
    {
            BorrowedBookSection section1(book.second, height, font, book.first);
            height += 200;
            carti.push_back(section1);
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                for (auto& x : carti)
                {
                    isBack =  x.buttonClicked(window,acc,avalabileBooks,x.id);

                    if (isBack == true)
                    {
                        
                        window.close();
                        UserAccountScene userAccount(acc, avalabileBooks);
                    }
                }
                if (back.isMouseover(window))
                {
                    window.close();
                    UserAccountScene userAccount(acc,avalabileBooks);
                }
            }
           
            if (event.type == sf::Event::MouseMoved)
            {
                back.mouseHovered(sf::Color::Black, sf::Color::White, window);

            }
            if (event.type == sf::Event::MouseMoved)
            {
                for (auto& x : carti)
                {
                    x.returnButton.mouseHovered(sf::Color::Black, sf::Color::White, window);
                    x.readButton.mouseHovered(sf::Color::Black, sf::Color::White, window);
                }
            }

            if (event.type == sf::Event::Resized)
            {
                sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }
            if (event.type == sf::Event::MouseWheelScrolled)
            {
                if (event.mouseWheelScroll.delta > 0 && y > 0)
                {
                    scroll.move(0, -100.f);
                    window.setView(scroll);
                    y--;
                }

            }
            if (event.type == sf::Event::MouseWheelScrolled)
            {
                if (event.mouseWheelScroll.delta < 0 && y<5)
                {
                    scroll.move(0, 100.f);
                    window.setView(scroll);
                    y++;
                }
            }
        }


        window.clear();

        for (auto& x : carti)
            x.drawBookBlock(window);
        window.draw(titlu);
        back.drawTo(window);
        window.display();
    }
}