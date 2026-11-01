#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 128

static int safe_copy(const unsigned char *input, size_t n)
{
    char buf[BUF_SIZE];

    if (n >= BUF_SIZE) {
        fprintf(stderr,
                "Error: input is too large (%zu bytes); maximum is %d bytes\n",
                n, BUF_SIZE - 1);
        return -1;
    }

    memcpy(buf, input, n);
    buf[n] = '\0';

    printf("Read %zu bytes. Log begins: %.32s\n", n, buf);
    return 0;
}

static int parse_log(const char *path)
{
    FILE *file = fopen(path, "rb");

    if (file == NULL) {
        perror("Could not open input file");
        return -1;
    }

    unsigned char input[BUF_SIZE];
    size_t n = fread(input, 1, sizeof(input), file);

    if (ferror(file)) {
        perror("Could not read input file");
        fclose(file);
        return -1;
    }

    fclose(file);

    if (n >= BUF_SIZE) {
        fprintf(stderr,
                "Error: input exceeds maximum size of %d bytes\n",
                BUF_SIZE - 1);
        return -1;
    }

    return safe_copy(input, n);
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s LOGFILE\n", argv[0]);
        return EXIT_FAILURE;
    }

    return parse_log(argv[1]) == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
