#ifndef book_h
#define book_h

using namespace std;
extern const int width_t=45;
extern const int width_a=25;
extern const int width_y=8;
extern const int width=15;

void print_header()
{
    std::cout << setw(4) << "  " <<
    setw(width_t) << left << "Title" <<
    setw(width_a) << "Author" <<
    setw(width_y) << "Year" <<
    setw(width) << "Category" <<
    setw(width) << "Availability" << endl;
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

#endif /* book_h */
