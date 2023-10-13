#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <memory>
#include <algorithm>
#include "item.h"

struct Block;

enum PlaceType { floor, ceiling, none };

struct ItemBestPlace {
    std::shared_ptr<Block> block;
    Point origin {0, 0};
    PlaceType type {none};
    int residual_space {-1};
};

class Block : public std::enable_shared_from_this<Block> {
public:
    std::vector<Item> floor;
    std::vector<Item> ceiling;
    Size size;
    Point origin;

    // pointer to child block of this block
    std::shared_ptr<Block> child_block;

    Block(Size size, Point origin, int min_item_height) : size(size), 
                                                            origin(origin), 
                                                            residual_floor_width(size.width), 
                                                            min_item_height(min_item_height) {};

    void add_item(Item& item);
    void add_item(Item& item, const ItemBestPlace& best_place);

    // find place with minimum residual space
    ItemBestPlace find_best_place(const Item& item);

    friend std::ostream& operator<<(std::ostream& os, const Block& block);

private:

    // residual floor width in block
    int residual_floor_width;

    // the lowest item
    int min_item_height;

    std::shared_ptr<Block> find_block_with_largest_area(const Item& item);
    
    // check that item can fit on the floor by width and height
    bool can_floor_fit_item(const Item& item);

    // check that item can fit on the ceiling by width and height
    bool can_ceiling_fit_item(const Item& item);

    // residual ceiling width of the block
    int residual_ceiling_width();

    // total ceiling width of the block. 
    // It is calculated as the sum of all widths of items on ceiling 
    inline int total_ceiling_width();

    // maximum x point of the block
    inline int max_x();
    
    // minimum y point of the block
    inline int max_y();
};

#endif