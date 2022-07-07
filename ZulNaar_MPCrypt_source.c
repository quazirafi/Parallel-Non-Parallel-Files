#include <stdio.h>
#include <stdint.h>
#include <malloc.h>
#include <string.h>
#include <time.h>
#include "omp.h"
#include "aes.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void readAllBytes(const char* file, uint8_t** buffer, uint64_t* length) {
	FILE* input = fopen(file, "rb");
	if (!input) {
		printf("File not found!\n");
		return;
	}
		
	fseek(input, 0, SEEK_END);
	*length = ftell(input);
	fseek(input, 0, SEEK_SET);

	*buffer = (uint8_t*)calloc(*length, sizeof(uint8_t));
	fread(*buffer, sizeof(uint8_t), *length, input);

	fclose(input);

	printf("Read %llu bytes from file %s\n", *length, file);
}

void writeToFile(const char* file, uint8_t** buffer, uint64_t length) {
	FILE* output = fopen(file, "wb");
	if (!output) {
		printf("An error occured...\n");
		return;
	}

	fwrite(*buffer, sizeof(uint8_t), length, output);

	fclose(output);

	printf("Wrote to file %s\n", file);
}

void printHex(uint8_t** buffer, uint64_t length) {
	dummyMethod3();
	for (uint64_t i = 0; i < length; i += 1)
		printf("%.2X ", (*buffer)[i]);
	dummyMethod4();
	printf("\n");
}

void printKey(const uint8_t* key) {
	printf("Key:\n");
	dummyMethod3();
	for (uint32_t i = 0; i < AES_BLOCKLEN; i += 1)
		printf("%.2X ", key[i]);
	dummyMethod4();
	printf("\n");
}

void padInput(uint8_t** buffer, uint64_t* length, uint64_t* no_blocks, uint64_t* padding) {
	*no_blocks = *length / AES_BLOCKLEN;
	uint8_t* padded_input = (uint8_t*)calloc((*no_blocks + 1) * AES_BLOCKLEN, sizeof(uint8_t));
	strncpy(padded_input, *buffer, *length);
	uint64_t a = *length % AES_BLOCKLEN;
	uint64_t b = *length / AES_BLOCKLEN;
	*padding = AES_BLOCKLEN - a;
	dummyMethod3();
	for (uint64_t i = 0; i < *padding; i += 1)
		padded_input[b * AES_BLOCKLEN + a + i] = *padding;
	dummyMethod4();
	free(*buffer);
	*buffer = padded_input;
	padded_input = NULL;
	printf("Padding input with value: %llu\n", *padding);
}

void remPadding(uint8_t** buffer, uint64_t* length, uint64_t* no_blocks, uint64_t* padding) {
	*padding = (*buffer)[*length - 1];
	printf("Discovered padding with value: %llu\n", *padding);
	uint8_t* plain_text = (uint8_t*)calloc(*length - *padding, sizeof(uint8_t));
	strncpy(plain_text, *buffer, *length - *padding);
	free(*buffer);
	*buffer = plain_text;
	plain_text = NULL;
}

void encryptionRoutine(const char* inFile, const uint8_t* key, const char* outFile) {
	uint64_t length, no_blocks, padding;
	uint8_t* buffer = NULL;

	printf("Sequential Encryption:\n");

	readAllBytes(inFile, &buffer, &length);

	if (!buffer)
		return;

	//printf("Input:\n");
	//printHex(&buffer, length);

	padInput(&buffer, &length, &no_blocks, &padding);

	//printf("Padded Input:\n");
	//printHex(&buffer, length + padding);

	//printKey(key);

	struct AES_ctx ctx;
	AES_init_ctx(&ctx, key);

	dummyMethod3();
	for (uint64_t i = 0; i < no_blocks + 1; i += 1)
		AES_ECB_encrypt(&ctx, buffer + i * 16);
	dummyMethod4();

	//printf("Cipher Text:\n");
	//printHex(&buffer, length + padding);

	writeToFile(outFile, &buffer, length + padding);
	
	free(buffer);
	buffer = NULL;

	printf("Sequential Encryption... done!\n\n");
}

void encryptionRoutineP(const char* inFile, const uint8_t* key, const char* outFile) {
	uint64_t length, no_blocks, padding;
	uint8_t* buffer = NULL;

	printf("Parallel Encryption:\n");

	readAllBytes(inFile, &buffer, &length);

	if (!buffer)
		return;

	//printf("Input:\n");
	//printHex(&buffer, length);

	padInput(&buffer, &length, &no_blocks, &padding);

	//printf("Padded Input:\n");
	//printHex(&buffer, length + padding);

	//printKey(key);

	struct AES_ctx ctx;
	AES_init_ctx(&ctx, key);

	int64_t i;

	dummyMethod1();
#pragma omp parallel for
	for (i = 0; i < no_blocks + 1; i += 1)
		AES_ECB_encrypt(&ctx, buffer + i * 16);
	dummyMethod2();

	//printf("Cipher Text:\n");
	//printHex(&buffer, length + padding);

	writeToFile(outFile, &buffer, length + padding);

	free(buffer);
	buffer = NULL;

	printf("Parallel Encryption... done!\n\n");
}

void decryptionRoutine(const char* inFile, const uint8_t* key, const char* outFile) {
	uint64_t length, no_blocks, padding;
	uint8_t* buffer = NULL;

	printf("Sequential Decryption:\n");

	readAllBytes(inFile, &buffer, &length);

	if (!buffer)
		return;

	no_blocks = length / AES_BLOCKLEN;

	//printf("Decryption Input:\n");
	//printHex(&buffer, length);

	//printKey(key);

	struct AES_ctx ctx;
	AES_init_ctx(&ctx, key);

	dummyMethod3();
	for (uint64_t i = 0; i < no_blocks; i += 1)
		AES_ECB_decrypt(&ctx, buffer + i * 16);
	dummyMethod4();

	//printf("Padded PlainText:\n");
	//printHex(&buffer, length);

	remPadding(&buffer, &length, &no_blocks, &padding);

	//printf("PlainText:\n");
	//printHex(&buffer, length - padding);

	writeToFile(outFile, &buffer, length - padding);

	free(buffer);
	buffer = NULL;

	printf("Sequential Decryption... done!\n\n");
}

void decryptionRoutineP(const char* inFile, const uint8_t* key, const char* outFile) {
	uint64_t length, no_blocks, padding;
	uint8_t* buffer = NULL;

	printf("Parallel Decryption:\n");

	readAllBytes(inFile, &buffer, &length);

	if (!buffer)
		return;

	no_blocks = length / AES_BLOCKLEN;

	//printf("Decryption Input:\n");
	//printHex(&buffer, length);

	//printKey(key);

	struct AES_ctx ctx;
	AES_init_ctx(&ctx, key);

	int64_t i;

	dummyMethod1();
#pragma omp parallel for
	for (i = 0; i < no_blocks; i += 1)
		AES_ECB_decrypt(&ctx, buffer + i * 16);
	dummyMethod2();

	//printf("Padded PlainText:\n");
	//printHex(&buffer, length);

	remPadding(&buffer, &length, &no_blocks, &padding);

	//printf("PlainText:\n");
	//printHex(&buffer, length - padding);

	writeToFile(outFile, &buffer, length - padding);

	free(buffer);
	buffer = NULL;

	printf("Parallel Decryption... done!\n\n");
}

int main(int argc, char** argv) {

	clock_t t;

	if (argc == 5) {
		uint8_t key[16];
		if (strcmp(argv[1], "-e") == 0) {
			if (strlen(argv[4]) == 16) {
				strncpy(key, argv[4], 16);
				t = clock();
				encryptionRoutine(argv[2], key, argv[3]);
				t = clock() - t;
				printf("Sequential time: %f seconds.\n\n", (float)t / CLOCKS_PER_SEC);
				t = clock();
				encryptionRoutineP(argv[2], key, argv[3]);
				t = clock() - t;
				printf("Parallel time: %f seconds.\n\n", (float)t / CLOCKS_PER_SEC);
			}
			else
				printf("Invalid key. Please specify a 128 bit key...\n");
		}
		else if (strcmp(argv[1], "-d") == 0) {
			if (strlen(argv[4]) == 16) {
				strncpy(key, argv[4], 16);
				t = clock();
				decryptionRoutine(argv[2], key, argv[3]);
				t = clock() - t;
				printf("Sequential time: %f seconds.\n\n", (float)t / CLOCKS_PER_SEC);
				t = clock();
				decryptionRoutineP(argv[2], key, argv[3]);
				t = clock() - t;
				printf("Parallel time: %f seconds.\n\n", (float)t / CLOCKS_PER_SEC);
			}
			else
				printf("Invalid key. Please specify a 128 bit key...\n");
		}
		else
			printf("Invalid operation. Specify -d for decryption or -e for encryption...\n");
	}
	else {
		printf("Usage: ProjectName.extension -e SourceFile.extension DestinationFile.extension Key\n");
		printf("Usage: ProjectName.extension -d SourceFile.extension DestinationFile.extension Key\n");
	}
	
	return 0;
}
int dummyMethod1(){
    return 0;
}
int dummyMethod2(){
    return 0;
}
int dummyMethod3(){
    return 0;
}
int dummyMethod4(){
    return 0;
}