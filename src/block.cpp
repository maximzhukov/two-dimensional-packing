#include "block.h"

void Block::add_item(Item& item, const ItemBestPlace& place) {
    item.origin = place.origin;
    if(place.type == PlaceType::floor) {
        residual_floor_width -= item.size.width;
        floor.push_back(item);
    } else if(place.type == PlaceType::ceiling) {
        ceiling.push_back(item);
    }
}

void Block::add_item(Item& item) {
    add_item(item, find_best_place(item));
}

ItemBestPlace Block::find_best_place(const Item& item) {
    ItemBestPlace best_place;

    bool can_floor_fit = can_floor_fit_item(item);
    bool can_ceiling_fit = can_ceiling_fit_item(item);

    if(can_floor_fit)
        best_place = {shared_from_this(), {max_x() - residual_floor_width, origin.y}, PlaceType::floor, residual_floor_width - item.size.width};

    if(can_ceiling_fit) {
        int residual_width_after_fit = residual_ceiling_width() - item.size.width;
        if(!can_floor_fit || (can_floor_fit && residual_width_after_fit < best_place.residual_space)) {
            // if the floor can't fit the item or if the ceiling has a residual space less than residual space on the floor then update best_place
            int last_ceiling_item_min_x = ceiling.empty() ? max_x() : ceiling.back().min_x();
            Point new_origin = {last_ceiling_item_min_x - item.size.width, origin.y + (size.height - item.size.height)};
            best_place = {shared_from_this(), new_origin, PlaceType::ceiling, residual_width_after_fit};
        }
    }

#ifdef RECURSIVE_BLOCK
    bool is_this_block_fit_item = can_floor_fit || can_ceiling_fit;
    if(child_block) {
        //Trying to find a place with minimal residual space for the item in a child block
        auto child_best_place = child_block->find_best_place(item);
        bool is_child_block_fit_item = child_best_place.residual_space >= 0;
        bool is_child_place_better = is_this_block_fit_item && child_best_place.residual_space < best_place.residual_space;
        if(is_child_block_fit_item && (!is_this_block_fit_item || is_child_place_better))
            best_place = child_best_place;
    } else if(!is_this_block_fit_item && !ceiling.empty()) { 
        // Trying to find a child block if there is no space on the floor and ceiling
        child_block = find_block_with_largest_area(item);
        if(child_block)
            best_place = child_block->find_best_place(item);
    }
#endif

    return best_place;
}

std::ostream& operator<<(std::ostream& os, const Block& block) {
    for (auto &item : block.floor)
        os << item << "\n";
    for (auto &item : block.ceiling)
        os << item << "\n";
    if(block.child_block) 
        os << *block.child_block;
    return os;
}

std::shared_ptr<Block> Block::find_block_with_largest_area(const Item& item) {
    Frame max_frame;
    for(auto& ceiling_item : ceiling) {
        for (auto& floor_item : floor) {
            auto new_block_size = Size({ceiling_item.max_x() - floor_item.min_x(), 
                                        ceiling_item.min_y() - floor_item.max_y()});
            if(new_block_size >= 0 && new_block_size > item.size) {
                int area = new_block_size.width * new_block_size.height;
                int max_area = max_frame.size.width * max_frame.size.height;
                if(area > max_area) {
                    max_frame = Frame({floor_item.min_x(), floor_item.max_y()}, new_block_size);
                }
            }
        }
    }

    if(max_frame.size > 0) {
        return std::make_shared<Block>(Block(max_frame.size, max_frame.origin, min_item_height));
    }

    return nullptr;
}

bool Block::can_floor_fit_item(const Item& item) {
    bool is_fit_in_width = residual_floor_width - item.size.width >= 0;
    bool is_fit_in_height = true;
    
    int y_point = origin.y + item.size.height;
    for (auto &ceiling_item : ceiling){
        int x_point = ceiling_item.max_x() + item.size.width;
        // if the upper right point of the item has crossed any item on the ceiling, then we assume that this item does not fit on the floor in height
        if(ceiling_item.containts_point({x_point, y_point}) && x_point > ceiling_item.min_x()) { 
            is_fit_in_height = false;
            break;
        }
    }
    
    return is_fit_in_width && is_fit_in_height;
}

bool Block::can_ceiling_fit_item(const Item& item) {
    int ceiling_width = residual_ceiling_width();
    bool is_fit_in_width = ceiling_width - item.size.width >= 0;
    bool is_fit_in_height = true;
    
    int last_item_x_position = !ceiling.empty() ? ceiling.back().min_x() : max_x();

    auto new_item_origin = Point(last_item_x_position - item.size.width, max_y() - item.size.height);
    for (auto &floor_item : floor){
        // If the lower left point of the item has crossed any item on the floor, then we assume that this item does not fit on the ceiling in height
        if(floor_item.containts_point(new_item_origin) && new_item_origin.x < floor_item.max_x() && new_item_origin.y < floor_item.max_y()) { 
            is_fit_in_height = false;
            break;
        }
    }

    return is_fit_in_width && is_fit_in_height;
}

int Block::residual_ceiling_width() {
    // extra_floor_width is width of all the items on the floor, 
    // which do not have enough space between their upper edge and the upper edge of the block 
    // to fit even the lowest item. This width is extra for total residual width
    int extra_floor_width {};
    for (auto &floor_item : floor) {
        if(size.height - floor_item.size.height < min_item_height)
            extra_floor_width += floor_item.size.width;
    }

    return size.width - total_ceiling_width() - extra_floor_width;
}

inline int Block::total_ceiling_width() {
    int width {};
    for (auto& item : ceiling)
        width += item.size.width;
    return width;
}

inline int Block::max_x() {
    return origin.x + size.width;
}

inline int Block::max_y() {
    return origin.y + size.height;
}