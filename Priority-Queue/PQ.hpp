#ifndef PQ_HPP
#define PQ_HPP

#include <vector>

template <typename T> class MaxHeap {
  private:
    std::vector<T> heap;

    int parent(int k) { return (k - 1) / 2; }
    int lchild(int k) { return 2 * k + 1; }

    void swim(int k) {
        while (k > 1 && heap[parent(k)] < heap[k]) {
            std::swap(heap[k], heap[parent(k)]);
            k = parent(k);
        }
    }

    void sink(int k) {
        while (lchild(k) < heap.size()) {
            int j = lchild(k);
            if (j + 1 < heap.size() && heap[j + 1] > heap[j])
                j++;
            if (heap[k] >= heap[j])
                break;
            std::swap(heap[k], heap[j]);
            k = j;
        }
    }

  public:
    void push(const T &t) {
        heap.emplace_back(t);
        swim(heap.size() - 1);
    }

    T top() { return heap.front(); }

    void pop() {
        std::swap(heap.front(), heap.back());
        heap.pop_back();
        sink(0);
    }
};

#endif // PQ_HPP
