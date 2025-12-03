#include <stdio.h>
#include "library.h"

int main() {
    int choice;

    printf("=====================================\n");
    printf("     Library Management System\n");
    printf("=====================================\n");

    while (1) {
        printf("\nMenu:\n");
        printf("1. Add Book\n");
        printf("2. List Books\n");
        printf("3. Search Book\n");
        printf("4. Issue Book\n");
        printf("5. Return Book\n");
        printf("6. Exit\n");
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
            searchBook();
            break;
        case 4:
            issueBook();
            break;
        case 5:
            returnBook();
            break;
        case 6:
            printf("Goodbye 👋\n");
            return 0;
        default:
            printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
