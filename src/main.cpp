#include <iostream>
#include "PaginatedList.hpp"

int main() {
    auto list = PaginatedList<int, 10>();
    size_t itemsToTest = 20;

    for (size_t i = 0; i < itemsToTest; i++) {
        list.append(i);
    }


    //list.printPagesAndItems();

    list.remove(0);
    for (int i = 0; i < 6; i++)
        list.remove(5);
    list.remove(10);

    //list.printPagesAndItems();

    list.compact();
    list.printPagesAndItems();

    list.remove(0);
    list.remove(0);
    list.compact();
    list.printPagesAndItems();

    try {
        std::cout << "4 == " << list.get(25000000) << std::endl;
    } catch (const std::out_of_range &e) {
        std::cout.flush();
        std::cerr << e.what() << std::endl;
    }


    /* std::cout << "Size of find many: " << list.findMany([] (int item) {
        if (item == 40 || item == 13)
            return true;
        return false;
    }).size() << std::endl; */
}
