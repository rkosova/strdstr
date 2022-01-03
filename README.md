
# strdstr

```./src/strdstr.c```

## Parameters

**in** ```char*``` - Pointer to input.

**delimiter** ```char``` - Character of delimiter.

**mode** ```unsigned char``` - Switches mode of function:

- Fast (```mode = 0```): 
	- Creates a space in the heap the size of the input and stores the data directly. Not very memory efficient but faster than alternative.

- Memory (```mode>0```):
	- Counts the number of separate "words" (data between delimiters) in input and the greatest distance between words (i.e the biggest word). Using this metadata, it creates an appropriately sized space in heap. Much more memory efficient but slower.



## Description

A function to separate input into different words based on a delimiter character. 


