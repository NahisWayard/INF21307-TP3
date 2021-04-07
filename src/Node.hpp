#ifndef INF21307_TP3_NODE_HPP
#define INF21307_TP3_NODE_HPP

#include <bitset>

enum Link {
    PREVIOUS = 0,
    NEXT = 1
};

template <typename T, size_t N>
class Node {
public:
    Node() : capacity() {
        std::cout << "New page" << std::endl;
        links[PREVIOUS] = nullptr;
        links[NEXT] = nullptr;
    }

    bool hasAvailableSpace() const {
        return !capacity.all();
    }

    void append(T item) {
        auto idx = firstAvailableIndex();

        capacity[idx] = true;
        data[idx] = item;
    }

    size_t usedSlots() const {
        return capacity.count();
    }

    std::bitset<N> getCapacity() const {
        return capacity;
    }

    void setBitOnCapacity(size_t pos, bool bitValue) {
        capacity[pos] = bitValue;
    }

    T &get(size_t idx) {
        return data[idx];
    }

    bool isUsed(size_t idx) {
        return capacity[idx];
    }

private:
    size_t firstAvailableIndex() const {
        for (size_t i = 0; i < N; i++) {
            if (!capacity[i])
                return i;
        }
        return UINTMAX_MAX;
    }

public:
    Node<T, N> *links[2];
private:
    std::bitset<N> capacity;
    T data[N]; // int data[10]

};

#endif
