#ifndef LIBRARY_H
#define LIBRARY_H

#define MAX_BOOKS 100
#define TITLE_LEN 50
#define AUTHOR_LEN 50

// Book structure
struct Book {
    int id;
    char title[TITLE_LEN];
    char author[AUTHOR_LEN];
    int total_copies;
    int available_copies;
};

// Global variables
extern struct Book library[MAX_BOOKS];
extern int book_count;

// Function prototypes
void addBook();
void listBooks();
void searchBook();
void issueBook();
void returnBook();

#endif
