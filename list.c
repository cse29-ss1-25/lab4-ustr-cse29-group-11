#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ustr.h"
#include "list.h"

/*
Returns an empty list of initial_capacity
*/
List new_list(int32_t initial_capacity) {
    List list;
    list.size = 0;
    list.capacity = initial_capacity;
    list.data = malloc(initial_capacity * sizeof(struct UStr));
    return list;
}

/*
Initializes an list of length size with elements from array
*/
List new_list_from_array(struct UStr* array, int32_t size) {
    List list = new_list(size);
    for (int32_t i = 0; i < size; i++) {
        list.data[i] = array[i];
    }
    list.size = size;
    return list;
}


/*
Given a list of strings and a separator string, returns a single string 
containing all the strings in list joined by the separator.
*/
UStr join(List* list, UStr separator) {
    // TODO: implement this
    if (list == NULL || list->size == 0) {
        return new_ustr("");
    }

    UStr result = new_ustr(list->data[0]->data);

    for (int i = 1; i < list->size; i++) {
        UStr temp1 = concat(&result, &separator);
        free_ustr(result);

        UStr temp2 = concat(&temp1, &list->data[i]);
        free_ustr(temp1);

        result = temp2;
    }

    return result;
}
/*
Inserts string s into list at index s, shifting elements to the right.
Expands the list's capacity if necessary (double the capacity, or set to 1 if 0).

Returns 1 on success, 0 if the index is invalid (out of bounds).
*/
int8_t insert(List* list, UStr s, int32_t index) {
    // TODO: implement this
    if (index < 0 || index > list->size) {
        return 0;
    }

    if (list->size >= list->capacity) {
        int32_t new_capacity = (list->capacity == 0) ? 1 : list->capacity * 2;
        struct UStr* new_data = malloc(new_capacity * sizeof(UStr));
        for (int32_t i = 0; i < list->size; i++) {
            new_data[i] = list->data[i];
        }
        free(list->data);
        list->data = new_data;
        list->capacity = new_capacity;
    }

    for (int32_t i = list->size; i > index; i--) {
        list->data[i] = list->data[i - 1];
    }

    list->data[index] = s;
    list->size++;
    return 1;
}
/*
Removes the element at the given index and shifts all subsequent elements left.

Returns 1 on success, 0 if the index is invalid (out of bounds).
*/
int8_t listRemoveAt(List* list, int32_t index) {
    // TODO:implement this
    if (index < 0 || index >= list->size) {
        return 0;
    }

    for (int i = index; i < list->size - 1; i++) {
        list->data[i] = list->data[i + 1];
    }

    list->size--;

    return 1;
}

/*
Splits the given string s into substrings separated by the given delimiter string.

Returns a List of String objects, each containing a segment between delimiters.

If the delimiter is the empty string, return a list containing the original 
string as a single element.

If the input string ends with the delimiter, include an empty string at the 
end of the result.

Note that the delimiter could be of a length of more than 1 character
*/
List split(UStr s, UStr separator) {
    // TODO: implement this
    if (len(separator) == 0) {
        List result = new_list(1);
        result.data[0] = new_ustr(s.contents);
        result.size = 1;
        return result;
    }

    List result = new_list(4);
    int32_t i = 0;
    int32_t start = 0;

    while (i <= s.codepoints - separator.codepoints) {
        int match = 1;

        for (int j = 0; j < separator.codepoints; j++) {
            UStr s_char = substring(s, i + j, i + j + 1);
            UStr sep_char = substring(separator, j, j + 1);

            if (strcmp(s_char.contents, sep_char.contents) != 0) {
                match = 0;
            }

            free_ustr(s_char);
            free_ustr(sep_char);

            if (!match) break;
        }

        if (match) {
            UStr token = substring(s, start, i);
            insert(&result, token, result.size);
            free_ustr(token);
            i += separator.codepoints;
            start = i;
        } else {
            i += 1;
        }
    }

    UStr final = substring(s, start, s.codepoints);
    insert(&result, final, result.size);
    free_ustr(final);

    return result;
}
