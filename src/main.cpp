#include <iostream>
#include "PaginatedList.hpp"

int main(int ac, char **av) {
    auto list = PaginatedList<int, 10>();
    size_t itemsToTest = 20;

    for (size_t i = 0; i < itemsToTest; i++) {
        list.append(i);
    }

    /*for (size_t i = 0; i < itemsToTest; i++) {
        std::cout << list.get(i) << std::endl;
    }

    std::cout << "Page count: " << list.getPageCount() << std::endl;
    std::cout << "Item count: " << list.getItemCount() << std::endl;*/


/*
    list.remove(2);
    list.remove(3);
    list.remove(4);
    //list.remove(5);
    list.remove(6);
    list.remove(7);
    //list.remove(8);

    list.remove(15);
    list.remove(10);
    //list.remove(12);
    list.remove(16);
    //list.remove(20);

    list.printPagesAndItems();
    list.compact();
    list.printPagesAndItems();

    //std::cout <<
    //list.getLastEmptyPage();
*/

/*
    list.remove(0);
    list.remove(2);
    list.remove(4);
    list.remove(6);
    list.remove(8);
    list.remove(10);
*/
    list.remove(5);
    list.printPagesAndItems();
    std::cout << "6 == " << list.get(5) << std::endl;
    std::cout << "7 == " << list.get(6) << std::endl;
    std::cout << "0 == " << list.get(0) << std::endl;
    std::cout << "4 == " << list.get(4) << std::endl;


    /* std::cout << "Size of find many: " << list.findMany([] (int item) {
        if (item == 40 || item == 13)
            return true;
        return false;
    }).size() << std::endl; */
}
