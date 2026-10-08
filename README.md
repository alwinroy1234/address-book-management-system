# Address Book Management System

A console-based Address Book Management System developed in C for managing contact information with persistent file storage.

## Features

- Create new contacts
- Search contacts by name, phone number, or email
- Edit existing contacts
- Delete contacts
- List all contacts
- Validate names, phone numbers, and email addresses
- Prevent duplicate phone numbers
- Save contacts to a file
- Load existing contacts when the program starts

## Technologies & Concepts

- C Programming
- Structures
- Functions
- Pointers
- Arrays
- String Handling
- File Handling
- Modular Programming
- Input Validation

## Project Structure

| File | Description |
|---|---|
| `main.c` | Main program and menu handling |
| `contact.c` | Contact creation, search, edit, delete and validation functions |
| `contact.h` | Contact structures and function declarations |
| `file.c` | File save and load operations |
| `file.h` | File handling function declarations |
| `contact.txt` | Persistent contact data |

## Compilation

```bash
gcc main.c contact.c file.c -o address_book
```
## Run
```bash
./address_book
```

