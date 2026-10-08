#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include <ctype.h>

int searchByName(AddressBook *addressBook, char name[], int indexes[])
{
    int i;
    int count = 0;

    for(i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(addressBook->contacts[i].name, name) == 0)
        {
            indexes[count] = i;
            count++;
        }
    }

    return count;
}
int searchByPhone(AddressBook *addressBook, char phone[])
{
    int i;

    for(i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(addressBook->contacts[i].phone, phone) == 0)
        {
            return i;
        }
    }

    return -1;
}
int searchByEmail(AddressBook *addressBook, char email[])
{
    int i;

    for(i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(addressBook->contacts[i].email, email) == 0)
        {
            return i;
        }
    }

    return -1;
}

void listContacts(AddressBook *addressBook) 
{
    
    int i;

    printf("\n");
    printf("=====================================================================\n");
    printf("%-5s %-20s %-15s %-30s\n", "S.No", "Name", "Phone", "Email");
    printf("=====================================================================\n");

    for(i = 0; i < addressBook->contactCount; i++)
    {
        printf("%-5d %-20s %-15s %-30s\n",
               i + 1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }

    printf("=====================================================================\n");
    
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

int validateName(char name[])
{
    int i;

    for(i = 0; name[i] != '\0'; i++)
    {
        if(!isalpha(name[i]) && name[i] != ' ')
        {
            return 0;
        }
    }

    return 1;
}
int validatePhone(char phone[])
{
    int i;

    if(strlen(phone) != 10)
    {
        return 0;
    }

    for(i = 0; phone[i] != '\0'; i++)
    {
        if(!isdigit(phone[i]))
        {
            return 0;
        }
    }

    return 1;
}
int validateEmail(char email[])
{
    char *at;
    char *dot;

    at = strchr(email, '@');
    dot = strchr(email, '.');

    if(at == NULL || dot == NULL)
    {
        return 0;
    }

    if(at == email)
    {
        return 0;
    }

    if(dot <= at + 1)
    {
        return 0;
    }

    if(*(dot + 1) == '\0')
    {
        return 0;
    }

    return 1;
}

void createContact(AddressBook *addressBook)
{
    char name[50];
    char phone[20];
    char email[50];

    while(1)
    {
        printf("Enter name: ");
        scanf(" %[^\n]", name);

        if(validateName(name))
        {
            break;
        }

        printf("Invalid name. Please enter a valid name.\n");
    }


    while(1)
    {
        printf("Enter phone number: ");
        scanf("%19s", phone);

        if(!validatePhone(phone))
        {
            printf("Invalid phone number. Enter exactly 10 digits.\n");
            continue;
        }

        if(searchByPhone(addressBook, phone) != -1)
        {
            printf("Phone number already exists.\n");
            continue;
        }

        break;
    }


    while(1)
    {
        printf("Enter email: ");
        scanf("%49s", email);

        if(validateEmail(email))
        {
            break;
        }

        printf("Invalid email. Please enter a valid email.\n");
    }


    strcpy(addressBook->contacts[addressBook->contactCount].name, name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);
    strcpy(addressBook->contacts[addressBook->contactCount].email, email);

    addressBook->contactCount++;

    printf("Contact added successfully.\n");
}

void searchContact(AddressBook *addressBook)
{
    int choice;
    int index;

    int indexes[100];
    int i;
    int count;

    char name[50];
    char phone[20];
    char email[50];

    printf("\nSearch Contact\n");
    printf("1. Search by Name\n");
    printf("2. Search by Phone\n");
    printf("3. Search by Email\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch(choice)
    {
        case 1:

            printf("Enter name: ");
            scanf(" %[^\n]", name);

            count = searchByName(addressBook, name, indexes);

            break;

        case 2:

            printf("Enter phone: ");
            scanf(" %19s", phone);

            index = searchByPhone(addressBook, phone);

            if(index != -1)
            {
                count = 1;
                indexes[0] = index;
            }
            else
            {
                count = 0;
            }

            break;

        case 3:

            printf("Enter email: ");
            scanf(" %49s", email);

            index = searchByEmail(addressBook, email);

            if(index != -1)
            {
                count = 1;
                indexes[0] = index;
            }
            else
            {
                count = 0;
            }

            break;

        default:

            printf("Invalid choice.\n");
            return;
    }

    if(count > 0)
    {
        printf("\n=====================================================================\n");
        printf("%-5s %-20s %-15s %-30s\n",
               "S.No", "Name", "Phone", "Email");
        printf("=====================================================================\n");

        for(i = 0; i < count; i++)
        {
            printf("%-5d %-20s %-15s %-30s\n",
                   indexes[i] + 1,
                   addressBook->contacts[indexes[i]].name,
                   addressBook->contacts[indexes[i]].phone,
                   addressBook->contacts[indexes[i]].email);
        }

        printf("=====================================================================\n");
    }
    else
    {
        printf("\nContact not found.\n");
    }
}

void editContact(AddressBook *addressBook)
{
    int choice;
    int editChoice;
    int index;
    int indexes[100];
    int count;
    int i;
    int found;

    char name[50];
    char phone[20];
    char email[50];

    printf("\nEdit Contact\n");
    printf("1. Search by Name\n");
    printf("2. Search by Phone\n");
    printf("3. Search by Email\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch(choice)
    {
        case 1:

            printf("Enter name: ");
            scanf(" %[^\n]", name);

            count = searchByName(addressBook, name, indexes);

            if(count == 0)
            {
                printf("Contact not found.\n");
                return;
            }

            printf("\nMatching Contacts:\n");

            printf("=====================================================================\n");
            printf("%-5s %-8s %-20s %-15s %-30s\n",
                   "S.No", "Index", "Name", "Phone", "Email");
            printf("=====================================================================\n");

            for(i = 0; i < count; i++)
            {
                printf("%-5d %-8d %-20s %-15s %-30s\n",
                       i + 1,
                       indexes[i],
                       addressBook->contacts[indexes[i]].name,
                       addressBook->contacts[indexes[i]].phone,
                       addressBook->contacts[indexes[i]].email);
            }

            printf("=====================================================================\n");

            printf("Enter index of the contact to edit: ");
            scanf("%d", &index);

            found = 0;

            for(i = 0; i < count; i++)
            {
                if(indexes[i] == index)
                {
                    found = 1;
                    break;
                }
            }

            if(found == 0)
            {
                printf("Invalid index.\n");
                return;
            }

            break;


        case 2:

            printf("Enter phone number: ");
            scanf("%19s", phone);

            index = searchByPhone(addressBook, phone);

            if(index == -1)
            {
                printf("Contact not found.\n");
                return;
            }

            break;


        case 3:

            printf("Enter email: ");
            scanf("%49s", email);

            index = searchByEmail(addressBook, email);

            if(index == -1)
            {
                printf("Contact not found.\n");
                return;
            }

            break;


        default:

            printf("Invalid choice.\n");
            return;
    }


    /* Ask what needs to be edited */

    printf("\nWhat do you want to edit?\n");
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("Enter your choice: ");
    scanf("%d", &editChoice);


    switch(editChoice)
    {
        case 1:

            while(1)
            {
                printf("Enter new name: ");
                scanf(" %[^\n]", name);

                if(validateName(name))
                {
                    break;
                }

                printf("Invalid name. Please enter a valid name.\n");
            }

            strcpy(addressBook->contacts[index].name, name);

            printf("Name updated successfully.\n");

            break;


        case 2:

            while(1)
            {
                printf("Enter new phone number: ");
                scanf("%19s", phone);

                if(!validatePhone(phone))
                {
                    printf("Invalid phone number. Enter exactly 10 digits.\n");
                    continue;
                }

                /* Check if phone belongs to another contact */

                found = 0;

                for(i = 0; i < addressBook->contactCount; i++)
                {
                    if(i != index &&
                       strcmp(addressBook->contacts[i].phone, phone) == 0)
                    {
                        found = 1;
                        break;
                    }
                }

                if(found == 1)
                {
                    printf("Phone number already exists.\n");
                }
                else
                {
                    break;
                }
            }

            strcpy(addressBook->contacts[index].phone, phone);

            printf("Phone number updated successfully.\n");

            break;


        case 3:

            while(1)
            {
                printf("Enter new email: ");
                scanf("%49s", email);

                if(validateEmail(email))
                {
                    break;
                }

                printf("Invalid email. Please enter a valid email.\n");
            }

            strcpy(addressBook->contacts[index].email, email);

            printf("Email updated successfully.\n");

            break;


        default:

            printf("Invalid choice.\n");
            return;
    }
}

void deleteContact(AddressBook *addressBook)
{
    int choice;
    int index;
    int indexes[100];
    int count;
    int i;
    int found;

    char name[50];
    char phone[20];
    char email[50];

    printf("\nDelete Contact\n");
    printf("1. Delete by Name\n");
    printf("2. Delete by Phone\n");
    printf("3. Delete by Email\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch(choice)
    {
        case 1:

            printf("Enter name: ");
            scanf(" %[^\n]", name);

            count = searchByName(addressBook, name, indexes);

            if(count == 0)
            {
                printf("Contact not found.\n");
                return;
            }

            printf("\nMatching Contacts:\n");

            printf("=====================================================================\n");
            printf("%-5s %-8s %-20s %-15s %-30s\n",
                   "S.No", "Index", "Name", "Phone", "Email");
            printf("=====================================================================\n");

            for(i = 0; i < count; i++)
            {
                printf("%-5d %-8d %-20s %-15s %-30s\n",
                       i + 1,
                       indexes[i],
                       addressBook->contacts[indexes[i]].name,
                       addressBook->contacts[indexes[i]].phone,
                       addressBook->contacts[indexes[i]].email);
            }

            printf("=====================================================================\n");

            if(count == 1)
            {
                index = indexes[0];
            }
            else
            {
                printf("Enter the index of the contact to delete: ");
                scanf("%d", &index);

                found = 0;

                for(i = 0; i < count; i++)
                {
                    if(indexes[i] == index)
                    {
                        found = 1;
                        break;
                    }
                }

                if(found == 0)
                {
                    printf("Invalid index.\n");
                    return;
                }
            }

            break;


        case 2:

            printf("Enter phone number: ");
            scanf("%19s", phone);

            index = searchByPhone(addressBook, phone);

            if(index == -1)
            {
                printf("Contact not found.\n");
                return;
            }

            break;


        case 3:

            printf("Enter email: ");
            scanf("%49s", email);

            index = searchByEmail(addressBook, email);

            if(index == -1)
            {
                printf("Contact not found.\n");
                return;
            }

            break;


        default:

            printf("Invalid choice.\n");
            return;
    }


    /* Shift contacts after the deleted contact */

    for(i = index; i < addressBook->contactCount - 1; i++)
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }

    addressBook->contactCount--;

    printf("Contact deleted successfully.\n");
}
