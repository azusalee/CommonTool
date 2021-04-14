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

// 链表节点
struct ListNode {
    int val;
    struct ListNode *next;
};

// 二叉树
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

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

// 1438. 绝对差不超过限制的最长连续子数组
int longestSubarray(int* nums, int numsSize, int limit);

// 1178. 猜字谜
int* findNumOfValidWords(char ** words, int wordsSize, char ** puzzles, int puzzlesSize, int* returnSize);

// 395. 至少有 K 个重复字符的最长子串
int longestSubstring(char * s, int k);

// 354. 俄罗斯套娃信封问题
int maxEnvelopes(int** envelopes, int envelopesSize, int* envelopesColSize);

// 132. 分割回文串 II
int minCut(char * s);

// 179. 最大数
char * largestNumber(int* nums, int numsSize);

#endif /* LeetCodeC2_h */
