#include <stdio.h>
#include "file.h"
#include "contact.h"

void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fptr;
    int i;

    fptr = fopen("contact.txt", "w");

    if(fptr == NULL)
    {
        printf("Unable to open file.\n");
        return;
    }

    fprintf(fptr, "%d\n", addressBook->contactCount);

    for(i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fptr, "%s,%s,%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    fclose(fptr);

    printf("Contacts saved successfully.\n");
}

void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fptr;
    int i;

    fptr = fopen("contact.txt", "r");

    if(fptr == NULL)
    {
        printf("File not found.\n");
        addressBook->contactCount = 0;
        return;
    }

    fscanf(fptr, "%d", &addressBook->contactCount);

    for(i = 0; i < addressBook->contactCount; i++)
    {
        fscanf(fptr, " %[^,],%[^,],%[^\n]",
        addressBook->contacts[i].name,
        addressBook->contacts[i].phone,
        addressBook->contacts[i].email);
    }

    fclose(fptr);
}
