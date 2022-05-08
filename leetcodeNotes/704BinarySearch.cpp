//
// Created by apple on 2022/5/7.
//
#include <vector>
#include <math.h>
using namespace std;
class Solution {
public:

    int search(vector<int>& nums, int target) {
        // write code here
        int n = nums.size();
        int mid;
        while (n > 1) {
            if (nums[n] == target)
                break;
            if (n % 2 == 0) {
                mid = (nums[n / 2] + nums[n / 2 + 1]) / 2;
                if (mid > target) // mid right
                    n = (n / 2 + n) / 2;
                else // mid left
                    n = n / 4;
            }
            if (n % 2 == 1) {
                mid = nums[((n + 1) / 2)-1];
                if (mid == target) {
                    n = (n + 1) / 2;
                    return n;
                } else if (mid > target) { // find left
                    n = (n + 1) / 4;
                } else {
                    n = (n + (n + 1) / 2) / 2;
                }
            }
            return n;
        }
    }


    // 2ms
    int search2(vector<int>& nums, int target) {
        int low, mid, high;
        low = 0;
        high = nums.size()-1;
        while( low <= high){
            mid = floor(nums[(low+high)/2]);
            if(nums[mid] == target)
                return mid;
            else if( nums[mid] > target){ // find left
                high = mid - 1;
            }
            else{ //find right
                low = mid + 1;
            }
        }
        return -1;

    }
};

