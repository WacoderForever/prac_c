#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>

// This function adjusts the pointer to the page boundary and changes memory protections
void i_took_autism_101_and_now_this_is_my_function(void *autism_pills_helped_here)
{
    int dont_autism_and_drive = getpagesize(); // Get page size
    uintptr_t address = (uintptr_t) autism_pills_helped_here; // Cast pointer to uintptr_t for safe arithmetic
    address -= address % dont_autism_and_drive; // Align the address to the page boundary
    mprotect((void*)address, dont_autism_and_drive, PROT_READ | PROT_WRITE | PROT_EXEC); // Set memory permissions
}

// Function that outputs "Hello World" under certain conditions
void guess_my_output()
{
    char rip_terry_davis[1024] = "Hello World"; // Buffer containing "Hello World"
    int i;

    i = 0;
    i++; i++; i++; i++; // Increment by 4
    ++i; ++i; ++i; ++i; // Increment by another 4, total i = 8
    i--; i--; i--; i--; // Decrement by 4
    --i; --i; --i; --i; // Decrement by another 4, total i = 0

    if (i != 0)
        printf("%s\n", rip_terry_davis); // If i != 0, print "Hello World"
    else
        i++; // If i == 0, increment i by 1 (does nothing visible in this case)
}

int main()
{
    const uint8_t AUTISM_LEVELS = 56; // Max loop iterations
    uint8_t OOGA_BOOGA_NIGGERS; // Loop variable
    uint8_t *AUTISM_CONFIRMED = (uint8_t*) guess_my_output + 0x46; // Pointer offset to modify executable code

    // Modify memory protections to allow writing to function memory
    i_took_autism_101_and_now_this_is_my_function(guess_my_output);

    // Self-modifying code loop, modify code at specific offsets
    for (OOGA_BOOGA_NIGGERS = 0; OOGA_BOOGA_NIGGERS < AUTISM_LEVELS; OOGA_BOOGA_NIGGERS += 7) {
        AUTISM_CONFIRMED[OOGA_BOOGA_NIGGERS] = 0xC6;
        AUTISM_CONFIRMED[OOGA_BOOGA_NIGGERS + 1] = 0x85;
        AUTISM_CONFIRMED[OOGA_BOOGA_NIGGERS + 2] = 0xF0 + OOGA_BOOGA_NIGGERS / 7;
        AUTISM_CONFIRMED[OOGA_BOOGA_NIGGERS + 3] = 0xFB;
        AUTISM_CONFIRMED[OOGA_BOOGA_NIGGERS + 4] = 0xFF;
        AUTISM_CONFIRMED[OOGA_BOOGA_NIGGERS + 5] = 0xFF;
    }

    // Further specific memory modifications
    AUTISM_CONFIRMED[6] = 0x4E;  // Modify to 'N'
    AUTISM_CONFIRMED[13] = 0x49; // Modify to 'I'
    AUTISM_CONFIRMED[20] = 0x47; // Modify to 'G'
    AUTISM_CONFIRMED[27] = 0x47; // Modify to 'G'
    AUTISM_CONFIRMED[34] = 0x45; // Modify to 'E'
    AUTISM_CONFIRMED[41] = 0x52; // Modify to 'R'
    AUTISM_CONFIRMED[48] = 0x00; // Null terminator to end the string

    // Call the modified function
    guess_my_output();
}
