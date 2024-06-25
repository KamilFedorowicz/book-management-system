#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class Book
{
public:
    Book(const string& title_par, const string& author_par, const int& year_par): title(title_par), author(author_par), year(year_par){};
    
    string get_title()const{ return title;}
    string get_author()const{ return author;}
    int get_year()const{ return year;}
    
private:
    string title;
    string author;
    int year;
    
};

/*-----------------------------------*/

class CSVHandler
{
public:
    
    static vector<Book> load(const string& filename)
    {
        vector<Book> books;
        ifstream file(filename);
        if(!file.is_open()) return books;
        
        string line;
        
        
        
        while(getline(file, line))
        {
            stringstream ss(line);
            string title;
            string author;
            string yearStr;
            int year;
            
            getline(ss, title, ',');
            getline(ss, author, ',');
            getline(ss, yearStr, ',');
            year = stoi(yearStr);
            books.emplace_back(title, author, year);
            
        }
        
        return books;
    }
    
    static void save(const string& filename, const vector<Book>& books)
    {
        ofstream file(filename);
        for(const auto& book: books)
        {
            file << book.get_title() << "," <<
            book.get_author() << "," <<
            book.get_year() << "\n";
        }
        
    }
    
};

/*------------------------------*/

class Library
{
public:
    void add_book(const Book& book)
    {
        books.push_back(book);
    }
    
    void display_books()
    {
        for(const Book& book: books)
        {
            std::cout << "title: " << book.get_title() <<
            ", author: " << book.get_author() <<
            ", year: " << book.get_year() << std::endl;
        }
    }
    
    void load_books(const string& filename)
    {
        books = CSVHandler::load(filename);
    }
    
    void save_books(const string& filename)
    {
        CSVHandler::save(filename, books);
    }
    
private:
    vector<Book> books;
};




int main(int argc, const char * argv[]) {
    
    Library library;
    library.load_books("books.csv");
    
    library.add_book(Book("title1", "author1", 21));
    library.add_book(Book("title2", "author2", 23));

    
    library.save_books("books.csv");
    
    return 0;
}
