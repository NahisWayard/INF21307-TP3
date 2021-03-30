#ifndef INF21307_TP3_PAGINATEDLIST_HPP
#define INF21307_TP3_PAGINATEDLIST_HPP

#include <vector>
#include <functional>
#include "Node.hpp"

template <typename T, size_t N = 10>
class PaginatedList {
public:
    typedef Node<T, N> NodeType;

    explicit PaginatedList() {
        head = new NodeType();
    }

    virtual ~PaginatedList() {
        delete head;
    }

    void append(T item) {
        Node<T, N> *prev = nullptr;
        auto *pageToAdd = head;

        while (pageToAdd != nullptr) {
            if (pageToAdd->hasAvailableSpace())
                break;
            prev = pageToAdd;
            pageToAdd = pageToAdd->links[Link::NEXT];
        }
        if (pageToAdd == nullptr) {
            auto *newPage = new NodeType;

            newPage->links[Link::PREVIOUS] = prev;
            prev->links[Link::NEXT] = newPage;
            pageToAdd = newPage;
        }
        pageToAdd->append(item);
    };

    size_t findOne(T item) {

    };

    std::vector<size_t> findMany(std::function<bool (T &item)> criteria) {

    };

    T &get(size_t index) {
        auto *p = head;
        size_t slots = p->usedSlots();

        while (index >= slots) {
            index -= slots;
            p = p->links[Link::NEXT];
            slots = p->usedSlots();
        }

        return p->get(index);
    };

    void remove(size_t index) {

    };

    void compact() {

    };

    size_t getPageCount() {
        size_t res = 1;

        for (auto *p = head; p != nullptr; (p = p->links[Link::NEXT]) && (res++));
        return res;
    };

    size_t getItemCount() {
        size_t res = 0;

        for (auto *p = head; p != nullptr; (res += p->usedSlots()) && (p = p->links[Link::NEXT]));
        return res;
    };

private:


private:
    NodeType *head;
};

#endif
