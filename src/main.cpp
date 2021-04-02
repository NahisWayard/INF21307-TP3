#include <iostream>
#include "PaginatedList.hpp"

int main(int ac, char **av) {
    auto list = PaginatedList<int>();
    size_t itemsToTest = 42;

    for (size_t i = 0; i < itemsToTest; i++) {
        list.append(i + 1);
    }

    for (size_t i = 0; i < itemsToTest; i++) {
        std::cout << list.get(i) << std::endl;
    }
    std::cout << "Page count: " << list.getPageCount() << std::endl;
    std::cout << "Item count: " << list.getItemCount() << std::endl;

    std::cout << "Idx for 3: " << list.findOne(42) << std::endl;
    std::cout << "Size of find many: " << list.findMany([] (int item) {
        if (item == 40 || item == 13)
            return true;
        return false;
    }).size() << std::endl;
}
