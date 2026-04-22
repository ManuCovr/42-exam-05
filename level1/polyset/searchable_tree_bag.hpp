#pragma once
#include "searchable_bag.hpp"
#include "tree_bag.hpp"

class searchable_tree_bag : public tree_bag, public searchable_bag {
public:
    searchable_tree_bag() {}
    searchable_tree_bag(const searchable_tree_bag& o) : tree_bag(o) {}
    searchable_tree_bag operator=(const searchable_tree_bag& o) { if (this != &o) tree_bag::operator=(o); return *this; }
    ~searchable_tree_bag() {}
    bool has(int value) const {
        node *cur = tree;
        while (cur) {
            if (cur->value == value) return true;
            cur = cur->value > value ? cur->l : cur->r;
        }
        return false;
    }
};
