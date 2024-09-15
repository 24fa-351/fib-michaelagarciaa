#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>  // For uint32_t
#include <limits.h>  // For UINT32_MAX

// Function prototypes
uint32_t fib_r(int n);
uint32_t fib_i(int n);
uint32_t fib_r_wrapper(int n);
uint32_t fib_i_wrapper(int n);
uint32_t (*fib_func)(int n);

// Memoization array for recursive
uint32_t *memo_r = NULL;

// Memoization array for iterative
uint32_t *memo_i = NULL;

// Main program
int main(int argc, char *argv[]) {
    int input_number = atoi(argv[1]);
    char method = argv[2][0];
    char *filename = argv[3];

    // Open and read the file
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file.\n");
        return 1;
    }

    int file_number;
    fscanf(file, "%d", &file_number);
    fclose(file);

    int n = input_number + file_number;

    // Allocate memory for memoization arrays (if needed)
    memo_r = (uint32_t *)malloc((n + 1) * sizeof(uint32_t));
    memo_i = (uint32_t *)malloc((n + 1) * sizeof(uint32_t));

    // Initialize memoization arrays to an invalid value (UINT32_MAX indicates uncomputed)
    for (int i = 0; i <= n; i++) {
        memo_r[i] = UINT32_MAX;
        memo_i[i] = UINT32_MAX;
    }

    uint32_t fibonacci_result;

    // Function pointer setup for recursive or iterative methods
    if (method == 'r') {
        fib_func = fib_r;
    } else if (method == 'i') {
        fib_func = fib_i;
    } else {
        printf("Error: Unknown method '%c'.\n", method);
        free(memo_r);
        free(memo_i);
        return 1;
    }

    // Call the appropriate Fibonacci function
    fibonacci_result = fib_func(n);

    if (fibonacci_result == UINT32_MAX) {
        printf("The Fibonacci number is too large to calculate with 'uint32_t'.\n");
    } else {
        printf("The %dth Fibonacci number is: %u\n", n, fibonacci_result);
    }

    // Free memoization arrays
    free(memo_r);
    free(memo_i);

    return 0;
}

// Memoized recursive Fibonacci function
uint32_t fib_r(int n) {
    if (n <= 1) {
        return n;
    }

    // Return the cached value if already computed
    if (memo_r[n] != UINT32_MAX) {
        return memo_r[n];
    }

    // Otherwise, compute the value and store it in the cache
    memo_r[n] = fib_r_wrapper(n - 1) + fib_r_wrapper(n - 2);
    return memo_r[n];
}

// Wrapper for the original recursive function
uint32_t fib_r_wrapper(int n) {
    if (n <= 1) {
        return n;
    }
    return fib_r_wrapper(n - 1) + fib_r_wrapper(n - 2);
}

// Memoized iterative Fibonacci function
uint32_t fib_i(int n) {
    if (n <= 1) {
        return n;
    }

    // Return the cached value if already computed
    if (memo_i[n] != UINT32_MAX) {
        return memo_i[n];
    }

    // Compute and store the Fibonacci values iteratively
    memo_i[n] = fib_i_wrapper(n);
    return memo_i[n];
}

// Wrapper for the original iterative function
uint32_t fib_i_wrapper(int n) {
    if (n <= 1) {
        return n;
    }

    uint32_t first = 0, second = 1, next_number;
    for (int index = 2; index <= n; index++) {
        if (UINT32_MAX - second < first) {
            return UINT32_MAX;  // Overflow detected
        }
        next_number = first + second;
        first = second;
        second = next_number;
    }
    return second;
}
