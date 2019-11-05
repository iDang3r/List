//
// Created by Александр on 05.11.2019.
//

#ifndef LIST_MY_LIST_ENUMS_H
#define LIST_MY_LIST_ENUMS_H

enum list_errors {
    OK         = 0,
    SIZE       = 1,
    CANARIES   = 2,
    LIST_HASH  = 3,
    DATA_HASH  = 4,
    NEXT_HASH  = 5,
    PREV_HASH  = 6,
    DATA_ELEMS = 7,
    FREE_ELEMS = 8,
    PREV_ELEMS = 9,
    HEAD_POINT = 10,
    TAIL_POINT = 11,
    FREE_POINT = 12,

};

enum fatal_errors {


};

#endif //LIST_MY_LIST_ENUMS_H
