//
//  2293.c
//  CommonTool
//
//  Created by lizihong on 2023/1/16.
//  Copyright © 2023 AL. All rights reserved.
//

#include "2293.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>


int minMaxGame(int* nums, int numsSize){
    if (numsSize == 1) return nums[0];
    int n = numsSize>>1;
    int newNums[n];
    
    while (n >= 1) {
        for (int i = 0; i < n; ++i) {
            if (i%2 == 0) {
                newNums[i] = fmin(nums[2*i], nums[2*i+1]);
            } else {
                newNums[i] = fmax(nums[2*i], nums[2*i+1]);
            }
        }
        n = n>>1;
        nums = newNums;
    }
    return newNums[0];
}
