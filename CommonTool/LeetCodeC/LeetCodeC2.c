//
//  LeetCodeC2.c
//  CommonTool
//
//  Created by lizihong on 2021/2/8.
//  Copyright © 2021 AL. All rights reserved.
//

#include "LeetCodeC2.h"


int majorityElement(int* nums, int numsSize){
    // 先用投票法找出较多的元素(如果有多个数量一样的，那么得到的是最后一个出现的较多元素)
    int result = nums[0];
    int score = 1;
    for (int i = 1; i < numsSize; ++i) {
        if (score == 0) {
            result = nums[i];
        }
        if (nums[i] == result) {
            score += 1;
        }else{
            score -= 1;
        }
    }
    // 计算该元素的个数
    int count = 0;
    for (int i = 0; i < nums[i]; ++i) {
        if (nums[i] == result) ++count;
    }
    return (count>=numsSize/2+1)?result:-1;
}
