#include "RegisterForm.h"

RegisterForm::RegisterForm(std::unordered_map<int, Book> avalabileBooks)
{
    window.create(sf::VideoMode(900, 900), "Register");
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cout << "Nu";
    }
    font.loadFromFile("arial.ttf");
    Button back("Back", { 110,50 }, sf::Color::White, sf::Color::Black, font, { 10,10 });
    Button login("Login", { 200,50 }, sf::Color::White, sf::Color::Black, font, { 410,600 });
    Button registerB("Register", { 200,50 }, sf::Color::White, sf::Color::Black, font, { 200,600 });

    sf::Text titlu;
    titlu.setFont(font);
    titlu.setCharacterSize(30);
    titlu.setPosition({ 330,10 });
    titlu.setString("Create an account");

    sf::Texture t;
    if (!t.loadFromFile("images/background.png"))
     {
        std::cout << "Nu";
     }
    t.loadFromFile("images/background.png");
    
        sf::Sprite s;
    s.setTexture(t);

    sf::Text LabelUsername;
    LabelUsername.setFont(font);
    LabelUsername.setCharacterSize(30);
    LabelUsername.setPosition({ 330,90 });
    LabelUsername.setString("Username");

    sf::Text PasswordLabel;
    PasswordLabel.setFont(font);
    PasswordLabel.setCharacterSize(30);
    PasswordLabel.setPosition({ 330,190 });
    PasswordLabel.setString("Password");

    InputBox usernameInput(20, sf::Color::Black, true, 10, false);
    usernameInput.setFont(font);
    InputBox passwordInput(20, sf::Color::Black, true, 10, false);
    passwordInput.setFont(font);
    passwordInput.SetPass(true);
    usernameInput.setPosition({ 300, 150 });
    passwordInput.setPosition({ 300, 250 });


    sf::Text RegisterLabel;
    RegisterLabel.setFont(font);
    RegisterLabel.setCharacterSize(15);
    RegisterLabel.setPosition({ 410,560 });
    RegisterLabel.setString("Already have an account?");
    bool isBack = false;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseMoved)
            {
                back.mouseHovered(sf::Color::Black, sf::Color::White, window);
                login.mouseHovered(sf::Color::Black, sf::Color::White, window);
                registerB.mouseHovered(sf::Color::Black, sf::Color::White, window);
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (back.isMouseover(window))
                {
                    window.close();
                    MainWindow m;
                    m.display(avalabileBooks);
                }
            }
            if (isBack == true)
            {
                window.close();
                MainWindow m;
                m.display(avalabileBooks);
            }
            if (event.type == sf::Event::TextEntered)
            {
                usernameInput.typedOn(event);
                passwordInput.typedOn(event);

            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (usernameInput.isMouseover(window))
                {
                    usernameInput.setSelected(true);
                    passwordInput.setSelected(false);
                }
                if (passwordInput.isMouseover(window))
                {
                    passwordInput.setSelected(true);
                    usernameInput.setSelected(false);
                }
                if (registerB.isMouseover(window))
                {
                    std::cout << usernameInput.getText() << " " << passwordInput.getPassword();
                    Client c("commands.txt", "order.txt", "Requests.txt", "logIn.txt");
                    bool isRegisterOk = c.newAccount(usernameInput.getText(),passwordInput.getPassword());      
                    isBack = true;
                    if (isRegisterOk == false)
                    {
                        RegisterError();
                    }
                }
                if (login.isMouseover(window))
                {
                    window.close();
                    LoginForm logIn(avalabileBooks);
                }
            }
        }
        window.clear();
        back.drawTo(window);
        login.drawTo(window);
        registerB.drawTo(window);
        window.draw(LabelUsername);
        window.draw(PasswordLabel);
        window.draw(titlu);
        window.draw(RegisterLabel);
        usernameInput.drawTo(window);
        passwordInput.drawTo(window);
        window.display();
        
    }

}
