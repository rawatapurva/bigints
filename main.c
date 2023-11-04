#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arithmetic.h"

int main() {
	int i;
    char num1_str[1000], num2_str[1000];
    struct Node* num1 = NULL;
    struct Node* num2 = NULL;
    struct Node* result = NULL;
    int choice;

    printf("Enter the first big integer: ");
    scanf("%s", num1_str);
    printf("Enter the second big integer: ");
    scanf("%s", num2_str);

    for ( i = strlen(num1_str) - 1; i >= 0; i--) {
        int digit = num1_str[i] - '0';
        insertAtEnd(&num1, digit);
    }

    for (i = strlen(num2_str) - 1; i >= 0; i--) {
        int digit = num2_str[i] - '0';
        insertAtEnd(&num2, digit);
    }

    while (1) {
        printf("\nMenu:\n");
        printf("1. Add\n");
        printf("2. Subtract\n");
        printf("3. Multiply\n");
        printf("4. Divide\n");
        printf("5. Modulus\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                result = addBigIntegers(num1, num2);
                printf("Sum of the two big integers: ");
                printList(result);
                freeList(result);
                break;

            case 2:
                result = subtractBigIntegers(num1, num2);
                printf("Difference of the two big integers: ");
                printList(result);
                freeList(result);
                break;

            case 3:
                result = multiplyBigIntegers(num1, num2);
                printf("Product of the two big integers: ");
                printList(result);
                freeList(result);
                break;

            case 4:
                result = divideBigIntegers(num1, num2);
                printf("Division of the two big integers: ");
                printList(result);
                freeList(result);
                break;

            case 5:
                result = modulusBigIntegers(num1, num2);
                printf("Modulus of the two big integers: ");
                printList(result);
                freeList(result);
                break;

            case 6:
                // Free memory for num1 and num2
                freeList(num1);
                freeList(num2);
                exit(0);

            default:
                printf("Invalid choice. Please select a valid option.\n");
        }
    }

    return 0;
}

