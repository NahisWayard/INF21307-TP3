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
}
