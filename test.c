#include <stdio.h>

#define BASE_UWU_IMPLEMENTATION
#include "baseuwu.h"

int main(int argc, const char *argv[]) {
	int status;
	
	// Test encoding
	char data[] = "Hewwo! :3";
	char *output;
	
	status = UwU_Encode(strlen(data) + 1, data, &output);
	
	if (status) {
		printf("Error: Status %d\n", status);
		return status;
	}
	
	printf("Encoded:\n%s\n\n", output);
	
	// Test decoding
	size_t decoded_length;
	char *decoded;
	
	status = UwU_Decode(output, &decoded_length, &decoded);
	
	if (status) {
		printf("Error: Status %d\n", status);
		return status;
	}
	
	printf("Decoded (length = 0x%zx):\n%s\n\n", decoded_length, decoded);
	
	// Test validator
	char *validations[] = {
		"UwUUwUOwO", // Not enough data
		"UwUUwUOwOUwUUwUOwOOwOUwU", // This should be okay
		"ASOKRAOKERKOERKOEOEOOEOO", // Bad chars
		"UwUOwOUwUOwOUwUOwOAwAOwO", // Bad chars ('w's are correct)
	};
	
	for (size_t i = 0; i < sizeof(validations) / sizeof(*validations); i++) {
		printf("Is %s valid? %x\n", validations[i], UwU_Validate(validations[i]));
	}
	
	return 0;
}
