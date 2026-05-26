#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct Node {
    unsigned char symbol;
    uint64_t freq;
    struct Node *left;
    struct Node *right;
} Node;

static Node *makeNode(unsigned char symbol, uint64_t freq, Node *left, Node *right) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (!node) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->symbol = symbol;
    node->freq = freq;
    node->left = left;
    node->right = right;
    return node;
}

static void freeTree(Node *root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

static void swapNodes(Node **a, Node **b) {
    Node *tmp = *a;
    *a = *b;
    *b = tmp;
}

static void heapifyDown(Node **heap, int size, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < size && heap[left]->freq < heap[smallest]->freq) smallest = left;
    if (right < size && heap[right]->freq < heap[smallest]->freq) smallest = right;
    if (smallest != i) {
        swapNodes(&heap[i], &heap[smallest]);
        heapifyDown(heap, size, smallest);
    }
}

static Node *extractMin(Node **heap, int *size) {
    if (*size <= 0) return NULL;
    Node *min = heap[0];
    heap[0] = heap[*size - 1];
    *size -= 1;
    heapifyDown(heap, *size, 0);
    return min;
}

static void heapifyUp(Node **heap, int idx) {
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (heap[parent]->freq <= heap[idx]->freq) break;
        swapNodes(&heap[parent], &heap[idx]);
        idx = parent;
    }
}

static void insertHeap(Node **heap, int *size, Node *node) {
    heap[*size] = node;
    *size += 1;
    heapifyUp(heap, *size - 1);
}

static Node *buildHuffmanTree(uint64_t freq[256]) {
    Node *heap[256];
    int heapSize = 0;
    for (int i = 0; i < 256; ++i) {
        if (freq[i] > 0) {
            heap[heapSize++] = makeNode((unsigned char)i, freq[i], NULL, NULL);
        }
    }
    if (heapSize == 0) {
        return NULL;
    }
    if (heapSize == 1) {
        Node *single = makeNode(heap[0]->symbol, heap[0]->freq, NULL, NULL);
        Node *root = makeNode(0, heap[0]->freq, heap[0], single);
        return root;
    }
    for (int i = heapSize / 2 - 1; i >= 0; --i) {
        heapifyDown(heap, heapSize, i);
    }
    while (heapSize > 1) {
        Node *left = extractMin(heap, &heapSize);
        Node *right = extractMin(heap, &heapSize);
        Node *combined = makeNode(0, left->freq + right->freq, left, right);
        insertHeap(heap, &heapSize, combined);
    }
    return heap[0];
}

static void buildCodes(Node *root, char codes[256][256], int lengths[256], char codeBuffer[256], int depth) {
    if (!root) return;
    if (!root->left && !root->right) {
        if (depth == 0) {
            codeBuffer[depth++] = '0';
        }
        codeBuffer[depth] = '\0';
        strcpy(codes[root->symbol], codeBuffer);
        lengths[root->symbol] = depth;
        return;
    }
    if (root->left) {
        codeBuffer[depth] = '0';
        buildCodes(root->left, codes, lengths, codeBuffer, depth + 1);
    }
    if (root->right) {
        codeBuffer[depth] = '1';
        buildCodes(root->right, codes, lengths, codeBuffer, depth + 1);
    }
}

static void writeUint64(FILE *out, uint64_t value) {
    for (int i = 0; i < 8; ++i) {
        fputc((unsigned char)(value >> (i * 8)), out);
    }
}

static uint64_t readUint64(FILE *in) {
    uint64_t value = 0;
    for (int i = 0; i < 8; ++i) {
        int ch = fgetc(in);
        if (ch == EOF) return 0;
        value |= ((uint64_t)(unsigned char)ch) << (i * 8);
    }
    return value;
}

static void writeUint16(FILE *out, uint16_t value) {
    fputc((unsigned char)(value & 0xff), out);
    fputc((unsigned char)((value >> 8) & 0xff), out);
}

static uint16_t readUint16(FILE *in) {
    int lo = fgetc(in);
    int hi = fgetc(in);
    if (lo == EOF || hi == EOF) return 0;
    return (uint16_t)((unsigned char)lo | ((unsigned char)hi << 8));
}

static void compressFile(const char *inputPath, const char *outputPath) {
    FILE *in = fopen(inputPath, "rb");
    if (!in) {
        fprintf(stderr, "Cannot open input file '%s'\n", inputPath);
        exit(EXIT_FAILURE);
    }

    uint64_t freq[256] = {0};
    uint64_t originalSize = 0;
    int ch;
    while ((ch = fgetc(in)) != EOF) {
        freq[(unsigned char)ch]++;
        originalSize++;
    }
    rewind(in);

    Node *root = buildHuffmanTree(freq);
    if (!root) {
        FILE *out = fopen(outputPath, "wb");
        if (out) fclose(out);
        fclose(in);
        return;
    }

    char codes[256][256] = {{0}};
    int lengths[256] = {0};
    char codeBuffer[256];
    buildCodes(root, codes, lengths, codeBuffer, 0);

    FILE *out = fopen(outputPath, "wb");
    if (!out) {
        fprintf(stderr, "Cannot open output file '%s'\n", outputPath);
        freeTree(root);
        fclose(in);
        exit(EXIT_FAILURE);
    }

    fwrite("HUF1", 1, 4, out);
    writeUint64(out, originalSize);
    uint16_t symbolCount = 0;
    for (int i = 0; i < 256; ++i) {
        if (freq[i] > 0) symbolCount++;
    }
    writeUint16(out, symbolCount);
    for (int i = 0; i < 256; ++i) {
        if (freq[i] > 0) {
            fputc((unsigned char)i, out);
            writeUint64(out, freq[i]);
        }
    }

    unsigned char buffer = 0;
    int bitCount = 0;
    while ((ch = fgetc(in)) != EOF) {
        const char *code = codes[(unsigned char)ch];
        for (int i = 0; code[i]; ++i) {
            buffer <<= 1;
            if (code[i] == '1') buffer |= 1;
            bitCount++;
            if (bitCount == 8) {
                fputc(buffer, out);
                buffer = 0;
                bitCount = 0;
            }
        }
    }
    unsigned char padding = 0;
    if (bitCount > 0) {
        buffer <<= (8 - bitCount);
        fputc(buffer, out);
        padding = 8 - bitCount;
    }
    fputc(padding, out);

    fclose(in);
    fclose(out);
    freeTree(root);
}

static void decompressFile(const char *inputPath, const char *outputPath) {
    FILE *in = fopen(inputPath, "rb");
    if (!in) {
        fprintf(stderr, "Cannot open input file '%s'\n", inputPath);
        exit(EXIT_FAILURE);
    }
    char magic[5] = {0};
    if (fread(magic, 1, 4, in) != 4 || strcmp(magic, "HUF1") != 0) {
        fprintf(stderr, "Input file is not a supported Huffman archive\n");
        fclose(in);
        exit(EXIT_FAILURE);
    }

    uint64_t originalSize = readUint64(in);
    uint16_t symbolCount = readUint16(in);
    uint64_t freq[256] = {0};
    for (int i = 0; i < symbolCount; ++i) {
        int sym = fgetc(in);
        if (sym == EOF) {
            fprintf(stderr, "Invalid compressed file\n");
            fclose(in);
            exit(EXIT_FAILURE);
        }
        freq[(unsigned char)sym] = readUint64(in);
    }

    Node *root = buildHuffmanTree(freq);
    if (!root) {
        FILE *out = fopen(outputPath, "wb");
        if (out) fclose(out);
        fclose(in);
        return;
    }

    fseek(in, 0, SEEK_END);
    long fileSize = ftell(in);
    if (fileSize < 0) {
        fprintf(stderr, "Cannot determine compressed file size\n");
        freeTree(root);
        fclose(in);
        exit(EXIT_FAILURE);
    }
    long currentPos = ftell(in);
    fseek(in, currentPos, SEEK_SET);

    if (fseek(in, 4 + 8 + 2 + symbolCount * 9, SEEK_SET) != 0) {
        fprintf(stderr, "Invalid compressed file structure\n");
        freeTree(root);
        fclose(in);
        exit(EXIT_FAILURE);
    }
    // The file pointer now points at compressed data, but we need to read after it.
    // We'll read all bytes except the last padding byte.
    long dataStart = ftell(in);
    if (fseek(in, -1, SEEK_END) != 0) {
        fprintf(stderr, "Invalid compressed file structure\n");
        freeTree(root);
        fclose(in);
        exit(EXIT_FAILURE);
    }
    int padding = fgetc(in);
    long dataEnd = ftell(in) - 1;
    long compressedDataSize = dataEnd - dataStart;
    if (compressedDataSize < 0) compressedDataSize = 0;
    fseek(in, dataStart, SEEK_SET);

    FILE *out = fopen(outputPath, "wb");
    if (!out) {
        fprintf(stderr, "Cannot open output file '%s'\n", outputPath);
        freeTree(root);
        fclose(in);
        exit(EXIT_FAILURE);
    }

    Node *node = root;
    uint64_t written = 0;
    int bitIndex = 0;
    for (long i = 0; i < compressedDataSize && written < originalSize; ++i) {
        int byte = fgetc(in);
        if (byte == EOF) break;
        for (int b = 7; b >= 0 && written < originalSize; --b) {
            int bit = (byte >> b) & 1;
            if (bit == 0) {
                if (node->left) node = node->left;
            } else {
                if (node->right) node = node->right;
            }
            if (!node->left && !node->right) {
                fputc(node->symbol, out);
                written++;
                node = root;
            }
            bitIndex++;
        }
    }

    if (written < originalSize && padding > 0) {
        int byte = fgetc(in);
        if (byte != EOF) {
            for (int b = 7; b >= padding && written < originalSize; --b) {
                int bit = (byte >> b) & 1;
                if (bit == 0) {
                    if (node->left) node = node->left;
                } else {
                    if (node->right) node = node->right;
                }
                if (!node->left && !node->right) {
                    fputc(node->symbol, out);
                    written++;
                    node = root;
                }
            }
        }
    }

    fclose(out);
    freeTree(root);
    fclose(in);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <c|d> <input_file> <output_file>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char mode = argv[1][0];
    if (mode == 'c' || mode == 'C') {
        compressFile(argv[2], argv[3]);
    } else if (mode == 'd' || mode == 'D') {
        decompressFile(argv[2], argv[3]);
    } else {
        fprintf(stderr, "Unknown mode '%c'. Use 'c' for compression or 'd' for decompression.\n", mode);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
