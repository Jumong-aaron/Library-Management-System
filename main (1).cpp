#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

/* ===== BOOK STRUCT ===== */
struct Book {
    int id;
    string title;
    string author;
    bool isBorrowed = false;
};

/* ===== DATA STRUCTURES ===== */
vector<Book> books;                     // VECTOR
unordered_map<int, Book> bookMap;       // HASH TABLE
queue<int> borrowQueue;                 // QUEUE

/* ===== ADD BOOK ===== */
void addBook(int id, string title, string author) {
    Book b = { id, title, author, false };

    books.push_back(b);
    bookMap[id] = b;

    cout << "Book added!\n";
}

/* ===== DISPLAY BOOKS ===== */
void displayBooks() {
    cout << "\n--- BOOK LIST ---\n";

    for (int i = 0; i < books.size(); i++) {
        cout << "ID: " << books[i].id
            << " | Title: " << books[i].title
            << " | Author: " << books[i].author
            << " | Status: "
            << (books[i].isBorrowed ? "Borrowed" : "Available")
            << endl;
    }
}

/* ===== SEARCH BOOK ===== */
void searchBook(int id) {
    if (bookMap.find(id) != bookMap.end()) {
        cout << "Found: " << bookMap[id].title << endl;
    }
    else {
        cout << "Book not found\n";
    }
}

/* ===== BORROW BOOK ===== */
void borrowBook(int bookID) {

    if (bookMap.find(bookID) == bookMap.end()) {
        cout << "Book not found\n";
        return;
    }

    if (!bookMap[bookID].isBorrowed) {
        bookMap[bookID].isBorrowed = true;

        for (int i = 0; i < books.size(); i++) {
            if (books[i].id == bookID)
                books[i].isBorrowed = true;
        }

        cout << "Book borrowed!\n";
    }
    else {
        borrowQueue.push(bookID);
        cout << "Book already borrowed. Added to queue.\n";
    }
}

/* ===== RETURN BOOK ===== */
void returnBook(int bookID) {

    if (bookMap.find(bookID) == bookMap.end()) {
        cout << "Book not found\n";
        return;
    }

    bookMap[bookID].isBorrowed = false;

    for (int i = 0; i < books.size(); i++) {
        if (books[i].id == bookID)
            books[i].isBorrowed = false;
    }

    cout << "Book returned!\n";

    if (!borrowQueue.empty()) {
        cout << "Next request for Book ID: " << borrowQueue.front() << endl;
        borrowQueue.pop();
    }
}

/* ===== MAIN ===== */
int main() {
    int choice;

    do {
        cout << "\nMenu\n1 Add Book\n2 Display Books\n3 Search Book\n4 Borrow\n5 Return\n6 Exit\nChoice:";
        cin >> choice;

        if (choice == 1) {
            int id;
            string title, author;

            cout << "Book ID: ";
            cin >> id;
            cin.ignore();

            cout << "Title: ";
            getline(cin, title);

            cout << "Author: ";
            getline(cin, author);

            addBook(id, title, author);
        }

        else if (choice == 2) displayBooks();

        else if (choice == 3) {
            int id;
            cout << "Enter ID: ";
            cin >> id;
            searchBook(id);
        }

        else if (choice == 4) {
            int id;
            cout << "Enter Book ID: ";
            cin >> id;
            borrowBook(id);
        }

        else if (choice == 5) {
            int id;
            cout << "Enter Book ID: ";
            cin >> id;
            returnBook(id);
        }

    } while (choice != 6);

    return 0;
}