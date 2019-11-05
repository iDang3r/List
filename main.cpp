#include <cstdio>
#include <iostream>
#include <cassert>

using std::cin;
using std::cout;
using std::endl;

#include "super_define.h"
#include "dump.h"

#include "my_list.h"

int main() {
    FILE *dump_file = fopen("/Users/alex/Desktop/dump_file.txt", "w");
    if (dump_file == nullptr) {
        printf("Error opening dump_file\n");
        return 1;
    }

    LIST(A);

    // UPDATED

    A.push_back(-9);

    A.dump_picture();

    cout << "\nEND\n";
    fclose(dump_file);
    return 0;
}
