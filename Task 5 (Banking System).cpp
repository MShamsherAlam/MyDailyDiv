#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>

using namespace std;

struct Book {
    string title;
    string author;
    string ISBN;
    bool isAvailable;
};

struct Borrower {
    string name;
    string borrowedBookISBN;
    time_t checkoutDate;
};

class Library {
public:
    void addBook(const string& title, const string& author, const string& ISBN) {
        books.push_back({title, author, ISBN, true});
    }

    void searchBook(const string& searchTerm) const {
        bool found = false;
        for (const auto& book : books) {
            if (book.title == searchTerm || book.author == searchTerm || book.ISBN == searchTerm) {
                cout << "Title: " << book.title << ", Author: " << book.author << ", ISBN: " << book.ISBN;
                cout << (book.isAvailable ? " [Available]" : " [Checked Out]") << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No books found." << endl;
        }
    }

    void checkoutBook(const string& ISBN, const string& borrowerName) {
        for (auto& book : books) {
            if (book.ISBN == ISBN && book.isAvailable) {
                book.isAvailable = false;
                borrowers.push_back({borrowerName, ISBN, time(nullptr)});
                cout << "Book checked out successfully!" << endl;
                return;
            }
        }
        cout << "Book not available or does not exist." << endl;
    }

    void returnBook(const string& ISBN) {
        for (auto& book : books) {
            if (book.ISBN == ISBN) {
                book.isAvailable = true;
                // Find and remove the borrower
                for (auto it = borrowers.begin(); it != borrowers.end(); ++it) {
                    if (it->borrowedBookISBN == ISBN) {
                        borrowers.erase(it);
                        cout << "Book returned successfully!" << endl;
                        return;
                    }
                }
                cout << "Borrower record not found." << endl;
                return;
            }
        }
        cout << "Book does not exist." << endl;
    }

    void calculateFine(const string& borrowerName) const {
        const int finePerDay = 1; // Fine in dollars
        const int maxDays = 30; // Max days allowed before fine is charged
        time_t currentTime = time(nullptr);

        bool found = false;
        for (const auto& borrower : borrowers) {
            if (borrower.name == borrowerName) {
                time_t checkoutTime = borrower.checkoutDate;
                double daysOverdue = difftime(currentTime, checkoutTime) / (60 * 60 * 24);
                if (daysOverdue > maxDays) {
                    int fine = (daysOverdue - maxDays) * finePerDay;
                    cout << "Total fine for " << borrowerName << ": $" << fine << endl;
                } else {
                    cout << "No fine for " << borrowerName << "." << endl;
                }
                found = true;
                return;
            }
        }
        if (!found) {
            cout << "Borrower not found." << endl;
        }
    }

    void displayMenu() {
        while (true) {
            cout << "\nLibrary Management System" << endl;
            cout << "1. Add Book" << endl;
            cout << "2. Search Book" << endl;
            cout << "3. Checkout Book" << endl;
            cout << "4. Return Book" << endl;
            cout << "5. Calculate Fine" << endl;
            cout << "6. Exit" << endl;
            cout << "Enter your choice: ";

            int choice;
            cin >> choice;

            string input;
            switch (choice) {
                case 1:
                    {
                        string title, author, ISBN;
                        cout << "Enter book title: ";
                        cin.ignore();
                        getline(cin, title);
                        cout << "Enter book author: ";
                        getline(cin, author);
                        cout << "Enter book ISBN: ";
                        getline(cin, ISBN);
                        addBook(title, author, ISBN);
                    }
                    break;
                case 2:
                    {
                        cout << "Enter search term (title, author, or ISBN): ";
                        cin.ignore();
                        getline(cin, input);
                        searchBook(input);
                    }
                    break;
                case 3:
                    {
                        string ISBN, borrowerName;
                        cout << "Enter book ISBN: ";
                        cin.ignore();
                        getline(cin, ISBN);
                        cout << "Enter borrower's name: ";
                        getline(cin, borrowerName);
                        checkoutBook(ISBN, borrowerName);
                    }
                    break;
                case 4:
                    {
                        cout << "Enter book ISBN: ";
                        cin.ignore();
                        getline(cin, input);
                        returnBook(input);
                    }
                    break;
                case 5:
                    {
                        string borrowerName;
                        cout << "Enter borrower's name: ";
                        cin.ignore();
                        getline(cin, borrowerName);
                        calculateFine(borrowerName);
                    }
                    break;
                case 6:
                    cout << "Exiting the Library Management System. Goodbye!" << endl;
                    return;
                default:
                    cout << "Invalid choice! Please try again." << endl;
            }
        }
    }

private:
    vector<Book> books;
    vector<Borrower> borrowers;
};

int main() {
    Library library;
    library.displayMenu();
    return 0;
}

