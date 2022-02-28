#include "UserAccountScene.h"


UserAccountScene::UserAccountScene(UserAccount &acc, std::unordered_map<int, Book> &avalabileBooks)
{
    window.create(sf::VideoMode(900, 900), "User Account");
    std::cout<<std::endl << "NUMARUL CARTILOR CONTULUI: " << acc.getBooks().size();
    Client c("commands.txt", "order.txt", "Requests.txt", "logIn.txt");
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cout << "Nu";
    }
    font.loadFromFile("arial.ttf");

    sf::Text titlu;
    titlu.setFont(font);
    titlu.setCharacterSize(30);
    titlu.setPosition({ 330,10 });
    titlu.setString("Hello " + acc.getUsername());

    sf::Texture t;
     if (!t.loadFromFile("images/background.png"))
     {
        std::cout << "Nu";
     }
     t.loadFromFile("images/background.png");
    
     sf::Sprite s;
     s.setTexture(t);

    Button back("Exit", { 110,50 }, sf::Color::White, sf::Color::Black, font, { 10,10 });
    Button availableBooks("See available books", { 370,50 }, sf::Color::White, sf::Color::Black, font, { 300,100 });
    Button searchBook("Search book", { 370,50 }, sf::Color::White, sf::Color::Black, font, { 300,200 });
    Button burrowedBooks("See borrowed books", { 370,50 }, sf::Color::White, sf::Color::Black, font, { 300,300 });
    Button deleteAccount("Delete Account", { 370,50 }, sf::Color::White, sf::Color::Black, font, { 300,400 });

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseMoved)
            {

                availableBooks.mouseHovered(sf::Color::Black, sf::Color::White, window);

                searchBook.mouseHovered(sf::Color::Black, sf::Color::White, window);

                burrowedBooks.mouseHovered(sf::Color::Black, sf::Color::White, window);

                back.mouseHovered(sf::Color::Black, sf::Color::White, window);
                deleteAccount.mouseHovered(sf::Color::Black, sf::Color::White, window);
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (deleteAccount.isMouseover(window))
                {
                    c.deleteAccount(acc.getUsername(),acc.getUserID());
                    AccountDeletedSuccessfully();
                    window.close();
                }
                if (back.isMouseover(window))
                {
                    window.close();
                }
                if(searchBook.isMouseover(window))
                {
                    window.close();
                    SearchBookScene searchBook(acc,avalabileBooks);
                }
                if (availableBooks.isMouseover(window))
                {
                    window.close();
                    AvailableBooksScene avBooks(avalabileBooks, acc);
                }
                if (burrowedBooks.isMouseover(window))
                {
                    window.close();
                    BorrowedBooks borrowedBooks(acc, avalabileBooks);
                }
            }
        }
        window.clear();

        window.draw(s);
        availableBooks.drawTo(window);
        searchBook.drawTo(window);
        burrowedBooks.drawTo(window);
        window.draw(titlu);
        back.drawTo(window);
        deleteAccount.drawTo(window);
        window.display();
    }

}
