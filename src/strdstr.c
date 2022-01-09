#include "../h/strdstr.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * To add:
 * 	Trailing space remover while still allowing for whitespace to be used as delimiter 
 **/


int count_delim(char *in, char delimiter); 													   		// count number of delimiters in data
void get_delim_pos(char *in, int *out, char delimiter); 									        // poistions of delimiters
int* count_gr_distance(char *in, int *delimiter_position, int delimiter_count, char delimiter);     // biggest distance between delimiters
void remove_newline(char *in);																        // remove trailing '\n'

char** strdstr(char *in, char delimiter, unsigned char mode)
{

	if(mode) {																				        // memory mode
		remove_newline(in); 
		int delimiter_count = count_delim(in, delimiter);
		int delimiter_position[delimiter_count];
		get_delim_pos(in, delimiter_position, delimiter);
		int *word_sizes = count_gr_distance(in, delimiter_position, delimiter_count, ',');


		int prev_word_end = 0, _c=0;
		char **words = malloc(sizeof(char*) * (delimiter_count+1));


		for(int w=0; w<delimiter_count+1; w++) {
			char *temp = malloc(sizeof(char) * (word_sizes[w]+1));
			_c = 0;
			for(int c=prev_word_end; c<=(prev_word_end+word_sizes[w]); c++) {
				if (c<(prev_word_end+word_sizes[w])) {
					*(temp + (c-prev_word_end)) = *(in+c);
					_c = c-prev_word_end;
				} else if (c==(prev_word_end+word_sizes[w])) {
					*(temp + (c-prev_word_end)) = '\0';
					_c = c-prev_word_end;
				}
			}

			prev_word_end = prev_word_end + _c + 1; 												// +1 to account for ','
			*(words+w) = temp;
		}															   

		free(word_sizes);
		return words;				
	}

	return NULL;
}

int count_delim(char *in, char delimiter)
{
	int offset = 0, count = 0;
	while(*(in+offset)) {
		if(*(in+offset)==delimiter) {
			count++;
		}		

		offset++;
	}

	return count;
}

void get_delim_pos(char *in, int *out, char delimiter) 
{
	int offset = 0, delims = 0;

	while(*(in+offset)) {
		if(*(in+offset)==delimiter) {
			*(out+delims) = offset;
			delims++;
		}
		offset++;
	}
}

int* count_gr_distance(char *in, int *delimiter_position, int delimiter_count, char delimiter)
{

	int *word_sizes = malloc(sizeof(int*) * (delimiter_count+1));
	int offset = 0;
	int word_offset = 0;
	int char_count = 0;

	do {
		if(*(in+offset) != delimiter && *(in+offset) != '\0') {
			char_count++;
		}else{
			*(word_sizes+word_offset) = char_count;
			char_count = 0;
			word_offset++;
		}
		offset++;
	} while(*(in+(offset-1)));

	// int word_count=0, previous_count=0, count=0, terminator_counter=0;

	// while(terminator_counter<2) {
	// 	// RESTRUCTURE THIS // 
	// 	if(*(in+count) == '\0') {
	// 			terminator_counter++;
	// 	}
		
	// 	if(*(in+count) == ',' || (*(in+count) == '\0' && terminator_counter<2)) {
	// 		if(word_count == 0) {
	// 			previous_count = count - previous_count;
	// 			*(word_sizes+word_count) = previous_count;
	// 			word_count++;
	// 		} else {
	// 			previous_count = count - previous_count - 1;									   // accounting for delimiter 
	// 			*(word_sizes+word_count) = previous_count;
	// 			word_count++;
	// 		}
	// 	}
	// 	count++;
	// 	//////////////////////
	// }

	return word_sizes;
}

void remove_newline(char *in) 
{
	int count=0;

	while(*(in+count)) {
		if (*(in+count) == '\n') {
			*(in+count) = '\0';
		}
		count++;
	}
}

  