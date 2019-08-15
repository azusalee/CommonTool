//
//  LeetCodeC.h
//  CommonTool
//
//  Created by lizihong on 2019/8/8.
//  Copyright © 2019 AL. All rights reserved.
//

#ifndef LeetCodeC_h
#define LeetCodeC_h

#include <stdio.h>
#include <stdbool.h>

// 链表节点
struct ListNode {
    int val;
    struct ListNode *next;
};

/// 罗马数字转整数(1~3999) https://leetcode-cn.com/problems/roman-to-integer/
int romanToInt(char * s);

/// 回文数 https://leetcode-cn.com/problems/palindrome-number/
bool isPalindrome(int x);

// 有效括号{} [] () https://leetcode-cn.com/problems/valid-parentheses/submissions/
bool isVaildBrackets(char *s);

// +1 https://leetcode-cn.com/problems/plus-one/submissions/
int* plusOne(int* digits, int digitsSize, int* returnSize);

/// 字符串转换整数 (atoi) https://leetcode-cn.com/problems/string-to-integer-atoi/
int myAtoi(char * str);

/// 删除链表中倒数第n个数 https://leetcode-cn.com/problems/remove-nth-node-from-end-of-list/submissions/
struct ListNode* removeNthFromEnd(struct ListNode* head, int n);

/// Z 字形变换 https://leetcode-cn.com/problems/zigzag-conversion/submissions/
char * convertZ(char * s, int numRows);

/// 获取字符串所在的位置 https://leetcode-cn.com/problems/implement-strstr/submissions/
int strStr(char * haystack, char * needle);

/// 最长公共前缀 https://leetcode-cn.com/problems/longest-common-prefix/
char * longestCommonPrefix(char ** strs, int strsSize);

// 三数之和 https://leetcode-cn.com/problems/3sum/submissions/
int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes);

// 删除排序数组中的重复项 https://leetcode-cn.com/problems/remove-duplicates-from-sorted-array/submissions/
int removeDuplicates(int* nums, int numsSize);

// 合并两个有序链表 https://leetcode-cn.com/problems/merge-two-sorted-lists/submissions/
struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2);

// 搜索插入位置 https://leetcode-cn.com/problems/search-insert-position/submissions/
int searchInsert(int* nums, int numsSize, int target);

// 最大子序和 https://leetcode-cn.com/problems/maximum-subarray/
int maxSubArray(int* nums, int numsSize);

// 合并两个有序数组 https://leetcode-cn.com/problems/merge-sorted-array/submissions/
void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n);

// 电话号码的字母组合 https://leetcode-cn.com/problems/letter-combinations-of-a-phone-number/
char ** letterCombinations(char * digits, int* returnSize);

#endif /* LeetCodeC_h */
