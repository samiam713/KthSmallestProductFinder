//
//  Heap.hpp
//  HeapExample
//
//  Created by Samuel Donovan on 4/21/20.
//  Copyright © 2020 Samuel Donovan. All rights reserved.
//

#ifndef Heap_hpp
#define Heap_hpp

#include <vector>
#include <iostream>
#include <algorithm>

template <typename T,typename Op>
class Heap {
public:
    Heap(std::vector<T> const & heap, Op op) :
    heap(heap) , op(op) {
        size_t const x = heap.size()/2;
        for (size_t i = x; i <= x; i--) {
            trickleDown(i);
        }
    };
    
    Heap(std::vector<T> const & heap) :
    heap(heap) , op() {
        size_t const x = heap.size()/2;
        for (size_t i = x; i <= x; i--) {
            trickleDown(i);
        }
    };
    
    Heap(Op op) :
    heap(), op(op) {};
    
    Heap() :
    heap() , op() {};
    
    void insert(T const & item);
    const T& front();
    void popFront();
    friend std::ostream& operator<<(std::ostream& os, Heap<T,Op> const & heap) {
        if (heap.empty()) {
            std::cout << "EMPTY_HEAP";
            return os;
        }
        int lol = 0;
        for (const auto& item : heap.heap) {
            os << lol << ':' << item << ' ';
            lol++;
        }
        return os;
    }
    bool empty() const {return heap.empty();}
    
private:
    void trickleUp(size_t child);
    void trickleDown(size_t parent);
    Op op;
    std::vector<T> heap;
};

template <typename T,typename Op>
void Heap<T,Op>::insert(T const & item) {
    this->heap.push_back(item);
    trickleUp(heap.size()-1);
}

template <typename T,typename Op>
const T& Heap<T,Op>::front() {
    return heap.front();
}

template <typename T,typename Op>
void Heap<T,Op>::popFront() {
    if (heap.size() < 2) {
        if (heap.size() == 1) {
            heap.clear();
            return;
        } else {
            throw std::logic_error("Popping from empty heap");
        }
    }
    
    heap.front() = heap.back();
    heap.pop_back();
    trickleDown(0);
    
}

template <typename T,typename Op>
void Heap<T,Op>::trickleUp(size_t child) {
    if (child == 0) return;
    
    size_t const parent = (child - 1)/2;
    
    if (op(heap[child],heap[parent])) {
        std::swap(heap[child], heap[parent]);
        trickleUp(parent);
    }
    
}

template <typename T,typename Op>
void Heap<T,Op>::trickleDown(size_t parent) {
    
    size_t const og = parent;
    size_t const child1 = 2*parent + 1;
    size_t const child2 = child1 + 1;
    
    if (child1 >= heap.size()) return;
    
    if (op(heap[child1],heap[parent])) {
        parent = child1;
    }
    
    if (child2 < heap.size()) {
        if (op(heap[child2],heap[parent])) {
            parent = child2;
        }
    }
    if (parent != og) {
        std::swap(heap[og], heap[parent]);
        trickleDown(parent);
    }
}

#endif /* Heap_hpp */
