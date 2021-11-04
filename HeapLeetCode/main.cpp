//
//  main.cpp
//  HeapLeetCode
//
//  Created by Samuel Donovan on 10/18/21.
//

// PROBLEM
// given vector<int> nums1, vector<int> nums2, long long k,
// of all possible products nums1[i]*nums2[j], finds the k-th smallest one (1-based index)

// SOLUTIONS:
// KthSmallestProductFinder class
//     works very efficiently for k small relative to nums1.size()*nums2.size()
//     This class was a lot of work and is cool^

// NaiveSolution class
//    just puts all possible products in a vector, sorts them, and picks the kth one

#include "NaiveSolution.hpp"
#include "Solution.hpp"
#include "Global.h"

using namespace std;

int main(int argc, const char * argv[]) {
    
    
    vector<int> nums1 = NUMS1;
    vector<int> nums2 = NUMS2;
    Int goal = WHICH;
    
// #if PRINTING
    cout << NaiveSolution::kthSmallestProduct(nums1, nums2, goal) << endl;
// #endif
    cout << KthSmallestProductFinder(nums1,nums2,goal).getAns() << endl;
    
    return 0;
}
