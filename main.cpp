#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class Book
{
public:
    Book(const string& title_par, const string& author_par, const int& year_par, const string& category_par): title(title_par), author(author_par), year(year_par), category(category_par) {};
    
    string get_title()const{ return title;}
    string get_author()const{ return author;}
    int get_year()const{ return year;}
    string get_category()const{ return category;}
    
private:
    string title;
    string author;
    int year;
    string category;
    
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
            string category;
            
            getline(ss, title, ',');
            getline(ss, author, ',');
            getline(ss, yearStr, ',');
            getline(ss, category, ',');
            year = stoi(yearStr);
            books.emplace_back(title, author, year, category);
            
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
            book.get_year() << "," <<
            book.get_category() << "\n";
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
        std::cout << setw(3) << "  " << setw(10) << left << "Title" <<
        setw(10) << "Author" <<
        setw(10) << "Year" <<
        setw(10) << "Category" << endl;
        
        int num = 1;
        for(const Book& book: books)
        {
            
            cout << num <<  ". " <<
            setw(10) << left << book.get_title() <<
            setw(10) << book.get_author() <<
            setw(10) << book.get_year() <<
            setw(10) << book.get_category() << std::endl;
            
            num++;
        }
    }
    
    void search_by_author(const string& author)
    {
        bool flag = false;
    
        cout << "Books written by " << author << ": " << endl;
        for(const Book& book : books)
        {
            if(book.get_author()==author)
            {
                std::cout  << setw(10) << left << book.get_title() <<
                setw(10) << book.get_author() <<
                setw(10) << book.get_year() <<
                setw(10) << book.get_category() << std::endl;
                
                flag=true;
            }
        }
        if(flag==false)
        {
            cout << "No books written by " << author << endl;
        }
    }
    
    void search_by_category(const string& category)
    {
        bool flag = false;
    
        cout << "Books in the category " << category << ": " << endl;
        for(const Book& book : books)
        {
            if(book.get_category()==category)
            {
                std::cout  << setw(10) << left << book.get_title() <<
                setw(10) << book.get_author() <<
                setw(10) << book.get_year() <<
                setw(10) << book.get_category() << std::endl;
                
                flag=true;
            }
        }
        if(flag==false)
        {
            cout << "No books written in the category " << category << endl;
        }
    }
    
    void delete_book()
    {
        int index;
        cout << "Provide the index of the book to delete: ";
        cin >> index;
        if(index>0 && index<=books.size())
        {
            books.erase(books.begin()+index-1);
        }
        else
        {
            cout << "Index out of range" <<endl;
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
    
    library.add_book(Book("title1", "author1", 21, "fiction"));
    library.add_book(Book("title2", "author2", 23, "sport"));
    library.add_book(Book("title3", "author2", 10, "sport"));
    library.add_book(Book("title4", "author2", 20, "science"));
    
    library.display_books();
    library.delete_book();
    library.display_books();

    
    library.save_books("books.csv");
    
    return 0;
}
