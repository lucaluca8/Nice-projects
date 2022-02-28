#include <iostream>
#include <fstream>
#include "Server.h"

int main()
{
	Server s("C:/Users/OMEN_PC1/Desktop/FINAL REPO/Proiect Bibloteca/Proiectu Bibloteca/Proiectu_Bibloteca/commands.txt", "C:/Users/OMEN_PC1/Desktop/FINAL REPO/Proiect Bibloteca/Proiectu Bibloteca/Proiectu_Bibloteca/order.txt", "C:/Users/OMEN_PC1/Desktop/FINAL REPO/Proiect Bibloteca/Proiectu Bibloteca/Proiectu_Bibloteca/books.txt", "C:/Users/OMEN_PC1/Desktop/FINAL REPO/Proiect Bibloteca/Proiectu Bibloteca/Proiectu_Bibloteca/AccountDataBase.txt", "C:/Users/OMEN_PC1/Desktop/FINAL REPO/Proiect Bibloteca/Proiectu Bibloteca/Proiectu_Bibloteca/UsersBooks.txt", "C:/Users/OMEN_PC1/Desktop/FINAL REPO/Proiect Bibloteca/Proiectu Bibloteca/Proiectu_Bibloteca/Requests.txt","C:/Users/OMEN_PC1/Desktop/FINAL REPO/Proiect Bibloteca/Proiectu Bibloteca/Proiectu_Bibloteca/BurrowedTime.txt", "C:/Users/OMEN_PC1/Desktop/FINAL REPO/Proiect Bibloteca/Proiectu Bibloteca/Proiectu_Bibloteca/logIn.txt");
	s.serve();
	return 0;
}
