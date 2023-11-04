#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arithmetic.h"
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->next = NULL;
    return node;
}
void insertAtEnd(struct Node** head, int data) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = data;
    temp->next = NULL;
    if (*head == NULL) {
        *head = temp;
    } else {
        struct Node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = temp;
    }
}

void reverseList(struct Node** head) {
    struct Node* prev = NULL;
    struct Node* current = *head;
    struct Node* next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
}

void printList(struct Node* head) {
    while (head != NULL) {
        printf("%d", head->data);
        head = head->next;
    }
    printf("\n");
}


void freeList(struct Node* head) {
    while (head != NULL) {
        struct Node* temp = head;
        head = head->next;
        free(temp);
    }
}

int compareBigIntegers(struct Node* num1, struct Node* num2) {
    // Compare two linked lists representing big integers
    while (num1 != NULL && num2 != NULL) {
        if (num1->data > num2->data) {
            return 1;
        } else if (num1->data < num2->data) {
            return -1;
        }
        num1 = num1->next;
        num2 = num2->next;
    }

    if (num1 != NULL) {
        return 1;
    } else if (num2 != NULL) {
        return -1;
    }

    return 0;
}

struct Node* addBigIntegers(struct Node* num1, struct Node* num2) {
    struct Node* result = NULL;
    int carry = 0;

    while (num1 != NULL || num2 != NULL || carry) {
        int sum = carry;
        if (num1 != NULL) {
            sum += num1->data;
            num1 = num1->next;
        }
        if (num2 != NULL) {
            sum += num2->data;
            num2 = num2->next;
        }
        carry = sum / 10;
        sum %= 10;
        insertAtEnd(&result, sum);
    }

    reverseList(&result); // Reverse before returning
    return result;
}

struct Node* subtractBigIntegers(struct Node* num1, struct Node* num2) {
    struct Node* result = NULL;
    int borrow = 0;

    while (num1 != NULL || num2 != NULL) {
        int diff = borrow;
        if (num1 != NULL) {
            diff += num1->data;
            num1 = num1->next;
        }
        if (num2 != NULL) {
            diff -= num2->data;
            num2 = num2->next;
        }
        if (diff < 0) {
            diff += 10;
            borrow = -1;
        } else {
            borrow = 0;
        }
        insertAtEnd(&result, diff);
    }

    // Remove leading zeros
    while (result != NULL && result->data == 0) {
        struct Node* temp = result;
        result = result->next;
        free(temp);
    }

    reverseList(&result); // Reverse before returning
    return result;
}

struct Node* multiplyBigIntegers(struct Node* num1, struct Node* num2) {
	int i;
    struct Node* result = newNode(0); // Initialize result with 0

    if (num1 == NULL || num2 == NULL) {
        return result;
    }

    struct Node* temp1 = num1;

    while (temp1 != NULL) {
        int carry = 0;
        struct Node* tempResult = newNode(0);
        struct Node* temp2 = num2;
        int position = 0;

        while (temp2 != NULL || carry) {
            int digit1 = temp1->data;
            int digit2 = (temp2 != NULL) ? temp2->data : 0;
            int product = (digit1 * digit2) + carry;
            carry = product / 10;
            insertAtEnd(&tempResult, product % 10);

            if (temp2 != NULL) {
                temp2 = temp2->next;
            }
        }

        // Add the temporary result to the overall result, shifting it appropriately
        for ( i = 0; i < position; i++) {
            insertAtEnd(&tempResult, 0);
        }

        result = addBigIntegers(result, tempResult);

        position++;
        temp1 = temp1->next;
    }

    return result;
}






struct Node* divideBigIntegers(struct Node* num1, struct Node* num2) {
    struct Node* result = newNode(0);

    // Ensure num2 is not zero (division by zero)
    if (num2 == NULL || (num2->data == 0 && num2->next == NULL)) {
        printf("Division by zero is not allowed.\n");
        return result;
    }

    struct Node* currentQuotient = NULL;
    struct Node* currentDividend = NULL;

    while (num1 != NULL) {
        int quotientDigit = 0;

        // Append a digit from num1 to the current dividend
        insertAtEnd(&currentDividend, num1->data);

        // While the current dividend is greater than or equal to num2, subtract num2 from it
        while (compareBigIntegers(currentDividend, num2) >= 0) {
            currentDividend = subtractBigIntegers(currentDividend, num2);
            quotientDigit++;
        }

        // Append the quotientDigit to the result
        insertAtEnd(&currentQuotient, quotientDigit);

        num1 = num1->next;
    }

    // Remove leading zeros from the quotient
    while (currentQuotient != NULL && currentQuotient->data == 0) {
        struct Node* temp = currentQuotient;
        currentQuotient = currentQuotient->next;
        free(temp);
    }

    // Reverse the quotient
    reverseList(&currentQuotient);

    return currentQuotient;
}



struct Node* modulusBigIntegers(struct Node* num1, struct Node* num2) {
    struct Node* tempResult = divideBigIntegers(num1, num2);

    if (tempResult == NULL) {
        return NULL;
    }

    struct Node* result = multiplyBigIntegers(tempResult, num2);
    struct Node* remainder = subtractBigIntegers(num1, result);

    return remainder;
}
