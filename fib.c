#include <stdio.h>
#include <stdlib.h>

unsigned long long fibonacci_recursive(int n);
unsigned long long fibonacci_iterative(int n);

int main(int argc, char *argv[]) {
    int input_number = atoi(argv[1]);  
    char method = argv[2][0];          
    char *filename = argv[3];          

 
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file.\n");
        return 1;
    }

    int file_number;
    fscanf(file, "%d", &file_number);
    fclose(file);  

    int n = input_number + file_number;

    unsigned long long fibonacci_result;
    if (method == 'r') {
        fibonacci_result = fibonacci_recursive(n);
    } else if (method == 'i') {
        fibonacci_result = fibonacci_iterative(n);
    } else {
        printf("Error: Unknown method '%c'.\n", method);
        return 1;
    }

    printf("The %dth Fibonacci number is: %llu\n", n, fibonacci_result);

    return 0;
}

unsigned long long fibonacci_recursive(int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
}

unsigned long long fibonacci_iterative(int n) {
    if (n <= 1) {
        return n;
    }

    unsigned long long first = 0, second = 1, next_number;
    for (int index = 2; index <= n; index++) {
        next_number = first + second;
        first = second;
        second = next_number;
    }
    return second;
}
