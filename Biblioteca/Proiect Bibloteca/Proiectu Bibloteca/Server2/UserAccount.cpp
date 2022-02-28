#include "UserAccount.h"

UserAccount::UserAccount()
{
    this->username = "";
    this->password = "";
}

UserAccount::UserAccount(std::string username, std::string password)
{
    this->username = username;
    this->password = password;
}

const std::string UserAccount::getUsername()const
{
    return username;
}

const std::string UserAccount::getPassword()const
{
    return password;
}

void UserAccount::setUsername(std::string username)
{
    this->username = username;
}

void UserAccount::setPassword(std::string password)
{
    this->password = password;
}

void UserAccount::setBooks(std::unordered_map<int, Book> books)
{
    this->books = books;
}

void UserAccount::addBook(Book b)
{
    books.insert({b.getId(),b});  
}

void UserAccount::addBookByID(int id)
{
    booksID.push_back(id);
}


std::unordered_map<int, Book>& UserAccount::getBooks()
{
    return this->books;
}
void UserAccount::setUserID(int ID)
{
    this->user_id = ID;
}

int UserAccount::getUserID()
{
    return this->user_id;
}
std::vector<int> UserAccount::getBooksIDs()
{
    return booksID;
}

