//
//  LeetCodeC3.c
//  CommonTool
//
//  Created by lizihong on 2022/8/2.
//  Copyright © 2022 AL. All rights reserved.
//

#include "LeetCodeC3.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>
// 二叉树
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};


// 链表节点
struct ListNode {
    int val;
    struct ListNode *next;
};

typedef struct {
    // 当前数量
    int count;
    // 最大数量
    int maxCount;
    int *list;
    int start;
    int end;
    
} MyCircularQueue;


MyCircularQueue* myCircularQueueCreate(int k) {
    MyCircularQueue *obj = malloc(sizeof(MyCircularQueue));
    obj->list = malloc(sizeof(int)*k);
    obj->start = -1;
    obj->end = -1;
    obj->count = 0;
    obj->maxCount = k;
    return obj;
}

bool myCircularQueueEnQueue(MyCircularQueue* obj, int value) {
    if (obj->maxCount <= obj->count) {
        // 超出队列
        return false;
    }
    
    int nextEnd = (obj->end+1)%obj->maxCount;
    if (obj->start == -1) {
        obj->start = 0;
    }
    obj->list[nextEnd] = value;
    obj->end = nextEnd;
    obj->count += 1;
    return true;
}

bool myCircularQueueDeQueue(MyCircularQueue* obj) {
    if (obj->count == 0) {
        return false;
    }
    int nextStart = (obj->start+1)%obj->maxCount;
    obj->start = nextStart;
    obj->count -= 1;
    if (obj->count == 0) {
        obj->start = -1;
        obj->end = -1;
    }
    return true;
}

int myCircularQueueFront(MyCircularQueue* obj) {
    if (obj->count == 0) {
        return -1;
    }
    return obj->list[obj->start];
}

int myCircularQueueRear(MyCircularQueue* obj) {
    if (obj->count == 0) {
        return -1;
    }
    return obj->list[obj->end];
}

bool myCircularQueueIsEmpty(MyCircularQueue* obj) {
    return obj->count == 0;
}

bool myCircularQueueIsFull(MyCircularQueue* obj) {
    return obj->count == obj->maxCount;
}

void myCircularQueueFree(MyCircularQueue* obj) {
    free(obj->list);
    free(obj);
}

char * generateTheString(int n){
    
    char *result = malloc(sizeof(int)*n+1);
    result[n] = '\0';
    for (int i = 0; i < n; ++i) {
        result[i] = 'a';
    }
    if (n%2 == 0) {
        result[n-1] = 'b';
    }
    
    return result;
}

char * orderlyQueue(char * s, int k){
    // acdb cbda cdab dabc abcd
    
}

// 从大到小排列
int compareDes(void* a, void* b) {
    return -*(int*) a + *(int*) b;
}

// 从小到大排列
int compareAes(void* a, void* b) {
    return *(int*) a - *(int*) b;
}

int* minSubsequence(int* nums, int numsSize, int* returnSize){
    qsort(nums, numsSize, sizeof(*nums), compareDes);
    
    int *result = malloc(sizeof(int)*numsSize);
    
    int total = 0;
    for (int i = 0; i < numsSize; ++i) {
        total += nums[i];
    }
    int target = total/2;
    int sum = 0;
    int index = 0;
    for (int i = 0; i < numsSize; ++i) {
        sum += nums[i];
        result[index++] = nums[i];
        if (sum > target) {
            break;
        }
    }
    *returnSize = index;
    return result;
}

/*
 分治
 把一个特殊字符串拆成n个的子特殊字符串，然后再排序成最大字典序拼在一起
 */
static inline int cmp(const void* pa, const void* pb) {
    return strcmp(*(char **)pb, *(char **)pa);
}

char *helper(char *s, int start, int end) {
    int len = end - start + 1;
    if (len <= 2) {
        char *ans = (char *)malloc(sizeof(char) * (len + 1));
        strncpy(ans, s + start, len);
        ans[len] = '\0';
        return ans;
    }
    int cnt = 0, left = start;
    char **subs = (char **)malloc(sizeof(char *) * len);
    int subsSize = 0;
    for (int i = start; i <= end; ++i) {
        if (s[i] == '1') {
            ++cnt;
        } else {
            --cnt;
            if (cnt == 0) {
                char *res = helper(s, left + 1, i - 1);
                subs[subsSize] = (char *)malloc(sizeof(char) * (strlen(res) + 3));
                sprintf(subs[subsSize], "%s%s%s", "1", res, "0");
                left = i + 1;
                subsSize++;
            }
        }
    }
    qsort(subs, subsSize, sizeof(char *), cmp);
    char *ans = (char *)malloc(sizeof(char) * (len + 1));
    int pos = 0;
    for (int i = 0; i < subsSize; i++) {
        pos += sprintf(ans + pos, "%s", subs[i]);
        free(subs[i]);
    }
    ans[pos] = '\0';
    return ans;
}

char * makeLargestSpecial(char * s) {
    int len = strlen(s);
    return helper(s, 0, len - 1);
}

char * solveEquation(char * equation){

    int i = 0;
    int curNum = 0;
    bool isRight = false;
    bool isMinus = false;
    bool isX = false;
    int xCount = 0;
    int numCount = 0;
    while (equation[i] != '\0') {
        if (equation[i] == '=' || equation[i] == '+' || equation[i] == '-') {
            if (isX) {
                if (isMinus^isRight) {
                    xCount -= curNum;
                } else {
                    xCount += curNum;
                }
            } else {
                if (isMinus^isRight) {
                    numCount -= curNum;
                } else {
                    numCount += curNum;
                }
            }
            if (equation[i] == '=') {
                isRight = true;
                isMinus = false;
            } else if (equation[i] == '+') {
                isMinus = false;
            } else if (equation[i] == '-') {
                isMinus = true;
            }
            curNum = 0;
            isX = false;
        } else if (equation[i] == 'x') {
            if ((i == 0) || (curNum == 0 && equation[i-1] != '0')) {
                curNum = 1;
            }
            isX = true;
        } else {
            curNum = 10*curNum+equation[i]-'0';
        }
        ++i;
    }
    if (isX) {
        if (isMinus^isRight) {
            xCount -= curNum;
        } else {
            xCount += curNum;
        }
    } else {
        if (isMinus^isRight) {
            numCount -= curNum;
        } else {
            numCount += curNum;
        }
    }
    if (xCount == 0 && numCount != 0) {
        return "No solution";
    } else if (xCount == 0 && numCount == 0) {
        return "Infinite solutions";
    } else {
        int xValue = -numCount/xCount;
        char *result = malloc(sizeof(char)*7);
        result[0] = 'x';
        result[1] = '=';
        int index = 2;
        if (xValue < 0) {
            result[index++] = '-';
            xValue = -xValue;
        }
        int x_100 = xValue/100;
        if (x_100 > 0) {
            result[index++] = '0'+x_100;
        }
        int x_10 = (xValue%100)/10;
        if (x_10 > 0 || x_100 > 0) {
            result[index++] = '0'+x_10;
        }
        int x_1 = xValue%10;
        result[index++] = '0'+x_1;
        
        
        result[index] = '\0';
        return result;
    }
    
}

char * reformat(char * s){
    int len = strlen(s);
    char *result = malloc(sizeof(char)*(len+1));
    result[len] = '\0';
    int i = 0;
    int l = 0;
    int r = len-1;
    while (s[i] != '\0') {
        if (s[i] >= '0' && s[i] <= '9') {
            result[r--] = s[i];
        } else {
            result[l++] = s[i];
        }
        ++i;
    }
    
    int numCount = len-l;
    if (numCount == l) {
        // 字母数字一样
        int j = 1;
        for(int i = len-2; i > r; i-=2) {
            char c = result[i];
            result[i] = result[j];
            result[j] = c;
            j += 2;
        }
    } else if (numCount == l+1) {
        // 数字多一个
        int j = 0;
        for(int i = len-2; i > r; i-=2) {
            char c = result[i];
            result[i] = result[j];
            result[j] = c;
            j += 2;
        }
    } else if (numCount+1 == l) {
        // 字母多一个
        int j = 1;
        for(int i = len-1; i > r; i-=2) {
            char c = result[i];
            result[i] = result[j];
            result[j] = c;
            j += 2;
        }
    } else {
        // 格式不合
        result[0] = '\0';
    }
    
    return result;
}

int** groupThePeople(int* groupSizes, int groupSizesSize, int* returnSize, int** returnColumnSizes){
    // 注: 用链表可以减少空间复杂度
    // 这里为了写得方便，用二维数组处理
    int **bucket = malloc(sizeof(int*)*(groupSizesSize+1));
    int *bucketNum = malloc(sizeof(int)*(groupSizesSize+1));
    memset(bucketNum, 0, sizeof(int)*(groupSizesSize+1));
    
    for (int i = 1; i <= groupSizesSize; ++i) {
        bucket[i] = malloc(sizeof(int)*groupSizesSize);
    }
    
    for (int i = 0; i < groupSizesSize; ++i) {
        int size = groupSizes[i];
        bucket[size][bucketNum[size]] = i;
        bucketNum[size] += 1;
    }
    
    int **result = malloc(sizeof(int*)*groupSizesSize);
    *returnColumnSizes = malloc(sizeof(int)*groupSizesSize);
    memset(*returnColumnSizes, 0, sizeof(int)*groupSizesSize);
    int resultCount = 0;
    int *array = NULL;
    for (int i = 1; i <= groupSizesSize; ++i) {
        for (int j = 0; j < bucketNum[i]; ++j) {
            if (array == NULL) {
                array = malloc(sizeof(int)*i);
            }
            array[(*returnColumnSizes)[resultCount]] = bucket[i][j];
            (*returnColumnSizes)[resultCount] += 1;
            if ((*returnColumnSizes)[resultCount] == i) {
                // 塞满一组
                result[resultCount++] = array;
                array = NULL;
            }
        }
    }
    *returnSize = resultCount;
    
    // free
    for (int i = 1; i <= groupSizesSize; ++i) {
        free(bucket[i]);
    }
    free(bucketNum);
    free(bucket);
    
    return result;
}

int maxEqualFreq(int* nums, int numsSize){
    
    // 统计每个数的数量
    int *numCounts = malloc(sizeof(int)*100001);
    memset(numCounts, 0, sizeof(int)*100001);
    // 统计各个数量的数量
    int *countCounts = malloc(sizeof(int)*100002);
    memset(countCounts, 0, sizeof(int)*100002);
    
    // 不同数字的量
    int diffNum = 0;
    int diffCount = 0;
    int maxLen = 0;
    
    for (int i = 0; i < numsSize; ++i) {
        
        if (numCounts[nums[i]] == 0) {
            diffNum += 1;
        }
        
        countCounts[numCounts[nums[i]]] -= 1;
        if (countCounts[numCounts[nums[i]]] == 0) {
            diffCount -= 1;
        }
        numCounts[nums[i]] += 1;
        
        countCounts[numCounts[nums[i]]] += 1;
        if (countCounts[numCounts[nums[i]]] == 1) {
            diffCount += 1;
        }
        if (diffNum == 1 || (countCounts[1] == 1 && diffCount <= 2)
            || (countCounts[1] != 0 && diffCount == 1)
            || (diffCount == 2 && ((countCounts[numCounts[nums[i]]] == 1 && countCounts[numCounts[nums[i]]-1] != 0) || countCounts[numCounts[nums[i]]+1] == 1))) {
            /*
             1. 各个数量为1 符合
             2. 有一个数量为n，其他都为n-1，符合
             3. 有一个数量为1，其他数量都为n，符合
             4. 只有一种数
             */
            maxLen = i+1;
        }
    }
    
    free(numCounts);
    free(countCounts);
    
    return maxLen;
}

int busyStudent(int* startTime, int startTimeSize, int* endTime, int endTimeSize, int queryTime){
    
    int n = startTimeSize;
    int result = 0;
    
    for (int i = 0; i < n; ++i) {
        if (startTime[i] <= queryTime && queryTime <= endTime[i]) {
            ++result;
        }
    }
    return result;
}

int getTreeHeight(struct TreeNode* root) {
    if (root == NULL) {
        return 0;
    }
    
    int left = getTreeHeight(root->left);
    int right = getTreeHeight(root->right);
    
    return (left>right?left:right)+1;
}

void printTreeHelper(struct TreeNode* root, char ***result, int height, int row, int col) {
    
    result[row][col] = malloc(sizeof(char)*4);
    sprintf(result[row][col], "%d", root->val);
    
    if (root->left != NULL) {
        printTreeHelper(root->left, result, height, row+1, col-(1<<( height-row-1)));
    }
    if (root->right != NULL) {
        printTreeHelper(root->right, result, height, row+1, col+(1<<( height-row-1)));
    }
}

char *** printTree(struct TreeNode* root, int* returnSize, int** returnColumnSizes){
    // 获取树高O(n)
    int height = getTreeHeight(root);
    *returnSize = height;
    *returnColumnSizes = malloc(sizeof(int*)*height);
    char ***result = malloc(sizeof(char**)*height);
    
    int colCount = (1<<(height-1))-1;
    
    for (int i = 0; i < height; ++i) {
        result[i] = malloc(sizeof(char*)*colCount);
        (*returnColumnSizes)[i] = colCount;
        for (int j = 0; j < colCount; ++j) {
            result[i][j] = "";
        }
    }
    
    printTreeHelper(root, result, height-1, 0, colCount/2);
    return result;
}

int isPrefixOfWord(char * sentence, char * searchWord){
    
    int i = 0;
    int j = 0;
    int wordIndex = 1;
    
    while (sentence[i] != '\0') {
        bool isPrefix = true;
        while (searchWord[j] != '\0') {
            if (sentence[i] != searchWord[j]) {
                isPrefix = false;
                j = 0;
                break;
            }
            ++i;
            ++j;
        }
        
        if (isPrefix) {
            return wordIndex;
        }
        
        while (sentence[i] != '\0') {
            if (sentence[i++] == ' ') break;
        }
        ++wordIndex;
    }
    
    return -1;
}

bool canBeEqual(int* target, int targetSize, int* arr, int arrSize){
    int hash[1001] = {0};
    int diffCount = 0;
    
    for (int i = 0; i < targetSize; ++i) {
        int oldCount = hash[target[i]];
        hash[target[i]] += 1;
        if (hash[target[i]] == 0) {
            --diffCount;
        } else if (oldCount == 0) {
            ++diffCount;
        }
        oldCount = hash[arr[i]];
        hash[arr[i]] -= 1;
        if (hash[arr[i]] == 0) {
            --diffCount;
        } else if (oldCount == 0) {
            ++diffCount;
        }
    }
    return diffCount==0;
}

int* shuffle(int* nums, int numsSize, int n, int* returnSize){
    
    int *result = malloc(sizeof(int)*numsSize);
    
    int i = 0;
    int j = n;
    int index = 0;
    while (j < numsSize) {
        result[index++] = nums[i++];
        result[index++] = nums[j++];
    }
    *returnSize = numsSize;
    return result;
}

bool validateStackSequences(int* pushed, int pushedSize, int* popped, int poppedSize){
    int *stack = malloc(sizeof(int)*pushedSize);
    int index = 0;
    for (int i = 0, j = 0; i < pushedSize; ++i) {
        stack[index++] = pushed[i];
        while (index > 0 && popped[j] == stack[index-1]) {
            --index;
            ++j;
        }
    }
    free(stack);
    return index==0;
}

// 模拟 O(n^2)
int* finalPrices(int* prices, int pricesSize, int* returnSize){
    int *result = malloc(sizeof(int)*pricesSize);
    int index = 0;
    for (int i = 0; i < pricesSize; ++i) {
        for (int j = i+1; j < pricesSize; ++j) {
            if (prices[i] >= prices[j]) {
                result[index++] = prices[i]-prices[j];
                break;
            }
        }
        if (index == i) {
            result[index++] = prices[i];
        }
    }
    *returnSize = pricesSize;
    return result;
}

// 单调栈 O(n)
int* finalPrices2(int* prices, int pricesSize, int* returnSize){
    int *result = malloc(sizeof(int)*pricesSize);
    int *stack = malloc(sizeof(int)*pricesSize);
    int top = 0;
    for (int i = pricesSize-1; i >= 0; --i) {
        while (top > 0 && stack[top-1] > prices[i]) {
            --top;
        }
        result[i] = top==0?prices[i]:prices[i]-stack[top-1];
        stack[top++] = prices[i];
    }
    *returnSize = pricesSize;
    free(stack);
    return result;
}

struct TreeNode** findDuplicateSubtrees(struct TreeNode* root, int* returnSize){
    /*
     1: 4, 0, 0
     2: 2, 1, 0
     3: 3, 2, 1
     4: 1, 2, 3
     */
    
    
}


int kSimilarity(char * s1, char * s2){
    /*
     1 <= s1.length <= 20
     s2.length == s1.length
     s1 和 s2  只包含集合 {'a', 'b', 'c', 'd', 'e', 'f'} 中的小写字母
     s2 是 s1 的一个字母异位词
     
     每个位的组合共36种
     其中 aa bb cc dd ee ff，文字相同无需交换
     不同的情况为30种
     ab ac ad ...等等
     ab 和 ba 是相对的，两个只需交换一次就有两个位变成相同
     
     abcdef
     bcdefa
     
     4
     "cdbcdeaafbf"
     "baddacffbec"
     aabbccddeff
     ffdebdaacbc
     
     10
     cda
     dac
     */
    
    // aa 0 bb 7 cc 14 dd 21 ee 28 ff 35
    // ab 1 ba 6
    // ac 2 ca 12
    // ad 3 da 18
    // bc 8 cb 13
    int len = strlen(s1);
    int *combine = malloc(sizeof(int)*36);
    int charCount[6] = {0};
    memset(combine, 0, sizeof(int)*36);
    for (int i = 0; i < len; ++i) {
        int index = (s1[i]-'a')*6+(s2[i]-'a');
        combine[index] += 1;
    }
    int total = 0;
    int leftCount = 0;
    int maxCount = 0;
    for (int i = 0; i < 6; ++i) {
        for (int j = i+1; j < 6; ++j) {
            int index1 = i*6+j;
            int index2 = i+j*6;
            if (combine[index1] > combine[index2]) {
                total += combine[index2];
                combine[index1] = combine[index1]-combine[index2];
                combine[index2] = 0;
                leftCount += combine[index1];
                charCount[i] += combine[index1];
            } else {
                total += combine[index1];
                combine[index2] = combine[index2]-combine[index1];
                combine[index1] = 0;
                leftCount += combine[index2];
                charCount[j] += combine[index2];
            }
        }
    }
    for (int i = 0; i < 6; ++i) {
        if (charCount[i] > maxCount) {
            maxCount = charCount[i];
        }
    }
    
    return total+leftCount-maxCount;
}

// 链表节点
struct MyHashObject {
    // hash值
    int key;
    // 任意对象
    int value;
};

// 一般的hash流程
// hash值计算
int calulateHashValue(int value) {
    return value%100;
}

// 尝试插入，如果该hash值被占用返回false
bool setObjectIfNotFill(struct MyHashObject** hashArray, int hash, int key, int value) {
    struct MyHashObject* object = hashArray[hash];
    if (object != NULL) {
        if (object->key == key) {
            // 同一值
            return true;
        } else {
            // 插入失败
            return false;
        }
    }
    struct MyHashObject* newObject = malloc(sizeof(struct MyHashObject));
    newObject->key = key;
    newObject->value = value;
    hashArray[hash] = newObject;
    return true;
}

// 插入值
void setValue(struct MyHashObject** hashArray, int key, int value) {
    
    int hash = calulateHashValue(key);
    while (setObjectIfNotFill(hashArray, hash, key, value)) {
        // 插入失败，用延长的方式，找出下一个空位
        hash = (hash+1)%100;
        break;
    }
}

// 找值
int getValue(struct MyHashObject** hashArray, int key) {
    int hash = calulateHashValue(key);
    while (1) {
        struct MyHashObject* object = hashArray[hash];
        if (object != NULL) {
            if (object->key == key) {
                // 同一值
                return object->value;
            } else {
                // 找下一个
                hash = (hash+1)%100;
            }
        } else {
            return -1;
        }
    }
}

bool canFormArray(int* arr, int arrSize, int** pieces, int piecesSize, int* piecesColSize){
    
    // 哈希 O(n)
    // 由于数值最大为100，这里可以用简易的数组代替hash
    int hash[101] = {-1};
    for (int i = 0; i < piecesSize; ++i) {
        hash[pieces[i][0]] = i;
    }
    
    for (int i = 0; i < arrSize; ) {
        int index = hash[arr[i]];
        if (index == -1) return false;
        
        int* piece = pieces[index];
        for (int j = 0; j < piecesColSize[index]; ++j,++i) {
            if (i >= arrSize || arr[i] != piece[j]) {
                return false;
            }
        }
    }
    return true;
    
    // 遍历 O(n^2)
    int i = 0;
    for (int j = 0; j < piecesSize && i < arrSize; ++j) {
        int* piece = pieces[j];
        if (arr[i] == piece[0]) {
            for (int k = 0; k < piecesColSize[j]; ++k,++i) {
                int num = piece[k];
                if (i >= arrSize || arr[i] != num) {
                    return false;
                }
            }
            j = -1;
        }
    }
    
    return i == arrSize;
}

typedef struct {
    struct ListNode *head;
    struct ListNode *tail;
    
} MyLinkedList;

struct ListNode* createListNode(int val) {
    struct ListNode *newNode = malloc(sizeof(struct ListNode));
    newNode->val = val;
    newNode->next = NULL;
    return newNode;
}

MyLinkedList* myLinkedListCreate() {
    MyLinkedList *object = malloc(sizeof(MyLinkedList));
    object->head = NULL;
    object->tail = NULL;
    return object;
}

int myLinkedListGet(MyLinkedList* obj, int index) {
    if (index < 0) {
        return -1;
    }
    struct ListNode *curNode = obj->head;
    for (int i = 0; i < index; ++i) {
        if (curNode != NULL) {
            curNode = curNode->next;
        } else {
            // 超出长度
            return -1;
        }
    }
    if (curNode != NULL) {
        return curNode->val;
    }
    return -1;
}

void myLinkedListAddAtHead(MyLinkedList* obj, int val) {
    struct ListNode *newNode = createListNode(val);
    newNode->next = obj->head;
    if (obj->head == NULL) {
        obj->tail = newNode;
    }
    obj->head = newNode;
}

void myLinkedListAddAtTail(MyLinkedList* obj, int val) {
    struct ListNode *newNode = createListNode(val);
    if (obj->tail != NULL) {
        obj->tail->next = newNode;
    } else {
        obj->head = newNode;
    }
    obj->tail = newNode;
}

void myLinkedListAddAtIndex(MyLinkedList* obj, int index, int val) {
    
    struct ListNode *curNode = obj->head;
    struct ListNode *preNode = NULL;
    for (int i = 0; i < index; ++i) {
        if (curNode != NULL) {
            preNode = curNode;
            curNode = curNode->next;
        } else {
            // 超出长度
            return;
        }
    }
    
    struct ListNode *newNode = createListNode(val);
    newNode->next = curNode;
    if (preNode == NULL) {
        obj->head = newNode;
    } else {
        preNode->next = newNode;
    }
    if (curNode == NULL) {
        obj->tail = newNode;
    }
}

void myLinkedListDeleteAtIndex(MyLinkedList* obj, int index) {
    if (index < 0) {
        return;
    }
    struct ListNode *curNode = obj->head;
    struct ListNode *preNode = NULL;
    for (int i = 0; i < index; ++i) {
        if (curNode != NULL) {
            preNode = curNode;
            curNode = curNode->next;
        } else {
            // 超出长度
            return;
        }
    }
    
    if (curNode != NULL) {
        if (preNode != NULL) {
            preNode->next = curNode->next;
            if (preNode->next == NULL) {
                obj->tail = preNode;
            }
        } else {
            obj->head = curNode->next;
            if (obj->head == NULL) {
                obj->tail = NULL;
            }
        }
        free(curNode);
    }
}

void myLinkedListFree(MyLinkedList* obj) {
    struct ListNode *node = obj->head;
    while (node) {
        struct ListNode *preNode = node;
        node = node->next;
        free(preNode);
    }
    
    free(obj);
}

int* missingTwo(int* nums, int numsSize, int* returnSize){
    int *result = malloc(sizeof(int)*2);
    int n = numsSize+2;
    int xorValue = 0;
    // 计算出a^b
    for (int i = 0; i < numsSize; ++i) {
        xorValue = xorValue^nums[i];
    }
    for (int i = 1; i <= n; ++i) {
        xorValue = xorValue^i;
    }
    // 找出a、b不同的位
    int difBit = xorValue&(-xorValue);
    int a = 0;
    int b = 0;
    for (int i = 0; i < numsSize; ++i) {
        if (nums[i]&difBit) {
            a ^= nums[i];
        } else {
            b ^= nums[i];
        }
    }
    for (int i = 1; i <=n; ++i) {
        if (i&difBit) {
            a ^= i;
        } else {
            b ^= i;
        }
    }
    result[0] = a;
    result[1] = b;
    *returnSize = 2;
    return result;
}

int getKthMagicNumber(int k){
    /*
     3 5 7
     
     */
    int dp[k + 1];
    dp[1] = 1;
    int p3 = 1, p5 = 1, p7 = 1;
    for (int i = 2; i <= k; i++) {
        int num3 = dp[p3] * 3, num5 = dp[p5] * 5, num7 = dp[p7] * 7;
        dp[i] = fmin(fmin(num3, num5), num7);
        if (dp[i] == num3) {
            p3++;
        }
        if (dp[i] == num5) {
            p5++;
        }
        if (dp[i] == num7) {
            p7++;
        }
    }
    return dp[k];

}

bool isFlipedString(char* s1, char* s2){
    
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    // 長度不一樣
    if (len1 != len2) return false;
    // 空字符串
    if (len1 == 0) return true;
    int doubleLen = len1*2;
    // 一次輪轉 檢查s2是否s1+s1的子串，需要O(n^2)
    for (int i = 0; i < doubleLen; ++i) {
        bool isSub = true;
        for (int j = 0; j < len1; ++j) {
            if (s2[j] != s1[(i+j)%len1]) {
                isSub = false;
                break;
            }
        }
        if (isSub) {
            return true;
        }
    }
    
    return false;
}

/*
 kmp算法
 ABCDABCABCEABCABCD
 ABCABCD
 next[] = {-1, 0, 0, -1, 0, 0, 3}
 
 */

void setZeroes(int** matrix, int matrixSize, int* matrixColSize){
    int m = matrixSize;
    int n = matrixColSize[0];
    int *row = malloc(sizeof(int)*m);
    int *col = malloc(sizeof(int)*n);
    memset(row, 0, sizeof(int)*m);
    memset(col, 0, sizeof(int)*n);
    
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j< n; ++j) {
            if (matrix[i][j] == 0) {
                row[i] = 1;
                col[j] = 1;
            }
        }
    }
    
    for (int i = 0; i < m; ++i) {
        if (row[i] == 1) {
            for (int j = 0; j < n; ++j) {
                matrix[i][j] = 0;
            }
        }
    }
    for (int j = 0; j < n; ++j) {
        if (col[j] == 1) {
            for (int i = 0; i < m; ++i) {
                matrix[i][j] = 0;
            }
        }
    }
    free(row);
    free(col);
}

static int cmp(const void *pa, const void *pb) {
    int *a = (int *)pa;
    int *b = (int *)pb;
    return a[1] - b[1];
}

int* advantageCount(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize) {
    int n = nums1Size;
    int idx1[n][2], idx2[n][2];
    for (int i = 0; i < n; i++) {
        idx1[i][0] = i, idx1[i][1] = nums1[i];
        idx2[i][0] = i, idx2[i][1] = nums2[i];
    }
    qsort(idx1, n, sizeof(idx1[0]), cmp);
    qsort(idx2, n, sizeof(idx2[0]), cmp);
    int *ans = (int *)malloc(sizeof(int) * n);
    int left = 0, right = n - 1;
    for (int i = 0; i < n; ++i) {
        if (nums1[idx1[i][0]] > nums2[idx2[left][0]]) {
            ans[idx2[left][0]] = nums1[idx1[i][0]];
            ++left;
        }
        else {
            ans[idx2[right][0]] = nums1[idx1[i][0]];
            --right;
        }
    }
    *returnSize = n;
    return ans;
}

//int scoreOfParenthesesHelper(char * s, int *move){
//    int result = 0;
//    int other = 0;
//    int i = 1;
//    int count = 1;
//    while (s[i] != 0) {
//        if (s[i] == ')') {
//            count -= 1;
//            if (count < 0) {
//                break;
//            }
//            char preChar = s[i-1];
//            if (preChar == ')') {
//                result *= 2;
//            } else {
//                result = 1;
//            }
//        } else {
//            
//            char preChar = s[i-1];
//            if (preChar == ')') {
//                int newMove = 0;
//                result += scoreOfParenthesesHelper(s+i, &newMove);
//                i += newMove-1;
//            } else {
//                count += 1;
//            }
//        }
//        ++i;
//    }
//    *move += i;
//    
//    return result;
//}
//
//int scoreOfParentheses(char * s){
//   
//    int move = 0;
//    int result = scoreOfParenthesesHelper(s, &move);
//    
//    return result;
//}

int scoreOfParentheses(char * s) {
    /*
     由于(1+1)*2 = 1*2 + 1*2
     只需计算每个()和其深度，然后加起来
     */
    int bal = 0, n = strlen(s), res = 0;
    for (int i = 0; i < n; i++) {
        bal += (s[i] == '(' ? 1 : -1);
        if (s[i] == ')' && s[i - 1] == '(') {
            res += 1 << bal;
        }
    }
    return res;
}

int minSwap(int* nums1, int nums1Size, int* nums2, int nums2Size){
    int n = nums1Size;
    /*
     a为当前不交换的最小次数
     b为当前交换的最小次数
     */
    int a = 0, b = 1;
    for (int i = 1; i < n; i++) {
        int at = a, bt = b;
        /*
         在符合情况1，而不符合情况2下:
            前面的数和当前的数交换情况必须一致，a = a, b = b+1
         在不符合情况1，而符合情况2下:
            前面的数和当前的数交换情况必须不一致, a = b, b = a+1
         在符合情况1，且符合情况2下:
            取交换数小的即可, 有 a = min(a, b), b = min(b+1, a+1)
         在不符合情况1，且不符合情况2下:
            这情况说明输入数据有问题，无论交不交换都无法获得符合题目的数据
         */
        // 情况1
        bool state1 = (nums1[i] > nums1[i - 1] && nums2[i] > nums2[i - 1]);
        // 情况2
        bool state2 = (nums1[i] > nums2[i - 1] && nums2[i] > nums1[i - 1]);
        if (state1 && state2) {
            a = MIN(at, bt);
            b = MIN(bt+1, at+1);
        } else if (state1) {
            b = bt+1;
        } else {
            a = bt;
            b = at+1;
        }
    }
    return MIN(a, b);
}

bool areAlmostEqual(char * s1, char * s2){
    int len = strlen(s1);
    int diffCount = 0;
    int diffIndex[2];
    for (int i = 0; i < len; ++i) {
        if (s1[i] != s2[i]) {
            if (diffCount == 2) return false;
            diffIndex[diffCount++] = i;
        }
    }
    if (diffCount == 0) return true;
    if (diffCount == 2 && (s1[diffIndex[0]] == s2[diffIndex[1]] && s1[diffIndex[1]] == s2[diffIndex[0]])) {
        return true;
    }
    return false;
}

char * reformatNumber(char * number){
    
    int count = 0;
    int i = 0;
    while (number[i] != '\0') {
        if (number[i] >= '0' && number[i] <= '9') {
            count += 1;
        }
        ++i;
    }
    int lastLeftCount = count%3;
    int resultLen = count;
    if (lastLeftCount == 0) {
        resultLen += (count-1)/3;
    } else {
        resultLen += count/3;
    }
    char *result = malloc(sizeof(int)*(resultLen+1));
    int index = 0;
    i = 0;
    int symbolCount = 0;
    count = 0;
    while (number[i] != '\0') {
        if (number[i] >= '0' && number[i] <= '9') {
            if (count/3 > symbolCount) {
                result[index++] = '-';
                ++symbolCount;
            }
            result[index++] = number[i];
            count += 1;
        }
        ++i;
    }
    if (lastLeftCount == 1 && resultLen > 1) {
        result[resultLen-2] = result[resultLen-3];
        result[resultLen-3] = '-';
    }
    result[index] = '\0';
    return result;
}

int numComponents(struct ListNode* head, int* nums, int numsSize){
    struct ListNode *cur = head;
    int n = 0;
    while (cur != NULL) {
        cur = cur->next;
        ++n;
    }
    int *contain = malloc(sizeof(int)*n);
    memset(contain, 0, sizeof(int)*n);
    for (int i = 0; i < numsSize; ++i) {
        contain[nums[i]] = 1;
    }
    int result = 0;
    cur = head;
    while (cur != NULL) {
        if (contain[cur->val] == 1 && (cur->next == NULL || contain[cur->next->val] == 0)) {
            result += 1;
        }
        cur = cur->next;
    }
    free(contain);
    return result;
}

const int mod = 1e9 + 7;
int distinctSubseqII(char * s){
    // 假设不去除重复, 那么子序列个数为2^len-1
    // 设f(n)代表第n位不重复子序列个数
    // 设g(n)代表包含第n位时不重复子序列个数
    // g(n) = f(n-1)+1
    // f(n) = f(n-1)+g(n)-重复序列
    // 有a0和a1，代表字符a所在的两个位置 且a1 > a0，且a0...a1间不包含其他a
    // 那么g(a1)子集必定包含g(a0)的所有子集
    // 有f(a1) = f(a1-1)+g(a1)-g(a0)
    
    int g[26];
    memset(g, 0, sizeof(g));
    int n = strlen(s), total = 0;
    for (int i = 0; i < n; ++i) {
        int oi = s[i] - 'a';
        int prev = g[oi];
        g[oi] = (total + 1) % mod;
        total = ((total + g[oi] - prev) % mod + mod) % mod;
    }
    return total;

}

int totalFruit(int* fruits, int fruitsSize){
    /*
     简单来说就是找只包含2种数字的最长子数组
     */
    
    if (fruitsSize < 2) {
        return fruitsSize;
    }
    
    int bucket1 = fruits[0];
    int bucket2 = -1;
    int left = 0;
    int right = 0;
    
    // 找出第一个不同的数
    while (right < fruitsSize) {
        if (fruits[right] != bucket1) {
            bucket2 = fruits[right];
            right += 1;
            break;
        }
        right += 1;
    }
    
    // 找只两个不同数的最长序列
    int lastBucket1Index = right-2;
    int lastBucket2Index = right-1;
    int maxLen = right;
    
    while (right < fruitsSize) {
        if (fruits[right] == bucket1) {
            lastBucket1Index = right;
        } else if (fruits[right] == bucket2) {
            lastBucket2Index = right;
        } else {
            if (right-left > maxLen) {
                maxLen = right-left;
            }
            if (lastBucket1Index < lastBucket2Index) {
                left = lastBucket1Index+1;
                bucket1 = bucket2;
                lastBucket1Index = lastBucket2Index;
            } else {
                left = lastBucket2Index+1;
            }
            
            bucket2 = fruits[right];
            lastBucket2Index = right;
        }
        right += 1;
    }
    if (right-left > maxLen) {
        maxLen = right-left;
    }
    
    return maxLen;
}

char ** buildArray(int* target, int targetSize, int n, int* returnSize){
    char **result = malloc(sizeof(char*)*target[targetSize-1]*2);
    int count = 0;
    int num = 1;
    for (int i = 0; i < targetSize; ++i) {
        
        while (target[i] > num) {
            result[count++] = "Push";
            result[count++] = "Pop";
            ++num;
        }
        result[count++] = "Push";
        ++num;
    }
    *returnSize = count;
    return result;
}

bool dfs(int curnode, int nowcolor, int *color, struct ListNode **g) {
    color[curnode] = nowcolor;
    for (struct ListNode *nextnode = g[curnode]; nextnode; nextnode = nextnode->next) {
        if (color[nextnode->val] && color[nextnode->val] == color[curnode]) {
            return false;
        }
        if (!color[nextnode->val] && !dfs(nextnode->val, 3 ^ nowcolor, color, g)) {
            return false;
        }
    }
    return true;
}

bool possibleBipartition(int n, int** dislikes, int dislikesSize, int* dislikesColSize) {
    int color[n + 1];
    struct ListNode *g[n + 1];
    for (int i = 0; i <= n; i++) {
        color[i] = 0;
        g[i] = NULL;
    }
    for (int i = 0; i < dislikesSize; i++) {
        int a = dislikes[i][0], b = dislikes[i][1];
        struct ListNode *node = (struct ListNode *)malloc(sizeof(struct ListNode));
        node->val = a;
        node->next = g[b];
        g[b] = node;
        node = (struct ListNode *)malloc(sizeof(struct ListNode));
        node->val = b;
        node->next = g[a];
        g[a] = node;
    }
    for (int i = 1; i <= n; ++i) {
        if (color[i] == 0 && !dfs(i, 1, color, g)) {
            for (int j = 0; j <= n; j++) {
                struct ListNode * node = g[j];
                while (node) {
                    struct ListNode * prev = node;
                    node = node->next;
                    free(prev);
                }
            }
            return false;
        }
    }
    for (int j = 0; j <= n; j++) {
        struct ListNode * node = g[j];
        while (node) {
            struct ListNode * prev = node;
            node = node->next;
            free(prev);
        }
    }
    return true;
}

int atMostNGivenDigitSet(char ** digits, int digitsSize, int n){
    int less[10] = {0};
    int contain[10] = {0};
    int nDigit[10] = {0};
    int digitPower[10] = {1};
    int digitPowerPlus[10] = {0};
    for (int i = 0; i < digitsSize; ++i) {
        int num = digits[i][0]-'0';
        int preNum = 0;
        if (i > 0) {
            preNum = digits[i-1][0]-'0';
        }
        for (int j = num; j > preNum; --j) {
            less[j] = i;
        }
        contain[num] = 1;
    }
    int maxDigit = digits[digitsSize-1][0]-'0';
    for (int i = maxDigit+1; i <= 9; ++i) {
        less[i] = less[maxDigit]+1;
    }
    
    for (int i = 1; i < 10; ++i) {
        digitPower[i] = digitPower[i-1]*digitsSize;
        digitPowerPlus[i] = digitPower[i]+digitPowerPlus[i-1];
    }
    digitPowerPlus[0] = 1;
    
    int index = 9;
    int num = n;
    int muti = 1000000000;
    while (muti > 1) {
        nDigit[index--] = num/muti;
        num = num%muti;
        muti /= 10;
    }
    nDigit[0] = num;
    
    int result = 0;
    int i = 9;
    for (; i >= 0; --i) {
        if (nDigit[i] != 0) {
            break;
        }
    }
    for (; i >= 0; --i) {
        result += less[nDigit[i]]*digitPowerPlus[i];
        if (contain[nDigit[i]] == 0) {
            if (i > 0 && less[nDigit[i]] == 0) {
                result += digitPowerPlus[i];
            } else if (i > 0 && less[nDigit[i]] > 0) {
                result += digitPower[i];
            }
            break;
        } else {
            result += digitPower[i];
        }
    }
    /*
     ["1","2","3","6","7","8"]
     211
     
     6*6+6
     
     
     */
    return result;
}

int countStudents(int* students, int studentsSize, int* sandwiches, int sandwichesSize){
    int n = sandwichesSize;
    int left[2] = {0};
    for (int i = 0; i < n; ++i) {
        left[students[i]] -= 1;
        left[sandwiches[i]] += 1;
    }
    
    int leftNum = 0;
    if (left[0] > 0) {
        // 0有余
    } else if (left[1] > 0) {
        // 1有余
        leftNum = 1;
    } else {
        return 0;
    }
    
    for (int i = sandwichesSize-1; i >=0; --i) {
        if (sandwiches[i] == leftNum && --left[leftNum] == 0) {
            return sandwichesSize-i;
        }
    }
    
    return 0;
}

int kthGrammar(int n, int k){
    /*
     0
     01
     0110
     01101001
     0110100110010110
     
     每一行是上一行长度*2，前半与上一行相同，后半为前半的反转
     1 2 5 9 17 2^n+1
     
     f(k) = f(k-)^1
     
     f(1) = 0
     f(2) = f(1)^1
     f(3) = f(1)^1
     f(4) = f(2)^1
     f(5) = f(1)^1
     
     111
     110
     101
     100
     
     k&(k-1) 会把最后一位的1去掉
     可以通过循环k&(k-1)计算出有多少位为1
     */
    
    int result = 0;
    k = k-1;
    while (k > 0) {
        k &= k - 1;
        result ^= 1;
    }
    return result;
}

struct StockNode {
    int val;
    int span;
    struct StockNode *spanNode;
    struct StockNode *next;
};

typedef struct {
    struct StockNode *now;
} StockSpanner;

StockSpanner* stockSpannerCreate() {
    StockSpanner *obj = malloc(sizeof(StockSpanner));
    obj-> now = NULL;
    return obj;
}

int stockSpannerNext(StockSpanner* obj, int price) {
    struct StockNode *node = malloc(sizeof(struct StockNode));
    node->val = price;
    node->next = obj->now;
    node->span = 1;
    node->spanNode = node;
    struct StockNode *tmpNode = obj->now;
    while (tmpNode) {
        if (node->val >= tmpNode->val) {
            node->span += tmpNode->span;
            node->spanNode = tmpNode->spanNode;
            tmpNode = node->spanNode->next;
        } else {
            break;
        }
    }
    
    obj->now = node;
    
    return node->span;
}

void stockSpannerFree(StockSpanner* obj) {
    struct StockNode *next = obj->now;
    while (next) {
        struct StockNode *tmp = next;
        next = next->next;
        free(tmp);
    }
    
    free(obj);
}

int partitionDisjoint(int* nums, int numsSize){
    /*
     在最大值处划分，可以分出符合的数组，但左数组不一定是最短的
     */
    
    // 维护分割左数组的最大值
    
    int maxValue = nums[0];
    int leftValue = maxValue;
    int result = 0;
    int n = numsSize-1;
    for (int i = 1; i < n; ++i) {
        if (nums[i] < leftValue) {
            // 新的分割位，更新位置和左边最大值
            result = i;
            leftValue = maxValue;
        } else if (nums[i] > maxValue) {
            // 记录下一个的左边最大值
            maxValue = nums[i];
        }
    }
    return result+1;
}

int shortestBridge(int** grid, int gridSize, int* gridColSize){
    
    
}


int shortestSubarray(int* nums, int numsSize, int k){
    int sum = 0;
    int left = 0;
    int right = 0;
    int minLength = numsSize+1;
    while (right < numsSize) {
        
        sum += nums[right];
        if (nums[right] >= sum) {
            sum = nums[right];
            left = right;
        }
        if (sum >= k) {
            int len = right-left+1;
            if (len < minLength) {
                minLength = len;
            }
            while (left < right) {
                sum -= nums[left++];
                if (nums[right] >= sum) {
                    sum = nums[right];
                    left = right;
                }
                while (nums[left] <= 0 && left < right) {
                    sum -= nums[left++];
                }
                if (sum >= k) {
                    int len = right-left+1;
                    if (len < minLength) {
                        minLength = len;
                    }
                } else {
                    break;
                }
            }
        }
        
        right += 1;
    }
    if (minLength == numsSize+1) {
        return -1;
    }
    return minLength;
}

char * customSortString(char * order, char * s){
    int count[26] = {0};
    int length = strlen(s);
    char *result = malloc(sizeof(int)*(length+1));
    int index = 0;
    
    while (*s != '\0') {
        count[*s-'a'] += 1;
        ++s;
    }
    while (*order != '\0') {
        int alpha = *order-'a';
        while (count[alpha]) {
            result[index++] = *order;
            count[alpha] -= 1;
        }
        ++order;
    }
    for (int i = 0; i < 26; ++i) {
        while (count[i]) {
            result[index++] = 'a'+i;
            count[i] -= 1;
        }
    }
    result[length] = '\0';
    return result;
}

int numMatchingSubseq(char * s, char ** words, int wordsSize){
    int sLen = strlen(s);
    int **map = malloc(sizeof(int*)*sLen);
    int minIndex[26];
    for (int i; i < 26; ++i) {
        minIndex[i] = -1;
    }
    // 复杂度 26*sLen
    for (int i = sLen-1; i >= 0; --i) {
        map[i] = malloc(sizeof(int)*26);
        for (int j = 0; j < 26; ++j) {
            map[i][j] = minIndex[j];
        }
        minIndex[s[i]-'a'] = i;
    }
    
    int count = 0;
    for (int i = 0; i < wordsSize; ++i) {
        int lastIndex = -1;
        int j = 0;
        while (words[i][j] != '\0') {
            if (lastIndex == -1) {
                lastIndex = minIndex[words[i][j]-'a'];
            } else {
                lastIndex = map[lastIndex][words[i][j]-'a'];
            }
            if (lastIndex == -1) {
                break;
            }
            ++j;
        }
        if (words[i][j] == '\0') {
            ++count;
        }
    }
    // 释放
    for (int i = sLen-1; i >= 0; --i) {
        free(map[i]);
    }
    free(map);
    
    return count;
}

// 复杂度 n+m，m为所有words中的字符长度加起来的值，n位s的长度
int numMatchingSubseq2(char * s, char ** words, int wordsSize){
    int res = 0;
    int len_s = strlen(s);
    // 以某字母开头的word数组，记录对应word的下标
    int bucket[26][wordsSize];
    // 以某字母开头的数量，a下标为0
    int count[26] = {0};
    // 每个word的偏移值
    int offset[wordsSize];

    memset(bucket, 0, sizeof(bucket));
    memset(offset, 0, sizeof(offset));

    for (int i = 0; i < wordsSize; i++)
    {
        int idx = words[i][0] - 'a';
        bucket[idx][count[idx]++] = i;
    }

    for (int i = 0; i < len_s; i++)
    {
        int idx = s[i] - 'a';
        int num = count[idx];
        count[idx] = 0;
        for(int j = 0; j < num; j++)
        {
            // 找出遍历到某字母的word
            int temp = bucket[idx][j];
            char *ptr = words[temp];
            offset[temp] += 1;
            if (ptr[offset[temp]] != 0)
            {
                // 这里会改变words[temp]的指针位置，如果要求不能改入参，
                // 可以增加一个数组去记录每个word的指针偏移值
                int next = ptr[offset[temp]] - 'a';
                bucket[next][count[next]++] = temp;
            }else{
                // 已经把这个word遍历完，说明word是子序列
                res++;
            }
            
        }
    }
    return res;
}

int countBalls(int lowLimit, int highLimit){
    int count[46] = {0};
    int maxCount = 0;
    for (int i = lowLimit; i <= highLimit; ++i) {
        int index = 0;
        int value = i;
        while (value > 0) {
            index += value%10;
            value/=10;
        }
        count[index] += 1;
        if (count[index] > maxCount) {
            maxCount = count[index];
        }
    }
    return maxCount;
}

int closestCost(int* baseCosts, int baseCostsSize, int* toppingCosts, int toppingCostsSize, int target){

    // 全部组合共 m*3^n 种
    
    
    
}

int minOperations(int* nums1, int nums1Size, int* nums2, int nums2Size){

    if (nums2Size > nums1Size) {
        // 让数组1长度大于数组2
        int *tmpNums = nums1;
        nums1 = nums2;
        nums2 = tmpNums;
        int tmpNum = nums1Size;
        nums1Size = nums2Size;
        nums2Size = tmpNum;
    }
    
    if ((nums1Size-1)/nums2Size >= 6) {
        // 一个数组大于另一个6倍时，不可能有解
        return -1;
    }
    
    int count1[7] = {0};
    int count2[7] = {0};
    
    int sum1 = 0;
    int sum2 = 0;
    
    for (int i = 0; i < nums1Size; ++i) {
        count1[nums1[i]] += 1;
        sum1 += nums1[i];
    }
    for (int i = 0; i < nums2Size; ++i) {
        count2[nums2[i]] += 1;
        sum2 += nums2[i];
    }
    //int moreSize = nums1Size-nums2Size;
    int moreSum = sum1-sum2;
    
    int result = 0;
    if (moreSum > 0) {
        for (int i = 1; i < 7; ++i) {
            int value = 6-i;
            int needCount = moreSum/value;
            int left = moreSum%value;
            int hasCount = count1[7-i]+count2[i];
            
            if (hasCount > needCount) {
                result += needCount;
                if (left > 0) {
                    result += 1;
                }
                break;
            } else {
                moreSum -= value*hasCount;
                result += hasCount;
            }
            if (moreSum == 0) {
                break;
            }
        }
    } else if (moreSum < 0) {
        moreSum = -moreSum;
        for (int i = 1; i < 7; ++i) {
            int value = 6-i;
            int needCount = moreSum/value;
            int left = moreSum%value;
            int hasCount = count2[7-i]+count1[i];
            
            if (hasCount > needCount) {
                result += needCount;
                if (left > 0) {
                    result += 1;
                }
                break;
            } else {
                moreSum -= value*hasCount;
                result += hasCount;
            }
            if (moreSum == 0) {
                break;
            }
        }
    }
    
    return result;
    
}

int countHomogenous(char * s){

    char pre = 0;
    int count = 0;
    int result = 0;
    
    while (*s != '\0') {
        if (*s == pre) {
            ++count;
            count %= 1000000007;
        } else {
            count = 1;
        }
        result += count;
        result %= 1000000007;
        pre = *s;
        ++s;
    }
    
    return result;
}

char * largestMerge(char * word1, char * word2){
    
    int m = strlen(word1), n = strlen(word2);
        char *merge = (char *)malloc(sizeof(char) * (m + n + 1));
        int i = 0, j = 0, pos = 0;
        while (i < m || j < n) {
            if (i < m && strcmp(word1 + i, word2 + j) > 0) {
                merge[pos] = word1[i];
                pos++, i++;
            } else {
                merge[pos] = word2[j];
                pos++, j++;
            }
        }
        merge[pos] = '\0';
        return merge;

}

int finalValueAfterOperations(char ** operations, int operationsSize){

    int result = 0;
    for (int i = 0; i < operationsSize; ++i) {
        int j = 0;
        while (operations[i][j] != '\0') {
            if (operations[i][j] == '+') {
                result += 1;
                break;
            } else if (operations[i][j] == '-') {
                result -= 1;
                break;
            }
            ++j;
        }
    }
    return result;
}

int maximumScore(int a, int b, int c){

    int sum = a+b+c;
    int m1 = 0;
    if (a > b && a > c) {
        m1 = a;
    } else if (b > a && b > c) {
        m1 = b;
    } else {
        m1 = c;
    }
    
    if (m1 >= sum-m1) {
        return sum-m1;
    } else {
        return sum/2;
    }
    
}

int minimumMoves(char * s){
    
    int xCount = 0;
    int result = 0;
    while (*s != '\0') {
        if (*s == 'X' || xCount != 0) {
            xCount += 1;
            if (xCount == 3) {
                result += 1;
                xCount = 0;
            }
        }
        ++s;
    }
    if (xCount > 0) result += 1;
    return result;
}

int minimumLength(char * s){
    
    int len = strlen(s);
    
    int l = 0;
    int r = len-1;
    
    while (l < r && s[l] == s[r]) {
        char c = s[l];
        while (s[++l] == c && l < r);
        while (s[--r] == c && l <= r);
    }
    
    return r-l+1;
}

int* twoOutOfThree(int* nums1, int nums1Size, int* nums2, int nums2Size, int* nums3, int nums3Size, int* returnSize){

    int *result = malloc(sizeof(int)*100);
    int count = 0;
    
    int contain[101] = {0};
    for (int i = 0; i < nums1Size; ++i) {
        contain[nums1[i]] = 1;
    }
    for (int i = 0; i < nums2Size; ++i) {
        if (contain[nums2[i]] == 1) {
            result[count++] = nums2[i];
            contain[nums2[i]] = 11;
        } else if (contain[nums2[i]] == 0) {
            contain[nums2[i]] = 10;
        }
        
    }
    for (int i = 0; i < nums3Size; ++i) {
        if (contain[nums3[i]] == 1 || contain[nums3[i]] == 10) {
            result[count++] = nums3[i];
            contain[nums3[i]] += 100;
        } else {
            contain[nums3[i]] = 100;
        }
    }
    
    *returnSize = count;
    return result;
}

typedef struct {
    struct ListNode *node;
    int n;
} ExamRoom;


ExamRoom* examRoomCreate(int n) {

    ExamRoom *obj = malloc(sizeof(ExamRoom));
    obj->node = NULL;
    obj->n = n;
    return obj;
}

int examRoomSeat(ExamRoom* obj) {
 
    struct ListNode *curNode = obj->node;
    
    int l = -1;
    int r = -1;
    int maxLen = 0;
    struct ListNode *target = NULL;
    struct ListNode *preNode = NULL;
    
    while (curNode) {
        l = r;
        r = curNode->val;
        if (l == -1) {
            maxLen = r;
        } else if ((r-l)/2 > maxLen) {
            maxLen = (r-l)/2;
            target = preNode;
        }
        preNode = curNode;
        curNode = curNode->next;
    }
    
    struct ListNode *node = malloc(sizeof(struct ListNode));
    if (r != -1 && obj->n-1-r > maxLen) {
        node->val = obj->n-1;
        node->next = NULL;
        preNode->next = node;
    } else if (target == NULL) {
        node->val = 0;
        node->next = obj->node;
        obj->node = node;
    } else {
        node->val = target->val+maxLen;
        node->next = target->next;
        target->next = node;
    }
    
    return node->val;
}

void examRoomLeave(ExamRoom* obj, int p) {
    struct ListNode *curNode = obj->node;
    struct ListNode *preNode = NULL;
    while (curNode) {
        if (curNode->val == p) {
            if (preNode == NULL) {
                obj->node = curNode->next;
            } else {
                preNode->next = curNode->next;
            }
            free(curNode);
            break;
        }
        preNode = curNode;
        curNode = curNode->next;
    }
}

void examRoomFree(ExamRoom* obj) {
    struct ListNode *curNode = obj->node;
    while (curNode) {
        struct ListNode *next = curNode->next;
        free(curNode);
        curNode = next;
    }
    free(obj);
}

int jump(int* nums, int numsSize){
    
    int maxPos = 0;
    int end = 0;
    int step = 0;
    
    for (int i = 0; i < numsSize-1; ++i) {
        if (maxPos >= i) {
            maxPos = fmax(maxPos, i+nums[i]);
            if (i == end) {
                end = maxPos;
                ++step;
            }
        }
    }
    
    return step;
}

bool areNumbersAscending(char * s){
    int num = 0;
    int preNum = -1;
    while (*s != '\0') {
        if (*s >= '0' && *s <= '9') {
            num = num*10+*s-'0';
        } else if (num > 0) {
            if (num <= preNum) {
                return false;
            }
            preNum = num;
            num = 0;
        }
    }
    if (num > 0) {
        return num > preNum;
    }
    return true;
}

struct OrderNode {
    int price;
    int count;
    struct OrderNode *next;
};

int getNumberOfBacklogOrders(int** orders, int ordersSize, int* ordersColSize){
    
    struct OrderNode *buyNode = NULL;
    struct OrderNode *sellNode = NULL;
    int totalCount = 0;

    for (int i = 0; i < ordersSize; ++i) {
        int price = orders[i][0];
        int count = orders[i][1];
        if (orders[i][2] == 0) {
            // buy
            
            while (sellNode) {
                if (sellNode->price <= price) {
                    if (sellNode->count <= count) {
                        count -= sellNode->count;
                        totalCount -= sellNode->count;
                        sellNode->count = 0;
                        struct OrderNode *freeNode = sellNode;
                        sellNode = sellNode->next;
                        free(freeNode);
                    } else {
                        sellNode->count -= count;
                        totalCount -= count;
                        count = 0;
                        break;
                    }
                } else {
                    break;
                }
            }
            if (totalCount < 0) {
                totalCount += 1000000007;
            }
            if (count == 0) {
                continue;
            }
            
            totalCount += count;
            totalCount %= 1000000007;
            
            struct OrderNode *tmpNode = buyNode;
            struct OrderNode *preNode = NULL;
            while (tmpNode) {
                if (tmpNode->price <= price) {
                    break;
                }
                preNode = tmpNode;
                tmpNode = tmpNode->next;
            }
            struct OrderNode *newNode;
            if (tmpNode != NULL && tmpNode->price == price) {
                tmpNode->count += count;
                newNode = tmpNode;
            } else {
                newNode = malloc(sizeof(struct OrderNode));
                newNode->price = price;
                newNode->count = count;
                newNode->next = tmpNode;
            }
            if (preNode != NULL) {
                preNode->next = newNode;
            } else {
                buyNode = newNode;
            }
            
        } else {
            // sell
            
            while (buyNode) {
                if (buyNode->price >= price) {
                    if (buyNode->count <= count) {
                        count -= buyNode->count;
                        totalCount -= buyNode->count;
                        buyNode->count = 0;
                        struct OrderNode *freeNode = buyNode;
                        buyNode = buyNode->next;
                        free(freeNode);
                    } else {
                        buyNode->count -= count;
                        totalCount -= count;
                        count = 0;
                        break;
                    }
                } else {
                    break;
                }
            }
            if (totalCount < 0) {
                totalCount += 1000000007;
            }
            if (count == 0) {
                continue;
            }
            
            totalCount += count;
            totalCount %= 1000000007;
            
            struct OrderNode *tmpNode = sellNode;
            struct OrderNode *preNode = NULL;
            while (tmpNode) {
                if (tmpNode->price >= price) {
                    break;
                }
                preNode = tmpNode;
                tmpNode = tmpNode->next;
            }
            struct OrderNode *newNode;
            if (tmpNode != NULL && tmpNode->price == price) {
                tmpNode->count += count;
                newNode = tmpNode;
            } else {
                newNode = malloc(sizeof(struct OrderNode));
                newNode->price = price;
                newNode->count = count;
                newNode->next = tmpNode;
            }
            if (preNode != NULL) {
                preNode->next = newNode;
            } else {
                sellNode = newNode;
            }
        }
        
    }
    
    
    return totalCount;
}

int maxValue(int n, int index, int maxSum){
    
    /*
     按题意可知
     0..index 为递增，index..n-1为递减时为最优解
     
     由于每个数都必须是正整数，所以每个位置的最小值是1
     每个数放1
     有 1 1 1 1 .. 1
     设剩余可用数为sum
     此时 sum = maxSum-n;
     
     如果sum>=1，往index处+1
     有 1 1 1 2 .. 1
     此时sum = sum-1;
     
     设两个数列最长长度分别为m1、m2，其中m2>=m1
     
     情况1:
     当长度达到m1前有
     所需数量为 m1*(m1+1)+m1
     如果sum比这个值小，通过解方程 可得解 result = sqrt(sum+1)-1
     最终 index处的最大值为 result+2
     
     
     情况2:
     sum >= m1*(m1+1)+m1
     sum = sum-(m1*(m1+1)+m1)
     index 处的值 增加 m1
     
     设k = m2-m1
     那么达到k前，增加数为2*k*m1+k*(k+1)/2+k
     如果剩余sum < 2*k*m1+k*(k+1)/2+k
     通过解方程可得 result = sqrt(2*sum+(2*m1+1.5)*(2*m1+1.5))-(2*m1+1.5)
     最终 index处的最大值为 result+m1+2
     
     情况3
     如果剩余sum >= 2*k*m1+k*(k+1)/2+k
     sum = sum-(2*k*m1+k*(k+1)/2+k)
     index 处的值 增加 k
     此时index每增加1其他的位置都必须加1
     有 result = sum/n;
     最终 index处的最大值为 result+m1+k+2
     
     */
    
    long m1 = index;
    long m2 = n-index-1;
    
    if (m1 > m2) {
        long tmp = m2;
        m2 = m1;
        m1 = tmp;
    }
    
    int result = 1;
    maxSum -= n;
    if (maxSum >= 1) {
        result += 1;
        maxSum -= 1;
    }
    
    if (maxSum >= m1*(m1+2)) {
        maxSum -= m1*(m1+2);
        result += m1;
        long k = m2-m1;
        if (2*k*m1+k*(k+1)/2+k <= maxSum) {
            // 情况3
            maxSum -= 2*k*m1+k*(k+1)/2+k;
            result += k;
            result += maxSum/n;
        } else {
            // 情况2
            result += sqrt(2*maxSum+(2*m1+1.5)*(2*m1+1.5))-(2*m1+1.5);
        }
        
    } else {
        // 情况1
        result += sqrt(maxSum+1)-1;
    }
    
    return result;
}

int reinitializePermutation(int n){
    int target = 1;
    int next = n/2;
    int step = 1;
    while (target != next) {
        target = 2*target%(n-1);
        ++step;
    }
    return step;
}


int prefixCount(char ** words, int wordsSize, char * pref){
    int count = 0;
    for (int i = 0; i < wordsSize; ++i) {
        int j = 0;
        while (words[i][j] != '\0') {
            if (pref[j] == '\0') {
                ++count;
                break;
            }
            if (words[i][j] != pref[j]) {
                break;
            }
            ++j;
        }
    }
    return count;
}


int minOperations(int* nums, int numsSize, int x){
    
    //f[l][r] = L[l]+R[r];
    //L[0] = 0;
    //L[1] = nums[0];
    //R[r] = sum-L[r];
    
    int sum = 0;
    for (int i = 0; i < numsSize; ++i) sum += nums[i];
    
    if (sum == x) return numsSize;
    if (sum < x) return -1;
    
    int rightSum = sum;
    int leftSum = 0;
    int minCount = numsSize+1;
    int right = 0;
    for (int i = 0; i < numsSize; ++i) {
        
        while (right < numsSize && leftSum+rightSum > x) {
            rightSum -= nums[right++];
        }
        
        if (leftSum+rightSum == x && i+numsSize-right < minCount) {
            minCount = i+numsSize-right;
        }
        leftSum += nums[i];
    }
    if (minCount > numsSize) return -1;
    return minCount;
}


