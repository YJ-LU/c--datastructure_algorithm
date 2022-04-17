//
// Created by YJ on 2022/4/17.
//
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        //choose two as a window, and sum with the third number
        vector<int>::iterator it;
        for(it=nums.begin();it!=nums.end();++it){

        }

        if( nums.empty()){
            return {};
        }
        if( nums.size() == 1 && nums[0] == 0){
            return {};
        }

    }
};

