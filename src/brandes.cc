#include <cstdio>

int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "USAGE: ./brandes <number-threads> <input-file> <output-file>\n");
        return 1;
    }

    return 0;
}
