#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hashtable.h"

static void
hashTableResize()
{
    HashTableNode *table = calloc(hashTable.numBuckets * 2, sizeof (void*));

}

static unsigned long long
hashApply(const char *key)
{
    unsigned long long hash = 3;
    int i = 0;

    for (i = 0; i < strlen(key); i++) {
        // Multiply hash by 31
        hash += hash << 5 - hash + key[i];
    }

    return hash % hashTable.numBuckets;
}

unsigned long long
hashTablePrint()
{
    int i;
    HashTableNode node;

    for (i = 0; i < hashTable.numBuckets; i++) {
        node = hashTable.table[i];
        fprintf(stderr, "table[%03d]:", i);

        while(node != NULL)
            fprintf(stderr, "(%s,%llu), ", node->key, node->value);

        fprintf(stderr, "\n");
    }

    return 0;
}

unsigned long long
hashTableLookup(const char *key)
{
    unsigned long long index;
    HashTableNode node;

    index = hashApply(key);
    node = hashTable.table[index];

    while (node != NULL) {
        if (node->key == key)
            return node->value;

        node = node->next;
    }

    fprintf(stderr, "Key not present in hash table\n");

    return -1;
}

static void
hashTableDoInsert(const char *key, unsigned long long value)
{
    unsigned long long index;
    HashTableNode newNode;
    HashTableNode node;

    // Initialize the hash table if needed.
    if (hashTable.numBuckets == 0) {
        hashTable.table = calloc(HASHTABLE_INITIAL_BUCKETS, sizeof (void *));
        hashTable.numBuckets = HASHTABLE_INITIAL_BUCKETS;
    }

    index = hashApply(key);
    node = hashTable.table[index];

    if (node != NULL) {
        // Make sure the key isn't already present
        // This will ensure they key isn't entered multiple times.
        // O(n/k) average, where n/k is the load factor.
        while (node != NULL) {
            if (node->key == key) {
                fprintf(stderr, "Key %s already present with value %llu, ignoring\n",
                        key, node->value);
                return;
            }
            node = node->next;
        }
    }

    node = hashTable.table[index];
    newNode = malloc(sizeof *node);
    newNode->key = key;
    newNode->value = value;
    newNode->next = node;
    hashTable.table[index] = newNode;
    hashTable.numEntries++;
}

void
hashTableInsert(const char *key, unsigned long long value)
{
    hashTableDoInsert(key, value);

    if ((float)hashTable.numEntries / hashTable.numBuckets > 0.75) {
        hashTableResize();
    }
}

void
hashTableDelete(const char *key)
{
    unsigned long long index;
    HashTableNode node, slowNode;

    if (hashTable.numBuckets == 0) {
        fprintf(stderr, "Hash table empty, nothing to delete\n");
        return;
    }

    index = hashApply(key);
    node = hashTable.table[index];
    slowNode = hashTable.table[index];

    while (node != NULL) {
        if (node->key == key) {
            if (slowNode == node)
                // first node being removed
                hashTable.table[index] = node->next;
            else
                slowNode->next = node->next;

            free(node);
            hashTable.numEntries--;

            return;
        }
        slowNode = node;
        node = node->next;
    }

    fprintf(stderr, "Key not present, nothing to delete\n");
}
