#include <iostream>
#include "unit.h"

int main() {
    int unit_width {};
    std::cin >> unit_width;

    int number_of_rectangles {};
    std::cin >> number_of_rectangles;

    Unit unit(unit_width);
    
    for (size_t i = 0; i < number_of_rectangles; i++) {
        int width {};
        int height {};

        std::cin >> width;
        std::cin >> height;
        if(width > unit_width)
            continue;
        unit.add_item(Item(Size(width,height)));
    }
    
    unit.start_packaging();
    std::cout << unit << std::endl;

    return 0;
}