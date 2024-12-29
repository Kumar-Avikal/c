#include <iostream>
#include <unordered_map>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;
class ISBNGenerator
{
private:
    static int count;

public:
    static string generateISBN()
    {
        count++;
        srand(time(nullptr) + count);
        int randomPart = rand() % 1000;
        return "ISBN-" + to_string(count) + "-" + to_string(randomPart);
    }
};

int ISBNGenerator::count = 0;

class Book
{
private:
    string title;
    string author;
    string isbn;
    bool isAvailable;

public:
    Book() {};
    Book(string title, string author)
    {
        this->title = title;
        this->author = author;
        isbn = ISBNGenerator::generateISBN();
        isAvailable = true;
    };

    string getISBN() const { return isbn; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    bool getAvailability() const { return isAvailable; }

    void changeAvailability()
    {
        isAvailable = !isAvailable;
    }

    void display() const
    {
        cout << "Title: " << title << ", Author: " << author
             << ", ISBN: " << isbn << ", Available: " << (isAvailable ? "Yes" : "No") << endl;
    }
};

class Library
{
private:
    unordered_map<string, Book> lib;

public:
    void addBook()
    {
        string title, author;
        cout << "Please enter the Book title: ";
        cin >> title;
        cout << "Please enter the Book author: ";
        cin >> author;
        Book book(title, author);
        lib[book.getISBN()] = book;
        cout << "Book added successfully.\n";
    }

    void searchBook()
    {
        string search;
        cout << "Enter search string: ";
        cin >> search;

        int matchCount = 0;
        for (const auto &entry : lib)
        {
            const Book &book = entry.second;
            if (search == book.getAuthor() || search == book.getTitle() || search == book.getISBN())
            {
                book.display();
                matchCount++;
            }
        }

        cout << "Total search results: " << matchCount << "\n";
    }

    void displayAll()
    {
        for (const auto &entry : lib)
        {
            entry.second.display();
        }
    }

    void borrow()
    {
        string isbn;
        cout << "Enter ISBN to borrow book: ";
        cin >> isbn;

        auto it = lib.find(isbn);
        if (it == lib.end())
        {
            cout << "Book not in stock.\n";
        }
        else
        {
            Book &book = it->second;
            if (book.getAvailability())
            {
                book.changeAvailability();
                cout << "Thank you for borrowing.\n";
            }
            else
            {
                cout << "Book already borrowed.\n";
                book.display();
            }
        }
    }

    void returnBook()
    {
        string isbn;
        cout << "Please enter the ISBN to return the book: ";
        cin >> isbn;

        auto it = lib.find(isbn);
        if (it == lib.end())
        {
            cout << "Invalid ISBN. Book not found in the library.\n";
        }
        else
        {
            Book &book = it->second;
            book.changeAvailability();
            cout << "Thank you for returning the book.\n";
            book.display();
        }
    }
};

int main()
{
    Library library;
    int option;
    do
    {
        cout << "\nLibrary Menu:\n";
        cout << "1. Add a Book\n";
        cout << "2. Search for a Book\n";
        cout << "3. Display All Books\n";
        cout << "4. Borrow a Book\n";
        cout << "5. Return a Book\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> option;

        switch (option)
        {
        case 1:
            library.addBook();
            break;
        case 2:
            library.searchBook();
            break;
        case 3:
            library.displayAll();
            break;
        case 4:
            library.borrow();
            break;
        case 5:
            library.returnBook();
            break;
        case 0:
            cout << "Exiting the Library System. Goodbye!\n";
            break;
        default:
            cout << "Invalid option. Please try again.\n";
        }
    } while (option != 0);

    return 0;
}
