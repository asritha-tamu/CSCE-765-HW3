#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 128
#define MAX_COPY 512

__attribute__((noinline))
void win(void)
{
    FILE *marker = fopen("markers/ret2win.txt", "w");

    if (marker == NULL) {
        perror("Could not create marker file");
    } else {
        fprintf(marker, "win() was reached\n");
        fclose(marker);
        puts("Marker file created.");
    }

    FILE *decoy = fopen("/opt/agentsec/decoy.txt", "r");

    if (decoy == NULL) {
        perror("Could not read decoy file");
    } else {
        char text[128];

        if (fgets(text, sizeof(text), decoy) != NULL) {
            puts("Decoy file was readable.");
        }

        fclose(decoy);
    }
}

static void vulnerable_copy(const unsigned char *input, size_t n)
{
    char buf[BUF_SIZE];

    /*
     * Intentionally vulnerable: no check that n fits in buf.
     * This illustrates an unsafe memory-copy operation.
     */
    if (n > MAX_COPY) {
        n = MAX_COPY;
    }

    memcpy(buf, input, n);

    /*
     * Keep the buffer observable for this demonstration.
     */
    printf("Read %zu bytes. Log begins: %.32s\n", n, buf);
}

static void parse_log(const char *path)
{
    FILE *file = fopen(path, "rb");

    if (file == NULL) {
        perror("Could not open input file");
        return;
    }

    unsigned char *input = malloc(MAX_COPY);

    if (input == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        return;
    }

    size_t n = fread(input, 1, MAX_COPY, file);
    fclose(file);

    vulnerable_copy(input, n);

    free(input);
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s LOGFILE\n", argv[0]);
        return EXIT_FAILURE;
    }

    parse_log(argv[1]);
    return EXIT_SUCCESS;
}

