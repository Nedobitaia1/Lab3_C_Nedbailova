#ifndef BOOK_HPP
#define BOOK_HPP


#include <string>


class Book {
private:
    std::string* title;    
    std::string* author;  
    int* year;            


public:
    Book();

    Book(const std::string& t, const std::string& a, int y);

    Book(const Book& other);

    Book(Book&& other) noexcept;

    Book& operator=(const Book& other);

    Book& operator=(Book&& other) noexcept;

    ~Book();

    std::string getTitle() const;
    std::string getAuthor() const;
    int getYear() const;

    void printBookInfo() const;
    void setTitle(const std::string& newTitle);
};


#endif
