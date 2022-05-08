//
// Created by YJ on 2022/4/17.
//
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        //choose two as a window, and sum with the third number
//        vector<int>::iterator it;
//        for(it=nums.begin();it!=nums.end();++it){
//
//        }
        int n = nums.size();
        //vector<int> v(nums);
        vector<int> zero;
        vector<vector<int>> res;
        int window, sum;
        for(int i=0; i<n-1; i++){
            window = nums[i]+nums[i+1];
            for(int j = i+2; j<n-1; j++){
                sum = window + nums[j];
                if( sum == 0){
                    zero.insert(zero.begin(),nums[i]);
                    zero.insert(zero.begin()+1,nums[i+1]);
                    zero.insert(zero.begin()+2,nums[j]);
                    res.push_back(zero);
                    zero.clear();
                    break;
                }
            }
        }

        // nums = {}
        if( nums.empty()){
            return {};
        }
        // nums={0}
        if( nums.size() == 1 && nums[0] == 0){
            res.insert(res.begin(),nums);
            return res;
        }
    }

    vector<vector<int>> threeSum2(vector<int>& nums){
        //double pointer

        // to avoid duplicate, can sort the vector first
        // O(NlogN)
        sort(nums.begin(), nums.end()); // very important

        vector<vector<int>> res;
        vector<int> v;
        for(auto it = nums.begin(); it != nums.end(); ++it){
            if( *it > 0)
                break;


            else{
                auto left = it + 1;
                auto right = nums.end() - 1;
                // sorted
                while (left < right){
                    if(*it + *left + *right > 0){
                        right--;
                    }
                    else if(*it + *left + *right < 0){
                        left++;
                    }
                    else{ //*it + *left + *right = 0
                        v.push_back(*it);
                        v.push_back(*left);
                        v.push_back(*right);
                    }
                    res.push_back(v);
                }
            }
            return res;

        }




    }
};

