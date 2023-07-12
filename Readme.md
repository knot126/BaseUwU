# BaseUwU Binary to Text Encoding

BaseUwU is a **THICCCC** binary to text encowoding using only `UwU`s and `OwO`s for maxium communication clarity among furries and weebs.

It's extremely inefficent &mdash; **THICCCC** with four C's, that is &mdash; at 24 output bytes per input byte - making it the perfect fit to keep fat fetishsts intrested in your project!

## Usage

This is a single header C library, in the style of an STB library. It only needs support for `strlen` and `malloc`, so it should run basically anywhere. In the future, we might support custom names for these functions if you need to use non-default ones, in a way that mirrors how stb libraries do it.

### Including

To include the library implementation, define `BASE_UWU_IMPLEMENTATION` before `#include`ing the file:

```c
#define BASE_UWU_IMPLEMENTATION
#include "baseuwu.h"
```

### Encoding

To encode, use `UwU_Encode`:

```c
// Declaration for UwU_Encode
int UwU_Encode(size_t input_size, const uint8_t *input_data, char **output_data_pointer);

void something() {
	char data[] = "Hello, world!";
	char *output; // The pointer to the resulting data is stored here.
	
	// Encode the binary data
	int status = UwU_Encode(strlen(data) + 1, data, output);
	
	if (status) {
		// Handle error...
	}
	
	printf("Output: %s\n", output);
	
	free(output);
}
```

### Decoding

To decode data, use `UwU_Decode`:

```c
// Declaration for UwU_Decode
int UwU_Decode(const char *input_data, size_t *output_size_ptr, const uint8_t **output_data_ptr);

void something() {
	char data[] = "OwOUwUOwOOwOUwUOwOOwOOwOOwOUwUUwUOwOOwOUwUOwOUwUOwOUwUUwUUwUOwOUwUUwUUwUOwOUwUUwUUwUOwOUwUUwUUwUOwOUwUUwUOwOUwUUwUUwUUwUOwOOwOUwUOwOOwOOwOOwOUwUOwOOwOUwUOwOOwOOwOOwOOwOOwOOwOUwUUwUUwUOwOUwUOwOOwOOwOUwUUwUOwOOwOUwUUwUOwOOwOOwOOwOOwOOwOOwOOwO";
	size_t output_size; // The size of the loaded data is stored here
	char *output_data; // The pointer to the loaded data is stored here
	
	// Decode the text data
	int status = UwU_Decode(data, &output_size, &output_data);
	
	if (status) {
		// Handle error ...
	}
	
	// NOTE: This assumes that the NUL byte was kept at the end of the encoded data.
	printf("Decoded: %s (length = %x)\n", output_data, output_size);
	
	free(output_data);
}
```

# Licence

No.
