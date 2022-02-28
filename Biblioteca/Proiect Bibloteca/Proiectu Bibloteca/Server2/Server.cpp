#include "Server.h"

Server::Server(std::string commandFilename, std::string orderFilename, std::string booksFile, std::string accFile,std::string userBooksFile, std::string requestFile,std::string burrowedTimeFile,std::string logInFile)
{
	this->commandFilename = commandFilename;
	this->orderFilename = orderFilename;
	this->booksFile = booksFile;
	this->accFile = accFile;
	this->burrowedTimeFile=burrowedTimeFile;
	this->admin = Admin(booksFile, accFile, userBooksFile,burrowedTimeFile);
	this->requestFile = requestFile;
	this->logInFile = logInFile;	
}

const void Server::serve()
{

	sendAvalabileBooks();
	std::cout << "Running" << std::endl;
	std::cout << "Avalabile books sent!" << std::endl;
	while (true)
	{
		announce();
		wait();

		int request = getRequestType();
		std::cout << std::endl << "Request number is: " << request<<std::endl;

		switch (request)
		{
			case 1: 
			{
				addAccount();
				break;
			}
			case 2: 
			{
				login();
				break;
			}
			case 3: 			
			{
				removeBook();
				break;
			}
			case 4 : 
			{
				burrowBook();
				break;
			}
			case 5:
			{
				deleteAccount();
				break;
			}
			request = 0;
		}
	}
}

const void Server::wait()
{
	bool order = 0;
	while (order != 1)
	{
		std::ifstream fin(this->orderFilename);
		fin >> order; 
		fin.close();
	}
}

const void Server::announce()
{
	std::ofstream fout(this->orderFilename);
	fout << 0; 
	fout.close();
}

const void Server::addAccount()
{
	std::ifstream fin(this->logInFile);
	std::string username, password;
	fin >> username >> password;
	fin.close();
	std::cout << username << " " << password <<" ";
	std::ofstream fout(this->logInFile);
	fout<<admin.getAccountDB().createAccount(username, password);
	announce();
}

const void Server::login()
{
	std::ifstream fin(this->logInFile);
	std::string username,password;
	fin >> username>>password;
	std::cout<<std::endl << "SERVER USERNAME: " << username<<std::endl;
	std::cout << std::endl << "SERVER USERNAME: " << password << std::endl;
	if (admin.getAccountDB().accountExists(username) == true && admin.getAccountDB().getAccount(username).getPassword() == password)
	{
		std::ofstream fout(this->logInFile);
		UserAccount acc = admin.getAccountDB().getAccount(username);
		fout << acc.getUserID()<<std::endl;
		std::cout << "SERVER ID: " << acc.getUserID();
		admin.transformBookIdToBooks(acc); 
		for (auto& book : acc.getBooks())
		{
			fout << book.second.getId() << std::endl << book.second.getTitle() << std::endl << book.second.getAuthor() << std::endl << book.second.getPublisher() << std::endl << book.second.getGenre() << std::endl;
			std::cout << "Titlul este: " << book.second.getTitle() << std::endl;
		}
		fout.close();
	}
	else 
	{
		std::ofstream fout(this->logInFile);
		fout << -1;
	}
	announce();
}

const int Server::getRequestType()
{
	std::ifstream rin(this->requestFile);
	int request;
	rin >> request;
	std::cout<<std::endl << "Request recived" << std::endl;
	rin.close();
	return request;
}

const void Server::sendAvalabileBooks()
{
	std::ofstream fout(this->commandFilename);
	for (auto& book : admin.getAvailableBooks())
	{
		fout <<book.second.getId()<<std::endl<< book.second.getTitle() << std::endl << book.second.getAuthor() << std::endl << book.second.getPublisher() << std::endl << book.second.getGenre() << std::endl;
	}
	announce();
}

const void Server::removeBook()
{
	std::ifstream fin(this->commandFilename);
	int bookId,userId;
	fin >> bookId >> userId;

	std::set<int>auxiliarySet;
	for (auto& id : admin.getUserBooks()[userId])
	{
		if (id != bookId)
			auxiliarySet.insert(id);
	}

	if (auxiliarySet.size() != 0)
		admin.getUserBooks()[userId] = auxiliarySet;
	else
		admin.getUserBooks()[userId].clear();
	admin.addBookToAvalabileBooks(admin.getAllBooks()[bookId-1]); 
	admin.getBurrowedTimeBooks().erase(bookId);
	admin.saveUsersBooksToFile(); 
	admin.saveBurrowedTimeBooks();
	std::cout<<std::endl << "Book removed succesfully";
	announce();
}

const void Server::burrowBook()
{
	std::ifstream fin(this->commandFilename);
	int bookId,userId;
	fin >> bookId >> userId;
	std::set<int>auxiliarySet;
	for (auto& id : admin.getUserBooks()[userId])
	{
		auxiliarySet.insert(id);
	}
	std::cout<<std::endl<<"Le book id: " << bookId << " " << userId << " "<<std::endl;
	auxiliarySet.insert(bookId);
	admin.getUserBooks()[userId] = auxiliarySet;
	admin.addBookToBurrowedBooksTime(bookId);
	admin.saveUsersBooksToFile();
	admin.saveBurrowedTimeBooks();
	admin.getAvailableBooks().erase(bookId);
	announce();
}

const void Server::deleteAccount()
{
	std::ifstream fin(this->commandFilename);
	std::string username;
	int id;
	fin >> username>>id;
	admin.getAccountDB().deleteAccount(username);
	admin.getUserBooks().erase(id);
	admin.saveUsersBooksToFile();
}
