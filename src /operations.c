#include <stdio.h>
#include <string.h>
#include "library.h"

struct Book library[MAX_BOOKS];
int book_count = 0;

// Add a new book
void addBook() {
    if (book_count >= MAX_BOOKS) {
        printf("\nLibrary is full, cannot add more books.\n");
        return;
    }

    struct Book newBook;
    int i, exists = 0;

    printf("\n--- Add New Book ---\n");

    printf("Enter book ID: ");
    scanf("%d", &newBook.id);
    getchar();

    // Check duplicate ID
    for (i = 0; i < book_count; i++) {
        if (library[i].id == newBook.id) {
            exists = 1;
            break;
        }
    }

    if (exists) {
        printf("A book with this ID already exists.\n");
        return;
    }

    printf("Enter book title: ");
    fgets(newBook.title, TITLE_LEN, stdin);
    newBook.title[strcspn(newBook.title, "\n")] = '\0';

    printf("Enter author name: ");
    fgets(newBook.author, AUTHOR_LEN, stdin);
    newBook.author[strcspn(newBook.author, "\n")] = '\0';

    printf("Enter total copies: ");
    scanf("%d", &newBook.total_copies);

    newBook.available_copies = newBook.total_copies;

    library[book_count] = newBook;
    book_count++;

    printf("Book added successfully.\n");
}

// List all books
void listBooks() {
    int i;

    printf("\n--- Library Books ---\n");

    if (book_count == 0) {
        printf("No books available.\n");
        return;
    }

    printf("%-5s %-30s %-20s %-10s %-10s\n",
           "ID","Title","Author","Total","Available");
    printf("---------------------------------------------------------\n");

    for (i = 0; i < book_count; i++) {
        printf("%-5d %-30s %-20s %-10d %-10d\n",
               library[i].id,
               library[i].title,
               library[i].author,
               library[i].total_copies,
               library[i].available_copies);
    }
}

// Search by ID
void searchBook() {
    int id,i;

    printf("\n--- Search Book ---\n");
    printf("Enter book ID: ");
    scanf("%d", &id);

    for (i = 0; i < book_count; i++) {
        if (library[i].id == id) {
            printf("\nBook found!\n");
            printf("ID: %d\n", library[i].id);
            printf("Title: %s\n", library[i].title);
            printf("Author: %s\n", library[i].author);
            printf("Total copies: %d\n", library[i].total_copies);
            printf("Available copies: %d\n", library[i].available_copies);
            return;
        }
    }

    printf("Book not found.\n");
}

// Issue book
void issueBook() {
    int id,i;

    printf("\n--- Issue Book ---\n");
    printf("Enter book ID: ");
    scanf("%d", &id);

    for (i = 0; i < book_count; i++) {
        if (library[i].id == id) {
            if (library[i].available_copies > 0) {
                library[i].available_copies--;
                printf("Issued: %s\n", library[i].title);
            } else {
                printf("No available copies.\n");
            }
            return;
        }
    }

    printf("Book not found.\n");
}

// Return book
void returnBook() {
    int id,i;

    printf("\n--- Return Book ---\n");
    printf("Enter book ID: ");
    scanf("%d", &id);

    for (i = 0; i < book_count; i++) {
        if (library[i].id == id) {

            if (library[i].available_copies < library[i].total_copies) {
                library[i].available_copies++;
                printf("Returned: %s\n", library[i].title);
            } else {
                printf("All copies are already in library.\n");
            }
            return;
        }
    }

    printf("Book not found.\n");
}
