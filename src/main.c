#include <stdio.h>
#include "library.h"

int main() {
    int choice;
    const char *datafile = "library_data.txt";

    // Load existing data from file (if any)
    loadBooks(datafile);

    printf("=====================================\n");
    printf("        Library Management\n");
    printf("=====================================\n");

    while (1) {
        printf("\nMenu:\n");
        printf("1. Add Book\n");
        printf("2. List All Books\n");
        printf("3. List Available Books\n");
        printf("4. Search Book by ID\n");
        printf("5. Search Book by Title\n");
        printf("6. Search Book by Author\n");
        printf("7. Issue Book\n");
        printf("8. Return Book\n");
        printf("9. Delete Book\n");
        printf("10. Show Library Statistics\n");
        printf("11. Save & Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            addBook();
            break;
        case 2:
            listBooks();
            break;
        case 3:
            listAvailableBooks();
            break;
        case 4:
            searchBookById();
            break;
        case 5:
            searchBookByTitle();
            break;
        case 6:
            searchBookByAuthor();
            break;
        case 7:
            issueBook();
            break;
        case 8:
            returnBook();
            break;
        case 9:
            deleteBook();
            break;
        case 10:
            showStats();
            break;
        case 11:
            saveBooks(datafile);
            printf("Data saved. Exiting...\n");
            return 0;
        default:
            printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}

