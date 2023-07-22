#include <stdio.h>

int binary_search_asm(const int *arr, int size, int target) {
    int result;

    __asm__ (
        "xor %%eax, %%eax\n"          // Initialize result to -1
        "mov $0, %%ecx\n"             // Initialize low index to 0
        "mov %1, %%edx\n"             // Load the array size into edx
        "dec %%edx\n"                 // Adjust the array length for 0-based indexing

    "binary_search_loop:\n"
        "cmp %%ecx, %%edx\n"         // Compare low index and high index
        "jl binary_search_not_found\n" // If low index > high index, jump to not_found

        "mov %%ecx, %%eax\n"         // Calculate the middle index
        "add %%edx, %%eax\n"
        "shr $1, %%eax\n"            // Right-shift by one (divide by 2)

        "mov (%%rsi, %%rax, 4), %%ebx\n" // Load the middle element into ebx
        "cmp %2, %%ebx\n"            // Compare the middle element with the target element
        "je binary_search_found\n"   // If they are equal, jump to found
        "jg binary_search_search_left\n" // If the middle element is greater, jump to search_left

    "binary_search_search_right:\n"
        "inc %%ecx\n"                // Search the right half of the array (low index = middle index + 1)
        "jmp binary_search_loop\n"   // Repeat the search loop

    "binary_search_search_left:\n"
        "dec %%eax\n"                // Search the left half of the array (high index = middle index - 1)
        "jmp binary_search_loop\n"   // Repeat the search loop

    "binary_search_found:\n"
        "ret\n"                      // Return with the index of the target element in eax

    "binary_search_not_found:\n"
        "mov $-1, %%eax\n"           // Element not found, return -1 in eax
        "ret\n"                      // Return

    : [result] "=a" (result)        // Output: result in eax
    : [arr] "S" (arr), [size] "c" (size), [target] "d" (target) // Input: arr in rsi, size in rcx, target in rdx
    : "ebx", "memory", "cc"
    );

    return result;
}

int main() {
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int arr_len = sizeof(array) / sizeof(array[0]);
    int target = 6;

    int result = binary_search_asm(array, arr_len, target);

    if (result != -1) {
        printf("Target element %d found at index %d.\n", target, result);
    } else {
        printf("Target element %d not found.\n", target);
    }

    return 0;
}

