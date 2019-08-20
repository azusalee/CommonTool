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

// 二叉树
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
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

// 报数 https://leetcode-cn.com/problems/count-and-say/
char * countAndSay(int n);

// 括号生成 https://leetcode-cn.com/problems/generate-parentheses/submissions/
char ** generateParenthesis(int n, int* returnSize);

// 宝石与石头 https://leetcode-cn.com/problems/jewels-and-stones/
int numJewelsInStones(char * J, char * S);

// 只出现一次的数字 https://leetcode-cn.com/problems/single-number/
int singleNumber(int* nums, int numsSize);

// 二进制求和 https://leetcode-cn.com/problems/add-binary/submissions/
char * addBinary(char * a, char * b);

// 爬楼梯 https://leetcode-cn.com/problems/climbing-stairs/submissions/
int climbStairs(int n);

// 反转链表 https://leetcode-cn.com/problems/reverse-linked-list/submissions/
struct ListNode* reverseList(struct ListNode* head);

// 最后一个单词的长度 https://leetcode-cn.com/problems/length-of-last-word/submissions/
int lengthOfLastWord(char * s);

// 搜索旋转排序数组 https://leetcode-cn.com/problems/search-in-rotated-sorted-array/submissions/
int search(int* nums, int numsSize, int target);

// 两两交换链表中的节点 https://leetcode-cn.com/problems/swap-nodes-in-pairs/
struct ListNode* swapPairs(struct ListNode* head);

// 盛最多水的容器 https://leetcode-cn.com/problems/container-with-most-water/submissions/
int maxArea(int* height, int heightSize);

// 二叉树的最大深度 https://leetcode-cn.com/problems/maximum-depth-of-binary-tree/submissions/
int maxDepth(struct TreeNode* root);

// K 个一组翻转链表 https://leetcode-cn.com/problems/reverse-nodes-in-k-group/submissions/
struct ListNode* reverseKGroup(struct ListNode* head, int k);

// 反转字符串 https://leetcode-cn.com/problems/reverse-string/submissions/
void reverseString(char* s, int sSize);

// 在排序数组中查找元素的第一个和最后一个位置 https://leetcode-cn.com/problems/find-first-and-last-position-of-element-in-sorted-array/submissions/
int* searchRange(int* nums, int numsSize, int target, int* returnSize);

// 整数转罗马数字 https://leetcode-cn.com/problems/integer-to-roman/submissions/
char * intToRoman(int num);

// 移动零 https://leetcode-cn.com/problems/move-zeroes/submissions/
void moveZeroes(int* nums, int numsSize);

// 合并K个排序链表 https://leetcode-cn.com/problems/merge-k-sorted-lists/submissions/
struct ListNode* mergeKLists(struct ListNode** lists, int listsSize);

// 回文链表 https://leetcode-cn.com/problems/palindrome-linked-list/submissions/
bool isPalindromeList(struct ListNode* head);

#endif /* LeetCodeC_h */
