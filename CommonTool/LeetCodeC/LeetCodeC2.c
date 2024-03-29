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

// 从小到大排序
int compare(void* a, void* b) {
    return *(int*) a - *(int*) b;
}

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

int longestSubarray(int* nums, int numsSize, int limit){
    int left = 0;
    int right = 1;
    int minNum = nums[0];
    int maxNum = nums[0];
    int maxLen = 1;
    for (int i = 1; i < numsSize; ++i) {
        if (nums[i] < minNum) {
            minNum = nums[i];
        }else if (nums[i] > maxNum) {
            maxNum = nums[i];
        }
        if (maxNum-minNum > limit) {
            maxNum = nums[i];
            minNum = nums[i];
            int minNum2 = minNum;
            int maxNum2 = maxNum;
            left = right;
            while (maxNum-minNum <= limit) {
                --left;
                if (left < 0) {
                    break;
                }
                if (nums[left] < minNum) {
                    minNum2 = minNum;
                    minNum = nums[left];
                }else if (nums[left] > maxNum) {
                    maxNum2 = maxNum;
                    maxNum = nums[left];
                }
            }
            minNum = minNum2;
            maxNum = maxNum2;
            ++left;
            ++right;
        }else{
            ++right;
            if (right-left > maxLen) {
                maxLen = right-left;
            }
        }
    }
    
    return maxLen;
}


typedef struct {
    struct ListNode *firstNode;
    int k;
    int count;
} KthLargest;


KthLargest* kthLargestCreate(int k, int* nums, int numsSize) {
    KthLargest *obj = malloc(sizeof(KthLargest));
    obj->firstNode = NULL;
    obj->k = k;
    qsort(nums, numsSize, sizeof(*nums), compare);
    struct ListNode *lastNode = NULL;
    int i = numsSize-k;
    if (numsSize < k) {
        i = 0;
        obj->count = numsSize;
    }else{
        obj->count = k;
    }
    for (; i < numsSize; ++i) {
        struct ListNode *newNode = malloc(sizeof(struct ListNode));
        newNode->val = nums[i];
        newNode->next = NULL;
        if (lastNode == NULL) {
            lastNode = newNode;
            obj->firstNode = newNode;
        }else{
            lastNode->next = newNode;
        }
        lastNode = newNode;
    }
    
    return obj;
}

int kthLargestAdd(KthLargest* obj, int val) {
    
    struct ListNode *lastNode = NULL;
    struct ListNode *curNode = obj->firstNode;
    if (obj->count != obj->k) {
    
    }else if (obj->firstNode->val >= val) {
        return obj->firstNode->val;
    }
    
    struct ListNode *newNode = malloc(sizeof(struct ListNode));
    newNode->val = val;
    newNode->next = NULL;
    while (curNode) {
        if (curNode->val >= val) {
            newNode->next = curNode;
            break;
        }
        lastNode = curNode;
        curNode = curNode->next;
    }
    if (lastNode == NULL) {
        lastNode = newNode;
        obj->firstNode = lastNode;
    }else{
        lastNode->next = newNode;
    }
    if (obj->count == obj->k) {
        struct ListNode *oldNode = obj->firstNode;
        obj->firstNode = obj->firstNode->next;
        free(oldNode);
    }else{
        obj->count = obj->k;
    }
    return obj->firstNode->val;
}

void kthLargestFree(KthLargest* obj) {
    
}

//struct unordered_map {
//    int key, val;
//    UT_hash_handle hh;
//};
//
//int* findNumOfValidWords(char** words, int wordsSize, char** puzzles, int puzzlesSize, int* returnSize) {
//    struct unordered_map* frequency = NULL;
//
//    for (int i = 0; i < wordsSize; i++) {
//        int n = strlen(words[i]);
//        int mask = 0;
//        for (int j = 0; j < n; j++) {
//            mask |= (1 << (words[i][j] - 'a'));
//        }
//        if (__builtin_popcount(mask) <= 7) {
//            struct unordered_map* tmp;
//            
//            HASH_FIND_INT(frequency, &mask, tmp);
//            if (tmp == NULL) {
//                tmp = malloc(sizeof(struct unordered_map));
//                tmp->key = mask;
//                tmp->val = 1;
//                HASH_ADD_INT(frequency, key, tmp);
//            } else {
//                tmp->val++;
//            }
//        }
//    }
//
//    int* ans = malloc(sizeof(int) * puzzlesSize);
//    *returnSize = 0;
//
//    for (int i = 0; i < puzzlesSize; i++) {
//        int total = 0;
//
//        // 枚举子集方法一
//        // for (int choose = 0; choose < (1 << 6); ++choose) {
//        //     int mask = 0;
//        //     for (int j = 0; j < 6; ++j) {
//        //         if (choose & (1 << j)) {
//        //             mask |= (1 << (puzzles[i][j + 1] - 'a'));
//        //         }
//        //     }
//        //     mask |= (1 << (puzzles[i][0] - 'a'));
//        //     struct unordered_map* tmp;
//        //     HASH_FIND_INT(frequency, &mask, tmp);
//        //     if (tmp != NULL) {
//        //         total += tmp->val;
//        //     }
//        // }
//
//        // 枚举子集方法二
//        int mask = 0;
//        for (int j = 1; j < 7; ++j) {
//            mask |= (1 << (puzzles[i][j] - 'a'));
//        }
//        int subset = mask;
//        do {
//            int s = subset | (1 << (puzzles[i][0] - 'a'));
//            struct unordered_map* tmp;
//            HASH_FIND_INT(frequency, &s, tmp);
//            if (tmp != NULL) {
//                total += tmp->val;
//            }
//            subset = (subset - 1) & mask;
//        } while (subset != mask);
//        ans[(*returnSize)++] = total;
//    }
//    return ans;
//}

//int* findNumOfValidWords(char ** words, int wordsSize, char ** puzzles, int puzzlesSize, int* returnSize){
//    // m*n的複雜度，會超時
//    int *result = malloc(sizeof(int)*puzzlesSize);
//    memset(result, 0, sizeof(int)*puzzlesSize);
//    *returnSize = puzzlesSize;
//    int puzzleCharCount[puzzlesSize];
//    
//    for (int i = 0; i < puzzlesSize; ++i) {
//        int j = 0;
//        puzzleCharCount[i] = 0;
//        while (puzzles[i][j] != '\0') {
//            puzzleCharCount[i] |= 1<<(puzzles[i][j]-'a');
//            ++j;
//        }
//    }
//    
//    for (int i = 0; i < wordsSize; ++i) {
//        int j = 0;
//        int mask = 0;
//        while (words[i][j] != '\0') {
//            mask |= 1 << (words[i][j]-'a');
//            ++j;
//        }
//        for (int k = 0; k < puzzlesSize; ++k) {
//            if ((mask & (1 << (puzzles[k][0]-'a'))) == 0) {
//                continue;
//            }
//            int flag = mask&puzzleCharCount[k];
//            if (mask == flag) result[k] += 1;
//        }
//    }
//    
//    return result;
//}

int longestSubstring(char * s, int k){
    int ret = 0;
    int n = strlen(s);
    for (int t = 1; t <= 26; t++) {
        int l = 0, r = 0;
        int cnt[26];
        memset(cnt, 0, sizeof(cnt));
        int tot = 0;
        int less = 0;
        while (r < n) {
            cnt[s[r] - 'a']++;
            if (cnt[s[r] - 'a'] == 1) {
                tot++;
                less++;
            }
            if (cnt[s[r] - 'a'] == k) {
                less--;
            }

            while (tot > t) {
                cnt[s[l] - 'a']--;
                if (cnt[s[l] - 'a'] == k - 1) {
                    less++;
                }
                if (cnt[s[l] - 'a'] == 0) {
                    tot--;
                    less--;
                }
                l++;
            }
            if (less == 0) {
                ret = fmax(ret, r - l + 1);
            }
            r++;
        }
    }
    return ret;

}

typedef struct {
    int** sums;
    int sumsSize;
} NumMatrix;

NumMatrix* numMatrixCreate(int** matrix, int matrixSize, int* matrixColSize) {
    NumMatrix* ret = malloc(sizeof(NumMatrix));
    ret->sums = malloc(sizeof(int*) * (matrixSize + 1));
    ret->sumsSize = matrixSize + 1;
    int n = matrixSize ? matrixColSize[0] : 0;
    for (int i = 0; i <= matrixSize; i++) {
        ret->sums[i] = malloc(sizeof(int) * (n + 1));
        memset(ret->sums[i], 0, sizeof(int) * (n + 1));
    }
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixColSize[i]; j++) {
            ret->sums[i + 1][j + 1] = ret->sums[i][j + 1] + ret->sums[i + 1][j] - ret->sums[i][j] + matrix[i][j];
        }
    }
    return ret;
}

int numMatrixSumRegion(NumMatrix* obj, int row1, int col1, int row2, int col2) {
    return obj->sums[row2 + 1][col2 + 1] - obj->sums[row1][col2 + 1] - obj->sums[row2 + 1][col1] + obj->sums[row1][col1];
}

void numMatrixFree(NumMatrix* obj) {
    for (int i = 0; i < obj->sumsSize; i++) {
        free(obj->sums[i]);
    }
    free(obj->sums);
}


int findRepeatNumber(int* nums, int numsSize){
    // hash法, 时 O(n), 空 O(n)
    int count[numsSize];
    memset(count, 0, sizeof(int)*numsSize);
    for (int i = 0; i < numsSize; ++i) {
        count[nums[i]] += 1;
        if (count[nums[i]] > 1) return nums[i];
    }
    
    // 原地置换, 时 O(n), 空 O(1)，但要修改原数组
    for (int i = 0; i < numsSize;) {
        if (nums[i] == i) {
            ++i;
            continue;
        }
        if (nums[nums[i]] == nums[i]) {
            return nums[i];
        }
        int tmp = nums[nums[i]];
        nums[nums[i]] = nums[i];
        nums[i] = tmp;
    }
    
    return -1;
}

bool findNumberIn2DArrayHelper(int** matrix, int target, int r1, int r2, int c1, int c2) {
    if (r2 < r1 || c2 < c1) return false;
    int r = (r1+r2)/2;
    int c = (c1+c2)/2;
    if (matrix[r][c] == target) {
        return true;
    }else if (matrix[r][c] > target) {
        bool flag = findNumberIn2DArrayHelper(matrix, target, r1, r2, c1, c-1);
        if (flag) return flag;
        return findNumberIn2DArrayHelper(matrix, target, r1, r-1, c, c2);
    }else{
        bool flag = findNumberIn2DArrayHelper(matrix, target, r1, r2, c+1, c2);
        if (flag) return flag;
        return findNumberIn2DArrayHelper(matrix, target, r+1, r2, c1, c);
    }
}

bool findNumberIn2DArray(int** matrix, int matrixSize, int* matrixColSize, int target){
    if (matrixSize == 0) return false;
    // 二分递归, O(log(m*n)), O(log(m)+log(n))
    return findNumberIn2DArrayHelper(matrix, target, 0, matrixSize-1, 0, matrixColSize[0]-1);
    /*
    target > matrix[r][c]
        target不在matrix[0~r][0~c]
    target < matrix[r][c]
        target不在matrix[r~n-1][c~m-1]
     */
     
     // 线性查找，可从右上角或左下角开始找, O(m+n), O(1)
    int r = 0;
    int c = matrixColSize[0]-1;
    while (r < matrixSize && c >= 0) {
        if (matrix[r][c] == target) {
            return true;
        }else if (matrix[r][c] > target) {
            --c;
        }else{
            ++r;
        }
    }
    
    return false;
}

char* replaceSpace(char* s){
    int length = strlen(s);
    char* result = malloc(sizeof(char)*length*3+1);
    int i = 0;
    int index = 0;
    while (s[i] != 0) {
        if (s[i] == ' ') {
            result[index++] = '%';
            result[index++] = '0';
            result[index] = '2';
        }else{
            result[index] = s[i];
        }
        ++index;
        ++i;
    }
    result[index] = '\0';
    
    return result;
}

int* reversePrint(struct ListNode* head, int* returnSize){
    int *result = malloc(sizeof(int)*10000);
    int length = 0;
    struct ListNode* curNode = head;
    while (curNode) {
        result[length++] = curNode->val;
        curNode = curNode->next;
    }
    int left = 0;
    int right = length-1;
    while (left < right) {
        int tmp = result[right];
        result[right] = result[left];
        result[left] = tmp;
        ++left;
        --right;
    }
    *returnSize = length;
    return result;
}

struct TreeNode* buildTreeHelper(int* preorder, int* inorder, int pl, int pr, int il, int ir) {
    if (pr < pl) return NULL;
    int rootValue = preorder[pl];
    int rootValueIndex = il-1;
    for (int i = il; i <= ir; ++i) {
        if (inorder[i] == rootValue) {
            rootValueIndex = i;
            break;
        }
    }
    int leftSize = rootValueIndex-il;
    struct TreeNode *rootNode = malloc(sizeof(struct TreeNode));
    rootNode->val = rootValue;
    rootNode->left = buildTreeHelper(preorder, inorder, pl+1, pl+leftSize, il, rootValueIndex-1);
    rootNode->right = buildTreeHelper(preorder, inorder, pl+leftSize+1, pr, rootValueIndex+1, ir);
    
    return rootNode;
}

struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize){
    // 前序历遍 根左右
    // 中序历遍 左根右
    // 后序历遍 左右根
    
    /*
    前序历遍第一个是根，然后通过根在中序历遍里找，就可以确定根在中序历遍的位置，从而获得左右子树的节点数量
    
     */
    return buildTreeHelper(preorder, inorder, 0, preorderSize-1, 0, inorderSize-1);
    
}

int maxEnvelopesCmp(int** a, int** b) {
    return (*a)[0] == (*b)[0] ? (*b)[1] - (*a)[1] : (*a)[0] - (*b)[0];
}

int maxEnvelopes(int** envelopes, int envelopesSize, int* envelopesColSize) {
    if (envelopesSize == 0) {
        return 0;
    }
    // 宽从小到大排序，再把高从大到小排序
    qsort(envelopes, envelopesSize, sizeof(int*), maxEnvelopesCmp);

    int n = envelopesSize;
    int f[n];
    for (int i = 0; i < n; i++) {
        f[i] = 1;
    }
    int ret = 1;
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (envelopes[j][1] < envelopes[i][1]) {
                f[i] = fmax(f[i], f[j] + 1);
            }
        }
        ret = fmax(ret, f[i]);
    }
    return ret;
}

int minCut(char * s){
    int n = strlen(s);
    bool g[n][n];
    memset(g, 1, sizeof(g));

    for (int i = n - 1; i >= 0; --i) {
        for (int j = i + 1; j < n; ++j) {
            g[i][j] = (s[i] == s[j]) && g[i + 1][j - 1];
        }
    }

    int f[n];
    for (int i = 0; i < n; ++i) {
        f[i] = INTMAX_MAX;
    }
    for (int i = 0; i < n; ++i) {
        if (g[0][i]) {
            f[i] = 0;
        } else {
            for (int j = 0; j < i; ++j) {
                if (g[j + 1][i]) {
                    f[i] = fmin(f[i], f[j] + 1);
                }
            }
        }
    }

    return f[n - 1];

}

int fib(int n){
    if (n == 0) return 0;
    if (n == 1) return 1;
    
    int f1 = 0;
    int f2 = 1;
    for (int i = 2; i <= n; ++i) {
        int tmp = f1+f2;
        f1 = f2;
        f2 = tmp%1000000007;
    }
    
    return f2;
}

int numWays(int n){
    if (n < 2) return 1;
    int f0 = 1;
    int f1 = 1;
    for (int i = 2; i <= n; ++i) {
        int tmp = f0+f1;
        f0 = f1;
        f1 = tmp%1000000007;
    }
    
    return f1;
}

bool existHelper(char** board, int n, int m, char* word, int i, int j){
    if (word[0] == 0) return true;
    if (i < 0 || i == n || j < 0 || j == m  || board[i][j] != word[0]) {
        return false;
    }
    
    board[i][j] = 0;
    int isExist = false;
    isExist = existHelper(board, n, m, word+1, i+1, j) || existHelper(board, n, m, word+1, i-1, j) || existHelper(board, n, m, word+1, i, j+1) || existHelper(board, n, m, word+1, i, j-1);
    board[i][j] = word[0];
    
    return isExist;
}

bool exist(char** board, int boardSize, int* boardColSize, char* word){
    int n = boardSize;
    int m = boardColSize[0];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            bool isExist = existHelper(board, n, m, word, i, j);
            if (isExist) return isExist;
        }
    }
    return false;
}

int movingCountHelper(int m, int n, int k, int **visit, int i, int j, int *bit) {
    if (i >= m || j >= n || bit[i]+bit[j] > k || visit[i][j] == 1) {
        return 0;
    }
    visit[i][j] = 1;
    int count = 1;
    count += movingCountHelper(m, n, k, visit, i+1, j, bit)+movingCountHelper(m, n, k, visit, i, j+1, bit);
    return count;
}

int movingCount(int m, int n, int k){
    int **visit = malloc(sizeof(int*)*m);
    for (int i = 0; i < m; ++i) {
        visit[i] = malloc(sizeof(int)*n);
        for (int j = 0; j < n; ++j) {
            visit[i][j] = 0;
        }
    }
    
    int maxNum = fmax(m, n);
    int *bit = malloc(sizeof(int)*maxNum);
    for (int i = 0; i < maxNum; ++i) {
        bit[i] = i/100+i%10+(i/10)%10;
    }
    
    return movingCountHelper(m, n, k, visit, 0, 0, bit);
}

int calculateHelper(char * s, int *i){
    int startI = *i;
    long num = 0;
    long result = 0;
    int isPlus = true;
    while (s[*i] != 0) {
        if (s[*i] == '(') {
            *i += 1;
            num = calculateHelper(s, i);
        }else if (s[*i] == ')') {
            if (isPlus) {
                result += num;
            }else{
                result -= num;
            }
            num = 0;
            if (startI != 0) return result;
        }else if (s[*i] == '+') {
            if (isPlus) {
                result += num;
            }else{
                result -= num;
            }
            num = 0;
            isPlus = true;
        }else if (s[*i] == '-') {
            if (isPlus) {
                result += num;
            }else{
                result -= num;
            }
            num = 0;
            isPlus = false;
        }else if (s[*i] == ' ') {
        
        }else{
            num = num*10+s[*i]-'0';
        }
        
        *i += 1;
    }
    
    if (isPlus) {
        result += num;
    }else{
        result -= num;
    }
    
    return result;
}

int calculate(char * s){
    int i = 0;
    return calculateHelper(s, &i);
}


int calculate2(char * s){

    long result = 0;
    long num = 0;
    long mutNum = 1;
    int isMut = 1;
    int isPlus = 1;
    
    int i = 0;
    while (s[i] != 0) {
        if (s[i] >= '0' && s[i] <= '9') {
            num = num*10+s[i]-'0';
        }else if (s[i] != ' '){
            if (isMut == 1) {
                mutNum *= num;
            }else{
                mutNum /= num;
            }
            num = 0;
            if (s[i] == '/') {
                isMut = 0;
            }else{
                isMut = 1;
                if (s[i] != '*') {
                    if (isPlus == 1) {
                        result += mutNum;
                    }else{
                        result -= mutNum;
                    }
                    mutNum = 1;
                    if (s[i] == '+') {
                        isPlus = 1;
                    }else{
                        isPlus = 0;
                    }
                }
            }
        }
        ++i;
    }
    
    if (isMut == 1) {
        mutNum *= num;
    }else{
        mutNum /= num;
    }
    num = 0;
    isMut = 1;
    if (isPlus == 1) {
        result += mutNum;
    }else{
        result -= mutNum;
    }
    
    return result;
}

bool isValidSerialization(char * preorder){
    // #的数量为n, 那么有值的节点为n-1，','的数量为2(n-1)
    int i = 0;
    int countnull = -2;
    int countPoint = 0;
    while (preorder[i] != 0) {
        if (preorder[i] == ',') {
            countPoint += 1;
        }else if (preorder[i] == '#'){
            countnull += 2;
            if (countnull > countPoint || (countnull == countPoint && preorder[i+1] != 0)) {
                return false;
            }
        }
        ++i;
    }
    return countnull == countPoint;
}

int* nextGreaterElements(int* nums, int numsSize, int* returnSize){
    *returnSize = numsSize;
    if (numsSize == 0) {
        return NULL;
    }
    int* ret = malloc(sizeof(int) * numsSize);
    memset(ret, -1, sizeof(int) * numsSize);

    int stk[numsSize * 2 - 1], top = 0;
    for (int i = 0; i < numsSize * 2 - 1; i++) {
        while (top > 0 && nums[stk[top - 1]] < nums[i % numsSize]) {
            ret[stk[top - 1]] = nums[i % numsSize];
            top--;
        }
        stk[top++] = i % numsSize;
    }
    return ret;

}

int largestNumberCmp(char** a, char** b) {
    int i = 0;
    int j = 0;
    // str1 a+b
    // str2 b+a
    char *a1 = *a;
    char *b1 = *b;
    
    while (a1[i] != 0 || b1[j] != 0) {
        if (a1[i] == 0) {
            a1 = *b;
            i = 0;
        }else if (b1[j] == 0) {
            b1 = *a;
            j = 0;
        }
        if (a1[i] == b1[j]) {
            
        }else if (a1[i] > b1[j]){
            return -1;
        }else{
            return 1;
        }
        ++i;
        ++j;
    }
    return 0;
}

char * largestNumber(int* nums, int numsSize){
    char ** numStrs = malloc(sizeof(char*)*numsSize);
    int maxNum = 0;
    int maxLength = 1;
    for (int i = 0; i < numsSize; ++i) {
        numStrs[i] = malloc(sizeof(char)*11);
        int num = nums[i];
        if (num > maxNum) {
            maxNum = num;
        }
        int index = 0;
        while (num > 9) {
            int last = num%10;
            num /= 10;
            numStrs[i][index++] = last+'0';
        }
        numStrs[i][index] = num+'0';
        numStrs[i][index+1] = '\0';
        maxLength += index+1;
        int left = 0;
        while (left < index) {
            char tmp = numStrs[i][left];
            numStrs[i][left] = numStrs[i][index];
            numStrs[i][index] = tmp;
            ++left;
            --index;
        }
    }
    if (maxNum == 0) {
        char *result = malloc(sizeof(char)*2);
        result[0] = '0';
        result[1] = '\0';
        return result;
    }
    
    qsort(numStrs, numsSize, sizeof(char*), largestNumberCmp);
    
    char *result = malloc(sizeof(char)*maxLength);
    int index = 0;
    for (int i = 0; i < numsSize; ++i) {
        int j = 0;
        while (numStrs[i][j] != '\0') {
            result[index++] = numStrs[i][j++];
        }
        free(numStrs[i]);
    }
    free(numStrs);
    result[index] = '\0';
    return result;
}

/*
 群友面试题，计算删除所有卡片所需的最小花费,
 有n张卡, 每张卡标有1~n的唯一数字，
 只能删最顶端的卡片，
 移动卡只能从顶部移到底部或底部移到顶部，
 每次移动需要花费卡片上的值
*/
int moveCardMinCost(int *nums, int numSize) {
    // 只有两种操作，从左开始(顶部)或从右开始(底部)
    // 每次删除后，剩余数组都是一样的，即删除值左边的值都会移到右边(可以看作环形循环)
    // 那么只需思考每次删除的最小cost即可
    int totalCost = numSize*(numSize+1)/2; // 所有卡变加起来的数值
    int cost = 0; // 单次删除cost
    int result = 0; // 最终结果
    int j = 0;
    
    /*
    每次删除的的时间复杂度为O(n)
    要删n个数，所以时间复杂度O(n^2)
    空间复杂度为O(1)
     */
    // 1~n-1，从小到大删除(只剩n的情况下，只有一个数，不用对比，可以跳过)
    for (int i = 1; i < numSize; ++i) {
        cost = 0;
        // 从左历遍
        while (1) {
            // 环形
            if (j == numSize) j = 0;
            if (nums[j] < i) {
                // 跳过已经被删除的值
                ++j;
                continue;
            }
            if (nums[j] == i) {
                // 总值减去一边值，得到另一边的值，取值较小的一边
                if (totalCost-cost < cost) {
                    cost = totalCost-cost;
                }
                totalCost -= i;
                result += cost;
                break;
            }
            cost += nums[j];
            ++j;
        }
    }
    return result;
}

typedef struct Trie {
    struct Trie* children[26];
    bool isEnd;
} Trie;

/** Initialize your data structure here. */

Trie* trieCreate() {
    struct Trie* obj = malloc(sizeof(struct Trie));
    //obj->children = malloc(sizeof(<#expression-or-type#>))
    obj->isEnd = false;
    return obj;
}

/** Inserts a word into the trie. */
void trieInsert(Trie* obj, char * word) {
  
}

/** Returns if the word is in the trie. */
bool trieSearch(Trie* obj, char * word) {
  
}

/** Returns if there is any word in the trie that starts with the given prefix. */
bool trieStartsWith(Trie* obj, char * prefix) {
  
}

void trieFree(Trie* obj) {
    
}

// 377. 组合总和 Ⅳ
int combinationSum4Helper(int* nums, int numsSize, int target, int* cache){
    if (target == 0) return 1;
    if (cache[target] != -1) {
        // 由于会把计算过的taret缓存，所以递归最多不会超过target次(有些target可能不用计算，所以有少于target次的可能)
        return cache[target];
    }
    
    int count = 0;
    for (int i = 0; i < numsSize; ++i) {
//        if (nums[i] > target) {
//            break;
//        }
        if (nums[i] <= target) {
            count += combinationSum4Helper(nums, numsSize, target-nums[i], cache);
        }
    }
    // 缓存各个target的组合数
    cache[target] = count;
    
    return count;
}

int combinationSum4(int* nums, int numsSize, int target){
    int cache[target+1];
    for (int i = 1; i <= target; ++i) {
        cache[i] = -1;
    }
    // nlog(n)
    //qsort(nums, numsSize, sizeof(int), compare);
    
    // target*n(最坏情况)
    return combinationSum4Helper(nums, numsSize, target, cache);
}

// 1011. 在 D 天内送达包裹的能力
int shipWithinDays(int* weights, int weightsSize, int D){
    // 题目的意思: 把数组按顺序分割成D组，让各组的合计值的最大值尽量小, 输出这个最小值
    // C(D, size)种分割方法
    // 暴力法，把所有可能的分割方法历遍(超时)
//    if (weightsSize == 0) {
//        return 0;
//    }
//    if (D == 1) {
//        int cost = 0;
//        for (int i = 0; i < weightsSize; ++i) {
//            cost += weights[i];
//        }
//        return cost;
//    }
//    int cost = 0;
//    int minMaxCost = 50000000;
//    for (int i = 0; i < weightsSize; ++i) {
//        cost += weights[i];
//        int maxCost = cost;
//        int nextCost = shipWithinDays(weights+i+1, weightsSize-i-1, D-1);
//        if (nextCost > maxCost) {
//            maxCost = nextCost;
//        }
//        if (minMaxCost > maxCost) {
//            minMaxCost = maxCost;
//        }
//    }
//    
//    return minMaxCost;

    // 二分
    int left = 0, right = 0;
    for (int i = 0; i < weightsSize; i++) {
        left = fmax(left, weights[i]);
        right += weights[i];
    }
    
    while (left < right) {
        int mid = (left + right) / 2;
        // need 为需要运送的天数
        // cur 为当前这一天已经运送的包裹重量之和
        int need = 1, cur = 0;
        for (int i = 0; i < weightsSize; i++) {
            if (cur + weights[i] > mid) {
                ++need;
                cur = 0;
            }
            cur += weights[i];
        }
        if (need <= D) {
            // 需要日数少于D, 可以降低运输能力
            right = mid;
        } else {
            // 需要日数大于D, 要增加运输能力
            left = mid + 1;
        }
    }
    return left;

}

//bool canCrossHelper(int* stones, int stonesSize, int jump, int now){
//    if (stonesSize == 0) return true;
//    //[1,2,2,1,2,4,5]
//    //[1,1,1,1,4,1,2]
//    //
//    int i = 0;
//    while (i < stonesSize) {
//        if (stones[i] > jump+1+now) {
//            return false;
//        }
//        for (int j = jump+1; j >= jump-1; --j) {
//            if (stones[i] == j+now) {
//                bool flag = canCrossHelper(stones+i+1, stonesSize-i-1, j, stones[i]);
//                if (flag == true) {
//                    return true;
//                }
//            }
//        }
//        ++i;
//    }
//    return false;
//}

// 403. 青蛙过河
bool canCross(int* stones, int stonesSize){
    // 动态规划(O(n^2))
    int dp[stonesSize][stonesSize];
    memset(dp, 0, sizeof(dp));
    dp[0][0] = true;
    // 0 1 3 6 10 15
    for (int i = 1; i < stonesSize; ++i) {
        if (stones[i] - stones[i - 1] > i) {
            return false;
        }
    }
    for (int i = 1; i < stonesSize; ++i) {
        for (int j = i - 1; j >= 0; --j) {
            int k = stones[i] - stones[j];
            if (k > j + 1) {
                break;
            }
            dp[i][k] = dp[j][k - 1] || dp[j][k] || dp[j][k + 1];
            if (i == stonesSize - 1 && dp[i][k]) {
                return true;
            }
        }
    }
    return false;
    
//    // 暴力递归(超时，指数级复杂度)
//    if (stones[1] != 1) return false;
//    int jump = 1;
//    return canCrossHelper(stones+2, stonesSize-2, jump, 1);
}

// 368. 最大整除子集
int* largestDivisibleSubset(int* nums, int numsSize, int* returnSize){
    int len = numsSize;
    qsort(nums, numsSize, sizeof(int), compare);
    
    
    // 第 1 步：动态规划找出最大子集的个数、最大子集中的最大整数
    int dp[len];
    for (int i = 0; i < len; i++) {
        dp[i] = 1;
    }
    int maxSize = 1;
    int maxVal = dp[0];
    for (int i = 1; i < len; i++) {
        for (int j = 0; j < i; j++) {
            // 题目中说「没有重复元素」很重要
            if (nums[i] % nums[j] == 0) {
                dp[i] = fmax(dp[i], dp[j] + 1);
            }
        }

        if (dp[i] > maxSize) {
            maxSize = dp[i];
            maxVal = nums[i];
        }
    }

    // 第 2 步：倒推获得最大子集
    int* res = malloc(sizeof(int) * len);
    *returnSize = 0;
    if (maxSize == 1) {
        res[(*returnSize)++] = nums[0];
        return res;
    }

    for (int i = len - 1; i >= 0 && maxSize > 0; i--) {
        if (dp[i] == maxSize && maxVal % nums[i] == 0) {
            res[(*returnSize)++] = nums[i];
            maxVal = nums[i];
            maxSize--;
        }
    }
    return res;

}

// 363. 矩形区域不超过 K 的最大数值和
int maxSumSubmatrix(int** matrix, int matrixSize, int* matrixColSize, int k){
    // 共m^2*n^2种组合，暴力法就是m^2*n^2的复杂度
    int cSize = matrixColSize[0];
    int rSize = matrixSize;
    
    int result = -1000000;
    
    int csizes[rSize][cSize];
    // csizes[r][m][n] = csizes[r][n]-csizes[r][m-1]
    for (int i = 0; i < rSize; ++i) {
        csizes[i][0] = matrix[i][0];
        for (int j = 1; j < cSize; ++j) {
            csizes[i][j] = csizes[i][j-1]+matrix[i][j];
        }
    }
    
    for (int c1 = 0; c1 < cSize; ++c1) {
        for (int c2 = c1; c2 < cSize; ++c2) {
            for (int r1 = 0; r1 < rSize; ++r1) {
                int tmp = 0;
                for (int r2 = r1; r2 < rSize; ++r2) {
                    tmp += csizes[r2][c2];
                    if (c1 > 0) tmp -= csizes[r2][c1-1];
                    if (tmp == k) return k;
                    if (tmp < k && tmp > result) result = tmp;
                    
                }
            }
        }
    }
    
    return result;
}

// 91. 解码方法
int numDecodingsHelper(char * s, int index, int *table){
    if (s[index] == '0') return 0;
    if (s[index] == 0) return 1;
    if (table[index] != -1) return table[index];
    
    int count = numDecodingsHelper(s, index+1, table);
    if (s[index+1] != 0 && (s[index] == '1' || (s[index] == '2' && s[index+1] < '7'))) {
        count += numDecodingsHelper(s, index+2, table);
    }
    table[index] = count;
    
    return count;
}

int numDecodings(char * s){
    int length = strlen(s);
    int *table = malloc(sizeof(int)*length);
    for (int i = 0; i < length; ++i) {
        table[i] = -1;
    }
    int result = numDecodingsHelper(s, 0, table);
    free(table);
    return result;
    
    // s[i] = s[i-1]+s[i-2]
}

// 1486. 数组异或操作
// 模拟O(n)
//int xorOperation(int n, int start){
//    int result = 0;
//    for (int i = 0; i < n; ++i) {
//        result = result^(start+2*i);
//    }
//    return result;
//}
// 数学O(1)
int sumXor(int x) {
    if (x % 4 == 0) {
        return x;
    }
    if (x % 4 == 1) {
        return 1;
    }
    if (x % 4 == 2) {
        return x + 1;
    }
    return 0;
}

int xorOperation(int n, int start) {
    //4i⊕(4i+1)⊕(4i+2)⊕(4i+3)=0
    // 2*i+start
    
    int s = start >> 1, e = n & start & 1;
    int ret = sumXor(s - 1) ^ sumXor(s + n - 1);
    return ret << 1 | e;
}

// 1720. 解码异或后的数组
int* decode(int* encoded, int encodedSize, int first, int* returnSize){
    
    *returnSize = encodedSize+1;
    
    int *result = malloc(sizeof(int)*(encodedSize+1));
    // result[i]^result[i+1] = encoded[i]
    result[0] = first;
    for (int i = 1; i < *returnSize; ++i) {
        result[i] = encoded[i-1]^result[i-1];
    }
    
    return result;
}

// 740. 删除并获得点数
int deleteAndEarn(int* nums, int numsSize){
    qsort(nums, numsSize, sizeof(*nums), compare);
    /*
    f(4) = max(f(2), f(1))
    f(3) = max(f(1), f(0))
    f(n) = max(f(n-2), f(n-3))
     */
     
    int maxValue = nums[numsSize-1];
    int f[maxValue+1];
    memset(f, 0, sizeof(int)*(maxValue+1)); 
    int lastValue = nums[0];
    int i = 0;
    while (i < numsSize) {
        if (nums[i] == lastValue) {
            f[nums[i]] += nums[i];
            ++i;
        }else if (nums[i] == lastValue+1){
            if (nums[i] > 2) {
                f[nums[i]] = fmax(f[nums[i]-2], f[nums[i]-3]);
            }
            lastValue = nums[i];
        }else{
            f[nums[i]] = fmax(f[lastValue], f[lastValue-1]);
            if (nums[i] == lastValue+2 && lastValue > 2) {
                f[lastValue+1] = fmax(f[lastValue-1], f[lastValue-2]);
            }else{
                f[nums[i]-1] = f[nums[i]]; 
            }
            
            lastValue = nums[i];
        }
    }
    return fmax(f[maxValue], f[maxValue-1]);
}

// 1723. 完成所有工作的最短时间
bool backtrack(int* jobs, int jobsSize, int* workloads, int workloadsSize, int idx, int limit) {
    if (idx >= jobsSize) {
        return true;
    }
    int cur = jobs[idx];
    for (int i = 0; i < workloadsSize; i++) {
        if (workloads[i] + cur <= limit) {
            workloads[i] += cur;
            if (backtrack(jobs, jobsSize, workloads, workloadsSize, idx + 1, limit)) {
                return true;
            }
            workloads[i] -= cur;
        }
        // 如果当前工人未被分配工作，那么下一个工人也必然未被分配工作
        // 或者当前工作恰能使该工人的工作量达到了上限
        // 这两种情况下我们无需尝试继续分配工作
        if (workloads[i] == 0 || workloads[i] + cur == limit) {
            break;
        }
    }
    return false;
}

bool check(int* jobs, int jobsSize, int k, int limit) {
    int workloads[k];
    memset(workloads, 0, sizeof(workloads));
    return backtrack(jobs, jobsSize, workloads, k, 0, limit);
}

int cmp(int* a, int* b) {
    return *b - *a;
}

int accumulate(int* arr, int* arrSize) {
    int ret = 0;
    for (int i = 0; i < arrSize; i++) {
        ret += arr[i];
    }
    return ret;
}

int minimumTimeRequired(int* jobs, int jobsSize, int k) {
    qsort(jobs, jobsSize, sizeof(int), cmp);
    int l = jobs[0], r = accumulate(jobs, jobsSize);
    while (l < r) {
        int mid = (l + r) >> 1;
        if (check(jobs, jobsSize, k, mid)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    return l;
}

int leastBricks(int** wall, int wallSize, int* wallColSize){
    /*
    -- ---- ---- --
    ------ -- ---- 
    -- ------ ---- 
    -- ----  
     */
    return 0;
}

// 1482. 制作 m 束花所需的最少天数
// 递归历遍 超时
//int minDaysHelper(int* bloomDay, int bloomDaySize, int m, int k, int offset, int *maxDayTable) {
//    if (m == 0) return 0;
//    if (bloomDaySize-offset < m*k) return -1;
//    
//    int minDay = 1000000000;
//    for (int i = k+offset; i <= bloomDaySize; ++i) {
//        int day = maxDayTable[i-k];
//        int nextDay = minDaysHelper(bloomDay, bloomDaySize, m-1, k, i, maxDayTable);
//        if (nextDay == -1) break;
//        
//        day = fmax(day, nextDay);
//        if (minDay > day) minDay = day;
//    }
//    
//    return minDay;
//}
//
//int minDays(int* bloomDay, int bloomDaySize, int m, int k){
//    if (bloomDaySize < m*k) return -1;
//    
//    int maxDayTable[bloomDaySize];
//    memset(maxDayTable, 0, sizeof(int)*bloomDaySize);
//    for (int i = k; i <= bloomDaySize; ++i) {
//        int day = 0;
//        if (i > k && maxDayTable[i-k-1] <= bloomDay[i-1]) {
//            maxDayTable[i-k] = bloomDay[i-1];
//        }else{
//            for (int j = i-k; j < i; ++j) {
//                if (bloomDay[j] > day) {
//                    day = bloomDay[j];
//                }
//            }
//            maxDayTable[i-k] = day;
//        }
//    }
//    return minDaysHelper(bloomDay, bloomDaySize, m, k, 0, maxDayTable);
//}

// 二分
bool canMake(int* bloomDay, int bloomDaySize, int days, int m, int k) {
    int bouquets = 0;
    int flowers = 0;
    int length = bloomDaySize;
    for (int i = 0; i < length && bouquets < m; i++) {
        if (bloomDay[i] <= days) {
            flowers++;
            if (flowers == k) {
                bouquets++;
                flowers = 0;
            }
        } else {
            flowers = 0;
        }
    }
    return bouquets >= m;
}

int minDays(int* bloomDay, int bloomDaySize, int m, int k) {
    if (m > bloomDaySize / k) {
        return -1;
    }
    int low = INT_MAX, high = 0;
    for (int i = 0; i < bloomDaySize; i++) {
        low = fmin(low, bloomDay[i]);
        high = fmax(high, bloomDay[i]);
    }
    while (low < high) {
        int days = (high - low) / 2 + low;
        if (canMake(bloomDay, bloomDaySize, days, m, k)) {
            high = days;
        } else {
            low = days + 1;
        }
    }
    return low;
}


// 1310. 子数组异或查询
int* xorQueries(int* arr, int arrSize, int** queries, int queriesSize, int* queriesColSize, int* returnSize){
//    int *result = malloc(sizeof(int)*queriesSize);
//    memset(result, 0, sizeof(int)*queriesSize);
//    *returnSize = queriesSize;
//    // 模拟(超时)
//    for (int i = 0; i < queriesSize; ++i) {
//        for (int j = queries[i][0]; j <= queries[i][1]; ++j) {
//            result[i] ^= arr[j];
//        }
//    }
//    return result;
    /*
    l<r, 
    q(l, r) = q(l, r-1)^arr(r)
     */
    int n = arrSize;
    int xors[n + 1];
    xors[0] = 0;
    for (int i = 0; i < n; i++) {
        xors[i + 1] = xors[i] ^ arr[i];
    }
    int m = queriesSize;
    int* ans = malloc(sizeof(int) * m);
    *returnSize = m;
    for (int i = 0; i < m; i++) {
        ans[i] = xors[queries[i][0]] ^ xors[queries[i][1] + 1];
    }
    return ans;

}

// 1738. 找出第 K 大的异或坐标值
int Partition(int* arr,int low ,int high)
{
    int temp = arr[low];
    while(low < high)
    {
        while(low < high && arr[high] >= temp)
            high--;
        arr[low] = arr[high];
        while(low < high && arr[low] <= temp)
            low++;
        arr[high] = arr[low];
    }
    arr[low] = temp;//确定参考元素的位置
    return low;
}

int KthElement(int * arr,int low, int high,int n ,int k)
{
    if(low >= high)//边界条件和特殊输入的处理
        return arr[high];
    int pos = Partition(arr,low,high);
    while(pos != n - k)
    {
        if(pos > n - k)
        {
            high = pos - 1;
            pos = Partition(arr,low,high);
        }else{
            low = pos + 1;
            pos = Partition(arr,low,high);
        }
    }
    return arr[pos];
 
}

int kthLargestValue(int** matrix, int matrixSize, int* matrixColSize, int k){
    // f(i,j) = f(i-1,j)^f(i,j-1)^f(i-1,j-1)^m(i,j)
    int r = matrixSize;
    int c = matrixColSize[0];
    int *numArr = malloc(sizeof(int)*r*c);
    int index = 0;
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (i > 0 && j > 0) {
                matrix[i][j] = matrix[i-1][j]^matrix[i][j-1]^matrix[i-1][j-1]^matrix[i][j];
            }else if (i > 0) {
                matrix[i][j] = matrix[i-1][j]^matrix[i][j];
            }else if (j > 0){
                matrix[i][j] = matrix[i][j-1]^matrix[i][j];
            }
            numArr[index++] = matrix[i][j];
        }
    }
    
    int result = KthElement(numArr, 0, index-1, index, k);
    free(numArr);
    
    return result;
}


//int cmp(int* a, int* b) {
//    return *b - *a;
//}
//
//int kthLargestValue(int** matrix, int matrixSize, int* matrixColSize, int k) {
//    int m = matrixSize, n = matrixColSize[0];
//    int pre[m + 1][n + 1];
//    memset(pre, 0, sizeof(pre));
//    int results[m * n], resultsSize = 0;
//    for (int i = 1; i <= m; ++i) {
//        for (int j = 1; j <= n; ++j) {
//            pre[i][j] = pre[i - 1][j] ^ pre[i][j - 1] ^ pre[i - 1][j - 1] ^ matrix[i - 1][j - 1];
//            results[resultsSize++] = pre[i][j];
//        }
//    }
//
//    qsort(results, resultsSize, sizeof(int), cmp);
//    return results[k - 1];
//}

// 1442. 形成两个异或相等数组的三元组数目
int countTriplets(int* arr, int arrSize){
    // f(j-1)^f(i-1) == f(k)^f(j-1) i<j<=k
    // f(i-1) == f(k) k-i个
    for (int i = 1; i < arrSize; ++i) {
        arr[i] ^= arr[i-1];
    }
    int result = 0;
    for (int k = 1; k < arrSize; ++k) {
        if (arr[k] == 0) {
            result += k;
        }
    }
    for (int i = 1; i < arrSize; ++i) {
        for (int k = i+1; k < arrSize; ++k) {
            if (arr[i-1] == arr[k]) {
                result += k-i;
            }
        }
    }
    return result;
}

// 1035. 不相交的线
int maxUncrossedLines(int* nums1, int nums1Size, int* nums2, int nums2Size){
    
    int m = nums1Size, n = nums2Size;
    int dp[m + 1][n + 1];
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= m; i++) {
        int num1 = nums1[i - 1];
        for (int j = 1; j <= n; j++) {
            int num2 = nums2[j - 1];
            if (num1 == num2) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = fmax(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[m][n];
}

// 664. 奇怪的打印机
int strangePrinter(char * s){
    // abcdefabcdef
    
    int n = strlen(s);
    int f[n][n];
    for (int i = n - 1; i >= 0; i--) {
        f[i][i] = 1;
        for (int j = i + 1; j < n; j++) {
            if (s[i] == s[j]) {
                f[i][j] = f[i][j - 1];
            } else {
                int minn = n;
                for (int k = i; k < j; k++) {
                    minn = fmin(minn, f[i][k] + f[k + 1][j]);
                }
                f[i][j] = minn;
            }
        }
    }
    return f[0][n - 1];

}

// 525. 连续数组
int findMaxLength(int* nums, int numsSize){
    /*
    0 <= i < j < n
    f[i][i] = 0
    f[i][j] = f[i][j-1]
    
     */
    int result = 0;
    // 暴力法O(n^2)
//    for (int i = 0; i < numsSize; ++i) {
//    
//        int count0 = 0;
//        int count1 = 0;
//        if (nums[i] == 0) {
//            ++count0;
//        }else{
//            ++count1;
//        }
//        for (int j = i+1; j < numsSize; ++j) {
//            if (nums[j] == 0) {
//                ++count0;
//            }else{
//                ++count1;
//            }
//            if (count0 == count1 && count0 > result) {
//                result = count0;
//            }
//        }
//    }

    /*
    11110000111100001111
    
     */
    // hash表记录前序O(n), O(n)
    int tableSize = numsSize*2+1;
    int table[tableSize];
    for (int i = 0; i < tableSize; ++i) {
        table[i] = -2;
    }
    int count = numsSize;
    table[numsSize] = -1;
    
    int addNum[2] = {-1, 1};
    for (int i = 0; i < numsSize; ++i) {
        count += addNum[nums[i]];
        if (table[count] != -2) {
            result = fmax(result, i-table[count]);
        }else{
            table[count] = i;
        }
    }

    return result;
}

bool* canEat(int* candiesCount, int candiesCountSize, int** queries, int queriesSize, int* queriesColSize, int* returnSize){
    bool* result = malloc(sizeof(bool)*queriesSize);
    *returnSize = queriesSize;
    
    long canSumCount[candiesCountSize+1];
    canSumCount[0] = 0;
    for (int i = 1; i <= candiesCountSize; ++i) {
        canSumCount[i] = canSumCount[i-1]+candiesCount[i-1];
    }
    
    for (int i = 0; i < queriesSize; ++i) {
        int type = queries[i][0];
        int day = queries[i][1];
        int dayCap = queries[i][2];
        
        long canCount = canSumCount[type];
        // day日内最多可以吃的糖果
        long maxCap = (long)dayCap*(day+1);
        // day日内最少吃day+1颗糖果
        // 需要在day日内吃掉所有type前的糖果, 且day日前不能吃光所有type的糖果(每天吃1颗的情况下，不会吃光)
        result[i] = (maxCap > canCount && day < canSumCount[type+1]);
    }
    
    return result;
}

// 523. 连续的子数组和
bool checkSubarraySum(int* nums, int numsSize, int k){
    // k值很大，不能用数组代替
    int hash[k];
    
    for (int i = 0; i < k; ++i) {
        hash[i] = -2;
    }
    hash[0] = -1;
    long sum = 0;
    for (int i = 0; i < numsSize; ++i) {
        sum += nums[i];
        int num = sum%k;
        if (hash[num] != -2 && i-hash[num] > 1){
            return true;
        }else if (hash[num] == -2) {
            hash[num] = i;
        }
    }
    
    return false;
}

// 1711. 大餐计数
struct HashTable {
    int key, val;
    UT_hash_handle hh;
};

const int MOD = 1000000007;
//用哈希表做，以deliciousness的值为key，每个值出现的次数为value
int countPairs(int* deliciousness, int deliciousnessSize) {
    int maxVal = 0;
    for (int i = 0; i < deliciousnessSize; i++) {
        maxVal = fmax(maxVal, deliciousness[i]);
    }
    int maxSum = maxVal * 2;
    int pairs = 0;
    struct HashTable *hashTable = NULL, *tmp;
    int n = deliciousnessSize;
    for (int i = 0; i < deliciousnessSize; i++) {
        int val = deliciousness[i];
        for (int sum = 1; sum <= maxSum; sum <<= 1) {
            int target = sum - val;
            HASH_FIND_INT(hashTable, &target, tmp);
            int count = tmp == NULL ? 0 : tmp->val;
            pairs = (pairs + count) % MOD;
        }
        HASH_FIND_INT(hashTable, &val, tmp);
        if (tmp == NULL) {
            tmp = malloc(sizeof(struct HashTable));
            tmp->key = val, tmp->val = 1;
            HASH_ADD_INT(hashTable, key, tmp);
        } else {
            tmp->val++;
        }
    }
    return pairs;
}

//bool searchIsIn(long value, long *list, int left, int right) {
//    while (left <= right) {
//        int center = (left+right)/2;
//        if (list[center] == value) {
//            return true;
//        }else if (list[center] > value) {
//            right = center-1;
//        }else{
//            left = center+1;
//        }
//    }
//    return false;
//}
//
//int countPairs(int* deliciousness, int deliciousnessSize){
//    
//
//    /*
//    
//    O(n^2)，会超时
//    1 <= deliciousness.length <= 10的5次方
//    0 <= deliciousness[i] <= 2的20次方
//    
//    那么最大合计值为2的21次方，符合的值实际只用22种
//     */
//    long answerList[22] = {0};
//    long answer = 1;
//    answerList[0] = answer;
//    for (int i = 1; i < 22; ++i) {
//        answer *= 2;
//        answerList[i] = answer;
//    } 
//    long count = 0;
//    for (int i = 0; i < deliciousnessSize; ++i) {
//        for (int j = i+1; j < deliciousnessSize; ++j) {
//            long value = deliciousness[i]+deliciousness[j];
//            if (value != 1 && value%2 == 1) {
//                continue;
//            }
//            if (searchIsIn(value, answerList, 0, 21)) {
//                ++count;
//            }
//        }
//    }
//    return count%1000000007;
//}

void findNode(struct TreeNode* root, struct TreeNode* target, struct TreeNode** parentTable) {
    if (root->left != NULL) {
        parentTable[root->left->val] = root;
        if (root->left == target) {
            return;
        }
        findNode(root->left, target, parentTable);
    }
    if (root->right != NULL) {
        parentTable[root->right->val] = root;
        if (root->right == target) {
            return;
        }
        findNode(root->right, target, parentTable);
    }
    
}

void distanceKHelper(struct TreeNode* root, struct TreeNode* preTarget, int k, int distance, int* result, int* returnSize) {
    if (root == preTarget || root == NULL) {
        return;
    }
    
    if (distance == k) {
        result[*returnSize] = root->val;
        (*returnSize) += 1;
    }else{
        distanceKHelper(root->left, preTarget, k, distance+1, result, returnSize);
        distanceKHelper(root->right, preTarget, k, distance+1, result, returnSize);
    }
    
}

int* distanceK(struct TreeNode* root, struct TreeNode* target, int k, int* returnSize) {
    
    struct TreeNode* parentTable[501] = {0};
    findNode(root, target, parentTable);
    
    struct TreeNode* preTarget = NULL;
    struct TreeNode* curTarget = target;
    
    int* result = malloc(sizeof(int)*501);
    *returnSize = 0;
    
    int distance = 0;
    
    while (distance <= k && curTarget != 0) {
        distanceKHelper(curTarget, preTarget, k, distance, result, returnSize);
        preTarget = curTarget;
        curTarget = parentTable[curTarget->val];
        distance += 1;
    }
    
    return result;
}

int findInsertIndex(int value, int *nums, int length) {
    int left = 0;
    int right = length-1;
    while (left < right) {
        int mid = (left+right)/2;
        if (nums[mid] < value) {
            left = mid+1;
        }else{
            right = mid-1;
        }
    }
    if (nums[left] < value) {
        return left+1;
    }else{
        return left;
    }
}


int lengthOfLIS(int* nums, int numsSize){
    int dArray[numsSize];
    int length = 0;
    if (numsSize > 0) {
        dArray[0] = nums[0];
        length = 1;
    }
    
    for (int i = 1; i < numsSize; ++i) {
        if (nums[i] > dArray[length-1]) {
            dArray[length++] = nums[i];
        }else{
            dArray[findInsertIndex(nums[i], dArray, length)] = nums[i];
        }
    }
    return length;
}


char * maximumTime(char * time){
    char * result = malloc(sizeof(char)*6);
    result[5] = '\0';
    result[2] = ':';
    
    if (time[0] != '?') {
        result[0] = time[0];
        if (time[1] == '?') {
            result[1] = (time[0] != '2')?'9':'3';
        }else{
            result[1] = time[1];
        }
    }else{
        if (time[1] == '?') {
            result[0] = '2';
            result[1] = '3';
        }else{
            result[1] = time[1];
            result[0] = (time[1] < '4')?'2':'1';
        }
    }
    
    result[3] = (time[3] != '?')?time[3]:'5';
    result[4] = (time[4] == '?')?time[4]:'9';
    
    return result;
}

bool isCovered(int** ranges, int rangesSize, int* rangesColSize, int left, int right){
    
    for (int i = left; i <= right; ++i) {
        int j = 0;
        while (ranges[j][0] > i || i > ranges[j][1]) {
            // 不在范围，找下一个
            ++j;
            if (j == rangesSize) {
                return false;
            }
        }
    }
    
    return true;
}

struct ListNode** splitListToParts(struct ListNode* head, int k, int* returnSize){
    
    struct ListNode** result = malloc(sizeof(struct ListNode)*k);
    int count = 0;
    struct ListNode* tmp = head;
    while (tmp) {
        tmp = tmp->next;
        count += 1;
    }
    int aveNum = count/k;
    int leftCount = count%k;
    
    *returnSize = 0;
    
    tmp = head;
    while (tmp) {
        result[*returnSize] = tmp;
        (*returnSize) += 1;
        int i = 0;
        int targetNum = aveNum-1;
        if (leftCount > 0) {
            leftCount -= 1;
            targetNum += 1;
        }
        while (i < targetNum) {
            tmp = tmp->next;
            i += 1;
        }
        struct ListNode* nextNode = tmp->next;
        tmp->next = NULL;
        tmp = nextNode;
    }
    
    while ((*returnSize) < k) {
        result[(*returnSize)] = NULL;
        (*returnSize) += 1;
    }
    
    return result;
}

// 583. 两个字符串的删除操作
int minDistance(char * word1, char * word2){
    int len1 = strlen(word1);
    int len2 = strlen(word2);
    
    int dp[len1+1][len2+1];
    dp[0][0] = 0;
    for (int i = 1; i <= len1; ++i) {
        dp[i][0] = 0;
    }
    for (int i = 1; i <= len2; ++i) {
        dp[0][i] = 0;
    }
    for (int i = 1; i <= len1; ++i) {
        char c1 = word1[i-1];
        for (int j = 1; j <= len2; ++j) {
            char c2 = word2[j-1];
            if (c1 == c2) {
                dp[i][j] = dp[i-1][j-1]+1;
            } else {
                dp[i][j] = fmax(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    return len1+len2-dp[len1][len2]*2;
}

// 58. 最后一个单词的长度
int lengthOfLastWord(char * s){
    int count = s[0]==' '?0:1;
    int i = 1;
    while (s[i]) {
        if (s[i] != ' ') {
            if (s[i-1] == ' ') {
                count = 1;
            } else {
                ++count;
            }
        }
        ++i;
    }
    return count;
}

// 673. 最长递增子序列的个数
int findNumberOfLIS(int* nums, int numsSize){
    
    
    return 0;
}

typedef struct WordDictionary {
    struct WordDictionary *wordList[26];
    bool isEnd;
} WordDictionary;

WordDictionary* wordDictionaryCreate() {
    WordDictionary *obj = malloc(sizeof(WordDictionary));
    obj->isEnd = false;
    for (int i = 0; i < 26; ++i) {
        obj->wordList[i] = NULL;
    }
    return obj;
}

void wordDictionaryAddWord(WordDictionary* obj, char * word) {
    if (*word == 0) {
        obj->isEnd = true;
        return;
    }
    int index = (*word)-'a';
    if (obj->wordList[index] == NULL) {
        obj->wordList[index] = wordDictionaryCreate();
    }
    wordDictionaryAddWord(obj->wordList[index], word+1);
}

bool wordDictionarySearch(WordDictionary* obj, char * word) {
    if (*word == '\0') return obj->isEnd;
    if (*word == '.') {
        for (int i = 0; i < 26; ++i) {
            if (obj->wordList[i] != NULL && wordDictionarySearch(obj->wordList[i], word+1)) {
                return true;
            }
        }
        return false;
    } else {
        int index = (*word)-'a';
        if (obj->wordList[index] == NULL) {
            return false;
        } else {
            return wordDictionarySearch(obj->wordList[index], word+1);
        }
    }
}

void wordDictionaryFree(WordDictionary* obj) {
    for (int i = 0; i < 26; ++i) {
        if (obj->wordList[i] != NULL) {
            wordDictionaryFree(obj->wordList[i]);
        }
    }
    free(obj);
}

//char ** removeInvalidParentheses(char * s, int* returnSize){
//    
//    int i = 0;
//    int leftCount = 0;
//    int rightCount = 0;
//    
//    int maxLength = strlen(s)+1;
//    
//    int resultCount = 0;
//    
//    char **resultArray = malloc(sizeof(char*)*100);
//    
//    while (s[i] != 0) {
//        if (s[i] == '(') {
//            leftCount += 1;
//        } else if (s[i] == ')') {
//            rightCount += 1;
//        }
//        if (rightCount > leftCount) {
//            break;
//        }
//        ++i;
//    }
//    
//    if (leftCount > rightCount) {
//        // 从右计算
//        --i;
//        leftCount = 0;
//        rightCount = 0;
//        while (i >= 0) {
//            if (s[i] == '(') {
//                leftCount += 1;
//            } else if (s[i] == ')') {
//                rightCount += 1;
//            }
//            if (leftCount > rightCount) {
//                break;
//            }
//            --i;
//        }
//        // 中途左括号过多, 分割左右两段处理
//        char *leftString = malloc(sizeof(char)*(i+1));
//        memcpy(leftString, s, sizeof(char)*i);
//        leftString[i] = '\0';
//        
//        char ** nextArray = removeInvalidParentheses(leftString, returnSize);
//        int j = i;
//        int lastLeftIndex = i;
//        while (j < maxLength-1) {
//            if (s[j] != '(') {
//                char *rightString = malloc(sizeof(char)*(maxLength-j));
//                int k = i;
//                int index = 0;
//                while (k < maxLength-1) {
//                    if (k != lastLeftIndex) {
//                        rightString[index++] = s[k];
//                    }
//                    ++k;
//                }
//                rightString[index] = '\0';
//                
//                for (int l = 0; l < *returnSize; ++l) {
//                    char *lString = nextArray[l];
//                    char *resultString = malloc(sizeof(char)*maxLength);
//                    int leftLen = strlen(lString);
//                    strcpy(resultString, lString);
//                    strcpy(resultString+leftLen, rightString);
//                    resultArray[resultCount++] = resultString;
//                }
//            } else {
//                lastLeftIndex = j;
//            }
//            ++j;
//        }
//        
//    } else if (rightCount > leftCount) {
//        // 中途右括号过多，分割左右两段处理
//        char ** nextArray = removeInvalidParentheses(s+i+1, returnSize);
//        int j = i;
//        int lastRightIndex = i;
//        while (j >= 0) {
//            if (s[j] != ')') {
//                char *leftString = malloc(sizeof(char)*i);
//                int k = 0;
//                int index = 0;
//                while (k <= i) {
//                    if (k != lastRightIndex) {
//                        leftString[index++] = s[k];
//                    }
//                    ++k;
//                }
//                leftString[index] = '\0';
//                for (int l = 0; l < *returnSize; ++l) {
//                    char *nextS = nextArray[l];
//                    char *resultString = malloc(sizeof(char)*maxLength);
//                    strcpy(resultString, leftString);
//                    strcpy(resultString+index, nextS);
//                    resultArray[resultCount++] = resultString;
//                }
//            } else {
//                lastRightIndex = j;
//            }
//            --j;
//        }
//    } else {
//        // 括号都有效，无需删除
//        char *resultString = malloc(sizeof(char)*maxLength);
//        strcpy(resultString, s);
//        resultArray[resultCount++] = resultString;
//    }
//    
//    *returnSize = resultCount;
//    return resultArray;
//}

/// 335. 路径交叉
bool isSelfCrossing(int* distance, int distanceSize){
    int n = distanceSize;
    for (int i = 3; i < n; ++i) {
        // 第 1 类路径交叉的情况
        if (distance[i] >= distance[i - 2] && distance[i - 1] <= distance[i - 3]) {
            return true;
        }
        
        // 第 2 类路径交叉的情况
        if (i == 4 && (distance[3] == distance[1]
                       && distance[4] >= distance[2] - distance[0])) {
            return true;
        }
        
        // 第 3 类路径交叉的情况
        if (i >= 5 && (distance[i - 3] - distance[i - 5] <= distance[i - 1]
                       && distance[i - 1] <= distance[i - 3]
                       && distance[i] >= distance[i - 2] - distance[i - 4]
                       && distance[i - 2] > distance[i - 4])) {
            return true;
        }
    }
    
    return false;
}

/// 869. 重新排序得到 2 的幂
bool reorderedPowerOf2(int n){
    /*
     1 2 4 6 8 
     16 32 64
     128 256 512
     1024 2048 4096 8192
     
     
     */
    
    // 
}

struct AlphabetTree {
    int count;
    int level;
    char c;
    struct AlphabetTree *parentTree; 
    struct AlphabetTree *nextTrees[26];
};

struct AlphabetTree * createAlphabetTree(char c) {
    struct AlphabetTree *tree = malloc(sizeof(struct AlphabetTree));
    tree->count = 0;
    tree->level = 0;
    tree->c = c;
    tree->parentTree = NULL;
    for (int i = 0; i < 26; ++i) {
        tree->nextTrees[i] = NULL;
    }
    return tree;
}

// 1044. 最长重复子串
char * longestDupSubstring(char * s){
    // 用字母树
    int length = strlen(s);
    
    struct AlphabetTree *trees[26];
    for (int i = 0; i < 26; ++i) {
        trees[i] = NULL;
    }
    
    struct AlphabetTree *resultTree = NULL;
    
    for (int i = 0; i < length; ++i) {
        struct AlphabetTree *curTree = trees[s[i]-'a'];
        if (curTree == NULL) {
            curTree = createAlphabetTree(s[i]);
            trees[s[i]-'a'] = curTree;
        }
        curTree->count += 1;
        if (curTree->count > 2) {
            if (resultTree == NULL) {
                resultTree = curTree;
            } else if (curTree->level > resultTree->level) {
                resultTree = curTree;
            }
        }
        for (int j = i+1; j < length; ++j) {
            int index = s[j]-'a';
            struct AlphabetTree *nextTree = curTree->nextTrees[index];
            if (nextTree == NULL) {
                nextTree = createAlphabetTree(s[j]);
                nextTree->parentTree = curTree;
                nextTree->level = curTree->level+1;
                curTree->nextTrees[index] = nextTree;
            }
            curTree = nextTree;
            curTree->count += 1;
            if (curTree->count > 2) {
                if (resultTree == NULL) {
                    resultTree = curTree;
                } else if (curTree->level > resultTree->level) {
                    resultTree = curTree;
                }
            }
        }
    }
    char *resultString;
    if (resultTree != NULL) {
        resultString = malloc(sizeof(char)*(resultTree->level+2));
        int index = resultTree->level;
        resultString[index+1] = '\0';
        while (resultTree) {
            resultString[index] = resultTree->c;
            index -= 1;
        }
        return resultString;
    } else {
        resultString = "";
    }
    // 要释放所有AlphabetTree
    
    return resultString;
}

// 539. 最小时间差
int findMinDifference(char ** timePoints, int timePointsSize){
    if (timePointsSize > 1440) {
        return 0;
    }
    int *timeMinutes = malloc(sizeof(int)*timePointsSize);
    for (int i = 0; i < timePointsSize; ++i) {
        int hour = (timePoints[i][0]-'0')*10+(timePoints[i][1]-'0');
        int minute = (timePoints[i][3]-'0')*10+(timePoints[i][4]-'0');
        int totalMinute = hour*60+minute;
        timeMinutes[i] = totalMinute;
    }
    // 排序
    qsort(timeMinutes, timePointsSize, sizeof(*timeMinutes), compare);
    int minMinute = 1440;
    for (int i = 1; i < timePointsSize; ++i) {
        int timeInter = timeMinutes[i]-timeMinutes[i-1];
        if (timeInter < minMinute) {
            minMinute = timeInter;
        }
    }
    int lastMinute = 1440+timeMinutes[0]-timeMinutes[timePointsSize-1];
    if (lastMinute < minMinute) {
        minMinute = lastMinute;
    }
    free(timeMinutes);
    return minMinute;
}
