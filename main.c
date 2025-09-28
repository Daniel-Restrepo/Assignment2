// main.c
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

void oct_to_bin(const char *oct, char *out);
void oct_to_hex(const char *oct, char *out);
void hex_to_bin(const char *hex, char *out);
void to_sign_magnitude(int32_t n, char *out);
void to_ones_complement(int32_t n, char *out);
void to_twos_complement(int32_t n, char *out);

// checks for spaces and tabs at the start of each line and skips
static char* ltrim(char *s) {
    while (*s == ' ' || *s == '\t') {
        s++;
    }
    return s;
}

int main(void) {

    // opens test file
    const char *filenames[] = {
        "A2_tests.txt",
        "a2_test.txt",
        "a2_tests.txt",
        NULL
    };

    FILE *fp = NULL;
    for (int i = 0; filenames[i]; ++i) {
        fp = fopen(filenames[i], "r");
        if (fp) {
            printf("Opened test file: %s\n\n", filenames[i]);
            break;
        }
    }
    if (!fp) {
        printf("Error: Could not open A2 test file.\n");
        return 1;
    }

    char line[256]; // buffer to hold one line of text from the test file
    int total  = 0;  // total number of tests
    int passed = 0;  // total number of passed tests
    
    //                  Logic (test runner):
    //  while loop reads every line
    //  trims spaces and tabs
    //  skips comments and empty lines
    //  reads the first word of function name
    //  moves pointer (p) past function name to values
    //  compares and matches func with possible funcs
    //  reads input and expected output
    //  runs func under test
    //  compares answer with expected answer
    //  prints pass or fail depending on comparision

    while (fgets(line, sizeof(line), fp)) {
        char *p = ltrim(line); // calls helper function

        // skips comments and empty lines
        if (*p == '\0' || *p == '\n' || *p == '#') {
            continue;
        }

        char func[32] = {0}; //stores what function name is being tsted
        if (sscanf(p, "%31s", func) != 1) {
            continue;
        }

        // move past function name and spaces
        p += (int)strlen(func);
        while (*p == ' ' || *p == '\t') {
            p++;
        }

        // matches function name
        
        if (strcmp(func, "oct_to_bin") == 0) {
            char in[128] = {0}, exp[256] = {0}, got[512];
            if (sscanf(p, "%127s %255s", in, exp) == 2) {
                oct_to_bin(in, got);
                total++;
                if (strcmp(exp, got) == 0) {
                    printf("oct_to_bin(%s): expected=%s got=%s  [PASS]\n", in, exp, got);
                    passed++;
                }
                else {
                    printf("oct_to_bin(%s): expected=%s got=%s  [FAIL]\n", in, exp, got);
                }
            }
        }
        else if (strcmp(func, "oct_to_hex") == 0) {
            char in[128] = {0}, exp[256] = {0}, got[512];
            if (sscanf(p, "%127s %255s", in, exp) == 2) {
                oct_to_hex(in, got);
                total++;
                if (strcmp(exp, got) == 0) {
                    printf("oct_to_hex(%s): expected=%s got=%s  [PASS]\n", in, exp, got);
                    passed++;
                }
                else {
                    printf("oct_to_hex(%s): expected=%s got=%s  [FAIL]\n", in, exp, got);
                }
            }
        }
        else if (strcmp(func, "hex_to_bin") == 0) {
            char in[128] = {0}, exp[256] = {0}, got[512];
            if (sscanf(p, "%127s %255s", in, exp) == 2) {
                hex_to_bin(in, got);
                total++;
                if (strcmp(exp, got) == 0) {
                    printf("hex_to_bin(%s): expected=%s got=%s  [PASS]\n", in, exp, got);
                    passed++;
                }
                else {
                    printf("hex_to_bin(%s): expected=%s got=%s  [FAIL]\n", in, exp, got);
                }
            }
        }
        else if (strcmp(func, "to_sign_magnitude") == 0) {
            char in[128] = {0}, exp[256] = {0}, got[64];
            if (sscanf(p, "%127s %255s", in, exp) == 2) {
                int32_t n = (int32_t)strtol(in, NULL, 10);
                to_sign_magnitude(n, got);
                total++;
                if (strcmp(exp, got) == 0) {
                    printf("to_sign_magnitude(%d): expected=%s got=%s  [PASS]\n", n, exp, got);
                    passed++;
                }
                else {
                    printf("to_sign_magnitude(%d): expected=%s got=%s  [FAIL]\n", n, exp, got);
                }
            }
        }
        else if (strcmp(func, "to_ones_complement") == 0) {
            char in[128] = {0}, exp[256] = {0}, got[64];
            if (sscanf(p, "%127s %255s", in, exp) == 2) {
                int32_t n = (int32_t)strtol(in, NULL, 10);
                to_ones_complement(n, got);
                total++;
                if (strcmp(exp, got) == 0) {
                    printf("to_ones_complement(%d): expected=%s got=%s  [PASS]\n", n, exp, got);
                    passed++;
                }
                else {
                    printf("to_ones_complement(%d): expected=%s got=%s  [FAIL]\n", n, exp, got);
                }
            }
        }
        else if (strcmp(func, "to_twos_complement") == 0) {
            char in[128] = {0}, exp[256] = {0}, got[64];
            if (sscanf(p, "%127s %255s", in, exp) == 2) {
                int32_t n = (int32_t)strtol(in, NULL, 10);
                to_twos_complement(n, got);
                total++;
                if (strcmp(exp, got) == 0) {
                    printf("to_twos_complement(%d): expected=%s got=%s  [PASS]\n", n, exp, got);
                    passed++;
                }
                else {
                    printf("to_twos_complement(%d): expected=%s got=%s  [FAIL]\n", n, exp, got);
                }
            }
        }
    }

    fclose(fp);

    // prints test summary
    printf("\nSummary: %d/%d tests passed, %d failed\n", passed, total, total - passed);
    return 0;
}