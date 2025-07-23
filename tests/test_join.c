#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

/*
Run in a loop, taking in a separator as input

Prints out predefined string joined by the separator
*/
int main() {
    char input[256];
    while (fgets(input, sizeof(input), stdin)) {
        // Remove newline character if present
        size_t l = strlen(input);
        if (l > 0 && input[l - 1] == '\n') {
            input[l - 1] = '\0';
        }

        // read separator from stdin
        char sep[256];
        sscanf(input, "%255s", sep);

        // create a list of strings to be joined
        UStr s1 = new_ustr("hello");
        UStr s2 = new_ustr("this is");
        UStr s3 = new_ustr("cse29🐕");
        UStr arr[3] = {s1, s2, s3};
        UStr* ptr = &arr[0];
        List lst = new_list_from_array(ptr, 3);

        UStr separator = new_ustr(sep);

        UStr result = join(&lst, separator);

        print_ustr(result);
        printf("\n");

        free_ustr(separator);
        free_ustr(result);
        free_ustr(s3);
        free_ustr(s2);
        free_ustr(s1);
        free(lst.data);
    }
    return 0;
}
