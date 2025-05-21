#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <limits>

using namespace std;

#define COLOR_RESET   "\033[0m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_CYAN    "\033[36m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_BOLD    "\033[1m"
#define COLOR_RED     "\033[31m"

class Book
{
public:
    string title;
    string author;
    string isbn;
    bool isBorrowed;

    Book(string title, string author, string isbn, bool isBorrowed = false)
    {
        this->title = title;
        this->author = author;
        this->isbn = isbn;
        this->isBorrowed = isBorrowed;
    }

    void displayDetails()
    {
        cout << COLOR_CYAN << "Title: " << COLOR_RESET << title << endl
             << COLOR_CYAN << "Author: " << COLOR_RESET << author << endl
             << COLOR_CYAN << "ISBN: " << COLOR_RESET << isbn << endl
             << COLOR_CYAN << "Borrowed: " << COLOR_RESET << boolalpha << isBorrowed << endl;
    }

    void borrowBook()
    {
        isBorrowed = true;
    }

    void returnBook()
    {
        isBorrowed = false;
    }
};

class Library
{
public:
    vector<Book> books;

    void addBook(Book newBook)
    {
        books.push_back(newBook);
    }

    Book *findBook(const string &searchISBN)
    {
        for (auto &book : books)
        {
            if (book.isbn == searchISBN)
            {
                return &book;
            }
        }
        return nullptr;
    }

    void borrowBook(string isbn)
    {
        Book *book_ptr = findBook(isbn);
        if (book_ptr == nullptr)
        {
            cout << COLOR_RED << "Book not found." << COLOR_RESET << endl;
            return;
        }

        if (book_ptr->isBorrowed)
        {
            cout << COLOR_YELLOW << "Book not available" << COLOR_RESET << endl;
        }
        else
        {
            book_ptr->borrowBook();
            cout << COLOR_GREEN << "Book borrowed successfully." << COLOR_RESET << endl;
        }
    }

    void returnBook(string isbn)
    {
        Book *book_ptr = findBook(isbn);
        if (book_ptr == nullptr)
        {
            cout << COLOR_RED << "Book not found." << COLOR_RESET << endl;
            return;
        }

        if (book_ptr->isBorrowed)
        {
            book_ptr->returnBook();
            cout << COLOR_GREEN << "Book returned successfully." << COLOR_RESET << endl;
        }
        else
        {
            cout << COLOR_YELLOW << "Book not borrowed." << COLOR_RESET << endl;
        }
    }

    void listAllBooks()
    {
        if (books.empty()) {
            cout << COLOR_YELLOW << "No books in the library." << COLOR_RESET << endl;
            return;
        }
        cout << COLOR_BOLD << COLOR_MAGENTA << "=== All Books ===" << COLOR_RESET << endl;
        for (auto &book : books)
        {
            book.displayDetails();
            cout << "------------------------" << endl;
        }
    }

    void listAvailableBooks()
    {
        bool found = false;
        cout << COLOR_BOLD << COLOR_MAGENTA << "=== Available Books ===" << COLOR_RESET << endl;
        for (auto &book : books)
        {
            if (book.isBorrowed == false)
            {
                book.displayDetails();
                cout << "------------------------" << endl;
                found = true;
            }
        }
        if (!found) {
            cout << COLOR_YELLOW << "No available books." << COLOR_RESET << endl;
        }
    }
};

void clearScreen() {
    cout << "\033[2J\033[1;1H";
}

void printBanner() {
    cout << COLOR_BOLD << COLOR_GREEN;
    cout << "==========================================" << endl;
    cout << "         LIBRARY MANAGER SYSTEM           " << endl;
    cout << "==========================================" << COLOR_RESET << endl;
}

int main() {
    Library library;
    int choice;
    string title, author, isbn;

    while (true)
    {
        clearScreen();
        printBanner();

        cout << COLOR_BOLD << "\nACTIONS:\n" << COLOR_RESET
             << COLOR_CYAN << "1." << COLOR_RESET << "\tAdd new book\n"
             << COLOR_CYAN << "2." << COLOR_RESET << "\tBorrow a book\n"
             << COLOR_CYAN << "3." << COLOR_RESET << "\tReturn a book\n"
             << COLOR_CYAN << "4." << COLOR_RESET << "\tList all books\n"
             << COLOR_CYAN << "5." << COLOR_RESET << "\tList all available books\n"
             << COLOR_CYAN << "6." << COLOR_RESET << "\tExit\n"
             << COLOR_BOLD << "Choice:\t" << COLOR_RESET;
        if (!(cin >> choice)) {
            cin.clear();
            cout << COLOR_RED << "Invalid input." << COLOR_RESET << endl;
            Sleep(1200);
            continue;
        }
        cin.ignore();

        clearScreen();
        printBanner();

        switch (choice)
        {
        case 1:
            cout << COLOR_BOLD << "\nEnter title: " << COLOR_RESET;
            getline(cin, title);
            cout << COLOR_BOLD << "Enter author: " << COLOR_RESET;
            getline(cin, author);
            cout << COLOR_BOLD << "Enter ISBN: " << COLOR_RESET;
            getline(cin, isbn);

            library.addBook(Book(title, author, isbn));
            cout << COLOR_GREEN << "Book added successfully.\n" << COLOR_RESET;
            break;
        case 2:
            cout << COLOR_BOLD << "\nEnter ISBN: " << COLOR_RESET;
            getline(cin, isbn);
            library.borrowBook(isbn);
            break;
        case 3:
            cout << COLOR_BOLD << "\nEnter ISBN: " << COLOR_RESET;
            getline(cin, isbn);
            library.returnBook(isbn);
            break;
        case 4:
            library.listAllBooks();
            break;
        case 5:
            library.listAvailableBooks();
            break;
        case 6:
            cout << COLOR_BOLD << COLOR_GREEN << "\nThank you for using Library Manager! Goodbye!\n" << COLOR_RESET;
            Sleep(1200);
            clearScreen();
            exit(0);
            break;
        default:
            cout << COLOR_RED << "Invalid input." << COLOR_RESET << endl;
            break;
        }

        cout << COLOR_YELLOW << "\nPress Enter to continue..." << COLOR_RESET;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return 0;
}