#include "BookSection.h"

BookSection::BookSection(Book &book,float y, sf::Font& font,int idul)
{

    this->title.setFont(font);
    this->title.setString("Title: "+book.getTitle());
    this->title.setCharacterSize(30);
    this->title.setPosition({ 100,y });
    y = y + 30;
    this->author.setFont(font);
    this->author.setString("Author: " + book.getAuthor());
   
    this->author.setCharacterSize(30);
    this->author.setPosition({ 100,y });
    y = y + 30;
    this->genre.setFont(font);
    this->genre.setString("Genre: " + book.getGenre());
    this->genre.setCharacterSize(30);
    this->genre.setPosition({ 100,y });

    id = idul;
    this->burrowButton.setFont(font);
    this->burrowButton.setSize({ 200,40 });
    this->burrowButton.setBackColor(sf::Color::White);
    this->burrowButton.setTextColor(sf::Color::Black);
    this->burrowButton.setString("Burrow");
    this->burrowButton.setPosition({ 600,y-20 });
}

void BookSection::drawBookBlock(sf::RenderWindow& window)
{
    burrowButton.drawTo(window);
    window.draw(title);
    window.draw(author);
    window.draw(genre);
  

}

bool BookSection::buttonClicked(sf::RenderWindow& window,UserAccount &acc,std::unordered_map<int, Book>&avalabileBooks,int id)
{
    if (burrowButton.isMouseover(window))
    {
        std::cout << std::endl << "IDUL ESTEE: " << id << std::endl;
        Client c("commands.txt", "order.txt", "Requests.txt", "logIn.txt");
        int borrowSuccess  = c.burrowBook(acc,avalabileBooks,id);    
        if (borrowSuccess == 0)
        {
            acc.addBook(avalabileBooks[id]);
            avalabileBooks.erase(id);
        }
        else {
            ErrorBorrowingBook();
        }
        return true;
    }
    return false;
}
