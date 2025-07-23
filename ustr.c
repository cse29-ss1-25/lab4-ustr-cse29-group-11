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
	if (start < 0) start = 0;
    	if (end > s.codepoints) end = s.codepoints;
    	if (start >= end) {
        	return new_ustr("");  // Returns an empty string
    	}

    	int start_byte = utf8_index_to_byte_index(s.contents, start);
    	int end_byte = utf8_index_to_byte_index(s.contents, end);
    	int sub_len = end_byte - start_byte;

    	char* sub_str = malloc(sub_len + 1);
    	memcpy(sub_str, s.contents + start_byte, sub_len);
    	sub_str[sub_len] = '\0';

    	UStr result = new_ustr(sub_str);
    	free(sub_str);  // new_ustr made a copy sothan  we free the temp
    	return result;

}

/*
Given 2 strings s1 and s2, returns a string that is the result of 
concatenating s1 and s2. 
*/
UStr concat(UStr s1, UStr s2) {
	// TODO: implement this
    int total_len = s1.bytes + s2.bytes;
    char* combined = malloc(total_len + 1);
    strcpy(combined, s1.contents);
    strcat(combined, s2.contents);

    UStr result = new_ustr(combined);
    free(combined);
    return result;	
}

/*
Given a string s and an index, return a string with the character at index 
removed from the original string. 

Returns the original string if index is out of bounds.
*/
UStr removeAt(UStr s, int32_t index) {
	// TODO: implement this
	if (index < 0 || index >= s.codepoints) {
        return new_ustr(s.contents);
    }

    int start_byte = utf8_index_to_byte_index(s.contents, index);
    int end_byte = utf8_index_to_byte_index(s.contents, index + 1);
    int new_len = s.bytes - (end_byte - start_byte);
    char* buffer = malloc(new_len + 1);

    memcpy(buffer, s.contents, start_byte);
    memcpy(buffer + start_byte, s.contents + end_byte, s.bytes - end_byte);
    buffer[new_len] = '\0';

    UStr result = new_ustr(buffer);
    free(buffer);
    return result;
}

/*
Given a string s, return s reversed. 

Example: reverse("apples🍎 and bananas🍌") = "🍌sananab dna 🍎selppa")
*/
UStr reverse(UStr s) {
	// TODO: implement this
	char* reversed = malloc(s.bytes + 1);
    int write_index = 0;

    for (int i = s.codepoints - 1; i >= 0; i--) {
        int byte_index = utf8_index_to_byte_index(s.contents, i);
        int cp_len = utf8_codepoint_len(s.contents[byte_index]);
        memcpy(reversed + write_index, s.contents + byte_index, cp_len);
        write_index += cp_len;
    }

    reversed[write_index] = '\0';
    UStr result = new_ustr(reversed);
    free(reversed);
    return result;
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

