#include "Admin.h"

void Admin::loadFromFile(std::string filename)
{
	std::ifstream fin(filename);
	while (fin.good())
	{
		int id;
		std::string title, author, publisher, genere;
		fin >> id >> title >> author >> publisher >> genere;
		Book b(id,title, author, publisher, genere);
		allBooks.insert({ b.getId(),b });
	}
}

const void Admin::saveToFile()const
{
	std::ofstream fout(filename);
	for (auto& book : allBooks)
	{
		std::string toWrite = "";
		Book bok = book.second;
		toWrite += bok.getTitle() + "\n" + bok.getAuthor() + "\n" + bok.getPublisher() + "\n" + bok.getGenre() + "\n";
		fout << toWrite;
	}
}

const void Admin::saveOneToFile(Book book)const
{
	std::ofstream fout;
	fout.open(filename, std::ios_base::app);
	std::string toWrite = "";
	toWrite += book.getTitle() + "\n" + book.getAuthor() + "\n" + book.getPublisher() + "\n" + book.getGenre() + "\n";
	fout << toWrite;
}

const void Admin::saveUsersBooksToFile()const
{
	std::ofstream fout(this->userBooksFile);
	for (auto& user : userBooks)
	{
		if (user.first >= 0)
		fout << user.first << std::endl << user.second.size() << std::endl;	
		for (auto& id : user.second)
		{
			fout << id << " ";
		}
		fout<< std::endl;
	}
}

const void Admin::saveBurrowedTimeBooks()const
{
	std::ofstream fout(burrowedTimeFile);
	for (auto& book : burrowedTimeBooks)
	{
		if(book.first>=0)
			fout << book.first << std::endl << book.second << std::endl;
	}
}

void Admin::makeAvalabileBooks()
{
	std::ifstream fin(this->userBooksFile);
	std::set<int> ids; 
	while (fin.good())
	{
		int userId, burrowedSize;
		fin >> userId >> burrowedSize;
		for (int i = 0; i < burrowedSize; i++)
		{
			int bookId;
			fin >> bookId;
			ids.insert(bookId);
		}
	}
	fin.close();
	for (auto& book : allBooks)
	{
		if (ids.count(book.second.getId()) == 0)
			availableBooks.insert(book); 
	}
}

void Admin::loadUserBooks()
{
	std::ifstream uin(userBooksFile);
	while (uin.good())
	{
		int uID, nrBooks;
		std::set<int> booksID;
		uin >> uID >> nrBooks;
		for (int i = 0; i < nrBooks; i++)
		{
			int book;
			uin >> book;
			booksID.insert(book);
		}
		userBooks.insert(std::make_pair(uID, booksID));
	}
	uin.close();
}

void Admin::loadBurrowedTimeFile()
{
	std::ifstream fin(this->burrowedTimeFile);
	while (fin.good())
	{
		int bookId, burrowedTime;
		fin >> bookId >> burrowedTime;
		burrowedTimeBooks.insert({ bookId,burrowedTime });
	}
}

void Admin::makeBurrowedTimeBooks()
{
	for (auto& user : userBooks)
	{
		for(auto&book: user.second)
		{
			if(book>0)
				burrowedTimeBooks.insert({ book,time(NULL)/3600 });
		}
	}
	saveBurrowedTimeBooks();
}

Admin::Admin()
{
}

Admin::Admin(std::string filename,std::string accFile, std::string userBooksFile, std::string burrowedTimeFile)
{
	this->filename = filename;
	this->accFile = accFile;
	this->userBooksFile = userBooksFile;
	this->burrowedTimeFile = burrowedTimeFile;
	this->accounts = AccountDatabase(accFile,userBooksFile);
	loadFromFile(filename); 
	loadUserBooks();
	loadBurrowedTimeFile();
	makeAvalabileBooks();
}

void Admin::transformBookIdToBooks(UserAccount &acc)
{
	for (auto& it : acc.getBooksIDs())
	{
		acc.addBook(allBooks[it]);
	}
}

std::unordered_map<int, Book>& Admin::getAllBooks()
{
	return allBooks;
}

std::unordered_map<int, Book>& Admin::getAvailableBooks()
{
	return availableBooks;
}


void Admin::setAllBooks(std::unordered_map<int, Book> newAllBooks)
{
	this->allBooks = newAllBooks;
}

void Admin::setAvailableBooks(std::unordered_map<int, Book> newAvailableBooks)
{
	this->availableBooks = newAvailableBooks;
}

bool Admin::searchBook(std::string name)
{
	for (auto& book : allBooks) {
		if (book.second.getTitle() == name)
			return true;
	}
	return false;
}

AccountDatabase& Admin::getAccountDB()
{
	return accounts;
}

 std::map<int, std::set<int>>& Admin::getUserBooks()
{
	return userBooks;
}

void Admin::addBookToAvalabileBooks(Book b)
{
	availableBooks.insert({ b.getId(),b });
}

std::map<int, int>& Admin::getBurrowedTimeBooks()
{
	return this->burrowedTimeBooks;
}

void Admin::addBookToBurrowedBooksTime(int bId)
{
	burrowedTimeBooks.insert({ bId,time(NULL) / 3600 });
}
