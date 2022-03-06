#include "MainWindow.h"

MainWindow::MainWindow()
{
	window.create(sf::VideoMode(900, 900), "Library");
}

int MainWindow::display(std::unordered_map<int, Book> &avalabileBooks)
{
    Client c("commands.txt", "order.txt", "Requests.txt", "logIn.txt");
    std::string text = "Click Me";
    sf::Font font;
    font.loadFromFile("arial.ttf");
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cout << "Nu";
    }
    

    sf::Text titlu;
    titlu.setFont(font);
    titlu.setCharacterSize(30);
    titlu.setPosition({ 330,10 });
    titlu.setString("Biblioteca");
    sf::Texture logo;
    if (!logo.loadFromFile("images/logo.png"))
    {
       std::cout << "Nu";
    }
    logo.loadFromFile("images/logo.png");
    
    sf::Sprite logos;
    logos.setTexture(logo);
    logos.setScale(sf::Vector2f(0.25f, 0.25f));
    logos.setPosition({ 260,40 });
    
    sf::Texture t;
    if(!t.loadFromFile("images/background.png"))
     {
       std::cout << "Nu";
     }
    t.loadFromFile("images/background.png");
    sf::Sprite s;
    s.setTexture(t);

    Button login("Login", { 200,50 }, sf::Color::White, sf::Color::Black, font, { 300,280 });

    Button registerB("Register", { 200,50 }, sf::Color::White, sf::Color::Black, font, { 300,380 });
    Button exitB("Exit", { 200,50 }, sf::Color::White, sf::Color::Black, font, { 300,480 });

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseMoved)
            {
              
                login.mouseHovered(sf::Color::Black, sf::Color::White, window);

                registerB.mouseHovered(sf::Color::Black, sf::Color::White, window);

                exitB.mouseHovered(sf::Color::Black, sf::Color::White, window);
            }
         
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (login.isMouseover(window))
                {
                    window.close();
                    LoginForm loginForm(avalabileBooks);
                }
                if (exitB.isMouseover(window))
                {
                    window.close();
                }
                if (registerB.isMouseover(window))
                {
                    window.close();
                    RegisterForm registerForm(avalabileBooks);
                }

            }
        }
        window.clear();
       
        window.draw(s);
        window.draw(logos);
        login.drawTo(window);
        registerB.drawTo(window);
        window.draw(titlu);
        exitB.drawTo(window);
        window.display();
    }


    return 0;
}
