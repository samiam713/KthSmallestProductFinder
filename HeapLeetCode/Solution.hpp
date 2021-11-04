//
//  Solution.hpp
//  HeapLeetCode
//
//  Created by Samuel Donovan on 11/4/21.
//

#ifndef Solution_hpp
#define Solution_hpp

#include <iostream>
#include <vector>
#include "Heap.h"
#include "Global.h"

struct ProductStatement {
    Int num1Index;
    Int num2Index;
    Int equals;
    
    bool tag;
};

bool heapOrderer(ProductStatement first, ProductStatement second);

struct Boundaries {
    Int endNegatives;
    Int endZeros;
    Int endPositives;
    
    Int numZeros() const {
        return endZeros - endNegatives;
    }
};

void setBoundaries(Boundaries* boundaries, std::vector<int>& vector);

struct KthSmallestProductFinder {
    std::vector<int>* nums1;
    std::vector<int>* nums2;
    
    Boundaries boundaries1;
    Boundaries boundaries2;
    
    Int k;
    bool done;
    Int ans;
    
    KthSmallestProductFinder(std::vector<int>& nums1, std::vector<int>& nums2, Int k);
    
    Int getAns();
    
    void kthSmallestFromNegatives();
    void kthSmallestFromPositives();
    void kthSmallestFromZeros();
};

#endif /* Solution_hpp */
