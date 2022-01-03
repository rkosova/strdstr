#include "../h/strdstr.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * To add:
 * 	Trailing space remover while still allowing for whitespace to be used as delimiter 
 **/


int count_delim(char *in, char delimiter); 													       // count number of delimiters in data
void get_delim_pos(char *in, int *out, char delimiter); 									       // poistions of delimiters
int* count_gr_distance(char *in, int *delimiter_position, int delimiter_count, char delimiter);    // biggest distance between delimiters
void remove_newline(char *in);																       // remove trailing '\n'

char** strdstr(char *in, char delimiter, unsigned char mode)
{

	if(mode) {																				       // memory mode
		remove_newline(in); 
		int delimiter_count = count_delim(in, delimiter);
		int delimiter_position[delimiter_count];
		get_delim_pos(in, delimiter_position, delimiter);
		int *word_sizes = count_gr_distance(in, delimiter_position, delimiter_count, ',');

		int prev_delimiter_position = 0;
		char **words = malloc(sizeof(char*)*(delimiter_count+1));

		for(int w=0; w<delimiter_count+1; w++) {
			char *temp = malloc((word_sizes[w]+1) * sizeof(char));

			if (w==0) {
				for(int c=0; c<delimiter_position[w]+1; c++) {
					if (c<delimiter_position[w]) {
						*(temp+c) = *(in+c); 
					} else {
						*(temp+c) = '\0';   
					}
				}
				prev_delimiter_position = delimiter_position[w];	

			} else if (w>0 && w<delimiter_count) {
				int count=0;
				for(int c=prev_delimiter_position+1; c<delimiter_position[w]+1; c++) {
					if (c<delimiter_position[w]) {
						*(temp+count) = *(in+c);
						count++; 
					} else {
						*(temp+count) = '\0';
						count++;
					}
				}
				prev_delimiter_position = delimiter_position[w];	

			} else if (w==delimiter_count) {  	// since w starts at 0 delimiter count doesn't have to be added 1
				int countw = 0;
				for(int c=prev_delimiter_position+1; c<(prev_delimiter_position+word_sizes[w]+2); c++) {
					if (c<prev_delimiter_position+word_sizes[w]+1) {
						*(temp+countw) = *(in+c); 
						countw++;
					} else {
						*(temp+countw) = '\0';
						countw++;
					}
				} // issue in this siection; repeats too many times. can lead to segfault
			}

			*(words+w)  = temp;						
		}			// restructure																			   

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

	int word_count=0, previous_count=0, count=0, terminator_counter=0;

	while(terminator_counter<2) {
		// RESTRUCTURE THIS // 
		if(*(in+count) == '\0') {
				terminator_counter++;
		}
		
		if(*(in+count) == ',' || (*(in+count) == '\0' && terminator_counter<2)) {
			if(word_count == 0) {
				previous_count = count - previous_count;
				*(word_sizes+word_count) = previous_count;
				word_count++;
			} else {
				previous_count = count - previous_count - 1;									   // accounting for delimiter 
				*(word_sizes+word_count) = previous_count;
				word_count++;
			}
		}
		count++;
		//////////////////////
	}

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

  