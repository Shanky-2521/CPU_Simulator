#include <stdio.h>

// Global variable to track recursive call count
static int recursive_call_count = 0;

// Recursive factorial function
int factorial(int n) {
    // Increment recursive call counter
    recursive_call_count++;

    // Base case
    if (n <= 1) {
        return 1;
    }

    // Recursive case
    return n * factorial(n - 1);
}

int main() {
    int number = 5;
    int result = factorial(number);

    printf("Factorial of %d is %d\n", number, result);
    printf("Number of recursive calls: %d\n", recursive_call_count);

    return 0;
}
