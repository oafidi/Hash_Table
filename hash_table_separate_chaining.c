#include "hash_table.h"

Case *lst_findNodeWithPrev(Case *head, char *key, Case **prev) {
    Case *current = head;
    *prev = NULL;

    while (current != NULL) {
        if (!strcmp(current->key, key)) {
            return current;
        }
        *prev = current;
        current = current->next;
    }
    return NULL;
}

void lst_deleteNode(Case **head, char *key) {
    Case *temp = *head;
    Case *prev = NULL;

    if (temp != NULL && !strcmp(temp->key, key)) {
        *head = temp->next;
        free(temp->value);
        free(temp->key);
        free(temp);
        return;
    }
    while (temp != NULL && strcmp(temp->key, key)) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("No element in the table has the key %s \n", key);
        return;
    }
    prev->next = temp->next;
    free(temp->value);
    free(temp->key);
    free(temp);
}

unsigned int hash_function(char *key) {
    unsigned int hash_key = 0;
    size_t key_len = strlen(key);

    for (int i = 0; i < key_len; i++) {
        hash_key = ((hash_key + key[i]) * key[i]) % TABLE_SIZE;
    }
    return hash_key;
}

bool insert_element(Case **Hash_Table, char *key, char *value) {
    int hash_key;
    Case *element, *Node, *prev;

    if (!key || !value)
        return false;

    element = malloc(sizeof(Case));
    if (!element)
        return false;

    element->key = strdup(key);
    element->value = strdup(value);
    element->next = NULL;

    hash_key = hash_function(key);

    if (!Hash_Table[hash_key]) {
        Hash_Table[hash_key] = element;
        return true;
    }
    Node = lst_findNodeWithPrev(Hash_Table[hash_key], key, &prev);
    if (Node) {
        free(Node->value);
        Node->value = strdup(value);
        free(element->key);
        free(element);
        return true;
    } else {
        element->next = Hash_Table[hash_key];
        Hash_Table[hash_key] = element;
        return true;
    }
}

void delete_element(Case **Hash_Table, char *key) {
    if (!key || !Hash_Table)
        return;
    int hash_key = hash_function(key);
    lst_deleteNode(&Hash_Table[hash_key], key);
}

void read_table(Case **Hash_Table) {
    char *c = " ";
    Case *temp;

    printf("[");
    for (int i = 0; i < TABLE_SIZE; i++) {
        temp = Hash_Table[i];
        while (temp) {
            printf("%s%s:%s", c, temp->key, temp->value);
            c = ", ";
            temp = temp->next;
        }
    }
    printf(" ]");
}

void clear_table(Case **Hash_Table) {
    Case *temp, *next;

    for (int i = 0; i < TABLE_SIZE; i++) {
        temp = Hash_Table[i];
        while (temp) {
            next = temp->next;
            free(temp->value);
            free(temp->key);
            free(temp);
            temp = next;
        }
        Hash_Table[i] = NULL;
    }
    free(Hash_Table);
}

int main() {
    Case **Hash_Table = calloc(TABLE_SIZE, sizeof(Case *));

    if (!Hash_Table)
        return 1;

    insert_element(Hash_Table, "Morocco", "Rabat");
    insert_element(Hash_Table, "France", "Paris");
    insert_element(Hash_Table, "America", "Washington");
    printf("Before deletion:\n");
    read_table(Hash_Table);

    delete_element(Hash_Table, "France");
    printf("\nAfter deletion:\n");
    read_table(Hash_Table);

    clear_table(Hash_Table);
    return 0;
}
