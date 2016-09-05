#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

//  g++ main.cpp -o main

// Node to represent a LinkList
class Node
{
public:
    Node() :
        _next(NULL),
        _value(NULL),
        _key("")
        {}
    ~Node() {}

    Node* Next() const { return _next; }
    void* Value() { return _value; }

    const char* Key() { return _key.c_str(); }

    void SetNext(Node* n) { _next = n; }
    void SetValue(void* v) { _value = v; }
    void SetKey(const char* key) { _key.assign(key); }

private:
    Node*   _next;
    void*   _value;
    std::string _key; // use this for the copy ctor
};

class HashTable
{
    static const int ARRAY_SIZE = 1024;
public:
    HashTable() {}

    // djb2
    unsigned long Hash(const unsigned char *str)
    {
        unsigned long hash = 5381;
        int c;

        while ((c = *str++))
        {
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
        }

        return hash;
    }

    // Will silently replace existing values
    void Add(const char* key, void* value)
    {
        // truncated to int
        int index = (int) Hash((const unsigned char*)key) % ARRAY_SIZE;

        printf("[%s] has hash [%d]\n", key, index);

        if(_data[index].Value() == NULL
           || strcmp (_data[index].Key(), key) == 0)
        {
            _data[index].SetKey(key);
            _data[index].SetValue(value);
        }
        else
        {
            printf("Collision\n");
            Node* cursor = &_data[index];

            // You also need to check for the key
            // being already added.

            while(cursor->Next() != NULL)
            {
                cursor = cursor->Next();

                // Replace existing value if
                // key matches
                if(strcmp(cursor->Key(), key) == 0)
                {
                    printf("Replacing existing key\n");
                    cursor->SetValue(value);
                    return;
                }
            }

            printf("Adding key on the end\n");
            // We're at the end
            Node* n = new Node();
            n->SetValue(value);
            n->SetKey(key);
            cursor->SetNext(n);
        }
    };

    void Remove(const char* key)
    {
        // if it's the head null it
        int index = (int) Hash((const unsigned char*)key) % ARRAY_SIZE;
        Node* cursor = &_data[index];

        if(strcmp(cursor->Key(), key) == 0)
        {
            cursor->SetValue(NULL);
            cursor->SetKey("");

            // should really move any linked list
            // stuff down one

            return;
        }


        // if it's in the linked list, it should
        // really be remove properly
    }

    void* Get(const char* key)
    {
        int index = (int) Hash((const unsigned char*)key) % ARRAY_SIZE;

        if(_data[index].Value() == NULL)
        {
            return NULL;
        }
        else
        {
            Node* cursor = &_data[index];
            while(cursor->Next() != NULL
                  && (strcmp(cursor->Key(), key) != 0))
            {
                cursor = cursor->Next();
            }

            if(strcmp(cursor->Key(), key) == 0)
            {
                return cursor->Value();
            }
            else
            {
                return NULL;
            }
        }
    }

private:
    Node _data[ARRAY_SIZE];
};

int main()
{
    Node head;
    head.SetValue((void*)"Hello");
    head.SetNext(new Node());
    head.Next()->SetValue((void*)"Goodbye");
    char* dataAsStr = (char*)head.Next()->Value();
    printf("%s\n", dataAsStr);

    HashTable table;

    // Try and get a key that doesn't exist
    void* value = table.Get("test");
    if(value == NULL)
    {
        printf("When trying to get a key that doesn't exist we got NULL.\n");
    }
    else
    {
        printf("Something went wrong.\n");
    }

    printf("Yo.\n");
    const char* collision1 = "FYFYFYEzFYFYFYEzFYEzFYFYFYFYFY";
    const char* collision2 = "EzFYEzEzEzFYFYFYFYEzEzFYEzEzFY";
    printf("Ho\n");

    printf("Add c1");
    table.Add(collision1, (void*) "This is a test string.");
    printf("Add c2");
    table.Add(collision2, (void*) "This is a test string 2.");
    table.Add("t0xxw", (void*) "This is a test string 3.");

    printf("%s -> %s\n", collision1, (const char*)table.Get(collision1));
    printf("%s -> %s\n", collision2, (const char*)table.Get(collision2));
    printf("%s -> %s\n", "t0xxw", (const char*)table.Get("t0xxw"));

    return 0;
}