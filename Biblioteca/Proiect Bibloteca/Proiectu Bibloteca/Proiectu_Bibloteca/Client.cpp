#include "Client.h"

Client::Client(std::string commandFilename, std::string orderFilename,std::string requestFile, std::string logInFile)
{
	this->commandFilename = commandFilename;
	this->orderFilename = orderFilename;	
	this->requestFile = requestFile;
	this->logInFile = logInFile;
}

const void Client::wait()
{
	int order = 1;
	while (order != 0)
	{
		std::ifstream fin(orderFilename); 
		fin >> order; 
		fin.close();
	}
}

const void Client::announce()
{
	std::ofstream fout(orderFilename);
	fout << 1 << std::endl; 
}

const UserAccount Client::logIn(bool &login,std::string username,std::string password)
{
	sendRequestType(2);
	UserAccount account;
	std::ofstream fout(this->logInFile);
	
	fout << username << std::endl<<password;
	fout.close();
	announce();
	wait();
	std::ifstream fin(this->logInFile);
	int id;
	fin >> id;
	std::cout<<std::endl<<"ID-UL ESTE: " << id<<std::endl;
	if (id != -1)
	{
		account.setUsername(username);
		account.setPassword(password);
		account.setUserID(id);
		while (fin.good())
		{
			int id;
			std::string title, author, genere, publisher;
			fin >> id >> title >> author >> genere >> publisher;
			Book b(id, title, author, publisher, genere);
			if(b.getId()>0)
				account.addBook(b);
			std::cout << "Titlul este: " << title << std::endl;
			
		}
		login = true;
		fin.close();
	}
	else {
		std::cout << "Invalid account data";
	}
	return account;	
}

const bool Client::newAccount(std::string username,std::string password)
{
	sendRequestType(1);
	std::ofstream fout(this->logInFile);
	fout << username << std::endl << password;
	fout.close();
	announce();
	wait();
	std::ifstream fin(this->logInFile);
	bool response;
	fin >> response;
	fin.close();
	if (response == true)
		return true;
	return false;
}

const std::vector<Book> Client::searchBook(std::unordered_map<int, Book> avalabileBooks, std::string bookTitle)
{
	std::cout << "Introduce the book you would like to search: ";
	std::vector<Book> results;
	for (auto& book : avalabileBooks)
	{
		if (book.second.getTitle().compare(bookTitle) == 0)
		{
			results.push_back(book.second);
			
			return results;
		}
	}
	for (auto& book : avalabileBooks)
	{
		int distance = -1;
		distance = levenstheinDistance(bookTitle, book.second.getTitle());
		if (distance != -1 && distance < 6)
			results.push_back(book.second);
		
	}
	std::cout << std::endl << std::endl << results.size();
	return results;
}

const std::unordered_map<int, Book> Client::makeAvalabileBooks()
{
	wait();
	std::ifstream fin(this->commandFilename);
	std::unordered_map<int, Book> avalabileBooks;
	int id;
	while (fin.good())
	{
		std::string title, author, publisher, genere;
		fin >> id >> title >> author >> publisher >> genere;
		Book b(id, title, author, publisher, genere);
		avalabileBooks.insert({b.getId(),b});
	}
	return avalabileBooks;
}

const void Client::seeAvalabileBooks(std::unordered_map<int,Book>avalabileBooks)
{
	for (auto& book : avalabileBooks)
	{	
			book.second.printBook();
			std::cout << std::endl;	
	}
}

const bool Client::burrowBook(UserAccount &acc, std::unordered_map<int, Book> avalabileBooks,int id)
{
	sendRequestType(4);

	for (auto& it : avalabileBooks)
	{
		std::cout << it.first << " " << it.second.getTitle()<<std::endl;
	}
	if (avalabileBooks.find(id) != avalabileBooks.end()) 
	{
		if (acc.checkBurrowBookEligibility(id) == true)
		{
			acc.addBook(avalabileBooks[id]);
			std::ofstream fout(this->commandFilename);
			fout << id << std::endl << acc.getUserID();
			std::cout << "IDUL ESTE: " << id << "IDUL CONTULUI ESTE: " << acc.getUserID()<<std::endl;
			fout.close();
			announce();
			std::cout<<std::endl << "Book burrowed succesfully"<<std::endl;
		}
		else
		{		
			std::cout<<std::endl << "Conditions to burrow the book not met (error 203)"<<std::endl;
			return 1;
		}
	}
	else {
		std::cout << "Book is unavalabile " << std::endl;
		return 1;
	}
	return 0;
}

const void Client::returnBook(UserAccount acc,int id)
{
	sendRequestType(3);
	acc.removeBook(id);
	std::cout<<std::endl << "Book returned succesfuly";
	std::ofstream fout(this->commandFilename);
	fout << id <<std::endl<<acc.getUserID();
	announce();	
}

const void Client::sendRequestType(int request)
{
	std::ofstream fout(this->requestFile);
	fout << request;
}

const void Client::seeBurrowedBooks(UserAccount account)
{
	for (auto&book : account.getBooks())
	{
		book.second.printBook();
		std::cout << std::endl;
	}
}

#define MIN(x,y) ((x) < (y) ? (x) : (y))
int Client::levenstheinDistance(std::string string1, std::string string2)
{
	int l1, l2, t, track;
	int dist[50][50];
	l1 = string1.size();
	l2 = string2.size();

	for (int i = 0; i < l1; i++) 
	{
		dist[0][i] = i;
	}
	for (int j = 0; j < l2; j++) {
		dist[j][0] = j;
	}
	for (int j = 1; j <= l1; j++) {
		for (int i = 1; i <= l2; i++) 
		{
			if (string1[j-1] == string2[i-1]) {
				track = 0;
			}
			else {
				track = 1;
			}
			t = MIN((dist[i-1][j] + 1), (dist[i][j - 1] + 1));
			dist[i][j] = MIN(t, (dist[i - 1][j - 1] + track));
		}
	}
	std::cout << std::endl << dist[l2-1][l1-1] << std::endl;
	return dist[l2-1][l1-1];
}

const std::vector<Book> Client::seeSearchResults(std::unordered_map<int, Book> avalabileBooks,std::string bookTitle)
{
	std::vector<Book>results=searchBook(avalabileBooks,bookTitle);
	for(auto & book:results)
	{
		std::cout << book.getTitle() << " ";
	}
	return results;
}

const void Client::deleteAccount(std::string username,int id)
{
	sendRequestType(5);
	std::ofstream fout(this->commandFilename);
	fout << username<<" "<<id;
	announce();
	fout.close();
}

