#include "unit.h"

void Unit::add_item(Item item) {
    items.push_back(item);
}

void Unit::start_packaging() {
    sort();
    for (auto &item : items) {
        ItemBestPlace best_place;
        int min_residual_space = INT_MAX;
        for (auto &block : blocks) { 
            auto block_best_place = block->find_best_place(item);
            if((block_best_place.residual_space >= 0) && (block_best_place.residual_space < min_residual_space)) {
                min_residual_space = block_best_place.residual_space;
                best_place = block_best_place;
            }
        }

        if(best_place.block) {
            best_place.block->add_item(item, best_place);
        } else {
            // If the item cannot be placed in the current blocks and their child blocks, then create a new block in the unit
            auto new_block = std::make_shared<Block>(Block({width, item.size.height}, 
                                                            {0, total_height()}, 
                                                            min_item_height()));
            new_block->add_item(item);
            blocks.push_back(new_block);
        }
    }
}

std::ostream& operator<<(std::ostream& os, const Unit& unit) {
    os << unit.total_height() << " " << unit.width << std::endl;
    os << unit.items.size() << std::endl;
    for (auto &block : unit.blocks) {
        os << *block;
    }
    
    return os;
}

inline void Unit::sort() {
    std::sort(begin(items), end(items), [](const Item&  first, const Item& second) { return (first.size.height > second.size.height); });
}

inline int Unit::total_height() const {
    int height {};
    for (auto &block : blocks) {
        height += block->size.height;
    }
    
    return height;
}

inline int Unit::min_item_height() const {
    return items.empty() ? 0 : items.back().size.height;
}