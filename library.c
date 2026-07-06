#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 100
#define TITLE_LENGTH 100
#define AUTHOR_LENGTH 50

// Structure to store book details
struct Book {
    int id;
    char title[TITLE_LENGTH];
    char author[AUTHOR_LENGTH];
    int isIssued; // 0 = Available, 1 = Issued
};

// Function prototypes
void addBook(struct Book library[], int *count);
void displayBooks(const struct Book library[], int count);
void searchBook(const struct Book library[], int count);
void issueBook(struct Book library[], int count);

int main() {
    struct Book library[MAX_BOOKS];
    int count = 0;
    int choice;

    while (1) {
        printf("\n=== Library Management System ===\n");
        printf("1. Add Book\n");
        printf("2. Display All Books\n");
        printf("3. Search Book by ID\n");
        printf("4. Issue / Return Book\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }

        switch (choice) {
            case 1:
                addBook(library, &count);
                break;
            case 2:
                displayBooks(library, count);
                break;
            case 3:
                searchBook(library, count);
                break;
            case 4:
                issueBook(library, count);
                break;
            case 5:
                printf("Exiting library system. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice. Please select between 1 and 5.\n");
        }
    }

    return 0;
}

// Function to add a new book to the library
void addBook(struct Book library[], int *count) {
    if (*count >= MAX_BOOKS) {
        printf("Library storage is full!\n");
        return;
    }

    struct Book newBook;

    printf("\nEnter Book ID: ");
    scanf("%d", &newBook.id);

    // Check for duplicate ID
    for (int i = 0; i < *count; i++) {
        if (library[i].id == newBook.id) {
            printf("Error: A book with ID %d already exists.\n", newBook.id);
            return;
        }
    }

    printf("Enter Book Title: ");
    getchar(); // Clear trailing newline from scanf
    fgets(newBook.title, TITLE_LENGTH, stdin);
    newBook.title[strcspn(newBook.title, "\n")] = '\0'; // Remove newline character

    printf("Enter Author Name: ");
    fgets(newBook.author, AUTHOR_LENGTH, stdin);
    newBook.author[strcspn(newBook.author, "\n")] = '\0';

    newBook.isIssued = 0; // New books are available by default

    library[*count] = newBook;
    (*count)++;

    printf("Book added successfully!\n");
}

// Function to list all books
void displayBooks(const struct Book library[], int count) {
    if (count == 0) {
        printf("\nThe library is empty.\n");
        return;
    }

    printf("\n%-5s %-35s %-25s %-10s\n", "ID", "Title", "Author", "Status");
    printf("----------------------------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-5d %-35s %-25s %-10s\n", 
               library[i].id, 
               library[i].title, 
               library[i].author, 
               library[i].isIssued ? "Issued" : "Available");
    }
}

// Function to search for a book by its ID
void searchBook(const struct Book library[], int count) {
    if (count == 0) {
        printf("\nNo books available to search.\n");
        return;
    }

    int searchId;
    printf("\nEnter Book ID to search: ");
    scanf("%d", &searchId);

    for (int i = 0; i < count; i++) {
        if (library[i].id == searchId) {
            printf("\nBook Found:\n");
            printf("ID: %d\n", library[i].id);
            printf("Title: %s\n", library[i].title);
            printf("Author: %s\n", library[i].author);
            printf("Status: %s\n", library[i].isIssued ? "Issued" : "Available");
            return;
        }
    }

    printf("Book with ID %d not found.\n", searchId);
}

// Function to toggle the availability status of a book
void issueBook(struct Book library[], int count) {
    if (count == 0) {
        printf("\nNo books available in the library.\n");
        return;
    }

    int bookId, option;
    printf("\nEnter Book ID: ");
    scanf("%d", &bookId);

    for (int i = 0; i < count; i++) {
        if (library[i].id == bookId) {
            printf("Book current status: %s\n", library[i].isIssued ? "Issued" : "Available");
            printf("1. Issue Book\n2. Return Book\nSelect option: ");
            scanf("%d", &option);

            if (option == 1) {
                if (library[i].isIssued == 1) {
                    printf("Book is already issued out.\n");
                } else {
                    library[i].isIssued = 1;
                    printf("Book issued successfully!\n");
                }
            } else if (option == 2) {
                if (library[i].isIssued == 0) {
                    printf("Book is already in the library.\n");
                } else {
                    library[i].isIssued = 0;
                    printf("Book returned successfully!\n");
                }
            } else {
                printf("Invalid option.\n");
            }
            return;
        }
    }

    printf("Book with ID %d not found.\n", bookId);
}
