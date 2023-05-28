# File Access Management System

This repository contains the implementation of a file access management system in C++. The system uses a **hash table** to store file information and a **priority queue** to manage file access requests from users.

## Files

The repository includes the following files:

1. `Driver.cpp`: The main driver program that provides a menu-based interface for interacting with the file access management system.
2. `Project.cpp`: Contains the implementation of classes and functions used in the file access management system.
3. `Project.h`: Header file containing the class and function declarations used in the system.

## Usage

To use the file access management system, follow these steps:

1. Clone the repository to your local machine.
2. Compile the source code files using a C++ compiler.
3. Execute the compiled program.

The program will display a menu with several options:

- **Load data from file (Option 1):** This option loads file data from a text file named `file.txt` and populates the hash table.
- **Print the hash table (Option 2):** This option prints the contents of the hash table, displaying the files and users accessing them.
- **Request file access (Option 3):** This option allows a user to request access to a file by providing the user ID, access type (reading or writing), and priority.
- **Release file access (Option 4):** This option releases the file access for a user by removing them from the corresponding file's user list.
- **Insert a file (Option 5):** This option allows you to manually insert a new file into the system by providing the file ID and user access information.
- **Delete a file (Option 6):** This option deletes a file from the system by removing it from the hash table.
- **Exit program (Option 0):** This option terminates the program.

Choose the desired option by entering the corresponding number and follow the prompts to perform the specified operation.

## Notes

- The file access management system uses a hash table to store file information. Each file is represented by a `fileNode` object, which contains the file ID, a priority queue (`pQueue`) of users waiting for access, and a vector of users currently accessing the file.
- The `pQueue` class is a template-based priority queue that handles user information based on priority.
- The `repositoryOfFiles` class manages the hash table and provides functions to load data, print the table, search for files, insert files, and delete files.
- The program reads file data from a text file named `file.txt`. Make sure to format the file properly with each line containing the file ID, user ID, priority, and access type.
- The program uses simple console input/output for interaction.

Please note that this project has a specific scope.
