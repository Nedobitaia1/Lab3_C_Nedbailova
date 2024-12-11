#include "Book.hpp"
#include <iostream>


// Конструктор по умолчанию
Book::Book() : title(new std::string("Unknown")), author(new std::string("Unknown")), year(new int(0)) {
    // std::cout << "Constructor without parameters: title='Unknown', author='Unknown', year=0" << std::endl;
}


// Конструктор с параметрами
Book::Book(const std::string& t, const std::string& a, int y)
    : title(new std::string(t)), author(new std::string(a)), year(new int(y)) {
    // std::cout << "Constructor with parameters: title='" << t << "', author='" << a << "', year=" << y << std::endl;
}


// Конструктор копирования
Book::Book(const Book& other)
    : title(new std::string(*other.title)), author(new std::string(*other.author)), year(new int(*other.year)) {
    // std::cout << "Copy constructor" << std::endl;
}


// Конструктор перемещения
Book::Book(Book&& other) noexcept
    : title(other.title), author(other.author), year(other.year) {
    other.title = nullptr;
    other.author = nullptr;
    other.year = nullptr;
    // std::cout << "Move constructor" << std::endl;
}


// перегрузка оператора присваивания без перемещения
Book& Book::operator=(const Book& other) {
    if (this != &other) {
        // std::cout << "Overloading the assignment operator without moving" << std::endl;


        delete title;
        delete author;
        delete year;


        title = new std::string(*other.title);
        author = new std::string(*other.author);
        year = new int(*other.year);


    }
    return *this;
}


// перегрузка оператора присваивания с перемещением
Book& Book::operator=(Book&& other) noexcept {
    if (this != &other) {
        // std::cout << "Overloading the assignment operator with moving" << std::endl;


        delete title;
        delete author;
        delete year;


        title = other.title;
        author = other.author;
        year = other.year;


        other.title = nullptr;
        other.author = nullptr;
        other.year = nullptr;


    }
    return *this;
}


// Деструктор
Book::~Book() {
    // std::cout << "Destructor " << std::endl;
   
    // if (title) {
    //     std::cout << "title='" << *title << "', ";
    // }
    // if (author) {
    //     std::cout << "author='" << *author << "', ";
    // }
    // if (year) {
    //     std::cout << "year=" << *year << std::endl;
    // }
    delete title;
    delete author;
    delete year;
}


// Методы для получения информации о книге
std::string Book::getTitle() const {
    return *title;
}


std::string Book::getAuthor() const {
    return *author;
}


int Book::getYear() const {
    return *year;
}


// Вывод информации о книге
void Book::printBookInfo() const {
    std::cout << "Title: " << getTitle() << ", Author: " << getAuthor() << ", Year: " << getYear() << std::endl;
}


// Изменение заголовка
void Book::setTitle(const std::string& newTitle) {
        *title = newTitle;
}
