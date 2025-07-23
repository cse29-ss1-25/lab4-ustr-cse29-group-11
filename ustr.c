#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ustr.h"
#include "pset1.h"

/*
Initializes a new UStr with contents
*/
UStr new_ustr(char* contents) {
	int32_t bytes = strlen(contents);
	int32_t codepoints = utf8_strlen(contents);
	uint8_t all_ascii = bytes == codepoints;
	char* contents_copy = malloc(bytes + 1);
	strcpy(contents_copy, contents);
	UStr s = {
		codepoints,
		bytes,
		all_ascii,
		contents_copy
	};
	return s;
}

/*
Returns length of string
*/
int32_t len(UStr s) {
	return s.codepoints;
}

/*
Returns a substring of str, starting at index start (inclusive) 
and ending at index end (exclusive).

Returns an empty string on invalid range.
*/
UStr substring(UStr s, int32_t start, int32_t end) {
	// TODO: implement this
    int start_byte = bi_of_cpi(s.contents, start);
    int end_byte = bi_of_cpi(s.contents, end);

    if (start_byte < 0 || end_byte < 0 || start > end || end > s.codepoints) {
        return new_ustr("");
    }

    int new_len = end_byte - start_byte;
    char* new_str = malloc(new_len + 1);
    strncpy(new_str, s.contents + start_byte, new_len);
    new_str[new_len] = '\0';
    UStr result = new_ustr(new_str);
    free(new_str); 

    return result;
}
/*
Given 2 strings s1 and s2, returns a string that is the result of 
concatenating s1 and s2. 
*/
UStr concat(UStr s1, UStr s2) {
	// TODO: implement this
    int total_len = s1.bytes + s2.bytes;
    char* new_str = malloc(total_len + 1);

    strcpy(new_str, s1.contents);
    strcat(new_str, s2.contents);

    return new_ustr(new_str);
}

/*
Given a string s and an index, return a string with the character at index 
removed from the original string. 

Returns the original string if index is out of bounds.
*/
UStr removeAt(UStr s, int32_t index) {
	// TODO: implement this
    int start_byte = bi_of_cpi(s.contents, index);
    int end_byte = bi_of_cpi(s.contents, index + 1);

    if (start_byte < 0 || end_byte < 0) {
        return new_ustr("");
    }

    int new_len = s.bytes - (end_byte - start_byte);
    char* new_str = malloc(new_len + 1);

    strncpy(new_str, s.contents, start_byte);
    strcpy(new_str + start_byte, s.contents + end_byte);

    return new_ustr(new_str);
}

/*
Given a string s, return s reversed. 

Example: reverse("apples🍎 and bananas🍌") = "🍌sananab dna 🍎selppa")
*/
UStr reverse(UStr s) {
	// TODO: implement this
    char* new_str = malloc(s.bytes + 1);
    int write_pos = 0;

    for (int i = s.codepoints - 1; i >= 0; i--) {
        int byte_index = bi_of_cpi(s.contents, i);
        int cp_len = utf8_codepoint_size(s.contents[byte_index]);

        strncpy(new_str + write_pos, s.contents + byte_index, cp_len);
        write_pos += cp_len;
    }

    new_str[write_pos] = '\0';
    return new_ustr(new_str);
}


void print_ustr(UStr s) {
	printf("%s [codepoints: %d | bytes: %d]", s.contents, s.codepoints, s.bytes);
}

void free_ustr(UStr s) {
	if (s.contents != NULL) {
		free(s.contents);
		s.contents = NULL;
	}
}

