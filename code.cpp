#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;

class Book {
private:
    int bookID;
    char title[50];
    char author[50];
    bool issued;

public:
    void addBook() {
        cout << "\nEnter Book ID: ";
        cin >> bookID;

        cin.ignore();

        cout << "Enter Book Title: ";
        cin.getline(title, 50);

        cout << "Enter Author Name: ";
        cin.getline(author, 50);

        issued = false;
    }

    void displayBook() {
        cout << left << setw(10) << bookID
             << setw(25) << title
             << setw(25) << author
             << setw(10) << (issued ? "Issued" : "Available")
             << endl;
    }

    int getBookID() {
        return bookID;
    }

    char* getTitle() {
        return title;
    }

    char* getAuthor() {
        return author;
    }

    bool isIssued() {
        return issued;
    }

    void issueBook() {
        if (!issued) {
            issued = true;
            cout << "\nBook Issued Successfully!\n";
        } else {
            cout << "\nBook Already Issued!\n";
        }
    }

    void returnBook() {
        if (issued) {
            issued = false;
            cout << "\nBook Returned Successfully!\n";
        } else {
            cout << "\nBook was not issued!\n";
        }
    }
};

// Add Book
void addNewBook() {
    Book b;

    ofstream file("library.dat", ios::binary | ios::app);

    b.addBook();

    file.write((char*)&b, sizeof(b));

    file.close();

    cout << "\nBook Added Successfully!\n";
}

// Display All Books
void displayBooks() {
    Book b;

    ifstream file("library.dat", ios::binary);

    cout << "\n================ Library Books ================\n";

    cout << left << setw(10) << "Book ID"
         << setw(25) << "Title"
         << setw(25) << "Author"
         << setw(10) << "Status"
         << endl;

    while (file.read((char*)&b, sizeof(b))) {
        b.displayBook();
    }

    file.close();
}

// Search by Title
void searchByTitle() {
    Book b;
    char searchTitle[50];
    bool found = false;

    ifstream file("library.dat", ios::binary);

    cin.ignore();

    cout << "\nEnter Book Title to Search: ";
    cin.getline(searchTitle, 50);

    while (file.read((char*)&b, sizeof(b))) {
        if (strcmp(b.getTitle(), searchTitle) == 0) {
            cout << "\nBook Found:\n";
            b.displayBook();
            found = true;
        }
    }

    if (!found)
        cout << "\nBook Not Found!\n";

    file.close();
}

// Search by Author
void searchByAuthor() {
    Book b;
    char searchAuthor[50];
    bool found = false;

    ifstream file("library.dat", ios::binary);

    cin.ignore();

    cout << "\nEnter Author Name to Search: ";
    cin.getline(searchAuthor, 50);

    while (file.read((char*)&b, sizeof(b))) {
        if (strcmp(b.getAuthor(), searchAuthor) == 0) {
            cout << "\nBook Found:\n";
            b.displayBook();
            found = true;
        }
    }

    if (!found)
        cout << "\nNo Books Found for this Author!\n";

    file.close();
}

// Issue Book
void issueBook() {
    Book b;
    int id;
    bool found = false;

    fstream file("library.dat", ios::binary | ios::in | ios::out);

    cout << "\nEnter Book ID to Issue: ";
    cin >> id;

    while (file.read((char*)&b, sizeof(b))) {
        if (b.getBookID() == id) {
            b.issueBook();

            int pos = (-1) * sizeof(b);
            file.seekp(pos, ios::cur);

            file.write((char*)&b, sizeof(b));

            found = true;
            break;
        }
    }

    if (!found)
        cout << "\nBook Not Found!\n";

    file.close();
}

// Return Book
void returnBook() {
    Book b;
    int id;
    bool found = false;

    fstream file("library.dat", ios::binary | ios::in | ios::out);

    cout << "\nEnter Book ID to Return: ";
    cin >> id;

    while (file.read((char*)&b, sizeof(b))) {
        if (b.getBookID() == id) {
            b.returnBook();

            int pos = (-1) * sizeof(b);
            file.seekp(pos, ios::cur);

            file.write((char*)&b, sizeof(b));

            found = true;
            break;
        }
    }

    if (!found)
        cout << "\nBook Not Found!\n";

    file.close();
}

int main() {
    int choice;

    do {
        cout << "\n========== LIBRARY MANAGEMENT SYSTEM ==========\n";
        cout << "1. Add New Book\n";
        cout << "2. Display All Books\n";
        cout << "3. Search Book by Title\n";
        cout << "4. Search Book by Author\n";
        cout << "5. Issue Book\n";
        cout << "6. Return Book\n";
        cout << "7. Exit\n";
        cout << "Enter Your Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addNewBook();
                break;

            case 2:
                displayBooks();
                break;

            case 3:
                searchByTitle();
                break;

            case 4:
                searchByAuthor();
                break;

            case 5:
                issueBook();
                break;

            case 6:
                returnBook();
                break;

            case 7:
                cout << "\nExiting Library System...\n";
                break;

            default:
                cout << "\nInvalid Choice! Try Again.\n";
        }

    } while (choice != 7);

    return 0;
}
