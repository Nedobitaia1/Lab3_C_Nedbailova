#include <vector>
#include <list>
#include "Book.hpp"
#include <iostream>
#include <random>
#include <algorithm>
#include <numeric>


bool compareByYearMax(const Book& a, const Book& b) {
    return a.getYear() > b.getYear(); 
}

bool compareByYearMin(const Book& a, const Book& b) {
    return a.getYear() < b.getYear();
}

int sumBookYears(int sum, const Book& book) {
    return sum + book.getYear();
}

bool isYearGreaterThanAverage(const Book& book, double averageYear) {
    return book.getYear() > averageYear;
}

bool isOddYear(const Book& book) {
    return book.getYear() % 2 != 0;
}


void processBooks(const std::vector<Book>& books) {
    std::cout << "-----processBooks: -----" << std::endl;
    for (const auto& book : books) {
        book.printBookInfo();
    }
    std::cout << "-----processBooks end -----" << std::endl;
}

Book createBook() {
    std::cout << "-----createBook: -----" << std::endl;
    return Book("And Quiet Flows the Don", "Mikhail Sholokhov", 1928);
    std::cout << "-----createBook end -----" << std::endl;
}

Book& getBookByIndex(std::vector<Book>& books, size_t index) {
    return books[index];  
}


Book getBook(Book book) {
    std::cout << "-----getBook-----" << std::endl;
    book.setTitle(book.getTitle() + " - Special Edition");
    std::cout << "Processing book: ";
    book.printBookInfo();
    std::cout << "-----getBook end-----" << std::endl;
    return book; 
}

int main() {

//-------------------------------- 1 -------------------------------------     
    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> distrib(500, 1000); 
    std::uniform_int_distribution<> distrib2(0, 2020);
    
    int random_number = distrib(gen);

    std::cout<<"Vector size:"<< random_number << std::endl;

    std::uniform_int_distribution<> distrib3(0, int(random_number/2));
    std::uniform_int_distribution<> distrib4(int(random_number/2), random_number);

    std::vector<Book> v1;

    for (int i = 0; i < random_number; i++) {
        std::string title = "Book" + std::to_string(distrib2(gen));
        std::string author = "Author" + std::to_string(distrib2(gen));
        int date = distrib2(gen);
        v1.push_back(Book(title, author, date));
    }

    
    for (int i = 0; i < 5; i++) {
        Book& bookFromVector = getBookByIndex(v1, i);      
        bookFromVector.printBookInfo();
    }
//------------------------------------------------------------------------  



// ------------------------------------ 2 ---------------------------------
    std::vector<Book> v2_1;
    std::copy(v1.end() - 200, v1.end(), std::back_inserter(v2_1));

    std::vector<Book> v2_2;
    int b = distrib3(gen);
    int e = distrib4(gen);
    std::cout<<"b: "<< b << " e: "<< e << std::endl;
    std::copy(v1.begin() + b, v1.begin() + e, std::back_inserter(v2_2));
//-----------------------------------------------------------------------

//------------------------------------ 3 -----------------------------------
    std::uniform_int_distribution<> distrib5(20, 50);
    int n_1 = distrib5(gen);
    std::cout << "Top " << n_1 << " books sorted by max year:" << std::endl;
    std::partial_sort(v1.begin(), v1.begin() + n_1, v1.end(), compareByYearMax);

    std::list<Book> list1(v1.begin(), v1.begin() + n_1);

    std::cout << "Books in the list sorted by max year:" << std::endl;
    for (const auto& book : list1) {
        book.printBookInfo();
    }
//--------------------------------------------------------------------------

//------------------------------------ 4 -----------------------------------
    int n_2 = distrib5(gen);
    std::cout << "Top " << n_2 << " books sorted by min year:" << std::endl;
    std::partial_sort(v2_1.begin(), v2_1.begin() + n_2, v2_1.end(), compareByYearMin);

    std::list<Book> list2(v2_1.begin(), v2_1.begin() + n_2);

    std::cout << "Books in the list sorted by min year:" << std::endl;
    for (const auto& book : list2) {
        book.printBookInfo();
    }
//--------------------------------------------------------------------------

//------------------------------------ 5 -----------------------------------
    std::cout << "Size of v1: " << v1.size() << std::endl;
    std::cout << "Size of v2_1: " << v2_1.size() << std::endl;

    v1.erase(v1.begin(), v1.begin() + n_1);
    v2_1.erase(v2_1.begin(), v2_1.begin() + n_2);

    std::cout << "New size of v1: " << v1.size() << std::endl;
    std::cout << "New size of v2_1: " << v2_1.size() << std::endl;
    
//-------------------------------------------------------------------------- 

//------------------------------------ 6 -----------------------------------
    double averageYear = std::accumulate(
            list1.begin(), list1.end(), 0, sumBookYears
        ) / static_cast<double>(list1.size());
    
    std::cout << "Average year list1: " << averageYear <<std::endl;

    std::list<Book> filteredBooks;
    std::copy_if(list1.begin(), list1.end(), std::back_inserter(filteredBooks),
    [&averageYear](const Book& book) {
        return isYearGreaterThanAverage(book, averageYear);
    });

    std::cout << "Books with a year more than average:" << std::endl;
    for (const auto& book : filteredBooks) {
        book.printBookInfo();
    }      
//-------------------------------------------------------------------------- 

//------------------------------------ 7 -----------------------------------
    list2.erase(std::remove_if(list2.begin(), list2.end(), isOddYear), list2.end());

    std::cout << "Items in list2 after removing odd years:" << std::endl;
    for (const auto& book : list2) {
        book.printBookInfo();
    }
//-------------------------------------------------------------------------- 

//------------------------------------ 8 -----------------------------------
    std::vector<Book> v3;
    std::vector<Book> sorted_v1 = v1;
    std::vector<Book> sorted_v2 = v2_1;
    
    std::sort(sorted_v1.begin(), sorted_v1.end(), compareByYearMin);
    std::sort(sorted_v2.begin(), sorted_v2.end(), compareByYearMin);

    std::set_intersection(sorted_v1.begin(), sorted_v1.end(),
                          sorted_v2.begin(), sorted_v2.end(),
                          std::back_inserter(v3), compareByYearMin);


//-------------------------------------------------------------------------- 

//------------------------------------ 9 -----------------------------------
    std::cout << "list1:" << list1.size()<< std::endl;
    std::cout << "list2:" << list2.size()<< std::endl;

    int difference;

    if(list1.size() > list2.size()){
        difference = list1.size() - list2.size();
        list1.erase(list1.begin(), std::next(list1.begin(),difference));
    }
    else{
        difference = list2.size() - list1.size();
        list2.erase(list2.begin(), std::next(list2.begin(),difference));
    }

    std::cout << "new list1:" << list1.size()<< std::endl;
    std::cout << "new list2:" << list2.size()<< std::endl;

     // Используем std::transform для создания list3
    std::list<std::pair<Book, Book>> list3;

    // Преобразуем элементы list1 и list2 в пары и помещаем их в list3
    std::transform(list1.begin(), list1.end(), list2.begin(), std::back_inserter(list3),
                   [](const Book& book1, const Book& book2) {
                       return std::make_pair(book1, book2);
                   });

    std::cout << "Pairs in list3: " << list3.size()<<std::endl;
//-------------------------------------------------------------------------- 

//------------------------------------ 10 -----------------------------------
    size_t minSize = std::min(v1.size(), v2_1.size());
    std::cout << "new v1:" << v1.size()<< std::endl;
    std::cout << "new v2_1:" << v2_1.size()<< std::endl;
    std::cout << "minSize = " << minSize << std::endl;

    std::vector<std::pair<Book, Book>> v3_1;
    std::transform(v1.begin(), v1.begin() + minSize, v2_1.begin(), std::back_inserter(v3_1), [](const Book& book1, const Book& book2) {
                       return std::make_pair(book1, book2);
                   });

    std::cout << "Pairs in v3_1: " << v3_1.size()<< std::endl;
//-------------------------------------------------------------------------- 

}
