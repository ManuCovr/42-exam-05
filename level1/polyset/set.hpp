#pragma once
#include "searchable_bag.hpp"

class set {
    searchable_bag &bag;
public:
    set(searchable_bag &bag) : bag(bag) {}
    set(const set& o) : bag(o.bag) {}
    ~set() {}
    void insert(int v)            { if (!bag.has(v)) bag.insert(v); }
    void insert(int *d, int size) { for (int i = 0; i < size; i++) if (!bag.has(d[i])) bag.insert(d[i]); }
    void print() const            { bag.print(); }
    void clear()                  { bag.clear(); }
    bool has(int v) const         { return bag.has(v); }
    const searchable_bag &get_bag() const { return bag; }
};
