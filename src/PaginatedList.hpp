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
        tail = head;
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
            tail = newPage;
        }
        pageToAdd->append(item);
    };

    size_t findOne(T item) {
        size_t res = -1;

        for (auto *p = head; p != nullptr; p = p->links[Link::NEXT]) {
            for (size_t intIndex = 0; intIndex < N; intIndex++) {
                if (!p->isUsed(intIndex))
                    continue;
                res++;
                if (item == p->data[intIndex])
                    return res;
            }
        }
        return UINTMAX_MAX;
    };

    std::vector<size_t> findMany(std::function<bool (T &item)> criteria) {
        std::vector<size_t> res = {};
        size_t id = -1;

        for (auto *p = head; p != nullptr; p = p->links[Link::NEXT]) {
            for (size_t intIndex = 0; intIndex < N; intIndex++) {
                if (p->isUsed(intIndex)) {
                    id++;
                    if (criteria(p->data[intIndex]))
                        res.push_back(id);
                }
            }
        }
        return res;
    };

    void printPagesAndItems(){
        size_t page = 0;
        size_t absoluteIdx = 0;
        size_t realIdx = 0;

        std::cout << "----------------------------------------------------" << std::endl;
        for (auto *p = head; p != nullptr; (p = p->links[Link::NEXT])){
            std::cout << "[ PAGE " << page << " ]"<< std::endl;

            for (std::size_t i = 0; i < p->capacity.size(); i++) {
                if (p->capacity[i] == true) {
                    std::cout << "|" << realIdx  << "| " <<"[" << i << "] - " << p->getData()[i] << " - " << absoluteIdx << std::endl;
                    realIdx++;
                }
                else {
                    std::cout << "|X| " << "[" << i << "] - EMPTY - " << absoluteIdx << std::endl;
                }
                absoluteIdx++;
            }
            page++;
            std::cout << std::endl;
        }
        std::cout << "-------------" << std::endl;
        std::cout << "Page count: " << this->getPageCount() << std::endl;
        std::cout << "Item count: " << this->getItemCount() << std::endl;
        std::cout << "----------------------------------------------------" << std::endl;
        std::cout << std::endl;
    }

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

    T &get(size_t index) {
        auto *p = head;
        size_t slots = p->usedSlots();

        if (index > getItemCount())
            throw std::out_of_range("Out of range index");

        while (index >= slots) {
            index -= slots;
            p = p->links[Link::NEXT];
            slots = p->usedSlots();
        }

        return p->get(index);
    };

    void remove(size_t indexToRemove) {
        for (auto *p = head; p != nullptr; (p = p->links[Link::NEXT])){
            size_t usedSlots = p->usedSlots();

            if (indexToRemove >= usedSlots) {
                indexToRemove -= usedSlots;
                continue;
            }

            size_t intIdx = p->getInternalIndex(indexToRemove);
            p->capacity[intIdx] = false;
            break;
        }
    };

    void compact() {
        auto *t = tail;
        auto *h = head;

        T tmpItem = 0;
        size_t toFill = 0;
        size_t toPlace = 0;

        for (auto *p = head; p != nullptr; (p = p->links[Link::NEXT])){
            this->compactPage(p);
        }

        while (this->getFirstPageToPlaceItem() != t &&
               this->getFirstPageToPlaceItem() != nullptr) {

            h = this->getFirstPageToPlaceItem();

            toFill = h->firstAvailableIndex();
            toPlace = t->lastFilledIndex();

            tmpItem = t->get(toPlace);
            h->capacity[toFill] = tmpItem;
            h->capacity[toFill] = true;
            t->capacity[toPlace] = false;

            if (t->isEmpty() == true) {
                t = t->links[Link::PREVIOUS];
                this->unlinkPage(t->links[Link::NEXT]); // TODO fonction temporaire a remplacer
            }
        }
    };

private:
    NodeType *getFirstPageToPlaceItem(){
        for (auto *p = head; p != nullptr; (p = p->links[Link::NEXT])){
            if (p->hasAvailableSpace() == true){
                return p;
            }
        }
        return nullptr;
    }

    void compactPage(Node<T, N> *p) {

        T tmpItem = 0;
        size_t toFill = p->firstAvailableIndex();
        size_t toPlace = p->lastFilledIndex();

        while (toFill < toPlace) {
            tmpItem = p->data[toPlace];
            p->data[toFill] = tmpItem;
            p->capacity[toFill] = true;
            p->capacity[toPlace] = false;

            toPlace = p->lastFilledIndex();
            toFill = p->firstAvailableIndex();
        }
    }

    void unlinkPage(NodeType *p){

        NodeType *tmp = p;

        if (p == head)
            return;

        if (p == tail) {
            tmp = p->links[Link::PREVIOUS];
            tmp->links[Link::NEXT] = nullptr;
            p->links[Link::NEXT] = nullptr;
            delete p;
            return;
        }

        tmp = p->links[Link::PREVIOUS];
        tmp->links[Link::NEXT] = p->links[Link::NEXT];
        p->links[Link::NEXT]->links[Link::PREVIOUS] = tmp;
        p->links[Link::NEXT] = nullptr;
        p->links[Link::PREVIOUS] = nullptr;
    }

private:
    NodeType *head;
    NodeType *tail;
};

#endif
