#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "library.h"

struct Book library[MAX_BOOKS];
int book_count = 0;

// Helper: trim newline from fgets
static void trimNewline(char *s) {
    size_t len = strlen(s);
    if (len > 0 && s[len - 1] == '\n') {
        s[len - 1] = '\0';
    }
}

// Load books from a text file
// Format per line: id;title;author;total;available;last_borrower
void loadBooks(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        // File may not exist on first run - not an error
        book_count = 0;
        return;
    }

    char line[256];
    book_count = 0;

    while (fgets(line, sizeof(line), fp) && book_count < MAX_BOOKS) {
        trimNewline(line);
        if (line[0] == '\0') continue;

        struct Book b;
        char title[TITLE_LEN], author[AUTHOR_LEN], borrower[NAME_LEN];

        // Using sscanf expecting semicolon-separated fields
        int scanned = sscanf(line, "%d;%49[^;];%49[^;];%d;%d;%49[^\n]",
                             &b.id, title, author,
                             &b.total_copies,
                             &b.available_copies,
                             borrower);
        if (scanned == 6) {
            strncpy(b.title, title, TITLE_LEN);
            b.title[TITLE_LEN - 1] = '\0';
            strncpy(b.author, author, AUTHOR_LEN);
            b.author[AUTHOR_LEN - 1] = '\0';
            strncpy(b.last_borrower, borrower, NAME_LEN);
            b.last_borrower[NAME_LEN - 1] = '\0';

            library[book_count++] = b;
        }
    }

    fclose(fp);
}

// Save books to file
void saveBooks(const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        printf("Error: Could not open file to save data.\n");
        return;
    }

    for (int i = 0; i < book_count; i++) {
        fprintf(fp, "%d;%s;%s;%d;%d;%s\n",
                library[i].id,
                library[i].title,
                library[i].author,
                library[i].total_copies,
                library[i].available_copies,
                library[i].last_borrower);
    }

    fclose(fp);
}

// Add a new book
void addBook() {
    if (book_count >= MAX_BOOKS) {
        printf("\nLibrary is full, cannot add more books.\n");
        return;
    }

    struct Book newBook;
    int exists = 0;

    printf("\n--- Add New Book ---\n");

    printf("Enter book ID: ");
    scanf("%d", &newBook.id);
    getchar(); // clear newline

    // Check duplicate ID
    for (int i = 0; i < book_count; i++) {
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
    trimNewline(newBook.title);

    printf("Enter author name: ");
    fgets(newBook.author, AUTHOR_LEN, stdin);
    trimNewline(newBook.author);

    printf("Enter total copies: ");
    scanf("%d", &newBook.total_copies);
    getchar();

    if (newBook.total_copies < 0) {
        newBook.total_copies = 0;
    }

    newBook.available_copies = newBook.total_copies;
    strcpy(newBook.last_borrower, "None");

    library[book_count++] = newBook;

    printf("Book added successfully.\n");
}

// List all books
void listBooks() {
    printf("\n--- All Books in Library ---\n");

    if (book_count == 0) {
        printf("No books available.\n");
        return;
    }

    printf("%-5s %-30s %-20s %-8s %-8s %-15s\n",
           "ID", "Title", "Author", "Total", "Avail", "Last Borrower");
    printf("--------------------------------------------------------------------------\n");

    for (int i = 0; i < book_count; i++) {
        printf("%-5d %-30s %-20s %-8d %-8d %-15s\n",
               library[i].id,
               library[i].title,
               library[i].author,
               library[i].total_copies,
               library[i].available_copies,
               library[i].last_borrower);
    }
}

// List books with available copies only
void listAvailableBooks() {
    int found = 0;

    printf("\n--- Books Currently Available ---\n");

    for (int i = 0; i < book_count; i++) {
        if (library[i].available_copies > 0) {
            if (!found) {
                printf("%-5s %-30s %-20s %-8s %-8s\n",
                       "ID", "Title", "Author", "Total", "Avail");
                printf("--------------------------------------------------------------\n");
            }
            printf("%-5d %-30s %-20s %-8d %-8d\n",
                   library[i].id,
                   library[i].title,
                   library[i].author,
                   library[i].total_copies,
                   library[i].available_copies);
            found = 1;
        }
    }

    if (!found) {
        printf("No books are currently available.\n");
    }
}

// Search by ID
void searchBookById() {
    int id;
    printf("\n--- Search Book by ID ---\n");
    printf("Enter book ID: ");
    scanf("%d", &id);

    for (int i = 0; i < book_count; i++) {
        if (library[i].id == id) {
            printf("\nBook found:\n");
            printf("ID: %d\n", library[i].id);
            printf("Title: %s\n", library[i].title);
            printf("Author: %s\n", library[i].author);
            printf("Total copies: %d\n", library[i].total_copies);
            printf("Available copies: %d\n", library[i].available_copies);
            printf("Last borrower: %s\n", library[i].last_borrower);
            return;
        }
    }

    printf("Book not found.\n");
}

// Search by title (partial match)
void searchBookByTitle() {
    char keyword[TITLE_LEN];
    int found = 0;

    printf("\n--- Search Book by Title ---\n");
    printf("Enter part of the title: ");
    getchar(); // clear leftover newline
    fgets(keyword, TITLE_LEN, stdin);
    trimNewline(keyword);

    printf("\nSearch results for \"%s\":\n", keyword);

    for (int i = 0; i < book_count; i++) {
        if (strstr(library[i].title, keyword) != NULL) {
            if (!found) {
                printf("%-5s %-30s %-20s %-8s %-8s\n",
                       "ID", "Title", "Author", "Total", "Avail");
                printf("--------------------------------------------------------------\n");
            }
            printf("%-5d %-30s %-20s %-8d %-8d\n",
                   library[i].id,
                   library[i].title,
                   library[i].author,
                   library[i].total_copies,
                   library[i].available_copies);
            found = 1;
        }
    }

    if (!found) {
        printf("No books matched the given title.\n");
    }
}

// NEW: Search by author
void searchBookByAuthor() {
    char keyword[AUTHOR_LEN];
    int found = 0;

    printf("\n--- Search Book by Author ---\n");
    printf("Enter part of the author name: ");
    getchar(); // clear newline
    fgets(keyword, AUTHOR_LEN, stdin);
    trimNewline(keyword);

    printf("\nSearch results for author containing \"%s\":\n", keyword);

    for (int i = 0; i < book_count; i++) {
        if (strstr(library[i].author, keyword) != NULL) {
            if (!found) {
                printf("%-5s %-30s %-20s %-8s %-8s\n",
                       "ID", "Title", "Author", "Total", "Avail");
                printf("--------------------------------------------------------------\n");
            }
            printf("%-5d %-30s %-20s %-8d %-8d\n",
                   library[i].id,
                   library[i].title,
                   library[i].author,
                   library[i].total_copies,
                   library[i].available_copies);
            found = 1;
        }
    }

    if (!found) {
        printf("No books matched the given author.\n");
    }
}

// Issue a book (with borrower name)
void issueBook() {
    int id;
    printf("\n--- Issue Book ---\n");
    printf("Enter book ID: ");
    scanf("%d", &id);
    getchar();

    for (int i = 0; i < book_count; i++) {
        if (library[i].id == id) {
            if (library[i].available_copies > 0) {
                char name[NAME_LEN];
                printf("Enter borrower name: ");
                fgets(name, NAME_LEN, stdin);
                trimNewline(name);

                library[i].available_copies--;
                strncpy(library[i].last_borrower, name, NAME_LEN);
                library[i].last_borrower[NAME_LEN - 1] = '\0';

                printf("Book \"%s\" issued to %s.\n", library[i].title, library[i].last_borrower);
            } else {
                printf("Sorry, no available copies of \"%s\".\n", library[i].title);
            }
            return;
        }
    }

    printf("Book not found.\n");
}

// Return a book
void returnBook() {
    int id;
    printf("\n--- Return Book ---\n");
    printf("Enter book ID: ");
    scanf("%d", &id);

    for (int i = 0; i < book_count; i++) {
        if (library[i].id == id) {
            if (library[i].available_copies < library[i].total_copies) {
                library[i].available_copies++;
                printf("Book \"%s\" returned.\n", library[i].title);
            } else {
                printf("All copies of this book are already in the library.\n");
            }
            return;
        }
    }

    printf("Book not found.\n");
}

// Delete a book by ID
void deleteBook() {
    int id;
    printf("\n--- Delete Book ---\n");
    printf("Enter book ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < book_count; i++) {
        if (library[i].id == id) {
            // shift left
            for (int j = i; j < book_count - 1; j++) {
                library[j] = library[j + 1];
            }
            book_count--;
            printf("Book with ID %d deleted.\n", id);
            return;
        }
    }

    printf("No book found with ID %d.\n", id);
}

// Show basic statistics
void showStats() {
    int total_copies = 0;
    int total_available = 0;

    for (int i = 0; i < book_count; i++) {
        total_copies += library[i].total_copies;
        total_available += library[i].available_copies;
    }

    printf("\n--- Library Statistics ---\n");
    printf("Total distinct books : %d\n", book_count);
    printf("Total copies         : %d\n", total_copies);
    printf("Total available      : %d\n", total_available);
}
