# Hash Table Implementation in C

## Description

This project is a simple implementation of a hash table in C. It demonstrates how to store, retrieve, and delete key-value pairs using a hash function. Two methods are implemented to handle collisions: linear probing and chaining with linked lists.

## Features

- **Hash Function:** Generates a hash key based on the ASCII values of characters in the key.
- **Collision Handling:**
  - **Linear Probing:** Searches for the next available slot in case of a collision.
  - **Chaining (Linked Lists):** Stores multiple elements in the same index using linked lists.
- **Insertion:** Adds a key-value pair to the hash table.
- **Deletion:** Removes a key-value pair from the hash table.
- **Reading:** Prints all elements of the hash table.
- **Clearing:** Frees all allocated memory and resets the table.

## Files

- `hash_table.h`: Header file containing the structure definitions.
- `/*.c`: Contains the main logic and function implementations.

## Data Structures

```c
typedef struct Case {
    char *key;
    char *value;
    struct Case *next;
} Case;
```

## Functions

- `hash_function`: Computes the hash key for a given string.
- `insert_element`: Inserts a key-value pair into the hash table, using either linear probing or chaining.
- `delete_element`: Deletes a key-value pair from the hash table.
- `read_table`: Reads and prints the contents of the hash table.
- `clear_table`: Clears the entire hash table and frees memory.

## Example Usage

```c
Case **Hash_Table = calloc(TABLE_SIZE, sizeof(Case *));
insert_element(Hash_Table, "Morocco", "Rabat");
insert_element(Hash_Table, "France", "Paris");
read_table(Hash_Table);
delete_element(Hash_Table, "France");
read_table(Hash_Table);
clear_table(Hash_Table);
```

## Compilation and Execution

```bash
gcc -o hash_table main.c
./hash_table
```

## Future Improvements

- Handle dynamic resizing of the table.
- Implement a more robust hash function.
- Optimize collision resolution strategies.

## License

This project is open-source and free to use.

---

