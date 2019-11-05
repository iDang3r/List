//
// Created by Александр on 05.11.2019.
//

#ifndef LIST_MY_LIST_H
#define LIST_MY_LIST_H

#include "super_define.h"

#define LIST(x) List x(#x);

typedef int elem_t;

struct List {
    const int MAX_SIZE_ = 16;
    const elem_t poison_val_ = -9999999;

    int size_ = 0;

    elem_t* data_ = nullptr;
    int* next_ = nullptr;
    int* prev_ = nullptr;

    int head_ = 0;
    int tail_ = 0;
    int free_ = 1;

    bool is_sorted_ = true;

    char* name_ = nullptr;
    int errno_ = 0;

    List(const char* name = "NO_NAME");

    ~List();

    void dump_(const char* flag);

    void dump_picture(bool with_free = false);

    int add_first_elem(elem_t value);

    int push_back(elem_t value);

    int push_front(elem_t value);

    int add_after(int pos, elem_t value);

    int add_before(int pos, elem_t value);

    int pop_back();

    int pop_front();

    int erase(int del_pos);

    int find_index_by_value(int value);

    int front_index();

    int back_index();

    elem_t front();

    elem_t back();

    int size();

    int get_next_index(int pos);

    int get_prev_index(int pos);

    elem_t& operator[](int num);

};

List::List(const char* name) {
    data_ = (elem_t*)calloc(MAX_SIZE_ + 1, sizeof(elem_t));
    next_ =    (int*)calloc(MAX_SIZE_ + 1, sizeof(int));
    prev_ =    (int*)calloc(MAX_SIZE_ + 1, sizeof(int));
    name_ =   (char*)calloc(strlen(name) + 1, sizeof(char));

    if (data_ == nullptr) {
        dump(DUMP_INFO, "Memory for data_ was not allocated!");
        assert(ERROR);
    }

    if (next_ == nullptr) {
        dump(DUMP_INFO, "Memory for next_ was not allocated!");
        assert(ERROR);
    }

    if (prev_ == nullptr) {
        dump(DUMP_INFO, "Memory for prev_ was not allocated!");
        assert(ERROR);
    }

    if (name_ == nullptr) {
        dump(DUMP_INFO, "Memory for name_ was not allocated!");
        assert(ERROR);
    }

    strcpy(name_, name);

    // filling array for free pointer

    free_ = 1;
    for (int i = 1; i < MAX_SIZE_; i++)
        next_[i] = i + 1;
    next_[MAX_SIZE_] = 0;

    for (int i = 1; i <= MAX_SIZE_; i++)
        data_[i] = poison_val_;
}

List::~List() {
    if (data_ == errptr<elem_t>()) {
        dump(DUMP_INFO, "DOUBLE DESTRUCTOR! or double free of data_");
        assert(ERROR);
    }

    if (next_ == errptr<int>()) {
        dump(DUMP_INFO, "DOUBLE DESTRUCTOR! or double free of next_");
        assert(ERROR);
    }

    if (prev_ == errptr<int>()) {
        dump(DUMP_INFO, "DOUBLE DESTRUCTOR! or double free of prev_");
        assert(ERROR);
    }

    if (name_ == errptr<char>()) {
        dump(DUMP_INFO, "DOUBLE DESTRUCTOR! or double free of name_");
        assert(ERROR);
    }

    free(data_);
    free(next_);
    free(prev_);
    free(name_);

    poison(&data_);
    poison(&next_);
    poison(&prev_);
    poison(&name_);
}

void List::dump_(const char* flag) {

}

void List::dump_picture(bool with_free) {
    FILE* out = fopen("/Users/alex/Desktop/pictures/list_uml.pu", "w");

    fprintf(out, "@startuml\n !define DARKORANGE\n !include style.puml\n class head_\n");

    fprintf(out, "note right: size_: %d\n", size_);

    fprintf(out, "class tail_\n");

    fprintf(out, "note left: free_: %d\n", free_);

    for (int i = head_, logic = 1; i != 0; i = next_[i], logic++) {
        fprintf(out, "class %d {\n", i);
        fprintf(out, "logic: %d\n", logic);
        fprintf(out, "--\n");
        fprintf(out, "value: %d\n", data_[i]);
        fprintf(out, "--\n");
        fprintf(out, "next: %d\n", next_[i]);
        fprintf(out, "--\n");
        fprintf(out, "prev: %d\n", prev_[i]);
        fprintf(out, "}\n");
    }

    fprintf(out, "head_ ..> %d\n", head_);

    for (int i = head_; i != tail_; i = next_[i]) {
        fprintf(out, "%d -> %d\n", i, next_[i]);
    }

    for (int i = tail_; i != head_; i = prev_[i]) {
        fprintf(out, "%d -> %d\n", i, prev_[i]);
    }

    fprintf(out, "tail_ ..> %d\n", tail_);

    if (with_free) {
        fprintf(out, "class free_\n");

        for (int i = free_; i != 0; i = next_[i]) {
            fprintf(out, "class %d {\n", i);
            fprintf(out, "next: %d\n", next_[i]);
            fprintf(out, "}\n");
        }

        fprintf(out, "free_ ..> %d\n", free_);
        for (int i = free_; next_[i] != 0; i = next_[i]) {
            fprintf(out, "%d -> %d\n", i, next_[i]);
        }

        fprintf(out, "%d -[hidden]-> free_\n", head_);
    }

    fprintf(out, "@enduml\n");

    fclose(out);
    system("java -jar --illegal-access=warn /Users/alex/plantuml.jar -tsvg /Users/alex/Desktop/pictures/list_uml.pu");
    system("open /Users/alex/Desktop/pictures/list_uml.svg");
}

int List::add_first_elem(elem_t value) {
    if (free_ == 0 || data_[free_] != poison_val_) {
        dump(DUMP_INFO, "failed free_ pointer");
        return -1;
    }

    int new_pos = free_;
    free_ = next_[free_];

    head_ = tail_ = new_pos;

    next_[new_pos] = prev_[new_pos] = 0;

    data_[new_pos] = value;

    size_++;

    return new_pos;
}

int List::push_back(elem_t value) {
    if (free_ == 0) {
        dump(DUMP_INFO, "List is full");
        return -1;
    }

    if (size_ == 0) {
        return add_first_elem(value);
    }

    if (data_[free_] != poison_val_) {
        dump(DUMP_INFO, "failed free_ pointer");
        return -1;
    }

    is_sorted_ = false;

    int new_pos = free_;
    free_ = next_[free_];

    next_[tail_] = new_pos;
    prev_[new_pos] = tail_;
    next_[new_pos] = 0;
    tail_ = new_pos;

    data_[new_pos] = value;

    size_++;

    return new_pos;

}

int List::push_front(elem_t value) {
    if (free_ == 0) {
        dump(DUMP_INFO, "List is full");
        return -1;
    }

    if (size_ == 0) {
        return add_first_elem(value);
    }

    if (data_[free_] != poison_val_) {
        dump(DUMP_INFO, "failed free_ pointer");
        return -1;
    }

    is_sorted_ = false;

    int new_pos = free_;
    free_ = next_[free_];

    prev_[head_] = new_pos;
    next_[new_pos] = head_;
    prev_[new_pos] = 0;
    head_ = new_pos;

    data_[new_pos] = value;

    size_++;

    return new_pos;
}

int List::add_after(int pos, elem_t value) {
    if (data_[pos] == poison_val_) {
        dump(DUMP_INFO, "undefined element with index: pos");
        return -1;
    }

    if (free_ == 0) {
        dump(DUMP_INFO, "List is full");
        return -1;
    }

    if (pos == tail_) {
        return push_back(value);
    }

    if (data_[free_] != poison_val_) {
        dump(DUMP_INFO, "failed free_ pointer");
        return -1;
    }

    is_sorted_ = false;

    int new_pos = free_;
    free_ = next_[free_];

    prev_[next_[pos]] = new_pos;
    prev_[new_pos] = pos;
    next_[new_pos] = next_[pos];
    next_[pos] = new_pos;

    data_[new_pos] = value;

    size_++;

    return new_pos;
}

int List::add_before(int pos, elem_t value) {
    if (data_[pos] == poison_val_) {
        dump(DUMP_INFO, "undefined element with index: pos");
        return -1;
    }

    if (free_ == 0) {
        dump(DUMP_INFO, "List is full");
        return -1;
    }

    if (pos == head_) {
        return push_front(value);
    }

    if (data_[free_] != poison_val_) {
        dump(DUMP_INFO, "failed free_ pointer");
        return -1;
    }

    is_sorted_ = false;

    int new_pos = free_;
    free_ = next_[free_];

    next_[prev_[pos]] = new_pos;
    next_[new_pos] = pos;
    prev_[new_pos] = prev_[pos];
    prev_[pos] = new_pos;

    data_[new_pos] = value;

    size_++;

    return new_pos;
}

int List::pop_back() {
    int del_pos = tail_;
    if (del_pos == 0) {
        dump(DUMP_INFO, "pop_back was called from empty List");
        return -1;
    }

    is_sorted_ = false;

    tail_ = prev_[del_pos];
    next_[prev_[del_pos]] = 0; // hide if you want to show all

    data_[del_pos] = poison_val_;

    next_[del_pos] = free_;
    free_ = del_pos;

    size_--;

    if (size_ == 0)
        head_ = 0;

    return 0;
}

int List::pop_front() {
    int del_pos = head_;
    if (del_pos == 0) {
        dump(DUMP_INFO, "pop_front was called from empty List");
        return -1;
    }

    is_sorted_ = false;

    head_ = next_[del_pos];
    prev_[next_[del_pos]] = 0;

    data_[del_pos] = poison_val_;

    next_[del_pos] = free_;
    free_ = del_pos;

    size_--;

    if (size_ == 0)
        tail_ = 0;

    return 0;
}

int List::erase(int del_pos) {
    if (del_pos <= 0 ||del_pos > MAX_SIZE_ || data_[del_pos] == poison_val_) {
        dump(DUMP_INFO, "undefined element with index: del_pos");
        return -1;
    }

    if (del_pos == head_)
        return pop_front();

    if (del_pos == tail_)
        return pop_back();

    is_sorted_ = false;

    next_[prev_[del_pos]] = next_[del_pos];
    prev_[next_[del_pos]] = prev_[del_pos];

    next_[del_pos] = free_;
    free_ = del_pos;

    data_[del_pos] = poison_val_;

    size_--;

    return 0;
}

int List::find_index_by_value(int value) {
    if (value == poison_val_) {
        dump(DUMP_INFO, "value is equal to poison_val_");
        return -1;
    }

    for (int i = head_; i != 0; i = next_[i])
        if (data_[i] == value)
            return i;

    return 0;
}

int List::front_index() {
    return head_;
}

int List::back_index() {
    return tail_;
}

elem_t List::front() {
    return data_[head_];
}

elem_t List::back() {
    return data_[tail_];
}

int List::size() {
    return size_;
}

int List::get_next_index(int pos) {
    if (data_[pos] == poison_val_) {
        dump(DUMP_INFO, "undefined element with index: pos");
        return -1;
    }

    return next_[pos];
}

int List::get_prev_index(int pos) {
    if (data_[pos] == poison_val_) {
        dump(DUMP_INFO, "undefined element with index: pos");
        return -1;
    }

    return prev_[pos];
}

elem_t& List::operator[](int num) {
    if (num <= 0 || num > size_) {
        dump(DUMP_INFO, "false logical number for List");
        assert(ERROR);
        return data_[0];
    }

    int index = head_;

    for (int i = 1; i < num; i++)
        index = next_[index];

    return data_[index];
}

#endif //LIST_MY_LIST_H
