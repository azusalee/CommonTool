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

// 最小栈
typedef struct {
    struct ListNode *top;
    struct ListNode *min;
} MinStack;

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

// 全排列 https://leetcode-cn.com/problems/permutations/
int** permute(int* nums, int numsSize, int* returnSize, int** returnColumnSizes);

// 求众数 https://leetcode-cn.com/problems/majority-element/
int majorityElement(int* nums, int numsSize);

// x 的平方根 https://leetcode-cn.com/problems/sqrtx/submissions/
int mySqrt(int x);

// 螺旋矩阵 https://leetcode-cn.com/problems/spiral-matrix/
int* spiralOrder(int** matrix, int matrixSize, int* matrixColSize, int* returnSize);

// 反转字符串中的单词 III https://leetcode-cn.com/problems/reverse-words-in-a-string-iii/submissions/
char * reverseWords(char * s);

// 字符串相乘 https://leetcode-cn.com/problems/multiply-strings/submissions/
char * multiply(char * num1, char * num2);

// 数组中的第K个最大元素 https://leetcode-cn.com/problems/kth-largest-element-in-an-array/
int findKthLargest(int* nums, int numsSize, int k);
int findKthLargest2(int* nums, int numsSize, int k);
void myprintNums(int* nums, int numsSize);

// 环形链表 https://leetcode-cn.com/problems/linked-list-cycle/submissions/
bool hasCycle(struct ListNode *head);

// 旋转图像 https://leetcode-cn.com/problems/rotate-image/submissions/
void rotate(int** matrix, int matrixSize, int* matrixColSize);

// 验证回文串 https://leetcode-cn.com/problems/valid-palindrome/submissions/
bool isPalindromeString(char * s);

// 打家劫舍 https://leetcode-cn.com/problems/house-robber/solution/da-jia-jie-she-by-leetcode/
int rob(int* nums, int numsSize);

// 二叉树的层次遍历 https://leetcode-cn.com/problems/binary-tree-level-order-traversal/submissions/
int** levelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes);

// 两数相除 https://leetcode-cn.com/problems/divide-two-integers/
int divide(int dividend, int divisor);

// 不同路径 https://leetcode-cn.com/problems/unique-paths/solution/
long long uniquePaths(int m, int n);

// 买卖股票的最佳时机 https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock/submissions/
int maxProfit(int* prices, int pricesSize);

// 旋转链表 https://leetcode-cn.com/problems/rotate-list/solution/xuan-zhuan-lian-biao-by-leetcode/
struct ListNode* rotateRight(struct ListNode* head, int k);

// 最小栈 https://leetcode-cn.com/problems/min-stack/submissions/
MinStack* minStackCreate(void);
void minStackPush(MinStack* obj, int x);
void minStackPop(MinStack* obj);
int minStackTop(MinStack* obj);
int minStackGetMin(MinStack* obj);
void minStackFree(MinStack* obj);

// 买卖股票的最佳时机 II https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-ii/submissions/
int maxProfit2(int* prices, int pricesSize);

// 杨辉三角 https://leetcode-cn.com/problems/pascals-triangle/submissions/
int** generate(int numRows, int* returnSize, int** returnColumnSizes);

// 移除链表元素 https://leetcode-cn.com/problems/remove-linked-list-elements/submissions/
struct ListNode* removeElements(struct ListNode* head, int val);

// 反转链表 II https://leetcode-cn.com/problems/reverse-linked-list-ii/submissions/
struct ListNode* reverseBetween(struct ListNode* head, int m, int n);

// IP 地址无效化 https://leetcode-cn.com/problems/defanging-an-ip-address/submissions/
char * defangIPaddr(char * address);

// 汉明距离 https://leetcode-cn.com/problems/hamming-distance/
int hammingDistance(int x, int y);

// 缺失的第一个正数 https://leetcode-cn.com/problems/first-missing-positive/
int firstMissingPositive(int* nums, int numsSize);

// 删除最外层的括号 https://leetcode-cn.com/problems/remove-outermost-parentheses/
char * removeOuterParentheses(char * S);

// 合并区间 https://leetcode-cn.com/problems/merge-intervals/solution/he-bing-qu-jian-by-leetcode/
int** mergeSet(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize, int** returnColumnSizes);

// 最小路径和 https://leetcode-cn.com/problems/minimum-path-sum/submissions/
int minPathSum(int** grid, int gridSize, int* gridColSize);

// 旋转数组 https://leetcode-cn.com/problems/rotate-array/solution/
void rotateNums(int* nums, int numsSize, int k);

// 子集 https://leetcode-cn.com/problems/subsets/
int** subsets(int* nums, int numsSize, int* returnSize, int** returnColumnSizes);

// 两数之和 II - 输入有序数组 https://leetcode-cn.com/problems/two-sum-ii-input-array-is-sorted/
int* twoSum(int* numbers, int numbersSize, int target, int* returnSize);

// 相同的树 https://leetcode-cn.com/problems/same-tree/
bool isSameTree(struct TreeNode* p, struct TreeNode* q);

// 相交链表 https://leetcode-cn.com/problems/intersection-of-two-linked-lists/submissions/
struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB);

// 删除排序链表中的重复元素 II https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list-ii/submissions/
struct ListNode* deleteDuplicates(struct ListNode* head);

// 接雨水 https://leetcode-cn.com/problems/trapping-rain-water/
int trap(int* height, int heightSize);

// 四数之和 https://leetcode-cn.com/problems/4sum/
int** fourSum(int* nums, int numsSize, int target, int* returnSize, int** returnColumnSizes);

// 最接近的三数之和 https://leetcode-cn.com/problems/3sum-closest/
int threeSumClosest(int* nums, int numsSize, int target);

// 岛屿数量 https://leetcode-cn.com/problems/number-of-islands/
int numIslands(char** grid, int gridSize, int* gridColSize);

// 三角形最小路径和 https://leetcode-cn.com/problems/triangle/
int minimumTotal(int** triangle, int triangleSize, int* triangleColSize);

// 对称二叉树 https://leetcode-cn.com/problems/symmetric-tree/
bool isSymmetric(struct TreeNode* root);

// 验证二叉搜索树 https://leetcode-cn.com/problems/validate-binary-search-tree/
bool isValidBST(struct TreeNode* root);

// 下一个排列 https://leetcode-cn.com/problems/next-permutation/
void nextPermutation(int* nums, int numsSize);

// 螺旋矩阵 II https://leetcode-cn.com/problems/spiral-matrix-ii/
int** generateMatrix(int n, int* returnSize, int** returnColumnSizes);

// 斐波那契数 https://leetcode-cn.com/problems/fibonacci-number/submissions/
int fib(int N);

// 组合总和 https://leetcode-cn.com/problems/combination-sum/
int** combinationSum(int* candidates, int candidatesSize, int target, int* returnSize, int** returnColumnSizes);

// 正则表达式匹配 https://leetcode-cn.com/problems/regular-expression-matching/
bool isMatch(char * s, char * p);

// 两个数组的交集 II https://leetcode-cn.com/problems/intersection-of-two-arrays-ii/
int* intersect(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize);

// 存在重复元素 https://leetcode-cn.com/problems/contains-duplicate/
bool containsDuplicate(int* nums, int numsSize);

// 翻转图像 https://leetcode-cn.com/problems/flipping-an-image/
int** flipAndInvertImage(int** A, int ASize, int* AColSize, int* returnSize, int** returnColumnSizes);

// 快乐数 https://leetcode-cn.com/problems/happy-number/
bool isHappy(int n);

// 删除排序链表中的重复元素 https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list/
struct ListNode* deleteDuplicates2(struct ListNode* head);

// 跳跃游戏 https://leetcode-cn.com/problems/jump-game/
bool canJump(int* nums, int numsSize);

// 有效的字母异位词 https://leetcode-cn.com/problems/valid-anagram/
bool isAnagram(char * s, char * t);

// 两个数组的交集 https://leetcode-cn.com/problems/intersection-of-two-arrays/
int* intersection(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize);

// 2的幂 https://leetcode-cn.com/problems/power-of-two/
bool isPowerOfTwo(int n);

// 杨辉三角 II https://leetcode-cn.com/problems/pascals-triangle-ii/
int* getRow(int rowIndex, int* returnSize);

#endif /* LeetCodeC_h */
