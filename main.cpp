#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

void print_header()
{
    std::cout << setw(3) << "  " << setw(10) << left << "Title" <<
    setw(10) << "Author" <<
    setw(10) << "Year" <<
    setw(10) << "Category" <<
    setw(10) << "Availability" << endl;
}


class Book
{
public:
    Book(const string& title_par, const string& author_par, const int& year_par, const string& category_par, bool availability): title(title_par), author(author_par), year(year_par), category(category_par), is_available(availability) {};
    
    string get_title()const{ return title;}
    string get_author()const{ return author;}
    int get_year()const{ return year;}
    string get_category()const{ return category;}
    bool get_availability()const{ return is_available;}
    
    void rent_it(){ is_available=0;}
    void return_it(){ is_available=1;}
    
private:
    string title;
    string author;
    int year;
    string category;
    bool is_available;
    
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
            string is_available_str;
            bool is_available;
            
            getline(ss, title, ',');
            getline(ss, author, ',');
            getline(ss, yearStr, ',');
            getline(ss, category, ',');
            getline(ss, is_available_str, ',');
            year = stoi(yearStr);
            is_available = stoi(is_available_str);
            books.emplace_back(title, author, year, category, is_available);
            
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
            book.get_category() << "," <<
            book.get_availability() << "\n";
        }
        
    }
    
};

/*------------------------------*/
bool sort_func(const Book& b1, const Book& b2)
{
    return b1.get_year() < b2.get_year();
}



class Library
{
public:
    
    /* ----- disiplay/add/remove books ----- */
    void display_books()
    {
        print_header();
        
        int num = 1;
        for(const Book& book: books)
        {
            
            cout << num <<  ". " <<
            setw(10) << left << book.get_title() <<
            setw(10) << left << book.get_author() <<
            setw(10) << left << book.get_year() <<
            setw(10) << left << book.get_category() <<
            setw(10) << left << book.get_availability() << std::endl;
            
            num++;
        }
    }
    
    void add_book(const Book& book)
    {
        books.push_back(book);
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
    
    /* ----- rent/return stuff ----- */
    
    void rent_book()
    {
        int index;
        cout << "Here are the books that you can rent. Provide the index of the book to rent: " <<endl;
        vector<int> books_to_rent = display_available_books();
        cin >> index;
        
        auto it = std::find(books_to_rent.begin(), books_to_rent.end(), index);
        if (it != books_to_rent.end())
        {
            books[index-1].rent_it();
        } else
        {
            cout << "Wrong number" <<endl;
        }
    }
    
    void return_book()
    {
        int index;
        cout << "Which of the books do you want to return: " <<endl;
        vector<int> books_to_return = display_rented_books();
        cin >> index;
        
        auto it = std::find(books_to_return.begin(), books_to_return.end(), index);
        if (it != books_to_return.end())
        {
            books[index-1].return_it();
        } else
        {
            cout << "Wrong number" <<endl;
        }
        
    }
    
    /* ----- searching stuff ----- */
    
    vector<int> display_available_books()
    {
        vector<int> available_books;
        int num = 1;
        print_header();
        for(const Book& book: books)
        {
            if(book.get_availability()==1)
            {
                cout << num <<  ". " <<
                setw(10) << left << book.get_title() <<
                setw(10) << left << book.get_author() <<
                setw(10) << left << book.get_year() <<
                setw(10) << left << book.get_category() <<
                setw(10) << left << book.get_availability() << std::endl;
                available_books.push_back(num);
            }
            
            num++;
        }
        return available_books;
    }
    
    vector<int> display_rented_books()
    {
        vector<int> rented_books;
        int num = 1;
        cout << "Here are the available books: " <<endl;
        print_header();
        for(const Book& book: books)
        {
            if(book.get_availability()==0)
            {
                cout << num <<  ". " <<
                setw(10) << left << book.get_title() <<
                setw(10) << left << book.get_author() <<
                setw(10) << left << book.get_year() <<
                setw(10) << left << book.get_category() <<
                setw(10) << left << book.get_availability() << std::endl;
                rented_books.push_back(num);
            }
            
            num++;
        }
        return rented_books;
    }
    
    void search_by_author()
    {
        bool flag = false;
        string author;
        cout << "What author are you looking for? " ;
        cin>> author;
    
        cout << "Books written by " << author << ": " << endl;
        print_header();
        
        int n = 1;
        for(const Book& book : books)
        {
            if(book.get_author()==author)
            {
                cout  << n << ". " <<
                setw(10) << left << book.get_title() <<
                setw(10) << left << book.get_author() <<
                setw(10) << left << book.get_year() <<
                setw(10) << left << book.get_category() <<
                setw(10) << left << book.get_availability() << std::endl;
                
                n++;
                flag=true;
            }
        }
        if(flag==false)
        {
            cout << "No books written by " << author << endl;
        }
    }
    
    void search_by_category()
    {
        bool flag = false;
        string category;
        cout << "What category are you interested in? " ;
        cin >> category;
    
        cout << "Books in the category " << category << ": " << endl;
        print_header();
        
        int n=1;
        for(const Book& book : books)
        {
            if(book.get_category()==category)
            {
                cout  << n << ". " <<
                setw(10) << left << book.get_title() <<
                setw(10) << left << book.get_author() <<
                setw(10) << left << book.get_year() <<
                setw(10) << left << book.get_category() <<
                setw(10) << left << book.get_availability() << std::endl;
                
                n++;
                flag=true;
            }
        }
        if(flag==false)
        {
            cout << "No books written in the category " << category << endl;
        }
    }
    
    void sort_by_year()
    {
        vector<Book> books2;
        books2 = books;
        sort(books2.begin(), books2.end(), sort_func);
        
        cout << "Books sorted by year. \n";
        print_header();
        
        int num=1;
        for(const Book& book: books2)
        {
            cout << num <<  ". "  <<
            setw(10) << left << book.get_title() <<
            setw(10) << left << book.get_author() <<
            setw(10) << left << book.get_year() <<
            setw(10) << left << book.get_category() <<
            setw(10) << left << book.get_availability() << std::endl;
            num++;
        }
        
    }
    
    /* ----- loading/saving stuff ----- */
    
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
    
//    library.add_book(Book("title1", "author1", 21, "fiction", 1));
//    library.add_book(Book("title2", "author2", 23, "sport", 1));
//    library.add_book(Book("title3", "author2", 10, "sport", 1));
//    library.add_book(Book("title4", "author2", 20, "science", 1));
    
    library.display_books();


    
    library.search_by_author();
    library.search_by_category();
    


    
    library.save_books("books.csv");
    
    return 0;
}
