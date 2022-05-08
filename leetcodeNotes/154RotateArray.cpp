#include <vector>
#include "math.h"
using namespace std;

class Solution {
public:
    int minNumberInRotateArray(vector<int> rotateArray) {
        int low, mid, high;
        low = 0;
        high = rotateArray.size()-1;
        while(low <= high){
            mid = floor((high+low)/2);
            if( rotateArray[mid] > rotateArray[high])
                low = mid + 1;
            else if(rotateArray[mid] == rotateArray[high])
                high--;
            else{
                high = mid;
            }

        }
        return rotateArray[low];

    }
};

