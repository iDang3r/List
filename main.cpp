#include <cstdio>
#include <iostream>
#include <cassert>
#include <ctime>

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

    srand(time(NULL));

    LIST(Q);

    // UPDATED

    for (int i = 1; i <= 5; i++)
        Q.push_back(i * 10);

    for (int i = 1; i <= 5; i++)
        Q.add_after(i, i * 100);

    Q.erase(3);
    Q.erase(8);

    Q.sort();

    Q.dump_picture(true);

    cout << "\nEND\n";
    fclose(dump_file);
    return 0;
}
