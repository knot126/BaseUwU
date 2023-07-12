/**
 * BaseUwU binary to text encoding
 * 
 * Copyright (C) 2023 Knot126
 */

#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <stdbool.h>

int UwU_Encode(size_t input_size, const uint8_t *input_data, char **output_data_pointer);
bool UwU_Validate(const char *input_data);
int UwU_Decode(const char *input_data, size_t *output_size_ptr, const uint8_t **output_data_ptr);

#ifdef BASE_UWU_IMPLEMENTATION

int UwU_Encode(size_t input_size, const uint8_t *input_data, char **output_data_pointer) {
	/**
	 * Encode the data to BaseUwU
	 * 
	 * @note The format is:
	 *     For a 0 bit, append an OwO
	 *     For a 1 bit, append an UwU
	 * 
	 * @param input_size Size of the input data
	 * @param input_data Input data
	 * @param output_data_pointer Where to put the pointer to the output data
	 * @return Status code, 0 = success, anything else is failure
	 */
	
	size_t output_size = input_size * 24; // 3 bytes per UwU/OwO * 8 bits per char
	
	// Allocate the output data
	char *output_data = (char *) malloc(output_size + 1); // Need NUL byte
	
	if (!output_data) {
		return 1;
	}
	
	// Encode to BaseUwU
	for (size_t i = 0; i < input_size; i++) {
		for (size_t j = 0; j < 8; j++) {
			// What the current bit is
			bool bit = (input_data[i] >> (7 - j)) & 1;
			
			// Set U_U or O_O based on value
			char eye = bit ? 'U' : 'O';
			
			// Put characters
			// i represents a space of 24 (8 bits per input byte * 3 bytes per UwU/OwO)
			// j represents a space of 3 for bytes per UwU/OwO in each input byte
			// Last we have which byte it is in the UwU/OwO itself
			output_data[24 * i + 3 * j + 0] = eye;
			output_data[24 * i + 3 * j + 1] = 'w';
			output_data[24 * i + 3 * j + 2] = eye;
		}
	}
	
	// Output NUL byte
	output_data[output_size] = '\0';
	
	// Save output data pointer
	output_data_pointer[0] = output_data;
	
	return 0;
}

bool UwU_Validate(const char *input_data) {
	/**
	 * Validate that the input data is valid BaseUwU
	 * 
	 * @param input_data The data to check
	 * @return true if valid, false if not
	 */
	
	size_t length = strlen(input_data);
	
	// BaseUwU needs to have 8 bits per byte at 3 chars per bit, so length must
	// be BaseUwUDataLength % 24 == 0
	if (length % 24 != 0) {
		return false;
	}
	
	// Find the number of bits represented by this string
	size_t num_bits = length / 3;
	
	// Check that the 'w' char is okay in each UwU/OwO
	for (size_t i = 0; i < num_bits; i++) {
		if (input_data[(i * 3) + 1] != 'w') {
			return false;
		}
	}
	
	// Check that the first and last char of each UwU and OwO are really U or W
	for (size_t i = 0; i < num_bits; i++) {
		if (!( (input_data[(i * 3)] == 'O' && input_data[(i * 3) + 2] == 'O')
			|| (input_data[(i * 3)] == 'U' && input_data[(i * 3) + 2] == 'U'))
		) {
			return false;
		}
	}
	
	// If we got here, this is valid BaseUwU!
	return true;
}

int UwU_Decode(const char *input_data, size_t *output_size_ptr, const uint8_t **output_data_ptr) {
	/**
	 * Decode BaseUwU back to bytes
	 * 
	 * @param input_data The BaseUwU string
	 * @param output_size_ptr Where to put the size of the output data
	 * @param output_data_ptr Where to put the pointer to the output data
	 * @return Error code, 0 is no error, other is error
	 */
	
	// Make sure this is valid BaseUwU (so we can make some assumptions)
	if (!UwU_Validate(input_data)) {
		return 2;
	}
	
	size_t input_size = strlen(input_data);
	
	// Find the size of the output
	size_t output_size = input_size / 24;
	
	// Allocate the output data
	uint8_t *output_data = (uint8_t *) malloc(output_size);
	
	if (!output_data) {
		return 1;
	}
	
	// Decode the BaseUwU
	for (size_t i = 0; i < output_size; i++) {
		char byte = 0;
		
		for (size_t j = 0; j < 8; j++) {
			char bit = input_data[i * 24 + j * 3]; // Current bit as 'O' or 'U'
			
			// Convert to actual bit value
			bit = !!(bit == 'U');
			
			// Add a bit to the output
			byte = (byte << 1) | (bit);
		}
		
		output_data[i] = byte;
	}
	
	// Return outputs
	output_size_ptr[0] = output_size;
	output_data_ptr[0] = output_data;
	
	return 0;
}

#endif
