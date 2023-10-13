#ifndef STRIP_H
#define STRIP_H

#include <utility>
#include <iostream>
#include "block.h"

class Unit {
public:
    Unit(int width) : width(width) { }

    void add_item(Item item);
    void start_packaging();
    friend std::ostream& operator<<(std::ostream& os, const Unit& unit);
    
private:
    std::vector<std::shared_ptr<Block>> blocks;
    std::vector<Item> items;

    //width of the unit
    int width; 

    // non-increasing sort of items
    inline void sort();
    
    // total height of blocks
    inline int total_height() const;

    // the lowest item
    inline int min_item_height() const;
};

#endif