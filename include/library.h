#ifndef LIBRARY_H
#define LIBRARY_H

#define MAX_BOOKS 100
#define TITLE_LEN 50
#define AUTHOR_LEN 50
#define NAME_LEN 50

// Book structure
struct Book {
    int id;
    char title[TITLE_LEN];
    char author[AUTHOR_LEN];
    int total_copies;
    int available_copies;
    char last_borrower[NAME_LEN];  // NEW: who last borrowed this book
};

// Global variables (defined in operations.c)
extern struct Book library[MAX_BOOKS];
extern int book_count;

// Core functions
void loadBooks(const char *filename);
void saveBooks(const char *filename);

void addBook();
void listBooks();
void listAvailableBooks();
void searchBookById();
void searchBookByTitle();
void searchBookByAuthor();   // NEW
void issueBook();
void returnBook();
void deleteBook();
void showStats();            // NEW

#endif
