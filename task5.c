#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int bookID;
    char title[100];
    char author[50];
    int year;
    float price;
} Book;

Book books[100];
int N = 0; 

void loadBookData();
void saveBookData();
void inputBookData();
void displayBookData();
void findBookByID();
void calculateTotalValue();
int isUniqueID(int id);

void loadBookData() {
    FILE *file = fopen("books.dat", "rb");
    if (file != NULL) {
        fread(&N, sizeof(int), 1, file); 
        fread(books, sizeof(Book), N, file); 
        fclose(file);
        printf("Loaded %d books from books.dat.\n", N);
    } else {
        printf("No existing data found. Starting with an empty library.\n");
    }
}

void saveBookData() {
    FILE *file = fopen("books.dat", "wb");
    if (file == NULL) {
        perror("Error saving data");
        return;
    }
    fwrite(&N, sizeof(int), 1, file); 
    fwrite(books, sizeof(Book), N, file); 
    fclose(file);
    printf("Book data saved to books.dat.\n");
}

int isUniqueID(int id) {
    for (int i = 0; i < N; i++) {
        if (books[i].bookID == id) {
            return 0; 
        }
    }
    return 1; 
}

void inputBookData() {
    if (N >= 100) {
        printf("Library is full. Cannot add more books.\n");
        return;
    }

    Book newBook;
    printf("Enter book details:\n");

    do {
        printf("ID: ");
        scanf("%d", &newBook.bookID);
        if (!isUniqueID(newBook.bookID)) {
            printf("This ID already exists. Please enter a unique ID.\n");
        }
    } while (!isUniqueID(newBook.bookID));

    getchar(); 
    printf("Title: ");
    fgets(newBook.title, sizeof(newBook.title), stdin);
    newBook.title[strcspn(newBook.title, "\n")] = 0; 
    printf("Author: ");
    fgets(newBook.author, sizeof(newBook.author), stdin);
    newBook.author[strcspn(newBook.author, "\n")] = 0; 
    printf("Year: ");
    scanf("%d", &newBook.year);
    printf("Price (SAR): ");
    scanf("%f", &newBook.price);

    books[N++] = newBook; 
    saveBookData(); 
}

void displayBookData() {
    if (N == 0) {
        printf("No books in the library.\n");
        return;
    }
    printf("Book List:\n");
    for (int i = 0; i < N; i++) {
        printf("ID: %d\n", books[i].bookID);
        printf("Title: %s\n", books[i].title);
        printf("Author: %s\n", books[i].author);
        printf("Year: %d\n", books[i].year);
        printf("Price: %.2f SAR\n", books[i].price);
        printf("-------------------------\n");
    }
}

void findBookByID() {
    int id;
    printf("Enter book ID to search: ");
    scanf("%d", &id);

    for (int i = 0; i < N; i++) {
        if (books[i].bookID == id) {
            printf("Book found:\n");
            printf("ID: %d\n", books[i].bookID);
            printf("Title: %s\n", books[i].title);
            printf("Author: %s\n", books[i].author);
            printf("Year: %d\n", books[i].year);
            printf("Price: %.2f SAR\n", books[i].price);
            return;
        }
    }
    printf("No book found with ID %d.\n", id);
}

void calculateTotalValue() {
    float totalValue = 0.0;
    for (int i = 0; i < N; i++) {
        totalValue += books[i].price;
    }
    printf("Total value of all books: %.2f SAR\n", totalValue);
}

int main() {
    loadBookData();

    int choice;
    while (1) {
        printf("\nLibrary Management System\n");
        printf("1. Add a Book\n");
        printf("2. Display All Books\n");
        printf("3. Search for Book by ID\n");
        printf("4. Calculate Total Value of Books\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                inputBookData();
                break;
            case 2:
                displayBookData();
                break;
            case 3:
                findBookByID();
                break;
            case 4:
                calculateTotalValue();
                break;
            case 5:
                printf("Exiting the program. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

