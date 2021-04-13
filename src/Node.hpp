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

    std::bitset<N> getCapacity() const {
        return capacity;
    }

    void setBitOnCapacity(size_t pos, bool bitValue) {
        capacity[pos] = bitValue;
    }

    T &get(size_t idx) {
        size_t offset = 0;

        for (size_t i = 0; i < capacity.size() && i < idx; i++) {
            if (capacity[i] == false)
                offset++;
        }
        return data[idx + offset];
    }

    void setDataByIndex(size_t idx, T nData) {
        data[idx] = nData;
    }

    bool isUsed(size_t idx) const {
        return capacity[idx];
    }

    size_t getInternalIndex(size_t idx) {
        if (capacity.none() || idx + 1 > capacity.count())
            return UINTMAX_MAX;
        if (capacity.all())
            return idx;

        for (int i = 0; i <= idx; i++) {
            if (capacity[i] == false)
                idx++;
        }
        return idx;
    }

//private:
    size_t firstAvailableIndex() const {
        for (size_t i = 0; i < N; i++) {
            if (!capacity[i])
                return i;
        }
        return UINTMAX_MAX;
    }

    size_t lastFilledIndex() const {
        for (size_t i = N; i >= 0; i--) {
            if (isUsed(i) == true)
                return i;
        }
        return UINTMAX_MAX;
    }

    const T *getData() const {
        return data;
    }
public:
    Node<T, N> *links[2];
private:
    std::bitset<N> capacity;
    T data[N];
};

#endif
