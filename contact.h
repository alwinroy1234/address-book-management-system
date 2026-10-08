#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[MAX_CONTACTS];
    int contactCount;
} AddressBook;

void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);

int searchByName(AddressBook *addressBook, char name[], int indexes[]);
int searchByPhone(AddressBook *addressBook, char phone[]);
int searchByEmail(AddressBook *addressBook, char email[]);

int validateName(char name[]);
int validatePhone(char phone[]);
int validateEmail(char email[]);

#endif
