#include "hash_table.h"

unsigned int hash_function(char *key)
{
    unsigned int hash_key = 0;
    size_t key_len = strlen(key);

    for (int i = 0; i < key_len; i++)
        hash_key = ((hash_key + key[i]) * key[i]) % TABLE_SIZE;

    return hash_key;
}

bool insert_element(Case **Hash_Table, char *key, char *value)
{
    int hash_key, i;
    Case *element;

    if (!key || !Hash_Table || !value)
        return false;
    element = malloc(sizeof(Case));
    if (!element)
        return false;

    element->value = strdup(value);
    element->key = strdup(key);
    hash_key = hash_function(key);

    if (!Hash_Table[hash_key])
    {
        Hash_Table[hash_key] = element;
        return true;
    }
    else
    {
        if (!strcmp(key, Hash_Table[hash_key]->key))
        {
            free(Hash_Table[hash_key]->value);
            Hash_Table[hash_key]->value = element->value;
            free(element->key);
            free(element);
            return true;
        }
        i = 1;
        while (i < TABLE_SIZE)
        {
            hash_key = (hash_key + i++) % TABLE_SIZE;
            if (!Hash_Table[hash_key] || !strcmp(key, Hash_Table[hash_key]->key))
            {
                if (Hash_Table[hash_key])
                    free(Hash_Table[hash_key]->value);
                Hash_Table[hash_key] = element;
                return true;
            }
        }
        free(element->key);
        free(element->value);
        free(element);
        return false;
    }
}

bool delete_element(Case **Hash_Table, char *key)
{
    int hash_key, i;

    if (!key || !Hash_Table)
        return false;
    hash_key = hash_function(key);

    i = 0;
    while (i < TABLE_SIZE)
    {
        if (Hash_Table[hash_key] && !strcmp(Hash_Table[hash_key]->key, key))
        {
            free(Hash_Table[hash_key]->key);
            free(Hash_Table[hash_key]->value);
            free(Hash_Table[hash_key]);
            Hash_Table[hash_key] = NULL;
            return true;
        }
        hash_key = (hash_key + i++) % TABLE_SIZE;
    }
    return false;
}

void read_table(Case **Hash_Table)
{
    if (!Hash_Table)
        return ;
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if (Hash_Table[i])
            printf("[%d] %s : %s\n", i, Hash_Table[i]->key, Hash_Table[i]->value);
    }
}

void clear_table(Case **Hash_Table)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if (Hash_Table[i])
        {
            free(Hash_Table[i]->key);
            free(Hash_Table[i]->value);
            free(Hash_Table[i]);
            Hash_Table[i] = NULL;
        }
    }
    free(Hash_Table);
}
int main()
{

    Case **Hash_Table = calloc(TABLE_SIZE, sizeof(Case *));

    if (!Hash_Table)
        return 1;

    insert_element(Hash_Table, "Morocco", "Rabat");
    insert_element(Hash_Table, "France", "Paris");
    insert_element(Hash_Table, "America", "Washington");
    insert_element(Hash_Table, "France", "NICE");
    read_table(Hash_Table);

    delete_element(Hash_Table, "France");
    read_table(Hash_Table);
    clear_table(Hash_Table);

    return 0;
}
