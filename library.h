//
//  library.h
//  book_management_system
//
//  Created by Kamil Fedorowicz on 27/06/2024.
//

#ifndef library_h
#define library_h
#include "book.h"
#include "CSVHandler.h"

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
            
            cout << setw(2) << num <<  ". " <<
            setw(width_t) << left << book.get_title() <<
            setw(width_a) << left << book.get_author() <<
            setw(width_y) << left << book.get_year() <<
            setw(width) << left << book.get_category() <<
            setw(width) << left << book.get_availability() << std::endl;
            
            num++;
        }
        cout << "\n";
    }
    
    void add_book()
    {
        string title, author, category;
        int year;
        bool availability;
        
        
        cout << "Provide the book title: ";
        std::getline(std::cin >> std::ws, title);
        cout << "Provide the book author: ";
        std::getline(std::cin >> std::ws, author);
        cout << "Provide the book category: ";
        std::getline(std::cin >> std::ws, category);
        cout << "Provide the year that the book was published: ";
        cin >> year;
        
        // the availability element is 1, meaning that when we add the book it is already available in the library
        books.push_back(Book(title, author, year, category, 1));
        cout << "Book added to the library!" << endl;
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
            cout << "Book rented!";
        } else
        {
            cout << "Wrong number" <<endl;
        }
        cout << "\n \n";
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
            cout << "Book returned";
        } else
        {
            cout << "Wrong number" <<endl;
        }
        cout << "\n \n";
        
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
                cout << setw(2) << num <<  ". " <<
                setw(width_t) << left << book.get_title() <<
                setw(width_a) << left << book.get_author() <<
                setw(width_y) << left << book.get_year() <<
                setw(width) << left << book.get_category() <<
                setw(width) << left << book.get_availability() << std::endl;
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
                setw(width_t) << left << book.get_title() <<
                setw(width_a) << left << book.get_author() <<
                setw(width_y) << left << book.get_year() <<
                setw(width) << left << book.get_category() <<
                setw(width) << left << book.get_availability() << std::endl;
                
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
        getline(std::cin >> std::ws, author);
    
        cout << "Books written by " << author << ": " << endl;
        print_header();
        
        int num = 1;
        for(const Book& book : books)
        {
            if(book.get_author()==author)
            {
                cout << setw(2) << num <<  ". " <<
                setw(width_t) << left << book.get_title() <<
                setw(width_a) << left << book.get_author() <<
                setw(width_y) << left << book.get_year() <<
                setw(width) << left << book.get_category() <<
                setw(width) << left << book.get_availability() << std::endl;
                
                num++;
                flag=true;
            }
        }
        if(flag==false)
        {
            cout << "No books written by " << author << endl;
            
        }
        cout << "\n";
    }
    
    void search_by_category()
    {
        bool flag = false;
        string category;
        cout << "What category are you interested in? " ;
        cin >> category;
    
        cout << "Books in the category " << category << ": " << endl;
        print_header();
        
        int num=1;
        for(const Book& book : books)
        {
            if(book.get_category()==category)
            {
                cout << setw(2) << num <<  ". " <<
                setw(width_t) << left << book.get_title() <<
                setw(width_a) << left << book.get_author() <<
                setw(width_y) << left << book.get_year() <<
                setw(width) << left << book.get_category() <<
                setw(width) << left << book.get_availability() << std::endl;
                
                num++;
                flag=true;
            }
        }
        if(flag==false)
        {
            cout << "No books written in the category " << category << endl;
        }
        cout << "\n";
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
            setw(width_t) << left << book.get_title() <<
            setw(width_a) << left << book.get_author() <<
            setw(width_y) << left << book.get_year() <<
            setw(width) << left << book.get_category() <<
            setw(width) << left << book.get_availability() << std::endl;
            num++;
        }
        cout << "\n\n";
        
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


#endif /* library_h */
