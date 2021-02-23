//
//  LeetCodeC2.h
//  CommonTool
//
//  Created by lizihong on 2021/2/8.
//  Copyright © 2021 AL. All rights reserved.
//
// 代码太多导致卡顿，换个文件写

#ifndef LeetCodeC2_h
#define LeetCodeC2_h

#include <stdio.h>
#include <stdbool.h>

// 面试题 17.10. 主要元素
int majorityElement(int* nums, int numsSize);

// 面试题 01.01. 判定字符是否唯一
bool isUnique(char* astr);

// 面试题 05.06. 整数转换
int convertInteger(int A, int B);

// 992. K 个不同整数的子数组
int subarraysWithKDistinct(int* A, int ASize, int K);

// 567. 字符串的排列
bool checkInclusion(char * s1, char * s2);

// 765. 情侣牵手
int minSwapsCouples(int* row, int rowSize);

// 995. K 连续位的最小翻转次数
int minKBitFlips(int* A, int ASize, int K);

// 1052. 爱生气的书店老板
int maxSatisfied(int* customers, int customersSize, int* grumpy, int grumpySize, int X);

#endif /* LeetCodeC2_h */
