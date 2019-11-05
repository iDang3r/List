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

    for (int i = 1; i <= 20; i++)
        Q.push_back(i);

    for (int i = 1; i <= 10; i++)
        Q.erase(rand() % 20 + 1);

    Q.dump_picture(true);




    cout << "\nEND\n";
    fclose(dump_file);
    return 0;
}
