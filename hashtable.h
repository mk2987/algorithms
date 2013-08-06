#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

typedef struct hashTableNode_st {
    const char *key;
    unsigned long long value;
    struct hashTableNode_st *next;
} *HashTableNode;

struct {
    HashTableNode *table;
    unsigned long long numBuckets;
    unsigned long long numEntries;
} hashTable;

// Prime number usually
#define HASHTABLE_INITIAL_BUCKETS 5

#endif
