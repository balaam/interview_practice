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
        _value(NULL)
        {}
    ~Node() {}

    Node* Next() const { return _next; }
    void* Value() { return _value; }

    void SetNext(Node* n) { _next = n; }
    void SetValue(void* v) { _value = v; }

private:
    Node*   _next;
    void*   _value;
};

Node* DeleteNode(Node* startNode, Node* toDelete)
{
    if(startNode == NULL || toDelete == NULL)
    {
        return startNode;
    }

    if(startNode == toDelete)
    {
        Node* next = startNode->Next();
        delete startNode;
        startNode = NULL;
        return next;
    }

    // otherwise do a linear search
    // keeping track of the prevNode

    Node* prevNode = startNode;
    Node* currNode = startNode->Next();

    while(currNode != NULL
          && currNode != toDelete)
    {
        Node* next = currNode->Next();
        prevNode = currNode;
        currNode = next;
    }

    // Either detected or failed to find
    if(currNode == NULL)
    {
        // Failed to find.
        return startNode;
    }

    // Found and need to remove
    Node* next = currNode->Next();
    prevNode->SetNext(next);
    delete currNode;

    return startNode;
}



int main()
{
    Node* head = new Node();
    head->SetValue((void*)"Hello");
    Node* goodbyeNode = new Node();
    head->SetNext(goodbyeNode);
    head->Next()->SetValue((void*)"Goodbye");
    char* dataAsStr = (char*)head->Next()->Value();
    printf("%s\n", dataAsStr);

    Node* firstNode = DeleteNode(head, head);

    if(firstNode==NULL)
    {
        printf("After deleting a node. The link list is empty.\n");
    }
    else
    {
        printf("After deleting node. First Node is %s\n", (const char*)firstNode->Value());
    }

    head = new Node();
    head->SetValue((void*)"New Hello");

    firstNode->SetNext(head);
    printf("After adding node back:\n"
           "First Node is %s\n"
           "Next Node is %s\n",
           (const char*)firstNode->Value(),
           (const char*)firstNode->Next()->Value());

    printf("Deleting second node\n");

    firstNode = DeleteNode(firstNode, head);
    printf("After deleting node."
           "First Node is %s\n"
           "Second Node is %s\n",
           (const char*)firstNode->Value(),
           (const char*)firstNode->Next()?"Not null (mistake)":"Null");

    return 0;
}