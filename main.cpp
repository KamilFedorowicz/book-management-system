#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "book.h"
#include "library.h"







/*------------------------------*/


void intro()
{
    cout << "1. Add a book." <<endl;
    cout << "2. Remove a book." <<endl;
    cout << "3. Display a book list." <<endl;
    cout << "4. Rent a book." <<endl;
    cout << "5. Return a book." <<endl;
    cout << "6. Search by author." <<endl;
    cout << "7. Search by cathegory." <<endl;
    cout << "8. Sort by year." <<endl;
    cout << "9. Exit and save books." <<endl;
}


int main(int argc, const char * argv[]) {
    
    Library library;
    library.load_books("books.csv");
    
    cout << "\nWelcome to the book management program!" << endl;

    char ch;
    
    do {
    
        cout << "What do you want to do?\n ";
        intro();
        
        cin >> ch;
        
        switch(ch)
        {
            case '1':
                library.add_book();
                break;
            case '2':
                library.delete_book();
                break;
            case '3':
                library.display_books();
                break;
            case '4':
                library.rent_book();
                break;
            case '5':
                library.return_book();
                break;
            case '6':
                library.search_by_author();
                break;
            case '7':
                library.search_by_category();
                break;
            case '8':
                library.sort_by_year();
                break;
        }
            
        
    } while (ch!='9');
    
    
    library.save_books("books.csv");
    
    return 0;
}
