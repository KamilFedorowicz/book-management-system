//
//  CSVHandler.h
//  book_management_system
//
//  Created by Kamil Fedorowicz on 27/06/2024.
//

#ifndef CSVHandler_h
#define CSVHandler_h



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


#endif /* CSVHandler_h */
