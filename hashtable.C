#include <iostream>
#include <string>
#include <cstring>
using namespace std;

// Hash table of (key, value) pairs
// T is the record type, K is the key type
// Each record type T must implement the
// following methods:
// K getKey()
// void setKey(K key)
// int getHashIndex(int numBuckets)
template<typename T, typename K>
class HashTable {
    int numBuckets;
    typedef struct node_st {
        T *record;
        struct node_st *next;
    } Node;
    Node **table;
public:
    HashTable(int numBuckets);

    void insert(T *newRecord);
    void remove(T *record);
    void print();
    T *find(K key);

    ~HashTable();
};

template<typename T, typename K>
HashTable<T, K>::HashTable(int numBuckets) {
    this->numBuckets = numBuckets;
    table = new Node*[numBuckets];
    memset(table, 0, numBuckets);
}

template<typename T, typename K>
HashTable<T, K>::~HashTable() {
    for (int i = 0; i < numBuckets; i++) {
        Node *node = table[i];
        while (node != NULL) {
            Node *tempNode = node;
            node = node->next;
            delete tempNode;
        }
    }
    delete table;
}

template<typename T, typename K>
void HashTable<T, K>::insert(T *newRecord) {
    int hashIndex = newRecord->getHashIndex(numBuckets); 
    Node **node = &table[hashIndex];

    while (*node != NULL) {
        if ((*node)->record == newRecord) {
            cout << "Record already present!\n";
            return;
        }
        node = &(*node)->next;
    }

    Node *newNode = new Node;
    newNode->next = NULL;
    newNode->record = newRecord;

    *node = newNode;

    cout << "Inserting record at index " << hashIndex << endl;
}

template<typename T, typename K>
void HashTable<T, K>::remove(T *record) {
    int hashIndex = record->getHashIndex(numBuckets); 
    Node **node = &table[hashIndex];
    int i = 0;

    while (*node != NULL) {
        if ((*node)->record == record) {
            cout << "Removing " << (*node)->record->getKey()
                 << " from index " << hashIndex
                 << " position " << i << endl;
            Node *tempNode = *node;
            *node = (*node)->next;
            delete tempNode;
            return;
        }
        i++;
        node = &(*node)->next;
    }
    
    cout << "Record not found!\n";
}

template<typename T, typename K>
void HashTable<T, K>::print() {
    for (int hashIndex = 0; hashIndex < numBuckets; hashIndex++) {
        Node *node = table[hashIndex];
        cout << "[" << hashIndex << "]->";
        while (node != NULL) {
            cout << "(" << node->record->printKey()
                 << "," << node->record->printValue()
                 << ")->";
            node = node->next;
        }
        cout << endl;
    }
}

template<typename T, typename K>
T *HashTable<T, K>::find(K key) {
    T tempRecord(key, "");
    int hashIndex = tempRecord.getHashIndex(numBuckets);
    Node **node = &table[hashIndex];
    int i = 0;

    while (*node != NULL) {
        if ((*node)->record->getKey() == key) {
            cout << (*node)->record->getKey()
                 << " found at index " << hashIndex
                 << " position " << i << endl;
            return (*node)->record;
        }
        node = &(*node)->next;
        i++;
    }
    
    cout << "Record not found!\n";
    return NULL;
}

class Record {
    string name;
    string address;
public:
    Record(string newName, string newAddress) {
        this->name = newName;
        this->address = newAddress;
    }

    string getKey() {
        return name;
    }

    void setKey(string key) {
        name = key;
    }

    int getHashIndex(int numBuckets) {
        int hashIndex = 0;
        for (int i = 0; i < name.size(); i++) {
            hashIndex += name[i];
        }
        return hashIndex % numBuckets;
    }

    string printKey() {
        return name;
    }

    string printValue () {
        return address;
    }
};

int main() {
    HashTable<Record, string> *hashTable = new HashTable<Record, string>(10);
    Record r1("Mayank", "Santa Clara");
    Record r2("Maitreyi", "Santa Clara");
    Record r3("Noodloo", "Santa Clara");
    Record r4("Popu", "Santa Clara");
    Record r5("Mishti", "Santa Clara");
    Record r6("Fuffin", "Santa Clara");

    Record r11("1Mayank", "Santa Clara");
    Record r22("2Maitreyi", "Santa Clara");
    Record r33("3Noodloo", "Santa Clara");
    Record r44("4Popu", "Santa Clara");
    Record r55("5Mishti", "Santa Clara");
    Record r66("6Fuffin", "Santa Clara");

    hashTable->insert(&r1);
    hashTable->insert(&r2);
    hashTable->insert(&r3);
    hashTable->insert(&r4);
    hashTable->insert(&r5);
    hashTable->insert(&r6);

    hashTable->print();

    hashTable->insert(&r11);
    hashTable->insert(&r22);
    hashTable->insert(&r33);
    hashTable->insert(&r44);
    hashTable->insert(&r55);
    hashTable->insert(&r66);

    hashTable->print();

    hashTable->find("Mayank");
    hashTable->find("Maitreyi");
    hashTable->find("Noodloo");
    hashTable->find("Popu");
    hashTable->find("Mishti");
    hashTable->find("Fuffin");

    hashTable->remove(&r11);
    hashTable->remove(&r22);
    hashTable->remove(&r33);
    hashTable->remove(&r44);
    hashTable->remove(&r55);
    hashTable->remove(&r66);

    hashTable->print();

    hashTable->insert(&r1);

    return 0;
}
