#include <iostream>
#include "PaginatedList.hpp"

int main() {
    auto list = PaginatedList<int, 10>();
    size_t itemsToTest = 30;

    for (size_t i = 0; i < itemsToTest; i++) {
        list.append(i);
    }
    list.printPagesAndItems();


    auto res = list.findMany([] (int item) {
        if (item % 3 == 0)
            return true;
        return false;
    });
    std::cout << "Items where i % 3 == 0" << std::endl;
    for (auto &i : res) {
        std::cout << list.get(i) << std::endl;
    }


    list.remove(25);
    list.remove(0);
    std::cout << "Index of value 10: " << list.findOne(10) << std::endl;
    std::cout << "Index of value 27: " << list.findOne(27) << std::endl;

    for (int i = 0; i < 10; i++)
        list.remove(9);
    list.printPagesAndItems();
    list.compact();
    std::cout << "Unlinked mid page" << std::endl;
    list.printPagesAndItems();

    for (int i = 0; i < 9; i++)
        list.remove(10);
    list.compact();
    std::cout << "Unlinked tail page" << std::endl;
    list.printPagesAndItems();

    for (int i = 0; i < 10; i++)
        list.remove(0);
    list.printPagesAndItems();
    list.compact();
    std::cout << "Should not remove the last page" << std::endl;
    list.printPagesAndItems();

    try {
        list.get(25000000);
    } catch (const std::out_of_range &e) {
        std::cout.flush();
        std::cerr << e.what() << std::endl;
    }
}
