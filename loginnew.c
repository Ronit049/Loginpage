#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function prototypes
void login();
void registerUser();
void viewUsers();

// Maximum length for username and password
#define MAX_LENGTH 30

// Structure to hold user details
struct User {
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];
};

int main() {
    int choice;

    while (1) {
        printf("\n=== Login System ===\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. View All Users\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                login();
                break;
            case 3:
                viewUsers();
                break;
            case 4:
                printf("Exiting... Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

void registerUser() {
    struct User user;
    FILE *file;

    // Open file for appending
    file = fopen("users.txt", "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\n=== Register ===\n");
    printf("Enter username: ");
    scanf("%s", user.username);
    printf("Enter password: ");
    scanf("%s", user.password);

    // Write user data to file
    fprintf(file, "%s %s\n", user.username, user.password);
    fclose(file);

    printf("Registration successful! You can now log in.\n");
}

void login() {
    struct User user;
    char inputUsername[MAX_LENGTH], inputPassword[MAX_LENGTH];
    FILE *file;
    int isAuthenticated = 0;

    // Open file for reading
    file = fopen("users.txt", "r");
    if (file == NULL) {
        printf("Error opening file! Make sure you have registered first.\n");
        return;
    }

    printf("\n=== Login ===\n");
    printf("Enter username: ");
    scanf("%s", inputUsername);
    printf("Enter password: ");
    scanf("%s", inputPassword);

    // Check credentials
    while (fscanf(file, "%s %s", user.username, user.password) != EOF) {
        if (strcmp(inputUsername, user.username) == 0 && strcmp(inputPassword, user.password) == 0) {
            isAuthenticated = 1;
            break;
        }
    }
    fclose(file);

    if (isAuthenticated) {
        printf("Login successful! Welcome, %s.\n", inputUsername);
    } else {
        printf("Invalid username or password. Please try again.\n");
    }
}

void viewUsers() {
    struct User user;
    FILE *file;

    // Open file for reading
    file = fopen("users.txt", "r");
    if (file == NULL) {
        printf("Error opening file! Make sure you have registered first.\n");
        return;
    }

    printf("\n=== Registered Users ===\n");
    printf("%-20s %-20s\n", "Username", "Password");
    printf("----------------------------------------\n");

    // Read and display user data from the file
    while (fscanf(file, "%s %s", user.username, user.password) != EOF) {
        printf("%-20s %-20s\n", user.username, user.password);
    }

    fclose(file);
}
