//
//  Solution.cpp
//  HeapLeetCode
//
//  Created by Samuel Donovan on 11/4/21.
//

#include "Solution.hpp"

using namespace std;

bool heapOrderer(ProductStatement first, ProductStatement second) {return first.equals < second.equals;}


void setBoundaries(Boundaries* boundaries, vector<int>& vector) {
    // naive (advanced would binary search)
    
    Int i = 0;
    Int vectorSize = Int(vector.size());
    
    while (i < vectorSize && vector[i] < 0) i++;
    boundaries->endNegatives = i;
    
    while (i < vectorSize && vector[i] == 0) i++;
    boundaries->endZeros = i;
    
    boundaries->endPositives = (Int)vector.size();
}



KthSmallestProductFinder::KthSmallestProductFinder(vector<int>& nums1, vector<int>& nums2, Int k) :
nums1(&nums1), nums2(&nums2), k(k), done(false), ans(0) {
    setBoundaries(&boundaries1, nums1);
    setBoundaries(&boundaries2, nums2);
    if (k > nums1.size()*nums2.size()) {
        done = true;
        ans = LONG_LONG_MIN;
    }
}

Int KthSmallestProductFinder::getAns() {
    if (done) return ans;
    
    kthSmallestFromNegatives();
    if (done) return ans;
    kthSmallestFromZeros();
    if (done) return ans;
    kthSmallestFromPositives();
    if (done) return ans;
    return LONG_LONG_MIN;
}

void KthSmallestProductFinder::kthSmallestFromNegatives() {
    // use a heap to search for k-th smallest negative product:
    Heap<ProductStatement, bool(*)(ProductStatement,ProductStatement)> searching(&heapOrderer);
    
    //     start from (maxAbsNeg1,maxAbsPos2) and move by (1,0) and (0,-1)
    //     TAG == TRUE
    if (boundaries1.endNegatives > 0 && boundaries2.endZeros != boundaries2.endPositives) {
        Int maxAbsPos2 = boundaries2.endPositives-1;
        Int equals = (Int)((*nums1)[0]) * (Int)((*nums2)[maxAbsPos2]);
        searching.insert({0,maxAbsPos2,equals,true});
    }
    
    //     start from (maxAbsPos1,maxAbsNeg2) and move by (-1,0) and (0,1)
    //     TAG == FALSE
    if (boundaries2.endNegatives > 0 && boundaries1.endZeros != boundaries1.endPositives) {
        Int maxAbsPos1 = boundaries1.endPositives-1;
        Int equals = Int((*nums1)[maxAbsPos1])*Int((*nums2)[0]);
        searching.insert({maxAbsPos1,0,equals,false});
    }
    
    Int highest1Index = 0;
    Int highest2Index = 0;
    
    while (!searching.empty()) {
        ProductStatement ps = searching.front();
        searching.popFront();
        
#if PRINTING
        // nums1[i]*nums2[j] == equals
        cout << "nums1[" << ps.num1Index << "]*nums2[" << ps.num2Index << "] == " << ps.equals << endl;
#endif
        
        if (k == 1) {
            ans = ps.equals;
            done = true;
            return;
        }
        else k--;
        
        // add potential next things to search
        if (ps.tag) {
            if (ps.num2Index > boundaries2.endZeros) {
                Int equals = Int((*nums1)[ps.num1Index])*Int((*nums2)[ps.num2Index-1]);
                searching.insert({ps.num1Index,ps.num2Index-1,equals,true});
            }
            
            if (ps.num1Index == highest1Index && ps.num1Index < boundaries1.endNegatives-1) {
                Int equals = Int((*nums1)[ps.num1Index+1])*Int((*nums2)[boundaries2.endPositives-1]);
                searching.insert({ps.num1Index+1,boundaries2.endPositives-1,equals,true});
                highest1Index++;
            }
        } else {
            // do above but for a positive 1 and a negative 2
            if (ps.num1Index > boundaries1.endZeros) {
                Int equals = (Int)((*nums1)[ps.num1Index-1])*(Int)((*nums2)[ps.num2Index]);
                searching.insert({ps.num1Index-1,ps.num2Index,equals,false});
            }
            
            if (ps.num2Index == highest2Index && ps.num2Index < boundaries2.endNegatives-1) {
                Int equals = Int((*nums1)[boundaries1.endPositives-1])*Int((*nums2)[ps.num2Index+1]);
                searching.insert({boundaries1.endPositives-1,ps.num2Index+1,equals,false});
                highest2Index++;
            }
        }
    }
}

void KthSmallestProductFinder::kthSmallestFromPositives() {
    // use a heap to search for k-th smallest positive product:
    Heap<ProductStatement, bool(*)(ProductStatement,ProductStatement)> searching(&heapOrderer);
    
    
    //     start from (minAbsNeg0,minAbsNeg1) and move by (-1,0) and (0,-1)
    //     TAG == TRUE
    if (boundaries1.endNegatives > 0 && boundaries2.endNegatives > 0) {
        Int minAbsNeg1 = boundaries1.endNegatives-1;
        Int minAbsNeg2 = boundaries2.endNegatives-1;
        
        Int equals = Int((*nums1)[minAbsNeg1])*Int((*nums2)[minAbsNeg2]);
        searching.insert({minAbsNeg1,minAbsNeg2,equals,true});
    }
    
    //     start from (minAbsPos0,minAbsPos1) and move by (1,0) and (0,1)
    //     TAG == FALSE
    if (boundaries1.endZeros != boundaries1.endPositives && boundaries2.endZeros != boundaries2.endPositives) {
        Int minAbsPos1 = boundaries1.endZeros;
        Int minAbsPos2 = boundaries2.endZeros;
        
        Int equals = Int((*nums1)[minAbsPos1])*Int((*nums2)[minAbsPos2]);
        searching.insert({minAbsPos1,minAbsPos2,equals,false});
    }
    
    Int lowest1IndexTrue = boundaries1.endNegatives-1;
    Int highest1IndexFalse = boundaries1.endZeros;
    
    while (!searching.empty()) {
        ProductStatement ps = searching.front();
        searching.popFront();
        
#if PRINTING
        // nums1[i]*nums2[j] == equals
        cout << "nums1[" << ps.num1Index << "]*nums2[" << ps.num2Index << "] == " << ps.equals << endl;
#endif
        
        if (k == 1) {
            ans = ps.equals;
            done = true;
            return;
        }
        else k--;
        
        if (ps.tag) {
            // try to go lower on the right
            if (ps.num2Index > 0) {
                Int equals = Int((*nums1)[ps.num1Index])*Int((*nums2)[ps.num2Index-1]);
                
                searching.insert({ps.num1Index,ps.num2Index-1,equals,true});
            }
            
            // try to go lower on the left if necessary
            if (ps.num1Index == lowest1IndexTrue && ps.num1Index > 0) {
                Int minAbsNeg2 = boundaries2.endNegatives-1;
                Int equals = Int((*nums1)[ps.num1Index-1])*Int((*nums2)[minAbsNeg2]);
                
                searching.insert({ps.num1Index-1,minAbsNeg2,equals,true});
                lowest1IndexTrue--;
            }
        } else {
            // try to go higher on the right
            if (ps.num2Index < boundaries2.endPositives-1) {
                Int equals = Int((*nums1)[ps.num1Index])*Int((*nums2)[ps.num2Index+1]);
                
                searching.insert({ps.num1Index,ps.num2Index+1,equals,false});
            }
            
            // try to go higher on the left if necessary
            if (ps.num1Index == highest1IndexFalse && ps.num1Index < boundaries1.endPositives-1) {
                Int minAbsPos2 = boundaries2.endZeros;
                Int equals = Int((*nums1)[ps.num1Index+1])*Int((*nums2)[minAbsPos2]);
                
                searching.insert({ps.num1Index+1,minAbsPos2,equals,false});
                highest1IndexFalse++;
            }
        }
    }
}

void KthSmallestProductFinder::kthSmallestFromZeros() {
    Int zerosPossible = boundaries1.numZeros()*boundaries2.endPositives + boundaries2.numZeros()*(boundaries1.endPositives - boundaries1.numZeros());
    
#if PRINTING
    cout << zerosPossible << " zeros" << endl;
#endif
    
    k -= zerosPossible;
    if (k < 1) {
        done = true;
        ans = 0;
    }
}

