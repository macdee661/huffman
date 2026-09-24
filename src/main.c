#include "huffman.h"

#include <stdio.h>
#include <string.h>

int main(int argc, char **argv){
	if(argc != 4){
		fprintf(stderr, "Usage: %s <compress|decompress> <input> <output>\n", argv[0]);
		return 1;
	}

	if(strcmp(argv[1], "compress") == 0 || strcmp(argv[1], "c") == 0){
		compress(argv[2], argv[3]);
	} else if(strcmp(argv[1], "decompress") == 0 || strcmp(argv[1], "d") == 0){
		decompress(argv[2], argv[3]);
	} else {
		fprintf(stderr, "Unknown operation: %s\n", argv[1]);
		return 1;
	}

	return 0;
}
