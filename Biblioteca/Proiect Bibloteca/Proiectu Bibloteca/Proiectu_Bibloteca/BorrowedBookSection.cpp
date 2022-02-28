#include "BorrowedBookSection.h"


BorrowedBookSection::BorrowedBookSection(Book& book, float y, sf::Font& font, int idul)
{
    this->title.setFont(font);
    this->title.setString("Title: " + book.getTitle());
    this->title.setCharacterSize(30);
    this->title.setPosition({ 80,y });
    y = y + 30;
    this->author.setFont(font);
    this->author.setString("Author: " + book.getAuthor());

    this->author.setCharacterSize(30);
    this->author.setPosition({ 80,y });
    y = y + 30;
    this->genre.setFont(font);
    this->genre.setString("Genre: " + book.getGenre());
    this->genre.setCharacterSize(30);
    this->genre.setPosition({ 80,y });

    id = idul;

    this->readButton.setFont(font);
    this->readButton.setSize({ 150,45 });
    this->readButton.setBackColor(sf::Color::White);
    this->readButton.setTextColor(sf::Color::Black);
    this->readButton.setString("Read");
    this->readButton.setPosition({ 700,y - 50 });

    this->returnButton.setFont(font);
    this->returnButton.setSize({ 150,45 });
    this->returnButton.setBackColor(sf::Color::White);
    this->returnButton.setTextColor(sf::Color::Black);
    this->returnButton.setString("Return");
    this->returnButton.setPosition({ 520,y +5 });
}

void BorrowedBookSection::drawBookBlock(sf::RenderWindow& window)
{

    burrowButton.drawTo(window);
    readButton.drawTo(window);
    returnButton.drawTo(window);
    window.draw(title);
    window.draw(author);
    window.draw(genre);

}

bool BorrowedBookSection::buttonClicked(sf::RenderWindow& window,UserAccount &acc, std::unordered_map<int, Book> &avalabileBooks,int id)
{
    Client c("commands.txt", "order.txt", "Requests.txt", "logIn.txt");
    if (readButton.isMouseover(window))
    {
        int idCarte = id;
        std::string cale = "images/poza" + std::to_string(idCarte);
        cale += ".png";
        std::cout << cale;
        BookContent(acc,avalabileBooks,cale);
    }
    if (returnButton.isMouseover(window))
    {
        avalabileBooks.insert({id,acc.getBooks()[id] });
        std::cout <<std::endl <<acc.getBooks()[id].getTitle() << std::endl;
        c.returnBook(acc, id);       
        acc.getBooks().erase(id);
        return true;
    }
    return false;
}