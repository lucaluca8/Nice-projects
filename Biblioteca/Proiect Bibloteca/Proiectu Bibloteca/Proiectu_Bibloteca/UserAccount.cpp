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

const std::string& UserAccount::getUsername() const 
{
    return this->username;
}

const std::string& UserAccount::getPassword() const
{
    return this->password;
}

void  UserAccount::setUsername(std::string username)
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


std::unordered_map<int, Book>& UserAccount::getBooks()
{
    return this->books;
}
void UserAccount::setUserID(int ID)
{
    this->user_id = ID;
}

const int& UserAccount::getUserID()const
{
    return this->user_id;
}

void UserAccount::removeBook(int id)
{
    books.erase(id);
}

const bool UserAccount::checkBurrowBookEligibility(int bookId)const
{
    if (books.size() == 0)
        return true;
    std::map<long long int, long long int> burrowedTimeBooks;
    std::ifstream fin("BurrowedTime.txt");
    while (fin.good())
    {
        long long int bId, timer;
        fin >> bId >> timer;
        burrowedTimeBooks.insert({ bId,timer });
    }
    std::cout <<std::endl << "CLIENT BOOK SIZE: " << books.size()<<std::endl;
    if (books.size() == 5)
        return false;
    if (books.find(bookId) != books.end())
        return false;
    bool burrowBookTimerOk = true;
    int timer = time(NULL)/3600;
    for (auto& it : books)
    {
        if (timer >= burrowedTimeBooks[it.first] + (14 * 24))
        {
            burrowBookTimerOk = false;
        }
    }
    if (burrowBookTimerOk == false)
        return false;
    return true;

}
