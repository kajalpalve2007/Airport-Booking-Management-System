
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for passenger details
typedef struct Passenger {
    char passport[20];
    char name[50];
    char destination[50];
    char email[50];
    int seat_num;

    struct Passenger *next;
} Passenger;

Passenger *head = NULL;
int seatCounter = 101;

static void clearInputBuffer(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }
}

static int readLine(const char *prompt, char *buffer, size_t size) {
    printf("%s", prompt);
    if (fgets(buffer, (int)size, stdin) == NULL) {
        buffer[0] = '\0';
        clearInputBuffer();
        return 0;
    }

    buffer[strcspn(buffer, "\n")] = '\0';
    return 1;
}

// Function to book a ticket
void bookTicket() {
    Passenger *newPassenger;
    Passenger *temp;

    newPassenger = (struct Passenger *)malloc(sizeof(struct Passenger));

    if (newPassenger == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("\nEnter Passport Number: ");
    scanf(" %19s", newPassenger->passport);

    // Check duplicate passport
    temp = head;
    while (temp != NULL) {
        if (strcmp(temp->passport, newPassenger->passport) == 0) {
            printf("Passenger already booked!\n");
            free(newPassenger);
            return;
        }
        temp = temp->next;
    }

    printf("Enter Passenger Name: ");
    scanf(" %49[^\n]", newPassenger->name);

    printf("Enter Destination: ");
    scanf(" %49[^\n]", newPassenger->destination);

    printf("Enter Email: ");
    scanf(" %49s", newPassenger->email);

    newPassenger->seat_num = seatCounter++;
    newPassenger->next = NULL;

    if (head == NULL) {
        head = newPassenger;
    } else {
        temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newPassenger;
    }

    printf("\nTicket Booked Successfully!\n");
    printf("Your Seat Number: %d\n", newPassenger->seat_num);
}

// Function to cancel booking
void cancelTicket() {
    char passport[20];
    struct Passenger *temp = head;
    struct Passenger *prev = NULL;

    printf("\nEnter Passport Number to Cancel: ");
    scanf(" %19s", passport);

    while (temp != NULL) {
        if (strcmp(temp->passport, passport) == 0) {

            if (prev == NULL) {
                head = temp->next;
            } else {
                prev->next = temp->next;
            }

            free(temp);
            printf("\nBooking Cancelled Successfully!\n");
            return;
        }

        prev = temp;
        temp = temp->next;
    }

    printf("\nBooking Not Found!\n");
}

// Function to display passenger records
void showRecords() {
    struct Passenger *temp = head;

    if (temp == NULL) {
        printf("\nNo Booking Records Found!\n");
        return;
    }

    printf("\n========== PASSENGER RECORDS ==========\n");

    while (temp != NULL) {
        printf("\nPassenger Name : %s", temp->name);
        printf("\nPassport Number: %s", temp->passport);
        printf("\nDestination    : %s", temp->destination);
        printf("\nEmail          : %s", temp->email);
        printf("\nSeat Number    : %d", temp->seat_num);
        printf("\n--------------------------------------\n");

        temp = temp->next;
    }
}

// Function to search passenger
void searchPassenger() {
    char passport[20];
    struct Passenger *temp = head;

    printf("\nEnter Passport Number: ");
    scanf(" %19s", passport);

    while (temp != NULL) {
        if (strcmp(temp->passport, passport) == 0) {
            printf("\nPassenger Found!\n");
            printf("Name        : %s\n", temp->name);
            printf("Destination : %s\n", temp->destination);
            printf("Seat Number : %d\n", temp->seat_num);
            printf("Email       : %s\n", temp->email);
            return;
        }

        temp = temp->next;
    }

    printf("\nPassenger Not Found!\n");
}

// Function to free allocated memory
void freeRecords() {
    struct Passenger *temp;

    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// Main function
int main() {
    int choice;

    do {
        printf("\n\n====================================");
        printf("\n     AIRPORT BOOKING MANAGEMENT");
        printf("\n====================================");
        printf("\n1. Book Flight Ticket");
        printf("\n2. Cancel Booking");
        printf("\n3. Show Passenger Records");
        printf("\n4. Search Passenger");
        printf("\n5. Exit");
        printf("\n====================================");
        printf("\nEnter Your Choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("\nInvalid Input!\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                bookTicket();
                break;

            case 2:
                cancelTicket();
                break;

            case 3:
                showRecords();
                break;

            case 4:
                searchPassenger();
                break;

            case 5:
                freeRecords();
                printf("\nThank You for Using Our System!\n");
                break;

            default:
                printf("\nInvalid Choice! Try Again.\n");
        }

    } while (choice != 5);

    return 0;
}
