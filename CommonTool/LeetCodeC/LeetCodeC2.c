//
//  LeetCodeC2.c
//  CommonTool
//
//  Created by lizihong on 2021/2/8.
//  Copyright © 2021 AL. All rights reserved.
//

#include "LeetCodeC2.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>

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

bool isUnique(char* astr){
    // hash表
    int ascMap[256] = {0};
    while (*astr) {
        ascMap[*astr] += 1;
        if (ascMap[*astr] > 1) {
            return false;
        }
        ++astr;
    }
    return true;
    
    // bit数位记录(原理上与hash表类似，不过用的空间更少)
    long mark64 = 0;
    long mark128 = 0;
    long mark192 = 0;
    long mark256 = 0;
    
    while (*astr) {
        long value = *astr;
        if (value < 64) {
            value = (long)1 << value;
            if ((mark64&value) != 0) {
                return false;
            }
            mark64 |= value;
        }else if (value < 128) {
            value = (long)1 << (value-64);
            if ((mark128&value) != 0) {
                return false;
            }
            mark128 |= value;
        }else if (value < 192) {
            value = (long)1 << (value-128);
            if ((mark192&value) != 0) {
                return false;
            }
            mark192 |= value;
        }else{
            value = (long)1 << (value-192);
            if ((mark256&value) != 0) {
                return false;
            }
            mark256 |= value;
        }
        
        ++astr;
    }
    return true;
}

int convertInteger(int A, int B){
    
    
    return 0;
}

int subarraysWithKDistinct(int* A, int ASize, int K){
    int countArray1[ASize+1];
    int countArray2[ASize+1];
    for (int i = 0; i <= ASize; ++i) {
        countArray1[i] = 0;
        countArray2[i] = 0;
    }
    
    // 复杂度为O(n)，三个游标各移动n次
    int diffCount1 = 0;
    int diffCount2 = 0;
    // 在右游标在right的情况下, left2-left1为不同数为K的子数组数量
    int left1 = 0;
    int left2 = 0;
    int right = 0;
    int result = 0;
    while (right < ASize) {
        countArray1[A[right]] += 1;
        if (countArray1[A[right]] == 1) {
            // 新增不同值
            ++diffCount1;
        }
        countArray2[A[right]] += 1;
        if (countArray2[A[right]] == 1) {
            ++diffCount2;
        }
        
        // 不同值数量多于K, 移动左游标，直到不同值数量为K
        if (diffCount1 > K) {
            while (left1 <= right) {
                countArray1[A[left1]] -= 1;
                if (countArray1[A[left1++]] == 0) {
                    diffCount1 -= 1;
                    break;
                }
            }
        }
        if (diffCount2 >= K) {
            while (left2 <= right) {
                countArray2[A[left2]] -= 1;
                if (countArray2[A[left2++]] == 0) {
                    diffCount2 -= 1;
                    break;
                }
            }
        }
        result += left2-left1;
        
        // 右游标+1
        ++right;
    }
    
    return result;
}


bool checkInclusion(char * s1, char * s2){
    
    int alphabetCount[26] = {0};
    int alphabetCount2[26] = {0};
    int length = 0;
    while (*s1) {
        alphabetCount[(*s1)-'a'] += 1;
        ++length;
        ++s1;
    }
    int rightLen = strlen(s2);
    if (rightLen < length) return false;
    
    int left = 0;
    int right = 0;
    
    for (; right < length; ++right) {
        alphabetCount2[s2[right]-'a'] += 1;
    }
    
    int equalCount = 0;
    for (int i = 0; i < 26; ++i) {
        if (alphabetCount[i] == alphabetCount2[i]) ++equalCount;
    }
    
    while (1) {
        if (equalCount == 26) return true;
        
        if (s2[right] == 0) break;
        
        int rightIndex = s2[right]-'a';
        alphabetCount2[rightIndex] += 1;
        if (alphabetCount2[rightIndex] == alphabetCount[rightIndex]) {
            ++equalCount;
        }else if (alphabetCount2[rightIndex]-1 == alphabetCount[rightIndex]) {
            --equalCount;
        }
        ++right;
        
        int leftIndex = s2[left]-'a';
        alphabetCount2[leftIndex] -= 1;
        if (alphabetCount2[leftIndex] == alphabetCount[leftIndex]) {
            ++equalCount;
        }else if (alphabetCount2[leftIndex]+1 == alphabetCount[leftIndex]) {
            --equalCount;
        }
        ++left;
    }
    
    return false;
}

int minSwapsCouples(int* row, int rowSize){
    int index[rowSize];
    for (int i = 0; i < rowSize; ++i) {
        index[row[i]] = i;
    }
    
    int result = 0;
    for (int i = 0; i < rowSize; i = i+2) {
        int l = row[i]/2;
        int r = row[i+1]/2;
        if (l != r) {
            int group = index[row[i]];
            int nextj = (row[i+1]%2 == 0)?index[row[i+1]+1]:index[row[i+1]-1];
            index[row[i+1]] = group;
            while (index[row[nextj]] != group) {
                index[row[nextj]] = group;
                int tmpj = (nextj%2==0)?nextj+1:nextj-1;
                index[row[tmpj]] = group;
                nextj = (row[tmpj]%2==0)?index[row[tmpj]+1]:index[row[tmpj]-1];
                ++result;
            }
        }
    }
    
    return result;
}

int minKBitFlips(int* A, int ASize, int K){
    int count = 0;
    int needFlip = 0;
    for (int i = 0; i < ASize-K+1; ++i) {
        if (needFlip == 1) {
            A[i+K-1] = A[i+K-1]^1;
        }
        if (A[i] == needFlip) {
            needFlip = needFlip^1;
            ++count;
        }
    }
    
    for (int i = ASize-K+1; i < ASize; ++i) {
        if (A[i] == needFlip) return -1;
    }
    
    return count;
}

int maxSatisfied(int* customers, int customersSize, int* grumpy, int grumpySize, int X){
    
    // 计算出不忍耐下的满意数
    int minCount = 0;
    for (int i = 0; i < customersSize; ++i) {
        minCount = minCount+customers[i]*(1-grumpy[i]);
    }
    
    // 计算出忍耐最大增加满意数
    int maxPlusCount = 0;
    for (int i = 0; i < X; ++i) {
        maxPlusCount += customers[i]*grumpy[i];
    }
    int tmpPlusCount = maxPlusCount;
    for (int i = X; i < customersSize; ++i) {
        tmpPlusCount = tmpPlusCount+customers[i]*grumpy[i]-customers[i-X]*grumpy[i-X];
        if (tmpPlusCount > maxPlusCount) {
            maxPlusCount = tmpPlusCount;
        }
    }
    
    return minCount+maxPlusCount;
}
