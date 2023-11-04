#ifndef ARITHMETIC_H
#define ARITHMETIC_H
struct Node {
    int data;
    struct Node* next;
};


void insertAtEnd(struct Node **head, int data);
void reverseList(struct Node **head);
void printList(struct Node *head);
void freeList(struct Node *head);
int compareBigIntegers(struct Node* num1, struct Node* num2);
struct Node* addBigIntegers(struct Node* num1, struct Node* num2);
struct Node* subtractBigIntegers(struct Node* num1, struct Node* num2);
struct Node* multiplyBigIntegers(struct Node* num1, struct Node* num2);
struct Node* divideBigIntegers(struct Node* num1, struct Node* num2);
struct Node* modulusBigIntegers(struct Node* num1, struct Node* num2);
#endif
