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
