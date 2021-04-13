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
        capacity.reset();
    }

    virtual ~Node() {
        std::cout << "Deleted page" << std::endl;
        if (links[NEXT] != nullptr)
            delete links[NEXT];
    }

    bool hasAvailableSpace() const {
        return !capacity.all();
    }

    bool isEmpty() const {
        if (capacity == 0) {
            return true;
        }
        return false;
    }

    void append(T item) {
        auto idx = firstAvailableIndex();

        capacity[idx] = true;
        data[idx] = item;
    }

    size_t usedSlots() const {
        return capacity.count();
    }

    T &get(size_t idx) {
        auto intIdx = getInternalIndex(idx);

        if (intIdx == UINTMAX_MAX)
            throw std::out_of_range("Out of range index");
        return data[intIdx];
    }

    size_t getInternalIndex(size_t idx) {
        if (capacity.none() || idx + 1 > capacity.count())
            return UINTMAX_MAX;
        if (capacity.all())
            return idx;

        for (size_t i = 0; i <= idx; i++) {
            if (capacity[i] == false)
                idx++;
        }
        return idx;
    }

    size_t firstAvailableIndex() const {
        for (size_t i = 0; i < N; i++) {
            if (capacity[i] == false)
                return i;
        }
        return UINTMAX_MAX;
    }

    size_t lastFilledIndex() const {
        for (size_t i = N; i >= 0; i--) {
            if (capacity[i] == true)
                return i;
        }
        return UINTMAX_MAX;
    }

    const T *getData() const {
        return data;
    }

    Node<T, N> *links[2];
    std::bitset<N> capacity;
    T data[N];
};

#endif
