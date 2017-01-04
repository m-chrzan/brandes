#include <iostream>

int main(int argc, char *argv[]) {
    if (argc < 4) {
        std::cerr
            << "USAGE: ./brandes <number-threads> <input-file> <output-file>"
            << std::endl;
        return 1;
    }

    return 0;
}
