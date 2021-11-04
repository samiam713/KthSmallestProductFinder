//
//  NaiveSolution.cpp
//  HeapLeetCode
//
//  Created by Samuel Donovan on 11/4/21.
//

#include "NaiveSolution.hpp"
#include "Global.h"

using namespace std;

Int NaiveSolution::kthSmallestProduct(vector<int>& nums1, vector<int>& nums2, Int k) {
   vector<Int> products;
   for(int num1 : nums1) {
       for(int num2 : nums2) {
           products.push_back(Int(num1)*Int(num2));
       }
   }
   sort(products.begin(),products.end());
   return products[k-1];
}
