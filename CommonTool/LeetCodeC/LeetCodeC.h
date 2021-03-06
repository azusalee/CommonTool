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

typedef struct {
    struct ListNode *top;
    struct ListNode *last;
} MyQueue;

struct Node {
    int val;
    int numNeighbors;
    struct Node** neighbors;
};

struct NodeRight {
  int val;
  struct NodeRight *left;
  struct NodeRight *right;
  struct NodeRight *next;
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

// 第k个排列 https://leetcode-cn.com/problems/permutation-sequence/
char * getPermutation(int n, int k);

// 用栈实现队列 https://leetcode-cn.com/problems/implement-queue-using-stacks/submissions/
/** Initialize your data structure here. */
MyQueue* myQueueCreate();
/** Push element x to the back of queue. */
void myQueuePush(MyQueue* obj, int x);
/** Removes the element from in front of queue and returns that element. */
int myQueuePop(MyQueue* obj);
/** Get the front element. */
int myQueuePeek(MyQueue* obj);
/** Returns whether the queue is empty. */
bool myQueueEmpty(MyQueue* obj);
void myQueueFree(MyQueue* obj);

// 翻转二叉树 https://leetcode-cn.com/problems/invert-binary-tree/
struct TreeNode* invertTree(struct TreeNode* root);

// N皇后 https://leetcode-cn.com/problems/n-queens/
char *** solveNQueens(int n, int* returnSize, int** returnColumnSizes);

// 最长有效括号 https://leetcode-cn.com/problems/longest-valid-parentheses/
int longestValidParentheses(char * s);

// 字符串中的第一个唯一字符 https://leetcode-cn.com/problems/first-unique-character-in-a-string/submissions/
int firstUniqChar(char * s);

// 最后一块石头的重量 https://leetcode-cn.com/problems/last-stone-weight/
int lastStoneWeight(int* stones, int stonesSize);

// 路径总和 https://leetcode-cn.com/problems/path-sum/submissions/
bool hasPathSum(struct TreeNode* root, int sum);

// 平衡二叉树 https://leetcode-cn.com/problems/balanced-binary-tree/submissions/
bool isBalanced(struct TreeNode* root);

// 数组的相对排序 https://leetcode-cn.com/problems/relative-sort-array/solution/
int* relativeSortArray(int* arr1, int arr1Size, int* arr2, int arr2Size, int* returnSize);

// 有效的数独 https://leetcode-cn.com/problems/valid-sudoku/submissions/
bool isValidSudoku(char** board, int boardSize, int* boardColSize);

// 二叉树的最小深度 https://leetcode-cn.com/submissions/detail/32562884/
int minDepth(struct TreeNode* root);

// 缺失数字 https://leetcode-cn.com/problems/missing-number/
int missingNumber(int* nums, int numsSize);

// 递增顺序查找树 https://leetcode-cn.com/problems/increasing-order-search-tree/
struct TreeNode* increasingBST(struct TreeNode* root);

// 下一个更大元素 I https://leetcode-cn.com/problems/next-greater-element-i/
int* nextGreaterElement(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize);

// 二叉树的层平均值 https://leetcode-cn.com/problems/average-of-levels-in-binary-tree/submissions/
double* averageOfLevels(struct TreeNode* root, int* returnSize);

// 旋转数字 https://leetcode-cn.com/problems/rotated-digits/
int rotatedDigits(int N);

// 一周中的第几天 https://leetcode-cn.com/problems/day-of-the-week/
char * dayOfTheWeek(int day, int month, int year);

// 写字符串需要的行数 https://leetcode-cn.com/problems/number-of-lines-to-write-string/
int* numberOfLines(int* widths, int widthsSize, char * S, int* returnSize);

// 拼写单词 https://leetcode-cn.com/problems/find-words-that-can-be-formed-by-characters/
int countCharacters(char ** words, int wordsSize, char * chars);

// 特殊等价字符串组 https://leetcode-cn.com/problems/groups-of-special-equivalent-strings/
int numSpecialEquivGroups(char ** A, int ASize);

// 三维形体投影面积 https://leetcode-cn.com/problems/projection-area-of-3d-shapes/
int projectionArea(int** grid, int gridSize, int* gridColSize);

// Fizz Buzz https://leetcode-cn.com/problems/fizz-buzz/
char ** fizzBuzz(int n, int* returnSize);

// “气球” 的最大数量 https://leetcode-cn.com/problems/maximum-number-of-balloons/
int maxNumberOfBalloons(char * text);

// 分糖果 II https://leetcode-cn.com/problems/distribute-candies-to-people/
int* distributeCandies(int candies, int num_people, int* returnSize);

// 字母大小写全排列 https://leetcode-cn.com/problems/letter-case-permutation/
char ** letterCasePermutation(char * S, int* returnSize);

// 位1的个数 https://leetcode-cn.com/problems/number-of-1-bits/
int hammingWeight(uint32_t n);

// 复写零 https://leetcode-cn.com/problems/duplicate-zeros/
void duplicateZeros(int* arr, int arrSize);

// 十进制整数的反码 https://leetcode-cn.com/problems/complement-of-base-10-integer/
int bitwiseComplement(int N);

// 二进制间距 https://leetcode-cn.com/problems/binary-gap/
int binaryGap(int N);

// 山羊拉丁文 https://leetcode-cn.com/problems/goat-latin/
char * toGoatLatin(char * S);

// 比较字符串最小字母出现频次 https://leetcode-cn.com/problems/compare-strings-by-frequency-of-the-smallest-character/
int* numSmallerByFrequency(char ** queries, int queriesSize, char ** words, int wordsSize, int* returnSize);

// 链表的中间结点 https://leetcode-cn.com/problems/middle-of-the-linked-list/
struct ListNode* middleNode(struct ListNode* head);

// 托普利茨矩阵 https://leetcode-cn.com/problems/toeplitz-matrix/
bool isToeplitzMatrix(int** matrix, int matrixSize, int* matrixColSize);

// 两句话中的不常见单词 https://leetcode-cn.com/problems/uncommon-words-from-two-sentences/
char ** uncommonFromSentences(char * A, char * B, int* returnSize);

// 把二叉搜索树转换为累加树 https://leetcode-cn.com/problems/convert-bst-to-greater-tree/
struct TreeNode* convertBST(struct TreeNode* root);

// 二叉搜索树的最近公共祖先 https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-search-tree/
struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q);

// 最大三角形面积 https://leetcode-cn.com/problems/largest-triangle-area/
double largestTriangleArea(int** points, int pointsSize, int* pointsColSize);

// 最小绝对差 https://leetcode-cn.com/problems/minimum-absolute-difference/
int** minimumAbsDifference(int* arr, int arrSize, int* returnSize, int** returnColumnSizes);

// Bigram 分词 https://leetcode-cn.com/problems/occurrences-after-bigram/
char ** findOcurrences(char * text, char * first, char * second, int* returnSize);

// 距离顺序排列矩阵单元格 https://leetcode-cn.com/problems/matrix-cells-in-distance-order/
int** allCellsDistOrder(int R, int C, int r0, int c0, int* returnSize, int** returnColumnSizes);

// 重塑矩阵 https://leetcode-cn.com/problems/reshape-the-matrix/
int** matrixReshape(int** nums, int numsSize, int* numsColSize, int r, int c, int* returnSize, int** returnColumnSizes);

// 二叉树的所有路径 https://leetcode-cn.com/problems/binary-tree-paths/
char ** binaryTreePaths(struct TreeNode* root, int* returnSize);

// 区域和检索 - 数组不可变 https://leetcode-cn.com/problems/range-sum-query-immutable/submissions/
typedef struct {
    int *nums;
    int numsSize;
    int *sums;
} NumArray;
NumArray* numArrayCreate(int* nums, int numsSize);
int numArraySumRange(NumArray* obj, int i, int j);
void numArrayFree(NumArray* obj);

// 用队列实现栈 https://leetcode-cn.com/problems/implement-stack-using-queues/submissions/
typedef struct {
    struct ListNode * top;
} MyStack;
MyStack* myStackCreate();
/** Push element x onto stack. */
void myStackPush(MyStack* obj, int x);
/** Removes the element on top of the stack and returns that element. */
int myStackPop(MyStack* obj);
/** Get the top element. */
int myStackTop(MyStack* obj);
/** Returns whether the stack is empty. */
bool myStackEmpty(MyStack* obj);
void myStackFree(MyStack* obj);

// 删除字符串中的所有相邻重复项 https://leetcode-cn.com/problems/remove-all-adjacent-duplicates-in-string/
char * removeDuplicates2(char * S);

// 叶子相似的树 https://leetcode-cn.com/problems/leaf-similar-trees/
bool leafSimilar(struct TreeNode* root1, struct TreeNode* root2);

// 猜数字 https://leetcode-cn.com/problems/guess-numbers/
int game(int* guess, int guessSize, int* answer, int answerSize);

// 删除链表中的节点 https://leetcode-cn.com/problems/delete-node-in-a-linked-list/
void deleteNode(struct ListNode* node);

// 转换成小写字母 https://leetcode-cn.com/problems/to-lower-case/
char * toLowerCase(char * str);

// 机器人能否返回原点 https://leetcode-cn.com/problems/robot-return-to-origin/
bool judgeCircle(char * moves);

// 有序数组的平方 https://leetcode-cn.com/problems/squares-of-a-sorted-array/
int* sortedSquares(int* A, int ASize, int* returnSize);

// 分割平衡字符串 https://leetcode-cn.com/problems/split-a-string-in-balanced-strings/
int balancedStringSplit(char * s);

// 自除数 https://leetcode-cn.com/problems/self-dividing-numbers/
int* selfDividingNumbers(int left, int right, int* returnSize);

// Nim 游戏 https://leetcode-cn.com/problems/nim-game/
bool canWinNim(int n);

// 增减字符串匹配 https://leetcode-cn.com/problems/di-string-match/
int* diStringMatch(char * S, int* returnSize);

// 唯一摩尔斯密码词 https://leetcode-cn.com/problems/unique-morse-code-words/
int uniqueMorseRepresentations(char ** words, int wordsSize);

// 合并二叉树 https://leetcode-cn.com/problems/merge-two-binary-trees/
struct TreeNode* mergeTrees(struct TreeNode* t1, struct TreeNode* t2);

// 最近的请求次数 https://leetcode-cn.com/problems/number-of-recent-calls/submissions/
typedef struct {
    struct ListNode *last;
} RecentCounter;
RecentCounter* recentCounterCreate();
int recentCounterPing(RecentCounter* obj, int t);
void recentCounterFree(RecentCounter* obj);

// 除数博弈 https://leetcode-cn.com/problems/divisor-game/
bool divisorGame(int N);

// 山脉数组的峰顶索引 https://leetcode-cn.com/problems/peak-index-in-a-mountain-array/
int peakIndexInMountainArray(int* A, int ASize);

// 数字的补数 https://leetcode-cn.com/problems/number-complement/
int findComplement(int num);

// 按奇偶排序数组 https://leetcode-cn.com/problems/sort-array-by-parity/
int* sortArrayByParity(int* A, int ASize, int* returnSize);

// 分糖果 https://leetcode-cn.com/problems/distribute-candies/
int distributeCandies2(int* candies, int candiesSize);

// 岛屿的周长 https://leetcode-cn.com/problems/island-perimeter/
int islandPerimeter(int** grid, int gridSize, int* gridColSize);

// 玩筹码 https://leetcode-cn.com/problems/play-with-chips/
int minCostToMoveChips(int* chips, int chipsSize);

// 单值二叉树 https://leetcode-cn.com/problems/univalued-binary-tree/
bool isUnivalTree(struct TreeNode* root);

// 各位相加 https://leetcode-cn.com/problems/add-digits/
int addDigits(int num);

// 数组拆分 I https://leetcode-cn.com/problems/array-partition-i/
int arrayPairSum(int* nums, int numsSize);

// 删列造序 https://leetcode-cn.com/problems/delete-columns-to-make-sorted/
int minDeletionSize(char ** A, int ASize);

// 将有序数组转换为二叉搜索树 https://leetcode-cn.com/problems/convert-sorted-array-to-binary-search-tree/
struct TreeNode* sortedArrayToBST(int* nums, int numsSize);

// 最小差值 I https://leetcode-cn.com/problems/smallest-range-i/
int smallestRangeI(int* A, int ASize, int K);

// 转置矩阵 https://leetcode-cn.com/problems/transpose-matrix/
int** transpose(int** A, int ASize, int* AColSize, int* returnSize, int** returnColumnSizes);

// 重复 N 次的元素 https://leetcode-cn.com/problems/n-repeated-element-in-size-2n-array/
int repeatedNTimes(int* A, int ASize);

// 最长特殊序列 Ⅰ https://leetcode-cn.com/problems/longest-uncommon-subsequence-i/
int findLUSlength(char * a, char * b);

// 棒球比赛 https://leetcode-cn.com/problems/baseball-game/
int calPoints(char ** ops, int opsSize);

// 独一无二的出现次数 https://leetcode-cn.com/problems/unique-number-of-occurrences/
bool uniqueOccurrences(int* arr, int arrSize);

// 按奇偶排序数组 II https://leetcode-cn.com/problems/sort-array-by-parity-ii/
int* sortArrayByParityII(int* A, int ASize, int* returnSize);

// Excel表列序号 https://leetcode-cn.com/problems/excel-sheet-column-number/
int titleToNumber(char * s);

// 二进制表示中质数个计算置位 https://leetcode-cn.com/problems/prime-number-of-set-bits-in-binary-representation/
int countPrimeSetBits(int L, int R);

// 查找常用字符 https://leetcode-cn.com/problems/find-common-characters/
char ** commonChars(char ** A, int ASize, int* returnSize);

// 独特的电子邮件地址 https://leetcode-cn.com/problems/unique-email-addresses/
int numUniqueEmails(char ** emails, int emailsSize);

// 修剪二叉搜索树 https://leetcode-cn.com/problems/trim-a-binary-search-tree/
struct TreeNode* trimBST(struct TreeNode* root, int L, int R);

// 二叉树的层次遍历 II https://leetcode-cn.com/problems/binary-tree-level-order-traversal-ii/
int** levelOrderBottom(struct TreeNode* root, int* returnSize, int** returnColumnSizes);

// 验证外星语词典 https://leetcode-cn.com/problems/verifying-an-alien-dictionary/
bool isAlienSorted(char ** words, int wordsSize, char * order);

// 第 N 个泰波那契数 https://leetcode-cn.com/problems/n-th-tribonacci-number/
int tribonacci(int n);

// 分发饼干 https://leetcode-cn.com/problems/assign-cookies/
int findContentChildren(int* g, int gSize, int* s, int sSize);

// 阶乘后的零 https://leetcode-cn.com/problems/factorial-trailing-zeroes/
int trailingZeroes(int n);

// 仅仅反转字母 https://leetcode-cn.com/problems/reverse-only-letters/
char * reverseOnlyLetters(char * S);

// 最大连续1的个数 https://leetcode-cn.com/problems/max-consecutive-ones/
int findMaxConsecutiveOnes(int* nums, int numsSize);

// 二叉搜索树结点最小距离 https://leetcode-cn.com/problems/minimum-distance-between-bst-nodes/
int minDiffInBST(struct TreeNode* root);

// 两地调度 https://leetcode-cn.com/problems/two-city-scheduling/
int twoCitySchedCost(int** costs, int costsSize, int* costsColSize);

// 最短完整词 https://leetcode-cn.com/problems/shortest-completing-word/
char * shortestCompletingWord(char * licensePlate, char ** words, int wordsSize);

// 回旋镖的数量 https://leetcode-cn.com/problems/number-of-boomerangs/
int numberOfBoomerangs(int** points, int pointsSize, int* pointsColSize);

// 相对名次 https://leetcode-cn.com/problems/relative-ranks/
char ** findRelativeRanks(int* nums, int numsSize, int* returnSize);

// 路径总和 III https://leetcode-cn.com/problems/path-sum-iii/
int pathSum(struct TreeNode* root, int sum);

// 二分查找 https://leetcode-cn.com/problems/binary-search/
int search2(int* nums, int numsSize, int target);

// 根据二叉树创建字符串 https://leetcode-cn.com/problems/construct-string-from-binary-tree/
char * tree2str(struct TreeNode* t);

// 三角形的最大周长 https://leetcode-cn.com/problems/largest-perimeter-triangle/
int largestPerimeter(int* A, int ASize);

// 图像渲染 https://leetcode-cn.com/problems/flood-fill/
int** floodFill(int** image, int imageSize, int* imageColSize, int sr, int sc, int newColor, int* returnSize, int** returnColumnSizes);

// 三维形体的表面积 https://leetcode-cn.com/problems/surface-area-of-3d-shapes/
int surfaceArea(int** grid, int gridSize, int* gridColSize);

// 检测大写字母 https://leetcode-cn.com/problems/detect-capital/
bool detectCapitalUse(char * word);

// 两整数之和 https://leetcode-cn.com/problems/sum-of-two-integers/
int getSum(int a, int b);

// 柠檬水找零 https://leetcode-cn.com/problems/lemonade-change/
bool lemonadeChange(int* bills, int billsSize);

// 最小移动次数使数组元素相等 https://leetcode-cn.com/problems/minimum-moves-to-equal-array-elements/
int minMoves(int* nums, int numsSize);

// 公交站间的距离 https://leetcode-cn.com/problems/distance-between-bus-stops/
int distanceBetweenBusStops(int* distance, int distanceSize, int start, int destination);

// 找到所有数组中消失的数字 https://leetcode-cn.com/problems/find-all-numbers-disappeared-in-an-array/
int* findDisappearedNumbers(int* nums, int numsSize, int* returnSize);

// 将数组分成和相等的三个部分 https://leetcode-cn.com/problems/partition-array-into-three-parts-with-equal-sum/
bool canThreePartsEqualSum(int* A, int ASize);

// 最长回文串 https://leetcode-cn.com/problems/longest-palindrome/
int longestPalindrome(char * s);

// 三个数的最大乘积 https://leetcode-cn.com/problems/maximum-product-of-three-numbers/
int maximumProduct(int* nums, int numsSize);

// 公平的糖果交换 https://leetcode-cn.com/problems/fair-candy-swap/
int* fairCandySwap(int* A, int ASize, int* B, int BSize, int* returnSize);

// 比较含退格的字符串 https://leetcode-cn.com/problems/backspace-string-compare/
bool backspaceCompare(char * S, char * T);

// 赎金信 https://leetcode-cn.com/problems/ransom-note/
bool canConstruct(char * ransomNote, char * magazine);

// 从根到叶的二进制数之和 https://leetcode-cn.com/problems/sum-of-root-to-leaf-binary-numbers/
int sumRootToLeaf(struct TreeNode* root);

// 一年中的第几天 https://leetcode-cn.com/problems/day-of-the-year/
int dayOfYear(char * date);

// 二叉树的坡度 https://leetcode-cn.com/problems/binary-tree-tilt/
int findTilt(struct TreeNode* root);

// 范围求和 II https://leetcode-cn.com/problems/range-addition-ii/
int maxCount(int m, int n, int** ops, int opsSize, int* opsColSize);

// 反转字符串 II https://leetcode-cn.com/problems/reverse-string-ii/
char * reverseStr(char * s, int k);

// 丑数 https://leetcode-cn.com/problems/ugly-number/
bool isUgly(int num);

// 旋转字符串 https://leetcode-cn.com/problems/rotate-string/
bool rotateString(char * A, char * B);

// 颠倒二进制位 https://leetcode-cn.com/problems/reverse-bits/
uint32_t reverseBits(uint32_t n);

// 二进制手表 https://leetcode-cn.com/problems/binary-watch/
char ** readBinaryWatch(int num, int* returnSize);

// 重新排列日志文件 https://leetcode-cn.com/problems/reorder-data-in-log-files/
char ** reorderLogFiles(char ** logs, int logsSize, int* returnSize);

// 数组的度 https://leetcode-cn.com/problems/degree-of-an-array/
int findShortestSubArray(int* nums, int numsSize);

// K 次取反后最大化的数组和 https://leetcode-cn.com/problems/maximize-sum-of-array-after-k-negations/
int largestSumAfterKNegations(int* A, int ASize, int K);

// 构造矩形 https://leetcode-cn.com/problems/construct-the-rectangle/
int* constructRectangle(int area, int* returnSize);

// 学生出勤记录 I https://leetcode-cn.com/problems/student-attendance-record-i/
bool checkRecord(char * s);

// 两个列表的最小索引总和 https://leetcode-cn.com/problems/minimum-index-sum-of-two-lists/
char ** findRestaurant(char ** list1, int list1Size, char ** list2, int list2Size, int* returnSize);

// 找到小镇的法官 https://leetcode-cn.com/problems/find-the-town-judge/
int findJudge(int N, int** trust, int trustSize, int* trustColSize);

// 二叉树的堂兄弟节点 https://leetcode-cn.com/problems/cousins-in-binary-tree/
bool isCousins(struct TreeNode* root, int x, int y);

// 数字转换为十六进制数 https://leetcode-cn.com/problems/convert-a-number-to-hexadecimal/ 
char * toHex(int num);

// 字符串相加 https://leetcode-cn.com/problems/add-strings/
char * addStrings(char * num1, char * num2);

// 反转字符串中的元音字母 https://leetcode-cn.com/problems/reverse-vowels-of-a-string/
char * reverseVowels(char * s);

// 计数二进制子串 https://leetcode-cn.com/problems/count-binary-substrings/
int countBinarySubstrings(char * s);

// 字符串的最大公因子 https://leetcode-cn.com/problems/greatest-common-divisor-of-strings/
char * gcdOfStrings(char * str1, char * str2);

// 找出井字棋的获胜者 https://leetcode-cn.com/problems/find-winner-on-a-tic-tac-toe-game/
char * tictactoe(int** moves, int movesSize, int* movesColSize);

// 缀点成线 https://leetcode-cn.com/problems/check-if-it-is-a-straight-line/
bool checkStraightLine(int** coordinates, int coordinatesSize, int* coordinatesColSize);

// 判断子序列 https://leetcode-cn.com/problems/is-subsequence/
bool isSubsequence(char * s, char * t);

// 七进制数 https://leetcode-cn.com/problems/base-7/
char * convertToBase7(int num);

// 4的幂 https://leetcode-cn.com/problems/power-of-four/
bool isPowerOfFour(int num);

// 同构字符串 https://leetcode-cn.com/problems/isomorphic-strings/
bool isIsomorphic(char * s, char * t);

// 腐烂的橘子 https://leetcode-cn.com/problems/rotting-oranges/
int orangesRotting(int** grid, int gridSize, int* gridColSize);

// 猜数字游戏 https://leetcode-cn.com/problems/bulls-and-cows/
char * getHint(char * secret, char * guess);

// 使用最小花费爬楼梯 https://leetcode-cn.com/problems/min-cost-climbing-stairs/
int minCostClimbingStairs(int* cost, int costSize);

// 二叉树的直径 https://leetcode-cn.com/problems/diameter-of-binary-tree/
int diameterOfBinaryTree(struct TreeNode* root);

// 计数质数 https://leetcode-cn.com/problems/count-primes/
int countPrimes(int n);

// 质数排列 https://leetcode-cn.com/problems/prime-arrangements/
int numPrimeArrangements(int n);

// 3的幂 https://leetcode-cn.com/problems/power-of-three/
bool isPowerOfThree(int n);

// 1比特与2比特字符 https://leetcode-cn.com/problems/1-bit-and-2-bit-characters/
bool isOneBitCharacter(int* bits, int bitsSize);

// 长按键入 https://leetcode-cn.com/problems/long-pressed-name/
bool isLongPressedName(char * name, char * typed);

// 二叉树中第二小的节点 https://leetcode-cn.com/problems/second-minimum-node-in-a-binary-tree/
int findSecondMinimumValue(struct TreeNode* root);

// 较大分组的位置 https://leetcode-cn.com/problems/positions-of-large-groups/
int** largeGroupPositions(char * S, int* returnSize, int** returnColumnSizes);

// 词典中最长的单词 https://leetcode-cn.com/problems/longest-word-in-dictionary/
char * longestWord(char ** words, int wordsSize);

// 重复的子字符串 https://leetcode-cn.com/problems/repeated-substring-pattern/
bool repeatedSubstringPattern(char * s);

// 矩形重叠 https://leetcode-cn.com/problems/rectangle-overlap/
bool isRectangleOverlap(int* rec1, int rec1Size, int* rec2, int rec2Size);

// 最长和谐子序列 https://leetcode-cn.com/problems/longest-harmonious-subsequence/
int findLHS(int* nums, int numsSize);

// 解数独 https://leetcode-cn.com/problems/sudoku-solver/
void solveSudoku(char** board, int boardSize, int* boardColSize);

// 回文素数 https://leetcode-cn.com/problems/prime-palindrome/
int primePalindrome(int N);

// 有效的完全平方数 https://leetcode-cn.com/problems/valid-perfect-square/
bool isPerfectSquare(int num);

// 不邻接植花 https://leetcode-cn.com/problems/flower-planting-with-no-adjacent/
int* gardenNoAdj(int N, int** paths, int pathsSize, int* pathsColSize, int* returnSize);

// 二叉搜索树中的众数 https://leetcode-cn.com/problems/find-mode-in-binary-search-tree/
int* findMode(struct TreeNode* root, int* returnSize);

// 数组形式的整数加法 https://leetcode-cn.com/problems/add-to-array-form-of-integer/
int* addToArrayForm(int* A, int ASize, int K, int* returnSize);

// 总持续时间可被 60 整除的歌曲 https://leetcode-cn.com/problems/pairs-of-songs-with-total-durations-divisible-by-60/
int numPairsDivisibleBy60(int* time, int timeSize);

// 最长连续递增序列 https://leetcode-cn.com/problems/longest-continuous-increasing-subsequence/
int findLengthOfLCIS(int* nums, int numsSize);

// 可被 5 整除的二进制前缀 https://leetcode-cn.com/problems/binary-prefix-divisible-by-5/
bool* prefixesDivBy5(int* A, int ASize, int* returnSize);

// 寻找比目标字母大的最小字母 https://leetcode-cn.com/problems/find-smallest-letter-greater-than-target/
char nextGreatestLetter(char* letters, int lettersSize, char target);

// 完美数 https://leetcode-cn.com/problems/perfect-number/
bool checkPerfectNumber(int num);

// 排列硬币 https://leetcode-cn.com/problems/arranging-coins/
int arrangeCoins(int n);

// 等价多米诺骨牌对的数量 https://leetcode-cn.com/problems/number-of-equivalent-domino-pairs/
int numEquivDominoPairs(int** dominoes, int dominoesSize, int* dominoesColSize);

// 至少是其他数字两倍的最大数 https://leetcode-cn.com/problems/largest-number-at-least-twice-of-others/
int dominantIndex(int* nums, int numsSize);

// 另一个树的子树 https://leetcode-cn.com/problems/subtree-of-another-tree/
bool isSubtree(struct TreeNode* s, struct TreeNode* t);

// 第三大的数 https://leetcode-cn.com/problems/third-maximum-number/
int thirdMax(int* nums, int numsSize);

// 移动石子直到连续 https://leetcode-cn.com/problems/moving-stones-until-consecutive/
int* numMovesStones(int a, int b, int c, int* returnSize);

// 第一个错误的版本 https://leetcode-cn.com/problems/first-bad-version/submissions/
int firstBadVersion(int n);

// 验证回文字符串 Ⅱ https://leetcode-cn.com/problems/valid-palindrome-ii/
bool validPalindrome(char * s);

// 单词规律 https://leetcode-cn.com/problems/word-pattern/ 
bool wordPattern(char * pattern, char * str);

// 压缩字符串 https://leetcode-cn.com/problems/string-compression/
int compress(char* chars, int charsSize);

// 给定数字能组成的最大时间 https://leetcode-cn.com/problems/largest-time-for-given-digits/
char * largestTimeFromDigits(int* A, int ASize);

// 寻找数组的中心索引 https://leetcode-cn.com/problems/find-pivot-index/
int pivotIndex(int* nums, int numsSize);

// 子数组最大平均数 I https://leetcode-cn.com/problems/maximum-average-subarray-i/
double findMaxAverage(int* nums, int numsSize, int k);

// 统计位数为偶数的数字 https://leetcode-cn.com/problems/find-numbers-with-even-number-of-digits/
int findNumbers(int* nums, int numsSize);

// 整数的各位积和之差 https://leetcode-cn.com/problems/subtract-the-product-and-sum-of-digits-of-an-integer/
int subtractProductAndSum(int n);

// 访问所有点的最小时间 https://leetcode-cn.com/problems/minimum-time-visiting-all-points/
int minTimeToVisitAllPoints(int** points, int pointsSize, int* pointsColSize);

// 二进制链表转整数 https://leetcode-cn.com/problems/convert-binary-number-in-a-linked-list-to-integer/
int getDecimalValue(struct ListNode* head);

// 二叉搜索树的范围和 https://leetcode-cn.com/problems/range-sum-of-bst/
int rangeSumBST(struct TreeNode* root, int L, int R);

// 奇数值单元格的数目 https://leetcode-cn.com/problems/cells-with-odd-values-in-a-matrix/
int oddCells(int n, int m, int** indices, int indicesSize, int* indicesColSize);

// 二叉搜索树中的搜索 https://leetcode-cn.com/problems/search-in-a-binary-search-tree/
struct TreeNode* searchBST(struct TreeNode* root, int val);

// 键盘行 https://leetcode-cn.com/problems/keyboard-row/
char ** findWords(char ** words, int wordsSize, int* returnSize);

// 字符的最短距离 https://leetcode-cn.com/problems/shortest-distance-to-a-character/
int* shortestToChar(char * S, char C, int* returnSize);

// 子域名访问计数 https://leetcode-cn.com/problems/subdomain-visit-count/
char ** subdomainVisits(char ** cpdomains, int cpdomainsSize, int* returnSize);

// 车的可用捕获量 https://leetcode-cn.com/problems/available-captures-for-rook/
int numRookCaptures(char** board, int boardSize, int* boardColSize);

// 有序数组中出现次数超过25%的元素 https://leetcode-cn.com/problems/element-appearing-more-than-25-in-sorted-array/
int findSpecialInteger(int* arr, int arrSize);

// 查询后的偶数和 https://leetcode-cn.com/problems/sum-of-even-numbers-after-queries/
int* sumEvenAfterQueries(int* A, int ASize, int** queries, int queriesSize, int* queriesColSize, int* returnSize);

// 分式化简 https://leetcode-cn.com/problems/deep-dark-fraction/
int* fraction(int* cont, int contSize, int* returnSize);

// 二叉搜索树的最小绝对差 https://leetcode-cn.com/problems/minimum-absolute-difference-in-bst/
int getMinimumDifference(struct TreeNode* root);

// 二维网格迁移 https://leetcode-cn.com/problems/shift-2d-grid/
int** shiftGrid(int** grid, int gridSize, int* gridColSize, int k, int* returnSize, int** returnColumnSizes);

// 左叶子之和 https://leetcode-cn.com/problems/sum-of-left-leaves/
int sumOfLeftLeaves(struct TreeNode* root);

// 两数之和 IV - 输入 BST https://leetcode-cn.com/problems/two-sum-iv-input-is-a-bst/
bool findTarget(struct TreeNode* root, int k);

// 存在重复元素 II https://leetcode-cn.com/problems/contains-duplicate-ii/
bool containsNearbyDuplicate(int* nums, int numsSize, int k);

// 错误的集合 https://leetcode-cn.com/problems/set-mismatch/
int* findErrorNums(int* nums, int numsSize, int* returnSize);

// Excel表列名称 https://leetcode-cn.com/problems/excel-sheet-column-title/
char * convertToTitle(int n);

// 密钥格式化 https://leetcode-cn.com/problems/license-key-formatting/
char * licenseKeyFormatting(char * S, int K);

// 强整数 https://leetcode-cn.com/problems/powerful-integers/
int* powerfulIntegers(int x, int y, int bound, int* returnSize);

// 到最近的人的最大距离 https://leetcode-cn.com/problems/maximize-distance-to-closest-person/
int maxDistToClosest(int* seats, int seatsSize);

// 有效的回旋镖 https://leetcode-cn.com/problems/valid-boomerang/
bool isBoomerang(int** points, int pointsSize, int* pointsColSize);

// 最常见的单词 https://leetcode-cn.com/problems/most-common-word/
char * mostCommonWord(char * paragraph, char ** banned, int bannedSize);

// 最短无序连续子数组 https://leetcode-cn.com/problems/shortest-unsorted-continuous-subarray/
int findUnsortedSubarray(int* nums, int numsSize);

// 平方数之和 https://leetcode-cn.com/problems/sum-of-square-numbers/
bool judgeSquareSum(int c);

// 非递减数列 https://leetcode-cn.com/problems/non-decreasing-array/
bool checkPossibility(int* nums, int numsSize);

// 卡牌分组 https://leetcode-cn.com/problems/x-of-a-kind-in-a-deck-of-cards/
bool hasGroupsSizeX(int* deck, int deckSize);

// 字符串中的单词数 https://leetcode-cn.com/problems/number-of-segments-in-a-string/
int countSegments(char * s);

// 模拟行走机器人 https://leetcode-cn.com/problems/walking-robot-simulation/
int robotSim(int* commands, int commandsSize, int** obstacles, int obstaclesSize, int* obstaclesColSize);

// 亲密字符串 https://leetcode-cn.com/problems/buddy-strings/ 
bool buddyStrings(char * A, char * B);

// 重复叠加字符串匹配 https://leetcode-cn.com/problems/repeated-string-match/
int repeatedStringMatch(char * A, char * B);

// 供暖器 https://leetcode-cn.com/problems/heaters/
int findRadius(int* houses, int housesSize, int* heaters, int heatersSize);

// 矩阵中的幻方 https://leetcode-cn.com/problems/magic-squares-in-grid/
int numMagicSquaresInside(int** grid, int gridSize, int* gridColSize);

// 种花问题 https://leetcode-cn.com/problems/can-place-flowers/
bool canPlaceFlowers(int* flowerbed, int flowerbedSize, int n);

// 层数最深叶子节点的和 https://leetcode-cn.com/problems/deepest-leaves-sum/
int deepestLeavesSum(struct TreeNode* root);

// TinyURL 的加密与解密 https://leetcode-cn.com/problems/encode-and-decode-tinyurl/
/** Encodes a URL to a shortened URL. */
char* encode(char* longUrl);
/** Decodes a shortened URL to its original URL. */
char* decode(char* shortUrl);

// 保持城市天际线 https://leetcode-cn.com/problems/max-increase-to-keep-city-skyline/
int maxIncreaseKeepingSkyline(int** grid, int gridSize, int* gridColSize);

// 最大二叉树 https://leetcode-cn.com/problems/maximum-binary-tree/
struct TreeNode* constructMaximumBinaryTree(int* nums, int numsSize);

// 用户分组 https://leetcode-cn.com/problems/group-the-people-given-the-group-size-they-belong-to/
int** groupThePeople(int* groupSizes, int groupSizesSize, int* returnSize, int** returnColumnSizes);

// 按递增顺序显示卡牌 https://leetcode-cn.com/problems/reveal-cards-in-increasing-order/
int* deckRevealedIncreasing(int* deck, int deckSize, int* returnSize);

// 所有可能的路径 https://leetcode-cn.com/problems/all-paths-from-source-to-target/
int** allPathsSourceTarget(int** graph, int graphSize, int* graphColSize, int* returnSize, int** returnColumnSizes);

// 比特位计数 https://leetcode-cn.com/problems/counting-bits/
int* countBits(int num, int* returnSize);

// 数组中的K-diff数对 https://leetcode-cn.com/problems/k-diff-pairs-in-an-array/ 
int findPairs(int* nums, int numsSize, int k);

// 祖父节点值为偶数的节点和 https://leetcode-cn.com/problems/sum-of-nodes-with-even-valued-grandparent/
int sumEvenGrandparent(struct TreeNode* root);

// 两棵二叉搜索树中的所有元素 https://leetcode-cn.com/problems/all-elements-in-two-binary-search-trees/
int* getAllElements(struct TreeNode* root1, struct TreeNode* root2, int* returnSize);

// 所有可能的满二叉树 https://leetcode-cn.com/problems/all-possible-full-binary-trees/
struct TreeNode** allPossibleFBT(int N, int* returnSize);

// 翻转矩阵后的得分 https://leetcode-cn.com/problems/score-after-flipping-matrix/
int matrixScore(int** A, int ASize, int* AColSize);

// 组合 https://leetcode-cn.com/problems/combinations/
int** combine(int n, int k, int* returnSize, int** returnColumnSizes);

// 活字印刷 https://leetcode-cn.com/problems/letter-tile-possibilities/
int numTilePossibilities(char * tiles);

// 从二叉搜索树到更大和树 https://leetcode-cn.com/problems/binary-search-tree-to-greater-sum-tree/
struct TreeNode* bstToGst(struct TreeNode* root);

// 二叉树剪枝 https://leetcode-cn.com/problems/binary-tree-pruning/
struct TreeNode* pruneTree(struct TreeNode* root);

// 先序遍历构造二叉树 https://leetcode-cn.com/problems/construct-binary-search-tree-from-preorder-traversal/
struct TreeNode* bstFromPreorder(int* preorder, int preorderSize);

// 二叉搜索树中的插入操作 https://leetcode-cn.com/problems/insert-into-a-binary-search-tree/
struct TreeNode* insertIntoBST(struct TreeNode* root, int val);

// 甲板上的战舰 https://leetcode-cn.com/problems/battleships-in-a-board/
int countBattleships(char** board, int boardSize, int* boardColSize);

// 矩阵区域和 https://leetcode-cn.com/problems/matrix-block-sum/
int** matrixBlockSum(int** mat, int matSize, int* matColSize, int K, int* returnSize, int** returnColumnSizes);

// 为运算表达式设计优先级 https://leetcode-cn.com/problems/different-ways-to-add-parentheses/
int* diffWaysToCompute(char * input, int* returnSize);

// 生命游戏 https://leetcode-cn.com/problems/game-of-life/
void gameOfLife(int** board, int boardSize, int* boardColSize);

// 组合总和 III https://leetcode-cn.com/problems/combination-sum-iii/
int** combinationSum3(int k, int n, int* returnSize, int** returnColumnSizes);

// 有序链表转换二叉搜索树 https://leetcode-cn.com/problems/convert-sorted-list-to-binary-search-tree/
struct TreeNode* sortedListToBST(struct ListNode* head);

// 二叉树的中序遍历 https://leetcode-cn.com/problems/binary-tree-inorder-traversal/
int* inorderTraversal(struct TreeNode* root, int* returnSize);

// 只出现一次的数字 III https://leetcode-cn.com/problems/single-number-iii/
int* singleNumber3(int* nums, int numsSize, int* returnSize);

// 使括号有效的最少添加 https://leetcode-cn.com/problems/minimum-add-to-make-parentheses-valid/
int minAddToMakeValid(char * S);

// 二叉搜索树中第K小的元素 https://leetcode-cn.com/problems/kth-smallest-element-in-a-bst/
int kthSmallest(struct TreeNode* root, int k);

// 查找和替换模式 https://leetcode-cn.com/problems/find-and-replace-pattern/
char ** findAndReplacePattern(char ** words, int wordsSize, char * pattern, int* returnSize);

// 划分字母区间 https://leetcode-cn.com/problems/partition-labels/
int* partitionLabels(char * S, int* returnSize);

// 找树左下角的值 https://leetcode-cn.com/problems/find-bottom-left-tree-value/
int findBottomLeftValue(struct TreeNode* root);

// 格雷编码 https://leetcode-cn.com/problems/gray-code/
int* grayCode(int n, int* returnSize);

// 字典序排数 https://leetcode-cn.com/problems/lexicographical-numbers/
int* lexicalOrder(int n, int* returnSize);

// 石子游戏 https://leetcode-cn.com/problems/stone-game/
bool stoneGame(int* piles, int pilesSize);

// 复数乘法 https://leetcode-cn.com/problems/complex-number-multiplication/
char * complexNumberMultiply(char * a, char * b);

// 二叉树寻路 https://leetcode-cn.com/problems/path-in-zigzag-labelled-binary-tree/
int* pathInZigZagTree(int label, int* returnSize);

// 最大层内元素和 https://leetcode-cn.com/problems/maximum-level-sum-of-a-binary-tree/
int maxLevelSum(struct TreeNode* root);

// 二叉树展开为链表 https://leetcode-cn.com/problems/flatten-binary-tree-to-linked-list/ 
void flatten(struct TreeNode* root);

// 从中序与后序遍历序列构造二叉树 https://leetcode-cn.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/
struct TreeNode* buildTree(int* inorder, int inorderSize, int* postorder, int postorderSize);

// 有效括号的嵌套深度 https://leetcode-cn.com/problems/maximum-nesting-depth-of-two-valid-parentheses-strings/
int* maxDepthAfterSplit(char * seq, int* returnSize);

// 除自身以外数组的乘积 https://leetcode-cn.com/problems/product-of-array-except-self/
int* productExceptSelf(int* nums, int numsSize, int* returnSize);

// 222.完全二叉树的节点个数 https://leetcode-cn.com/problems/count-complete-tree-nodes/
int countNodes(struct TreeNode* root);

// 137.只出现一次的数字 II https://leetcode-cn.com/problems/single-number-ii/
int singleNumber(int* nums, int numsSize);

// 1325.删除给定值的叶子节点 https://leetcode-cn.com/problems/delete-leaves-with-a-given-value/
struct TreeNode* removeLeafNodes(struct TreeNode* root, int target);

// 131.分割回文串 https://leetcode-cn.com/problems/palindrome-partitioning/
char *** partition(char * s, int* returnSize, int** returnColumnSizes);

// 40.组合总和 II https://leetcode-cn.com/problems/combination-sum-ii/
int** combinationSum2(int* candidates, int candidatesSize, int target, int* returnSize, int** returnColumnSizes);

// 1277.统计全为 1 的正方形子矩阵 https://leetcode-cn.com/problems/count-square-submatrices-with-all-ones/
int countSquares(int** matrix, int matrixSize, int* matrixColSize);

// 979.在二叉树中分配硬币 https://leetcode-cn.com/problems/distribute-coins-in-binary-tree/
int distributeCoins(struct TreeNode* root);

// 791.自定义字符串排序 https://leetcode-cn.com/problems/custom-sort-string/
char * customSortString(char * S, char * T);

// 96.不同的二叉搜索树 https://leetcode-cn.com/problems/unique-binary-search-trees/
int numTrees(int n);

// 面试题64. 求 1+2+...+n ，要求不能使用乘除法、for、while、if、else、switch、case等关键字及条件判断语句（A?B:C）。 https://leetcode-cn.com/problems/qiu-12n-lcof/
int sumNums(int n);

// 207.课程表
bool canFinish(int numCourses, int** prerequisites, int prerequisitesSize, int* prerequisitesColSize);
// 210. 课程表 II
int* findOrder(int numCourses, int** prerequisites, int prerequisitesSize, int* prerequisitesColSize, int* returnSize);

// 47. 全排列 II
int** permuteUnique(int* nums, int numsSize, int* returnSize, int** returnColumnSizes);

// 837. 新21点
double new21Game(int N, int K, int W);

// 1028. 从先序遍历还原二叉树
struct TreeNode* recoverFromPreorder(char * S);

// 1014. 最佳观光组合
int maxScoreSightseeingPair(int* A, int ASize);

// 297. 二叉树的序列化与反序列化
/** Encodes a tree to a single string. */
char* serialize(struct TreeNode* root);
/** Decodes your encoded data to tree. */
struct TreeNode* deserialize(char* data);

// 面试题 16.18. 模式匹配
bool patternMatching(char* pattern, char* value);

// 209. 长度最小的子数组
int minSubArrayLen(int s, int* nums, int numsSize);

//718. 最长重复子数组
int findLength(int* A, int ASize, int* B, int BSize);

//378. 有序矩阵中第K小的元素
int kthSmallest2(int** matrix, int matrixSize, int* matrixColSize, int k);

//剑指 Offer 09. 用两个栈实现队列
typedef struct {
    struct ListNode *first;
    struct ListNode *last;
} CQueue;

CQueue* cQueueCreate(void);

void cQueueAppendTail(CQueue* obj, int value);

int cQueueDeleteHead(CQueue* obj);

void cQueueFree(CQueue* obj);

// 785. 判断二分图
bool isBipartite(int** graph, int graphSize, int* graphColSize);

// 剑指 Offer 11. 旋转数组的最小数字
int minArray(int* numbers, int numbersSize);

// 95. 不同的二叉搜索树 II
struct TreeNode** generateTrees(int n, int* returnSize);

// 97. 交错字符串
bool isInterleave(char * s1, char * s2, char * s3);

// 174. 地下城游戏
int calculateMinimumHP(int** dungeon, int dungeonSize, int* dungeonColSize);

// 315. 计算右侧小于当前元素的个数
int* countSmaller(int* nums, int numsSize, int* returnSize);

// 329. 矩阵中的最长递增路径
int longestIncreasingPath(int** matrix, int matrixSize, int* matrixColSize);

// LCP 13. 寻宝
int minimalSteps(char** maze, int mazeSize);

// 343. 整数拆分
int integerBreak(int n);

// 312. 戳气球
int maxCoins(int* nums, int numsSize);

// 面试题 08.03. 魔术索引
int findMagicIndex(int* nums, int numsSize);

// 133. 克隆图
struct Node *cloneGraph(struct Node *s);

// 130. 被围绕的区域
void solve(char** board, int boardSize, int* boardColSize);

// 93. 复原IP地址
char ** restoreIpAddresses(char * s, int* returnSize);

// 99. 恢复二叉搜索树
void recoverTree(struct TreeNode* root);

// 546. 移除盒子(未完成TODO)
int removeBoxes(int* boxes, int boxesSize);

// 647. 回文子串
int countSubstrings(char * s);

// 529. 扫雷游戏
char** updateBoard(char** board, int boardSize, int* boardColSize, int* click, int clickSize, int* returnSize, int** returnColumnSizes);

// 剑指 Offer 20. 表示数值的字符串
bool isNumber(char* s);

// 486. 预测赢家
bool PredictTheWinner(int* nums, int numsSize);

// 841. 钥匙和房间
bool canVisitAllRooms(int** rooms, int roomsSize, int* roomsColSize);

// 214. 最短回文串
char * shortestPalindrome(char * s);

// 347. 前 K 个高频元素
int* topKFrequent(int* nums, int numsSize, int k, int* returnSize);

// 79. 单词搜索
bool exist(char** board, int boardSize, int* boardColSize, char * word);

// 968. 监控二叉树
int minCameraCover(struct TreeNode* root);

// 416. 分割等和子集
bool canPartition(int* nums, int numsSize);

// 116. 填充每个节点的下一个右侧节点指针
struct NodeRight* connectRight(struct NodeRight* root);

// 52. N皇后 II
int totalNQueens(int n);

// 140. 单词拆分 II
char ** wordBreak(char * s, char ** wordDict, int wordDictSize, int* returnSize);

// 129. 求根到叶子节点数字之和
int sumNumbers(struct TreeNode* root);

// 144. 二叉树的前序遍历
int* preorderTraversal(struct TreeNode* root, int* returnSize);

// 57. 插入区间
int** insert(int** intervals, int intervalsSize, int* intervalsColSize, int* newInterval, int newIntervalSize, int* returnSize, int** returnColumnSizes);

// 1356. 根据数字二进制下 1 的数目排序
int* sortByBits(int* arr, int arrSize, int* returnSize);

// 127. 单词接龙
int ladderLength(char * beginWord, char * endWord, char ** wordList, int wordListSize);

// 328. 奇偶链表
struct ListNode* oddEvenList(struct ListNode* head);

// 406. 根据身高重建队列
int** reconstructQueue(int** people, int peopleSize, int* peopleColSize, int* returnSize, int** returnColumnSizes);

// 134. 加油站
int canCompleteCircuit(int* gas, int gasSize, int* cost, int costSize);

// 402. 移掉K位数字
char * removeKdigits(char * num, int k);

// 147. 对链表进行插入排序
struct ListNode* insertionSortList(struct ListNode* head);

// 452. 用最少数量的箭引爆气球
int findMinArrowShots(int** points, int pointsSize, int* pointsColSize);


// 148. 排序链表
struct ListNode* sortList(struct ListNode* head);

// 1370. 上升下降字符串
char * sortString(char * s);

// 767. 重构字符串
char * reorganizeString(char * S);

// 493. 翻转对
int reversePairs(int* nums, int numsSize);

// 321. 拼接最大数
int* maxNumber(int* nums1, int nums1Size, int* nums2, int nums2Size, int k, int* returnSize);

// 842. 将数组拆分成斐波那契序列
int* splitIntoFibonacci(char * S, int* returnSize);

// 621. 任务调度器
int leastInterval(char* tasks, int tasksSize, int n);

// 659. 分割数组为连续子序列
bool isPossible(int* nums, int numsSize);

// 649. Dota2 参议院
char * predictPartyVictory(char * senate);


// 49. 字母异位词分组
char *** groupAnagrams(char ** strs, int strsSize, int* returnSize, int** returnColumnSizes);

// 738. 单调递增的数字
int monotoneIncreasingDigits(int N);

// 376. 摆动序列
int wiggleMaxLength(int* nums, int numsSize);

// 714. 买卖股票的最佳时机含手续费
int maxProfit3(int* prices, int pricesSize, int fee);

// 316. 去除重复字母
char * removeDuplicateLetters(char * s);

// 103. 二叉树的锯齿形层序遍历
int** zigzagLevelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes);

// 188. 买卖股票的最佳时机 IV
int maxProfit4(int k, int* prices, int pricesSize);

// 85. 最大矩形
int maximalRectangle(char** matrix, int matrixSize, int* matrixColSize);

// 330. 按要求补齐数组
int minPatches(int* nums, int numsSize, int n);

// 1202. 交换字符串中的元素
char * smallestStringWithSwaps(char * s, int** pairs, int pairsSize, int* pairsColSize);

// 1203. 项目管理
int* sortItems(int n, int m, int* group, int groupSize, int** beforeItems, int beforeItemsSize, int* beforeItemsColSize, int* returnSize);

// 684. 冗余连接
int* findRedundantConnection(int** edges, int edgesSize, int* edgesColSize, int* returnSize);

// 86. 分隔链表
struct ListNode* partition2(struct ListNode* head, int x);

// 399. 除法求值
double* calcEquation(char *** equations, int equationsSize, int* equationsColSize, double* values, int valuesSize, char *** queries, int queriesSize, int* queriesColSize, int* returnSize);

// 547. 省份数量
int findCircleNum(int** isConnected, int isConnectedSize, int* isConnectedColSize);

// 123. 买卖股票的最佳时机 III
int maxProfit5(int* prices, int pricesSize);

// 947. 移除最多的同行或同列石头
int removeStones(int** stones, int stonesSize, int* stonesColSize);

// 228. 汇总区间
char ** summaryRanges(int* nums, int numsSize, int* returnSize);

// 1584. 连接所有点的最小费用
int minCostConnectPoints(int** points, int pointsSize, int* pointsColSize);

// 1631. 最小体力消耗路径
int minimumEffortPath(int** heights, int heightsSize, int* heightsColSize);

// 424. 替换后的最长重复字符
int characterReplacement(char * s, int k);

// 778. 水位上升的泳池中游泳
int swimInWater(int** grid, int gridSize, int* gridColSize);

// 480. 滑动窗口中位数
double* medianSlidingWindow(int* nums, int numsSize, int k, int* returnSize);

// 1208. 尽可能使字符串相等
int equalSubstring(char * s, char * t, int maxCost);

// 1423. 可获得的最大点数
int maxScore(int* cardPoints, int cardPointsSize, int k);

// 面试题 16.05. 阶乘尾数
int trailingZeroes(int n);

// 面试题 10.05. 稀疏数组搜索
int findString(char** words, int wordsSize, char* s);

// 面试题 16.11. 跳水板
int* divingBoard(int shorter, int longer, int k, int* returnSize);

// 面试题 16.07. 最大数值 (不得使用if-else或其他比较运算符。)
int maximum(int a, int b);

// 面试题 16.15. 珠玑妙算
int* masterMind(char* solution, char* guess, int* returnSize);

// 978. 最长湍流子数组
int maxTurbulenceSize(int* arr, int arrSize);

// 面试题 17.04. 消失的数字
int missingNumber(int* nums, int numsSize);



#endif /* LeetCodeC_h */
