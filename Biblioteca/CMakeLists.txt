cmake_minimum_required(VERSION 3.20)
project(repobiblioteca)

set(CMAKE_CXX_STANDARD 14)

include_directories("Proiect Bibloteca/Proiectu Bibloteca/Proiectu_Bibloteca")

add_executable(repobiblioteca
        "Proiect Bibloteca/Proiectu Bibloteca/Proiectu_Bibloteca/AccountDatabase.cpp"
        "Proiect Bibloteca/Proiectu Bibloteca/Proiectu_Bibloteca/AccountDatabase.h"
        "Proiect Bibloteca/Proiectu Bibloteca/Proiectu_Bibloteca/Book.cpp"
        "Proiect Bibloteca/Proiectu Bibloteca/Proiectu_Bibloteca/Book.h"
        "Proiect Bibloteca/Proiectu Bibloteca/Proiectu_Bibloteca/Engine.cpp"
        "Proiect Bibloteca/Proiectu Bibloteca/Proiectu_Bibloteca/Engine.h"
        "Proiect Bibloteca/Proiectu Bibloteca/Proiectu_Bibloteca/Proiectu_Bibloteca.cpp"
        "Proiect Bibloteca/Proiectu Bibloteca/Proiectu_Bibloteca/UserAccount.cpp"
        "Proiect Bibloteca/Proiectu Bibloteca/Proiectu_Bibloteca/UserAccount.h"
        "Proiect Bibloteca/Proiectu Bibloteca/Proiectu_Bibloteca/UserEngine.cpp"
        "Proiect Bibloteca/Proiectu Bibloteca/Proiectu_Bibloteca/UserEngine.h")
