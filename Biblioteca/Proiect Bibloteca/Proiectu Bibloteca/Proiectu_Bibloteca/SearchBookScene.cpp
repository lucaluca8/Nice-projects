#include "SearchBookScene.h"


SearchBookScene::SearchBookScene(UserAccount acc, std::unordered_map<int, Book> avalabileBooks)
{
    window.create(sf::VideoMode(900, 900), "Search Books");

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
    titlu.setString("Search a book here");

    Button back("Back", { 110,50 }, sf::Color::White, sf::Color::Black, font, { 10,10 });

    InputBox searchBox(20, sf::Color::Black, true, 30, false);
    searchBox.setFont(font);
    searchBox.setPosition({ 300,80 });
    Button searchButton("Search", { 120,30 }, sf::Color::White, sf::Color::Black, font, { 550,80 });
    searchButton.setCharacterSize(20);

    sf::View scroll;
    int y = 0;
    scroll.setSize(sf::Vector2f(900.f, 900.f));
    scroll.setCenter(sf::Vector2f(450.f, 450.f));

    std::vector<BookSection> carti;
    int height = 200;

    bool searchPressed = false;
    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            bool isBack = false;
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                for (auto& x : carti)
                {
                    isBack = x.buttonClicked(window, acc, avalabileBooks, x.id);     
                    if (isBack == true)
                    {
                        window.close();
                        UserAccountScene userScene(acc, avalabileBooks);
                    }
                }

                if (searchBox.isMouseover(window))
                {
                    searchBox.setSelected(true);
                }
                if (searchButton.isMouseover(window))
                {
                    window.clear();
                    height = 200;
                    carti.clear();
                    std::string subject;
                    subject = searchBox.getText();
                    //get s the subject written in the searchbox
                    Client c("commands.txt", "order.txt", "Requests.txt", "logIn.txt");
                    std::vector<Book> searchResults = c.searchBook(avalabileBooks, subject);
                    float x = 150;
                    for (auto& it : searchResults)
                    {
                        BookSection section1(it, height, font, it.getId());
                        height += 200;
                        carti.push_back(section1);
                    }
                    x = 2500;
                }
                if (back.isMouseover(window))
                {
                    window.close();
                    UserAccountScene userScene(acc, avalabileBooks);
                }
            }
            if (event.type == sf::Event::TextEntered)
            {
                searchBox.typedOn(event);
            }
            if (event.type == sf::Event::MouseMoved)
            {
                back.mouseHovered(sf::Color::Black, sf::Color::White, window);
                searchButton.mouseHovered(sf::Color::Black, sf::Color::White, window);

            }
            if (event.type == sf::Event::MouseMoved)
            {
                for (auto& x : carti)
                {
                    x.burrowButton.mouseHovered(sf::Color::Black, sf::Color::White, window);
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
                if (event.mouseWheelScroll.delta < 0 && y < 92) 
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
        searchButton.drawTo(window);
        searchBox.drawTo(window);
        window.display();
    }

}
