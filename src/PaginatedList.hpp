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
        if (N >= UINTMAX_MAX)
            throw std::invalid_argument("N must be inferior to UINTMAX_MAX");
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
        size_t res = -1;
        for (auto *p = head; p != nullptr; p = p->links[Link::NEXT]) {
            for (size_t idx = 0; idx < N; idx++) {
                if (p->isUsed(idx)) {
                    res++;
                    if (item == p->get(idx))
                        return res;
                }
            }
        }
        return UINTMAX_MAX;
    };

    std::vector<size_t> findMany(std::function<bool (T &item)> criteria) {
        std::vector<size_t> res = {};
        size_t id = -1;

        for (auto *p = head; p != nullptr; p = p->links[Link::NEXT]) {
            for (size_t idx = 0; idx < N; idx++) {
                if (p->isUsed(idx)) {
                    id++;
                    if (criteria(p->get(idx)))
                        res.push_back(id);
                }
            }
        }
        return res;
    };

    T &get(size_t index) {
        auto *p = head;
        //TODO Works only when pages are full ???
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
