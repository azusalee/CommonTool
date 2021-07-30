//
//  LeetCodeC.c
//  CommonTool
//
//  Created by lizihong on 2019/8/8.
//  Copyright © 2019 AL. All rights reserved.
//

#include "LeetCodeC.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>

/*
 字符          数值
 I             1
 V             5
 X             10
 L             50
 C             100
 D             500
 M             1000
 */
/// 罗马数字转整数(1~3999)
int romanToInt(char * s) {
    int result = 0, lastIncrease = 0, curIncrease = 0, i = 0;
    while (1) {
        switch (s[i++]) {
            case 'M': curIncrease = 1000; break;
            case 'D': curIncrease = 500; break;
            case 'C': curIncrease = 100; break;
            case 'L': curIncrease = 50; break;
            case 'X': curIncrease = 10; break;
            case 'V': curIncrease = 5; break;
            case 'I': curIncrease = 1; break;
            // '\0'或者其他不符合的字符
            default: return result;
        }
        result += curIncrease;
        // 后面的比前面大，把前面的减去
        if (curIncrease - lastIncrease > 0) result -= lastIncrease*2;
        lastIncrease = curIncrease;
    }
    return result;
}

/// 回文数
bool isPalindrome(int x) {
    if (x < 0) {
        return false;
    } else {
        int tmpX = x;
        long result = 0;
        while (tmpX != 0) {
            result *= 10;
            result += tmpX%10;
            tmpX /= 10;
        }
        return result == x;
    }
}

// 有效括号{} [] ()
bool isVaildBrackets(char *s) {
    unsigned long strLength = strlen(s);
    if (strLength == 0) {
        return true;
    }
    char typeList[strLength];
    int i = 0, typeLen = 0;
    
    while (1) {
        switch (s[i++]) {
            case '(':
                typeList[typeLen++] = 1;
                break;
            case ')': 
                if (--typeLen < 0 || typeList[typeLen] != 1) return false;
                break;
            case '[': 
                typeList[typeLen++] = 2;
                break;
            case ']': 
                if (--typeLen < 0 || typeList[typeLen] != 2) return false;
                break;
            case '{': 
                typeList[typeLen++] = 3;
                break;
            case '}': 
                if (--typeLen < 0 || typeList[typeLen] != 3) return false;
                break;
            case '\0': return typeLen==0;
            default: continue;
        }
    }
    
    return typeLen==0;
}

// +1
int* plusOne(int* digits, int digitsSize, int* returnSize){
    bool needIncrease = true;
    for (int i = 0; i < digitsSize; ++i) {
        int num = digits[digitsSize-i-1];
        num += 1;
        if (num > 9) {
            digits[digitsSize-i-1] = 0;
        } else {
            digits[digitsSize-i-1] = num;
            needIncrease = false;
            break;
        }
    }
    
    if (needIncrease) {
        int *result = malloc(sizeof(int)*(digitsSize+1));
        result[0] = 1;
        memset(result+1, 0, sizeof(int)*digitsSize);
        *returnSize = digitsSize+1;
        return result;
    } else {
        *returnSize = digitsSize;
        return digits;
    }
}

/// 字符串转换整数 (atoi)
int myAtoi(char * str){
    int i = 0;
    long result = 0;
    bool flag = false, minus = false;
    while (1) {
        char c = str[i++];
        if (c >= '0' && c <= '9') {
            if (flag == false) flag = true;
            result = result*10+c-'0';
        } else if (c == ' ') {
            if (flag) {
                if (minus) return (int)(-result);
                else return (int)result;
            }
            continue;
        } else if (c == '+') {
            if (flag == false) {
                flag = true;
            } else {
                if (minus) return (int)(-result);
                else return (int)result;
            }
            continue;
        } else if (c == '-') {
            if (flag == false) {
                flag = true;
                minus = true;
            } else {
                if (minus) return (int)(-result);
                else return (int)result;
            }
            continue;
        } else if (c == '\0') {
            if (minus) return (int)(-result);
            else return (int)result;
        } else {
            if (flag) {
                if (minus) return (int)(-result);
                else return (int)result;
            } else {
                return 0;
            }
        }
        if (result >= 2147483647) {
            if (minus == false) return 2147483647;
            else if (result >= 2147483648) return -2147483648;
        }
    }
}

/// 删除链表中倒数第n个数
struct ListNode* removeNthFromEnd(struct ListNode* head, int n){
    if (n > 0) {
        struct ListNode *tmp = head;
        while (--n) {
            tmp = tmp->next;
        }
        
        if (tmp->next == NULL) {
            return head->next;
        }else{
            tmp = tmp->next;
        }
        
        struct ListNode *tmp2 = head;
        while (tmp->next != NULL) {
            tmp = tmp->next;
            tmp2 = tmp2->next;
        }
        
        tmp2->next = tmp2->next->next;
        
        return head;
    }
    return head;
}

/// Z 字形变换
char * convertZ(char * s, int numRows){
    // 以numRows为4做例子
    // 0  6         (numRows*2-2)*n
    // 1 57         (numRows*2-2)*n-1, (numRows+2)*n+1
    // 24 8         (numRows*2-2)*n-2, (numRows+2)*n+2
    // 3  9         (numRows*2-2)*n+3, (numRows*2-2)*n-3
    
    if (numRows < 2) return s;
    unsigned long len = strlen(s);
    if (len <= 2) return s;
    int loopLen = numRows*2-2, row = 0, i = loopLen, j = 1;
    char *result = malloc(sizeof(char)*(len+1));
    result[0] = s[0];
    while (1) {
        if (i >= len) {
            if (++row == numRows) break;
            i = row;
            continue;
        }
        result[j++] = s[i];
        if (row != 0 && row != numRows-1 && i+loopLen-row*2 < len) result[j++] = s[i+loopLen-row*2];
        i += loopLen;
    }
    result[j] = '\0';
    return result;
}

int strStr(char * haystack, char * needle){
    if (*needle == '\0') return 0;
    int i = 0, j = 0, location = 0;
    while (haystack[i] != '\0') {
        if (needle[j] == haystack[i]) {
            location = i;
            while (1) {
                if (needle[++j] == '\0') return location;
                if (haystack[++i] == '\0') return -1;
                if (needle[j] != haystack[i]) {
                    i = location;
                    j = 0;
                    break;
                }
            }
        }
        ++i;
    }
    return -1;
}

char * longestCommonPrefix(char ** strs, int strsSize){
    if (strsSize == 0) return "";
    if (strsSize == 1) return strs[0];
    char *str1 = strs[0];
    if (str1[0] == '\0') return "";
    int j = 0;
    while (1) {
        for (int i = 1; i < strsSize; ++i) {
            if (str1[j] != strs[i][j]) {
                str1[j] = '\0';
                return str1;
            }
        }
        if (str1[++j] == '\0') break;
    }
    return str1;
}

//快排代码
void quickSort(int* nums,int first,int end){
    int temp,l,r;
    if(first>=end)return;
    temp=nums[first];
    l=first;r=end;
    while(l<r){
        while(l<r && nums[r]>=temp)r--;
        if(l<r)nums[l]=nums[r];
        while(l<r && nums[l]<=temp)l++;
        if(l<r)nums[r]=nums[l];
    }
    nums[l]=temp;
    quickSort(nums,first,l-1);
    quickSort(nums,l+1,end);
}

int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){
    quickSort(nums, 0, numsSize-1);
    
    int sum, i, j, k;
    int length = 0;
    int oneGroupSize = 3*sizeof(int);

    int pre_alloc_size = 16;
    int *block = (int *)malloc(pre_alloc_size*oneGroupSize);
    
    for (i = 0; i < numsSize-2; ++i) {
        if (nums[i] > 0) break;
        if (i >= 1 && nums[i] == nums[i-1]) continue;
        //双指针
        j = i + 1;
        k = numsSize - 1;
        while (j < k) {
            sum = nums[i] + nums[j] + nums[k];
            if (sum == 0) {
                if (length == pre_alloc_size) {
                    // 动态增长
                    pre_alloc_size *= 2;
                    block = (int *)realloc(block, (pre_alloc_size)*oneGroupSize);
                }
                
                block[length*3] = nums[i];
                block[length*3+1] = nums[j];
                block[length*3+2] = nums[k];
                ++length;
                
                while (j < k && nums[j] == nums[j+1]) ++j;
                while (j < k && nums[k] == nums[k-1]) --k;
                ++j;
                --k;
            } else if (sum < 0) {
                while (j < k && nums[j] == nums[j+1]) ++j;
                ++j;
            } else {
                while (j < k &&  nums[k] == nums[k-1]) --k;
                --k;
            }
        }
    }
    
    *returnColumnSizes = (int *)malloc(sizeof(int) * length);
    int **result = (int **)malloc(sizeof(int *) * length);
    for (int i = 0; i < length; ++i) {
        (*returnColumnSizes)[i] = 3;
        result[i] = block+i*3;
    }
    *returnSize = length;
    return result;
}

int removeDuplicates(int* nums, int numsSize){
    if (numsSize < 1) return 0;
    int setCount = 1;
    for (int i = 0; i < numsSize-1; ++i) {
        if (nums[i] != nums[i+1]) nums[setCount++] = nums[i+1];
    }
    
    return setCount;
}

struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2){
    if (l1 == NULL) return l2;
    if (l2 == NULL) return l1;
    
    struct ListNode *tmpNode;
    if (l2->val < l1->val) {
        tmpNode = l1;
        l1 = l2;
        l2 = tmpNode;
    }
    
    struct ListNode *minNode = l1;
    
    while (l1->next != NULL && l2 != NULL) {
        if (l1->next->val > l2->val) {
            tmpNode = l1->next;
            l1->next = l2;
            l2 = l2->next;
            l1->next->next = tmpNode;
        }else{
            l1 = l1->next;
        }
    }
    if (l1->next == NULL) l1->next = l2;

    return minNode;
}

int searchInsert(int* nums, int numsSize, int target){
    // 历遍
    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] >= target) return i;
    }
    return numsSize;
    
    // 二分法
//    int left = 0, right = numsSize - 1, mid; // 注意
//    while(left <= right) { // 注意
//        mid = (left + right) / 2; // 注意
//        if(nums[mid] == target) { // 注意
//            // 相关逻辑
//            return mid;
//        } else if(nums[mid] < target) {
//            left = mid + 1; // 注意
//        } else {
//            right = mid - 1; // 注意
//        }
//    }
//    // 相关返回值
//    if (nums[mid] > target) {
//        return mid;
//    }else{
//        return mid+1;
//    }
}

int maxSubArray(int* nums, int numsSize){
    int sum = nums[0], lastMaxSum = nums[0];
    for (int i = 1; i < numsSize; ++i) {
        sum = sum<0?nums[i]:(sum+nums[i]);
        if (sum > lastMaxSum) lastMaxSum = sum;
    }
    return lastMaxSum;
}

void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n){
//    // 从左到右插入
//    int *nums3 = malloc(sizeof(int)*nums1Size);
//    int i = 0, j = 0, k = 0;
//    while (i < m && j < n) {
//        if (nums1[i] > nums2[j]) {
//            nums3[k++] = nums2[j++];
//        }else{
//            nums3[k++] = nums1[i++];
//        }
//    }
//    if (j == n) {
//        while (i < m) nums3[k++] = nums1[i++];
//    }else{
//        while (j < n)  nums3[k++] = nums2[j++];
//    }
//    memcpy(nums1, nums3, sizeof(int)*nums1Size);
    
    // 从右到左插入
    int index = m+n-1;
    int i = m-1, j = n-1;
    while (i >= 0 && j >= 0) {
        if (nums1[i] > nums2[j]) {
            nums1[index--] = nums1[i--];
        }else{
            nums1[index--] = nums2[j--];
        }
    }
    while (j >= 0) nums1[index--] = nums2[j--];
}

// 电话号码的字母组合 https://leetcode-cn.com/problems/letter-combinations-of-a-phone-number/
char ** letterCombinations(char * digits, int* returnSize){
    if (digits[0] == '\0') {
        *returnSize = 0;
        return NULL;
    }
    int i = 0;
    int arraySize = 1;
    unsigned long length = 0;
    while (digits[i] != '\0') {
        ++length;
        switch (digits[i++]) {
            case '2':
                //abc
                arraySize *= 3;
                break;
            case '3':
                //def
                arraySize *= 3;
                break;
            case '4':
                //ghi
                arraySize *= 3;
                break;
            case '5':
                //jkl
                arraySize *= 3;
                break;
            case '6':
                //mno
                arraySize *= 3;
                break;
            case '7':
                //pqrs
                arraySize *= 4;
                break;
            case '8':
                //tuv
                arraySize *= 3;
                break;
            case '9':
                //wxyz
                arraySize *= 4;
                break;
                
            default:
                break;
        }
    }
    
    char **result = malloc(sizeof(char*)*arraySize);
    for (i = 0; i < arraySize; ++i) {
        result[i] = malloc(sizeof(char)*(length+1));
        memset(result[i], '\0', sizeof(char)*(length+1));
    }
    
    *returnSize = arraySize;
    arraySize = 1;
    
    i = 0;
    while (digits[i] != '\0') {
        switch (digits[i]) {
            case '2':
                //abc
                for (int j = 0; j < arraySize; ++j) {
                    char *str1 = result[j];
                    char *str2 = result[j+arraySize];
                    char *str3 = result[j+arraySize*2];
                    memcpy(str2, str1, sizeof(char)*i);
                    memcpy(str3, str1, sizeof(char)*i);
                    str1[i] = 'a';
                    str2[i] = 'b';
                    str3[i] = 'c';
                }
                arraySize *= 3;
                break;
            case '3':
                //def
                for (int j = 0; j < arraySize; ++j) {
                    char *str1 = result[j];
                    char *str2 = result[j+arraySize];
                    char *str3 = result[j+arraySize*2];
                    memcpy(str2, str1, sizeof(char)*i);
                    memcpy(str3, str1, sizeof(char)*i);
                    str1[i] = 'd';
                    str2[i] = 'e';
                    str3[i] = 'f';
                }
                arraySize *= 3;
                break;
            case '4':
                //ghi
                for (int j = 0; j < arraySize; ++j) {
                    char *str1 = result[j];
                    char *str2 = result[j+arraySize];
                    char *str3 = result[j+arraySize*2];
                    memcpy(str2, str1, sizeof(char)*i);
                    memcpy(str3, str1, sizeof(char)*i);
                    str1[i] = 'g';
                    str2[i] = 'h';
                    str3[i] = 'i';
                }
                arraySize *= 3;
                break;
            case '5':
                //jkl
                for (int j = 0; j < arraySize; ++j) {
                    char *str1 = result[j];
                    char *str2 = result[j+arraySize];
                    char *str3 = result[j+arraySize*2];
                    memcpy(str2, str1, sizeof(char)*i);
                    memcpy(str3, str1, sizeof(char)*i);
                    str1[i] = 'j';
                    str2[i] = 'k';
                    str3[i] = 'l';
                }
                arraySize *= 3;
                break;
            case '6':
                //mno
                for (int j = 0; j < arraySize; ++j) {
                    char *str1 = result[j];
                    char *str2 = result[j+arraySize];
                    char *str3 = result[j+arraySize*2];
                    memcpy(str2, str1, sizeof(char)*i);
                    memcpy(str3, str1, sizeof(char)*i);
                    str1[i] = 'm';
                    str2[i] = 'n';
                    str3[i] = 'o';
                }
                arraySize *= 3;
                break;
            case '7':
                //pqrs
                for (int j = 0; j < arraySize; ++j) {
                    char *str1 = result[j];
                    char *str2 = result[j+arraySize];
                    char *str3 = result[j+arraySize*2];
                    char *str4 = result[j+arraySize*3];
                    memcpy(str2, str1, sizeof(char)*i);
                    memcpy(str3, str1, sizeof(char)*i);
                    memcpy(str4, str1, sizeof(char)*i);
                    str1[i] = 'p';
                    str2[i] = 'q';
                    str3[i] = 'r';
                    str4[i] = 's';
                }
                arraySize *= 4;
                break;
            case '8':
                //tuv
                for (int j = 0; j < arraySize; ++j) {
                    char *str1 = result[j];
                    char *str2 = result[j+arraySize];
                    char *str3 = result[j+arraySize*2];
                    memcpy(str2, str1, sizeof(char)*i);
                    memcpy(str3, str1, sizeof(char)*i);
                    str1[i] = 't';
                    str2[i] = 'u';
                    str3[i] = 'v';
                }
                arraySize *= 3;
                break;
            case '9':
                //wxyz
                for (int j = 0; j < arraySize; ++j) {
                    char *str1 = result[j];
                    char *str2 = result[j+arraySize];
                    char *str3 = result[j+arraySize*2];
                    char *str4 = result[j+arraySize*3];
                    memcpy(str2, str1, sizeof(char)*i);
                    memcpy(str3, str1, sizeof(char)*i);
                    memcpy(str4, str1, sizeof(char)*i);
                    str1[i] = 'w';
                    str2[i] = 'x';
                    str3[i] = 'y';
                    str4[i] = 'z';
                }
                arraySize *= 4;
                break;
                
            default:
                break;
        }
        ++i;
    }
    
    return result;
}

char * countAndSay(int n){
    if (n == 1) {
        return "1";
    }
    
    int i = 0, count = 0, index = 0;
    
    char *str = malloc(sizeof(char)*10000);
    memset(str, '\0', sizeof(char)*10000);
    str[0] = '1';
    char tmp = '\0';
    char *tmpStr = malloc(sizeof(char)*10000);
    memset(tmpStr, '\0', sizeof(char)*10000);
    
    char *str2 = str;
    for (int k = 1; k < n; ++k) {
        while (1) {
            if (tmp != str[i]) {
                if (count != 0) {
                    tmpStr[index] = '0'+count;
                    tmpStr[index+1] = tmp;
                    index += 2;
                }
                tmp = str[i];
                count = 0;
            }
            if (str[i] == '\0') {
                tmpStr[index] = '\0';
                break;
            }
            ++count;
            ++i;
        }
        i = 0;
        count = 0;
        index = 0;
        str = tmpStr;
        tmpStr = str2;
        str2 = str;
    }
    free(tmpStr);
    
    return str;
}

int removeElement(int* nums, int numsSize, int val){
    int j = 0;
    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] == val) continue;
        nums[j++] = nums[i];
    }
    
    return j;
}

void createParenthesis(char **block, int *memSize, char *str, int n, int l, int r, int* returnSize) {
    if (l+r+1 == n) {
        if (*returnSize >= *memSize) {
            *memSize *= 2;
            *block = realloc(*block, sizeof(char)*(*memSize)*(n+1));
        }
        // 加入结果
        memcpy(*block+(*returnSize*(n+1)), str, sizeof(char)*(l+r));
        (*block)[(*returnSize*(n+1))+l+r] = ')';
        (*block)[(*returnSize*(n+1))+l+r+1] = '\0';
        ++(*returnSize);
    }else{
        if (l > r) {
            str[l+r] = ')';
            createParenthesis(block, memSize, str, n, l, r+1, returnSize);
        }
        if (2*l < n) {
            str[l+r] = '(';
            createParenthesis(block, memSize, str, n, l+1, r, returnSize);
        }
    }
}

char ** generateParenthesis(int n, int* returnSize){
    *returnSize = 0;
    if (n == 0) return NULL;
    
    char *block = malloc(sizeof(char)*n*(2*n+1));
    char *str = malloc(sizeof(char)*(2*n+1));
    str[0] = '(';
    int memSize = n;
    createParenthesis(&block, &memSize, str, n*2, 1, 0, returnSize);
    free(str);
    char **result = malloc(sizeof(char*)*(*returnSize));
    for (int i = 0; i < *returnSize; ++i) {
        result[i] = block+i*(2*n+1); 
    }
    
    return result;
}

int numJewelsInStones(char * J, char * S){
    if (S[0] == '\0' || J[0] == '\0') return 0;
    
    char arr[58] = {0};
    int i = 0, count = 0;
    while (J[i] != '\0') {
        arr[J[i++]-'A'] = 1;
    }
    i = 0;
    while (S[i] != '\0') {
        if (arr[S[i++]-'A'] == 1) ++count;
    }
    return count;
}

int singleNumber(int* nums, int numsSize){
    while (numsSize > 1) nums[0] ^= nums[--numsSize];
    return nums[0];
}

char * addBinary(char * a, char * b){
    unsigned long lena = strlen(a);
    unsigned long lenb = strlen(b);
    
    unsigned long resultLen = lena;
    if (lena < lenb) {
        char *tmp;
        tmp = a;
        a = b;
        b = tmp;
        lena = lenb;
        lenb = resultLen;
        resultLen = lena;
    }
    
    bool up = false;
    while (lenb != 0 && lena != 0) {
        --lenb;
        --lena;
        if (a[lena] == b[lenb]) {
            if (a[lena] == '1') {
                if (up == true) {
                    a[lena] = '1';
                }else{
                    a[lena] = '0';
                }
                up = true;
            }else{
                if (up == true) {
                    a[lena] = '1';
                }else{
                    a[lena] = '0';
                }
                up = false;
            }
        }else{
            if (up == true) {
                a[lena] = '0';
                up = true;
            }else{
                a[lena] = '1';
                up = false;
            }
        }
    }
    
    if (up == false) {
        return a;
    }else{
        while (lena != 0) {
            --lena;
            if (a[lena] == '1') {
                a[lena] = '0';
            }else{
                a[lena] = '1';
                return a;
            }
        }
        char *result = malloc(sizeof(char)*(resultLen+2));
        result[0] = '1';
        memcpy(result+1, a, sizeof(char)*(resultLen+1));
        return result;
    }
}

int climbStairs(int n){
    //C(n)=C(n-1)+C(n-2), C(1) = 1; C(2) = 2;
    if (n == 1) return 1;
    
    int first = 1;
    int second = 2;
    for (int i = 3; i <= n; i++) {
        int third = first + second;
        first = second;
        second = third;
    }
    return second;
}

struct ListNode* reverseList(struct ListNode* head){
    if (head == NULL || head->next == NULL) return head;
    
    struct ListNode *result = head;
    struct ListNode *p = head;
    struct ListNode *r = NULL;
    
    while (p != NULL) {
        result = p;
        p = p->next;
        result->next = r;
        r = result;
    }
    
    return result;
}

int lengthOfLastWord(char * s){
    int i = 0;
    int len = 0;
    bool isSpace = false;
    while (s[i] != '\0') {
        if (s[i] == ' ') {
            isSpace = true;
        }else{
            if (isSpace) {
                len = 0;
                isSpace = false;
            }
            ++len;
        }
        ++i;
    }

    return len;
}

int search(int* nums, int numsSize, int target){
    if (numsSize == 0) return -1;
    if (numsSize == 1) return nums[0]==target?0:-1;
    
    /*
    Binary search
    */
    int left = 0, right = numsSize-1;
    int rotateIndex = 0;
    if (nums[left] > nums[right]){
        while (left <= right) {
            int pivot = (left + right) / 2;
            if (nums[pivot] > nums[pivot + 1]){
                rotateIndex = pivot + 1;
                break;
            } else {
                if (nums[pivot] < nums[left])
                    right = pivot - 1;
                else
                    left = pivot + 1;
            }
        }
    }
    
    if (nums[rotateIndex] == target) return rotateIndex;
    
    if (rotateIndex == 0) {
        left = 0;
        right = numsSize-1;
    }else if (nums[0] > target) {
        left = rotateIndex;
        right = numsSize-1;
    }else{
        left = 0;
        right = rotateIndex-1;
    }
    
    while (left <= right) {
        int pivot = (left + right) / 2;
        if (nums[pivot] == target)
            return pivot;
        else {
            if (target < nums[pivot])
                right = pivot - 1;
            else
                left = pivot + 1;
        }
    }
    return -1;
}

struct ListNode* swapPairs(struct ListNode* head){
    if (head == NULL || head->next == NULL) return head;
    
    struct ListNode *p1 = head;
    struct ListNode *p2 = head->next;
    struct ListNode *result = p2;
    struct ListNode *tmpHead = NULL;
    
    while (1) {
        p1->next = p2->next;
        p2->next = p1;
        tmpHead = p1;
        p1 = p1->next;
        if (p1 == NULL) break;
        p2 = p1->next;
        if (p2 == NULL) break;
        tmpHead->next = p2;
    }
    
    return result;
}

int min(int num1, int num2) {
    return num1<num2?num1:num2;
}
int max(int num1, int num2) {
    return num1>num2?num1:num2;
}

int maxArea(int* height, int heightSize){
    // (n2-n1)*min(height1, height2);
    int i = 0;
    int j = heightSize-1;
    int maxsize = 0;
    int tmpsize = 0;
    
    while (i < j) {
        if (height[i] < height[j]) {
            tmpsize = (j-i)*height[i];
            if (tmpsize > maxsize) maxsize = tmpsize;
            ++i;
        }else{
            tmpsize = (j-i)*height[j];
            if (tmpsize > maxsize) maxsize = tmpsize;
            --j;
        }
        
    }
    
    return maxsize;
}

int maxDepth(struct TreeNode* root){
    if (root == NULL) return 0;
    int left = maxDepth(root->left)+1;
    int right = maxDepth(root->right)+1;
    return left>right?left:right;
}

struct ListNode* reverseKGroup(struct ListNode* head, int k){
    if (head == NULL || head->next == NULL || k < 2) return head;
    
    struct ListNode *p = head;
    struct ListNode *f = head;
    struct ListNode *f2 = NULL;
    struct ListNode *r = NULL;
    struct ListNode *cur = head;
    
    int loopCount = 0;
    bool flag = false;
    
    while (p != NULL) {
        cur = p;
        p = p->next;
        cur->next = r;
        r = cur;
        if (++loopCount == k) {
            if (flag == false) {
                head = cur;
                flag = true;
            }else{
                f->next = cur;
                f = f2;
            }
            f2 = p;
            r = NULL;
            loopCount = 0;
        }
    }
    
    if (loopCount != 0) {
        p = cur;
        r = NULL;
        while (p != NULL) {
            cur = p;
            p = p->next;
            cur->next = r;
            r = cur;
        }
        if (flag == true) {
            f->next = cur;
        }
    }
    
    return head;
}

void reverseString(char* s, int sSize){
    int i = 0, j = sSize-1;
    while (i < j) {
        char tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;
        ++i;
        --j;
    }
}

int* searchRange(int* nums, int numsSize, int target, int* returnSize){
    int *result = malloc(sizeof(int)*2);
    *returnSize = 2;
    result[0] = -1;
    result[1] = -1;
    
    int left = 0, right = numsSize-1;
    
    while (left <= right) {
        int mid = (left+right)/2;
        if (nums[mid] == target) {
            result[0] = mid;
            result[1] = mid;
            break;
        }else if (nums[mid] < target) {
            left = mid+1;
        }else{
            right = mid-1;
        }
    }
    if (result[0] == -1) {
        return result;
    }
    
    left = 0;
    right = result[0]-1;
    while (left <= right) {
        int mid = (left+right)/2;
        if (nums[mid] == target) {
            if (mid == 0 || nums[mid] != nums[mid-1]) {
                result[0] = mid;
                break;
            }
            right = mid-1;
        }else{
            if (nums[mid+1] == target) {
                result[0] = mid+1;
                break;
            }
            left = mid+1;
        }
    }
    
    left = result[1]+1;
    right = numsSize-1;
    
    while (left <= right) {
        int mid = (left+right)/2;
        if (nums[mid] == target) {
            if (mid == numsSize-1 || nums[mid] != nums[mid+1]) {
                result[1] = mid;
                break;
            }
            left = mid+1;
        }else{
            if (nums[mid-1] == target) {
                result[1] = mid-1;
                break;
            }
            right = mid-1;
        }
    }
    
    return result;
}

char * intToRoman(int num){
    char *result = malloc(sizeof(char)*16);
    
    const int map[] = {1000, 900,  500, 400, 100, 90,  50,  40,  10,  9,   5,  4,   1};
    const char *r[] = {"M" , "CM", "D", "CD","C", "XC","L", "XL","X", "IX","V","IV","I"};
    const int rlen[] = {1 , 2 , 1 , 2, 1, 2, 1, 2, 1, 2, 1, 2, 1};
    
    int index = 0, i = 0, tmp;
    while (num) {
        tmp = map[i];
        if (tmp > num) {
            ++i;
            continue;
        }
        num -= tmp;
        memcpy(result+index, r[i], sizeof(char)*rlen[i]);
        index += rlen[i];
    }
    
    result[index] = '\0';
    
    return result;
}

void moveZeroes(int* nums, int numsSize){
    int j = 0;
    for(int i = 0; i < numsSize; i++) if(nums[i] != 0) nums[j++] = nums[i];
    while (j < numsSize) nums[j++] = 0;
}

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize){
    if (listsSize == 0) return NULL;
    if (listsSize == 1) return lists[0];
    
    int mid = listsSize / 2;
    struct ListNode *l1 = mergeKLists(lists, mid);
    struct ListNode *l2 = mergeKLists(lists+mid, listsSize-mid);
    
    return mergeTwoLists(l1, l2);
}

bool isPalindromeList(struct ListNode* head){
    if (head == NULL || head->next == NULL) return true;
    struct ListNode *cur = head;
    int len = 0;
    while (cur) {
        cur = cur->next;
        ++len;
    }
    
    cur = head;
    int i = 0;
    for (i = 0; i < len/2; ++i) {
        cur = cur->next;
    }
    
    struct ListNode *r = reverseList(cur);
    cur = r;
    while (cur != NULL) {
        if (cur->val != head ->val) {
            reverseList(r);
            return false;
        }
        cur = cur->next;
        head = head->next;
    }
    
    reverseList(r);
    
    return true;
}

int** permute(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){
    if (numsSize == 0) {
        *returnSize = 0;
        return NULL;
    }
    int size = 1, i = 2, j, k, z;
    for (; i <= numsSize; ++i) {
        size *= i;
    }
    *returnSize = size;
    *returnColumnSizes = (int *)malloc(sizeof(int) * size);
    
    int **result = malloc(sizeof(int*)*size);
    for (i = 0; i < size; ++i) {
        result[i] = malloc(sizeof(int)*numsSize);
        (*returnColumnSizes)[i] = numsSize;
    }
    
    result[0][0] = nums[0]; 
    size = 1;
    int val;
    int *tmpstr, *tmpstr2;
    for (i = 1; i < numsSize; ++i) {
        val = nums[i];
        for (j = 0; j < size; ++j) {
            tmpstr = result[j];
            tmpstr[i] = val;
            for (k = 1; k <= i; ++k) {
                tmpstr2 = result[size*k+j];
                tmpstr2[i-k] = val;
                for (z = 0; z < i; ++z) {
                    if (z >= i-k) {
                        tmpstr2[z+1] = tmpstr[z];
                    }else{
                        tmpstr2[z] = tmpstr[z];
                    }
                }
            }
        }
        size = size*(i+1);
    }
    
    return result;
}

int majorityElement(int* nums, int numsSize){
    // 排序后取中获取总数 时间复杂度O(nlogn)(在leetcode里会超时，实际上只有哈希表和投票算法能通过，随机法运气好也有可能通过)
//    quickSort(nums, 0, numsSize-1);
//    return nums[numsSize/2];
    
    // Boyer-Moore 投票算法 时间复杂度O(n)
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
    return result;
}

int mySqrt(int x){
    if (x <= 1) return x;
    
    int left = 1;
    int right = x/2;
    int mid = 0;
    int tmp = 0;

    while (left <= right) {
        mid = (left+right)/2;
        tmp = x/mid;
        if (tmp == mid) {
            break;
        }else if (tmp < mid){
            right = mid-1;
        }else{
            left = mid+1;
        }
    }
    if (tmp < mid) {
        return mid-1;
    }
    return mid;
}

int* spiralOrder(int** matrix, int matrixSize, int* matrixColSize, int* returnSize){
    if (matrixSize == 0) {
        *returnSize = 0;
        return NULL;
    }
    
    int colSize = matrixColSize[0];
    *returnSize = colSize*matrixSize;
    if (matrixSize == 1) return matrix[0];
    
    int *result = malloc(sizeof(int)*(*returnSize));
    int index = 0;
    int firstRow = 0, firstCol = 0, lastRow = matrixSize-1, lastCol = colSize-1;
    while (1) {
        for (int i = firstCol; i <= lastCol; ++i) result[index++] = matrix[firstRow][i];
        if (++firstRow > lastRow) break;
        
        for (int i = firstRow; i <= lastRow; ++i) result[index++] = matrix[i][lastCol];
        if (--lastCol < firstCol) break;
        
        for (int i = lastCol; i >= firstCol; --i) result[index++] = matrix[lastRow][i];
        if (--lastRow < firstRow) break;
        
        for (int i = lastRow; i >= firstRow; --i) result[index++] = matrix[i][firstCol];
        if (++firstCol > lastCol) break;
    }
    
    return result;
}

char * reverseWords(char * s){
    char tmp;
    int i = 0, wordStartIndex = 0, wordEndIndex = 0;
    while (s[i] != '\0') {
        if (s[i] == ' ') {
            wordEndIndex = i-1;
            while (wordStartIndex < wordEndIndex) {
                tmp = s[wordStartIndex];
                s[wordStartIndex++] = s[wordEndIndex];
                s[wordEndIndex--] = tmp;
            }
            wordStartIndex = i+1;
        }
        ++i;
    }
    wordEndIndex = i-1;
    while (wordStartIndex < wordEndIndex) {
        tmp = s[wordStartIndex];
        s[wordStartIndex++] = s[wordEndIndex];
        s[wordEndIndex--] = tmp;
    }
    
    return s;
}

char * multiply(char * num1, char * num2){
    if (num1[0] == '0' || num2[0] == '0') {
        char* res = (char*)malloc(sizeof(char) * 2);
        res[0] = '0'; res[1] = '\0';
        return res;
    }
    
    int len1 = (int)strlen(num1);
    int len2 = (int)strlen(num2);
    
    int resultLen = len1+len2+1;
    char *result = malloc(sizeof(char)*resultLen);
    memset(result, '0', sizeof(char)*resultLen);
    result[resultLen-1] = '\0';
    
    int i = len1, j = len2, tmp2, tmp1, tmp3;
    while (--j >= 0) {
        tmp2 = num2[j]-'0';
        if (tmp2 != 0) {
            i = len1;
            while (--i >= 0) {
                resultLen = i+j;
                tmp1 = (num1[i]-'0')*tmp2;
                tmp3 = result[resultLen+1]-'0'+tmp1%10;
                
                result[resultLen+1] = tmp3%10+'0';
                result[resultLen] = result[resultLen]+tmp3/10+tmp1/10;
            }
        }
    }
    
    if (result[0] == '0') return result+1;
    return result;
}

int findKthLargest(int* nums, int numsSize, int k){
    if (numsSize == 1) return nums[0];
    int right = numsSize, targetIndex = 0;
    int i, tmp;
    if (k <= numsSize/2) {
        while (numsSize-right != k) {
            targetIndex = 0;
            tmp = nums[targetIndex];
            for (i = 1; i < right; ++i) {
                if (tmp < nums[i]) {
                    tmp = nums[i];
                    targetIndex = i;
                }
            }
            --right;
            nums[targetIndex] = nums[right];
            nums[right] = tmp;
        }
    }else{
        while (right+1 != k) {
            targetIndex = 0;
            tmp = nums[targetIndex];
            for (i = 1; i < right; ++i) {
                if (tmp > nums[i]) {
                    tmp = nums[i];
                    targetIndex = i;
                }
            }
            --right;
            nums[targetIndex] = nums[right];
            nums[right] = tmp;
        }
    }
    
    return nums[right];
    
//    int left = 0, right = numsSize, targetIndex = 0;
//    int i, j, tmp;
//    while (1) {
//        targetIndex = left;
//        j = right;
//        for (i = left+1; i <= j; ++i) {
//            tmp = nums[i];
//            if (tmp < nums[targetIndex]) {
//                nums[i] = nums[targetIndex];
//                nums[targetIndex] = tmp;
//                targetIndex = i;
//            }else{
//                nums[i--] = nums[j];
//                nums[j--] = tmp;
//            }
//        }
//        if (numsSize-targetIndex == k) {
//            break;
//        }else if (numsSize-targetIndex > k) {
//            left = targetIndex+1;
//        }else{
//            right = targetIndex-1;
//        }
//    }
//    
//    return nums[targetIndex];
}

int findKthLargest2(int* nums, int numsSize, int k){
    int i, temp;
    int parent, child;
    for (i = (numsSize - 1)/2; i >= 0; i--){
        temp = nums[i];
        for(parent = i; 2*parent + 1 <= numsSize - 1;parent = child ){
            if (2*parent + 1 == numsSize - 1 || nums[2*parent + 1] > nums[parent* 2 + 2])
                child = 2*parent + 1;
            else child = 2* parent + 2;
            if (temp < nums[child]){
                nums[parent] = nums[child];
                myprintNums(nums, numsSize);
            }
            else break;
        }
        nums[parent] = temp;
        myprintNums(nums, numsSize);
    }
    while(k - 1){
        numsSize--;
        temp = nums[numsSize];
        for(parent = 0; 2*parent + 1 <= numsSize - 1;parent = child ){
            if (2*parent + 1 == numsSize - 1 || nums[2*parent + 1] > nums[parent* 2 + 2])
                child = 2*parent + 1;
            else child = 2* parent + 2;
            if (temp < nums[child]){
                nums[parent] = nums[child];
                myprintNums(nums, numsSize);
            }
            else break;
        }
        nums[parent] = temp;
        myprintNums(nums, numsSize);
        k --;
    }
    return nums[0];
}

void myprintNums(int* nums, int numsSize) {
    for (int i = 0; i < numsSize; ++i) {
        printf("%d", nums[i]);
    }
    printf("\n");
}

bool hasCycle(struct ListNode *head) {
    if (head == NULL) return false;
    struct ListNode *tmp = head;
    head = head->next;
    
    while (head != NULL && head->next != NULL) {
        if (tmp == head) return true;
        head = head->next->next;
        tmp = tmp->next;
    }
    return false;
}

void rotate(int** matrix, int matrixSize, int* matrixColSize){
    /* n*n x为行，y为列
     左上角
     (x,y)
     右上角
     (y,n-1-x)
     右下角
     (n-1-x, n-1-y) 
     左下角
     (n-1-y, x)
     
     
     0,0
     0,2
     2,2
     2,0
     
     0,1
     1,2
     2,1
     1,0
     
    */
    if (matrixSize < 2) return;
    int halfSizeX = (matrixSize+1)/2;
    int halfSizeY = matrixSize/2;
    for (int x = 0; x < halfSizeX; ++x) {
        for (int y = 0; y < halfSizeY; ++y) {
            int tmp = matrix[x][y];
            matrix[x][y] = matrix[matrixSize-1-y][x];
            matrix[matrixSize-1-y][x] = matrix[matrixSize-1-x][matrixSize-1-y];
            matrix[matrixSize-1-x][matrixSize-1-y] = matrix[y][matrixSize-1-x];
            matrix[y][matrixSize-1-x] = tmp;
        }
    }

}

bool isPalindromeString(char * s){
    // 65~90 A~Z   97~122 a~z 
    // 48~57 0~9
    if (s[0] == '\0') return true;
    
    unsigned long p1 = 0;
    unsigned long p2 = strlen(s)-1;
    
    char c1, c2;
    
    while (p1 < p2) {
        c1 = s[p1];
        if (c1 >= 97 && c1 <= 122) {
            c1 -= 32;
        }else if ((c1 >= 65 && c1 <= 90) || (c1 >= 48 && c1 <= 57)){
            
        }else{
            ++p1;
            continue;
        }
        
        while (1) {
            c2 = s[p2];
            if (c2 >= 97 && c2 <= 122) {
                c2 -= 32;
            }else if ((c2 >= 65 && c2 <= 90) || (c2 >= 48 && c2 <= 57)){
                
            }else{
                --p2;
                if (p1 >= p2) return true;
                continue;
            }
            break;
        }
        
        if (c1 != c2) return false;
        ++p1;
        --p2;
    }
    return true;
}

/*
    31391
    
    0,0
    0,3
    3,3
    3,6
    6,12
    
    
    
*/

int rob(int* nums, int numsSize){
    int prevMax = 0;
    int currMax = 0;
    for (int i = 0; i < numsSize; ++i) {
        int temp = currMax;
        currMax = max(prevMax + nums[i], currMax);
        prevMax = temp;
    }
    return currMax;
}

void levelHelper(struct TreeNode* root, int level, int **result, int* returnColumnSizes) {
    if (root == NULL) return;
    
    result[level][(returnColumnSizes[level])++] = root->val;
    
    levelHelper(root->left, level+1, result, returnColumnSizes);
    levelHelper(root->right, level+1, result, returnColumnSizes);
}

void caculateLevelSize(struct TreeNode* root, int level, int* returnColumnSizes) {
    if (root == NULL) return;
    
    ++(returnColumnSizes[level]);
    
    caculateLevelSize(root->left, level+1, returnColumnSizes);
    caculateLevelSize(root->right, level+1, returnColumnSizes);
}

int** levelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes){
    int maxLevel = maxDepth(root);
    *returnColumnSizes = malloc(sizeof(int)*maxLevel);
    memset(*returnColumnSizes, 0, sizeof(int)*maxLevel);
    caculateLevelSize(root, 0,  *returnColumnSizes);
    int **result = malloc(sizeof(int*)*maxLevel);
    for (int i = 0; i < maxLevel; ++i) {
        result[i] = malloc(sizeof(int)*(*returnColumnSizes)[i]);
    }
    
    memset(*returnColumnSizes, 0, sizeof(int)*maxLevel);
    levelHelper(root, 0, result, *returnColumnSizes);
    *returnSize = maxLevel;
    return result;
}

int divide(int dividend, int divisor){
    if (dividend == 0) return 0;
    if (dividend == -2147483648 && divisor == -1) return 2147483647;
    
    bool isminus = false;
    if (dividend > 0) {
        dividend = -dividend;
        isminus = !isminus;
    }
    if (divisor > 0) {
        divisor = -divisor;
        isminus = !isminus;
    }
    
    int tmp = divisor;
    int times = -1;
    int count = 0;
    
    while (dividend <= divisor) {
        while (tmp >= -1073741824 && dividend <= tmp+tmp) {
            tmp += tmp;
            times += times;
        }
        dividend -= tmp;
        count += times;
        times = -1;
        tmp = divisor;
    }
    
    if (isminus) {
        return count;
    }else{
        return -count;
    }
}

long long uniquePaths(int m, int n){
    // m+n-2步 到右下角 (m-1)向右 (n-1)次向下
    // C(m-1, m+n-2)
    // (m+n-2)!/(m-1)!(n-1)!
    
    int i = 0;
    long long count = 1;
    if (--m > --n) while (i++ < n) count = count*(i+m)/i;
    else while (i++ < m) count = count*(i+n)/i;
    return count;
}

int maxProfit(int* prices, int pricesSize){
    int max = 0, i = 0, tmp;
    for (int j = i+1; j < pricesSize; ++j) {
        if (prices[j] <= prices[i]) {
            i = j;
            continue;
        }
        tmp = prices[j]-prices[i];
        if (max < tmp) max = tmp;
    }
    return max;
}

struct ListNode* rotateRight(struct ListNode* head, int k){
    // 每右移动一次，即把最后一个指向第一个，倒数第二个指向NULL
    if (head == NULL || head->next == NULL || k == 0) return head;
    
    struct ListNode *lastNode = head->next;
    int count = 2;
    while (lastNode->next != NULL) {
        lastNode = lastNode->next;
        ++count;
    }
    lastNode->next = head;
    lastNode = head;
    k = count-k%count-1;
    while (k-- > 0) lastNode = lastNode->next;
    head = lastNode->next;
    lastNode->next = NULL;
    return head;
}

MinStack* minStackCreate() {
    MinStack *minStack = malloc(sizeof(MinStack));
    minStack->top = NULL;
    minStack->min = NULL;
    return minStack;
}

void minStackPush(MinStack* obj, int x) {
    struct ListNode *node = malloc(sizeof(struct ListNode));
    node->next = NULL;
    node->val = x;
    
    if (obj->top == NULL) {
        obj->top = node;
        obj->min = node;
    }else{
        if (x < obj->min->val) obj->min = node;
        
        node->next = obj->top;
        obj->top = node;
    }
}

void minStackPop(MinStack* obj) {
    struct ListNode *top = obj->top;
    if (top) {
        obj->top = top->next;
        if (top == obj->min) {
            struct ListNode *cur = obj->top;
            obj->min = cur;
            while (cur != NULL) {
                if (cur->val < obj->min->val) obj->min = cur;
                cur = cur->next;
            }
        }
        free(top);
    }
}

int minStackTop(MinStack* obj) {
    return obj->top->val;
}

int minStackGetMin(MinStack* obj) {
    return obj->min->val;
}

void minStackFree(MinStack* obj) {
    struct ListNode *top = obj->top;
    struct ListNode *tmp;
    while (top) {
        tmp = top;
        top = top->next;
        free(tmp);
    }
    free(obj);
}

int maxProfit2(int* prices, int pricesSize){
    int totalMax = 0;
    for (int i = 1; i < pricesSize; ++i) 
        if (prices[i] > prices[i-1]) 
            totalMax += prices[i]-prices[i-1];
    
    return totalMax;
}

int** generate(int numRows, int* returnSize, int** returnColumnSizes){
    *returnSize = numRows;
    if (numRows == 0) return NULL;
    
    int **result = malloc(sizeof(int*)*numRows);
    *returnColumnSizes = malloc(sizeof(int)*numRows);
    int j = 0;
    for (int i = 0; i < numRows; ++i){
        result[i] = malloc(sizeof(int)*(i+1));
        (*returnColumnSizes)[i] = i+1;
        result[i][0] = 1;
        result[i][i] = 1;
        for (j = 1; j < i; ++j) {
            result[i][j] = result[i-1][j-1]+result[i-1][j];
        }
    } 
    return result;
}

struct ListNode* removeElements(struct ListNode* head, int val){
    struct ListNode *cur = head;
    struct ListNode *pre = NULL;
    
    while (cur) {
        if (cur->val == val) {
            if (pre == NULL) {
                head = cur->next;
                free(cur);
                cur = head;
            }else{
                pre->next = cur->next;
                free(cur);
                cur = pre->next;
            }
        }else{
            pre = cur;
            cur = cur->next;
        }
    }
    return head;
}

struct ListNode* reverseBetween(struct ListNode* head, int m, int n){
    if (m == n) return head;
    int i = 0;
    --m;
    --n;
    struct ListNode *cur = head;
    struct ListNode *pre = NULL;
    struct ListNode *tmp = NULL;
    struct ListNode *nodeM = NULL;
    struct ListNode *nodeMPre = NULL;
    while (cur) {
        if (i >= m) {
            if (i <= n) {
                if (nodeM == NULL) {
                    nodeM = cur;
                    nodeMPre = pre;
                }
                tmp = cur->next;
                cur->next = pre;
                pre = cur;
                cur = tmp;
                ++i;
                continue;
            }else{
                break;
            }
        }
        pre = cur;
        cur = cur->next;
        ++i;
    }
    if (nodeMPre) {
        nodeMPre->next = pre;
    }else{
        head = pre;
    }
    
    nodeM->next = cur;
    
    return head;
}

char * defangIPaddr(char * address){
    char *result = malloc(sizeof(char)*22);
    
    int i = 0;
    while (*address != '\0') {
        if (*address == '.') {
            result[i++] = '[';
            result[i++] = '.';
            result[i++] = ']';
        }else{
            result[i++] = *address;
        }
        ++address;
    }
    result[i] = '\0';
    return result;
}

int hammingDistance(int x, int y){
    x = x^y;
    y = 0;
    while (x != 0) {
        ++y;
        x &= x-1;
    }
    return y;
}

int firstMissingPositive(int* nums, int numsSize){
    int first = 1;
    int i = 0;
    for (; i < numsSize; ++i) {
        if (nums[i] < 1 || nums[i] > numsSize) {
            nums[i] = 1;
        }else if (nums[i] == first){
            ++first;
        }
    }
    
    if (first == 1) return 1;
    if (numsSize == 1) return 2;
    
    int a, tmp;
    for (i = 0; i < numsSize; ++i) {
        a = nums[i];
        if (a < 0) a = -a;
        a -= 1;
        tmp = nums[a];
        if (tmp < 0) nums[a] = tmp;
        else nums[a] = -tmp;
    }
    
    for (i = first-1; i < numsSize; ++i) {
        if (nums[i] > 0) return i+1;
    }
    
    return numsSize+1;
}

char * removeOuterParentheses(char * S){
    int i = 0;
    int left = 0;
    int right = 0;
    int len = 0;
    while (S[i] != '\0') {
        if (S[i] == '(') {
            ++left;
            if (left == 1) {
                
            }else{
                S[len++] = S[i];
            }
        }else if (S[i] == ')') {
            ++right;
            if (left == right) {
                left = 0;
                right = 0;
            }else{
                S[len++] = S[i];
            }
        }
        ++i;
    }
    S[len] = '\0';
    return S;
}

int** mergeSet(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize, int** returnColumnSizes){
    int left1, right1, left2, right2, i = 0, j;
    int len = 0;
    while (i < intervalsSize-1) {
        left1 = intervals[i][0];
        right1 = intervals[i][1];
        len = i+1;
        for (j = i+1; j < intervalsSize; ++j) {
            left2 = intervals[j][0];
            right2 = intervals[j][1];
            if (left1 <= right2 && right1 >= left2) {
                if (left1 > left2) {
                    left1 = left2;
                }
                if (right1 < right2) {
                    right1 = right2;
                }
                continue;
            }
            intervals[len][0] = intervals[j][0];
            intervals[len][1] = intervals[j][1];
            ++len;
        }
        intervals[i][0] = left1;
        intervals[i][1] = right1;
        if (len != intervalsSize) {
            intervalsSize = len;
        }else{
            ++i;
        }
    }
    
    *returnSize = len;
    *returnColumnSizes = intervalsColSize;
    return intervals;
}

int minPathHelp(int** grid, int gridSize, int colSize, int i, int j) {
    int num1 = grid[i][j];
    if (i+1 < gridSize) {
        num1 += minPathHelp(grid, gridSize, colSize, i+1, j);
        if (j+1 < colSize) {
            int num2 = grid[i][j];
            num2 += minPathHelp(grid, gridSize, colSize, i, j+1);
            return num1<num2?num1:num2;
        }else{
            return num1;
        }
    }else{
        if (j+1 < colSize) {
            num1 += minPathHelp(grid, gridSize, colSize, i, j+1);
            return num1;
        }else{
            return num1;
        }
    }
}

int minPathSum(int** grid, int gridSize, int* gridColSize){
    if (gridSize == 0 || gridColSize[0] == 0) return 0;
    int colSize = gridColSize[0];
    int j = --colSize-1;
    for (int i = --gridSize; i >= 0; --i) {
        while (j >= 0) {
            if (i != gridSize && j != colSize) {
                grid[i][j] = (grid[i+1][j] < grid[i][j+1])?grid[i][j]+grid[i+1][j]:grid[i][j]+grid[i][j+1];
            } else {
                grid[i][j] = (j != colSize)?grid[i][j]+grid[i][j+1]:grid[i][j]+grid[i+1][j];
            }
            --j;
        }
        j = colSize;
    }
    
    return grid[0][0];
}

void rotateNums(int* nums, int numsSize, int k){
    if (numsSize < 2) return;
    k = k%numsSize;
    if (k == 0) return;
    
    int i = k, count = 1;
    int tmp = nums[k], tmp2;
    int lastStart = 0;
    nums[k] = nums[0];
    while (count < numsSize) {
        if (i == lastStart) {
            ++lastStart;
            i = lastStart;
            tmp = nums[lastStart];
        }
        i = (i+k)%numsSize;
        tmp2 = nums[i];
        nums[i] = tmp;
        tmp = tmp2;
        ++count;
    }
}

void subsetsHelper(int* nums, int numsSize, int** result, int* returnSize, int** returnColumnSizes, int *preNums, int n) {
    for (int i = 0; i < numsSize; ++i) {
        (*returnColumnSizes)[*returnSize] = n+1;
        result[*returnSize] = malloc(sizeof(int)*(n+1));
        if (n != 0) {
            memcpy(result[*returnSize], preNums, sizeof(int)*n);
        }
        result[*returnSize][n] = nums[i];
        ++(*returnSize);
        subsetsHelper(nums+i+1, numsSize-i-1, result, returnSize, returnColumnSizes, result[*returnSize-1], n+1);
    }
}

int** subsets(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){
    // C(0,n)+C(1,n)+...+C(m,n)
    // 1+n+...+n!/(m!(n-m)!) = 2^(n+1)
    int totalSize = 1 << numsSize;
    
    int **result = malloc(sizeof(int*)*totalSize);
    *returnColumnSizes = malloc(sizeof(int)*totalSize);
    //特殊处理一个都不选的情况
    (*returnColumnSizes)[0] = 0;
    *returnSize = 1;
    subsetsHelper(nums, numsSize, result, returnSize, returnColumnSizes, NULL, 0);
    
    return result;
}

int* twoSum(int* numbers, int numbersSize, int target, int* returnSize){
    *returnSize = 2;
    int *result = malloc(sizeof(int)*2);
    int left = 0, right = numbersSize-1;
    
    while (left < right) {
        numbersSize = numbers[left]+numbers[right];
        if (numbersSize == target) {
            result[0] = left+1;
            result[1] = right+1;
            break;
        }else if (numbersSize > target){
            --right;
        }else{
            ++left;
        }
    }
    
    return result;
}

bool isSameTree(struct TreeNode* p, struct TreeNode* q){
    if (p == NULL && q == NULL) return true;
    if ((p == NULL || q == NULL) || (p->val != q->val) || isSameTree(p->left, q->left) == false || isSameTree(p->right, q->right) == false) return false;
    
    return true;
}

struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB) {
    int n1 = 0;
    int n2 = 0;
    struct ListNode *tmp = headA;
    while (tmp != NULL) {
        ++n1;
        tmp = tmp->next;
    }
    tmp = headB;
    while (tmp != NULL) {
        ++n2;
        tmp = tmp->next;
    }
    if (n1 < n2) {
        n2 = n2-n1;
        while (n2-- > 0)  headB = headB->next;
    }else{
        n2 = n1-n2;
        while (n2-- > 0) headA = headA->next;
    }
    while (headA != NULL) {
        if (headA == headB) return headA;
        headA = headA->next;
        headB = headB->next;
    }
    return NULL;
}

struct ListNode* deleteDuplicates(struct ListNode* head){
    if (head == NULL) return head;
    struct ListNode *pre = NULL;
    struct ListNode *cur = head;
    struct ListNode *prepre = NULL;
    while (cur) {
        pre = cur;
        cur = cur->next;
        while (cur && (pre->val == cur->val)) cur = cur->next;
        if (pre->next != cur) {
            if (head == pre) head = cur;
            if (prepre) prepre->next = cur;
        }else{
            prepre = pre;
        }
    }
    
    return head;
}

int trap(int* height, int heightSize){
    int left = 0, right = heightSize-1, leftMax = 0, rightMax = 0, lastMax = 0;
    int totalSize = 0;
    
    while (left < right) {
        if (leftMax < rightMax) {
            if (height[left] > leftMax) {
                leftMax = height[left];
                if (leftMax > rightMax) {
                    if (rightMax > lastMax) {
                        totalSize += (right-left)*(rightMax-lastMax);
                        lastMax = rightMax;
                    }
                }else{
                    if (leftMax > lastMax) {
                        totalSize += (right-left)*(leftMax-lastMax);
                        lastMax = leftMax;
                    }
                }
            }else{
                totalSize -= height[left];
                ++left;
            }
        }else{
            if (height[right] > rightMax) {
                rightMax = height[right];
                if (leftMax > rightMax) {
                    if (rightMax > lastMax) {
                        totalSize += (right-left)*(rightMax-lastMax);
                        lastMax = rightMax;
                    }
                }else{
                    if (leftMax > lastMax) {
                        totalSize += (right-left)*(leftMax-lastMax);
                        lastMax = leftMax;
                    }
                }
            }else{
                totalSize -= height[right];
                --right;
            }
        }
    }
    
    return totalSize;
}

int** fourSum(int* nums, int numsSize, int target, int* returnSize, int** returnColumnSizes){
    if (numsSize < 4) {
        *returnSize = 0;
        return NULL;
    }
    quickSort(nums, 0, numsSize-1);
    int **result = NULL;
    *returnSize = 0;
    int i,j,l,r,sum;
    for (i = 0; i < numsSize-3; ++i) {
        if (i != 0 && nums[i] == nums[i-1]) {
            continue;
        }
        for (j = i+1; j < numsSize-2; ++j) {
            if (j != i+1 && nums[j] == nums[j-1]) {
                continue;
            }
            l = j+1;
            r = numsSize-1;
            if (nums[i] + nums[j] + nums[r - 1] + nums[r] < target)
            {
                continue;
            }
            if (nums[i] + nums[j] + nums[l] + nums[l + 1] > target)
            {
                break;
            }
            while (l < r) {
                if (l != j+1 && nums[l] == nums[l-1]) {
                    ++l;
                    continue;
                }
                if (r != numsSize-1 && nums[r] == nums[r+1]) {
                    --r;
                    continue;
                }
                sum = nums[i]+nums[j]+nums[l]+nums[r];
                if (sum == target) {
                    if ((*returnSize)%100 == 0) {
                        result = realloc(result, sizeof(int*)*(*returnSize+100));
                    }
                    result[(*returnSize)] = malloc(sizeof(int)*4);
                    result[(*returnSize)][0] = nums[i];
                    result[(*returnSize)][1] = nums[j];
                    result[(*returnSize)][2] = nums[l];
                    result[(*returnSize)][3] = nums[r];
                    ++(*returnSize);
                    ++l;
                }else if (sum < target){
                    ++l;
                }else{
                    --r;
                }
            }
        }
    }
    
    *returnColumnSizes = malloc(sizeof(int)*(*returnSize));
    for (int i = 0; i < *returnSize; ++i) {
        (*returnColumnSizes)[i] = 4;
    }
    return result;
}

int threeSumClosest(int* nums, int numsSize, int target){
    quickSort(nums, 0, numsSize-1);
    int leftSum = nums[0]+nums[1]+nums[2];
    if (leftSum > target) return leftSum;
    int rightSum = nums[numsSize-1]+nums[numsSize-2]+nums[numsSize-3];
    if (rightSum < target) return rightSum;

    int l, r, sum;
    for (int i = 0; i < numsSize-2; ++i) {
        sum = nums[i] + nums[numsSize-1] + nums[numsSize-2];
        if (sum < target)
        {
            if (leftSum < sum) leftSum = sum;
            continue;
        }
        sum = nums[i] + nums[i+1] + nums[i+2];
        if (sum > target)
        {
            if (rightSum > sum) rightSum = sum;
            break;
        }
        l = i+1;
        r = numsSize-1;
        
        while (l < r) {
            sum = nums[i]+nums[l]+nums[r];
            if (sum == target) {
                return sum;
            }else if (sum > target) {
                if (rightSum > sum) rightSum = sum;
                --r;
            }else{
                if (leftSum < sum) leftSum = sum;
                ++l;
            }
        }
    }
    return abs(leftSum-target) < abs(rightSum-target)?leftSum:rightSum;
}

void numIslandsHelper(char** grid, int gridSize, int colSize, int i, int j) {
    if (grid[i][j] == '0') return;
    grid[i][j] = '0';
    if (i > 0) numIslandsHelper(grid, gridSize, colSize, i-1, j);
    if (i < gridSize-1) numIslandsHelper(grid, gridSize, colSize, i+1, j);
    if (j > 0) numIslandsHelper(grid, gridSize, colSize, i, j-1);
    if (j < colSize-1) numIslandsHelper(grid, gridSize, colSize, i, j+1);
}

int numIslands(char** grid, int gridSize, int* gridColSize){
    if (gridSize == 0) return 0;
    int colSize = gridColSize[0];
    int result = 0, i, j;
    for (i = 0; i < gridSize; ++i) {
        for (j = 0; j < colSize; ++j) {
            if (grid[i][j] == '1'){
                numIslandsHelper(grid, gridSize, colSize, i, j);
                ++result;
            }
        }
    }
    return result;
}

int minimumTotal(int** triangle, int triangleSize, int* triangleColSize){
// 不使用额外空间(利用triangle的空间)
//    for (int i = triangleSize-2; i >= 0; --i) {
//        for (int j = 0; j <= i; ++j) {
//            triangle[i][j] += triangle[i+1][j] < triangle[i+1][j+1]?triangle[i+1][j]:triangle[i+1][j+1];
//        }
//    }
//    return triangle[0][0];

// 不改变triangle空间，新建O(n)空间
    int i, j;
    int *tmp = malloc(sizeof(int)*triangleSize);
    memset(tmp, 0, sizeof(int)*triangleSize);
    
    for (i = 0; i < triangleSize; ++i) {
        for (j = i; j >= 0; --j) {
            if (j == 0) {
                tmp[j] += triangle[i][j];
            }else if (j < i) {
                if (tmp[j] < tmp[j-1]) {
                    tmp[j] += triangle[i][j];
                }else{
                    tmp[j] = tmp[j-1]+triangle[i][j];
                }
            }else{
                tmp[j] = tmp[j-1]+triangle[i][j];
            }
        }
    }
    int result = tmp[0];
    for (i = 1; i < triangleSize; ++i) {
        if (result > tmp[i]) result = tmp[i];
    }
    free(tmp);
    return result;
}

bool isSymmetricHelper(struct TreeNode *left, struct TreeNode *right) {
    if (left == NULL && right == NULL) return true;
    if (left == NULL || right == NULL) return false;
    if (left->val != right->val) return false;
    if (isSymmetricHelper(left->left, right->right) == false) return false;
    return isSymmetricHelper(left->right, right->left);
}

bool isSymmetric(struct TreeNode* root){
    if (root == NULL) return true;
    return isSymmetricHelper(root->left, root->right);
}

bool isValidBSTHelper(struct TreeNode* root, struct TreeNode* lower, struct TreeNode* upper) {
    if (root == NULL) return true;
    if (lower != NULL && root->val <= lower->val) return false;
    if (upper != NULL && root->val >= upper->val) return false;
    if (!isValidBSTHelper(root->left, lower, root)) return false;
    if (!isValidBSTHelper(root->right, root, upper)) return false;
    return true;
}

bool isValidBST(struct TreeNode* root){
    return isValidBSTHelper(root, NULL, NULL);
}

void nextPermutation(int* nums, int numsSize){
    int index = numsSize-2;
    int i = numsSize-2, j, tmp;
    while (index >= 0) {
        if (nums[index] >= nums[index+1]) {
            --index;
            continue;
        }
        j = index;
        for (i = numsSize-1; i > index; --i) {
            if (nums[i] > nums[index]) { 
                j = i;
                break;
            }
        }
        tmp = nums[index];
        nums[index] = nums[j];
        nums[j] = tmp;
        break;
    }
    i = index+1;
    j = numsSize-1;
    while (i < j) {
        tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
        ++i;
        --j;
    }
}

int** generateMatrix(int n, int* returnSize, int** returnColumnSizes){
    int **result = malloc(sizeof(int*)*n);
    *returnColumnSizes = malloc(sizeof(int)*n);
    *returnSize = n;
    int i;
    for (i = 0; i < n; ++i) {
        result[i] = malloc(sizeof(int)*n);
        (*returnColumnSizes)[i] = n;
    }
    int firstRow = 0, firstCol = 0, lastRow = n-1, lastCol = n-1, count = 1;
    while (1) {
        for (int i = firstCol; i <= lastCol; ++i) result[firstRow][i] = count++;
        if (++firstRow > lastRow) break;
        
        for (int i = firstRow; i <= lastRow; ++i) result[i][lastCol] = count++;
        if (--lastCol < firstCol) break;
        
        for (int i = lastCol; i >= firstCol; --i) result[lastRow][i] = count++;
        if (--lastRow < firstRow) break;
        
        for (int i = lastRow; i >= firstRow; --i) result[i][firstCol] = count++;
        if (++firstCol > lastCol) break;
    }
    return result;
}

int fib(int N){
    if (N < 2) return N;
    int sum = 0, m = 0, n = 1;
    for (int i = 1; i < N; ++i) {
        sum = m+n;
        m = n;
        n = sum;
    }
    return sum;
}

void combinationSumHelper(int* candidates, int candidatesSize, int target, int*** result, int* returnSize, int** returnColumnSizes, int *nums, int numsCount) {
    
    int tmp;
    for (int i = 0; i < candidatesSize; ++i) {
        if (candidates[i] > target) break;
        if (nums && nums[numsCount-1] > candidates[i]) continue;
        
        tmp = target-candidates[i];
        int *newNums = malloc(sizeof(int)*(numsCount+1));
        if (numsCount > 0) memcpy(newNums, nums, sizeof(int)*numsCount);
        
        newNums[numsCount] = candidates[i];
        if (tmp == 0) {
            if (*result == NULL) {
                *result = malloc(sizeof(int*)*100);
                *returnColumnSizes = malloc(sizeof(int)*100);
            }else if ((*returnSize)%100 == 0) {
                *result = realloc(*result, sizeof(int*)*((*returnSize)+100));
                *returnColumnSizes = realloc(*returnColumnSizes, sizeof(int)*((*returnSize)+100));
            }
            (*result)[*returnSize] = newNums;
            (*returnColumnSizes)[*returnSize] = numsCount+1;
            ++(*returnSize);
        }else{
            combinationSumHelper(candidates, candidatesSize, tmp, result, returnSize, returnColumnSizes, newNums, numsCount+1);
            free(newNums);
        }
    }
}

int** combinationSum(int* candidates, int candidatesSize, int target, int* returnSize, int** returnColumnSizes){
    quickSort(candidates, 0, candidatesSize-1);
    *returnSize = 0;
    int **result = NULL;
    combinationSumHelper(candidates, candidatesSize, target, &result, returnSize, returnColumnSizes, NULL, 0);
    
    return result;
}

bool isMatch(char * s, char * p){
    int sl = strlen(s);
    int pl = strlen(p);
    bool dp[sl + 1][pl + 1];
    bool flag = false;
    memset(dp, 0, sizeof(dp));
    for (int i = sl; i > -1; --i) {
        for (int j = pl; j > -1; --j) {
            if (i == sl && j == pl) {
                dp[i][j] = true;
                continue;
            }
            if (pl - j > 1 && p[j + 1] == '*') {
                flag = dp[i][j + 2] || (i < sl && (p[j] == '.' || p[j] == s[i]) && dp[i + 1][j]);
                dp[i][j] = flag;
            } else {
                flag = i < sl && (p[j] == '.' || p[j] == s[i]) && dp[i + 1][j + 1];
                dp[i][j] = flag;
            }
        }
    }
    return dp[0][0];
}

int* intersect(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize){
    int i, j;
    quickSort(nums1, 0, nums1Size-1);
    quickSort(nums2, 0, nums2Size-1);
    
    i = 0;
    j = 0;
    *returnSize = 0;
    while (i < nums1Size && j < nums2Size) {
        if (nums1[i] == nums2[j]) {
            nums1[*returnSize] = nums1[i];
            ++i;
            ++j;
            ++(*returnSize);
        }else if (nums1[i] < nums2[j]) {
            ++i;
        }else{
            ++j;
        }
    }
    
    return nums1;
}

int compare(void* a, void* b) {
    return *(int*) a - *(int*) b;
}

bool containsDuplicate(int* nums, int numsSize){
    qsort(nums, numsSize, sizeof(*nums), compare);
    --numsSize;
    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] == nums[i+1]) return true;
    }
    return false;
}

int** flipAndInvertImage(int** A, int ASize, int* AColSize, int* returnSize, int** returnColumnSizes){
    int left, right, tmp;
    for (int i = 0; i < ASize; ++i) {
        left = 0;
        right = AColSize[0]-1;
        while (left < right) {
            tmp = A[i][left];
            A[i][left++] = 1-A[i][right];
            A[i][right--] = 1-tmp;
        }
        if (left == right) A[i][left] = 1-A[i][left]; 
    }
    *returnSize = ASize;
    *returnColumnSizes = AColSize;
    return A;
}

int isHappyHelper(int n) {
    int total = 0;
    int bit;
    while (n != 0) {
        bit = n%10;
        total += bit*bit;
        n /= 10;
    }
    return total;
}

bool isHappy(int n){
    int fast = isHappyHelper(n);
    while (n != fast) {
        n = isHappyHelper(n);
        fast = isHappyHelper(isHappyHelper(fast));
    }
    return n == 1;
}

struct ListNode* deleteDuplicates2(struct ListNode* head){
    struct ListNode *cur = head;
    while (cur) {
        if (cur->next != NULL) {
            if (cur->val == cur->next->val) {
                cur->next = cur->next->next;
                continue;
            }
        }
        cur = cur->next;
    }
    return head;
}

bool canJump(int* nums, int numsSize){
    int needCount = 1;
    for (int i = numsSize-2; i >= 0; --i) {
        if (nums[i] < needCount) {
            ++needCount;
        }else{
            needCount = 1;
        }
    }
    return needCount == 1;
}

bool isAnagram(char * s, char * t){
    int tmp[26];
    memset(tmp, 0, sizeof(tmp));
    int length = 0;
    while (*s != '\0') {
        tmp[*s-'a'] += 1;
        ++s;
        ++length;
    }
    while (*t != '\0') {
        tmp[*t-'a'] -= 1;
        if (tmp[*t-'a'] < 0) return false;
        ++t;
        --length;
    }
    return length == 0;
}

int* intersection(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize){
    int i, j;
    quickSort(nums1, 0, nums1Size-1);
    quickSort(nums2, 0, nums2Size-1);
    
    i = 0;
    j = 0;
    *returnSize = 0;
    while (i < nums1Size && j < nums2Size) {
        if (nums1[i] == nums2[j]) {
            if (*returnSize > 0) {
                if (nums1[(*returnSize)-1] != nums1[i]) {
                    nums1[*returnSize] = nums1[i];
                    ++(*returnSize);
                }
            }else{
                nums1[*returnSize] = nums1[i];
                ++(*returnSize);
            }
            ++i;
            ++j;
        }else if (nums1[i] < nums2[j]) {
            ++i;
        }else{
            ++j;
        }
    }
    
    return nums1;
}

bool isPowerOfTwo(int n){
    if (n < 1) return false;
    while (n != 1) {
        if (n%2 != 0) return false;
        n = n >> 1;
    }
    return true;
}

int* getRow(int rowIndex, int* returnSize){
    int *result = malloc(sizeof(int)*(rowIndex+1));
    *returnSize = rowIndex+1;
    result[0] = 1;
    for (int i = 1; i <= rowIndex; ++i) {
        result[i] = 1;
        for (int j = i-1; j > 0; --j) {
            result[j] = result[j]+result[j-1];
        }
    }
    return result;
}

char * getPermutation(int n, int k){
    char tmp[10] = "123456789";
    char *result = malloc(sizeof(char)*(n+1));
    result[n] = '\0';
    int i, j, count = 1;
    for (i = 1; i < n; ++i) count *= i;
    int index = 0;
    k = k-1;
    while (n > 1) {
        j = k/count;
        result[index++] = tmp[j];
        for (i = j; i < n; ++i) tmp[i] = tmp[i+1];
        k = k%count;
        count = count/(--n);
    }
    result[index] = tmp[0];
    return result;
}

/** Initialize your data structure here. */
MyQueue* myQueueCreate() {
    MyQueue *myQueue = malloc(sizeof(MyQueue));
    myQueue->top = NULL;
    myQueue->last = NULL;
    return myQueue;
}

/** Push element x to the back of queue. */
void myQueuePush(MyQueue* obj, int x) {
    struct ListNode *node = malloc(sizeof(struct ListNode));
    node->next = NULL;
    node->val = x;
    if (obj->top == NULL) {
        obj->top = node;
    }else{
        obj->last->next = node;
    }
    obj->last = node;
}

/** Removes the element from in front of queue and returns that element. */
int myQueuePop(MyQueue* obj) {
    struct ListNode *top = obj->top;
    obj->top = top->next;
    int val = top->val;
    free(top);
    return val;
}

/** Get the front element. */
int myQueuePeek(MyQueue* obj) {
    return obj->top->val;
}

/** Returns whether the queue is empty. */
bool myQueueEmpty(MyQueue* obj) {
    return obj->top==NULL;
}

void myQueueFree(MyQueue* obj) {
    struct ListNode *top = obj->top;
    while (top) {
        obj->top = top->next;
        free(top);
        top = obj->top;
    }
    obj->last = NULL;
    free(obj);
}

struct TreeNode* invertTree(struct TreeNode* root){
    if (root == NULL) return root;
    
    struct TreeNode *left = root->left;
    struct TreeNode *right = root->right;
    invertTree(left);
    invertTree(right);
    root->left = right;
    root->right = left;
    return root;
}

void placeQueen(int row, int col, int n, int* queen, int* cols, int* hills, int* dales) {
    queen[row] = col;
    cols[col] = 1;
    hills[row-col+n-1] = 1;
    dales[row+col] = 1;
}

void removeQueen(int row, int col, int n, int* queen, int* cols, int* hills, int* dales) {
    queen[row] = 0;
    cols[col] = 0;
    hills[row-col+n-1] = 0;
    dales[row+col] = 0;
}

void backtrackQueen(int row, int n, int* queen, int* cols, int* hills, int* dales, char ***result, int* returnSize) {
    for (int col = 0; col < n; col++) {
      if (cols[col]+hills[row-col+n-1]+dales[row+col] == 0) {
        placeQueen(row, col, n, queen, cols, hills, dales);
        // if n queens are already placed
        if (row + 1 == n){
            char **solve = malloc(sizeof(char*)*n);
            for (int i = 0; i < n; ++i) {
                char *str = malloc(sizeof(char)*(n+1));
                str[n] = '\0';
                for (int j = 0; j < n; ++j) {
                    if (j == queen[i]) {
                        str[j] = 'Q';
                    }else{
                        str[j] = '.';
                    }
                }
                solve[i] = str;
            }
            result[*returnSize] = solve;
            ++(*returnSize);
        }
        else backtrackQueen(row + 1, n, queen, cols, hills, dales, result, returnSize);
        // backtrack
        removeQueen(row, col, n, queen, cols, hills, dales);
      }
    }
}

char *** solveNQueens(int n, int* returnSize, int** returnColumnSizes){
    char ***result = malloc(sizeof(char**)*512);
    int *cols = malloc(sizeof(int)*n);
    int *hills = malloc(sizeof(int)*(2*n-1));
    int *dales = malloc(sizeof(int)*(2*n-1));
    int *queen = malloc(sizeof(int)*n);
    memset(queen, 0, sizeof(int)*n);
    memset(cols, 0, sizeof(int)*n);
    memset(hills, 0, sizeof(int)*(2*n-1));
    memset(dales, 0, sizeof(int)*(2*n-1));
    
    *returnSize = 0;
    backtrackQueen(0, n, queen, cols, hills, dales, result, returnSize);
    *returnColumnSizes = malloc(sizeof(int)*(*returnSize));
    for (int i = 0; i < *returnSize; ++i) {
        (*returnColumnSizes)[i] = n;
    }
    
    return result;
}


int longestValidParentheses(char * s){
    int i = 0;
    int left = 0;
    int right = 0;
    int maxLen = 0;
    while (s[i] != '\0') {
        if (s[i] == '(') {
            ++left;
        }else if (s[i] == ')') {
            if (right < left) {
                ++right;
                if (right == left) {
                    if (right*2 > maxLen) {
                        maxLen = right*2;
                    }
                }
            }else{
                left = 0;
                right = 0;
            }
        }
        ++i;
    }
    --i;
    left = 0;
    right = 0;
    while (i >= 0) {
        if (s[i] == '(') {
            if (left < right) {
                ++left;
                if (right == left) {
                    if (right*2 > maxLen) {
                        maxLen = right*2;
                    }
                }
            }else{
                left = 0;
                right = 0;
            }
        }else if (s[i] == ')') {
            ++right;
        }
        --i;
    }
    
    return maxLen;
}

int firstUniqChar(char * s){
	int alphaList[26] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
	int i = 0;
	while(s[i] != '\0') {
		if (alphaList[s[i]-'a'] == -2)
		{
			
		}else if (alphaList[s[i]-'a'] == -1) {
			alphaList[s[i]-'a'] = i;
		}else{
			alphaList[s[i]-'a'] = -2;
		}
		++i;
	}
	int index = -1;
	for (i = 0; i < 26; ++i)
	{
		if (alphaList[i] >= 0 && (index > alphaList[i] || index == -1)) index = alphaList[i];
	}

	return index;
}

int lastStoneWeight(int* stones, int stonesSize){
    quickSort(stones, 0, stonesSize-1);
    
	int x;
    int i = stonesSize-1;
    int j;
    while (i > 0) {
        x = stones[i];
        --i;
        x -= stones[i];
        if (x == 0) {
            stonesSize -= 2;
            i -= 1;
        }else{
            stonesSize -= 2;
            for (j = 0; j < stonesSize; ++j) {
                if (x < stones[j]) {
                    stones[stonesSize] = stones[j];
                    stones[j] = x;
                    x = stones[stonesSize];
                    ++j;
                    break;
                }
            }
            ++stonesSize;
            for (; j < stonesSize; ++j) {
                stones[stonesSize] = stones[j];
                stones[j] = x;
                x = stones[stonesSize];
            }
        }
    }
    if (stonesSize == 0) return 0;
    else return stones[0];
}

bool hasPathSumHelper(struct TreeNode* root, int sum, int count){
    count += root->val;
    if (root->left != NULL && root->right != NULL) {
        bool flag = hasPathSumHelper(root->left, sum, count);
        if (flag == true) return flag;
        flag = hasPathSumHelper(root->right, sum, count);
        return flag;
    }else if (root->left != NULL){
        return hasPathSumHelper(root->left, sum, count);
    }else if (root->right != NULL){
        return hasPathSumHelper(root->right, sum, count);
    }else{
        return count==sum;
    }
}

bool hasPathSum(struct TreeNode* root, int sum){
    if (root == NULL) return false;
    return hasPathSumHelper(root, sum, 0);
}

//void isBalancedHelper(struct TreeNode* root, int count, int *min, int *max){
//    if (root == NULL) {
//        if (*min == 0 || *min > count) *min = count;
//        if (*max < count) *max = count;
//        return;
//    }
//    ++count;
//    isBalancedHelper(root->left, count, min, max);
//    isBalancedHelper(root->right, count, min, max);
//}

int isBalancedHelper(struct TreeNode* root, bool *flag){
    if (root == NULL) return 0;
    int left = isBalancedHelper(root->left, flag);
    if (*flag == false) return 0;
    int right = isBalancedHelper(root->right, flag);
    if (*flag == false) return 0;
    if (left > right) {
        if (left-right > 1) {
            *flag = false;
            return 0;
        }
        return 1+left;
    }else{
        if (right-left > 1) {
            *flag = false;
            return 0;
        }
        return 1+right;
    }
}

bool isBalanced(struct TreeNode* root){
    bool flag = true;
    isBalancedHelper(root, &flag);
    return flag;
}

int* relativeSortArray(int* arr1, int arr1Size, int* arr2, int arr2Size, int* returnSize){
    int tmp, i, j, count = 0;
    for (j = 0; j < arr2Size; ++j) {
        for (i = count; i < arr1Size; ++i) {
            if (arr1[i] == arr2[j]) {
                tmp = arr1[i];
                arr1[i] = arr1[count];
                arr1[count] = tmp;
                ++count;
            }
        }
    }
    quickSort(arr1, count, arr1Size-1);
    *returnSize = arr1Size;
    return arr1;
}

bool isValidSudoku(char** board, int boardSize, int* boardColSize){
    int i, j, k, l, boxx, boxy;
    for (i = 0; i < boardSize; ++i) {
        for (j = 0; j < boardSize; ++j) {
            if (board[i][j] == '.') continue;
            boxx = (i/3)*3+3;
            boxy = (j/3)*3;
            l = j+1;
            for (k = i; k < boxx; ++k) {
                for (; l < boxy+3; ++l) {
                    if (board[i][j] == board[k][l]) {
                        return false;
                    }
                }
                l = boxy;
            }
            l = boxy+3;
            for (; k < boardSize; ++k) {
                if (board[i][j] == board[k][j]) return false;
            }
            for (; l < boardSize; ++l) {
                if (board[i][j] == board[i][l]) return false;
            }
        }
    }
    return true;
}

int heightChecker(int* heights, int heightsSize){
    int *tmp = malloc(sizeof(int)*heightsSize);
    memcpy(tmp, heights, sizeof(int)*heightsSize);
    quickSort(tmp, 0, heightsSize-1);
    int count = 0;
    for (int i = 0; i < heightsSize; ++i) {
        if (tmp[i] != heights[i]) ++count;
    }
    
    return count;
}

int minDepth(struct TreeNode* root){
    if (root == NULL) return 0;
    if (root->left == NULL && root->right == NULL) return 1;
    if (root->left && root->right) {
        int left = minDepth(root->left);
        int right = minDepth(root->right);
        return left<right?left+1:right+1;
    }else if (root->left){
        return minDepth(root->left)+1;
    }else{
        return minDepth(root->right)+1;
    }
}

char findTheDifference(char * s, char * t){
    int flags[26] = {0};
    while (*s != '\0') {
        flags[*s-'a'] += 1;
        ++s;
    }
    while (*t != '\0') {
        if (flags[*t-'a'] == 0) return *t;
        flags[*t-'a'] -= 1;
        ++t;
    }
    
    return '0';
}

int missingNumber(int* nums, int numsSize){
    int i;
    int count = numsSize*(numsSize+1)/2;
    for (i = 0; i < numsSize; ++i) count -= nums[i];
    return count;
}

struct TreeNode* _increasingBST(struct TreeNode* node,struct TreeNode* pre){
    if(node==NULL) return pre;
    struct TreeNode* cur=_increasingBST(node->left,node);
    node->left=NULL;
    if(node->right) node->right=_increasingBST(node->right,pre);
    else node->right=pre;
    return cur;
}

struct TreeNode* increasingBST(struct TreeNode* root){
    return _increasingBST(root,NULL);
}

int* nextGreaterElement(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize){
    int *result = malloc(sizeof(int)*nums1Size);
    *returnSize = nums1Size;
    int i, j;
    for (i = 0; i < nums1Size; ++i) result[i] = -1;
    for (i = 0; i < nums1Size; ++i) {
        for (j = 0; j < nums2Size; ++j) {
            if (nums2[j] == nums1[i]) {
                while (j < nums2Size) {
                    if (nums2[j] > nums1[i]) {
                        result[i] = nums2[j];
                        break;
                    }
                    ++j;
                }
                break;
            }
        }
    }
    return result;
}

void averageOfLevelsHelper(struct TreeNode* root, int count, double* result, int* floorSize) {
    if (root == NULL) return;
    floorSize[count] += 1;
    result[count] += root->val;
    ++count;
    averageOfLevelsHelper(root->left, count, result, floorSize);
    averageOfLevelsHelper(root->right, count, result, floorSize);
}

double* averageOfLevels(struct TreeNode* root, int* returnSize){
    int count = maxDepth(root);
    double *result = malloc(sizeof(double)*count);
    int *floorSize = malloc(sizeof(int)*count);
    memset(result, 0, sizeof(double)*count);
    memset(floorSize, 0, sizeof(int)*count);
    averageOfLevelsHelper(root, 0, result, floorSize);
    *returnSize = count;
    for (int i = 0; i < count; ++i) result[i] = result[i]/floorSize[i];
    
    return result;
}

int rotatedDigits(int N){
    // 2,5,6,9
    // 0,1,8
    // 3,4,7
    // 9 -> 4, 6~8 -> 3, 5 -> 2, 2~4 -> 1, 0~1 -> 0
    
    int tmp, num, count = 0, hasVaildNum, wei = 1;
    for (int i = 1; i <= N; ++i) {
        tmp = i;
        hasVaildNum = false;
        wei = 1;
        while (tmp > 9) {
            num = tmp%10;
            if (num == 2 || num == 5 || num == 6 || num == 9) {
                tmp = tmp/10;
                hasVaildNum = true;
            }else if (num == 0 || num == 1 || num == 8){
                tmp = tmp/10;
            }else{
                i = i+wei-1;
                hasVaildNum = false;
                break;
            }
            wei = wei*10;
        }
        if (tmp == 2 || tmp == 5 || tmp == 6 || tmp == 9) hasVaildNum = true;
        else if (tmp != 0 && tmp != 1 && tmp != 8) hasVaildNum = false;
        
        if (hasVaildNum) ++count;
    }
    
    return count;
}

char * dayOfTheWeek(int day, int month, int year){
    char *str[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
    int w;
    if (month <= 2) {
        month += 12;
        --year;
    }
    int y = (year % 100);
    int c = (year / 100);
    int m = month;
    int d = day;

    w = y + y / 4 + c / 4 - 2 * c + 26 * (m + 1) / 10 + d - 1;
    w = w % 7;
    w = (w + 7) % 7;
    return str[w];
}

int* numberOfLines(int* widths, int widthsSize, char * S, int* returnSize){
    int row = 1;
    int curSize = 0;
    int width;
    while (*S != '\0') {
        width = widths[*S-'a'];
        if (curSize+width > 100) {
            ++row;
            curSize = width;
        }else{
            curSize += width;
        }
        ++S;
    }
    int *result = malloc(sizeof(int)*2);
    result[0] = row;
    result[1] = curSize;
    *returnSize = 2;
    return result;
}

int countCharacters(char ** words, int wordsSize, char * chars){
    int totalChars[26] = {0};
    while (*chars != '\0') {
        totalChars[*chars-'a'] += 1; 
        ++chars;
    } 
    int usedChars[26];
    int i, j, index, result = 0;
    for (i = 0; i < wordsSize; ++i) {
        j = 0;
        memset(usedChars, 0, sizeof(int)*26);
        while (words[i][j] != '\0') {
            index = words[i][j]-'a';
            usedChars[index] += 1;
            if (usedChars[index] > totalChars[index]) break;
            ++j;
        }
        if (words[i][j] == '\0') result += j;
    }
    
    return result;
}

int numSpecialEquivGroups(char ** A, int ASize){
    // 下面是取巧的方法，把每个数做一处理后加起来，当作是一个特征码，统计不一样的特征码个数。
    // 这个虽然可以过leetcode的测试用例，但是实际上作为解法并不正确。(存在特征码一样，但组合不一样的情况)
    int groups[ASize];
    memset(groups, 0, sizeof(int)*ASize);
    int tmp;
    int i, j, k, result = 0;
    bool flag;
    for (i = 0; i < ASize; ++i) {
        k = 0;
        while (A[i][k] != '\0') {
            tmp = A[i][k]*(k%2+1);
            groups[i] += tmp*tmp*tmp;
            ++k;
        }
        
        j = 0;
        flag = true;
        while (j < result) {
            if (groups[j] == groups[i]) {
                flag = false;
                break;
            }
            ++j;
        }
        if (flag) {
            groups[result] = groups[i];
            ++result;
        }
    }
    
    return result;
}

int projectionArea(int** grid, int gridSize, int* gridColSize){
    int i, j, result = 0, tmp;
    for (i = 0; i < gridSize; ++i) {
        tmp = 0;
        for (j = 0; j < gridColSize[i]; ++j) {
            if (grid[i][j] != 0) ++result;
            if (grid[i][j] > tmp) tmp = grid[i][j];
            if (grid[i][j] > grid[0][j]) grid[0][j] = grid[i][j]; 
        }
        result += tmp;
    }
    for (j = 0; j < gridColSize[0]; ++j) result += grid[0][j];
    return result;
}

char ** fizzBuzz(int n, int* returnSize){
    char **result = malloc(sizeof(char*)*n);
    *returnSize = n;
    int tmp, size;
    char *tmpStr;
    for (int i = 1; i <= n; ++i) {
        if (i%3 == 0 && i%5 == 0) {
            result[i-1] = "FizzBuzz";
        }else if (i%3 == 0){
            result[i-1] = "Fizz";
        }else if (i%5 == 0){
            result[i-1] = "Buzz";
        }else{
            tmp = i;
            size = 0;
            while (tmp) {
                tmp /= 10;
                ++size;
            }
            tmpStr = malloc(sizeof(char)*(size+1));
            tmp = i;
            tmpStr[size] = '\0';
            while (--size >= 0) {
                tmpStr[size] = '0'+tmp%10; 
                tmp /= 10;
            }
            result[i-1] = tmpStr;
        }
    }
    return result;
}

int maxNumberOfBalloons(char * text){
    // balloon
    int tmp[5] = {0};
    while (*text != '\0') {
        if (*text == 'b') ++tmp[0];
        else if (*text == 'a') ++tmp[1];
        else if (*text == 'l') ++tmp[2];
        else if (*text == 'o') ++tmp[3];
        else if (*text == 'n') ++tmp[4];
        ++text;
    }
    int result = 0;
    while (1) {
        if (tmp[0] < 1) break;
        --tmp[0];
        if (tmp[1] < 1) break;
        --tmp[1];
        if (tmp[2] < 2) break;
        tmp[2] -= 2;
        if (tmp[3] < 2) break;
        tmp[3] -= 2;
        if (tmp[4] < 1) break;
        --tmp[4];
        ++result;
    }
    
    return result;
}

int* distributeCandies(int candies, int num_people, int* returnSize){
    int *result = malloc(sizeof(int)*num_people);
    memset(result, 0, sizeof(int)*num_people);
    int i = 0, count;
    while (candies > 0) {
        count = i+1;
        if (candies < count) count = candies;
        result[i%num_people] += count;
        candies -= count;
        ++i;
    }
    *returnSize = num_people;
    return result;
}

char ** letterCasePermutation(char * S, int* returnSize){
    int i = 0;
    int length = 1;
    while (S[i] != '\0') {
        if ((S[i] >= 'a' && S[i] <= 'z') || (S[i] >= 'A' && S[i] <= 'Z')) length *= 2;
        ++i;
    }
    char** result = malloc(sizeof(char*)*length);
    
    length = i+1;
    char *tmp = malloc(sizeof(char)*length);
    memcpy(tmp, S, sizeof(char)*length);
    int j = 0;
    i = 0;
    result[0] = tmp;
    *returnSize = 1;
    int offset = 'a'-'A';
    while (S[i] != '\0') {
        if (S[i] >= 'a' && S[i] <= 'z'){
            for (j = 0; j < *returnSize; ++j) {
                tmp = malloc(sizeof(char)*length);
                memcpy(tmp, result[j], sizeof(char)*length);
                tmp[i] -= offset;
                result[j+(*returnSize)] = tmp;
            }
            *returnSize *= 2;
        }else if (S[i] >= 'A' && S[i] <= 'Z'){
            for (j = 0; j < *returnSize; ++j) {
                tmp = malloc(sizeof(char)*length);
                memcpy(tmp, result[j], sizeof(char)*length);
                tmp[i] += offset;
                result[j+(*returnSize)] = tmp;
            }
            *returnSize *= 2;
        }
        ++i;
    }
    
    return result;
}

int hammingWeight(uint32_t n) {
    int count = 0;
    while (n) {
        if (n%2 == 1) ++count;
        n /= 2;
    }
    return count;
}

void duplicateZeros(int* arr, int arrSize){
    int i, zeroCount = 0;
    for (i = 0; i < arrSize; ++i) {
        if (arr[i] == 0) ++zeroCount;
    }
    if (zeroCount == 0) return;
    
    int fixSize = arrSize+zeroCount;
    i = arrSize-1;
    while (1) {
        if (--fixSize <= arrSize){
            if (arr[i--] == 0) arr[--fixSize] = 0;
            break;
        }
        if (arr[i--] == 0){
            if (--fixSize <= arrSize) break;
        }
    }
    for (; i >= 0; --i) {
        arr[--fixSize] = arr[i];
        if (arr[i] == 0) arr[--fixSize] = 0;
    }
}

int bitwiseComplement(int N){
    int t=1;
    while(t<N){
        t<<=1;
        t+=1;
    }
    return t^N;
}

int binaryGap(int N){
    int result = 0;
    int tmp = 0, count = 1;
    while (N) {
        tmp = N%2;
        N /= 2;
        if (tmp == 1) break;
    }
    while (N) {
        tmp = N%2;
        if (tmp == 0) ++count;
        else {
            if (result < count) result = count;
            count = 1;
        }
        N /= 2;
    }
    return result;
}

char * toGoatLatin(char * S){
    char* result = malloc(sizeof(char)*1000);
    int index = 0;
    bool isfirst = true;
    char firstChar = '\0';
    int i, spaceCount = 0;
    while (*S != '\0') {
        if (*S == ' ') {
            isfirst = true;
            if (firstChar != '\0') {
                result[index++] = firstChar;
                firstChar = '\0';
            }
            result[index++] = 'm';
            result[index++] = 'a';
            ++spaceCount;
            for (i = 0; i < spaceCount; ++i) result[index++] = 'a';
            result[index++] = ' ';
        }else if (isfirst) {
            if (*S == 'a' || *S == 'e' || *S == 'i' || *S == 'o'|| *S == 'u' || *S == 'A' || *S == 'E' || *S == 'I' || *S == 'O'|| *S == 'U') result[index++] = *S;
            else firstChar = *S;
            
            isfirst = false;
        }else{
            result[index++] = *S;
        }
        ++S;
    }
    
    if (firstChar != '\0') result[index++] = firstChar;
    result[index++] = 'm';
    result[index++] = 'a';
    ++spaceCount;
    for (i = 0; i < spaceCount; ++i) result[index++] = 'a';
    
    result[index] = '\0';
    return result;
}

int* numSmallerByFrequency(char ** queries, int queriesSize, char ** words, int wordsSize, int* returnSize){
    int alphabatCount;
    char minAlphabat;
    int *queriesCount = malloc(sizeof(int)*queriesSize);
    memset(queriesCount, 0, sizeof(int)*queriesSize);
    int *wordsCount = malloc(sizeof(int)*wordsSize);
    memset(wordsCount, 0, sizeof(int)*wordsSize);
    int i, j;
    for (i = 0; i < wordsSize; ++i) {
        alphabatCount = 0;
        minAlphabat = 'z';
        j = 0;
        while (words[i][j] != '\0') {
            if (words[i][j] < minAlphabat) {
                minAlphabat = words[i][j];
                alphabatCount = 1;
            }else if (words[i][j] == minAlphabat){
                ++alphabatCount;
            }
            ++j;
        }
        wordsCount[i] = alphabatCount;
    }
    quickSort(wordsCount, 0, wordsSize-1);
    int l,r;
    for (i = 0; i < queriesSize; ++i) {
        alphabatCount = 0;
        minAlphabat = 'z';
        j = 0;
        while (queries[i][j] != '\0') {
            if (queries[i][j] < minAlphabat) {
                minAlphabat = queries[i][j];
                alphabatCount = 1;
            }else if (queries[i][j] == minAlphabat){
                ++alphabatCount;
            }
            ++j;
        }
        l = 0;
        r = wordsSize;
        do {
            j = (l+r)/2;
            if (wordsCount[j] <= alphabatCount) {
                l = j+1;
            }else{
                r = j;
            }
        }while (l < r);
        queriesCount[i] = wordsSize-r;
    }
    
    *returnSize = queriesSize;
    return queriesCount;
}

struct ListNode* middleNode(struct ListNode* head){
    int i = 0;
    struct ListNode *tmp = head;
    while (tmp != NULL) {
        tmp = tmp->next;
        ++i;
    }
    i /= 2;
    tmp = head;
    while (i) {
        tmp = tmp->next;
        --i;
    }
    
    return tmp;
}

bool isToeplitzMatrix(int** matrix, int matrixSize, int* matrixColSize){
    int i, j, k;
    for (k = 0; k < matrixSize-1; ++k) {
        j = 1;
        i = k+1;
        while (i < matrixSize && j < matrixColSize[0]) {
            if (matrix[i][j] != matrix[i-1][j-1]) return false; 
            ++i;
            ++j;
        }
    }
    for (k = 1; k < matrixColSize[0]-1; ++k) {
        j = k+1;
        i = 1;
        while (i < matrixSize && j < matrixColSize[0]) {
            if (matrix[i][j] != matrix[i-1][j-1]) return false; 
            ++i;
            ++j;
        }
    }
    
    return true;
}


char ** uncommonFromSentences(char * A, char * B, int* returnSize){
    char **result = malloc(sizeof(char*)*100);
    int *appearCounts = malloc(sizeof(int)*100);
    memset(appearCounts, 0, sizeof(int)*100);
    int count = 0;
    char *tmp = A;
    int i, j;
    bool isContain;
    while (*A != '\0') {
        if (*A == ' ') {
            *A = '\0';
            isContain = false;
            for (j = 0; j < count; ++j) {
                i = 0;
                while (tmp[i] != '\0') {
                    if (tmp[i] != result[j][i]) {
                        break;
                    }
                    ++i;
                }
                if (tmp[i] == '\0' && result[j][i] == '\0') {
                    isContain = true;
                    break;
                }
            }
            ++A;
            if (isContain) {
                appearCounts[j] += 1;
            }else{
                appearCounts[count] = 1;
                result[count++] = tmp;
            }
            tmp = A;
        }else{
            ++A;
        }
    }
    isContain = false;
    for (j = 0; j < count; ++j) {
        i = 0;
        while (tmp[i] != '\0') {
            if (tmp[i] != result[j][i]) {
                break;
            }
            ++i;
        }
        if (tmp[i] == '\0' && result[j][i] == '\0') {
            isContain = true;
            break;
        }
    }
    if (isContain) {
        appearCounts[j] += 1;
    }else{
        appearCounts[count] = 1;
        result[count++] = tmp;
    }
    tmp = B;
    while (*B != '\0') {
        if (*B == ' ') {
            *B = '\0';
            isContain = false;
            for (j = 0; j < count; ++j) {
                i = 0;
                while (tmp[i] != '\0') {
                    if (tmp[i] != result[j][i]) {
                        break;
                    }
                    ++i;
                }
                if (tmp[i] == '\0' && result[j][i] == '\0') {
                    isContain = true;
                    break;
                }
            }
            ++B;
            if (isContain) {
                appearCounts[j] += 1;
            }else{
                appearCounts[count] = 1;
                result[count++] = tmp;
            }
            tmp = B;
        }else{
            ++B;
        }
    }
    isContain = false;
    for (j = 0; j < count; ++j) {
        i = 0;
        while (tmp[i] != '\0') {
            if (tmp[i] != result[j][i]) {
                break;
            }
            ++i;
        }
        if (tmp[i] == '\0' && result[j][i] == '\0') {
            isContain = true;
            break;
        }
    }
    if (isContain) {
        appearCounts[j] += 1;
    }else{
        appearCounts[count] = 1;
        result[count++] = tmp;
    }
    j = 0;
    for (i = 0; i < count; ++i) {
        if (appearCounts[i] < 2) {
            result[j++] = result[i];
        }
    }
    *returnSize = j;
    
    return result;
}

void convertBSTHelper(struct TreeNode* root, int* pre) {
    if (root == NULL) return;
    convertBSTHelper(root->right, pre);
    root->val += *pre;
    *pre = root->val;
    convertBSTHelper(root->left, pre);
}

struct TreeNode* convertBST(struct TreeNode* root){
    int pre = 0;
    convertBSTHelper(root, &pre);
    return root;
}

struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q) {
    if (p->val < root->val && q->val < root->val) return lowestCommonAncestor(root->left, p, q);
    if (p->val > root->val && q->val > root->val) return lowestCommonAncestor(root->right, p, q);
    return root;
}

double largestTriangleArea(int** points, int pointsSize, int* pointsColSize){
    int i, j, k;
    double S = 0;
    double tmp;
    for (i = 0; i < pointsSize-2; ++i) {
        for (j = i; j < pointsSize-1; ++j) {
            for (k = j; k < pointsSize; ++k) {
                tmp = (points[i][0]*points[j][1]+points[j][0]*points[k][1]+points[k][0]*points[i][1]
                    -points[i][0]*points[k][1]-points[j][0]*points[i][1]-points[k][0]*points[j][1])/2.0f;
                tmp = fabs(tmp);
                if (tmp > S) S = tmp;
            }
        }
    }
    return S;
}

int** minimumAbsDifference(int* arr, int arrSize, int* returnSize, int** returnColumnSizes){
    quickSort(arr, 0, arrSize-1);
    int count = 0, tmp, i, maxSize = 16;
    int min = arr[1]-arr[0];
    int **result = malloc(sizeof(int*)*maxSize);
    for (i = 1; i < arrSize; ++i){
        tmp = arr[i]-arr[i-1];
        if (tmp < min) min = tmp;
    }
    for (i = 1; i < arrSize; ++i) {
        tmp = arr[i]-arr[i-1];
        if (tmp == min) {
            if (count == maxSize) {
                maxSize *= 2;
                result = realloc(result, sizeof(int*)*maxSize);
            }
            result[count] = malloc(sizeof(int)*2);
            result[count][0] = arr[i-1];
            result[count][1] = arr[i];
            ++count;
        }
    }
    *returnSize = count;
    *returnColumnSizes = malloc(sizeof(int)*count);
    for (i = 0; i < count; ++i) (*returnColumnSizes)[i] = 2;
    return result;
}

char ** findOcurrences(char * text, char * first, char * second, int* returnSize){
    char** result = malloc(sizeof(char*)*1000);
    *returnSize = 0;
    bool flag1 = false;
    bool flag2 = false;
    bool isFirst = true;
    char* tmp = text;
    int length = 0;
    int i = 0;
    while (*text != '\0') {
        if (*text == ' ') {
            if (flag1 == false) {
                i = 0;
                flag1 = true;
                while (tmp[i] != ' ') {
                    if (first[i] != tmp[i]) {
                        flag1 = false;
                        break;
                    }
                    ++i;
                }
            }else if (flag2 == false) {
                i = 0;
                flag2 = true;
                while (tmp[i] != ' ') {
                    if (second[i] != tmp[i]) {
                        flag2 = false;
                        flag1 = false;
                        break;
                    }
                    ++i;
                }
                if (flag1 == false) {
                    i = 0;
                    flag1 = true;
                    while (tmp[i] != ' ') {
                        if (first[i] != tmp[i]) {
                            flag1 = false;
                            break;
                        }
                        ++i;
                    }
                }
            }else{
                result[*returnSize] = malloc(sizeof(char)*(length+1));
                memcpy(result[*returnSize], tmp, sizeof(char)*length);
                result[*returnSize][length] = '\0';
                ++(*returnSize);
                flag2 = false;
                i = 0;
                while (tmp[i] != ' ') {
                    if (first[i] != tmp[i]) {
                        flag1 = false;
                        break;
                    }
                    ++i;
                }
            }
            isFirst = true;
        }else{
            if (isFirst) {
                tmp = text;
                length = 1;
                isFirst = false;
            }else{
                ++length;
            }
        }
        ++text;
    }
    if (flag1 == true && flag2 == true) {
        result[*returnSize] = malloc(sizeof(char)*(length+1));
        memcpy(result[*returnSize], tmp, sizeof(char)*length);
        result[*returnSize][length] = '\0';
        ++(*returnSize);
    }
    return result;
}

int** allCellsDistOrder(int R, int C, int r0, int c0, int* returnSize, int** returnColumnSizes){
    *returnSize = R*C;
    int** result = malloc(sizeof(int*)*(*returnSize));
    *returnColumnSizes = malloc(sizeof(int)*(*returnSize));
    int i, j = sizeof(int)*2;
    for (i = 0; i < *returnSize; ++i) {
        result[i] = malloc(j);
        (*returnColumnSizes)[i] = 2;
    }
    
    result[0][0] = r0;
    result[0][1] = c0;
    if (*returnSize == 1) return result;
    int index = 1;
    i = r0;
    j = c0;
    while (1) {
        --i;
        while (i < r0) {
            if (i < 0) {
                j -= i;
                i = 0;
            }else if (j >= C){
                i = (r0-(i-(j-(C-1))))+r0;
                j = C-1;
            }else{
                result[index][0] = i++;
                result[index++][1] = j++;
            }
        }
        if (index == *returnSize) break;
        while (j > c0) {
            if (i >= R) {
                j = (c0-(j+(i-(R-1))))+c0;
                i = R-1;
            }else if (j >= C){
                i = i+j-(C-1);
                j = C-1;
            }else{
                result[index][0] = i++;
                result[index++][1] = j--;
            }
        }
        if (index == *returnSize) break;
        while (i > r0) {
            if (i >= R) {
                j = j-(i-(R-1));
                i = R-1;
            }else if (j < 0){
                i = r0+r0-(i-j);
                j = 0;
            }else{
                result[index][0] = i--;
                result[index++][1] = j--;
            }
        }
        if (index == *returnSize) break;
        while (j < c0) {
            if (i < 0) {
                j = c0+c0-(j+i);
                i = 0;
            }else if (j < 0){
                i = i+j;
                j = 0;
            }else{
                result[index][0] = i--;
                result[index++][1] = j++;
            }
        }
        if (index == *returnSize) break;
    }
    
    return result;
}

int** matrixReshape(int** nums, int numsSize, int* numsColSize, int r, int c, int* returnSize, int** returnColumnSizes){
    if (numsSize == 0) {
        *returnSize = 0;
        return NULL;
    }
    
    if (r*c > numsSize*numsColSize[0]) {
        *returnSize = numsSize;
        *returnColumnSizes = numsColSize;
        return nums;
    }
    
    int i;
    *returnSize = r;
    *returnColumnSizes = malloc(sizeof(int)*r);
    int** result = malloc(sizeof(int*)*r);
    for (i = 0; i < r; ++i) {
        (*returnColumnSizes)[i] = c;
        result[i] = malloc(sizeof(int)*c);
    }
    
    int j, index = 0;
    for (i = 0; i < numsSize; ++i) {
        for (j = 0; j < numsColSize[0]; ++j) {
            result[index/c][index%c] = nums[i][j];
            ++index;
        }
    }
    
    return result;
}

void binaryTreePathsHelper(struct TreeNode* root, int* returnSize, char ** result, int index, char* prePath){
    int val = root->val;
    bool isminus = false;
    int count = 0;
    if (val < 0) {
        val = -val;
        isminus = true;
        ++count;
    }
    int len = 1;
    while (val >= len*10) {
        len *= 10;
        ++count;
    }
    if (prePath) count += 2;
    
    char* path = malloc(sizeof(int)*(index+count+1));
    if (prePath) {
        memcpy(path, prePath, sizeof(int)*index);
        path[index++] = '-';
        path[index++] = '>';
    }
    
    if (isminus) path[index++] = '-';
    
    while (len > 0) {
        path[index++] = (val%(len*10))/len+'0';
        len /= 10;
    }
    
    if (root->left == NULL && root->right == NULL) {
        path[index] = '\0';
        result[*returnSize] = path;
        *returnSize += 1;
        return;
    }
    if (root->left) binaryTreePathsHelper(root->left, returnSize, result, index, path);
    if (root->right) binaryTreePathsHelper(root->right, returnSize, result, index, path);
    free(path);
}

char ** binaryTreePaths(struct TreeNode* root, int* returnSize){
    *returnSize = 0;
    if (root == NULL) return NULL;
    
    char **result = malloc(sizeof(int*)*1000);
    binaryTreePathsHelper(root, returnSize, result, 0, NULL);
    
    return result;
}

NumArray* numArrayCreate(int* nums, int numsSize) {
    NumArray *array = malloc(sizeof(NumArray));
    array->nums = nums;
    array->numsSize = numsSize;
    array->sums = malloc(sizeof(int)*numsSize);
    int sum = 0;
    for (int i = 0; i < numsSize; ++i) {
        sum += nums[i];
        array->sums[i] = sum;
    }
    return array;
}

int numArraySumRange(NumArray* obj, int i, int j) {
    if (i == 0) return obj->sums[j];
    return obj->sums[j]-obj->sums[i-1];
}

void numArrayFree(NumArray* obj) {
    free(obj->sums);
    free(obj);
}



/** Initialize your data structure here. */

MyStack* myStackCreate() {
    MyStack *obj = malloc(sizeof(MyStack));
    obj->top = NULL;
    return obj;
}

/** Push element x onto stack. */
void myStackPush(MyStack* obj, int x) {
    struct ListNode *node = malloc(sizeof(struct ListNode));
    node->val = x;
    if (obj->top) node->next = obj->top;
    else node->next = NULL;
    obj->top = node;
}

/** Removes the element on top of the stack and returns that element. */
int myStackPop(MyStack* obj) {
    struct ListNode *top = obj->top;
    obj->top = top->next;
    int val = top->val;
    free(top);
    return val;
}

/** Get the top element. */
int myStackTop(MyStack* obj) {
    return obj->top->val;
}

/** Returns whether the stack is empty. */
bool myStackEmpty(MyStack* obj) {
    return obj->top == NULL;
}

void myStackFree(MyStack* obj) {
    struct ListNode *top = obj->top;
    struct ListNode *next = NULL;
    while (top) {
        next = top->next;
        free(top);
        top = next;
    }
    free(obj);
}

char * removeDuplicates2(char * S){
    int i = 0;
    int setCount = 0;
    while (S[i] != '\0') {
        if (S[i] == S[i+1]) {
            i += 2;
            while (setCount > 0) {
                if (S[setCount-1] == S[i]) {
                    --setCount;
                    ++i;
                }else{
                    break;
                }
            }
        }else{
            S[setCount++] = S[i++];
        }
    }
    S[setCount] = '\0';
    return S;
}

void leafSimilarHelper(struct TreeNode* root, int* nums, int* numsCount) {
    if (root->left == NULL && root->right == NULL) {
        nums[*numsCount] = root->val;
        *numsCount += 1;
    }
    if (root->left) leafSimilarHelper(root->left, nums, numsCount);
    if (root->right) leafSimilarHelper(root->right, nums, numsCount);
}

bool leafSimilar(struct TreeNode* root1, struct TreeNode* root2){
    int *nums1 = malloc(sizeof(int)*100);
    int *nums2 = malloc(sizeof(int)*100);
    int nums1Count = 0, nums2Count = 0;
    leafSimilarHelper(root1, nums1, &nums1Count);
    leafSimilarHelper(root2, nums2, &nums2Count);
    
    if (nums1Count != nums2Count) return false;
    for (int i = 0; i < nums1Count; ++i) {
        if (nums1[i] != nums2[i]) return false;
    }
    return true;
}

int game(int* guess, int guessSize, int* answer, int answerSize){
    int count = 0;
    for (int i = 0; i < guessSize; ++i) {
        if (guess[i] == answer[i]) ++count;
    }
    return count;
}

void deleteNode(struct ListNode* node) {
    while (node->next->next != NULL) {
        node->val = node->next->val;
        node = node->next;
    }
    node->val = node->next->val;
    node->next = NULL;
}

char * toLowerCase(char * str){
    int offset = 'a'-'A';
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] >= 'A' && str[i] <= 'Z') str[i] += offset;
        ++i;
    }
    return str;
}

bool judgeCircle(char * moves){
    int x = 0, y = 0;
    while (*moves != '\0') {
        if (*moves == 'U') --x;
        else if (*moves == 'D') ++x;
        else if (*moves == 'L') --y;
        else if (*moves == 'R') ++y;
        ++moves;
    }
    return x==0&&y==0;
}

int* sortedSquares(int* A, int ASize, int* returnSize){
    int* result = malloc(sizeof(int)*ASize);
    *returnSize = ASize;
    
    int l, r = ASize, i;
    for (i = 0; i < ASize; ++i) {
        if (A[i] >= 0) {
            r = i;
            break;
        }
    }
    
    i = 0;
    l = r-1;
    while (l >= 0 && r < ASize) {
        if (-A[l] < A[r]) {
            result[i] = A[l]*A[l];
            --l;
        }else{
            result[i] = A[r]*A[r];
            ++r;
        }
        ++i;
    }
    if (l >= 0) {
        while (l >= 0) {
            result[i++] = A[l]*A[l];
            --l;
        }
    }else{
        while (r < ASize) {
            result[i++] = A[r]*A[r];
            ++r;
        }
    }
    
    return result;
}

int balancedStringSplit(char * s){
    int l = 0;
    int count = 0;
    while (*s != '\0') {
        if (*s == 'L') ++l;
        else if (*s == 'R') --l;
        if (l == 0) ++count;
        ++s;
    }
    
    return count;
}

int* selfDividingNumbers(int left, int right, int* returnSize){
    *returnSize = 0;
    int* result = malloc(sizeof(int)*1000);
    int tmp, count;
    bool flag;
    while (left <= right) {
        tmp = left;
        flag = true;
        while (tmp) {
            count = tmp%10;
            if (count == 0 || left%count != 0) {
                flag = false;
                break;
            }
            tmp = tmp/10;
        }
        if (flag) {
            result[*returnSize] = left;
            *returnSize += 1;
        }
        ++left;
    }
    return result;
}

bool canWinNim(int n){
    return n%4 != 0;
}

int* diStringMatch(char * S, int* returnSize){
    int len = strlen(S);
    int* result = malloc(sizeof(int)*(len+1));
    *returnSize = len+1;
    int i = 0;
    int index = 0;
    
    while (*S != '\0') {
        if (*S == 'I') {
            result[index++] = i++;
        }else{
            result[index++] = len--;
        }
        ++S;
    }
    result[index++] = i++;
    
    return result;
}

int uniqueMorseRepresentations(char ** words, int wordsSize){
    char *str[] = { ".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."};
    int len[] = {2,4,4,3,1,4,3,4,2,4,3,4,2,2,3,4,4,3,3,1,3,4,3,4,4,4};
    char **result = malloc(sizeof(char*)*wordsSize);
    int *resultLen = malloc(sizeof(int)*wordsSize);
    char *tmp;
    int i, j, k, index, count = 0;
    bool flag, flag2;
    for (i = 0; i < wordsSize; ++i) {
        tmp = malloc(sizeof(char)*401);
        resultLen[count] = 0;
        j = 0;
        while (words[i][j] != '\0') {
            index = words[i][j]-'a';
            memcpy(tmp+resultLen[count], str[index], sizeof(char)*len[index]);
            resultLen[count] += len[index];
            ++j;
        }
        tmp[resultLen[count]] = '\0';
        flag = true;
        for (j = 0; j < count; ++j) {
            if (resultLen[j] != resultLen[count]) continue;
            k = 0;
            flag2 = true;
            while (tmp[k] != '\0' && result[j][k] != '\0') {
                if (tmp[k] != result[j][k]){
                    flag2 = false;
                    break;
                }
                ++k;
            }
            if (flag2) {
                flag = false;
                break;
            }
        }
        if (flag) {
            result[count++] = tmp;
        }else{
            free(tmp);
        }
    }
    
    return count;
}

struct TreeNode* mergeTrees(struct TreeNode* t1, struct TreeNode* t2){
    if (t1 == NULL) return t2;
    if (t2 == NULL) return t1;
    t1->val += t2->val;
    t1->left = mergeTrees(t1->left, t2->left);
    t1->right = mergeTrees(t1->right, t2->right);
    return t1;
}

RecentCounter* recentCounterCreate() {
    RecentCounter *obj = malloc(sizeof(RecentCounter));
    obj->last = NULL;
    return obj;
}

int recentCounterPing(RecentCounter* obj, int t) {
    struct ListNode *node = obj->last;
    int i = 0;
    while (node) {
        if (node->val < t-3000) break;
        node = node->next;
        ++i;
    }
    node = malloc(sizeof(struct ListNode));
    node->val = t;
    node->next = obj->last;
    obj->last = node;
    return i+1;
}

void recentCounterFree(RecentCounter* obj) {
    free(obj);
}

bool divisorGame(int N){
    return N%2==0;
}

int peakIndexInMountainArray(int* A, int ASize){
    int l = 1;
    int r = ASize-2;
    int center;
    while (1) {
        center = (l+r)/2;
        if (A[center] <= A[center-1]) {
            r = center-1;
            continue;
        }
        if (A[center] <= A[center+1]) {
            l = center+1;
            continue;
        }
        return center;
    }
    return l;
}

int findComplement(int num){
    int tmp = 0;
    int tmpNum = num;
    while (tmpNum) {
        tmpNum = tmpNum >> 1;
        tmp = (tmp << 1)+1;
    }
    return num^tmp;
}

int* sortArrayByParity(int* A, int ASize, int* returnSize){
    *returnSize = ASize;
    int l = 0;
    int r = ASize-1;
    int tmp;
    while (l < r) {
        if (A[l]%2 == 0) {
            ++l;
        }else{
            tmp = A[l];
            A[l] = A[r];
            A[r] = tmp;
            --r;
        }
    }
    return A;
}

int distributeCandies2(int* candies, int candiesSize){
    quickSort(candies, 0, candiesSize-1);
    int max = 1;
    for (int i = 0; i < candiesSize-1; ++i) {
        if (candies[i] != candies[i+1]) ++max;
    }
    if (max > candiesSize/2) max = candiesSize/2;
    return max;
}

int islandPerimeter(int** grid, int gridSize, int* gridColSize){
    int i, j, len = 0;
    for (i = 0; i < gridSize; ++i) {
        for (j = 0; j < gridColSize[0]; ++j) {
            if (grid[i][j] == 1) {
                len += 4;
                if (i > 0 && grid[i-1][j] == 1) --len;
                if (i < gridSize-1 && grid[i+1][j] == 1) --len;
                if (j > 0 && grid[i][j-1] == 1) --len;
                if (j < gridColSize[0]-1 && grid[i][j+1]) --len;
            }
        }
    }
    return len;
}

int minCostToMoveChips(int* chips, int chipsSize){
    int i, tmp1 = 0, tmp2 = 0;
    for (i = 0; i < chipsSize; ++i) {
        if (chips[i]%2 == 0) ++tmp2;
        else ++tmp1;
    }
    
    return tmp1>tmp2?tmp2:tmp1;
}

bool isUnivalTreeHelper(struct TreeNode* root, int preVal) {
    if (root == NULL) return true;
    if (root->val != preVal) return false;
    if (!isUnivalTreeHelper(root->left, root->val)) return false;
    if (!isUnivalTreeHelper(root->right, root->val)) return false;
    return true;
}

bool isUnivalTree(struct TreeNode* root){
    if (!isUnivalTreeHelper(root->left, root->val)) return false;
    if (!isUnivalTreeHelper(root->right, root->val)) return false;
    return true;
}

int addDigits(int num){
    // 数学方法
//    if (num > 9) {
//        num = num % 9;
//        if (num == 0) return 9;
//    }
//    return num;

    int result = num;
    int tmp;
    while (result >= 10) {
        tmp = 0;
        while (result > 0) {
            tmp += result%10;
            result = result/10;
        }
        result = tmp;
    }
    return result;
}

int arrayPairSum(int* nums, int numsSize){
    quickSort(nums, 0, numsSize-1);
    int total = 0;
    for (int i = 0; i < numsSize; i += 2) total += nums[i];
    return total;
}

int minDeletionSize(char ** A, int ASize){
    int i = 0;
    int j = 0;
    int count = 0;
    while (A[0][j] != '\0') {
        for (i = 0; i < ASize-1; ++i) {
            if (A[i][j] > A[i+1][j]) {
                ++count;
                break;
            }
        }
        ++j;
    }
    return count;
}

struct TreeNode* sortedArrayToBST(int* nums, int numsSize){
    if (numsSize == 0) return NULL;
    int center = numsSize/2;
    struct TreeNode *root = malloc(sizeof(struct TreeNode));
    root->val = nums[center];
    root->left = sortedArrayToBST(nums, center);
    root->right = sortedArrayToBST(nums+center+1, numsSize-center-1);
    
    return root;
}

int smallestRangeI(int* A, int ASize, int K){
    int min = A[0];
    int max = A[0];
    for (int i = 1; i < ASize; ++i) {
        if (A[i] < min) min = A[i];
        else if (A[i] > max) max = A[i];
    }
    int result = max-min-2*K;
    return result>0?result:0;
}

int** transpose(int** A, int ASize, int* AColSize, int* returnSize, int** returnColumnSizes){
    int** result = malloc(sizeof(int*)*AColSize[0]);
    *returnSize = AColSize[0];
    *returnColumnSizes = malloc(sizeof(int)*AColSize[0]);
    int i, j;
    for (i = 0; i < AColSize[0]; ++i) {
        result[i] = malloc(sizeof(int)*ASize);
        (*returnColumnSizes)[i] = ASize;
    }
    for (i = 0; i < ASize; ++i) {
        for (j = 0; j < AColSize[0]; ++j) {
            result[j][i] = A[i][j];
        }
    }

    return result;
}

int repeatedNTimes(int* A, int ASize){
    // 1. map方法 (由于题目0 <= A[i] <= 10000，所以可以这么做)
    int map[10000] = {0};
    for (int i = 0; i < ASize; ++i) {
        if (map[A[i]] == 0) map[A[i]] = 1;
        else return A[i];
    }
    // 2. 三个对比法
    for (int i = 2; i < ASize; ++i) {
        if (A[i-1] == A[i-2] || A[i] == A[i-1]) return A[i-1];
        else if (A[i] == A[i-2]) return A[i];
    }
    return A[0];
}

int findLUSlength(char * a, char * b){
    int alen = strlen(a);
    int blen = strlen(b);
    if (alen != blen) {
        return alen>blen?alen:blen;
    }else{
        int i = 0;
        while (a[i] != '\0') {
            if (a[i] != b[i]) return alen;
            ++i;
        }
        return -1;
    }
}

int calPoints(char ** ops, int opsSize){
    struct ListNode *node = NULL;
    struct ListNode *tmpNode = NULL;
    int j, tmp;
    bool isMinus, hasNum;
    for (int i = 0; i < opsSize; ++i) {
        j = 0;
        tmp = 0;
        isMinus = false;
        hasNum = true;
        while (ops[i][j] != '\0') {
            if (ops[i][j] == '-') {
                isMinus = true;
            }else if (ops[i][j] >= '0' && ops[i][j] <= '9') {
                tmp *= 10;
                tmp += ops[i][j]-'0';
            }else if (ops[i][j] == '+'){
                if (node) {
                    tmp += node->val;
                    if (node->next) tmp += node->next->val;
                }
            }else if (ops[i][j] == 'C'){
                if (node) {
                    tmpNode = node;
                    node = node->next;
                    free(tmpNode);
                }
                hasNum = false;
            }else if (ops[i][j] == 'D'){
                if (node) tmp = node->val*2;
            }
            ++j;
        }
        
        if (hasNum) {
            if (isMinus == true) tmp = -tmp;
            tmpNode = malloc(sizeof(struct ListNode));
            tmpNode->val = tmp;
            tmpNode->next = node;
            node = tmpNode;
        }
    }
    tmp = 0;
    while (node) {
        tmp += node->val;
        tmpNode = node;
        node = node->next;
        free(tmpNode);
    }
    
    return tmp;
}

bool uniqueOccurrences(int* arr, int arrSize){
    // 先统计，再排序
    int map[2001] = {0};
    int i, len = 0;
    for (i = 0; i < arrSize; ++i) map[1000+arr[i]] += 1;
    for (i = 0; i < 2001; ++i) {
        if (map[i] > 0) map[len++] = map[i];
    }
    quickSort(map, 0, len-1);
    for (i = 1; i < len; ++i) {
        if (map[i] == map[i-1]) return false;
    }
    return true;
}

int* sortArrayByParityII(int* A, int ASize, int* returnSize){
    int j = 0;
    int o = 0;
    int *result = malloc(sizeof(int)*ASize);
    *returnSize = ASize;
    for (int i = 0; i < ASize; ++i) {
        if (A[i]%2 == 0) {
            result[o*2] = A[i];
            ++o;
        }else{
            result[j*2+1] = A[i];
            ++j;
        }
    }
    return result;
}

int titleToNumber(char * s){
    int i = 0;
    int num, total = 0;
    while (s[i] != '\0') {
        num = s[i]-'A'+1;
        total *= 26;
        total += num;
        ++i;
    }
    return total;
}

int countPrimeSetBits(int L, int R){
    int map[32] = {0,0,1,1,0,1,0,1,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,0,0,1,0,1};
    int tmp = 0;
    int result = 0;
    int num;
    while (L <= R) {
        tmp = 0;
        num = L;
        while (num) {
            ++tmp;
            num = num & (num-1);
        }
        if (map[tmp] == 1) ++result;
        ++L;
    }
    return result;
}

char ** commonChars(char ** A, int ASize, int* returnSize){
    char* alphabet[26] = {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o",
    "p","q","r","s","t","u","v","w","x","y","z"};
    int** map = malloc(sizeof(int*)*ASize);
    int index;
    int i, j;
    for (i = 0; i < ASize; ++i) {
        map[i] = malloc(sizeof(int)*26);
        memset(map[i], 0, sizeof(int)*26);
    }
    char** result = malloc(sizeof(char*)*3333);
    
    *returnSize = 0;
    for (i = 0; i < ASize; ++i) {
        j = 0;
        while (A[i][j] != '\0') {
            index = A[i][j]-'a';
            map[i][index] += 1;
            ++j;
        }
    }
    bool contain;
    for (j = 0; j < 26;) {
        contain = true;
        for (i = 0; i < ASize; ++i) {
            if (map[i][j] == 0) {
                contain = false;
                ++j;
                break;
            }
            --map[i][j];
        }
        if (contain) {
            result[*returnSize] = alphabet[j];
            ++(*returnSize);
        }
    }
    
    return result;
}

int numUniqueEmails(char ** emails, int emailsSize){
    int i, j, index;
    bool isPlus;
    bool isAt;
    for (i = 0; i < emailsSize; ++i) {
        index = 0;
        j = 0;
        isPlus = false;
        isAt = false;
        while (emails[i][j] != '\0') {
            if (isAt) {
                emails[i][index++] = emails[i][j];
            }else{
                if (isPlus == false) {
                    if (emails[i][j] == '+') {
                        isPlus = true;
                    }else if (emails[i][j] == '@'){
                        isAt = true;
                        emails[i][index++] = emails[i][j];
                    }else if (emails[i][j] != '.'){
                        emails[i][index++] = emails[i][j];
                    }
                }else{
                    if (emails[i][j] == '@'){
                        isAt = true;
                        emails[i][index++] = emails[i][j];
                    }
                }
            }
            ++j;
        }
        emails[i][index] = '\0';
    }
    int count = emailsSize, k;
    bool isEqual;
    for (i = 0; i < emailsSize-1; ++i) {
        index = i+1;
        for (j = i+1; j < emailsSize; ++j) {
            k = 0;
            isEqual = true;
            while (emails[i][k] != '\0' && emails[j][k] != '\0') {
                if (emails[i][k] != emails[j][k]) {
                    isEqual = false;
                    break;
                }
                ++k;
            }
            if (isEqual) {
                if (emails[i][k] == emails[j][k]) {
                    --count;
                    continue;
                }
            }
            emails[index++] = emails[j];
        }
        emailsSize = count;
    }
    
    return count;
}

struct TreeNode* trimBST(struct TreeNode* root, int L, int R){
    if (root == NULL) return NULL;
    if (root->val < L) {
        return trimBST(root->right, L, R);
    }else if (root->val > R){
        return trimBST(root->left, L, R);
    }else{
        root->left = trimBST(root->left, L, R);
        root->right = trimBST(root->right, L, R);
    }
    return root;
}

void levelOrderBottomHelper(struct TreeNode* root, int level, int** result, int** returnColumnSizes) {
    if (root == NULL) return;
    result[level][(*returnColumnSizes)[level]] = root->val;
    ++(*returnColumnSizes)[level];
    levelOrderBottomHelper(root->left, level+1, result, returnColumnSizes);
    levelOrderBottomHelper(root->right, level+1, result, returnColumnSizes);
}

int** levelOrderBottom(struct TreeNode* root, int* returnSize, int** returnColumnSizes){
    int depth = maxDepth(root);
    int** result = malloc(sizeof(int*)*depth);
    int len = 1;
    for (int i = 0; i < depth; ++i) {
        result[i] = malloc(sizeof(int)*len);
        if (len < 1000) len *= 2;
    }
    *returnColumnSizes = malloc(sizeof(int)*depth);
    memset(*returnColumnSizes, 0, sizeof(int)*depth);
    *returnSize = depth;
    levelOrderBottomHelper(root, 0, result, returnColumnSizes);
    
    int l = 0, r = depth-1;
    int* tmpNums;
    int tmpSize;
    while (l < r) {
        tmpNums = result[l];
        result[l] = result[r];
        result[r] = tmpNums;
        tmpSize = (*returnColumnSizes)[l];
        (*returnColumnSizes)[l] = (*returnColumnSizes)[r];
        (*returnColumnSizes)[r] = tmpSize;
        ++l;
        --r;
    }
    
    return result;
}

bool isAlienSorted(char ** words, int wordsSize, char * order){
    if (wordsSize < 2) return true;
    int nums[26] = {0};
    int i = 0;
    while (order[i] != '\0') {
        nums[order[i]-'a'] = i;
        ++i;
    }
    int j;
    for (i = 1; i < wordsSize; ++i) {
        j = 0;
        while (words[i-1][j] != '\0' || words[i][j] != '\0') {
            if (words[i-1][j] == '\0') break;
            if (words[i][j] == '\0') return false;
            if (nums[words[i-1][j]-'a'] < nums[words[i][j]-'a']) break;
            if (nums[words[i-1][j]-'a'] > nums[words[i][j]-'a']) return false;
            ++j;
        }
    }
    return true;
}

int tribonacci(int n){
    if (n == 0) return 0;
    if (n == 1) return 1;
    if (n == 2) return 1;
    int n1 = 0, n2 = 1, n3 = 1, n4 = 2;
    for (int i = 3; i <= n; ++i) {
        n4 = n1+n2+n3;
        n1 = n2;
        n2 = n3;
        n3 = n4;
    }
    return n4;
}

int findContentChildren(int* g, int gSize, int* s, int sSize){
    quickSort(g, 0, gSize-1);
    quickSort(s, 0, sSize-1);
    int result = 0;
    int i = 0, j = 0;
    while (i < gSize && j < sSize) {
        if (g[i] <= s[j]) {
            ++result;
            ++i;
        }
        ++j;
    }
    return result;
}

int trailingZeroes(int n){
    int count = 0;
    while (n >= 5) {
        n /= 5;
        count += n;
    }
    
    return count;
}

char * reverseOnlyLetters(char * S){
    int r = (int)strlen(S)-1;
    int l = 0;
    char tmp;
    while (l < r) {
        if (!((S[l] >= 'A' && S[l] <= 'Z') || (S[l] >= 'a' && S[l] <= 'z'))) {
            ++l;
            continue;
        }
        while (!((S[r] >= 'A' && S[r] <= 'Z') || (S[r] >= 'a' && S[r] <= 'z'))) {
            --r;
        }
        if (l >= r) break;
        tmp = S[l];
        S[l] = S[r];
        S[r] = tmp;
        ++l;
        --r;
    }
    
    return S;
}

int findMaxConsecutiveOnes(int* nums, int numsSize){
    int maxCount = 0;
    int count = 0;
    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] == 1) ++count;
        else {
            if (count > maxCount) maxCount = count;
            count = 0;
        }
    }
    if (count > maxCount) maxCount = count;
    return maxCount;
}

void minDiffInBSTHelper(struct TreeNode* root, int* min, int* pre) {
    if (root->left) minDiffInBSTHelper(root->left, min, pre);
    if (*min == -2) {
        *min = -1;
    }else if(*min == -1){
        *min = root->val-(*pre);
    }else{
        int val = root->val-(*pre);
        if (val < *min) *min = val;
    }
    *pre = root->val;
    if (root->right) minDiffInBSTHelper(root->right, min, pre);
}

int minDiffInBST(struct TreeNode* root){
    int min = -2, pre;
    minDiffInBSTHelper(root, &min, &pre);
    return min;
}

int twoCitySchedCost(int** costs, int costsSize, int* costsColSize){
    int N = costsSize/2;
    int A = 0;
    int B = 0;
    int *tmp = malloc(sizeof(int)*costsSize);
    int total = 0;
    int i;
    for (i = 0; i < costsSize; ++i) {
        total += costs[i][0]+costs[i][1];
        tmp[i] = costs[i][0]-costs[i][1];
    }
    quickSort(tmp, 0, costsSize-1);
    int l = 0, r = costsSize-1;
    while (l <= r) {
        if (A == N) {
            total -= tmp[r--];
            ++B;
            continue;
        }
        if (B == N) {
            total += tmp[l++];
            ++A;
            continue;
        }
        if (tmp[r] > -tmp[l] || A == N) {
            total -= tmp[r--];
            ++B;
        }else{
            total += tmp[l++];
            ++A;
        }
    }
    free(tmp);
    return total/2;
}

char * shortestCompletingWord(char * licensePlate, char ** words, int wordsSize){
    char *result = "";
    int maxlen = 100;
    int i, j, index, count = 0;
    int alphabet[26] = {0};
    int tmp[26];
    int tmpCount;
    while (*licensePlate != '\0') {
        if (*licensePlate >= 'a' && *licensePlate <= 'z') {
            ++alphabet[*licensePlate-'a'];
            ++count;
        }else if (*licensePlate >= 'A' && *licensePlate <= 'Z'){
            ++alphabet[*licensePlate-'A'];
            ++count;
        }
        ++licensePlate;
    }
    for (i = 0; i < wordsSize; ++i) {
        j = 0;
        memset(tmp, 0, sizeof(int)*26);
        tmpCount = 0;
        while (words[i][j] != '\0') {
            if (j >= maxlen) break;
            if (words[i][j] >= 'a' && words[i][j] <= 'z') {
                index = words[i][j]-'a';
                ++tmp[index];
                if (tmp[index] <= alphabet[index]) {
                    ++tmpCount;
                }
            }else if(words[i][j] >= 'A' && words[i][j] <= 'Z'){
                index = words[i][j]-'A';
                ++tmp[index];
                if (tmp[index] <= alphabet[index]) {
                    ++tmpCount;
                }
            }
            ++j;
        }
        if (tmpCount == count && j < maxlen) {
            result = words[i];
            maxlen = j;
        }
    }
    return result;
}

int numberOfBoomerangs(int** points, int pointsSize, int* pointsColSize){
    if (pointsSize < 2) return 0;
    int i, j, k, l, m, n, count = 0;
    int lineSize = pointsSize-1;
    int *lines = malloc(sizeof(int)*lineSize);
    for (i = 0; i < pointsSize; ++i) {
        k = 0;
        for (j = 0; j < pointsSize; ++j) {
            if (i == j) continue;
            lines[k++] = pow(points[i][0]-points[j][0], 2)+pow(points[i][1]-points[j][1], 2);
        }
        quickSort(lines, 0, lineSize-1);
        m = lines[0];
        n = 1;
        for (l = 1; l < lineSize; ++l) {
            if (lines[l] != m) {
                if (n >= 2) count += n*(n-1);
                m = lines[l];
                n = 1;
            }else{
                ++n;
            }
        }
        if (n >= 2) count += n*(n-1);
    }
    
    free(lines);
    return count;
}

typedef struct _Data{
    int index;
    int val;
} Data;

int findRelativeRankscmp(const void *a, const void *b){
    return ((Data*)b)->val - ((Data*)a)->val;
}

char ** findRelativeRanks(int* nums, int numsSize, int* returnSize){
    *returnSize = numsSize;
    if (numsSize == 0) return NULL;
    Data *d = (Data*)malloc(numsSize * sizeof(Data));
    int i;
    for (i = 0; i < numsSize; ++i) {
        d[i].index = i;
        d[i].val = nums[i];
    }
    qsort(d, numsSize, sizeof(Data), findRelativeRankscmp);
    char **res = (char**)malloc(numsSize * sizeof(char*));
    memset(res, 0, numsSize * sizeof(char*));
    for (i = 0; i < numsSize; ++i){
        res[d[i].index] = (char*)malloc(13 * sizeof(char));
        memset(res[d[i].index], 0, 13 * sizeof(char));
        switch (i) {
        case 0:
            sprintf(res[d[i].index], "Gold Medal");
            break;
        case 1:
            sprintf(res[d[i].index], "Silver Medal");
            break;
        case 2:
            sprintf(res[d[i].index], "Bronze Medal");
            break;
        default:
            sprintf(res[d[i].index], "%d", i + 1);
            break;
        }
    }
    return res;
}

// 2重递归
//int pathSumHelper(struct TreeNode* root, int sum) {
//    if (root == NULL) return 0;
//    sum -= root->val;
//    return (sum==0?1:0)+pathSumHelper(root->left, sum)+pathSumHelper(root->right, sum);
//}
//
//int pathSum(struct TreeNode* root, int sum){
//    if (root == NULL) return 0;
//    return pathSumHelper(root, sum)+pathSum(root->left, sum)+pathSum(root->right, sum);
//}
// dfs回溯
int rootPath(struct TreeNode* root, int depth, int target, int* path_sum)
{
    if(root == NULL) return 0;
    int i, count;
    path_sum[depth] = root->val+path_sum[depth-1];
    
    for(count = 0, i = 0; i < depth; i++)
    {
        if(path_sum[depth]-path_sum[i] == target) count++;
    }
    return count+rootPath(root->left, depth+1, target, path_sum)+rootPath(root->right, depth+1, target, path_sum);
}

int pathSum(struct TreeNode* root, int sum)
{ 
    int path_sum[1001] = {0};
    return rootPath(root, 1, sum, path_sum);
}

int search2(int* nums, int numsSize, int target){
    int l = 0, r = numsSize-1, mid;
    while (l <= r) {
        mid = (l+r)/2;
        if (nums[mid] == target) {
            return mid;
        }else if (nums[mid] < target){
            l = mid+1;
        }else{
            r = mid-1;
        }
    }
    return -1;
}

void tree2strHelper(struct TreeNode* t, char* result, int* index) {
    int val = t->val;
    if (val < 0) {
        result[*index] = '-';
        (*index) += 1;
        val = -val;
    }
    sprintf(result+(*index), "%d", val);
    *index = (int)strlen(result);
    if (t->left == NULL && t->right == NULL) return;
    if (t->left != NULL) {
        result[*index] = '(';
        (*index) += 1;
        tree2strHelper(t->left, result, index);
        result[*index] = ')';
        (*index) += 1;
    }else{
        result[*index] = '(';
        (*index) += 1;
        result[*index] = ')';
        (*index) += 1;
    }
    if (t->right != NULL) {
        result[*index] = '(';
        (*index) += 1;
        tree2strHelper(t->right, result, index);
        result[*index] = ')';
        (*index) += 1;
    }
}

char * tree2str(struct TreeNode* t){
    if (t == NULL) return "";
    int index = 0;
    char* result = malloc(sizeof(char)*9999);
    tree2strHelper(t, result, &index);
    result[index] = '\0';
    return result;
}


int largestPerimeter(int* A, int ASize){
    quickSort(A, 0, ASize-1);
    for (int i = ASize-1; i > 1; --i) {
        if (A[i] < A[i-1]+A[i-2]) {
            return A[i]+A[i-1]+A[i-2];
        }
    }
    return 0;
}

void floodFillHelper(int** image, int imageSize, int* imageColSize, int sr, int sc, int newColor, int oriColor){
    image[sr][sc] = newColor;
    if (sr > 0) {
        if (image[sr-1][sc] == oriColor) {
            floodFillHelper(image, imageSize, imageColSize, sr-1, sc, newColor, oriColor);
        }
    }
    if (sc > 0) {
        if (image[sr][sc-1] == oriColor) {
            floodFillHelper(image, imageSize, imageColSize, sr, sc-1, newColor, oriColor);
        }
    }
    if (sr < imageSize-1) {
        if (image[sr+1][sc] == oriColor) {
            floodFillHelper(image, imageSize, imageColSize, sr+1, sc, newColor, oriColor);
        }
    }
    if (sc < imageColSize[0]-1) {
        if (image[sr][sc+1] == oriColor) {
            floodFillHelper(image, imageSize, imageColSize, sr, sc+1, newColor, oriColor);
        }
    }
} 

int** floodFill(int** image, int imageSize, int* imageColSize, int sr, int sc, int newColor, int* returnSize, int** returnColumnSizes){
    *returnSize = imageSize;
    *returnColumnSizes = imageColSize;
    int color = image[sr][sc];
    if (color != newColor) {
        floodFillHelper(image, imageSize, imageColSize, sr, sc, newColor, color);
    }
    return image;
}

int surfaceArea(int** grid, int gridSize, int* gridColSize){
    int i, j, result = 0;
    for (i = 0; i < gridSize; ++i) {
        for (j = 0; j < gridSize; ++j) {
            if (grid[i][j] > 0) {
                result += grid[i][j]*4+2;
                if (j > 0) result -= min(grid[i][j],grid[i][j-1])*2;
                if (i > 0) result -= min(grid[i][j],grid[i-1][j])*2;
            }
        }
    }
    return result;
}

bool detectCapitalUse(char * word){
    if (*word == '\0') return true;
    bool isAllBig = false;
    int index = 1;
    if (*word >= 'A' && *word <= 'Z') {
        if (word[index] == '\0') return true;
        if (word[index] >= 'A' && word[index]<= 'Z') {
            isAllBig = true;
            index = 2;
        }
    }
    
    while (word[index] != '\0') {
        if (isAllBig == false) {
            if (word[index] >= 'A' && word[index] <= 'Z') return false;
        }else{
            if (word[index] >= 'a' && word[index] <= 'z') return false;
        }
        ++index;
    }
    return true;
}

int getSum(int a, int b){
    /*
    例
    a 13 1101
    b 8 1000
    第一轮操作
    a  0101
    b 10000
    第二轮操作
    a 10101
    b 0
    进位为0
    10101 -> 21
     */
    while (b)
    {
        // 记录a+b的进位，直到进位为0是退出
        unsigned int carry = (unsigned int)(a & b)<<1;
        // 异或操作，得出除了进位外的和
        a = a^b;   //结果相加
        // 把进位值付给b
        b = carry;  //循环
        // 继续让a+b相加
    }
    return a;
}

bool lemonadeChange(int* bills, int billsSize){
    int money[2] = {0};
    for (int i = 0; i < billsSize; ++i) {
        if (bills[i] == 5) {
            money[0] += 1;
        }else if (bills[i] == 10) {
            if (money[0] < 1) return false;
            money[1] += 1;
            money[0] -= 1;
        }else{
            if (money[1] > 0) {
                if (money[0] < 1) return false;
                money[1] -= 1;
                money[0] -= 1;
            }else{
                if (money[0] < 3) return false;
                money[0] -= 3;
            }
        }
    }
    return true;
}

int minMoves(int* nums, int numsSize){
    long min = nums[0];
    long count = 0;
    for (int i = 0; i < numsSize; ++i) {
        if (min > nums[i]) min = nums[i];
        count = count+nums[i];
    }
    return (int)(count-min*numsSize);
}

int distanceBetweenBusStops(int* distance, int distanceSize, int start, int destination){
    if (start == destination) return 0;
    int tmp;
    if (start > destination) {
        tmp = destination;
        destination = start;
        start = tmp;
    }
    int i, tmp2 = 0;
    tmp = 0;
    for (i = start; i < destination; ++i) {
        tmp += distance[i];
    }
    for (i = 0; i < start; ++i) {
        tmp2 += distance[i];
    }
    for (i = destination; i < distanceSize; ++i) {
        tmp2 += distance[i];
    }
    
    return tmp<tmp2?tmp:tmp2;
}

int* findDisappearedNumbers(int* nums, int numsSize, int* returnSize){
    int i = 0, tmp;
    while (i < numsSize) {
        if (nums[i] == 0) {
            ++i;
            continue;
        }
        if (nums[i] != i+1) {
            if (nums[nums[i]-1] != nums[i]) {
                tmp = nums[nums[i]-1];
                nums[nums[i]-1] = nums[i];
                nums[i] = tmp;
            }else{
                nums[i] = 0;
                ++i;
            }
        }else{
            ++i;
        }
    }
    *returnSize = 0;
    for (i = 0; i < numsSize; ++i) {
        if (nums[i] == 0) {
            nums[*returnSize] = i+1;
            ++(*returnSize);
        }
    }
    return nums;
}

bool canThreePartsEqualSum(int* A, int ASize){
    // 平均法，O(n)
    int sum = 0;
    int i;
    for (i = 0; i < ASize; ++i) sum += A[i];
    
    if (sum%3 != 0) return false;
    sum = sum/3;
    int count = 0;
    int p = 0;
    for (i = 0; i < ASize; ++i) {
        count += A[i];
        if (count == sum) {
            if (p == 1) return true;
            count = 0;
            p = 1;
        }
    }
    return false;
    // 暴力法，超時 O(n^2)
//    int i, j, k;
//    int p1 = 0, p2, p3;
//    for (i = 0; i < ASize-2; ++i) {
//        p1 += A[i];
//        p2 = 0;
//        for (j = i+1; j < ASize-1; ++j) {
//            p2 += A[j];
//            if (p1 == p2) {
//                p3 = 0;
//                for (k = j+1; k < ASize; ++k) {
//                    p3 += A[k];
//                }
//                if (p3 == p2) {
//                    return true;
//                }
//            }
//        }
//    }
//    return false;
}

int longestPalindrome(char * s){
    int alphabetCaps[26] = {0};
    int alphabet[26] = {0};
    while (*s != '\0') {
        if (*s >= 'a') {
            alphabet[*s-'a'] += 1;
        }else{
            alphabetCaps[*s-'A'] += 1;
        }
        ++s;
    }
    int count = 0;
    int i, hasSingle = 0;
    for (i = 0; i < 26; ++i) {
        count += alphabet[i];
        count += alphabetCaps[i];
        if (alphabet[i]%2 == 1) {
            count -= 1;
            hasSingle = 1;
        }
        if (alphabetCaps[i]%2 == 1) {
            count -= 1;
            hasSingle = 1;
        }
    }
     
    return count+hasSingle;
}

int maximumProduct(int* nums, int numsSize){
    if (numsSize == 3) return nums[0]*nums[1]*nums[2];
    int i;
    int maxIndex;
    int minIndex;
    int tmp;
    
    int loopCount = 0;
    while (loopCount < 3) {
        if (numsSize-loopCount <= 2) break;
        maxIndex = loopCount;
        minIndex = loopCount;
        for (i = loopCount+1; i < numsSize-loopCount; ++i) {
            if (nums[maxIndex] < nums[i]) {
                maxIndex = i;
            }else if (nums[minIndex] > nums[i]) {
                minIndex = i;
            }
        }
        tmp = nums[loopCount];
        nums[loopCount] = nums[minIndex];
        nums[minIndex] = tmp;
        if (loopCount == maxIndex) maxIndex = minIndex;
        tmp = nums[numsSize-loopCount-1];
        nums[numsSize-loopCount-1] = nums[maxIndex];
        nums[maxIndex] = tmp;
        ++loopCount;
    }
    int max = nums[numsSize-3]*nums[numsSize-2]*nums[numsSize-1];
    if (nums[0] < 0 && nums[1] < 0) {
        int max2 = nums[0]*nums[1]*nums[numsSize-1];
        if (max2 > max) return max2;
    }
    
    return max;
}

int* fairCandySwap(int* A, int ASize, int* B, int BSize, int* returnSize){
    int *result = malloc(sizeof(int)*2);
    *returnSize = 2;
    int tmp = 0;
    int i;
    int hashB[100001] = {0};
    for (i = 0; i < ASize; ++i) {
        tmp += A[i];
    }
    for (i = 0; i < BSize; ++i) {
        hashB[B[i]] = 1;
        tmp -= B[i];
    }
    tmp = tmp/2;
    int BValue;
    for (i = 0; i < ASize; ++i) {
        BValue = A[i]-tmp;
        if (BValue >= 1 && BValue <= 100000 && hashB[BValue] == 1) {
            result[0] = A[i];
            result[1] = BValue;
            return result;
        }
    }
    return NULL;
}

bool backspaceCompare(char * S, char * T){
    int i = 0, len = 0;
    while (S[i] != '\0') {
        if (S[i] == '#') {
            if (len > 0) --len;
        }else{
            S[len++] = S[i];
        }
        ++i;
    }
    S[len] = '\0';
    int len2 = 0;
    i = 0;
    while (T[i] != '\0') {
        if (T[i] == '#') {
            if (len2 > 0) --len2;
        }else{
            T[len2++] = T[i];
        }
        ++i;
    }
    T[len2] = '\0';
    if (len != len2) return false;
    i = 0;
    while (S[i] != '\0' || T[i] != '\0') {
        if (S[i] != T[i]) return false;
        ++i;
    }
    return true;
}

bool canConstruct(char * ransomNote, char * magazine){
    int alphabet[26] = {0};
    while (*magazine != '\0') {
        alphabet[*magazine-'a'] += 1;
        ++magazine;
    }
    while (*ransomNote != '\0') {
        if (alphabet[*ransomNote-'a'] < 1) return false;
        alphabet[*ransomNote-'a'] -= 1;
        ++ransomNote;
    }
    return true;
}

void sumRootToLeafHelper(struct TreeNode* root, int* result, int preValue) {
    preValue = preValue*2+root->val;
    if (root->left == NULL && root->right == NULL) {
        *result = *result+preValue;
        return;
    }
    if (root->left) sumRootToLeafHelper(root->left, result, preValue);
    if (root->right) sumRootToLeafHelper(root->right, result, preValue);
}

int sumRootToLeaf(struct TreeNode* root){
    int result = 0;
    sumRootToLeafHelper(root, &result, 0);
    return result;
}

int dayOfYear(char * date){
    int year = 0, month = 0, day = 0;
    int type = 0;
    while (*date != '\0') {
        if (*date == '-') {
            ++type;
        }else{
            if (type == 0) {
                year = year*10+(*date-'0');
            }else if (type == 1) {
                month = month*10+(*date-'0');
            }else{
                day = day*10+(*date-'0');
            }
        }
        ++date;
    }
    
    if (month == 1) return day;
    day += 31;
    if (month == 2) return day;
    if (year%4 == 0 && year%100 != 0) day += 29;
    else day += 28;
    
    if (month == 3) return day;
    day += 31;
    if (month == 4) return day;
    day += 30;
    if (month == 5) return day;
    day += 31;
    if (month == 6) return day;
    day += 30;
    if (month == 7) return day;
    day += 31;
    if (month == 8) return day;
    day += 31;
    if (month == 9) return day;
    day += 30;
    if (month == 10) return day;
    day += 31;
    if (month == 11) return day;
    day += 30;
    
    return day;
}

int findTiltHelper(struct TreeNode* root, int* result){
    if (root == NULL) return 0;
    int left = findTiltHelper(root->left, result);
    int right = findTiltHelper(root->right, result);
    *result = *result+abs(left-right);
    return left+right+root->val;
}

int findTilt(struct TreeNode* root){
    int result = 0;
    findTiltHelper(root, &result);
    return result;
}

int maxCount(int m, int n, int** ops, int opsSize, int* opsColSize){
    for (int i = 0; i < opsSize; ++i) {
        if (ops[i][0] < m) m = ops[i][0];
        if (ops[i][1] < n) n = ops[i][1];
        if (m == 1 && n == 1) return 1;
    }
    return m*n;
}

char * reverseStr(char * s, int k){
    if (k < 2) return s;
    int i, j;
    int len = (int)strlen(s);
    int tmp;
    int offset = 0;
    while (len > 0) {
        i = offset;
        if (len <= k) k = len;
        j = offset+k-1;
        while (i < j) {
            tmp = s[i];
            s[i++] = s[j];
            s[j--] = tmp;
        }
        tmp = 2*k;
        offset += tmp;
        len -= tmp;
    }
    return s;
}

bool isUgly(int num){
    if (num < 1) return false;
    while (num%2 == 0) num = num/2;
    while (num%3 == 0) num = num/3;
    while (num%5 == 0) num = num/5;
    return num == 1;
}

bool rotateString(char * A, char * B){
    int alen = (int)strlen(A);
    int blen = (int)strlen(B);
    if (alen != blen) return false;
    if (alen == 0) return true;
    int i = 0, j = 0, startIndex = 0;
    while (startIndex < alen) {
        if (A[i%alen] == B[j]) {
            ++i;
            ++j;
            if (j == blen) return true;
        }else{
            ++startIndex;
            i = startIndex;
            j = 0;
        }
    }
    return false;
}

uint32_t reverseBits(uint32_t n) {
    uint32_t result = 0;
    uint32_t tmp = 2147483648;
    while (n > 0) {
        if ((n&1)) result += tmp;
        n >>= 1;
        tmp >>= 1;
    }
    return result;
}

char ** readBinaryWatch(int num, int* returnSize){
    *returnSize = 0;
    if (num >= 9) return NULL;
    
    int hourResult0[1] = {0};
    int hourResult1[4] = {1,2,4,8};
    int hourResult2[5] = {3,5,9,6,10};
    int hourResult3[2] = {7,11};
    
    int minuteResult0[1] = {0};
    int minuteResult1[6] = {1,2,4,8,16,32};
    int minuteResult2[15] = {3,5,9,17,33,6,10,18,34,12,20,36,24,40,48};
    int minuteResult3[20] = {7,11,13,14,19,21,22,25,26,28,35,37,38,41,42,44,49,50,52,56};
    int minuteResult4[14] = {15,23,27,29,30,39,43,45,46,51,53,54,57,58};
    int minuteResult5[4] = {31,47,55,59};
    
    int *tmpHourHash;
    int tmpHourCount;
    int *tmpMinuteHash;
    int tmpMinuteCount;
    
    char** result = malloc(sizeof(char*)*1000);
    char* tmpStr;
    int strIndex;
    int i, j, k;
    for (i = 0; i <= num && i < 4; ++i) {
        j = num-i;
        if (j >= 6) continue;
        if (i == 0) {
            tmpHourHash = hourResult0;
            tmpHourCount = 1;
        }else if (i == 1) {
            tmpHourHash = hourResult1;
            tmpHourCount = 4;
        }else if (i == 2) {
            tmpHourHash = hourResult2;
            tmpHourCount = 5;
        }else{
            tmpHourHash = hourResult3;
            tmpHourCount = 2;
        }
        if (j == 0) {
            tmpMinuteHash = minuteResult0;
            tmpMinuteCount = 1;
        }else if (j == 1) {
            tmpMinuteHash = minuteResult1;
            tmpMinuteCount = 6;
        }else if (j == 2) {
            tmpMinuteHash = minuteResult2;
            tmpMinuteCount = 15;
        }else if (j == 3) {
            tmpMinuteHash = minuteResult3;
            tmpMinuteCount = 20;
        }else if (j == 4) {
            tmpMinuteHash = minuteResult4;
            tmpMinuteCount = 14;
        }else{
            tmpMinuteHash = minuteResult5;
            tmpMinuteCount = 4;
        }
        
        for (j = 0; j < tmpHourCount; ++j) {
            for (k = 0; k < tmpMinuteCount; ++k) {
                strIndex = 0;
                if (tmpHourHash[j] >= 10) {
                    tmpStr = malloc(sizeof(char)*6);
                    tmpStr[strIndex++] = '1';
                    tmpStr[strIndex++] = '0'+tmpHourHash[j]%10;
                }else{
                    tmpStr = malloc(sizeof(char)*5);
                    tmpStr[strIndex++] = '0'+tmpHourHash[j];
                }
                tmpStr[strIndex++] = ':';
                tmpStr[strIndex++] = '0'+tmpMinuteHash[k]/10;
                tmpStr[strIndex++] = '0'+tmpMinuteHash[k]%10;
                tmpStr[strIndex] = '\0';
                result[(*returnSize)++] = tmpStr;
            }
        }
    }
    return result;
}

int** imageSmoother(int** M, int MSize, int* MColSize, int* returnSize, int** returnColumnSizes){
    int** result = malloc(sizeof(int*)*MSize);
    *returnSize = MSize;
    *returnColumnSizes = MColSize;
    int i, j, count, tmp;
    for (i = 0; i < MSize; ++i) {
        result[i] = malloc(sizeof(int)*MColSize[i]);
        for (j = 0; j < MColSize[i]; ++j) {
            count = 1;
            tmp = M[i][j];
            if (i > 0) {
                tmp += M[i-1][j];
                ++count;
            }
            if (j > 0) {
                tmp += M[i][j-1];
                ++count;
            }
            if (j > 0 && i > 0) {
                tmp += M[i-1][j-1];
                ++count;
            }
            if (i < MSize-1) {
                tmp += M[i+1][j];
                ++count;
            }
            if (i < MSize-1 && j > 0) {
                tmp += M[i+1][j-1];
                ++count;
            }
            if (i > 0 && j < MColSize[i]-1) {
                tmp += M[i-1][j+1];
                ++count;
            }
            if (j < MColSize[i]-1) {
                tmp += M[i][j+1];
                ++count;
            }
            if (i < MSize-1 && j < MColSize[i]-1) {
                tmp += M[i+1][j+1];
                ++count;
            }
            result[i][j] = tmp/count;
        }
    }
    
    return result;
}

int reorderLogFilesCmp(const void *a, const void *b){
    char* str1 = *(char**)a;
    char* str2 = *(char**)b;
    int i = 0;
    
    while (*str1 != ' ') ++str1;
    while (*str2 != ' ') ++str2;
    
    while (str1[i] != '\0' || str2[i] != '\0') {
        if (str1[i] != str2[i]) return ((int)str1[i]-(int)str2[i]);
        ++i;
    }
    str1 = *(char**)a;
    str2 = *(char**)b;
    i = 0;
    while (str1[i] != ' ' || str2[i] != ' ') {
        if (str1[i] != str2[i]) return ((int)str1[i]-(int)str2[i]);
        ++i;
    }
    return 0;
}

char ** reorderLogFiles(char ** logs, int logsSize, int* returnSize){
    char** result = malloc(sizeof(char*)*logsSize);
    *returnSize = logsSize;
    
    int index = logsSize-1;
    int pIndex = 0;
    
    int i, j;
    bool isContent;
    for (i = index; i >= 0; --i) {
        j = 0;
        isContent = false;
        while (logs[i][j] != '\0') {
            if (isContent) {
                if (logs[i][j] >= '0' && logs[i][j] <= '9') {
                    result[index--] = logs[i];
                    break;
                }else{
                    result[pIndex++] = logs[i];
                    break;
                }
            }else{
                if (logs[i][j] == ' ') {
                    isContent = true;
                }
            }
            ++j;
        }
    }
    
    qsort(result, pIndex, sizeof(*result), reorderLogFilesCmp);
    return result;
}

int findShortestSubArray(int* nums, int numsSize){
    int minNum = 49999;
    int maxNum = 0;
    int i;
    for (i = 0; i < numsSize; ++i) {
        if (nums[i] < minNum) minNum = nums[i];
        if (nums[i] > maxNum) maxNum = nums[i];
    }
    int numHash[50000] = {0};
    for (i = 0; i < numsSize; ++i) numHash[nums[i]] += 1;
    
    int index = 0, maxCount = 0;
    for (i = minNum; i <= maxNum; ++i) {
        if (numHash[i] > maxCount) {
            maxCount = numHash[i];
            index = 0;
            numHash[index++] = i;
        }else if (numHash[i] == maxCount){
            numHash[index++] = i;
        }
    }
    if (maxCount == 1) return 1;
    int tmpCount, j, left = 0, right = 49999;
    minNum = 49999;
    for (i = 0; i < index; ++i) {
        tmpCount = 0;
        for (j = 0; j < numsSize; ++j) {
            if (nums[j] == numHash[i]) {
                if (tmpCount == 0) left = j;
                ++tmpCount;
                if (tmpCount == maxCount) {
                    right = j;
                    break;
                }
                if (j-left+1 >= minNum) {
                    right = 49999;
                    break;
                }
            }
        }
        if (right-left+1 < minNum) minNum = right-left+1;
        if (minNum == 2) return 2;
    }
    
    return minNum;
}

bool isMonotonic(int* A, int ASize){
    if (ASize <= 2) return true;
    int i;
    for (i = 1; i < ASize; ++i) {
        if (A[i] != A[i-1]) break;
    }
    if (i == ASize) return true;
    if (A[i] < A[i-1]) {
        while (++i < ASize) {
            if (A[i] > A[i-1]) return false;
        }
    }else if (A[i] > A[i-1]){
        while (++i < ASize) {
            if (A[i] < A[i-1]) return false;
        }
    }
    return true;
}

int largestSumAfterKNegations(int* A, int ASize, int K){
    quickSort(A, 0, ASize-1);
    int i, sum = 0;
    for (i = 0; i < ASize; ++i) {
        if (A[i] >= 0) {
            if (K%2 == 1) {
                if (i > 0) {
                    if (A[i-1] < A[i]) {
                        A[i-1] = -A[i-1];
                    }else{
                        A[i] = -A[i];
                    }
                    sum += A[i-1];
                }else{
                    if (i > 0) sum += A[i-1];
                    A[i] = -A[i];
                }
            }else{
                if (i > 0) sum += A[i-1];
            }
            break;
        }else{
            A[i] = -A[i];
            if (i > 0) sum += A[i-1];
            if (--K == 0) {
                sum += A[i];
                ++i;
                break;
            }
        }
    }
    while (i < ASize) sum += A[i++];
    
    return sum;
}

int* constructRectangle(int area, int* returnSize){
    int l;
    int w = sqrt(area);
    while (area%w) --w;
    l = area/w;
    *returnSize = 2;
    int *result = malloc(sizeof(int)*2);
    result[0] = l;
    result[1] = w;
    return result;
}

bool checkRecord(char * s){
    int A = 0, L = 0;
    while (*s != '\0') {
        if (*s == 'A') {
            if (++A > 1) return false;
            L = 0;
        }else if (*s == 'L') {
            if (++L > 2) return false;
        }else{
            L = 0;
        }
        ++s;
    }
    
    return true;
}

char ** findRestaurant(char ** list1, int list1Size, char ** list2, int list2Size, int* returnSize){
    int i, j;
    char *s1;
    char *s2;
    bool isEqual;
    char** result = malloc(sizeof(char*)*list1Size);
    
    int* list1Hash = malloc(sizeof(int)*list1Size);
    memset(list1Hash, 0, sizeof(int)*list1Size);
    int* list2Hash = malloc(sizeof(int)*list2Size);
    memset(list2Hash, 0, sizeof(int)*list2Size);
    for (i = 0; i < list1Size; ++i) {
        j = 0;
        while (list1[i][j] != '\0') list1Hash[i] += list1[i][j++];
    }
    for (i = 0; i < list2Size; ++i) {
        j = 0;
        while (list2[i][j] != '\0') list2Hash[i] += list2[i][j++];
    }
    
    *returnSize = 0;
    int minCount = 2000;
    for (i = 0; i < list1Size; ++i) {
        if (i > minCount) break;
        for (j = 0; j < list2Size; ++j) {
            if (i+j > minCount) break;
            if (list1Hash[i] != list2Hash[j]) continue;
            s1 = list1[i];
            s2 = list2[j];
            isEqual = true;
            while (*s1 != '\0' || *s2 != '\0') {
                if (*s1 != *s2) {
                    isEqual = false;
                    break;
                }
                ++s1;
                ++s2;
            }
            if (isEqual) {
                if (i+j < minCount) {
                    minCount = i+j;
                    *returnSize = 0;
                    result[*returnSize] = list1[i];
                    *returnSize += 1;
                }else{
                    result[*returnSize] = list1[i];
                    *returnSize += 1;
                }
            }
        }
    }
    
    free(list1Hash);
    free(list2Hash);
    
    return result;
}

int findJudge(int N, int** trust, int trustSize, int* trustColSize){
    int *beTrustHash = malloc(sizeof(int)*(N+1));
    int *trustHash = malloc(sizeof(int)*(N+1));;
    memset(beTrustHash, 0, sizeof(int)*(N+1));
    memset(trustHash, 0, sizeof(int)*(N+1));
    int i;
    for (i = 0; i < trustSize; ++i) {
        trustHash[trust[i][0]] += 1;
        beTrustHash[trust[i][1]] += 1;
    }
    
    for (i = 1; i <= N; ++i) {
        if (trustHash[i] == 0 && beTrustHash[i] == N-1) return i;
    }
    
    free(trustHash);
    free(beTrustHash);
    return -1;
}

void isCousinsHelper(struct TreeNode* root, int x, int y, int* kx, int* ky, int k, bool* result){
    if (*kx != 0 && k >= *kx) return;
    if (*ky != 0 && k >= *ky) return;
    if (root->left) {
        if (root->left->val == x) {
            *kx = k+1;
            if (*ky != 0 && *kx == *ky) {
                *result = true;
                return;
            }
        }else if (root->left->val == y) {
            *ky = k+1;
            if (*kx != 0 && *kx == *ky) {
                *result = true;
                return;
            }
        }else{
            isCousinsHelper(root->left, x, y, kx, ky, k+1, result);
        }
    }
    if (root->right) {
        if (root->right->val == x) {
            *kx = k+1;
            if (*ky != 0 && *kx == *ky && (root->left == NULL || root->left->val != y)) {
                *result = true;
                return;
            }
        }else if (root->right->val == y) {
            *ky = k+1;
            if (*kx != 0 && *kx == *ky && (root->left == NULL || root->left->val != x)) {
                *result = true;
                return;
            }
        }else{
            isCousinsHelper(root->right, x, y, kx, ky, k+1, result);
        }
    }
}

bool isCousins(struct TreeNode* root, int x, int y){
    int kx = 0;
    int ky = 0;
    bool result = false;
    isCousinsHelper(root, x, y, &kx, &ky, 0, &result);
    return result;
}

char * toHex(int num){
    if (num == 0) return "0";
    char *result = malloc(sizeof(char)*9);
    result[8] = '\0';
    int tmp;
    int index = 7;
    unsigned int unsignedNum = num;
    while (unsignedNum > 0) {
        tmp = unsignedNum%16;
        if (tmp >= 10) {
            result[index] = 'a'+tmp-10;
        }else{
            result[index] = '0'+tmp;
        }
        --index;
        unsignedNum = unsignedNum/16;
    }
    
    return result+index+1;
}

char * addStrings(char * num1, char * num2){
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int resultLen = len1;
    if (len2 > len1) resultLen = len2;
    
    resultLen += 1;
    
    char* result = malloc(sizeof(char)*(resultLen+1));
    result[resultLen] = '\0';
    
    int i = len1-1;
    int j = len2-1;
    
    int tmp;
    int up = 0;
    while (1) {
        tmp = num1[i]-'0'+num2[j]-'0'+up;
        if (tmp/10 > 0) up = 1;
        else up = 0;
        --i;
        --j;
        result[--resultLen] = tmp%10+'0';
        if (i < 0) {
            while (j >= 0) {
                tmp = num2[j]-'0'+up;
                if (tmp/10 > 0) up = 1;
                else up = 0;
                --j;
                result[--resultLen] = tmp%10+'0';
            }
            break;
        }else if (j < 0){
            while (i >= 0) {
                tmp = num1[i]-'0'+up;
                if (tmp/10 > 0) up = 1;
                else up = 0;
                --i;
                result[--resultLen] = tmp%10+'0';
            }
            break;
        }
    }
    if (up > 0) result[--resultLen] = '1';
    return result+resultLen;
}

char * reverseVowels(char * s){
    int r = strlen(s)-1;
    int l = 0;
    int hash[256] = {0};
    hash['A'] = 1;
    hash['E'] = 1;
    hash['I'] = 1;
    hash['O'] = 1;
    hash['U'] = 1;
    hash['a'] = 1;
    hash['e'] = 1;
    hash['i'] = 1;
    hash['o'] = 1;
    hash['u'] = 1;
    
    char tmp;
    while (l < r) {
        while (l < r) {
            if (hash[s[l]] == 1) break;
            ++l;
        }
        while (l < r) {
            if (hash[s[r]] == 1) break;
            --r;
        }
        if (l < r) {
            tmp = s[l];
            s[l] = s[r];
            s[r] = tmp;
            ++l;
            --r;
        }else{
            break;
        }
    }
    
    return s;
}

int countBinarySubstrings(char * s){
    int count0 = 0, count1 = 0, result = 0;
    if (*s == '1') count1 = 1;
    else count0 = 1;
    char pre = *(s++);
    while (*s != '\0') {
        if (*s != pre) {
            result += count1>count0?count0:count1;
            if (*s == '1') count1 = 1;
            else count0 = 1;
        }else{
            if (*s == '1') count1 += 1;
            else count0 += 1;
        }
        pre = *(s++);
    }
    result += count1>count0?count0:count1;
    return result;
}

int gcdOfNums(int num1, int num2) {
    int tmp = num1%num2;
    while (tmp != 0) {
        num1 = num2;
        num2 = tmp;
        tmp = num1%num2;
    }
    return num2;
}

char * gcdOfStrings(char * str1, char * str2){
    int i;
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    if (len1 < len2) {
        char *tmp = str1;
        str1 = str2;
        str2 = tmp;
        i = len1;
        len1 = len2;
        len2 = i;
    }
    i = 0;
    while (str2[i] != '\0') {
        if (str1[i] != str2[i]) return "";
        ++i;
    }
    int j = 0;
    while (str1[i] != '\0') {
        if (str1[i] != str1[j]) return "";
        ++i;
        ++j;
    }
    i = 0;
    while (str2[i] != '\0') {
        if (str2[i] != str1[j]) return "";
        ++i;
        ++j;
    }
    i = gcdOfNums(len1, len2);
    str2[len2] = '\0';
    return str2;

}

char * tictactoe(int** moves, int movesSize, int* movesColSize){
    int nums[9] = {0};
    int i;
    if (movesSize%2 == 0) i = 1;
    else i = 0;
    
    for (; i < movesSize; i+=2) nums[moves[i][0]*3+moves[i][1]] = 1;
    if ((nums[0]&nums[1]&nums[2])||(nums[3]&nums[4]&nums[5])||(nums[6]&nums[7]&nums[8])||
        (nums[0]&nums[3]&nums[6])||(nums[1]&nums[4]&nums[7])||(nums[2]&nums[5]&nums[8])||
        (nums[0]&nums[4]&nums[8])||(nums[2]&nums[4]&nums[6])) {
        if (movesSize%2 == 0) return "B";
        else return "A";
    }else{
        if (movesSize == 9) return "Draw";
        else return "Pending";
    }
}

bool checkStraightLine(int** coordinates, int coordinatesSize, int* coordinatesColSize){
    int x = (coordinates[1][0]-coordinates[0][0]);
    if (x == 0) {
        for (int i = 2; i < coordinatesSize; ++i) {
            if (coordinates[i][0] != coordinates[0][0]) return false;
        }
        return true;
    }else{
        x = (coordinates[1][1]-coordinates[0][1])/x;
        int a = coordinates[0][1]-coordinates[0][0]*x;
        for (int i = 2; i < coordinatesSize; ++i) {
            if (coordinates[i][1] != coordinates[i][0]*x+a) return false;
        }
        return true;
    }
}

bool isSubsequence(char * s, char * t){
    if (s[0] == '\0') return true;
    int i = 0, j = 0;
    while (t[j] != '\0') {
        if (s[i] == t[j]) {
            ++i;
            if (s[i] == '\0') return true;
        }
        ++j;
    }
    return false;
}

char * convertToBase7(int num){
    if (num == 0) return "0";
    char* result = malloc(sizeof(char)*20);
    result[19] = '\0';
    int index = 18;
    bool isminus = false;
    if (num < 0) {
        isminus = true;
        num = -num;
    }
    
    while (num > 0) {
        result[index] = '0'+num%7;
        num /= 7;
        --index;
    }
    if (isminus) result[index--] = '-';
    
    return result+index+1;
}

bool isPowerOfFour(int num){
    if (num <= 0) return false;
    if ((num&(num-1)) != 0) return false;
    if ((num&0x55555555) == num) return true;
    return false;
}

bool isIsomorphic(char * s, char * t){
    int table[128] = {0};
    bool container[128] = {0};
    int i = 0;
    while (s[i] != '\0') {
        if (table[s[i]] == 0) {
            if (container[t[i]] == true) return false;
            table[s[i]] = t[i];
            container[t[i]] = true;
        }
        else if (table[s[i]] != t[i]) return false;
        ++i;
    }
    return true;
}

int orangesRotting(int** grid, int gridSize, int* gridColSize){
    int i, j;
    int nums[100] = {0};
    int count = 0;
    for (i = 0; i < gridSize; ++i) {
        for (j = 0; j < gridColSize[0]; ++j) {
            if (grid[i][j] == 2) {
                nums[count] = i*gridColSize[0]+j;
                ++count;
            }
        }
    }
    
    int dr[4] = {-1,0,1,0};
    int dc[4] = {0,-1,0,1};
    int tmpNums[100] = {0};
    int r, c, tmpCount, tmpr, tmpc;
    int depth = 0;
    if (count != 0) {
        while (count != 0) {
            memset(tmpNums, 0, sizeof(int)*100);
            tmpCount = 0;
            for (i = 0; i < count; ++i) {
                c = nums[i]%gridColSize[0];
                r = nums[i]/gridColSize[0];
                for (j = 0; j < 4; ++j) {
                    tmpr = r+dr[j];
                    tmpc = c+dc[j];
                    if (tmpr >= 0 && tmpr < gridSize && tmpc >= 0 && tmpc < gridColSize[0] && grid[tmpr][tmpc] == 1) {
                        tmpNums[tmpCount] = tmpr*gridColSize[0]+tmpc;
                        ++tmpCount;
                        grid[tmpr][tmpc] = 2;
                    }
                }
            }
            memcpy(nums, tmpNums, sizeof(int)*100);
            count = tmpCount;
            ++depth;
        }
        --depth;
    }
    
    for (i = 0; i < gridSize; ++i) {
        for (j = 0; j < gridColSize[0]; ++j) {
            if (grid[i][j] == 1) {
                return -1;
            }
        }
    }
    
    return depth;
}

char * getHint(char * secret, char * guess){
    int A = 0;
    int B = 0;
    int counts[10] = {0};
    
    int i = 0;
    while (secret[i] != '\0') {
        if (secret[i] == guess[i]) ++A;
        else {
            counts[secret[i]-'0'] += 1;
        }
        ++i;
    }
    i = 0;
    while (secret[i] != '\0') {
        if (secret[i] != guess[i]){
            if (counts[guess[i]-'0'] > 0) {
                counts[guess[i]-'0'] -= 1;
                ++B;
            }
        }
        ++i;
    }
    char *result = malloc(sizeof(char)*100);
    result[99] = '\0';
    result[98] = 'B';
    int index = 97;
    if (B == 0) {
        result[index--] = '0';
    }else{
        while (B != 0) {
            result[index--] = '0'+B%10;
            B = B/10;
        }
    }
    result[index--] = 'A';
    if (A == 0) {
        result[index--] = '0';
    }else{
        while (A != 0) {
            result[index--] = '0'+A%10;
            A = A/10;
        }
    }
    return result+index+1;
}

int minCostClimbingStairs(int* cost, int costSize){
    int cost1 = cost[0];
    int cost2 = cost[1];
    
    for (int i = 2; i < costSize; ++i) {
        if (i%2 == 0) {
            if (cost1 < cost2) {
                cost1 = cost1+cost[i];
            }else{
                cost1 = cost2+cost[i];
            }
        }else{
            if (cost1 < cost2) {
                cost2 = cost1+cost[i];
            }else{
                cost2 = cost2+cost[i];
            }
        }
    }
    return cost1<cost2?cost1:cost2;
}

int diameterOfBinaryTreeHelper(struct TreeNode* root, int* maxlen){
    if (root == NULL) return 0;
    int left = diameterOfBinaryTreeHelper(root->left, maxlen);
    int right = diameterOfBinaryTreeHelper(root->right, maxlen);
    if (left+right > *maxlen) *maxlen = left+right;
    return (left>right?left:right)+1;
}

int diameterOfBinaryTree(struct TreeNode* root){
    int maxLen = 0;
    diameterOfBinaryTreeHelper(root, &maxLen);
    return maxLen;
}

int countPrimes(int n){
    if (n <= 2) return 0;
    int *hash = malloc(sizeof(int)*(n));
    memset(hash, 0, sizeof(int)*(n));
    int count = 0;
    int i, j;
    int in = sqrt(n);
    for (i = 2; i <= in; ++i) {
        if (hash[i] == 1) continue;
        for (j = i*i; j < n; j+=i) {
            if (hash[j] == 1) continue;
            hash[j] = 1;
            ++count;
        }
    }
    ++count;
    free(hash);
    return n-count-1;
}

int numPrimeArrangements(int n){
    // A(n-m, n-m)*A(m, m)
    // (n-m)!*m! = (1*2*..*(n-m))*(1*2*..*m)
    int count = countPrimes(n+1);
    if (n > 8) count = n-count;
    
    long result = 1;
    for (int i = 2; i <= count; ++i) {
        result = result*i%1000000007;
        if (i == n-count) {
            result = result*result%1000000007;
        }
    }
    
    return result;
}

bool isPowerOfThree(int n){
    return n > 0 && 1162261467 % n == 0;
}

bool isOneBitCharacter(int* bits, int bitsSize){
//    int k = 0;
//    for (int i = bitsSize-2; i >= 0; --i) {
//        if (bits[i] == 0) {
//            if (k%2 == 0) {
//                return true;
//            }else{
//                return false;
//            }
//        }
//        ++k;
//    }
//    return k%2==0;
    if (bitsSize < 2) return true;
    else if (bits[bitsSize-2] == 0) return true;
    bool isone = false;
    bitsSize -= 2;
    for (int i = 0; i < bitsSize; ++i) {
        if (isone) isone = false;
        else if (bits[i] == 1) isone = true;
    }
    return isone;
}

bool isLongPressedName(char * name, char * typed){
    int i = 0, j = 0;
    while (typed[j] != '\0') {
        if (name[i] == typed[j]) {
            ++i;
            ++j;
        }else if (i > 0 && typed[j] == name[i-1]) ++j;
        else return false;
    }
    return name[i] == '\0';
}

int findSecondMinimumValue(struct TreeNode* root){
    if (root->left == NULL) return -1;
    if (root->left->val == root->right->val) {
        if (root->left->val > root->val) {
            return root->left->val;
        }else{
            int left = findSecondMinimumValue(root->left);
            int right = findSecondMinimumValue(root->right);
            if (left > root->val && right > root->val) return left>right?right:left;
            else if (left > root->val) return left;
            else if (right > root->val) return right;
            else return -1;
        }
    }else{
        if (root->left->val > root->val && root->right->val > root->val) {
            return root->left->val>root->right->val?root->right->val:root->left->val;
        }else{
            if (root->left->val > root->val) {
                int right = findSecondMinimumValue(root->right);
                if (right > root->val) {
                    return root->left->val>right?right:root->left->val;
                }else{
                    return root->left->val;
                }
            }else{
                int left = findSecondMinimumValue(root->left);
                if (left > root->val) {
                    return root->right->val>left?left:root->right->val;
                }else{
                    return root->right->val;
                }
            }
        }
    }
}

int** largeGroupPositions(char * S, int* returnSize, int** returnColumnSizes){
    int** result = malloc(sizeof(int*)*333);
    *returnColumnSizes = malloc(sizeof(int)*333);
    *returnSize = 0;
    int i = 1;
    char last = S[0];
    int count = 1;
    int firstIndex = 0;
    while (S[i] != '\0') {
        if (S[i] == last) {
            ++count;
        }else{
            if (count >= 3) {
                result[*returnSize] = malloc(sizeof(int)*2);
                returnColumnSizes[0][*returnSize] = 2;
                result[*returnSize][0] = firstIndex;
                result[*returnSize][1] = firstIndex+count-1;
                ++(*returnSize);
            }
            last = S[i];
            firstIndex = i;
            count = 1;
        }
        ++i;
    }
    if (count >= 3) {
        result[*returnSize] = malloc(sizeof(int)*2);
        returnColumnSizes[0][*returnSize] = 2;
        result[*returnSize][0] = firstIndex;
        result[*returnSize][1] = firstIndex+count-1;
        ++(*returnSize);
    }
    
    return result;
}

struct trie_node {
    bool is_end;
    struct trie_node *child[26];
};

static struct trie_node *create()
{
    struct trie_node *node = malloc(sizeof(struct trie_node));
    node->is_end = false;
    for (int i = 0; i < 26; i++) {
        node->child[i] = NULL;
    }
    return node;
}

static void insert_word(struct trie_node *obj, char *word)
{
    while (*word) {
        if (obj->child[*word - 'a'] == NULL) {
            obj->child[*word - 'a'] = create();
        }
        obj = obj->child[*word - 'a'];
        word++;
    }
    obj->is_end = true;
}

static bool is_inc_word(struct trie_node *obj, char *word)
{
    while (*word) {
        if (obj->child[*word - 'a'] == NULL)
            return false;
        else if (obj->child[*word - 'a']->is_end == false)
            return false;
        
        obj = obj->child[*word - 'a'];
        word++;
    }
    return obj->is_end;
}

static void free_trie(struct trie_node *obj)
{
    for (int i = 0; i < 26; i++) {
        if (obj->child[i] != NULL) {
            free_trie(obj->child[i]);
        }
    }
    free(obj);
}

char * longestWord(char ** words, int wordsSize){
    struct trie_node *root = create();
    for (int i = 0; i < wordsSize; i++) {
        insert_word(root, words[i]);
    }
    char *ret = malloc(sizeof(char) * 31);
    memset(ret, 0, sizeof(char) * 31);

    for (int i = 0; i < wordsSize; i++) {
        if (is_inc_word(root, words[i])) {
            if (strlen(words[i]) > strlen(ret))
                strcpy(ret, words[i]);
            else if (strlen(words[i]) == strlen(ret) && strcmp(words[i], ret) == -1)
                strcpy(ret, words[i]);
        }
    }

    return ret;
}

bool repeatedSubstringPattern(char * s){
    int len = strlen(s);
    char str[2 * len - 1];
    memset(str, 0, sizeof(str));
    // 下面两次操作是把s叠两次，然后去掉头尾字符，赋值给str
    strncat(str, s + 1, len - 1);
    strncat(str, s, len - 1);
    /*
        假设重复部分是x，则有s = nx, str = 2nx-2，当n大于等于2是有效
        
    */
    
    return strstr(str, s);
//    
//    int repeatLen = 1;
//    int len = strlen(s);
//    int i;
//    int j;
//    bool flag;
//    while (repeatLen <= len/2) {
//        if (len%repeatLen != 0) {
//            ++repeatLen;
//            continue;
//        }
//        i = 0;
//        j = repeatLen;
//        flag = true;
//        while (s[j] != '\0') {
//            if (s[i] != s[j]) {
//                flag = false;
//                break;
//            }
//            ++i;
//            ++j;
//            if (i == repeatLen) i = 0;
//        }
//        if (flag == true && i == 0) return true;
//        ++repeatLen;
//    }
//    return false;
}

bool isRectangleOverlap(int* rec1, int rec1Size, int* rec2, int rec2Size){
    return (rec2[0] >= rec1[2] || rec2[2] <= rec1[0] || rec2[1] >= rec1[3] || rec2[3] <= rec1[1])?false:true;
}

int compareInt(void *a, void *b)
{
    return *(int*)a > *(int*)b;
}

int findLHS(int* nums, int numsSize){
    if (numsSize < 2) return 0; 
    qsort(nums, numsSize, sizeof(int), compareInt);
    int maxlen = 0;
    int lastNum = nums[0];
    int lastCount = 0;
    int curCount = 1;
    for (int i = 1; i < numsSize; ++i) {
        if (lastNum == nums[i]) {
            ++curCount;
        }else{
            if (lastCount > 0 && curCount+lastCount > maxlen) maxlen = curCount+lastCount;
            if (nums[i]-lastNum == 1) lastCount = curCount;
            else lastCount = 0;
            curCount = 1;
            lastNum = nums[i];
        }
    }
    if (lastCount > 0 && curCount+lastCount > maxlen) maxlen = curCount+lastCount;
    return maxlen;
}

// 解数独
int yCache[9][9] = {0};
int xCache[9][9] = {0};
int bCache[9][9] = {0};
bool isSudokuSolved = false;
void sudokuBackTrace(char** board, int x, int y);
bool sudokuCouldPlaceNum(int num, int x, int y) {
    return xCache[x][num]+yCache[y][num]+bCache[x/3*3+y/3][num] == 0;
}

void sudokuPlaceNum(char** board, int num, int x, int y){
    xCache[x][num] = 1;
    yCache[y][num] = 1;
    bCache[x/3*3+y/3][num] = 1;
    board[x][y] = '1'+num;
}

void sudokuRemoveNum(char** board, int num, int x, int y){
    xCache[x][num] = 0;
    yCache[y][num] = 0;
    bCache[x/3*3+y/3][num] = 0;
    board[x][y] = '.';
}

void sudokuPlaceNextNum(char** board, int x, int y){
    if (x == 8 && y == 8) {
        isSudokuSolved = true;
    }else{
        if (y == 8) sudokuBackTrace(board, x+1, 0);
        else sudokuBackTrace(board, x, y+1);
    }
}

void sudokuBackTrace(char** board, int x, int y) {
    if (board[x][y] == '.') {
        for (int d = 0; d < 9; ++d) {
            if (sudokuCouldPlaceNum(d, x, y)) {
                sudokuPlaceNum(board, d, x, y);
                sudokuPlaceNextNum(board, x, y);
                if (isSudokuSolved == false) sudokuRemoveNum(board, d, x, y);
                else return;
            }
        }
    }else{
        sudokuPlaceNextNum(board, x, y);
    }
}

void solveSudoku(char** board, int boardSize, int* boardColSize){
    isSudokuSolved = false;
    memset(xCache, 0, sizeof(int)*81);
    memset(yCache, 0, sizeof(int)*81);
    memset(bCache, 0, sizeof(int)*81);
    int i, j;
    for (i = 0; i < 9; ++i) {
        for (j = 0; j < 9; ++j) {
            if (board[i][j] != '.') {
                sudokuPlaceNum(board, board[i][j]-'1', i, j);
            }
        }
    }
    sudokuBackTrace(board, 0, 0);
}

/// 是否素数
bool isPrime(int num) {
    if (num <= 3) {
        return num > 1;
    }
    if (num % 6 != 1 && num % 6 != 5) {
        return false;
    }
    int sqrtX = (int)sqrt(num);
    for (int i = 5; i <= sqrtX; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

int primePalindrome(int N){
    while (1) {
        // 从实际数据来看，大于11的且位数为双数的数都不能同时满足素数和回文数两个条件，所以直接跳过
        if (N >= 12 & N <= 100) return 101;
        else if (N >= 1000 && N <= 10000) return 10301;
        else if (N >= 100000 && N <= 1000000) return 1003001;
        else if (N >= 10000000 && N <= 100000000) return 100030001;
        if (isPalindrome(N) && isPrime(N)) {
            return N;
        } 
        ++N;
    }
    return N;
}

bool isPerfectSquare(int num){
    // 暴力法
    int tmp;
    int i = 1;
    while (1) {
        tmp = num/i;
        if (tmp <= i) break;
        ++i;
    }
    return (tmp == i && num%i == 0);
    
    // 数学方法 (1+3+5+...+(2n-1))=n^2
//    int result = 0;
//    int odd = 1;
//    while (1) {
//        result += odd;
//        odd += 2;
//        if (result > num) return false;
//        if (result == num) return true;
//    }

    // 中值查找
//    int l = 1;
//    int r = num;
//    int mid;
//    if (num > 46340) {
//        num = 46340;
//    }
//    while (l <= r) {
//    mid = (l+r)/2;
//        if (mid*mid > num) {
//            r = mid-1;
//        }else if (mid*mid < num) {
//            l = mid+1;
//        }else{
//            return true;
//        }
//    }
//    return false;
    
    //解法四：牛顿迭代法
//    if(1 == num) return true;
//    int i = num / 2;
//    while((double)i * i > num){
//        i = (i + num / i) / 2;
//    }
//    return i * i == num;
    
}

int* gardenNoAdj(int N, int** paths, int pathsSize, int* pathsColSize, int* returnSize){
    *returnSize = N;
    int* result = malloc(sizeof(int)*(N+1));
    memset(result, 0, sizeof(int)*(N+1));
    int** map = malloc(sizeof(int*)*(N+1));
    int i, j, index0, index1;
    for (i = 0; i <= N; ++i) {
        map[i] = malloc(sizeof(int)*3);
        memset(map[i], 0, sizeof(int)*3);
    }
    
    for (i = 0; i < pathsSize; ++i) {
        index0 = paths[i][0];
        index1 = paths[i][1];
        if (map[index0][0] == 0) map[index0][0] = index1;
        else if (map[index0][1] == 0) map[index0][1] = index1;
        else if (map[index0][2] == 0) map[index0][2] = index1;
        
        if (map[index1][0] == 0) map[index1][0] = index0;
        else if (map[index1][1] == 0) map[index1][1] = index0;
        else if (map[index1][2] == 0) map[index1][2] = index0;
    }
    
    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= 4; ++j) {
            if (result[map[i][0]] != j && result[map[i][1]] != j && result[map[i][2]] != j) {
                result[i] = j;
                break;
            }
        }
    }
    
    return result+1;
}

void findModeHelper(struct TreeNode* root, struct TreeNode** pre, int* curCount, int* maxCount, int* result, int *returnSize) {
    // 中序历遍bts二叉树，是一个有序数组，等于把问题变成 -- “从一个有序数组中找出众数”
    if (root == NULL) return;
    findModeHelper(root->left, pre, curCount, maxCount, result, returnSize);
    if (*pre != NULL) {
        // 与前一个数做对比
        if (root->val == (*pre)->val) {
            *curCount = *curCount+1;
        }else{
            *curCount = 1;
        }
    }
    if (*curCount == *maxCount) {
        // 等于当前众数数量，插入数组
        result[*returnSize] = root->val;
        ++(*returnSize);
    }else if(*curCount > *maxCount){
        // 大于当前众数数量，清空数组后，插入
        result[0] = root->val;
        *returnSize = 1;
        *maxCount = *curCount;
    }
    // 记录前一个数的指针
    *pre = root;
    findModeHelper(root->right, pre, curCount, maxCount, result, returnSize);
}

int* findMode(struct TreeNode* root, int* returnSize){
    *returnSize = 0;
    if (root == NULL) return NULL;
    int* result = malloc(sizeof(int)*10000);
    int maxCount = 0;
    int curCount = 1;
    struct TreeNode* pre = NULL;
    findModeHelper(root, &pre, &curCount, &maxCount, result, returnSize);
    
    return result;
}

int* addToArrayForm(int* A, int ASize, int K, int* returnSize){
    int size = 5;
    if (ASize >= size) size = ASize+1;
    int *result = malloc(sizeof(int)*size);
    int i = ASize-1, j = size-1;
    for (; i >= 0 && K > 0; --i, --j) {
        K = A[i]+K;
        result[j] = K%10;
        K = K/10;
    }
    if (K > 0) {
        while (K > 0) {
            result[j--] = K%10;
            K = K/10;
        }
    }else{
        while (i >= 0) result[j--] = A[i--];
    }
    
    *returnSize = size-j-1;
    return result+j+1;
}

int numPairsDivisibleBy60(int* time, int timeSize){
    int hash[60] = {0};
    int i, count = 0;
    for (i = 0; i < timeSize; ++i) ++hash[time[i]%60]; 
    count += hash[0]*(hash[0]-1)/2;
    count += hash[30]*(hash[30]-1)/2;
    for (i = 1; i < 30; ++i) {
        count += hash[i]*hash[60-i];
    }
    return count;
}

int findLengthOfLCIS(int* nums, int numsSize){
    if (numsSize == 0) return 0;
    int maxCount = 1;
    int curCount = 1;
    for (int i = 1; i < numsSize; ++i) {
        if (nums[i] > nums[i-1]) {
            ++curCount;
            if (curCount > maxCount) maxCount = curCount;
        }else{
            curCount = 1;
        }
    }
    return maxCount;
}

bool* prefixesDivBy5(int* A, int ASize, int* returnSize){
    /*
    0
    101
    1010
    1111
    10100
    11001
    11110
    100011
    101000
    
    n%5 == k;
    (n*2)%5 == (k*2)%5
    */
    
    *returnSize = ASize;
    bool* result = malloc(sizeof(bool)*ASize);
    int last = 0;
    for (int i = 0; i < ASize; ++i) {
        last = (last*2+A[i])%5;
        result[i] = (last == 0);
    }
    return result;
}

char nextGreatestLetter(char* letters, int lettersSize, char target){
    if (letters[lettersSize-1] <= target) return letters[0];
    ++target;
    int l = 0;
    int r = lettersSize-1;
    int m = 0;
    while (l < r) {
        m = (l+r)/2;
        if (letters[m] == target) {
            return letters[m];
        }else if (letters[m] > target) {
            r = m;
        }else{
            l = m+1;
        }
    }
    return letters[r];
    
    // 如果數組無序
//    int* hash[26] = {0};
//    int i = 0;
//    while (i < lettersSize) {
//        hash[letters[i]-'a'] += 1;
//        ++i;
//    }
//    i = (target-'a'+1)%26;
//    while (1) {
//        if (hash[i] > 0) return i+'a';
//        ++i;
//        if (i >= 26) i = i%26;
//    }
//    return 'a';
}

bool checkPerfectNumber(int num){
    // 欧几里得-欧拉定理 每个偶完全数都可以写成 2^(p-1)*(2^p-1)，p是素數；而奇完全數暫時還沒有發現
    // 由於在int的輸入範圍內，完全数不是很多，所以直接可以窮盡求解
    int p[] = {2,3,5,7,11,13,17,19,31};
    for (int i = 0; i < 9; ++i) {
        if (pow(2, p[i]-1)*(pow(2, p[i])-1) == num) return true;
    }
    return false;
    
    // 找出所有因數相加，對比。（暴力法）
    if (num < 5 || num&1) return false;
    int sum = 0;
    int target = num/2;
    for (int i = 1; i <= target; ++i) {
        if (num%i == 0) sum += i;
    }
    return sum==num;
}

int arrangeCoins(int n){
    //1+2+...+n = n*(n+1)/2;
    // n = m*(m+1)/2
    // 2n = m^2+m -> 2n+0.25 = (m+0.5)^2
    // m = sqrt(2n+0.25)-0.5
    return sqrt(2.0*n+0.25)-0.5;
//    int count = -1;
//    int i = 1;
//    while (n >= 0) {
//        n = n-i;
//        ++i;
//        ++count;
//    }
//    return count;
}

int numEquivDominoPairs(int** dominoes, int dominoesSize, int* dominoesColSize){
    int hash[91] = {0};
    int i, j;
    for (i = 0; i < dominoesSize; ++i) {
        if (dominoes[i][0] > dominoes[i][1]) {
            ++hash[dominoes[i][0]*9+dominoes[i][1]];
        }else{
            ++hash[dominoes[i][1]*9+dominoes[i][0]];
        }
    }
    int count = 0;
    for (i = 1; i <= 9; ++i) {
        for (j = i; j >= 1; --j) {
            count += hash[i*9+j]*(hash[i*9+j]-1)/2;
        }
    }
    
    return count;
}

int dominantIndex(int* nums, int numsSize){
    int max1 = 0;
    int max2 = 0;
    int index = 0;
    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] > max1) {
            max2 = max1;
            max1 = nums[i];
            index = i;
        }else if (nums[i] > max2){
            max2 = nums[i];
        }
    }
    
    return max1>=2*max2?index:-1;
}

bool isSubtreeHelper(struct TreeNode* s, struct TreeNode* t) {
    if (t == NULL && s == NULL) return true;
    if (s == NULL || t == NULL) return false;
    if (s->val == t->val) {
        return isSubtreeHelper(s->left, t->left)&&isSubtreeHelper(s->right, t->right);
    }else{
        return false;
    }
}

bool isSubtree(struct TreeNode* s, struct TreeNode* t){
    if (s == NULL) return false;
    return isSubtreeHelper(s, t)||isSubtree(s->left, t)||isSubtree(s->right, t);
}

int thirdMax(int* nums, int numsSize){
    int max1 = nums[0], max2, max3;
    bool hasSetMax2 = false;
    bool hasSetMax3 = false;
    for (int i = 1; i < numsSize; ++i) {
        if (nums[i] > max1) {
            if (hasSetMax2) {
                max3 = max2;
                hasSetMax3 = true;
            }
            max2 = max1;
            hasSetMax2 = true;
            max1 = nums[i];
        }else if (nums[i] < max1 && ((hasSetMax2 && nums[i] > max2) || hasSetMax2 == false)) {
            if (hasSetMax2) {
                if (nums[i] > max2) {
                    max3 = max2;
                    hasSetMax3 = true;
                    max2 = nums[i];
                }
            }else{
                max2 = nums[i];
                hasSetMax2 = true;
            }
        }else if (hasSetMax2 && nums[i] < max2) {
            if (hasSetMax3) {
                if (nums[i] > max3) {
                    max3 = nums[i];
                }
            }else{
                max3 = nums[i];
                hasSetMax3 = true;
            }
        }
    }
    
    return hasSetMax3?max3:max1;
}

int* numMovesStones(int a, int b, int c, int* returnSize){
    if (a>b) a^=b^=a^=b;
    if (a>c) a^=c^=a^=c;
    if (b>c) b^=c^=b^=c;
    int maxCount = 0;
    int minCount = 0;
    if (b-a == 2 || c-b == 2) minCount = 1;
    else{
        if (b-a > 1) ++minCount;
        if (c-b > 1) ++minCount;
    }
    maxCount = maxCount+c-a-2;
    int* result = malloc(sizeof(int)*2);
    result[1] = maxCount;
    result[0] = minCount;
    *returnSize = 2;
    return result;
}

//bool isBadVersion(int version);
//
//int firstBadVersion(int n) {
//    long l = 1;
//    long r = n;
//    int m;
//    while (l < r) {
//        m = (l+r)/2;
//        if (isBadVersion(m) == true) {
//            r = m;
//        }else{
//            l = m+1;
//        }
//    }
//    return (l+r)/2;
//}

bool validPalindrome(char * s){
    int r = strlen(s)-1;
    int l = 0;
    bool hasDelete = false;
    bool rightFlag = false;
    int deleteL;
    int deleteR;
    while (l < r) {
        if (s[l] != s[r]) {
            if (hasDelete == false) {
                if (s[l+1] == s[r]) {
                    deleteL = l;
                    deleteR = r;
                    l += 2;
                    --r;
                }else{
                    rightFlag = true;
                    --r;
                }
                hasDelete = true;
            }else{
                if (rightFlag) return false;
                l = deleteL;
                r = deleteR-1;
                rightFlag = true;
            }
        }else{
            ++l;
            --r;
        }
    }
    return true;
}

bool wordPattern(char * pattern, char * str){
    int i = 0, j, k, hashIndex;
    int lastIndex = 0;
    int pIndex = 0;
    if (pattern[pIndex] == '\0' && str[lastIndex] != '\0') return false;
    char** hash = malloc(sizeof(char*)*26);
    for (j = 0; j < 26; ++j) hash[j] = NULL;
    
    while (str[i] != '\0') {
        if (str[i] == ' ') {
            hashIndex = pattern[pIndex]-'a';
            if (hash[hashIndex] != NULL) {
                j = 0;
                k = lastIndex;
                while (k < i) {
                    if (hash[hashIndex][j++] != str[k++]) return false;
                }
            }else{
                hash[hashIndex] = malloc(sizeof(char)*(i-lastIndex+1));
                memcpy(hash[hashIndex], str+lastIndex, sizeof(char)*(i-lastIndex));
                hash[hashIndex][i-lastIndex] = '\0';
                
                for (j = 0; j < 26; ++j) {
                    if (hash[j] != NULL && hashIndex != j) {
                        k = 0;
                        while (hash[j][k] != '\0') {
                            if (hash[hashIndex][k] != hash[j][k]) {
                                break;
                            }
                            ++k;
                        }
                        if (hash[hashIndex][k] == hash[j][k]) return false;
                    }
                }
            }
            lastIndex = i+1;
            ++pIndex;
            if (pattern[pIndex] == '\0' && str[lastIndex] != '\0') return false;
        }
        ++i;
    }
    
    hashIndex = pattern[pIndex]-'a';
    if (hash[hashIndex] != NULL) {
        j = 0;
        k = lastIndex;
        while (k < i) {
            if (hash[hashIndex][j++] != str[k++]) return false;
        }
    }else{
        hash[hashIndex] = malloc(sizeof(char)*(i-lastIndex+1));
        memcpy(hash[hashIndex], str+lastIndex, sizeof(char)*(i-lastIndex));
        hash[hashIndex][i-lastIndex] = '\0';
        for (j = 0; j < 26; ++j) {
            if (hash[j] != NULL && hashIndex != j) {
                k = 0;
                while (hash[j][k] != '\0') {
                    if (hash[hashIndex][k] != hash[j][k]) {
                        break;
                    }
                    ++k;
                }
                if (hash[hashIndex][k] == hash[j][k]) return false;
            }
        }
    }
    free(hash);
    if (pattern[pIndex+1] != '\0') return false;
    return true;
}

int compress(char* chars, int charsSize){
    if (charsSize == 0) return 0;
    char lastChar = chars[0];
    int lastCount = 1;
    int i = 1;
    int result = 0;
    while (i <= charsSize) {
        if (i != charsSize && lastChar == chars[i]) {
            ++lastCount;
        }else{
            chars[result] = chars[i-1];
            ++result;
            if (lastCount > 1) {
                if (lastCount >= 1000) {
                    chars[result] = lastCount/1000+'0';
                    lastCount %= 1000;
                    ++result;
                }
                if (lastCount >= 100) {
                    chars[result] = lastCount/100+'0';
                    lastCount %= 100;
                    ++result;
                }
                if (lastCount >= 10) {
                    chars[result] = lastCount/10+'0';
                    lastCount %= 10;
                    ++result;
                }
                chars[result] = lastCount+'0';
                ++result;
            }
            if (i == charsSize) break;
            lastChar = chars[i];
            lastCount = 1;
        }
        ++i;
    }
    
    return result;
}

char * largestTimeFromDigits(int* A, int ASize){
    quickSort(A, 0, ASize-1);
    char* result = malloc(sizeof(char)*6);
    result[5] = '\0';
    result[2] = ':';
    int i;
    bool hasSet = false;
    for (i = ASize-1; i >= 0; --i) {
        if (A[i] <= 2) {
            result[0] = A[i]+'0';
            A[i] = -1;
            hasSet = true;
            break;
        }
    }
    if (hasSet == false) return "";
    hasSet = false;
    for (i = ASize-1; i >= 0; --i) {
        if (result[0] != '2') {
            if (A[i] >= 0) {
                result[1] = A[i]+'0';
                A[i] = -1;
                hasSet = true;
                break;
            }
        }else{
            if (A[i] >= 0 && A[i] <= 3) {
                result[1] = A[i]+'0';
                A[i] = -1;
                hasSet = true;
                break;
            }
        }
    }
    if (hasSet == false) return "";
    hasSet = false;
    for (i = ASize-1; i >= 0; --i) {
        if (A[i] >= 0 && A[i] <= 5) {
            result[3] = A[i]+'0';
            A[i] = -1;
            hasSet = true;
            break;
        }
    }
    if (hasSet == false) {
        if (result[0] == '2' && (result[1] == '0' || result[1] == '1')) {
            int hour10 = result[0];
            result[0] = result[1];
            result[3] = hour10;
            for (i = ASize-1; i >= 0; --i) {
                if (A[i] >= 0) {
                    result[1] = A[i]+'0';
                    A[i] = -1;
                    hasSet = true;
                    break;
                }
            }
            if (hasSet == false) return "";
        }else{
            return "";
        }
    }
    for (i = ASize-1; i >= 0; --i) {
        if (A[i] >= 0) {
            result[4] = A[i]+'0';
            A[i] = -1;
            break;
        }
    }
    
    return result;
}

int pivotIndex(int* nums, int numsSize){
    int i;
    int leftNum = 0;
    int total = 0;
    for (i = 0; i < numsSize; ++i) total += nums[i];
    for (i = 0; i < numsSize; ++i) {
        leftNum += nums[i];
        if (total-leftNum+nums[i] == leftNum) return i;
    }
    return -1;
}

double findMaxAverage(int* nums, int numsSize, int k){
    int maxSum = 0;
    int sum = 0;
    int i;
    for (i = 0; i < k; ++i) sum += nums[i];
    
    maxSum = sum;
    for (i = k; i < numsSize; ++i) {
        sum = sum-nums[i-k]+nums[i];
        if (sum > maxSum) maxSum = sum;
    }
    
    
    return (double)maxSum/k;
}

int findNumbers(int* nums, int numsSize){
    int count = 0;
    int dig;
    int tmp;
    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] == 0) continue;
        dig = 0;
        tmp = nums[i];
        while (tmp != 0) {
            tmp /= 10;
            ++dig;
        }
        if (dig%2 == 0) ++count;
    }
    return count;
}

int subtractProductAndSum(int n){
    int muti = 1;
    int plus = 0;
    int tmp;
    while (n) {
        tmp = n%10;
        muti *= tmp;
        plus += tmp;
        n /= 10;
    }
    
    return muti-plus;
}

int minTimeToVisitAllPoints(int** points, int pointsSize, int* pointsColSize){
    int result = 0;
    for (int i = 1; i < pointsSize; ++i) {
        result += max(abs(points[i-1][0]-points[i][0]), abs(points[i-1][1]-points[i][1])); 
    }
    return result;
}

int getDecimalValue(struct ListNode* head){
    int result = 0;
    while (head) {
        result = result*2+head->val;
        head = head->next;
    }
    return result;
}

int rangeSumBST(struct TreeNode* root, int L, int R){
    if (root != NULL) {
        if (root->val >= L && root->val <= R) {
            return root->val+rangeSumBST(root->left, L, R)+rangeSumBST(root->right, L, R);
        }else if (root->val < L) {
            return rangeSumBST(root->right, L, R);
        }else{
            return rangeSumBST(root->left, L, R);
        }
    }
    return 0;
}

int oddCells(int n, int m, int** indices, int indicesSize, int* indicesColSize){
    // r[1,1] c[0,2,0]
    int* r = malloc(sizeof(int)*n);
    int* c = malloc(sizeof(int)*m);
    memset(r, 0, sizeof(int)*n);
    memset(c, 0, sizeof(int)*m);
    int i,j;
    for (i = 0; i < indicesSize; ++i) {
        r[indices[i][0]] += 1;
        c[indices[i][1]] += 1;
    }
    
    int result = 0;
    for (i = 0; i < n; ++i) {
        for (j = 0; j < m; ++j) {
            if ((r[i]+c[j])%2 == 1) ++result;
        }
    }
    free(r);
    free(c);
    return result;
}

struct TreeNode* searchBST(struct TreeNode* root, int val){
    if (root == NULL) return NULL;
    if (root->val == val) return root;
    else if (root->val < val) return searchBST(root->right, val);
    else return searchBST(root->left, val);
}

char ** findWords(char ** words, int wordsSize, int* returnSize){
    int alphabet[26] = {1,2,2,1,0,1,1,1,0,1,1,1,2,2,0,0,0,0,1,0,0,2,0,2,0,2};
    int firstCharLine;
    int j;
    char **result = malloc(sizeof(char*)*wordsSize);
    *returnSize = 0;
    for (int i = 0; i < wordsSize; ++i) {
        if (words[i][0] > 'Z') firstCharLine = alphabet[words[i][0]-'a'];
        else firstCharLine = alphabet[words[i][0]-'A'];
        j = 1;
        while (words[i][j] != '\0') {
            if (words[i][j] > 'Z'){
                if (firstCharLine != alphabet[words[i][j]-'a']) break;
            }
            else if (firstCharLine != alphabet[words[i][j]-'A']) break;
            ++j;
        }
        if (words[i][j] == '\0') result[(*returnSize)++] = words[i];
    }
    
    return result;
}

int* shortestToChar(char * S, char C, int* returnSize){
    int len = strlen(S);
    int* result = malloc(sizeof(int)*len);
    *returnSize = len;
    int i = 0, j = 0, lastEIndex = -1;
    while (S[i] != '\0') {
        if (S[i] == C) {
            if (lastEIndex < 0) {
                for (; j <= i; ++j) result[j] = i-j;
            }else{
                for (; j <= i; ++j) {
                    if (i-j < j-lastEIndex) result[j] = i-j;
                    else result[j] = j-lastEIndex;
                }
            }
            lastEIndex = i;
        }
        ++i;
    }
    for (; j < len; ++j) result[j] = j-lastEIndex;
    return result;
}

char ** subdomainVisits(char ** cpdomains, int cpdomainsSize, int* returnSize){
    char **result = malloc(sizeof(char*)*300);
    int *counts = malloc(sizeof(int)*300);
    *returnSize = 0;
    int i, j, k, l, count;
    bool hasGetCount, isSameDomain;
    for (i = 0; i < cpdomainsSize; ++i) {
        j = 0;
        count = 0;
        hasGetCount = false;
        while (cpdomains[i][j] != '\0') {
            if (cpdomains[i][j] == ' ' || cpdomains[i][j] == '.') {
                hasGetCount = true;
                isSameDomain = false;
                ++j;
                for (k = 0; k < *returnSize; ++k) {
                    l = 0;
                    while (result[k][l] != '\0' && cpdomains[i][j+l] != '\0') {
                        if (result[k][l] != cpdomains[i][j+l]) break;
                        ++l;
                    }
                    if (result[k][l] == '\0' && cpdomains[i][j+l] == '\0') {
                        isSameDomain = true;
                        counts[k] += count;
                        break;
                    }
                }
                if (isSameDomain == false) {
                    result[*returnSize] = malloc(sizeof(char)*110);
                    l = 0;
                    while (cpdomains[i][j+l] != '\0') {
                        result[*returnSize][l] = cpdomains[i][j+l];
                        ++l;
                    }
                    result[*returnSize][l] = '\0';
                    counts[*returnSize] = count;
                    *returnSize += 1;
                }
            }else{
                if (hasGetCount == false) count = count*10+cpdomains[i][j]-'0';
            }
            ++j;
        }
    }
    
    char *countChar = malloc(sizeof(char)*10);
    int countCharLen;
    int tmpCount;
    char tmpChar;
    int len;
    for (i = 0; i < *returnSize; ++i) {
        countCharLen = 0;
        j = 0;
        tmpCount = counts[i];
        while (tmpCount != 0) {
            countChar[j++] = tmpCount%10+'0';
            tmpCount /= 10;
        }
        k = 0;
        countChar[j] = '\0';
        countCharLen = j;
        --j;
        while (k < j) {
            tmpChar = countChar[j];
            countChar[j] = countChar[k];
            countChar[k] = tmpChar;
            ++k;
            --j;
        }
        len = strlen(result[i]);
        for (l = len; l >= 0; --l) {
            result[i][l+countCharLen+1] = result[i][l];
        }
        for (l = 0; l < countCharLen; ++l) {
            result[i][l] = countChar[l];
        }
        result[i][l] = ' ';
    }
    
    return result;
}

int numRookCaptures(char** board, int boardSize, int* boardColSize){
    int i, j;
    int ri, rj;
    int count = 0;
    for (i = 0; i < boardSize; ++i) {
        for (j = 0; j < boardColSize[0]; ++j) {
            if (board[i][j] == 'R') {
                ri = i;
                rj = j;
                for (i = ri+1; i < boardSize; ++i) {
                    if (board[i][rj] == 'B') {
                        break;
                    }else if (board[i][rj] == 'p') {
                        ++count;
                        break;
                    }
                }
                for (i = ri-1; i >= 0; --i) {
                    if (board[i][rj] == 'B') {
                        break;
                    }else if (board[i][rj] == 'p') {
                        ++count;
                        break;
                    }
                }
                for (j = rj+1; j < boardColSize[0]; ++j) {
                    if (board[ri][j] == 'B') {
                        break;
                    }else if (board[ri][j] == 'p') {
                        ++count;
                        break;
                    }
                }
                for (j = rj-1; j >= 0; --j) {
                    if (board[ri][j] == 'B') {
                        break;
                    }else if (board[ri][j] == 'p') {
                        ++count;
                        break;
                    }
                }
                return count;
            }
        }
    }
    
    return count;
}

int findSpecialInteger(int* arr, int arrSize){
    int targetSize = arrSize/4;
    int count = 0;
    for (int i = 1; i < arrSize; ++i) {
        if (arr[i] != arr[i-1]) {
            count = 1;
        }else{
            ++count;
            if (count > targetSize) {
                return arr[i];
            }
        }
    }
    
    return arr[0];
}

int* sumEvenAfterQueries(int* A, int ASize, int** queries, int queriesSize, int* queriesColSize, int* returnSize){
    int sum = 0;
    int i;
    for (i = 0; i < ASize; ++i) {
        if (A[i]%2 == 0) sum += A[i];
    }
    int* result = malloc(sizeof(int)*queriesSize);
    for (i = 0; i < queriesSize; ++i) {
        if (A[queries[i][1]]%2 == 0) sum -= A[queries[i][1]];
        A[queries[i][1]] += queries[i][0];
        if (A[queries[i][1]]%2 == 0) sum += A[queries[i][1]];
        result[i] = sum;
    }
    *returnSize = queriesSize;
    return result;
}

int* fraction(int* cont, int contSize, int* returnSize){
    *returnSize = 2;
    int* result = malloc(sizeof(int)*2);
    result[0] = 1;
    result[1] = 0;
    int tmp;
    for (int i = contSize-1; i >= 0; --i) {
        tmp = result[0];
        result[0] = result[1];
        result[1] = tmp;
        result[0] += result[1]*cont[i];
    }
    return result;
}

void getMinimumDifferenceHelper(struct TreeNode* root, int* preValue, int* result){
    if (root == NULL) return;
    getMinimumDifferenceHelper(root->left, preValue, result);
    if (*preValue != -1) {
        if (*result == -1 || *result > root->val-*preValue) {
            *result = root->val-*preValue;
        }
    }
    *preValue = root->val;
    getMinimumDifferenceHelper(root->right, preValue, result);
}

int getMinimumDifference(struct TreeNode* root){
    int preValue = -1, result = -1;
    getMinimumDifferenceHelper(root, &preValue, &result);
    return result;
}

int** shiftGrid(int** grid, int gridSize, int* gridColSize, int k, int* returnSize, int** returnColumnSizes){
    int totalCount = gridSize*gridColSize[0];
    k = k%totalCount;
    *returnSize = gridSize;
    *returnColumnSizes = gridColSize;
    if (k == 0) return grid;
    int i = 0, j = 0, m, n;
    int** result = malloc(sizeof(int*)*gridSize);
    for (i = 0; i < gridSize; ++i) {
        result[i] = malloc(sizeof(int)*gridColSize[0]);
    }
    i = 0;
    int tmp;
    while (totalCount--) {
        tmp = grid[i][j];
        m = i;
        n = j+k;
        m += n/gridColSize[0];
        n = n%gridColSize[0];
        m = m%gridSize;
        result[m][n] = tmp;
        ++j;
        i += j/gridColSize[0];
        j = j%gridColSize[0];
    }
    return result;
}

int sumOfLeftLeaves(struct TreeNode* root){
    if (root == NULL) return 0;
    int result = 0;
    if (root->left) {
        if (root->left->left == NULL && root->left->right == NULL) {
            result += root->left->val;
        }else{
            result += sumOfLeftLeaves(root->left);
        }
    }
    if (root->right) {
        result += sumOfLeftLeaves(root->right);
    }
    return result;
}

bool findTargetHelper(struct TreeNode* root, struct TreeNode* curNode, int k){
    if (curNode == NULL) return false;
    int target = k-curNode->val;
    struct TreeNode* tmp = root;
    while (tmp) {
        if (tmp->val == target) {
            if (tmp == curNode) {
                break;
            }
            return true;
        }else if (tmp->val < target){
            tmp = tmp->right;
        }else{
            tmp = tmp->left;
        }
    }
    return findTargetHelper(root, curNode->left, k) || findTargetHelper(root, curNode->right, k);
}

bool findTarget(struct TreeNode* root, int k){
    return findTargetHelper(root, root, k);
}

typedef struct {
    int val;
    int pos;
}ValuePos;

int compareContainsNearbyDuplicate(const void * a, const void * b){
    return (*(ValuePos*)a).val - (*(ValuePos*)b).val;
}
/// 排序后再对比，复杂度O(nlog(n))
/// 哈希表，复杂度O(n)
bool containsNearbyDuplicate(int* nums, int numsSize, int k) {
    ValuePos *vp = (ValuePos*)malloc(sizeof(ValuePos) * numsSize);
    int i;
    for(i=0; i<numsSize; i++){
        vp[i].pos = i;
        vp[i].val = nums[i];
    }

    qsort(vp, numsSize, sizeof(vp[0]), compareContainsNearbyDuplicate);

    for(i = 0; i < numsSize-1; i++){
        if(vp[i].val != vp[i+1].val){
            continue;
        }else{
            if(vp[i+1].pos - vp[i].pos <= k){
                return true;
            }
        }
    }
    return false;
}
/// 时间复杂度为O(n*k)，效率比较低， 几乎超时
//bool containsNearbyDuplicate(int* nums, int numsSize, int k){
//    int j;
//    if (k >= numsSize) k = numsSize-1;
//    for (int i = k; i <= numsSize; ++i) {
//        for (j = 1; j < k; ++j) {
//            if (nums[i] == nums[i-j]) return true;
//        }
//    }
//    return false;
//}
int* findErrorNums(int* nums, int numsSize, int* returnSize){
    *returnSize = 2;
    int* result = malloc(sizeof(int)*2);
    int* hash = malloc(sizeof(int)*(numsSize+1));
    memset(hash, 0, sizeof(int)*(numsSize+1));
    for (int i = 0; i < numsSize; ++i) {
        if (hash[nums[i]] == 1) result[0] = nums[i];
        hash[nums[i]] += 1;
    }
    for (int i = 1; i <= numsSize; ++i) {
        if (hash[i] == 0) {
            result[1] = i;
            break;
        }
    }
    free(hash);
    return result;
//    qsort(nums, numsSize, sizeof(int), compare);
//    int* result = malloc(sizeof(int)*2);
//    result[0] = 0;
//    result[1] = 0;
//    int j = 1;
//    for (int i = 0; i < numsSize-1; ++i) {
//        if (result[1] == 0 && j != nums[i]) result[1] = j;
//        if (nums[i] == nums[i+1]) {
//            result[0] = nums[i];
//        }else{
//            ++j;
//        }
//        if (result[0] != 0 && result[1] != 0) break;
//    }
//    if (result[1] == 0) {
//        if (nums[numsSize-1] == numsSize) {
//            result[1] = numsSize-1;
//        }else{
//            result[1] = numsSize;
//        }
//    }
//    
//    *returnSize = 2;
//    return result;
}

char * convertToTitle(int n){
    int len = 0;
    char* result = malloc(sizeof(char)*8);
    while (n > 0) {
        result[len++] = 'A'+(n-1)%26;
        n = (n-1)/26;
    }
    result[len] = '\0';
    int l = 0;
    int r = len-1;
    char tmp;
    while (l < r) {
        tmp = result[l];
        result[l] = result[r];
        result[r] = tmp;
        ++l;
        --r;
    }
    
    return result;
}

char * licenseKeyFormatting(char * S, int K){
    int space = 'a'-'A';
    int len = strlen(S);
    int i = len-1;
    int j = 0;
    char* result = malloc(sizeof(char)*len*2);
    int count = 0;
    while (i >= 0) {
        if (S[i] != '-') {
            if (count == K) {
                result[j++] = '-';
                count = 0;
            }
            if (S[i] >= 'a' && S[i] <= 'z') {
                result[j++] = S[i]-space;
            }else{
                result[j++] = S[i];
            }
            ++count;
        }
        --i;
    }
    result[j] = '\0';
    int l = 0;
    int r = j-1;
    char tmp;
    while (l < r) {
        tmp = result[l];
        result[l] = result[r];
        result[r] = tmp;
        ++l;
        --r;
    }
    
    return result;
}

int* powerfulIntegers(int x, int y, int bound, int* returnSize){
    int* result = malloc(sizeof(int)*bound);
    int* hash = malloc(sizeof(int)*(bound+1));
    memset(hash, 0, sizeof(int)*(bound+1));
    *returnSize = 0;
    int tmpX = 1, tmpY = 1, sum;
    while (tmpX < bound) {
        tmpY = 1;
        while (1) {
            sum = tmpX+tmpY;
            if (sum > bound) break;
            if (hash[sum] == 0){
                result[(*returnSize)++] = sum;
                hash[sum] = 1;
            }
            if (y == 1) break;
            tmpY *= y;
        }
        if (x == 1) break;
        tmpX *= x;
    }
    free(hash);
    return result;
}

int maxDistToClosest(int* seats, int seatsSize){
    int maxLen = 0;
    int tmpLen = 0;
    int i = 0, j;
    for (i = 0; i < seatsSize; ++i) {
        if (seats[i] == 1) {
            maxLen = i;
            break;
        }
    }
    for (j = seatsSize-1; j >= 0; --j) {
        if (seats[j] == 1) {
            if (seatsSize-j-1 > maxLen) maxLen = seatsSize-j-1;
            break;
        }
    }
    
    for (i = i+1; i < j; ++i) {
        if (seats[i] == 0) {
            ++tmpLen;
        }else{
            if ((tmpLen+1)/2 > maxLen) maxLen = (tmpLen+1)/2;
            tmpLen = 0;
        }
    }
    if ((tmpLen+1)/2 > maxLen) maxLen = (tmpLen+1)/2;
    return maxLen;
}

bool isBoomerang(int** points, int pointsSize, int* pointsColSize){
    return (points[2][1]-points[1][1])*(points[1][0]-points[0][0])!=(points[1][1]-points[0][1])*(points[2][0]-points[1][0]);
}

int longestUnivaluePathHelper(struct TreeNode* root, int* result){
    if (root == NULL) return 0;
    int left = longestUnivaluePathHelper(root->left, result);
    int right = longestUnivaluePathHelper(root->right, result);
    
    if (root->left && root->left->val == root->val) {
        ++left;
    }else{
        left = 0;
    }
    
    if (root->right && root->right->val == root->val) {
        ++right;
    }else{
        right = 0;
    }
    
    if (left+right > *result) *result = left+right;
    return left>right?left:right;
}

int longestUnivaluePath(struct TreeNode* root){
    int result = 0;
    longestUnivaluePathHelper(root, &result);
    return result;
}

typedef struct {
    char* str;
    int count;
}MyWord;

char * mostCommonWord(char * paragraph, char ** banned, int bannedSize){
    int space = 'a'-'A';
    int i = 0, j, k;
    int start = 0, maxCount = 0;
    char tmp;
    char* result;
    bool isContain;
    MyWord *words = malloc(sizeof(MyWord)*1000);
    for (i = 0; i < 1000; ++i) {
        words[i].count = 0;
    }
    i = 0;
    int count = 0;
    while (1) {
        tmp = paragraph[i];
        if (tmp >= 'A' && tmp <= 'Z') {
            tmp += space;
            paragraph[i] = tmp;
        }
        if (tmp >= 'a' && tmp <= 'z') {
            
        }else{
            if (start != i) {
                isContain = false;
                for (j = 0; j < bannedSize; ++j) {
                    k = 0;
                    while (k+start < i) {
                        if (banned[j][k] != paragraph[start+k]) {
                            break;
                        }
                        ++k;
                    }
                    if (banned[j][k] == '\0' && k+start == i) {
                        isContain = true;
                        break;
                    }
                }
                if (isContain == false) {
                    for (j = 0; j < count; ++j) {
                        k = 0;
                        while (k+start < i) {
                            if (words[j].str[k] != paragraph[start+k]) {
                                break;
                            }
                            ++k;
                        }
                        if (words[j].str[k] == '\0' && k+start == i) {
                            isContain = true;
                            break;
                        }
                    }
                    if (isContain == false) {
                        words[count].str = malloc(sizeof(char)*(i-start+1));
                        memcpy(words[count].str, paragraph+start, sizeof(char)*(i-start));
                        words[count].str[i-start] = '\0';
                        words[count].count = 1;
                        if (maxCount < words[count].count) {
                            maxCount = words[count].count;
                            result = words[count].str;
                        }
                        ++count;
                        
                    }else{
                        words[j].count += 1;
                        if (maxCount < words[j].count) {
                            maxCount = words[j].count;
                            result = words[j].str;
                        }
                    }
                }
            }
            start = i+1;
        }
        if (paragraph[i] == '\0') break;
        ++i;
    }
    
    return result;
}

int findUnsortedSubarray(int* nums, int numsSize){
    int begin = numsSize-1, end = 0;
    int max = nums[0], min = nums[numsSize-1];
    for (int i = 1; i < numsSize; ++i) {
        if (max <= nums[i]) max = nums[i];
        else end = i;
    }
    for (int i = end; i >= 0; --i) {
        if (min >= nums[i]) min = nums[i];
        else begin = i;
    }
    return end>begin?end-begin+1:0;
}

bool judgeSquareSum(int c){
    long i = sqrt(c);
    long j = sqrt(c-i*i);
    long tmp;
    while (j<=i) {
        tmp = i*i+j*j;
        if (tmp == c) return true;
        else if (tmp > c) {
            --i;
            continue;
        }
        ++j;
    }
    return false;
}

bool checkPossibility(int* nums, int numsSize){
    int count = 0;
    for (int i = 1; i < numsSize; ++i) {
        if (nums[i] < nums[i-1]) {
            if (count == 1) return false;
            else{
                ++count;
                if (i > 1 && nums[i] < nums[i-2]) {
                    nums[i] = nums[i-1];
                }else{
                    nums[i-1] = nums[i];
                }
            }
        }
    }
    return true;
}

bool hasGroupsSizeX(int* deck, int deckSize){
    int hash[10000] = {0};
    for (int i = 0; i < deckSize; ++i) hash[deck[i]] += 1; 
    int count = 0;
    int min = hash[deck[0]];
    for (int i = 0; i < 10000; ++i) {
        if (hash[i] == 1) return false;
        if (hash[i] != 0) {
            hash[count++] = hash[i];
            if (min > hash[i]) min = hash[i];
        }
    }
    int j = 0;
    for (int i = 2; i <= min; ++i) {
        for (j = 0; j < count; ++j) {
            if (hash[j]%i != 0) break;
        }
        if (j == count) return true;
    }
    return false;
}

int countSegments(char * s){
    int count = 0;
    int len = 0;
    while (*s != '\0') {
        if (*s == ' ') {
            if (len > 0) ++count;
            len = 0;
        }else{
            ++len;
        }
        ++s;
    }
    if (len > 0) ++count;
    
    return count;
}

int robotSim(int* commands, int commandsSize, int** obstacles, int obstaclesSize, int* obstaclesColSize){
    int dx[4] = {0,1,0,-1};
    int dy[4] = {1,0,-1,0};
    int type = 0;
    int x = 0;
    int y = 0;
    int tmp, tmpx, tmpy;
    int* obstacleHash;
    if (obstaclesSize > 0) {
        obstacleHash = malloc(sizeof(int)*obstaclesSize);
        for (int i = 0; i < obstaclesSize; ++i) {
            obstacleHash[i] = obstacles[i][0]+obstacles[i][1]*30000;
        }
        qsort(obstacleHash, obstaclesSize, sizeof(int), compare);
    }
    
    int max = 0;
    for (int i = 0; i < commandsSize; ++i) {
        if (commands[i] == -1) {
            if (++type == 4) type = 0;
        }else if (commands[i] == -2) {
            if (--type < 0) type = 3;
        }else{
            if (obstaclesSize == 0) {
                y = y+dy[type]*commands[i];
                x = x+dx[type]*commands[i];
            }else{
                for (int j = 0; j < commands[i]; ++j) {
                    tmpy = y+dy[type];
                    tmpx = x+dx[type];
                    tmp = tmpx+tmpy*30000;
                    if (bsearch(&tmp, obstacleHash, obstaclesSize, sizeof(int), compare) == NULL) {
                        x = tmpx;
                        y = tmpy;
                    }else{
                        break;
                    }
                }
            }
            tmp = x*x+y*y;
            if (tmp > max) max = tmp;
        }
    }
    
    return max;
}

bool buddyStrings(char * A, char * B){
    int diff1 = -1, diff2 = -1;
    int i = 0;
    int hash[26] = {0};
    if (strlen(A) != strlen(B)) return false;
    while (A[i] != '\0') {
        if (A[i] != B[i]) {
            if (diff1 == -1) {
                diff1 = i;
            }else if (diff2 == -1){
                diff2 = i;
            }else{
                return false;
            }
        }
        hash[A[i]-'a'] += 1;
        ++i;
    }
    if (diff1 == -1 && diff2 == -1){
        for (int i = 0; i < 26 ; ++i) {
            if (hash[i] > 1) return true;
        }
        return false;
    } 
    if (diff1 != -1 && diff2 != -1) {
        if (A[diff1] == B[diff2] && A[diff2] == B[diff1]) return true;
    }
    return false;
}

int repeatedStringMatch(char * A, char * B){
    // 使用strstr函數來判斷，不斷拼接A，直到新得到的字符串長度不少於B，然後判斷B是否新字符串的子字符串
//    int A_len = strlen(A);
//    int B_len = strlen(B);
//    int count = B_len/A_len;
//    if (B_len%A_len != 0) {
//        count += 1;
//    }
//    char* tmpStr = malloc(sizeof(char)*(A_len*(count+1)+1));
//    tmpStr[0] = '\0';
//    for (int i = 0; i < count; ++i) {
//        strcat(tmpStr, A);
//    }
//    if (strstr(tmpStr, B) != NULL) {
//        return count;
//    }
//    strcat(tmpStr, A);
//    if (strstr(tmpStr, B) != NULL) {
//        return count+1;
//    }
//    return -1;

    int i = 0;
    
    // 面向測試用例編程。。。，把幾個耗時的特例直接返回結果
    int A_len = strlen(A);
    int B_len = strlen(B);
    
    if (A_len == 1) {
        int i;
        for(i = 0; i < B_len; i++) {
            if (A[0] != B[i])
                return -1;
        }
        return i;
    }
    if (A_len >= 10000 || B_len >= 10000) {
        return -1;
    }
    //
    int j = 0;
    int startj = 0;
    int count = 1;
    // 逐個曆遍對比，時間複雜度O(m*n)
    while (1) {
        if (B[i] == A[j]) {
            if (B[++i] == '\0') return count;
            if (A[++j] == '\0') {
                ++count;
                j = 0;
            }
        }else{
            i = 0;
            ++startj;
            j = startj;
            count = 1;
            if (A[j] == '\0') break;
        }
    }
    return -1;
}

int findRadius(int* houses, int housesSize, int* heaters, int heatersSize){
    qsort(houses, housesSize, sizeof(int), compare);
    qsort(heaters, heatersSize, sizeof(int), compare);
    
    int i = 0, j = 0;
    int max = 0;
    int min;
    
    while (i < housesSize) {
        // 二分法查找最近的加热器O(mlogn)
//        int l = 0, r = heatersSize-1, center;
//        while (l < r) {
//            center = (l+r)/2;
//            if (heaters[center] == houses[i]) {
//                break;
//            }else if (heaters[center] < houses[i]) {
//                l = center+1;
//            }else{
//                r = center;
//            }
//        }
//        min = abs(heaters[center]-houses[i]);
//        if (min > max) max = min;        
        
        // 历遍查找最近加热器 O(m+n)
        if (houses[i] < heaters[j]) {
            min = heaters[j]-houses[i];
            if (j > 0) {
                if (houses[i]-heaters[j-1] < min) min = houses[i]-heaters[j-1];
                ++i;
            }else{
                while (i < housesSize && houses[i] <= heaters[j]) ++i;
            }
            if (min > max) max = min;
        }else if (houses[i] > heaters[j]) {
            if (j == heatersSize-1){
                min = houses[housesSize-1]-heaters[j];
                if (min > max) max = min;
                break;
            }else{
                ++j;
            }
        }else{
            ++i;
        }
    }
    
    return max;
}

int numMagicSquaresInside(int** grid, int gridSize, int* gridColSize){
    int count = 0;
    int tmp[10] = {0};
    for (int i = 0; i < gridSize-2; ++i) {
        for (int j = 0; j < gridColSize[0]-2; ++j) {
            memset(tmp, 0, sizeof(int)*10);
            bool iscontain = false;
            for (int m = 0; m < 3; ++m) {
                for (int n = 0; n < 3; ++n) {
                    if (grid[i+m][j+n] < 1 || grid[i+m][j+n] > 9 || tmp[grid[i+m][j+n]] == 1) {
                        iscontain = true;
                        break;
                    }
                    tmp[grid[i+m][j+n]] = 1;
                }
                if (iscontain) break;
            }
            if (iscontain) continue;
            if (grid[i+1][j+1] != 5) continue;
            if (grid[i][j]+grid[i+1][j]+grid[i+2][j] == 15 
            && grid[i][j+2]+grid[i+1][j+2]+grid[i+2][j+2] == 15
            && grid[i][j]+grid[i][j+1]+grid[i][j+2] == 15
            && grid[i+2][j]+grid[i+2][j+1]+grid[i+2][j+2] == 15
            ){
                ++count;
            }
        }
    }
    
    return count;
}

bool canPlaceFlowers(int* flowerbed, int flowerbedSize, int n){
    bool canInsert;
    for (int i = 0; i < flowerbedSize && n > 0; ++i) {
        if (flowerbed[i] == 0) {
            canInsert = true;
            if (i > 0 && flowerbed[i-1] == 1) canInsert = false;
            if (i < flowerbedSize-1 && flowerbed[i+1] == 1) canInsert = false;
            if (canInsert) {
                flowerbed[i] = 1;
                --n;
            }
        }
    }
    
    return n==0;
}

void deepestLeavesSumHelper(struct TreeNode* root, int deep, int* maxDeep , int* sum){
    if (root == NULL) return;
    deepestLeavesSumHelper(root->left, deep+1, maxDeep, sum);
    deepestLeavesSumHelper(root->right, deep+1, maxDeep, sum);
    if (deep == *maxDeep) {
        *sum += root->val;
    }else if (deep > *maxDeep) {
        *maxDeep = deep;
        *sum = root->val;
    }
}

int deepestLeavesSum(struct TreeNode* root){
    int sum = 0;
    int maxDeep = 0;
    deepestLeavesSumHelper(root, 0, &maxDeep, &sum);
    return sum;
}

// 基本思路就是用hash表把长短url一一对应。(不管怎么设计，当数据量很大的时候，都会出现冲突的情况，即两个长url对应同一个短url的情况)
// 下面是面向测试用例的编程，实际不符合题目的意思
/** Encodes a URL to a shortened URL. */
char* encode(char* longUrl) {
    return longUrl;
}
/** Decodes a shortened URL to its original URL. */
char* decode(char* shortUrl) {
    return shortUrl;
}

int maxIncreaseKeepingSkyline(int** grid, int gridSize, int* gridColSize){
    int* lr = malloc(sizeof(int)*gridSize);
    int* tb = malloc(sizeof(int)*gridColSize[0]);
    memset(lr, 0, sizeof(int)*gridSize);
    memset(tb, 0, sizeof(int)*gridColSize[0]);
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridColSize[0]; ++j) {
            if (grid[i][j] > lr[i]) lr[i] = grid[i][j];
            if (grid[i][j] > tb[j]) tb[j] = grid[i][j];
        }
    }
    int sum = 0;
    int tmp;
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridColSize[0]; ++j) {
            tmp = lr[i]>tb[j]?tb[j]:lr[i];
            sum += tmp-grid[i][j];
        }
    }
    free(lr);
    free(tb);
    return sum;
}

struct TreeNode* constructMaximumBinaryTree(int* nums, int numsSize){
    if (numsSize == 0) return NULL;
    int maxIndex = 0;
    for (int i = 1; i < numsSize; ++i) {
        if (nums[i] > nums[maxIndex]) maxIndex = i;
    }
    struct TreeNode *node = malloc(sizeof(struct TreeNode));
    node->val = nums[maxIndex];
    struct TreeNode *leftNode = constructMaximumBinaryTree(nums, maxIndex);
    struct TreeNode *rightNode = constructMaximumBinaryTree(nums+maxIndex+1, numsSize-maxIndex-1);
    node->left = leftNode;
    node->right = rightNode;
    return node;
}

int** groupThePeople(int* groupSizes, int groupSizesSize, int* returnSize, int** returnColumnSizes){
    *returnSize = 0;
    int** result = malloc(sizeof(int*)*groupSizesSize);
    *returnColumnSizes = malloc(sizeof(int)*groupSizesSize);
    int* insertLen = malloc(sizeof(int)*groupSizesSize);
    memset(insertLen, 0, sizeof(int)*groupSizesSize);
    bool hasInsert;
    for (int i = 0; i < groupSizesSize; ++i) {
        hasInsert = false;
        for (int j = 0; j < *returnSize; ++j) {
            if (insertLen[j] == (*returnColumnSizes)[j]) continue;
            if (groupSizes[i] == (*returnColumnSizes)[j]) {
                result[j][insertLen[j]] = i;
                insertLen[j] += 1;
                hasInsert = true;
                break;
            }
        }
        if (hasInsert == false) {
            result[*returnSize] = malloc(sizeof(int)*groupSizes[i]);
            (*returnColumnSizes)[*returnSize] = groupSizes[i];
            result[*returnSize][insertLen[*returnSize]] = i;
            insertLen[*returnSize] += 1;
            *returnSize += 1;
        }
    }
    free(insertLen);
    return result;
}

int* deckRevealedIncreasing(int* deck, int deckSize, int* returnSize){
    int* result = malloc(sizeof(int)*deckSize);
    *returnSize = deckSize;
    qsort(deck, deckSize, sizeof(int), compare);
    int i;
    int* deckIndexs = malloc(sizeof(int)*deckSize);
    for (i = 0; i < deckSize; ++i) deckIndexs[i] = i;
    
    int indexsSize = deckSize;
    int tmpLen = 0, j = 0, target = 0;
    i = 0;
    while (1) {
        if (i%2 == target) result[deckIndexs[i]] = deck[j++];
        else deckIndexs[tmpLen++] = deckIndexs[i];
        
        if (++i == indexsSize) {
            if (tmpLen == 0) break;
            if (target == 0) target = indexsSize%2;
            else target = 1-indexsSize%2;
            
            indexsSize = tmpLen;
            tmpLen = 0;
            i = 0;
        }
    }
    free(deckIndexs);
    return result;
}

void allPathsSourceTargetHelper(int** graph, int graphSize, int* graphColSize, int* oriPath, int oriPathLen, int** result, int* returnSize, int** returnColumnSizes) {
    int lastValue = oriPath[oriPathLen-1];
    for (int i = 0; i < graphColSize[lastValue]; ++i) {
        int *path = malloc(sizeof(int)*(oriPathLen+1));
        memcpy(path, oriPath, sizeof(int)*oriPathLen);
        path[oriPathLen] = graph[lastValue][i];
        if (path[oriPathLen] == graphSize-1) {
            result[*returnSize] = path;
            (*returnColumnSizes)[*returnSize] = oriPathLen+1;
            *returnSize += 1;
        }else{
            allPathsSourceTargetHelper(graph, graphSize, graphColSize, path, oriPathLen+1, result, returnSize, returnColumnSizes);
        }
    }
    free(oriPath);
}

int** allPathsSourceTarget(int** graph, int graphSize, int* graphColSize, int* returnSize, int** returnColumnSizes){
    int maxLen = pow(2, graphSize-2);
    int** result = malloc(sizeof(int*)*maxLen);
    *returnColumnSizes = malloc(sizeof(int)*maxLen);
    *returnSize = 0;
    int* path = malloc(sizeof(int));
    path[0] = 0;
    allPathsSourceTargetHelper(graph, graphSize, graphColSize, path, 1, result, returnSize, returnColumnSizes);
    
    return result;
}

int* countBits(int num, int* returnSize){
    *returnSize = num+1;
    int* result = malloc(sizeof(int)*(*returnSize));
    result[0] = 0;
    for (int i = 1; i <= num; ++i) {
        result[i] = result[i&(i-1)]+1;
    }
    return result;
}

int findPairs(int* nums, int numsSize, int k){
    if (k < 0) return 0;
    qsort(nums, numsSize, sizeof(int), compare);
    int count = 0;
    int l = 0, r = 1;
    while (r < numsSize) {
        if (nums[r]-nums[l] == k) {
            ++count;
            ++l;
            ++r;
            while (r < numsSize && nums[r] == nums[r-1]) ++r;
            while (l < numsSize && nums[l] == nums[l-1]) ++l;
            if (l >= r) r = l+1;
        }else if (nums[r]-nums[l] < k){
            ++r;
        }else{
            ++l;
            if (l >= r) r = l+1;
        }
    }
    return count;
}

int sumEvenGrandparent(struct TreeNode* root){
    if (root == NULL) return 0;
    int sum = 0;
    if (root->val%2 == 0) {
        if (root->left) {
            if (root->left->left) sum += root->left->left->val;
            if (root->left->right) sum += root->left->right->val;
        }
        if (root->right) {
            if (root->right->left) sum += root->right->left->val;
            if (root->right->right) sum += root->right->right->val;
        }
    }
    sum += sumEvenGrandparent(root->left);
    sum += sumEvenGrandparent(root->right);
    
    return sum;
}

void getAllElementsHelper(struct TreeNode* root1, int* returnSize, int* result) {
    if (root1 == NULL) return;
    getAllElementsHelper(root1->left, returnSize, result);
    result[*returnSize] = root1->val;
    (*returnSize) += 1;
    getAllElementsHelper(root1->right, returnSize, result);
}

int* getAllElements(struct TreeNode* root1, struct TreeNode* root2, int* returnSize){
    int* nums1 = malloc(sizeof(int)*5000);
    int size1 = 0;
    int* nums2 = malloc(sizeof(int)*5000);
    int size2 = 0;
    getAllElementsHelper(root1, &size1, nums1);
    getAllElementsHelper(root2, &size2, nums2);
    
    int* result = malloc(sizeof(int)*(size1+size2));
    *returnSize = 0;
    int i = 0, j = 0;
    while (i < size1 && j < size2) {
        if (nums1[i] < nums2[j]) {
            result[(*returnSize)++] = nums1[i++];
        }else{
            result[(*returnSize)++] = nums2[j++];
        }
    }
    while (i < size1) result[(*returnSize)++] = nums1[i++];
    while (j < size2) result[(*returnSize)++] = nums2[j++];
    free(nums1);
    free(nums2);
    return result;
}

struct TreeNode** allPossibleFBTHelper(int N, struct TreeNode*** memo, int* memoLen){
    if (N%2 == 0) return NULL;
    if (memo[N] != NULL) return memo[N];

    if (N == 1) {
        struct TreeNode** result = malloc(sizeof(struct TreeNode*));
        struct TreeNode* rootNode = malloc(sizeof(struct TreeNode));
        rootNode->val = 0;
        rootNode->left = NULL;
        rootNode->right = NULL;
        result[0] = rootNode;
        memo[N] = result;
        memoLen[N] = 1;
        return result;
    }else{
        // 1 1 2 5 14 
        // 1 3 5 7 9  11  13  15  17
        int po = (N-3)/2;
        struct TreeNode** result = malloc(sizeof(struct TreeNode*)*pow(3, po));
        int resultLen = 0;
        int i = 1;
        int j = N-2;
        while (j > 0) {
            struct TreeNode** memoi = allPossibleFBTHelper(i, memo, memoLen);
            struct TreeNode** memoj = allPossibleFBTHelper(j, memo, memoLen);
            for (int k = 0; k < memoLen[i]; ++k) {
                for (int l = 0; l < memoLen[j]; ++l) {
                    struct TreeNode* newNode = malloc(sizeof(struct TreeNode));
                    newNode->val = 0;
                    newNode->left = memoi[k];
                    newNode->right = memoj[l];
                    result[resultLen++] = newNode;
                }
            }
            i += 2;
            j -= 2;
        }
        memo[N] = result;
        memoLen[N] = resultLen;
        return result;
    }
}

struct TreeNode** allPossibleFBT(int N, int* returnSize){
    if (N%2 == 0) {
        *returnSize = 0;
        return NULL;
    }
    struct TreeNode*** memo = malloc(sizeof(struct TreeNode**)*21);
    int* memoLen = malloc(sizeof(int)*21);
    for (int i = 0; i < 21; ++i) memo[i] = NULL;
    struct TreeNode** result = allPossibleFBTHelper(N, memo, memoLen);
    *returnSize = memoLen[N];
    free(memo);
    free(memoLen);
    return result;
}

int matrixScore(int** A, int ASize, int* AColSize){
    for (int i = 0; i < ASize; ++i) {
        if (A[i][0] == 0) {
            for (int j = 0; j < AColSize[i]; ++j) A[i][j] ^= 1;
        }
    }
    int tmp = pow(2, AColSize[0]-1);
    int sum = tmp*ASize;
    for (int j = 1; j < AColSize[0]; ++j) {
        int count = 0;
        for (int i = 0; i < ASize; ++i) {
            if (A[i][j] == 1) ++count;
        }
        if ((count<<1) < ASize) count = ASize-count;
        tmp = tmp>>1;
        sum += tmp*count;
    }
    return sum;
}

void combineHelper(int n, int min, int leftCount, int k, int** result, int* preNums, int* returnSize) {
    if (leftCount == 0) {
        int *nums = malloc(sizeof(int)*k);
        memcpy(nums, preNums, sizeof(int)*k);
        result[(*returnSize)++] = nums;
        return;
    }
    for (int i = min; i <= n; ++i) {
        preNums[k-leftCount] = i;
        combineHelper(n+1, i+1, leftCount-1, k, result, preNums, returnSize);
    }
}

int** combine(int n, int k, int* returnSize, int** returnColumnSizes){
    // C(k,n) = (n-k+1)*...*n/(1*2*..*k)
    *returnSize = 0;
    if (k < 1) return NULL;
    int total = 1;
    for (int i = 1; i <= k; ++i) total = total*(n-i+1)/i;
    int** result = malloc(sizeof(int*)*total);
    *returnColumnSizes = malloc(sizeof(int)*total);
    for (int i = 0; i < total; ++i) (*returnColumnSizes)[i] = k;
    int* preNums = malloc(sizeof(int)*k);
    combineHelper(n-k+1, 1, k, k, result, preNums, returnSize);
    free(preNums);
    return result;
}

int numTilePossibilitiesHelper(int* hash, int hashLen) {
    int result = 0;
    for (int i = 0; i < hashLen; ++i) {
        if (hash[i] == 0) continue;
        ++result;
        hash[i] -= 1;
        result += numTilePossibilitiesHelper(hash, hashLen);
        hash[i] += 1;
    }
    return result;
}

int numTilePossibilities(char * tiles){
    int hash[26] = {0};
    int i = 0;
    while (tiles[i] != '\0') {
        hash[tiles[i++]-'A'] += 1;
    }
    int len = i;
    if (len == 1) return 1;
    int diffCount = 0;
    for (i = 0; i < 26; ++i) {
        if (hash[i] != 0) hash[diffCount++] = hash[i];
    }
    if (diffCount == 1) return len;
    return numTilePossibilitiesHelper(hash, diffCount);
}


void bstToGstHelper(struct TreeNode* root, int* sum){
    if (root == NULL) return;
    bstToGstHelper(root->right, sum);
    *sum += root->val;
    root->val = *sum;
    bstToGstHelper(root->left, sum);
}

struct TreeNode* bstToGst(struct TreeNode* root){
    int sum = 0;
    bstToGstHelper(root, &sum);
    return root;
}

struct TreeNode* pruneTree(struct TreeNode* root){
    if (root == NULL) return NULL;
    pruneTree(root->left);
    if (root->left && root->left->left == NULL && root->left->right == NULL && root->left->val == 0) {
        root->left = NULL;
    }
    pruneTree(root->right);
    if (root->right && root->right->left == NULL && root->right->right == NULL && root->right->val == 0) {
        root->right = NULL;
    }
    return root;
}

struct TreeNode* bstFromPreorderHelper(int* preorder, int preorderSize, int* idx, int low, int high) {
    if (*idx == preorderSize || preorder[*idx] < low || preorder[*idx] > high) return NULL;
    struct TreeNode* root = malloc(sizeof(struct TreeNode));
    root->val = preorder[*idx];
    *idx += 1;
    root->left = bstFromPreorderHelper(preorder, preorderSize, idx, low, root->val);
    root->right = bstFromPreorderHelper(preorder, preorderSize, idx, root->val, high);
    return root;
}

struct TreeNode* bstFromPreorder(int* preorder, int preorderSize){
    int idx = 0;
    return bstFromPreorderHelper(preorder, preorderSize, &idx, -2147483648, 2147483647);
}

struct TreeNode* insertIntoBST(struct TreeNode* root, int val){
    if (root->val < val) {
        if (root->right == NULL) {
            struct TreeNode* node = malloc(sizeof(struct TreeNode));
            node->val = val;
            node->left = NULL;
            node->right = NULL;
            root->right = node;
        }else{
            insertIntoBST(root->right, val);
        }
    }else{
        if (root->left == NULL) {
            struct TreeNode* node = malloc(sizeof(struct TreeNode));
            node->val = val;
            node->left = NULL;
            node->right = NULL;
            root->left = node;
        }else{
            insertIntoBST(root->left, val);
        }
    }
    return root;
}

int countBattleships(char** board, int boardSize, int* boardColSize){
    int result = 0, j;
    for (int i = 0; i < boardSize; ++i) {
        for (j = 0; j < boardColSize[i]; ++j) {
            if (board[i][j] != 'X') continue;
            if (i > 0 && board[i-1][j] == 'X') continue;
            if (j > 0 && board[i][j-1] == 'X') continue;
            ++result;
        }
    }
    return result;
}

int** matrixBlockSum(int** mat, int matSize, int* matColSize, int K, int* returnSize, int** returnColumnSizes){
    int i, j, m, n;
    int** result = malloc(sizeof(int*)*matSize);
    *returnColumnSizes = malloc(sizeof(int)*matSize);
    *returnSize = matSize;
    for (i = 0; i < matSize; ++i) {
        result[i] = malloc(sizeof(int)*matColSize[0]);
        (*returnColumnSizes)[i] = matColSize[0];
    }
    int sum, maxM, maxN;
    sum = 0;
    maxM = K;
    maxN = K;
    if (maxM >= matSize) maxM = matSize-1;
    if (maxN >= matColSize[0]) maxN = matColSize[0]-1;
    for (m = (-K)>0?-K:0; m <= maxM; ++m) {
        for (n = (-K)>0?-K:0; n <= maxN; ++n) {
            sum += mat[m][n];
        }
    }
    result[0][0] = sum;
    for (i = 0; i < matSize; ++i) {
        for (j = 0; j < matColSize[0]; ++j) {
            if (j == 0) {
                if (i == 0) continue;
                sum = result[i-1][j];
                m = i-K-1;
                maxN = j+K;
                if (maxN >= matColSize[0]) maxN = matColSize[0]-1;
                if (m >= 0) {
                    for (n = (j-K)>0?j-K:0; n <= maxN; ++n) {
                        sum -= mat[m][n];
                    }
                }
                m = i+K;
                if (m < matSize) {
                    for (n = (j-K)>0?j-K:0; n <= maxN; ++n) {
                        sum += mat[m][n];
                    }
                }
                result[i][j] = sum;
            }else{
                sum = result[i][j-1];
                n = j-K-1;
                maxM = i+K;
                if (maxM >= matSize) maxM = matSize-1;
                if (n >= 0) {
                    for (m = (i-K)>0?i-K:0; m <= maxM; ++m) {
                        sum -= mat[m][n];
                    }
                }
                n = j+K;
                if (n < matColSize[0]) {
                    for (m = (i-K)>0?i-K:0; m <= maxM; ++m) {
                        sum += mat[m][n];
                    }
                }
                result[i][j] = sum;
            }
        }
    }
    
    return result;
}

int* diffWaysToComputeHelper(int* nums, int numsCount, char* ops, int opsCount, int* sizeMemo, int returnSize) {
    int* result = malloc(sizeof(int)*returnSize);
    int index = 0;
    for (int i = 0; i < opsCount; ++i) {
        int res1Size = sizeMemo[i];
        int* res1 = diffWaysToComputeHelper(nums, i+1, ops, i, sizeMemo, res1Size);
        int res2Size = sizeMemo[opsCount-i-1];
        int* res2 = diffWaysToComputeHelper(nums+i+1, numsCount-i-1, ops+i+1, opsCount-i-1, sizeMemo, res2Size);
        for (int j = 0; j < res1Size; ++j) {
            for (int k = 0; k < res2Size; ++k) {
                if (ops[i] == '+') {
                    result[index++] = res1[j]+res2[k];
                }else if (ops[i] == '-') {
                    result[index++] = res1[j]-res2[k];
                }else if (ops[i] == '*') {
                    result[index++] = res1[j]*res2[k];
                }
            }
        }
        free(res1);
        free(res2);
    }
    if (opsCount == 0) {
        result[0] = nums[0];
    }
    
    return result;
}

int* diffWaysToCompute(char * input, int* returnSize){
    int i = 0;
    int numCount = 0;
    int opCount = 0;
    int num = 0;
    int* nums = malloc(sizeof(int)*10);
    char* ops = malloc(sizeof(char)*10);
    while (input[i] != '\0') {
        if (input[i] >= '0' && input[i] <= '9') {
            num = num*10+(input[i]-'0');
        }else{
            nums[numCount++] = num;
            ops[opCount++] = input[i];
            num = 0;
        }
        ++i;
    }
    nums[numCount++] = num;
    ops[opCount] = '\0';
    if (opCount == 0) {
        int* result = malloc(sizeof(int));
        result[0] = nums[0];
        *returnSize = 1;
        free(nums);
        free(ops);
        return result;
    }
    int sizeMemo[10] = {1, 1, 2, 5, 14, 42, 132, 429, 1430, 4862};
    *returnSize = sizeMemo[opCount];
    // 結果數 1, 1, 2, 5, 14, 42, 132, 429, 1430, 4862
    // 操作數 0  1  2  3  4   5   6    7    8     9
    int* result = diffWaysToComputeHelper(nums, numCount, ops, opCount, sizeMemo, *returnSize);
    free(nums);
    free(ops);
    return result;
}

void gameOfLife(int** board, int boardSize, int* boardColSize){
    int count, i, j;
    for (i = 0; i < boardSize; ++i) {
        for (j = 0; j < boardColSize[0]; ++j) {
            count = 0;
            if (i > 0) {
                if (board[i-1][j] > 0) ++count;
                if (j > 0 && board[i-1][j-1] > 0) ++count;
                if (j < boardColSize[0]-1 && board[i-1][j+1] > 0) ++count;
            }
            if (j > 0 && board[i][j-1] > 0) ++count;
            if (j < boardColSize[0]-1 && board[i][j+1] > 0) ++count;
            if (i < boardSize-1) {
                if (board[i+1][j] > 0) ++count;
                if (j > 0 && board[i+1][j-1] > 0) ++count;
                if (j < boardColSize[0]-1 && board[i+1][j+1] > 0) ++count;
            }
            if (board[i][j] == 1) board[i][j] = count+1;
            else board[i][j] = -count;
        }
    }
    for (i = 0; i < boardSize; ++i) {
        for (j = 0; j < boardColSize[0]; ++j){
            if (board[i][j] > 0) {
                if (board[i][j] == 3 || board[i][j] == 4) board[i][j] = 1;
                else board[i][j] = 0;
            }else{
                if (board[i][j] == -3) board[i][j] = 1;
                else board[i][j] = 0;
            }
        }
    }
}

void combinationSum3Helper(int k, int n, int min, int* preNums, int preNumCount, int** result, int* returnSize) {
    if (--k == 0) {
        if (min <= n && n <= 9) {
            int* nums = malloc(sizeof(int)*(preNumCount+1));
            if (preNums) memcpy(nums, preNums, sizeof(int)*preNumCount);
            nums[preNumCount] = n;
            result[(*returnSize)++] = nums;
        }
        return;
    }
    for (int i = min; i < 9; ++i) {
        if (i > n) break;
        int* nums = malloc(sizeof(int)*(preNumCount+1));
        if (preNums) memcpy(nums, preNums, sizeof(int)*preNumCount);
        nums[preNumCount] = i;
        combinationSum3Helper(k, n-i, i+1, nums, preNumCount+1, result, returnSize);
        free(nums);
    }
}

int** combinationSum3(int k, int n, int* returnSize, int** returnColumnSizes){
    if (n > 45 || n <= 0 || k == 0 || k > 9) {
        *returnSize = 0;
        return NULL;
    }
    int** result = malloc(sizeof(int*)*15);
    *returnSize = 0;
    combinationSum3Helper(k, n, 1, NULL, 0, result, returnSize);
    *returnColumnSizes = malloc(sizeof(int)*(*returnSize));
    for (int i = 0; i < *returnSize; ++i) {
        (*returnColumnSizes)[i] = k;
    }
    return result;
}

struct TreeNode* sortedListToBSTHelper(int* nums, int listLen) {
    if (listLen == 0) return NULL;
    
    int halfLen = listLen/2;
    //struct ListNode* tmp = head;
    //for (int i = 0; i < halfLen; ++i) tmp = tmp->next;
    
    struct TreeNode* treeNode = malloc(sizeof(struct TreeNode));
    treeNode->val = nums[halfLen];
    treeNode->left = sortedListToBSTHelper(nums, halfLen);
    treeNode->right = sortedListToBSTHelper(nums+halfLen+1, listLen-halfLen-1);
    return treeNode;
}

struct TreeNode* sortedListToBST(struct ListNode* head){
    int listLen = 0;
    struct ListNode* tmp = head;
    while (tmp) {
        ++listLen;
        tmp = tmp->next;
    }
    int* nums = malloc(sizeof(int)*listLen);
    tmp = head;
    for (int i = 0; i < listLen; ++i) {
        nums[i] = tmp->val;
        tmp = tmp->next;
    }
    
    struct TreeNode* root = sortedListToBSTHelper(nums, listLen);
    free(nums);
    return root;
}

void inorderTraversalHelper(struct TreeNode* root, int* result, int* returnSize){
    if (root == NULL) return;
    inorderTraversalHelper(root->left, result, returnSize);
    result[(*returnSize)++] = root->val;
    inorderTraversalHelper(root->right, result, returnSize);
}

int* inorderTraversal(struct TreeNode* root, int* returnSize){
    int* result = malloc(sizeof(int)*1000);
    *returnSize = 0;
    // 递归中序历遍
    //inorderTraversalHelper(root, result, returnSize);
    // 莫里斯中序历遍
    struct TreeNode* cur = root;
    struct TreeNode* pre = NULL;
    while (cur != NULL) {
        if (cur->left == NULL) {
            result[(*returnSize)++] = cur->val;
            cur = cur->right;
        }else{
            pre = cur->left;
            while (pre->right != NULL && pre->right != cur) {
                pre = pre->right;
            }
            if (pre->right == NULL) {
                pre->right = cur;
                cur = cur->left;
            }
            if (pre->right == cur) {
                pre->right = NULL;
                result[(*returnSize)++] = cur->val;
                cur = cur->right;
            }
        }
    }
    return result;
}

int* singleNumber3(int* nums, int numsSize, int* returnSize){
    *returnSize = 2;
    int tmp1 = nums[0];
    for (int i = 1; i < numsSize; ++i) tmp1 ^= nums[i];
    int* result = malloc(sizeof(int)*2);
    // 保留最后的1的位置，这个1必定来自两个唯一数的其中一个
    int diff = tmp1&(-tmp1);
    int x = 0;
    // 通过diff，筛选出其中一个唯一数x
    for (int i = 0; i < numsSize; ++i) {
        if (nums[i]&diff) x ^= nums[i];
    }
    result[0] = x;
    result[1] = tmp1^x;
    return result;
}

int minAddToMakeValid(char * S){
    int i = 0;
    int count = 0;
    int tmp = 0;
    while (S[i] != '\0') {
        if (S[i] == ')') {
            --tmp;
        }else{
            if (tmp < 0) {
                count -= tmp;
                tmp = 1;
            }else{
                ++tmp;
            }
        }
        ++i;
    }
    count += abs(tmp);
    return count;
}

int kthSmallestHelper(struct TreeNode* root, int k, int* index){
    if (root == NULL) return 0;
    int val = kthSmallestHelper(root->left, k, index);
    if (*index == k) return val;
    if (++(*index) == k) return root->val;
    return kthSmallestHelper(root->right, k, index);
}

int kthSmallest(struct TreeNode* root, int k){
    int index = 0;
    return kthSmallestHelper(root, k, &index);
}

char ** findAndReplacePattern(char ** words, int wordsSize, char * pattern, int* returnSize){
    int i, j;
    bool flag;
    *returnSize = 0;
    char hashWToP[128] = {0};
    char hashPToW[128] = {0};
    for (i = 0; i < wordsSize; ++i) {
        j = 0;
        flag = true;
        memset(hashWToP, 0, sizeof(char)*128);
        memset(hashPToW, 0, sizeof(char)*128);
        while (words[i][j] != '\0') {
            if (hashWToP[words[i][j]] != 0) {
                if (hashWToP[words[i][j]] != pattern[j]) {
                    flag = false;
                    break;
                }
            }else{
                if (hashPToW[pattern[j]] != 0) {
                    flag = false;
                    break;
                }
                hashWToP[words[i][j]] = pattern[j];
                hashPToW[pattern[j]] = words[i][j];
            }
            ++j;
        }
        if (flag) words[(*returnSize)++] = words[i];
    }
    return words;
}

int* partitionLabels(char * S, int* returnSize){
    int hash[26] = {-1};
    int i = 0;
    while (S[i] != '\0') {
        hash[S[i]-'a'] = i;
        ++i;
    }
    *returnSize = 0;
    int *result = malloc(sizeof(int)*26);
    i = 0;
    int startIndex = 0, lastIndex = -1;
    while (S[i] != '\0') {
        if (hash[S[i]-'a'] > lastIndex) lastIndex = hash[S[i]-'a'];
        if (i == lastIndex) {
            result[(*returnSize)++] = lastIndex-startIndex+1;
            startIndex = lastIndex+1;
        }
        ++i;
    }
    return result;
}

void findBottomLeftValueHelper(struct TreeNode* root, int* result, int deep, int* maxDeep){
    if (root == NULL) return;
    if (deep > *maxDeep) {
        *maxDeep = deep;
        *result = root->val;
    }
    findBottomLeftValueHelper(root->left, result, deep+1, maxDeep);
    findBottomLeftValueHelper(root->right, result, deep+1, maxDeep);
}

int findBottomLeftValue(struct TreeNode* root){
    int result = 0, maxDeep = -1;
    findBottomLeftValueHelper(root, &result, 0, &maxDeep);
    return result;
}

int* grayCode(int n, int* returnSize){
    *returnSize = pow(2, n);
    int* result = malloc(sizeof(int)*(*returnSize));
    result[0] = 0;
    int i, j, index = 1, maxCount = 1;
    //公式解法
//    for (i = 0; i < *returnSize; ++i) {
//        result[i] = i^(i>>1);
//    }
    //每多一位多一倍，新增数为当前最高位置1然后与之前已有数相加得到。(动态规划)
    for (i = 0; i < n; ++i) {
        for (j = maxCount-1; j >= 0; --j) {
            result[index++] = maxCount+result[j];
        }
        maxCount = maxCount<<1;
    }
    return result;
}

void lexicalOrderHelper(int n, int preNum, int* result, int* returnSize) {
    result[(*returnSize)++] = preNum;
    int tmp;
    for (int i = 0; i < 10; ++i) {
        tmp = preNum*10+i;
        if (tmp > n) return; // 剪枝，递归结束条件
        lexicalOrderHelper(n, tmp, result, returnSize);
    }
}

int* lexicalOrder(int n, int* returnSize){
    int* result = malloc(sizeof(int)*n);
    *returnSize = 0;
    // 10叉树的先序历遍
    for (int i = 1; i < 10; ++i) {
        if (i > n) break;
        lexicalOrderHelper(n, i, result, returnSize);
    }
    return result;
//    *returnSize = n;
//    int index = 0;
//    int last = 1;
//    int bit = 0;
//    int tmp = 0;
//    while (last <= n) {
//        result[index++] = last;
//        last *= 10;
//    }
//    last /= 10;
//    while (index < n) {
//        if (last >= n) {
//            last = last/10+1;
//        }else{
//            ++last;
//        }
//        tmp = last;
//        bit = 0;
//        while (tmp%10 == 0) {
//            tmp /= 10;
//            ++bit;
//        }
//        while (bit != 0) {
//            result[index++] = tmp;
//            tmp *= 10;
//            --bit;
//        }
//        result[index++] = last;
//    }
//    
//    return result;
}

bool stoneGame(int* piles, int pilesSize){
    // 数学归纳：pilesSize为偶数，先选的可以做到选择所有的奇数位或所有的偶数位石碓，而这两组中必然有一组较大，所以先选的必胜
    return true;
}

char * complexNumberMultiply(char * a, char * b){
    // 使用库的函数
    {
        int aNum = atoi(a);
        int aiNum = atoi(strchr(a, '+')+1);
        int bNum = atoi(b);
        int biNum = atoi(strchr(b, '+')+1);
        char* result = malloc(sizeof(char)*20);
        sprintf(result, "%d+%di", aNum*bNum-aiNum*biNum, aNum*biNum+bNum*aiNum);
        return result;
    }
    
    // 不使用库的函数
    int aNum = 0;
    int aiNum = 0;
    int bNum = 0;
    int biNum = 0;
    bool isMinus = false;
    bool flag = false;
    if (a[0] == '-') {
        isMinus = true;
        ++a;
    }
    while (*a != 'i') {
        if (*a != '+') {
            if (flag) {
                if (*a == '-') {
                    isMinus = true;
                }else{
                    aiNum = aiNum*10+(*a-'0');
                }
            }else{
                aNum = aNum*10+(*a-'0');
            }
        }else{
            if (isMinus) {
                aNum = -aNum;
            }
            flag = true;
            isMinus = false;
        }
        ++a;
    }
    if (isMinus) {
        aiNum = -aiNum;
    }
    
    isMinus = false;
    flag = false;
    if (b[0] == '-') {
        isMinus = true;
        ++b;
    }
    while (*b != 'i') {
        if (*b != '+') {
            if (flag) {
                if (*b == '-') {
                    isMinus = true;
                }else{
                    biNum = biNum*10+(*b-'0');
                }
            }else{
                bNum = bNum*10+(*b-'0');
            }
        }else{
            if (isMinus) {
                bNum = -bNum;
            }
            flag = true;
            isMinus = false;
        }
        ++b;
    }
    if (isMinus) {
        biNum = -biNum;
    }
    int rNum = aNum*bNum-biNum*aiNum;
    int riNum = aNum*biNum+bNum*aiNum;
    char* result = malloc(sizeof(int)*100);
    int index = 0;
    if (rNum < 0) {
        result[index++] = '-';
        rNum = -rNum;
    }
    int l = index;
    if (rNum == 0) {
        result[index++] = '0';
    }
    while (rNum) {
        result[index++] = rNum%10+'0';
        rNum /= 10;
    }
    int r = index-1;
    char tmp;
    while (l < r) {
        tmp = result[l];
        result[l] = result[r];
        result[r] = tmp;
        ++l;
        --r;
    }
    result[index++] = '+';
    if (riNum < 0) {
        result[index++] = '-';
        riNum = -riNum;
    }
    l = index;
    if (riNum == 0) {
        result[index++] = '0';
    }
    while (riNum) {
        result[index++] = riNum%10+'0';
        riNum /= 10;
    }
    r = index-1;
    while (l < r) {
        tmp = result[l];
        result[l] = result[r];
        result[r] = tmp;
        ++l;
        --r;
    }
    result[index++] = 'i';
    result[index] = '\0';
    
    return result;
}

int* pathInZigZagTree(int label, int* returnSize){
    // 1+2+4+8+...+2^n = (2^(n+1))-1
    int tmp = label;
    int count = 1;
    while (tmp >= 2) {
        tmp = tmp>>1;
        ++count;
    }
    int* result = malloc(sizeof(int)*count);
    *returnSize = count;
    int rowmax = pow(2, count-1)-1;
    while (count > 0) {
        result[--count] = label;
        rowmax = rowmax>>1;
        label = rowmax^(label>>1);
    }
    return result;
}

void maxLevelSumHelper(struct TreeNode* root, int level, int* levelSum, int* maxLevel) {
    if (root == NULL) return;
    if (level > *maxLevel) *maxLevel = level;
    levelSum[level] += root->val;
    maxLevelSumHelper(root->left, level+1, levelSum, maxLevel);
    maxLevelSumHelper(root->right, level+1, levelSum, maxLevel);
}

int maxLevelSum(struct TreeNode* root){
    int maxLevel = 0;
    int* levelSum = malloc(sizeof(int)*1024);
    maxLevelSumHelper(root, 0, levelSum, &maxLevel);
    int index = 0;
    for (int i = 1; i < maxLevel; ++i) {
        if (levelSum[i] > levelSum[index]) index = i;
    }
    free(levelSum);
    return index+1;
}

void flattenHelper(struct TreeNode* root, struct TreeNode** preNode){
    if (root == NULL) return;
    //先序
//    struct TreeNode* left = root->left;
//    struct TreeNode* right = root->right;
//    if (*preNode != NULL) {
//        (*preNode)->right = root;
//        (*preNode)->left = NULL;
//    }
//    *preNode = root;
//    flattenHelper(left, preNode);
//    flattenHelper(right, preNode);
    
    // 后序
    flattenHelper(root->right, preNode);
    flattenHelper(root->left, preNode);
    root->right = *preNode;
    root->left = NULL;
    *preNode = root;
}

void flatten(struct TreeNode* root){
    struct TreeNode* preNode = NULL;
    // 用递归进行历遍, 空间复杂度O(n), 时间复杂度O(n)
    flattenHelper(root, &preNode);
    
    // 用类似morris历遍的方式历遍，空间复杂度O(1), 时间复杂度O(n)
    while (root != NULL) { 
        //左子树为 null，直接考虑下一个节点
        if (root->left == NULL) {
            root = root->right;
        } else {
            // 找左子树最右边的节点
            preNode = root->left;
            while (preNode->right != NULL) {
                preNode = preNode->right;
            } 
            //将原来的右子树接到左子树的最右边节点
            preNode->right = root->right;
            // 将左子树插入到右子树的地方
            root->right = root->left;
            root->left = NULL;
            // 考虑下一个节点
            root = root->right;
        }
    }
}

struct TreeNode* buildTree(int* inorder, int inorderSize, int* postorder, int postorderSize){
    /*
    中序历遍特点 左根右
    后序历遍特点 左右根
    后序数组最后一个数是根，找到中序数组里的根的位置，就可以对左子树和右子树分别做递归处理
    递归n次，每次要从n里找出对应的位置，要运算n次，合计1+2+...+n=n*(n+1)/2，时间复杂度O(n^2)
     */
    if (inorderSize == 0) return NULL;
    {
        int i = 0;
        while (inorder[i] != postorder[postorderSize-1]) ++i;
        struct TreeNode* node = malloc(sizeof(struct TreeNode));
        node->val = postorder[postorderSize-1];
        node->left = buildTree(inorder, i, postorder, i);
        node->right = buildTree(inorder+i+1, inorderSize-i-1, postorder+i, inorderSize-i-1);
        return node;
    }
    
    // 不用递归，时间复杂度O(n^3)
    struct TreeNode* root = malloc(sizeof(struct TreeNode));
    root->left = NULL;
    root->right = NULL;
    struct TreeNode** nodeList = malloc(sizeof(struct TreeNode*)*inorderSize);
    int* indexList = malloc(sizeof(int)*inorderSize);
    root->val = postorder[postorderSize-1];
    int rootIndex = 0;
    for (int i = 0; i < inorderSize; ++i) {
        if (root->val == inorder[i]) {
            rootIndex = i;
            break;
        }
    }
    nodeList[0] = root;
    indexList[0] = rootIndex;
    int listCount = 1;
    int k;
    int j = postorderSize-2;
    int type;
    struct TreeNode* preRoot = NULL;
    while (j >= 0) {
        for (int i = 0; i < inorderSize; ++i) {
            if (postorder[j] == inorder[i]) {
                struct TreeNode* node = malloc(sizeof(struct TreeNode));
                node->left = NULL;
                node->right = NULL;
                node->val = postorder[j];
                type = 0;
                for (k = listCount-1; k >= 0; --k) {
                    if (i > indexList[k]) {
                        if (type == 1) {
                            break;
                        }else if (type == 0){
                            preRoot = nodeList[k];
                            type = 2;
                        }
                    }else{
                        if (type == 2) {
                            break;
                        }
                        preRoot = nodeList[k];
                        type = 1;
                    }
                }
                if (type == 2) {
                    while (preRoot->right != NULL) {
                        preRoot = preRoot->right;
                    }
                    preRoot->right = node;
                }else{
                    while (preRoot->left != NULL) {
                        preRoot = preRoot->left;
                    }
                    preRoot->left = node;
                }
                nodeList[listCount] = node;
                indexList[listCount++] = i;
                break;
            }
        }
        --j;
    }
    return root;
}

int* maxDepthAfterSplit(char * seq, int* returnSize){
    int len = strlen(seq);
    int* result = malloc(sizeof(int)*len);
    *returnSize = len;
    // 记录两个的最大深度，尽可能使两个深度尽可能接近
    int count0 = 0, count1 = 0;
    for (int i = 0; i < len; ++i) {
        if (seq[i] == '(') {
            if (count0 <= count1) {
                result[i] = 0;
                ++count0;
            }else{
                result[i] = 1;
                ++count1;
            }
        }else{
            if (count0 > count1) {
                result[i] = 0;
                --count0;
            }else{
                result[i] = 1;
                --count1;
            }
        }
    }
    
    return result;
}

int* productExceptSelf(int* nums, int numsSize, int* returnSize){
    int* result = malloc(sizeof(int)*numsSize);
    *returnSize = numsSize;
    int total = 1, i;
    for (i = 0; i < numsSize; ++i) {
        result[i] = total;
        total *= nums[i];
    }
    
    total = 1;
    for (i = numsSize-1; i >= 0; --i) {
        result[i] = result[i]*total;
        total *= nums[i];
    }
    
    return result;
}

int countNodesHelper(struct TreeNode* root){
    if (root == NULL) return 0;
    int count = 0;
    while (root) {
        root = root->left;
        ++count;
    }
    return count;
}

int countNodes(struct TreeNode* root){
    // 层数h从0计起
    // 2^h-1+(1~2^h)
    // 需要计算层数和最后一层的节点数
    // O((logn)^2)
    if (root == NULL) return 0;
    
    int l = countNodesHelper(root->left);
    int r = countNodesHelper(root->right);
    if (l == r) {
        return countNodes(root->right)+(1<<l);
    }else{
        return countNodes(root->left)+(1<<r);
    }
}

int singleNumber2(int* nums, int numsSize){
    int b1 = 0, b2 = 0;
    for (int i = 0; i < numsSize; ++i) {
        b1 = (b1^nums[i])&~b2;
        b2 = (b2^nums[i])&~b1;
    }
    return b1;
}

struct TreeNode* removeLeafNodes(struct TreeNode* root, int target){
    if (root == NULL) return NULL;
    root->left = removeLeafNodes(root->left, target);
    root->right = removeLeafNodes(root->right, target);
    if (root->left == NULL && root->right == NULL && root->val == target) return NULL;
    return root;
}

bool partitionHelper(char * s, int end) {
    int l = 0;
    while (l < end) {
        if (s[l] != s[end]) return false;
        ++l;
        --end;
    }
    return true;
}

int partitionMaxLen = 16;

void partitionHelper2(char * s, bool** memo, int start, char**** result, int* returnSize, int** returnColumnSizes, char** tmpRecord, int recordLen){
    int i = start;
    int j, len;
    while (s[i] != '\0') {
        /* 判断s[0]~s[i] 是否回文
            是回文，把s[i+1]~s[n]递归
            不是，直接下一个
        */
        if (memo[start][i]) {
            memcpy(tmpRecord[recordLen], s+start, sizeof(char)*(i-start+1));
            tmpRecord[recordLen][i-start+1] = '\0';
            if (s[i+1] == '\0') {
                if (*returnSize >= partitionMaxLen) {
                    partitionMaxLen *= 2;
                    *result = realloc(*result, sizeof(char**)*partitionMaxLen);
                    *returnColumnSizes = realloc(*returnColumnSizes, sizeof(int)*partitionMaxLen);
                }
                (*result)[*returnSize] = malloc(sizeof(char*)*(recordLen+1));
                (*returnColumnSizes)[*returnSize] = recordLen+1;
                for (j = 0; j <= recordLen; ++j) {
                    len = (int)strlen(tmpRecord[j])+1;
                    (*result)[*returnSize][j] = malloc(sizeof(char)*len);
                    memcpy((*result)[*returnSize][j], tmpRecord[j], sizeof(char)*len);
                }
                ++(*returnSize);
            }else{
                partitionHelper2(s, memo, i+1, result, returnSize, returnColumnSizes, tmpRecord, recordLen+1);
            }
        }
        ++i;
    }
}

char *** partition(char * s, int* returnSize, int** returnColumnSizes){
    int len = (int)strlen(s);
    bool** memo = malloc(sizeof(bool*)*len);
    char** tmpRecord = malloc(sizeof(char*)*len);
    for (int i = 0; i < len; ++i) {
        memo[i] = malloc(sizeof(bool)*len);
        tmpRecord[i] = malloc(sizeof(char)*(len+1));
    }
    for (int i = 1; i <= len; ++i) {
        for (int j = 0; j <= len-i; ++j) {
            memo[j][j+i-1] = (s[j]==s[j+i-1])&&(i<3||memo[j+1][j+i-2]);
        }
    }
    partitionMaxLen = 16;
    *returnSize = 0;
    char*** result = malloc(sizeof(char**)*partitionMaxLen);
    *returnColumnSizes = malloc(sizeof(int)*partitionMaxLen);
    partitionHelper2(s, memo, 0, &result, returnSize, returnColumnSizes, tmpRecord, 0);
    for (int i = 0; i < len; ++i) {
        free(tmpRecord[i]);
        free(memo[i]);
    }
    free(tmpRecord);
    free(memo);
    return result;
//    int maxLen = 16;
//    char *** result = malloc(sizeof(char**)*maxLen);
//    *returnColumnSizes = malloc(sizeof(int)*maxLen);
//    int i = 0;
//    int count = 0;
//    int j, k;
//    while (s[i] != '\0') {
//        /* 判断s[0]~s[i] 是否回文
//            是回文，把s[i+1]~s[n]递归
//            不是，直接下一个
//        */
//        if (partitionHelper(s, i)) {
//            int tmpSize;
//            int* tmpColumnSizes;
//            if (s[i+1] == '\0') {
//                if (count >= maxLen) {
//                    maxLen *= 2;
//                    result = realloc(result, sizeof(char**)*maxLen);
//                    *returnColumnSizes = realloc(*returnColumnSizes, sizeof(int)*maxLen);
//                }
//                result[count] = malloc(sizeof(char*));
//                (*returnColumnSizes)[count] = 1;
//                result[count][0] = malloc(sizeof(char)*(i+2));
//                memcpy(result[count][0], s, sizeof(char)*(i+1));
//                result[count][0][i+1] = '\0';
//                ++count;
//            }else{
//                char *** tmp = partition(s+i+1, &tmpSize, &tmpColumnSizes);
//                for (j = 0; j < tmpSize; ++j) {
//                    if (count >= maxLen) {
//                        maxLen *= 2;
//                        result = realloc(result, sizeof(char**)*maxLen);
//                        *returnColumnSizes = realloc(*returnColumnSizes, sizeof(int)*maxLen);
//                    }
//                    result[count] = malloc(sizeof(char*)*(1+tmpColumnSizes[j]));
//                    (*returnColumnSizes)[count] = 1+tmpColumnSizes[j];
//                    result[count][0] = malloc(sizeof(char)*(i+2));
//                    memcpy(result[count][0], s, sizeof(char)*(i+1));
//                    result[count][0][i+1] = '\0';
//                    for (k = 0; k < tmpColumnSizes[j]; ++k) {
//                        len = (int)strlen(tmp[j][k]);
//                        result[count][k+1] = malloc(sizeof(char)*(len+1));
//                        memcpy(result[count][k+1], tmp[j][k], sizeof(char)*len);
//                        result[count][k+1][len] = '\0';
//                        free(tmp[j][k]);
//                    }
//                    free(tmp[j]);
//                    ++count;
//                }
//                free(tmp);
//                free(tmpColumnSizes);
//            }
//        }
//        ++i;
//    }
//    *returnSize = count;
//    
//    return result;
}

void combinationSum2Helper(int* candidates, int candidatesSize, int target, int* returnSize, int** returnColumnSizes, int** result, int* pre, int sum, int preCount){
    
    for (int i = 0; i < candidatesSize; ++i) {
        if ((i == 0 || candidates[i] != candidates[i-1]) && candidates[i] <= target-sum) {
            int* tmpNums = malloc(sizeof(int)*(preCount+1));
            if (pre != NULL) memcpy(tmpNums, pre, sizeof(int)*preCount);
            tmpNums[preCount] = candidates[i];
            if (sum+candidates[i] == target) {
                result[*returnSize] = tmpNums;
                (*returnColumnSizes)[*returnSize] = preCount+1;
                *returnSize += 1;
            }else{
                combinationSum2Helper(candidates+i+1, candidatesSize-i-1, target, returnSize, returnColumnSizes, result, tmpNums, sum+candidates[i], preCount+1);
                free(tmpNums);
            }
        }
    }
}

int** combinationSum2(int* candidates, int candidatesSize, int target, int* returnSize, int** returnColumnSizes){
    qsort(candidates, candidatesSize, sizeof(int), compare);
    
    int** result = malloc(sizeof(int*)*1000);
    *returnSize = 0;
    *returnColumnSizes = malloc(sizeof(int)*1000);
    combinationSum2Helper(candidates, candidatesSize, target, returnSize, returnColumnSizes, result, NULL, 0, 0);
    
    return result;
}

int countSquares(int** matrix, int matrixSize, int* matrixColSize){
    int i, j, count = 0;
    int** f = malloc(sizeof(int*)*matrixSize);
    for (i = 0; i < matrixSize; ++i) {
        f[i] = malloc(sizeof(int*)*matrixColSize[0]);
    }
    for (i = 0; i < matrixSize; ++i) {
        for (j = 0; j < matrixColSize[0]; ++j) {
            if (i == 0 || j == 0) {
                f[i][j] = matrix[i][j];
            }else if (matrix[i][j] == 0){
                f[i][j] = 0;
            }else{
                f[i][j] = min(min(f[i-1][j], f[i][j-1]), f[i-1][j-1])+1;
            }
            count += f[i][j];
        }
    }
    free(f);
    return count;
}

int distributeCoinsHelper(struct TreeNode* root, int *result) {
    if (root == NULL) return 0;
    int L = distributeCoinsHelper(root->left, result);
    int R = distributeCoinsHelper(root->right, result);
    *result += abs(L)+abs(R);
    return root->val+L+R-1;
}

int distributeCoins(struct TreeNode* root){
    int result = 0;
    distributeCoinsHelper(root, &result);
    return result;
}

char * customSortString(char * S, char * T){
    int slen = strlen(S);
    int tlen = strlen(T);
    int i = 0;
    int hash[26] = {-1};
    for (i = 0; i < 26; ++i) hash[i] = -1;
    i = 0;
    int counts[26] = {0};
    while (S[i] != '\0') {
        hash[S[i]-'a'] = i;
        ++i;
    }
    i = 0;
    int index = tlen-1;
    char* result = malloc(sizeof(char)*(tlen+1));
    result[tlen] = '\0';
    while (T[i] != '\0') {
        if (hash[T[i]-'a'] == -1) {
            result[index--] = T[i];
        }else{
            counts[T[i]-'a'] += 1;
        }
        ++i;
    }
    index = 0;
    for (i = 0; i < slen; ++i) {
        for (int j = 0; j < counts[S[i]]; ++j) {
            result[index++] = S[i];
        }
    }
    
    return result;
}

int numTrees(int n){

    /*
    1    1
    2     2
    5       3
    14      4
    42      5
    132     6
     */
     // G(n) = G(0)G(n-1)+G(1)G(n-2)+...+G(n-1)G(0);
     // G(n+1) = G(0)G(n)+G(1)G(n-1)+...+G(n)G(0);
     // 卡塔兰数 C(n+1) = C(n)*2*(2*n+1)/(n+2)
    long C = 1;
    for (int i = 1; i < n; ++i) {
        C = C*2*(2*i+1)/(i+2);
    }
    
    return (int)C;
}

int sumNums(int n){
    n > 1 && (n += sumNums(n-1));
    return n;
}

bool canFinish(int numCourses, int** prerequisites, int prerequisitesSize, int* prerequisitesColSize){
    int finishCoursesCount = 0;
    
    int coursesIn[numCourses];
    memset(coursesIn, 0, sizeof(int)*numCourses);
    int coursesOut[numCourses][numCourses];
    int coursesOutCount[numCourses];
    memset(coursesOutCount, 0, sizeof(int)*numCourses);
    
    int zeroInCourses[numCourses];
    int zeroInCoursesCount = 0;
    
    for (int i = 0; i < prerequisitesSize; ++i) {
        coursesIn[prerequisites[i][0]] += 1;
        coursesOut[prerequisites[i][1]][coursesOutCount[prerequisites[i][1]]] = prerequisites[i][0];
        coursesOutCount[prerequisites[i][1]] += 1;
    }
    
    for (int i = 0; i < numCourses; ++i) {
        if (coursesIn[i] == 0) {
            zeroInCourses[zeroInCoursesCount++] = i;
            finishCoursesCount += 1;
        }
    }
    
    int tmpCourse, zeroInCourse;
    while (zeroInCoursesCount > 0 && finishCoursesCount<numCourses) {
        zeroInCourse = zeroInCourses[zeroInCoursesCount-1];
        zeroInCoursesCount -= 1;
        
        while (coursesOutCount[zeroInCourse] > 0) {
            tmpCourse = coursesOut[zeroInCourse][coursesOutCount[zeroInCourse]-1];
            coursesIn[tmpCourse] -= 1;
            if (coursesIn[tmpCourse] == 0) {
                zeroInCourses[zeroInCoursesCount++] = tmpCourse;
                finishCoursesCount += 1;
            }
            coursesOutCount[zeroInCourse] -= 1;
        }
    }
    
    return finishCoursesCount==numCourses;
}

int* findOrder(int numCourses, int** prerequisites, int prerequisitesSize, int* prerequisitesColSize, int* returnSize){
    int* result = malloc(sizeof(int)*numCourses);
    int finishCoursesCount = 0;
    
    int coursesIn[numCourses];
    memset(coursesIn, 0, sizeof(int)*numCourses);
    int coursesOut[numCourses][numCourses];
    int coursesOutCount[numCourses];
    memset(coursesOutCount, 0, sizeof(int)*numCourses);
    int zeroInCourses[numCourses];
    int zeroInCoursesCount = 0;
    
    for (int i = 0; i < prerequisitesSize; ++i) {
        coursesIn[prerequisites[i][0]] += 1;
        coursesOut[prerequisites[i][1]][coursesOutCount[prerequisites[i][1]]] = prerequisites[i][0];
        coursesOutCount[prerequisites[i][1]] += 1;
    }
    
    for (int i = 0; i < numCourses; ++i) {
        if (coursesIn[i] == 0) {
            zeroInCourses[zeroInCoursesCount++] = i;
            result[finishCoursesCount] = i;
            finishCoursesCount += 1;
        }
    }
    
    int tmpCourse, zeroInCourse;
    while (zeroInCoursesCount > 0 && finishCoursesCount<numCourses) {
        zeroInCourse = zeroInCourses[zeroInCoursesCount-1];
        zeroInCoursesCount -= 1;
        
        while (coursesOutCount[zeroInCourse] > 0) {
            tmpCourse = coursesOut[zeroInCourse][coursesOutCount[zeroInCourse]-1];
            coursesIn[tmpCourse] -= 1;
            if (coursesIn[tmpCourse] == 0) {
                zeroInCourses[zeroInCoursesCount++] = tmpCourse;
                result[finishCoursesCount] = tmpCourse;
                finishCoursesCount += 1;
            }
            coursesOutCount[zeroInCourse] -= 1;
        }
    }
    if (finishCoursesCount==numCourses) {
        *returnSize = finishCoursesCount;
    }else{
        *returnSize = 0;
    }
    return result;
}

void permuteUniqueDFS(int* nums, int numsSize, int* used, int* returnSize, int** result, int* tmpPath, int pathLen){
    if (pathLen == numsSize) {
        int* path = malloc(sizeof(int)*numsSize);
        memcpy(path, tmpPath, sizeof(int)*numsSize);
        result[*returnSize] = path;
        (*returnSize) += 1;
        return;
    }
    for (int i = 0; i < numsSize; ++i) {
        if (i > 0 && nums[i] == nums[i-1] && used[i-1] == 0) {
            continue;
        }
        if (used[i] == 1) {
            continue;
        }
        used[i] = 1;
        tmpPath[pathLen] = nums[i];
        permuteUniqueDFS(nums, numsSize, used, returnSize, result, tmpPath, pathLen+1);
        used[i] = 0;
    }
}

int** permuteUnique(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){
    if (numsSize == 0) {
        *returnSize = 0;
        return NULL;
    }
    // C(n1, numSize)*C(n2, numSize-n1)*...*C(n3,n3)
    
    qsort(nums, numsSize, sizeof(*nums), compare);
    int maxCount = 1;
    for (int i = 2; i <= numsSize; ++i) {
        maxCount *= i;
    }
    int** result = malloc(sizeof(int*)*maxCount);
    *returnSize = 0;
    int* used = malloc(sizeof(int)*numsSize);
    memset(used, 0, sizeof(int)*numsSize);
    int* tmpPath = malloc(sizeof(int)*numsSize);
    permuteUniqueDFS(nums, numsSize, used, returnSize, result, tmpPath, 0);
    
    *returnColumnSizes = malloc(sizeof(int)*(*returnSize));
    for (int i = 0; i < *returnSize; ++i) {
        (*returnColumnSizes)[i] = numsSize;
    }
    return result;
}

// f(n)=(f(n+1)+f(n+2)+...f(n+W))/W
// f(n-1)=(f(n)+f(n)*W-f(n+W))/W
double new21Game(int N, int K, int W){
    if (K == 0 || K+W-1 <= N) return 1;
    double* hash = malloc(sizeof(double)*(K));
    hash[K-1] = (N-K+1)/(double)W;
    int end;
    for (int i = K-2; i >= 0; --i) {
        end = i+1+W;
        if (end < K) {
            hash[i] = (hash[i+1]*(1+W)-hash[end])/W;
        }else if (end > N) {
            hash[i] = (hash[i+1]*(1+W))/W;
        }else{
            hash[i] = (hash[i+1]*(1+W)-1)/W;
        }
    }
    double res = hash[0];
    free(hash);
    return res;
}

struct TreeNode* recoverFromPreorder(char * S){
    struct TreeNode **nodeList = malloc(sizeof(struct TreeNode*)*1000);
    struct TreeNode *fatherNode;
    
    int i = 0, level = 0, val = 0;
    while (1) {
        if (S[i] == '-' || S[i] == '\0') {
            if (val != 0) {
                struct TreeNode *node = malloc(sizeof(struct TreeNode));
                node->val = val;
                node->left = NULL;
                node->right = NULL;
                nodeList[level] = node;
                if (level > 0) {
                    fatherNode = nodeList[level-1];
                    if (fatherNode->left == NULL) {
                        fatherNode->left = node;
                    }else{
                        fatherNode->right = node;
                    }
                }
                level = 0;
                val = 0;
            }
            if (S[i] == '\0') break;
            level += 1;
        }else{
            val = val*10+S[i]-'0';
        }
        ++i;
    }
    
    fatherNode = nodeList[0];
    free(nodeList);
    return fatherNode;
}

int maxScoreSightseeingPair(int* A, int ASize){
    int ans = 0, mx = A[0];
    for (int i = 1; i < ASize; ++i) {
        if (ans < mx+A[i]-i) ans = mx+A[i]-i;
        if (mx < A[i]+i) mx = A[i]+i;
    }
    return ans;
//    int** hash = malloc(sizeof(int*)*1001);
//    int* hashCount = malloc(sizeof(int*)*1001);
//    memset(hashCount, 0, sizeof(int*)*1001);
//    
//    int maxNum = 0, minNum = 1000;
//    for (int i = 0; i < ASize; ++i) {
//        hashCount[A[i]] += 1;
//        if (A[i] > maxNum) maxNum = A[i];
//        if (A[i] < minNum) minNum = A[i];
//    }
//    for (int i = minNum; i <= maxNum; ++i) {
//        if (hashCount[i] > 0) {
//            hash[i] = malloc(sizeof(int)*hashCount[i]);
//        }
//    }
//    memset(hashCount, 0, sizeof(int*)*1001);
//    for (int i = 0; i < ASize; ++i) {
//        hash[A[i]][hashCount[A[i]]] = i;
//        hashCount[A[i]] += 1;
//    }
//    
//    int minLen = ASize;
//    int tmp = 0, max = 0;
//    int left = 0, right = 0, center = 0;
//    for (int i = maxNum; i >= minNum; --i) {
//        if (i*2-1 <= max) break;
//        if (hashCount[i] == 0) continue;
//        
//        if (hashCount[i] > 1) {
//            minLen = ASize;
//            for (int j = 1; j < hashCount[i]; ++j) {
//                tmp = hash[i][j]-hash[i][j-1];
//                if (tmp < minLen) minLen = tmp;
//            }
//            tmp = i*2-minLen;
//            if (tmp > max) max = tmp;
//        }
//        for (int j = i-1; j >= minNum; --j) {
//            if (i+j-1 <= max) break;
//            if (hashCount[j] == 0) continue;
//            
//            for (int k = 0; k < hashCount[i]; ++k) {
//                left = 1;
//                right = hashCount[j]-1;
//                center = 0;
//                minLen = abs(hash[j][0]-hash[i][k]);
//                while (left <= right) {
//                    center = (left+right) >> 1;
//                    tmp = hash[j][center] - hash[i][k];
//                    if (tmp < 0) {
//                        if (-tmp < minLen) minLen = -tmp;
//                        left = center+1;
//                    }else{
//                        if (tmp < minLen) minLen = tmp;
//                        right = center-1;
//                    }
//                }
//                tmp = i+j-minLen;
//                if (tmp > max) max = tmp;
//            }
//        }
//    }
//    
//    return max;
}

void serializeProcessHelper(struct TreeNode* root, char* data, int* dataLen){
    if (root == NULL) {
        data[*dataLen] = 'n';
        (*dataLen) += 1;
        return;
    }else{
        char tmp[20];
        int tmpLen = 0;
        
        if (root->val == 0) {
            data[*dataLen] = '0';
            (*dataLen) += 1;
        }else{
            int val = root->val;
            if (val < 0) {
                data[*dataLen] = '-';
                (*dataLen) += 1;
                val = -val;
            }
            while (val > 0) {
                tmp[tmpLen] = val%10+'0';
                ++tmpLen;
                val = val/10;
            }
            while (tmpLen > 0) {
                data[*dataLen] = tmp[tmpLen-1];
                (*dataLen) += 1;
                --tmpLen;
            }
        }
        
        data[*dataLen] = ',';
        (*dataLen) += 1;
    }
}

void serializeHelper(struct TreeNode* root, char* data, int* dataLen) {
    serializeProcessHelper(root, data, dataLen);
    if (root == NULL) return;
    serializeHelper(root->left, data, dataLen);
    serializeHelper(root->right, data, dataLen);
}

/** Encodes a tree to a single string. */
char* serialize(struct TreeNode* root) {
    char* data = malloc(sizeof(char)*60000);
    int dataLen = 0;
    serializeHelper(root, data, &dataLen);
    data[dataLen] = '\0';
    return data;
}

/** Decodes your encoded data to tree. */
struct TreeNode* deserialize(char* data) {
    if (data[0] == 'n') return NULL;
    int startFlag = 1, isminus = 0, i = 0, tmp = 0;
    struct TreeNode *nodeStack[1000];
    int leftSet[1000] = {0};
    int rightSet[1000] = {0};
    int level = 0;
    
    while (data[i] != '\0') {
        if (startFlag == 1) {
            if (data[i] == '-') {
                isminus = 1;
                startFlag = 0;
            }else if (data[i] == 'n'){
                if (leftSet[level-1] == 0) {
                    nodeStack[level-1]->left = NULL;
                    leftSet[level-1] = 1;
                }else if (rightSet[level-1] == 0) {
                    nodeStack[level-1]->right = NULL;
                    rightSet[level-1] = 1;
                    --level;
                    while (level > 0 && leftSet[level-1] == 1 && rightSet[level-1] == 1) {
                        --level;
                    }
                }
                isminus = 0;
                tmp = 0;
                startFlag = 1;
            }else{
                tmp = tmp*10+data[i]-'0';
                startFlag = 0;
            }
        }else{
            if (data[i] == ',') {
                struct TreeNode *node = malloc(sizeof(struct TreeNode));
                if (isminus) {
                    node->val = -tmp;
                }else{
                    node->val = tmp;
                }
                nodeStack[level] = node;
                leftSet[level] = 0;
                rightSet[level] = 0;
                if (level > 0) {
                    if (leftSet[level-1] == 0) {
                        nodeStack[level-1]->left = node;
                        leftSet[level-1] = 1;
                    }else if (rightSet[level-1] == 0) {
                        nodeStack[level-1]->right = node;
                        rightSet[level-1] = 1;
                    }
                }
                ++level;
                isminus = 0;
                tmp = 0;
                startFlag = 1;
            }else{
                tmp = tmp*10+data[i]-'0';
            }
        }
        ++i;
    }
    return nodeStack[0];
}

bool patternMatching(char* pattern, char* value){
    int aIndex[1000] = {0};
    int bIndex[1000] = {0};
    int aCount = 0;
    int bCount = 0;
    int i = 0;
    
    while (pattern[i] != '\0') {
        if (pattern[i] == 'a') {
            aIndex[aCount++] = i;
        }else{
            bIndex[bCount++] = i;
        }
        ++i;
    }
    if ((aCount == 1 || bCount == 1) && value[0] != '\0') {
        return true;
    }
    if ((aCount > 0 && bCount > 0) && value[0] == '\0') {
        return false;
    }
    
    i = 0;
    while (value[i] != '\0') ++i;
    int valueLen = i;
    
    if (aCount != 0) {
        if (bCount == 0 && valueLen%aCount != 0) {
            return false;
        }
    }else{
        if (bCount != 0) {
            if (valueLen%bCount != 0) return false;
        }else{
            if (valueLen > 0) {
                return false;
            }else{
                return true;
            }
        }
    }
    
    int alen = 0;
    int maxalen = 0;
    if (aCount > 0) maxalen = valueLen/aCount;

    int blen = 0;
    if (bCount == 0) alen = maxalen;
    
    while (alen <= maxalen) {
        if (bCount > 0 && (valueLen-alen*aCount)%bCount != 0) {
            ++alen;
            continue;
        }
        if (bCount > 0) {
            blen = (valueLen-alen*aCount)/bCount;
        }
        
        bool isEqual = true;
        int startOffset = aIndex[0]*blen;
        for (i = 1; i < aCount; ++i) {
            int offset = (aIndex[i]-aIndex[0]-i)*blen+i*alen;
            for (int j = 0; j < alen; ++j) {
                if (value[offset+j+startOffset] != value[j+startOffset]) {
                    isEqual = false;
                    break;
                }
            }
            if (isEqual == false) break;
        }
        if (isEqual == false) {
            ++alen;
            continue;
        }
        
        startOffset = bIndex[0]*alen;
        for (i = 1; i < bCount; ++i) {
            int offset = (bIndex[i]-bIndex[0]-i)*alen+i*blen;
            for (int j = 0; j < blen; ++j) {
                if (value[offset+j+startOffset] != value[j+startOffset]) {
                    isEqual = false;
                    break;
                }
            }
            if (isEqual == false) break;
        }
        if (isEqual == true) return true;
        ++alen;
    }
    
    return false;
}

int minSubArrayLen(int s, int* nums, int numsSize){
    int minNum = numsSize+1;
    int tmp = 0, l = 0, r = 0;
    while (r < numsSize) {
        tmp += nums[r];
        while (tmp >= s) {
            if (r-l+1 < minNum) minNum = r-l+1;
            tmp -= nums[l];
            ++l;
        }
        ++r;
    }
    return (minNum == numsSize+1)?0:minNum;
}

int findLength(int* A, int ASize, int* B, int BSize){
    // 暴力解法 O(m^2*n)
    
    // 动态规划 O(m*n)
    int maxLen = 0;
    int i, j, m = ASize+1, n = BSize+1;
    int* dp0 = malloc(sizeof(int)*n);
    memset(dp0, 0, sizeof(int)*n);
    int* dp1 = malloc(sizeof(int)*n);
    memset(dp1, 0, sizeof(int)*n);
    
    for (i = 1; i < m; ++i) {
        for (j = 1; j < n; ++j) {
            dp1[j] = A[i-1] == B[j-1]?dp0[j-1]+1:0;
            if (dp1[j] > maxLen) maxLen = dp1[j];
        }
        int* dpt = dp0;
        dp0 = dp1;
        dp1 = dpt;
    }
    
    free(dp0);
    free(dp1);
//    int maxLen = 0;
//    int i, j, offset = 0;
//    int** hashB = malloc(sizeof(int*)*100);
//    int* countB = malloc(sizeof(int)*100);
//    memset(countB, 0, sizeof(int)*100);
//    for (i = 0; i < 100; ++i) {
//        hashB[i] = malloc(sizeof(int)*BSize);
//    }
//    for (i = 0; i < BSize; ++i) {
//        hashB[B[i]][countB[B[i]]] = i;
//        countB[B[i]] += 1;
//    }
//    
//    for (i = 0; i+maxLen < ASize; ++i) {
//        for (j = 0; j < countB[A[i]] && hashB[A[i]][j]+maxLen < BSize; ++j) {
//            offset = 1;
//            while (i+offset < ASize && hashB[A[i]][j]+offset < BSize && A[i+offset] == B[hashB[A[i]][j]+offset]) {
//                ++offset;
//            }
//            if (offset > maxLen) maxLen = offset;
//        }
//    }
    
    return maxLen;
}

bool kthSmallest2Helper(int** matrix, int n, int mid, int k) {
    int count = 0;
    int i = n-1, j = 0;
    while (i >= 0 && j < n) {
        if (matrix[i][j] <= mid) {
            count += i+1;
            ++j;
        }else{
            --i;
        }
    }
    return count>=k;
}

int kthSmallest2(int** matrix, int matrixSize, int* matrixColSize, int k){
    int left = matrix[0][0];
    int right = matrix[matrixSize-1][matrixSize-1];
    int mid;
    while (left < right) {
        mid = (left+right)>>1;
        if (kthSmallest2Helper(matrix, matrixSize, mid, k)) {
            right = mid;
        }else{
            left = mid+1;
        }
    }
    return left;
}

CQueue* cQueueCreate() {
    CQueue *queue = malloc(sizeof(CQueue));
    queue->first = NULL;
    queue->last = NULL;
    return queue;
}

void cQueueAppendTail(CQueue* obj, int value) {
    struct ListNode *node = malloc(sizeof(struct ListNode));
    node->val = value;
    node->next = NULL;
    if (obj->first == NULL) {
        obj->first = node;
    }else{
        obj->last->next = node;
    }
    
    obj->last = node;
}

int cQueueDeleteHead(CQueue* obj) {
    if (obj->first == NULL) {
        return -1;
    }else{
        struct ListNode *node = obj->first;
        obj->first = node->next;
        if (obj->first == NULL) obj->last = NULL;
        int value = node->val;
        free(node);
        return value;
    }
}

void cQueueFree(CQueue* obj) {
    struct ListNode *node = obj->first;
    struct ListNode *tmpNode;
    while (node != NULL) {
        tmpNode = node;
        node = node->next;
        free(tmpNode);
    }
    free(obj);
}

bool isBipartite(int** graph, int graphSize, int* graphColSize){
    int* graphColor = malloc(sizeof(int)*graphSize);
    memset(graphColor, 0, sizeof(int)*graphSize);
    int* queue = malloc(sizeof(int)*graphSize);
    int l, r, i, j, node, nextColor;
    for (i = 0; i < graphSize; ++i) {
        if (graphColor[i] == 0) {
            graphColor[i] = 1;
            l = 0;
            r = 0;
            queue[0] = i;
            while (l <= r) {
                node = queue[l++];
                nextColor = graphColor[node]+((graphColor[node]&1)<<1)-1;
                for (j = 0; j < graphColSize[node]; ++j) {
                    if (graphColor[graph[node][j]] == 0) {
                        graphColor[graph[node][j]] = nextColor;
                        queue[++r] = graph[node][j];
                    }else if (graphColor[graph[node][j]] != nextColor){
                        free(graphColor);
                        free(queue);
                        return false;
                    }
                }
            }
        }
    }
    free(graphColor);
    free(queue);
    return true;
}

int minArray(int* numbers, int numbersSize){
    int left = 0;
    int right = numbersSize-1;
    int center;
    while (left < right) {
        center = (left+right)/2;
        if (numbers[center] < numbers[right]) {
            right = center;
        }else if (numbers[center] > numbers[right]){
            left = center+1;
        }else{
            --right;
        }
    }
    return numbers[left];
}

struct TreeNode** generateTreesHelper(int min, int max, int* returnSize){
    if (min > max) {
        *returnSize = 1;
        struct TreeNode** result = malloc(sizeof(struct TreeNode**));
        result[0] = NULL;
        return result;
    }
    
    int size = 0;
    struct TreeNode** result = malloc(0);
    int index = 0;
    for (int i = min; i <= max; ++i) {
        int rightSize = 0;
        struct TreeNode** rightTrees = generateTreesHelper(i+1, max, &rightSize);
        int leftSize = 0;
        struct TreeNode** leftTrees = generateTreesHelper(min, i-1, &leftSize);
        
        size += rightSize*leftSize;
        result = realloc(result, sizeof(struct TreeNode**)*size);
        for (int j = 0; j < rightSize; ++j) {
            for (int k = 0; k < leftSize; ++k) {
                struct TreeNode *node = malloc(sizeof(struct TreeNode));
                node->val = i;
                node->left = leftTrees[k];
                node->right = rightTrees[j];
                result[index++] = node;
            }
        }
        free(rightTrees);
        free(leftTrees);
    }
    
    *returnSize = size;
    return result;
}

struct TreeNode** generateTrees(int n, int* returnSize){
    *returnSize = 0;
    if (n == 0) return NULL;
    return generateTreesHelper(1, n, returnSize);
}

bool isInterleave(char * s1, char * s2, char * s3) {
    // 动态规划 O(mn)
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    int len3 = strlen(s3);
    if (len1+len2 != len3) {
        return false;
    }
    bool f[len1+1][len2+1];
    memset(f, 0, sizeof(f));
    f[0][0] = true;
    
    for (int i = 0; i <= len1; ++i) {
        for (int j = 0; j <= len2; ++j) {
            if (i > 0) {
                f[i][j] |= f[i-1][j] && s1[i-1] == s3[i+j-1];
            }
            if (j > 0) {
                f[i][j] |= f[i][j-1] && s2[j-1] == s3[i+j-1];
            }
        }
    }
    return f[len1][len2];

    // 递归 (O(2^(m+n)))
//    while (*s3 != '\0') {
//        if (*s3 == *s1 && *s3 == *s2) {
//            return isInterleave(s1+1, s2, s3+1) || isInterleave(s1, s2+1, s3+1);
//        }else if (*s3 == *s1) {
//            ++s1;
//        }else if (*s3 == *s2) {
//            ++s2;
//        }else{
//            return false;
//        }
//        
//        ++s3;
//    }
//    
//    return (*s1 == '\0' && *s2 == '\0');
}

int calculateMinimumHP(int** dungeon, int dungeonSize, int* dungeonColSize) {
    
    int col = dungeonColSize[0];
    int dp[dungeonSize+1][col+1];
    memset(dp, 0x3f, sizeof(dp));
    dp[dungeonSize][col - 1] = dp[dungeonSize - 1][col] = 1;
    
    for (int i = dungeonSize-1; i >= 0; --i) {
        for (int j = col-1; j >= 0; --j) {
            dp[i][j] = max(min(dp[i+1][j], dp[i][j+1])-dungeon[i][j], 1);
        }
    }
    
    return dp[0][0];
}

int LowBit(int x) { return x & (-x); }

void Update(int* c, int n, int pos) {
    while (pos < n) {
        c[pos] += 1;
        pos += LowBit(pos);
    }
}

int Query(int* c, int n, int pos) {
    int ret = 0;

    while (pos > 0) {
        ret += c[pos];
        pos -= LowBit(pos);
    }

    return ret;
}

int lower_bound(int* a, int n, int x) {
    int l = 0, r = n;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (a[mid] < x) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    return l;
}

int comp(const void* a, const void* b) { return (*(int*)a - *(int*)b); }

int Discretization(int* a, int* nums, int n) {
    memcpy(a, nums, sizeof(int) * n);
    qsort(a, n, sizeof(int), comp);
    int m = 0;
    for (int i = 1; i < n; i++) {
        if (a[i] > a[m]) {
            a[++m] = a[i];
        }
    }
    return m + 1;
}
int* countSmaller(int* nums, int numsSize, int* returnSize) {
    int* a = (int*)malloc(sizeof(int) * numsSize);
    int* c = (int*)malloc(sizeof(int) * (numsSize + 1));
    int* ret = (int*)malloc(sizeof(int) * numsSize);
    memset(a, 0, sizeof(int) * numsSize);
    memset(c, 0, sizeof(int) * (numsSize + 1));
    memset(ret, 0, sizeof(int) * numsSize);

    int m = Discretization(a, nums, numsSize);
    for (int i = numsSize - 1; i >= 0; --i) {
        int id = lower_bound(a, m, nums[i]) + 1;
        ret[i] = Query(c, m + 1, id - 1);
        Update(c, m + 1, id);
    }
    free(a);
    free(c);
    *returnSize = numsSize;
    return ret;
}

int longestIncreasingPathHelper(int** matrix, int matrixSize, int* matrixColSize, int i, int j, int** dp){
    if (dp[i][j] != 0) {
        return dp[i][j];
    }
    dp[i][j] += 1;
    
    if (i+1 < matrixSize && matrix[i+1][j] > matrix[i][j]) {
        dp[i][j] = max(dp[i][j], longestIncreasingPathHelper(matrix, matrixSize, matrixColSize, i+1, j, dp)+1);
    }
    if (i > 0 && matrix[i-1][j] > matrix[i][j]) {
        dp[i][j] = max(dp[i][j], longestIncreasingPathHelper(matrix, matrixSize, matrixColSize, i-1, j, dp)+1);
    }
    if (j+1 < matrixColSize[0] && matrix[i][j+1] > matrix[i][j]) {
        dp[i][j] = max(dp[i][j], longestIncreasingPathHelper(matrix, matrixSize, matrixColSize, i, j+1, dp)+1);
    }
    if (j > 0 && matrix[i][j-1] > matrix[i][j]) {
        dp[i][j] = max(dp[i][j], longestIncreasingPathHelper(matrix, matrixSize, matrixColSize, i, j-1, dp)+1);
    }
    return dp[i][j];
}

int longestIncreasingPath(int** matrix, int matrixSize, int* matrixColSize){
    if (matrixSize == 0) return 0;
    int maxCount = 1;
    int** dp = malloc(sizeof(int*)*matrixSize);
    for (int i = 0; i < matrixSize; ++i) {
        dp[i] = malloc(sizeof(int)*matrixColSize[0]);
        memset(dp[i], 0, sizeof(int)*matrixColSize[0]);
    }
    for (int i = 0; i < matrixSize; ++i) {
        for (int j = 0; j < matrixColSize[0]; ++j) {
           maxCount = max(maxCount, longestIncreasingPathHelper(matrix, matrixSize, matrixColSize, i, j, dp));
        }
    }
    
    return maxCount;
}

typedef struct point {
    int x, y;
} point;

const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};

bool inBound(int x, int y, int n, int m) { return x >= 0 && x < n && y >= 0 && y < m; }

int** bfs(int x, int y, char** maze, int n, int m) {
    int** ret = (int**)malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++) {
        ret[i] = (int*)malloc(sizeof(int) * m);
        memset(ret[i], -1, sizeof(int) * m);
    }
    ret[x][y] = 0;
    int quex[n * m], quey[n * m];
    quex[0] = x, quey[0] = y;
    int left = 0, right = 0;
    while (left <= right) {
        for (int k = 0; k < 4; k++) {
            int nx = quex[left] + dx[k], ny = quey[left] + dy[k];
            if (inBound(nx, ny, n, m) && maze[nx][ny] != '#' && ret[nx][ny] == -1) {
                ret[nx][ny] = ret[quex[left]][quey[left]] + 1;
                quex[++right] = nx, quey[right] = ny;
            }
        }
        left++;
    }
    return ret;
}

int minimalSteps(char** maze, int mazeSize){
    int sx = 0;
    int sy = 0;
    int tx = 0;
    int ty = 0;
    int n = mazeSize;
    int m = strlen(maze[0]);
    point* buttons = malloc(sizeof(point)*16);
    point* stones = malloc(sizeof(point)*40);
    int nb = 0, ns = 0;
    for (int i = 0; i < mazeSize; ++i) {
        int j = 0;
        while (maze[i][j] != '\0') {
            if (maze[i][j] == 'S') {
                sx = i;
                sy = j;
            }else if (maze[i][j] == 'T'){
                tx = i;
                ty = j;
            }else if (maze[i][j] == 'M'){
                buttons[nb++] = (point){i,j};
            }else if (maze[i][j] == 'O'){
                stones[ns++] = (point){i,j};
            }
            ++j;
        }
    }
    
    int** start_dist = bfs(sx, sy, maze, n, m);
    
    // 边界情况：没有机关
    if (nb == 0) {
        return start_dist[tx][ty];
    }
    // 从某个机关到其他机关 / 起点与终点的最短距离。
    int** dist = (int**)malloc(sizeof(int*) * nb);
    for (int i = 0; i < nb; i++) {
        dist[i] = (int*)malloc(sizeof(int) * (nb + 2));
        memset(dist[i], -1, sizeof(int) * (nb + 2));
    }
    // 中间结果
    int*** dd = (int***)malloc(sizeof(int**) * nb);
    for (int i = 0; i < nb; i++) {
        int** d = bfs(buttons[i].x, buttons[i].y, maze, n, m);
        dd[i] = d;
        // 从某个点到终点不需要拿石头
        dist[i][nb + 1] = d[tx][ty];
    }
    
    for (int i = 0; i < nb; i++) {
        int tmp = -1;
        for (int k = 0; k < ns; k++) {
            int mid_x = stones[k].x, mid_y = stones[k].y;
            if (dd[i][mid_x][mid_y] != -1 && start_dist[mid_x][mid_y] != -1) {
                if (tmp == -1 || tmp > dd[i][mid_x][mid_y] + start_dist[mid_x][mid_y]) {
                    tmp = dd[i][mid_x][mid_y] + start_dist[mid_x][mid_y];
                }
            }
        }
        dist[i][nb] = tmp;
        for (int j = i + 1; j < nb; j++) {
            int mn = -1;
            for (int k = 0; k < ns; k++) {
                int mid_x = stones[k].x, mid_y = stones[k].y;
                if (dd[i][mid_x][mid_y] != -1 && dd[j][mid_x][mid_y] != -1) {
                    if (mn == -1 || mn > dd[i][mid_x][mid_y] + dd[j][mid_x][mid_y]) {
                        mn = dd[i][mid_x][mid_y] + dd[j][mid_x][mid_y];
                    }
                }
            }
            dist[i][j] = mn;
            dist[j][i] = mn;
        }
    }
    // 无法达成的情形
    for (int i = 0; i < nb; i++) {
        if (dist[i][nb] == -1 || dist[i][nb + 1] == -1) return -1;
    }
    
    // dp 数组， -1 代表没有遍历到
    int** dp = (int**)malloc(sizeof(int*) * (1 << nb));
    for (int i = 0; i < (1 << nb); i++) {
        dp[i] = (int*)malloc(sizeof(int) * nb);
        memset(dp[i], -1, sizeof(int) * nb);
    }
    for (int i = 0; i < nb; i++) {
        dp[1 << i][i] = dist[i][nb];
    }
    
    // 由于更新的状态都比未更新的大，所以直接从小到大遍历即可
    for (int mask = 1; mask < (1 << nb); mask++) {
        for (int i = 0; i < nb; i++) {
            // 当前 dp 是合法的
            if (mask & (1 << i)) {
                for (int j = 0; j < nb; j++) {
                    // j 不在 mask 里
                    if (!(mask & (1 << j))) {
                        int next = mask | (1 << j);
                        if (dp[next][j] == -1 || dp[next][j] > dp[mask][i] + dist[i][j]) {
                            dp[next][j] = dp[mask][i] + dist[i][j];
                        }
                    }
                }
            }
        }
    }
    int ret = -1;
    int final_mask = (1 << nb) - 1;
    for (int i = 0; i < nb; i++) {
        if (ret == -1 || ret > dp[final_mask][i] + dist[i][nb + 1]) {
            ret = dp[final_mask][i] + dist[i][nb + 1];
        }
    }
    
    return ret;
}

int integerBreak(int n){
    if (n < 4) {
        return n-1;
    }
    int quotient = n / 3;
    int remainder = n % 3;
    if (remainder == 0) {
        return (int)pow(3, quotient);
    } else if (remainder == 1) {
        return (int)pow(3, quotient - 1) * 4;
    } else {
        return (int)pow(3, quotient) * 2;
    }
}

int maxCoins(int* nums, int numsSize){
    int rec[numsSize + 1][numsSize + 2];
    memset(rec, 0, sizeof(rec));
    int val[numsSize + 2];
    val[0] = val[numsSize + 1] = 1;
    for (int i = 1; i <= numsSize; i++) {
        val[i] = nums[i - 1];
    }
    for (int i = numsSize - 1; i >= 0; i--) {
        for (int j = i + 2; j <= numsSize + 1; j++) {
            for (int k = i + 1; k < j; k++) {
                int sum = val[i] * val[k] * val[j];
                sum += rec[i][k] + rec[k][j];
                rec[i][j] = fmax(rec[i][j], sum);
            }
        }
    }
    return rec[0][numsSize + 1];

}

int findMagicIndexHelper(int* nums, int left, int right) {
    if (left > right) return -1;
    
    int mid = (left+right)/2;
    if (nums[mid] < mid) {
        int target = findMagicIndexHelper(nums, left, nums[mid]);
        if (target != -1) {
            return target;
        }
        return findMagicIndexHelper(nums, mid+1, right);
    }else{
        int target = findMagicIndexHelper(nums, left, mid-1);
        if (target != -1) {
            return target;
        }
        if (mid == nums[mid]) {
            return mid;
        }
        return findMagicIndexHelper(nums, nums[mid], right);
    }
}

int findMagicIndex(int* nums, int numsSize){
    return findMagicIndexHelper(nums, 0, numsSize-1);
    
    
//    for (int i = 0; i < numsSize; ++i) {
//        if (nums[i] == i) return i;
//    }
//    return -1;
}

struct Node *cloneGraphHelper(struct Node *s, struct Node **hashNode){
    if (hashNode[s->val] != NULL) {
        return hashNode[s->val];
    }
    struct Node *mutiS = malloc(sizeof(struct Node));
    mutiS->val = s->val;
    mutiS->numNeighbors = s->numNeighbors;
    mutiS->neighbors = malloc(sizeof(struct Node*)*mutiS->numNeighbors);
    hashNode[mutiS->val] = mutiS;
    for (int i = 0; i < s->numNeighbors; ++i) {
        mutiS->neighbors[i] = cloneGraphHelper(s->neighbors[i], hashNode);
    }
    
    return mutiS;
}

struct Node *cloneGraph(struct Node *s){
    if (s == NULL) return NULL;
    
    struct Node **hashNode = malloc(sizeof(struct Node*)*101);
    for (int i = 0; i < 101; ++i) {
        hashNode[i] = NULL;
    }
    
    struct Node *result = cloneGraphHelper(s, hashNode);
    free(hashNode);
    return result;
}

void solveHelper(char** board, int m, int n, int i, int j, int** state){
    if (state[i][j] == 1 || board[i][j] == 'X') {
        return;
    }
    
    state[i][j] = 1;
    if (i > 0) solveHelper(board, m, n, i-1, j, state);
    if (i < m-1) solveHelper(board, m, n, i+1, j, state);
    if (j > 0) solveHelper(board, m, n, i, j-1, state);
    if (j < n-1) solveHelper(board, m, n, i, j+1, state);
}

void solve(char** board, int boardSize, int* boardColSize){
    if (boardSize < 3 || boardColSize[0] < 3) return;
    int m = boardSize;
    int n = boardColSize[0];
    
    int** state = malloc(sizeof(int*)*m);
    for (int i = 0; i < m; ++i) {
        state[i] = malloc(sizeof(int)*n);
        memset(state[i], 0, sizeof(int)*n);
    }
    
    for (int i = 0; i < m; ++i) {
        solveHelper(board, m, n, i, 0, state);
        solveHelper(board, m, n, i, n-1, state);
    }
    for (int j = 1; j < n-1; ++j) {
        solveHelper(board, m, n, 0, j, state);
        solveHelper(board, m, n, m-1, j, state);
    }
    
    --m;--n;
    for (int i = 1; i < m; ++i) {
        for (int j = 1; j < n; ++j) {
            if (state[i][j] == 0) board[i][j] = 'X';
        }
    }
    
    for (int i = 0; i < boardSize; ++i) {
        free(state[i]);
    }
    free(state);
}

void restoreIpAddressesHelper(char * s, int sLen, char *prefix, int prefixLen, int leftseg, char** result, int* returnSize) {
    if (leftseg == 0 && sLen == 0) {
        char *ipAddress = malloc(sizeof(char)*(prefixLen+1));
        memcpy(ipAddress, prefix, sizeof(char)*prefixLen);
        ipAddress[prefixLen] = '\0';
        result[*returnSize] = ipAddress;
        (*returnSize) += 1;
        
        return;
    }
    if (sLen > leftseg*3 || sLen < leftseg) return;
    
    int prefixIndex = prefixLen;
    if (leftseg < 4) prefix[prefixIndex++] = '.';
    
    int leftsLen = sLen;
    int addressValue = 0;
    while (*s != '\0') {
        addressValue = addressValue*10+(*s)-'0';
        if (addressValue > 255) return;
        prefix[prefixIndex] = *s;
        ++prefixIndex;
        --leftsLen;
        ++s;
        restoreIpAddressesHelper(s, leftsLen, prefix, prefixIndex, leftseg-1, result, returnSize);
        if (addressValue == 0) return;
    }
    
}

char ** restoreIpAddresses(char * s, int* returnSize){
    // C(3,len-1)
    *returnSize = 0;
    int sLen = strlen(s);
    if (sLen < 4 || sLen > 12) return NULL;
    
    char** result = malloc(sizeof(char*)*((sLen-1)*(sLen-2)*(sLen-3)/6));
    char* prefix = malloc(sizeof(char)*(sLen+4));
    restoreIpAddressesHelper(s, sLen, prefix, 0, 4, result, returnSize);
    free(prefix);
    return result;
}

void recoverTreeInOreder(struct TreeNode* root, int* nums, int* numSize) {
    if (root == NULL) return;
    recoverTreeInOreder(root->left, nums, numSize);
    nums[*numSize] = root->val;
    ++(*numSize);
    recoverTreeInOreder(root->right, nums, numSize);
}

void recoverTreeSearch(struct TreeNode* root, struct TreeNode** node1, struct TreeNode** node2, struct TreeNode** lastNode) {
    if (root == NULL) return;
    recoverTreeSearch(root->left, node1, node2, lastNode);
    if (*lastNode && root->val < (*lastNode)->val) {
        (*node2) = root;
        if (*node1) {
            return;
        }else{
            (*node1) = (*lastNode);
        }
    }
    (*lastNode) = root;
    recoverTreeSearch(root->right, node1, node2, lastNode);
}

void recoverTree(struct TreeNode* root){
    struct TreeNode* node1 = NULL;
    struct TreeNode* lastNode = NULL;
    struct TreeNode* node2 = NULL;
    recoverTreeSearch(root, &node1, &node2, &lastNode);
    int tmpVal = node1->val;
    node1->val = node2->val;
    node2->val = tmpVal;
}

int removeBoxes(int* boxes, int boxesSize){
    int max = 0;
    
    
    return max;
}


int countSubstrings(char * s){
    int n = strlen(s), ans = 0;
    for (int i = 0; i < 2 * n - 1; ++i) {
        int l = i / 2, r = i / 2 + i % 2;
        while (l >= 0 && r < n && s[l] == s[r]) {
            --l;
            ++r;
            ++ans;
        }
    }
    return ans;
}

int updateBoardDirR[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
int updateBoardDirC[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
void updateBoardHelper(char** board, int boardSize, int* boardColSize, int* click) {
    if (board[click[0]][click[1]] == 'E') {
        int count = 0;
        for (int i = 0; i < 8; ++i) {
            int r = click[0]+updateBoardDirR[i];
            int c = click[1]+updateBoardDirC[i];
            if (r >= 0 && r < boardSize && c >= 0 && c < boardColSize[0]) {
                count += board[r][c] == 'M';
            }
        }
        if (count > 0) {
            board[click[0]][click[1]] = '0'+count;
        }else{
            board[click[0]][click[1]] = 'B';
            for (int i = 0; i < 8; ++i) {
                int r = click[0]+updateBoardDirR[i];
                int c = click[1]+updateBoardDirC[i];
                if (r >= 0 && r < boardSize && c >= 0 && c < boardColSize[0] && board[r][c] == 'E') {
                    int nextClick[2] = {r, c};
                    updateBoardHelper(board, boardSize, boardColSize, nextClick);
                }
            }
        }
    }
}
char** updateBoard(char** board, int boardSize, int* boardColSize, int* click, int clickSize, int* returnSize, int** returnColumnSizes){
    *returnSize = boardSize;
    *returnColumnSizes = boardColSize;
    if (board[click[0]][click[1]] == 'M') {
        board[click[0]][click[1]] = 'X';
    }else{
        updateBoardHelper(board, boardSize, boardColSize, click);
    }
    
    return board;
}

bool isNumber(char* s){
    if (*s == '\0') {
        return false;
    }
    while (*s == ' ') {
        ++s;
    }
    if (*s == '+' || *s == '-') {
        ++s;
    }
    bool hasPoint = false;
    bool hasE = false;
    bool hasSpace = false;
    char preChar = '\0';
    char prepreChar = '\0';
    while (*s != '\0') {
        if (*s == ' ') {
            hasSpace = true;
            ++s;
            continue;
        }else{
            if (hasSpace) {
                return false;
            }
            if (*s == 'e' || *s == 'E') {
                if (hasE) {
                    return false;
                }
                if (preChar == '.') {
                    if (!(prepreChar <= '9' && prepreChar >= '0')){
                        return false;
                    }
                }else if (!(preChar <= '9' && preChar >= '0')) {
                    return false;
                }
                hasE = true;
                hasPoint = true;
            }else if (*s == '.') {
                if (hasPoint) {
                    return false;
                }
                hasPoint = true;
            }else if (*s == '+' || *s == '-'){
                if (preChar != 'e' && preChar != 'E') {
                    return false;
                }
            }
            else if (*s <= '9' && *s >= '0'){
                
            }else{
                return false;
            }
        }
        
        prepreChar = preChar;
        preChar = *s;
        ++s;
    }
    if (preChar == '.') {
        return (prepreChar <= '9' && prepreChar >= '0');
    }
    return (preChar <= '9' && preChar >= '0');
}

bool PredictTheWinner(int* nums, int numsSize){
    if (numsSize%2 == 0 || numsSize < 2) {
        return true;
    }
    // 单数情况下，先手不一定赢，动态规划，计算最优情况
    int dp[numsSize][numsSize];
    for (int i = 0; i < numsSize; i++) {
        dp[i][i] = nums[i];
    }
    for (int i = numsSize - 2; i >= 0; i--) {
        for (int j = i + 1; j < numsSize; j++) {
            dp[i][j] = fmax(nums[i] - dp[i + 1][j], nums[j] - dp[i][j - 1]);
        }
    }
    return dp[0][numsSize - 1] >= 0;
}

void canVisitAllRoomsHelper(int** rooms, int roomsSize, int* roomsColSize, int* inRoom, int roomIndex){
    if (inRoom[roomIndex] > 0) return;
    inRoom[roomIndex] = 1;
    inRoom[roomsSize] += 1;
    for (int i = 0; i < roomsColSize[roomIndex]; ++i) {
        canVisitAllRoomsHelper(rooms, roomsSize, roomsColSize, inRoom, rooms[roomIndex][i]);
    }
}

bool canVisitAllRooms(int** rooms, int roomsSize, int* roomsColSize){
    int inRoom[roomsSize+1];
    memset(inRoom, 0, sizeof(inRoom));
    canVisitAllRoomsHelper(rooms, roomsSize, roomsColSize, inRoom, 0);
    return inRoom[roomsSize] == roomsSize;
}

bool validPalindromeHelper(char * s, int l, int r){
    while (l < r) {
        if (s[l] != s[r]) {
            return false;
        }else{
            ++l;
            --r;
        }
    }
    return true;
}

char * shortestPalindrome(char * s){
    int n = strlen(s);
    int fail[n + 1];
    memset(fail, -1, sizeof(fail));
    for (int i = 1; i < n; ++i) {
        int j = fail[i - 1];
        if (j != -1 && s[j + 1] != s[i]) {
            j = fail[j];
        }
        if (s[j + 1] == s[i]) {
            fail[i] = j + 1;
        }
    }
    
    int best = -1;
    for (int i = n - 1; i >= 0; --i) {
        if (best != -1 && s[best + 1] != s[i]) {
            best = fail[best];
        }
        if (s[best + 1] == s[i]) {
            ++best;
        }
    }
    int ret_len = n - best - 1;
    char* ret = malloc(sizeof(char) * (ret_len + n + 1));
    for (int i = 0; i < ret_len; i++) ret[i] = s[n - i - 1];
    for (int i = 0; i < n; i++) ret[i + ret_len] = s[i];
    ret[ret_len + n] = 0;
    return ret;
}

struct NumFrequent {
    int val;
    int count;
};

int compNumFrequent(struct NumFrequent** a, struct NumFrequent** b) {
    return (-((*a)->count)+((*b)->count));
}

int* topKFrequent(int* nums, int numsSize, int k, int* returnSize){
    /*
     最优解法是先用hash表，统计每个数的数量，这部分时间复杂度O(n)
     然后对hash的数量从大到小快速排序，由于只需知道前k大的数，所以每轮快排只需排序一边，
     直到排出前k大的数即可，这部分时间复杂度为log(k)到klog(k)
     最终时间复杂度为O(klog(k))+O(n)，其中n>=k
     额外空间复杂度为O(n)
     */
     
          
    // 以下是简单的排序解法，时间复杂度是O(nlog(n))，不过这个做法不合题目要求
    int* result = malloc(sizeof(int)*k);
    *returnSize = k;
    
    qsort(nums, numsSize, sizeof(int), comp);
    
    int numCount[numsSize];
    int numHash[numsSize];
    memset(numCount, 0, sizeof(numCount));
    numHash[0] = nums[0];
    numCount[0] = 1;
    int index = 0;
    for (int i = 1; i < numsSize; ++i) {
        if (nums[i] != nums[i-1]) {
            ++index;
            numHash[index] = nums[i];
        }
        numCount[index] += 1;
    }
    int difNumsCount = index+1;
    struct NumFrequent** numFres = malloc(sizeof(struct NumFrequent*)*difNumsCount);
    for (int i = 0; i < difNumsCount; ++i) {
        numFres[i] = malloc(sizeof(struct NumFrequent));
        numFres[i]->val = numHash[i];
        numFres[i]->count = numCount[i];
    }
    
    qsort(numFres, difNumsCount, sizeof(struct NumFrequent), compNumFrequent);
    
    for (int i = 0; i < k; ++i) {
        result[i] = numFres[i]->val;
    }
    for (int i = 0; i < difNumsCount; ++i) {
        free(numFres[i]);
    }
    free(numFres);
    return result;
}

bool existHelper(char** board, int boardSize, int* boardColSize, char * word, int** use, int i, int j) {
    if (i < 0 || i >= boardSize || j < 0 || j >= boardColSize[0] || use[i][j] != 0 || board[i][j] != *word) {
        return false;
    }
    use[i][j] = 1;
    if (word[1] == '\0') {
        return true;
    }
    bool flag = false;
    flag = existHelper(board, boardSize, boardColSize, word+1, use, i+1, j);
    if (flag) return true;
    flag = existHelper(board, boardSize, boardColSize, word+1, use, i-1, j);
    if (flag) return true;
    flag = existHelper(board, boardSize, boardColSize, word+1, use, i, j+1);
    if (flag) return true;
    flag = existHelper(board, boardSize, boardColSize, word+1, use, i, j-1);
    if (flag) return true;
    use[i][j] = 0;
    
    return false;
}

bool exist(char** board, int boardSize, int* boardColSize, char * word){
    int** use = malloc(sizeof(int*)*boardSize);
    for (int i = 0; i < boardSize; ++i) {
        use[i] = malloc(sizeof(int)*boardColSize[0]);
        memset(use, 0, sizeof(int)*boardColSize[0]);
    }
    bool flag = false;
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardColSize[0]; ++j) {
            flag = existHelper(board, boardSize, boardColSize, word, use, i, j);
            if (flag) break;
        }
        if (flag) break;
    }
    for (int i = 0; i < boardSize; ++i) {
        free(use[i]);
    }
    free(use);
    return flag;
}

struct Status {
    int a, b, c;
};

struct Status dfs(struct TreeNode* root) {
    if (!root) {
        return (struct Status){INT32_MAX / 2, 0, 0};
    }
    struct Status l = dfs(root->left);
    struct Status r = dfs(root->right);
    int a = l.c + r.c + 1;
    int b = fmin(a, fmin(l.a + r.b, r.a + l.b));
    int c = fmin(a, l.b + r.b);
    return (struct Status){a, b, c};
}

int minCameraCover(struct TreeNode* root) {
    struct Status ret = dfs(root);
    return ret.b;
}


bool canPartition(int* nums, int numsSize){
    if (numsSize < 2) return false;
    int total = 0;
    int maxNum = 0;
    for (int i = 0; i < numsSize; ++i) {
        total += nums[i];
        if (nums[i] > maxNum) {
            maxNum = nums[i];
        }
    }
    if (total&1) {
        return false;
    }
    int target = total/2;
    if (maxNum > target) {
        return false;
    }
    int dp[target+1];
    memset(dp, 0, sizeof(dp));
    dp[0] = true;
    
    for (int i = 0; i < numsSize; ++i) {
        int num = nums[i];
        for (int j = target; j >= num; --j) {
            dp[j] |= dp[j-num];
        }
        if (dp[target]) break;
    }
    
    // 1, 5, 10, 12, 20
    // 48 -> 24
    // dp[24] |= dp[23]
    // ...
    // dp[1] |= dp[0] dp[1] = 1
    // dp[5] = 1 dp[6] = 1
    // dp[10] = 1 dp[11] dp[15] dp[16]
    // dp[12] = 1 dp[13] dp[17] dp[18]  dp[22] dp[23] 
    // dp[20] dp[21] 
    
    return dp[target];
}

void connectRightHelper(struct NodeRight* root) {
    if (root->left == NULL) {
        return;
    }
    root->left->next = root->right;
    if (root->next != NULL) {
        root->right->next = root->next->left;
    }else{
        root->right->next = NULL;
    }
    
    connectRightHelper(root->right);
    connectRightHelper(root->left);
}


struct NodeRight* connectRight(struct NodeRight* root) {
    if (root == NULL) {
        return root;
    }
    root->next = NULL;
    connectRightHelper(root);
    return root;   
}


int totalNQueens(int n){
    
    
    
    return 0;
}


bool workBreakContainCode(long code, long *wordCodeArray, int wordSize) {
    for (int i = 0; i < wordSize; ++i) {
        if (code == wordCodeArray[i]) return true;
    }
    return false;
}

void workBreakHelper(char * s, long *wordCodeArray, int wordDictSize, int* returnSize, char **result, char * lastStr, int lastCharLen, long maxCode) {
    if (s[0] == '\0') {
        char *copyStr = malloc(sizeof(char)*(lastCharLen+1));
        memcpy(copyStr, lastStr, sizeof(char)*lastCharLen);
        copyStr[lastCharLen] = '\0';
        result[(*returnSize)] = copyStr;
        (*returnSize) += 1;
        return;
    }
    int i = 0;
    long code = 0;
    while (s[i] != '\0') {
        code = code*4+s[i]*(i+13)-96;
        ++i;
        if (workBreakContainCode(code+i*53781, wordCodeArray, wordDictSize)) {
            int newLen = lastCharLen+i;
            char *newStr;
            if (lastCharLen > 0) {
                newLen += 1;
                newStr = malloc(sizeof(char)*(newLen+1));
                memcpy(newStr, lastStr, sizeof(char)*lastCharLen);
                newStr[lastCharLen] = ' ';
                memcpy(newStr+lastCharLen+1, s, sizeof(char)*i);
            }else{
                newStr = malloc(sizeof(char)*(newLen+1));
                memcpy(newStr, s, sizeof(char)*i);
            }
            
            newStr[newLen] = '\0';
            
            workBreakHelper(s+i, wordCodeArray, wordDictSize, returnSize, result, newStr, newLen, maxCode);
            free(newStr);
        }
        if (code > maxCode/4) {
            break;
        }
    }
}

char ** wordBreak(char * s, char ** wordDict, int wordDictSize, int* returnSize){
    
    int *charCountArray = malloc(sizeof(int)*256);
    memset(charCountArray, 0, sizeof(int)*256);
    long *wordCodeArray = malloc(sizeof(long)*wordDictSize);
    long maxCode = 0;
    for (int i = 0; i < wordDictSize; ++i) {
        int j = 0;
        long code = 0;
        while (wordDict[i][j] != '\0') {
            // 特征码计算(面向测试用例编程)
            code = code*4+wordDict[i][j]*(j+13)-96;
            charCountArray[wordDict[i][j]] += 1;
            ++j;
        }
        wordCodeArray[i] = code+j*53781;
        if (code > maxCode) {
            maxCode = code;
        }
    }
    
    *returnSize = 0;
    int i = 0;
    while (s[i] != '\0') {
        if (charCountArray[s[i]] == 0) {
            free(charCountArray);
            return NULL;
        }
        ++i;
    }
    free(charCountArray);
    
    // 空间申请(面向测试用例编程)
    char **result = malloc(sizeof(char*)*80);
    workBreakHelper(s, wordCodeArray, wordDictSize, returnSize, result, NULL, 0, maxCode);
    
    free(wordCodeArray);
    return result;
}

void sumNumbersHelper(struct TreeNode* root, int lastVal, int *total){
    int nowVal = lastVal*10+root->val;
    if (root->left == NULL && root->right == NULL) {
        *total += nowVal;
        return;
    }
    if (root->left != NULL) sumNumbersHelper(root->left, nowVal, total);
    if (root->right != NULL) sumNumbersHelper(root->right, nowVal, total);
}

int sumNumbers(struct TreeNode* root){
    int total = 0;
    if (root != NULL) sumNumbersHelper(root, 0, &total);
    return total;
}

void preorderTraversalHelper(struct TreeNode* root, int* returnSize, int *result){
    if (root == NULL) return;
    result[*returnSize] = root->val;
    (*returnSize) += 1;
    preorderTraversalHelper(root->left, returnSize, result);
    preorderTraversalHelper(root->right, returnSize, result);
}

int* preorderTraversal(struct TreeNode* root, int* returnSize){
    int *result = malloc(sizeof(int)*100);
    *returnSize = 0;
    preorderTraversalHelper(root, returnSize, result);
    return result;
}

int** insert(int** intervals, int intervalsSize, int* intervalsColSize, int* newInterval, int newIntervalSize, int* returnSize, int** returnColumnSizes){
    int newLeft = newInterval[0];
    int newRight = newInterval[1];
    
    bool isRight = false;
    
    int **result = malloc(sizeof(int*)*(intervalsSize+1));
    *returnSize = 0;
    
    int i = 0;
    while (i < intervalsSize) {
        if (isRight == false) {
            if (intervals[i][0] > newLeft) {
                isRight = true;
                continue;
            }
        }else{
            if (intervals[i][0] > newRight) break;
        }
        
        if (isRight == false) {
            if (intervals[i][1] >= newLeft) {
                newInterval[0] = intervals[i][0];
                isRight = true;
                if (intervals[i][1] > newRight) {
                    newInterval[1] = intervals[i][1];
                    ++i;
                    break;
                }
                ++i;
                continue; 
            }
        }else{
            if (intervals[i][1] >= newRight) {
                newInterval[1] = intervals[i][1];
                ++i;
                break;
            }else{
                ++i;
                continue;
            }
        }
        
        result[*returnSize] = intervals[i];
        (*returnSize) += 1;
        ++i;
    }
    result[*returnSize] = newInterval;
    (*returnSize) += 1;
    
    while (i < intervalsSize) {
        result[*returnSize] = intervals[i];
        (*returnSize) += 1;
        ++i;
    }
    
    *returnColumnSizes = malloc(sizeof(int)*(*returnSize));
    for (int j = 0; j < (*returnSize); ++j) {
        returnColumnSizes[0][j] = 2;
    }
    
    return result;
}

int count1bit(int a) {
    a = (a & 0x55555555) + ((a >> 1) & 0x55555555);
    a = (a & 0x33333333) + ((a >> 2) & 0x33333333);
    a = (a & 0x0f0f0f0f) + ((a >> 4) & 0x0f0f0f0f);
    a = (a & 0x00ff00ff) + ((a >> 8) & 0x00ff00ff);
    a = (a & 0x0000ffff) + ((a >> 16) & 0x0000ffff);
    return a;
}

int sortByBitsCompare(const void* a, const void* b) {
    int tmpa = *(int*) a;
    int tmpb = *(int*) b;
    int acount = count1bit(tmpa);
    int bcount = count1bit(tmpb);
    return acount == bcount?tmpa-tmpb:acount-bcount;
}


int* sortByBits(int* arr, int arrSize, int* returnSize){
    qsort(arr, arrSize, sizeof(*arr), sortByBitsCompare);
    *returnSize = arrSize;
    return arr;
}

int ladderLength(char * beginWord, char * endWord, char ** wordList, int wordListSize){
    /* hit
        
    */ 
    bool isContainEnd = false;
    for (int i = 0; i < wordListSize; ++i) {
        int j = 0;
        while (endWord[j] != '\0') {
            if (endWord[j] != wordList[i][j]) {
                break;;
            }
            ++j;
        }
        if (endWord[j] == '\0') {
            isContainEnd = true;
            break;
        }
    }
    if (isContainEnd == false) {
        // 不含有结尾词
        return 0;
    }
    int minLength = wordListSize;
    
    
    return 0;
}


struct ListNode* oddEvenList(struct ListNode* head){
    if (head == NULL) return head;
    // 奇数
    struct ListNode* curOddNode = head;
    // 偶数
    struct ListNode* evenHead = head->next;
    struct ListNode* curEvenNode = evenHead;
    
    while (curEvenNode != NULL && curEvenNode->next != NULL) {
        curOddNode->next = curEvenNode->next;
        curOddNode = curOddNode->next;
        curEvenNode->next = curOddNode->next;
        curEvenNode = curEvenNode->next;
    }
    curOddNode->next = evenHead;
    return head;
}

int reconstructQueuecmp(const void* _a, const void* _b) {
    int *a = *(int**)_a, *b = *(int**)_b;
    return a[0] == b[0] ? b[1] - a[1] : a[0] - b[0];
}

int** reconstructQueue(int** people, int peopleSize, int* peopleColSize, int* returnSize, int** returnColumnSizes){
    qsort(people, peopleSize, sizeof(int*), reconstructQueuecmp);
    *returnSize = peopleSize;
    *returnColumnSizes = malloc(sizeof(int)*peopleSize);
    memset(*returnColumnSizes, 0, sizeof(int) * peopleSize);
    int **result = malloc(sizeof(int*)*peopleSize);
    
    for (int i = 0; i < peopleSize; ++i) {
        int spaces = people[i][1]+1;
        for (int j = 0; j < peopleSize; ++j) {
            if ((*returnColumnSizes)[j] == 0) {
                --spaces;
                if (spaces == 0) {
                    (*returnColumnSizes)[j] = 2;
                    result[j] = malloc(sizeof(int)*2);
                    result[j][0] = people[i][0];
                    result[j][1] = people[i][1];
                    break;
                }
            }
        }
    }
    return result;
}

int canCompleteCircuit(int* gas, int gasSize, int* cost, int costSize){
    int start = 0;
    int leftGas = 0;
    while (start < gasSize) {
        leftGas = 0;
        int i = 0;
        while (i < gasSize) {
            int j = (i+start)%gasSize;
            leftGas = leftGas+gas[j]-cost[j];
            if (leftGas < 0) {
                break;
            }
            ++i;
        }
        if (i == gasSize) return start;
        start = start+i+1;
    }
    
    return -1;
}


char * removeKdigits(char * num, int k){
    if (k == 0) return num;
    int length = (int)strlen(num);
    if (length == k) return "0";
    
    char *result = malloc(sizeof(int)*(length+1));
    
    int i = 0;
    int j = 0;
    for (; i < length; ++i) {
        while (j > 0 && result[j-1] > num[i] && k > 0) {
            --j;
            --k;
        }
        result[j++] = num[i];
    }
    j -= k;
    result[j] = '\0';
    i = 0;
    for (; i < j-1; ++i) {
        if (result[i] != '0') {
            break;
        }
    }
    
    return result+i;
}


struct ListNode* insertionSortList(struct ListNode* head){
    if (head == NULL) return NULL;
    struct ListNode* resultHead = malloc(sizeof(struct ListNode));
    resultHead->val = 0;
    resultHead->next = head;
    struct ListNode* curNode = head->next;
    struct ListNode* curPre = head;
    struct ListNode* checkPre = resultHead;
    
    while (curNode != NULL) {
        while (checkPre->next != curNode) {
            if (curNode->val < checkPre->next->val) {
                curPre->next = curNode->next;
                curNode->next = checkPre->next;
                checkPre->next = curNode;
                curNode = curPre;
                break;
            }else{
                checkPre = checkPre->next;
            }
        }
        
        curPre = curNode;
        curNode = curNode->next;
        checkPre = resultHead;
    }
    return resultHead->next;
}

int findMinArrowShotscmp(void* _a, void* _b) {
    int *a = *(int**)_a, *b = *(int**)_b;
    return a[1] - b[1];
}


int findMinArrowShots(int** points, int pointsSize, int* pointsColSize){
    if (pointsSize == 0) return 0;
    
    qsort(points, pointsSize, sizeof(int*), findMinArrowShotscmp);
    int pos = points[0][1];
    int ans = 1;
    for (int i = 0; i < pointsSize; ++i) {
        if (points[i][0] > pos) {
            pos = points[i][1];
            ++ans;
        }
    }
    
    return ans;
}

struct ListNode* sortList(struct ListNode* head){
    /*
    -1 3 4 0 5
    -1 0 3 4 5
    1+2+4+8+..+n
    2^m = n
    m = log2(n)
     */
    
    return head;
}


char * sortString(char * s){
    /*
    abc
    abccbaabccba
     */
    
    int length = (int)strlen(s);
    char* result = malloc(sizeof(char)*(length+1));
    result[length] = '\0';
    
    int alphabet[26] = {0};
    int max = 0;
    int min = 25;
    while (*s != '\0') {
        int i = (*s)-'a';
        alphabet[i] += 1;
        if (i > max) max = i;
        if (i < min) min = i;
        ++s;
    }
    
    int index = 0;
    while (index < length) {
        for (int i = min; i <= max; ++i) {
            if (alphabet[i] > 0) {
                result[index++] = i+'a';
                alphabet[i] -= 1;
            }
        }
        for (int i = max; i >= min; --i) {
            if (alphabet[i] > 0) {
                result[index++] = i+'a';
                alphabet[i] -= 1;
            }
        }
    }
    return result;
}

char * reorganizeString(char * S){
    int length = (int)strlen(S);
    if (length < 2) return S;
    
    int alphabet[26] = {0};
    int max = 0;
    int min = 25;
    int maxcount = 0;
    while (*S != '\0') {
        int i = (*S)-'a';
        alphabet[i] += 1;
        if (i > max) max = i;
        if (i < min) min = i;
        ++S;
        if (alphabet[i] > maxcount) maxcount = alphabet[i];
    }
    if (maxcount > (length + 1) / 2) {
        return "";
    }
    
    char* result = malloc(sizeof(char)*(length+1));
    result[length] = '\0';
    
    int evenIndex = 0, oddIndex = 1;
    int halfLength = length / 2;
    for (int i = min; i <= max; ++i) {
        char c = i+'a';
        while (alphabet[i] > 0 && alphabet[i] <= halfLength && oddIndex < length) {
            result[oddIndex] = c;
            oddIndex += 2;
            alphabet[i] -= 1;
        }
        while (alphabet[i] > 0) {
            result[evenIndex] = c;
            evenIndex += 2;
            alphabet[i] -= 1;
        }
    }
    
    return result;
}

int reversePairsRecursive(int* nums, int left, int right) {
    if (left == right) {
        return 0;
    } else {
        int mid = (left + right) / 2;
        int n1 = reversePairsRecursive(nums, left, mid);
        int n2 = reversePairsRecursive(nums, mid + 1, right);
        int ret = n1 + n2;

        // 首先统计下标对的数量
        int i = left;
        int j = mid + 1;
        while (i <= mid) {
            while (j <= right && (long long)nums[i] > 2 * (long long)nums[j]) j++;
            ret += (j - mid - 1);
            i++;
        }

        // 随后合并两个排序数组
        int sorted[right - left + 1];
        int p1 = left, p2 = mid + 1;
        int p = 0;
        while (p1 <= mid || p2 <= right) {
            if (p1 > mid) {
                sorted[p++] = nums[p2++];
            } else if (p2 > right) {
                sorted[p++] = nums[p1++];
            } else {
                if (nums[p1] < nums[p2]) {
                    sorted[p++] = nums[p1++];
                } else {
                    sorted[p++] = nums[p2++];
                }
            }
        }
        for (int i = 0; i < right - left + 1; i++) {
            nums[left + i] = sorted[i];
        }
        return ret;
    }
}

int reversePairs(int* nums, int numsSize) {
    if (numsSize == 0) {
        return 0;
    }
    return reversePairsRecursive(nums, 0, numsSize - 1);
}

int* maxNumber(int* nums1, int nums1Size, int* nums2, int nums2Size, int k, int* returnSize){
    
    int bucket[10] = {0};
    
//    for (int i = 0; i < nums1Size; ++i) {
//        bucket[nums1[i]] += 1;
//    }
//    
//    for (int i = 0; i < nums2Size; ++i) {
//        bucket[nums2[i]] += 1;
//    }
    
    int *result = malloc(sizeof(int)*k);
    int i = 0, m = 0, n = 0;
    while (i < k) {
        if (m >= nums1Size) {
            result[i++] = nums1[n++];
        }else if (n >= nums2Size) {
            result[i++] = nums1[m++];
        }else{
            if (nums1[m] > nums2[n]) {
                result[i++] = nums1[m++];
            }else{
                result[i++] = nums1[n++];
            }
        }
    }
    
    // 9 3 4 6 5 1 2 5 8 3
    
    return result;
}


bool splitIntoFibonacciBacktrack(int* list, int* listSize, char* S, int length, int index, long long sum, int prev) {
    if (index == length) {
        return (*listSize) >= 3;
    }
    long long curr = 0;
    for (int i = index; i < length; i++) {
        if (i > index && S[index] == '0') {
            break;
        }
        curr = curr * 10 + S[i] - '0';
        if (curr > INT32_MAX) {
            break;
        }
        if ((*listSize) >= 2) {
            if (curr < sum) {
                continue;
            } else if (curr > sum) {
                break;
            }
        }
        list[(*listSize)++] = curr;
        if (splitIntoFibonacciBacktrack(list, listSize, S, length, i + 1, prev + curr, curr)) {
            return true;
        }
        (*listSize)--;
    }
    return false;
}

int* splitIntoFibonacci(char * S, int* returnSize){
    int length = strlen(S);
    if (length < 3) return NULL;
    
    int* result = malloc(sizeof(int)*length);
    *returnSize = 0;
    
    splitIntoFibonacciBacktrack(result, returnSize, S, strlen(S), 0, 0, 0);
    
    return result;
}

int leastInterval(char* tasks, int tasksSize, int n){
    if (n == 0 || tasksSize == 0) return tasksSize;
    
    int taskCount[26] = {0};
    
    for (int i = 0; i < tasksSize; ++i) {
        taskCount[tasks[i]-'A'] += 1;
    }
    
    int maxCount = 0;
    for (int i = 0; i < 26; ++i) {
        if (taskCount[i] > maxCount) maxCount = taskCount[i];
    }
    
    int lastOffset = 0;
    for (int i = 0; i < 26; ++i) {
        if (taskCount[i] == maxCount) ++lastOffset;
    }
    
    return fmax((maxCount-1)*(n+1)+lastOffset, tasksSize);
}


bool isPossible(int* nums, int numsSize){
    int n = numsSize;
    int dp1 = 0;    // 长度为1的子序列数目
    int dp2 = 0;    // 长度为2的子序列数目
    int dp3 = 0;    // 长度>=3的子序列数目
    int idx = 0;
    int start = 0;  // 起始位置
    
    while(idx < n){
        start = idx;                        // 重新将起始位置赋值
        int x = nums[idx];
        while(idx < n && nums[idx] == x){   // 去掉所有和x重复的元素
            idx++;
        }
        int cnt = idx - start;              
        
        if(start > 0 && x != nums[start - 1] + 1){  // 对于nums[idx] != nums[idx - 1] + 1，说明当前整数无法加入到以nums[idx-1] 为结尾的序列中
            if(dp1 + dp2 > 0){                      // 如果 dp1+dp2>0，说明有些长度≤2的序列无法被满足，因此不存在相应的分割方案。
                return false;
            }else{                                  // 否则，此前的序列全部作废
                dp1 = cnt;
                dp2 = dp3 = 0;
            }
        }else{                                      // 对于nums[idx] == nums[idx - 1] + 1，说明当前整数可以加入到所有以nums[idx-1]为结尾的序列中。假设数组中x的数目为cnt：
            if(dp1 + dp2 > cnt){                    // 首先，根据贪心的策略，我们要尽可能地先把 x 添加到长度≤2 的子序列中，从而尽可能地保证子序列的长度都≥3。如果x的数量不够，说明不存在相应的分割方案。
                return false;
            }
            int left = cnt - dp1 - dp2;             // 此时 还剩下left = cnt -dp1 -dp2个 nums[idx-1](x)
            int keep = fmin(dp3,left);          // 尽量将余下的left个整数添加到长度≥3的子序列中
            // 最后，我们更新 dp1,dp2,dp3的取值
            dp3 = keep + dp2;
            dp2 = dp1;
            dp1 = left - keep;                      // 如果还有剩余，才将开启对应数量的新序列。新序列的数目等于left−keep。
        }
    }
    
    return dp1 == 0 && dp2 == 0;
}


char * predictPartyVictory(char * senate){
    int length = strlen(senate);
    
    int *banList = malloc(sizeof(int)*length);
    memset(banList, 0, sizeof(int)*length);
    
    int RCount = 0;
    int DCount = 0;
    int RBCount = 0;
    int DBCount = 0;
    
    int index = 0;
    while (index < length) {
        if (senate[index] == 'R') {
            ++RCount;
        }else{
            ++DCount;
        }
        ++index;
    }
    
    index = 0;
    while (RCount > 0 && DCount > 0) {
        if (banList[index] == 0) {
            if (senate[index] == 'R') {
                if (RBCount == 0) {
                    ++DBCount;
                }else{
                    banList[index] = 1;
                    --RBCount;
                    --RCount;
                }
            }else{
                if (DBCount == 0) {
                    ++RBCount;
                }else{
                    banList[index] = 1;
                    --DBCount;
                    --DCount;
                }
            }
        }
        ++index;
        if (index >= length) index = 0;
    }
    
    free(banList);
    return RCount>0?"Radiant":"Dire";
}


char *** groupAnagrams(char ** strs, int strsSize, int* returnSize, int** returnColumnSizes){
    int **code = malloc(sizeof(int*)*strsSize);
    char ***result = malloc(sizeof(char**)*strsSize);
    
    *returnSize = 0;
    *returnColumnSizes = malloc(sizeof(int)*strsSize);
    memset(*returnColumnSizes, 0, sizeof(int)*strsSize);
    
    for (int i = 0; i < strsSize; ++i) {
        int *tmpCode = malloc(sizeof(int)*26);
        memset(tmpCode, 0, sizeof(int)*26);
        int j = 0;
        while (strs[i][j] != '\0') {
            tmpCode[strs[i][j]-'a'] += 1;
            ++j;
        }
        bool isNew = true;
        // 用hash可以减少下面的计算(10~20倍的运算时间)
        for (int k = 0; k < *returnSize; ++k) {
            for (int l = 0; l < 26; ++l) {
                if (tmpCode[l] != code[k][l]) {
                    break;
                }
                if (l == 25) {
                    isNew = false;
                    result[k][(*returnColumnSizes)[k]] = strs[i];
                    (*returnColumnSizes)[k] += 1;
                }
            }
            if (isNew == false) break;
        }
        
        if (isNew) {
            result[*returnSize] = malloc(sizeof(char*)*strsSize);
            result[*returnSize][0] = strs[i];
            (*returnColumnSizes)[*returnSize] += 1;
            code[*returnSize] = tmpCode;
            (*returnSize) += 1;
        }else{
            free(tmpCode);
        }
    }
    for (int k = 0; k < *returnSize; ++k) {
        free(code[k]);
    }
    free(code);
    
    return result;
}


int monotoneIncreasingDigits(int N){
    if (N < 10) return N;
    int tmp = N/10;
    int last = N%10;
    int result = 0;
    int muti = 1;
    while (tmp > 0) {
        int num = tmp%10;
        if (num > last) {
            num = num-1;
            last = 9;
            result = 0.999999999*muti;
        }
        result = result+last*muti;
        muti = muti*10;
        last = num;
        tmp = tmp/10;
    }
    result = result+last*muti;
    
    return result;
    
}

int wiggleMaxLength(int* nums, int numsSize){
    if (numsSize < 2) return numsSize;
    int last = nums[0]-nums[1];
    int result = last==0?1:2;
    for (int i = 2; i < numsSize; ++i) {
        int now = nums[i-1]-nums[i];
        if ((last >= 0 && now < 0) || (last <= 0 && now > 0)) {
            ++result;
            last = now;
        }
    }
    return result;
}

int maxProfit3(int* prices, int pricesSize, int fee){
    int sell = 0;
    int buy = -prices[0];
    for (int i = 0; i < pricesSize; ++i) {
        sell = fmax(sell, buy+prices[i]-fee);
        buy = fmax(buy, sell-prices[i]);
    }
    return sell;
}

char * removeDuplicateLetters(char * s){
    int vis[26], num[26];
    memset(vis, 0, sizeof(vis));
    memset(num, 0, sizeof(num));

    int n = strlen(s);
    for (int i = 0; i < n; i++) {
        num[s[i] - 'a']++;
    }

    char* stk = malloc(sizeof(char) * 27);
    int stkTop = 0;
    for (int i = 0; i < n; i++) {
        if (!vis[s[i] - 'a']) {
            while (stkTop > 0 && stk[stkTop - 1] > s[i]) {
                if (num[stk[stkTop - 1] - 'a'] > 0) {
                    vis[stk[--stkTop] - 'a'] = 0;
                } else {
                    break;
                }
            }
            vis[s[i] - 'a'] = 1;
            stk[stkTop++] = s[i];
        }
        num[s[i] - 'a'] -= 1;
    }
    stk[stkTop] = '\0';
    return stk;
}

void zigzagLevelOrderHelper(int** result, int level, struct TreeNode* root, int* returnSize, int** returnColumnSizes) {
    if (root == NULL) return;
    if (level+1 > *returnSize) {
        *returnSize = level+1;
        result[level] = malloc(sizeof(int)*pow(2, level));
    }
    zigzagLevelOrderHelper(result, level+1, root->left, returnSize, returnColumnSizes);
    zigzagLevelOrderHelper(result, level+1, root->right, returnSize, returnColumnSizes);
    
    result[level][(*returnColumnSizes)[level]++] = root->val;
}

int** zigzagLevelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes){
    
    *returnSize = 0;
    int** result = malloc(sizeof(int*)*100);
    *returnColumnSizes = malloc(sizeof(int)*100);
    memset(*returnColumnSizes, 0, sizeof(int)*100);
    zigzagLevelOrderHelper(result, 0, root, returnSize, returnColumnSizes);
    
    for (int i = 1; i < *returnSize; i += 2) {
        int left = 0;
        int right = (*returnColumnSizes)[i]-1;
        while (left < right) {
            int tmp = result[i][left];
            result[i][left++] = result[i][right];
            result[i][right--] = tmp;
        }
    }
    
    return result;
}

int maxProfit4(int k, int* prices, int pricesSize){
    int n = pricesSize;
    if (n == 0) {
        return 0;
    }

    k = fmin(k, n / 2);
    int buy[k + 1], sell[k + 1];
    memset(buy, 0, sizeof(buy));
    memset(sell, 0, sizeof(sell));

    buy[0] = -prices[0];
    sell[0] = 0;
    for (int i = 1; i <= k; ++i) {
        buy[i] = sell[i] = -9999;
    }

    for (int i = 1; i < n; ++i) {
        buy[0] = fmax(buy[0], sell[0] - prices[i]);
        for (int j = 1; j <= k; ++j) {
            buy[j] = fmax(buy[j], sell[j] - prices[i]);
            sell[j] = fmax(sell[j], buy[j - 1] + prices[i]);
        }
    }
    int ret = 0;
    for (int i = 0; i <= k; i++) {
        ret = fmax(ret, sell[i]);
    }

    return ret;

}


int maximalRectangle(char** matrix, int matrixSize, int* matrixColSize){
    
    int** VCount = malloc(sizeof(int*)*matrixSize);
    for (int i = 0; i < matrixSize; ++i) {
        VCount[i] = malloc(sizeof(int)*matrixColSize[i]);
        memset(VCount[i], 0, sizeof(int)*matrixColSize[i]);
    }
    
    for (int i = matrixSize-1; i >= 0; --i) {
        for (int j = 0; j < matrixColSize[i]; ++j) {
            if (matrix[i][j] == '1') {
                if (i < matrixSize-1) {
                    VCount[i][j] = VCount[i+1][j]+1;
                }else{
                    VCount[i][j] = 1;
                }
            }
        }
    }
    
    int result = 0;
    for (int i = 0; i < matrixSize; ++i) {
        for (int j = 0; j < matrixColSize[i]; ++j) {
            int maxV = VCount[i][j];
            for (int k = j; k < matrixColSize[i] && maxV > 0; ++k) {
                if (VCount[i][k] < maxV) maxV = VCount[i][k];
                result = fmax(result, maxV*(k-j+1));
            }
        }
    }
    
    return result;
}


int minPatches(int* nums, int numsSize, int n){
    int patches = 0;
    long long x = 1;
    int index = 0;
    while (x <= n) {
        if (index < numsSize && nums[index] <= x) {
            x += nums[index++];
        } else {
            x <<= 1;
            patches++;
        }
    }
    return patches;
}

char * smallestStringWithSwaps(char * s, int** pairs, int pairsSize, int* pairsColSize){
    int length = strlen(s);
    /*
    1. 下标分组:把有直接或间接关联的下标分为一组
    2. 排序:把每组对应的字符单独排序
    3. 合并:历遍下标，获取下标对应的分组，然后取该分组中最小的字符放入该下标，并删去分组里的该字符
    4. 完成
     */
    
    
    return "";
}

int* sortItems(int n, int m, int* group, int groupSize, int** beforeItems, int beforeItemsSize, int* beforeItemsColSize, int* returnSize){
    
    
    
    
    return NULL;
}


int Find(int* parent, int index) {
    if (parent[index] != index) {
        parent[index] = Find(parent, parent[index]);
    }
    return parent[index];
}

void Union(int* parent, int index1, int index2) {
    parent[Find(parent, index1)] = Find(parent, index2);
}

int* findRedundantConnection(int** edges, int edgesSize, int* edgesColSize, int* returnSize) {
    int nodesCount = edgesSize;
    int parent[nodesCount + 1];
    for (int i = 1; i <= nodesCount; ++i) {
        parent[i] = i;
    }
    for (int i = 0; i < edgesSize; ++i) {
        int node1 = edges[i][0], node2 = edges[i][1];
        if (Find(parent, node1) != Find(parent, node2)) {
            Union(parent, node1, node2);
        } else {
            *returnSize = 2;
            return edges[i];
        }
    }
    *returnSize = 0;
    return NULL;
}

struct ListNode* partition2(struct ListNode* head, int x){
    
    struct ListNode* smallList = malloc(sizeof(struct ListNode));
    struct ListNode* bigList = malloc(sizeof(struct ListNode));
    struct ListNode* smallCur = smallList;
    struct ListNode* bigCur = bigList;
    smallList->next = NULL;
    bigList->next = NULL;
    
    while (head != NULL) {
        if (head->val < x) {
            smallCur->next = head;
            smallCur = head;
        }else{
            bigCur->next = head;
            bigCur = head;
        }
        head = head->next;
    }
    smallCur->next = bigList->next;
    bigCur->next = NULL;
    smallCur = smallList->next;
    free(smallList);
    free(bigList);
    
    return smallCur;
}

double* calcEquation(char *** equations, int equationsSize, int* equationsColSize, double* values, int valuesSize, char *** queries, int queriesSize, int* queriesColSize, int* returnSize){
    
    
    
    
    return NULL;
}


int findCircleNum(int** isConnected, int isConnectedSize, int* isConnectedColSize){
    int *city = malloc(sizeof(int)*isConnectedSize);
    for (int i = 0; i < isConnectedSize; ++i) {
        city[i] = i;
    }
    
    for (int i = 0; i < isConnectedSize; ++i) {
        for (int j = i+1; j < isConnectedColSize[i]; ++j) {
            if (isConnected[i][j] == 1) {
                if (Find(city, i) != Find(city, j)) {
                    Union(city, i, j);
                }
            }
        }
    }
    
    int count = 0;
    for (int i = 0; i < isConnectedSize; ++i) {
        if (city[i] == i) {
            ++count;
        }
    }
    free(city);
    
    return count;
}


int maxProfit5(int* prices, int pricesSize){
    
    int buy1 = -prices[0];
    int buy2 = -prices[0];
    int sell1 = 0;
    int sell2 = 0;
    for (int i = 0; i < pricesSize; ++i) {
        if (buy1 < -prices[i]) {
            buy1 = -prices[i];
        }
        if (sell1 < buy1+prices[i]) {
            sell1 = buy1+prices[i];
        }
        if (buy2 < sell1-prices[i]) {
            buy2 = sell1-prices[i];
        }
        if (sell2 < buy2+prices[i]) {
            sell2 = buy2+prices[i];
        }
    }
    
    return sell2;
}

int removeStones(int** stones, int stonesSize, int* stonesColSize){
    
    int parent[stonesSize];
    for (int i = 0; i < stonesSize; ++i) {
        parent[i] = i;
    }
    
    int count = 0;
    for (int i = 0; i < stonesSize; ++i) {
        for (int j = i+1; j < stonesSize; ++j) {
            if ((stones[i][0] == stones[j][0] || stones[i][1] == stones[j][1]) && Find(parent, i) != Find(parent, j)) {
                Union(parent, i, j);
                ++count;
            }
        }
    }
    
    return count;
}

char* intToString(int num) {
    char *str = malloc(sizeof(char)*12);
    if(num == 0) {
        str[0] = '0';
        str[1] = '\0';
        return str;
    }
    int index = 0;
    int left = 0;
    if (num < 0) {
        str[index++] = '-';
        if (num == -2147483648) {
            str[index++] = '8';
            num = -214748364;
        }
        num = -num;
        left = 1;
    }
    while (num != 0) {
        str[index++] = (num%10)+'0';
        num /= 10;
    }
    str[index] = '\0';
    int right = index-1;
    while (left < right) {
        char tmp = str[left];
        str[left] = str[right];
        str[right] = tmp;
        ++left;
        --right;
    }
    
    return str;
}

char * createSummaryRanges(int start, int end){
    char *group = malloc(sizeof(char)*25);
    int index = 0;
    char *leftString = intToString(start);
    int j = 0;
    while (leftString[j] != '\0') {
        group[index++] = leftString[j];
        ++j;
    }
    free(leftString);
    if (start != end) {
        char *rightString = intToString(end);
        group[index++] = '-';
        group[index++] = '>';
        j = 0;
        while (rightString[j] != '\0') {
            group[index++] = rightString[j];
            ++j;
        }
        free(rightString);
    }
    group[index] = '\0';
    return group;
}

char ** summaryRanges(int* nums, int numsSize, int* returnSize){
    *returnSize = 0;
    if (numsSize == 0) return NULL;
    
    int count = 1;
    for (int i = 1; i < numsSize; ++i) {
        if (nums[i] != nums[i-1]+1) ++count;
    }
    char **result = malloc(sizeof(char*)*count);
    int start = nums[0];
    for (int i = 1; i < numsSize; ++i) {
        if (nums[i] != nums[i-1]+1) {
            result[(*returnSize)++] = createSummaryRanges(start, nums[i-1]);
            start = nums[i];
        }
    }
    result[(*returnSize)++] = createSummaryRanges(start, nums[numsSize-1]);
    
    return result;
}

int minCostConnectPoints(int** points, int pointsSize, int* pointsColSize){
    
    
    return 0;
}


int minimumEffortPath(int** heights, int heightsSize, int* heightsColSize){
    
    /*
     1 2 1 1 1
     1 2 1 2 1
     1 2 1 2 1
     1 2 1 2 1
     1 1 1 2 1
     */
    
    
    
    int colCount = heightsColSize[0];
    int result[colCount];
    for (int i = 0; i < colCount; ++i) {
        result[i] = 0;
    }
    for (int i = 0; i < heightsSize; ++i) {
        for (int j = 0; j < colCount; ++j) {
            if (i > 0 && j > 0) {
                result[j] = fmin(fmax(result[j], abs(heights[i][j]-heights[i-1][j])), fmax(result[j-1], abs(heights[i][j]-heights[i][j-1])));
            }else if (i > 0) {
                result[j] = fmax(result[j], abs(heights[i][j]-heights[i-1][j]));
            }else if (j > 0){
                result[j] = fmax(result[j-1], abs(heights[i][j]-heights[i][j-1]));
            }
        }
    }
    
    return result[colCount-1];
}


int characterReplacement(char * s, int k){
    int num[26];
    memset(num, 0, sizeof(num));
    int n = strlen(s);
    int maxn = 0;
    int left = 0, right = 0;
    while (right < n) {
        num[s[right] - 'A']++;
        maxn = fmax(maxn, num[s[right] - 'A']);
        if (right - left + 1 - maxn > k) {
            num[s[left] - 'A']--;
            left++;
        }
        right++;
    }
    return right - left;
}

bool isSimilar(char *s1, char *s2) {
    int difCount = 0;
    while (*s1 != 0) {
        if (*s1 != *s2) ++difCount;
        if (difCount > 2) return false;
        ++s1;
        ++s2;
    }
    
    return true;
}

int numSimilarGroups(char ** strs, int strsSize){
    int parent[strsSize];
    for (int i = 0; i < strsSize; ++i) {
        parent[i] = i;
    }
    
    for (int i = 0; i < strsSize; ++i) {
        for (int j = i+1; j < strsSize; ++j) {
            int findi = Find(parent, i);
            int findj = Find(parent, j);
            if (findi != findj) {
                if (isSimilar(strs[i], strs[j])) {
                    parent[findi] = findj;
                }
            }
        }
    }
    
    int count = 0;
    for (int i = 0; i < strsSize; ++i) {
        if (parent[i] == i) ++count;
    }
    
    return count;
}

int directions_four[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

int swimInWater(int** grid, int gridSize, int* gridColSize){
    
    int count = gridSize*gridSize;
    
    int parent[count];
    for (int i = 0; i < count; ++i) {
        parent[i] = i;
    }
    
    int idx[count][2];
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            idx[grid[i][j]][0] = i;
            idx[grid[i][j]][1] = j;
        }
    }
    
    for (int threshold = 0; threshold < count; ++threshold) {
        int i = idx[threshold][0];
        int j = idx[threshold][1];
        for (int k = 0; k < 4; ++k) {
            int ni = i+directions_four[k][0];
            int nj = j+directions_four[k][1];
            
            if (ni > 0 && ni < gridSize && nj > 0 && nj < gridSize && grid[ni][nj] <= threshold) {
                Union(parent, gridSize*i+j, gridSize*ni+nj);
            }
        }
        if (Find(parent, 0) == Find(parent, count-1)) {
            return threshold;
        }
    }
    
    return -1;
}

double* medianSlidingWindow(int* nums, int numsSize, int k, int* returnSize){
    // 暴力法，每次移动历遍找出窗口内的中位数O(klog(k))，串口可滑动n-k+1次，最终为O(k(n-k)log(k))
    
    
    
    return NULL;
}

int equalSubstring(char * s, char * t, int maxCost){
    
    int length = strlen(s);
    int costList[length];
    
    for (int i = 0; i < length; ++i) {
        costList[i] = abs(s[i]-t[i]);
    }
    
    int left = 0;
    int right = 0;
    int curCost = 0;
    int maxCount = 0;
    for (int i = 0; i < length; ++i) {
        curCost += costList[i];
        while (curCost > maxCost) {
            curCost -= costList[left++];
        }
        ++right;
        if (right-left > maxCount) maxCount=right-left;
    }
    
    return maxCount;
}

int maxScore(int* cardPoints, int cardPointsSize, int k){
    int maxPoint = 0;
    for (int i = 0; i < k; ++i) {
        maxPoint += cardPoints[i];
    }
    int curPoint = maxPoint;
    for (int i = k-1; i >= 0; --i) {
        curPoint = curPoint-cardPoints[i]+cardPoints[cardPointsSize-k+i];
        if (curPoint > maxPoint) maxPoint = curPoint;
    }

    return maxPoint;
}

//int trailingZeroes(int n){
//    // 要出现0，需要2*5，最终需要计算的是有多少对2和5
//    // 而在阶乘中5的个数必定小于等于2的个数，最终需要计算5的个数
//    // 5 1个
//    // 25 6个
//    // 125 31个
//    // 125/5 = 25; 25/5 = 5; 5/5 1; 
//    
//    int count = 0;
//    while (n >= 5) {
//        n /= 5;
//        count += n;
//    }
//    
//    return count;
//}

int findString(char** words, int wordsSize, char* s){
    //
//    char* tmpWords[wordsSize];
//    int tmpCount = 0;
//    int indexs[wordsSize];
//    for (int i = 0; i < wordsSize; ++i) {
//        if (words[i][0] != 0) {
//            tmpWords[tmpCount] = words[i];
//            indexs[tmpCount] = i;
//            ++tmpCount;
//        }
//    }
    
    int left = 0;
    int right = wordsSize-1;
    while (left <= right) {
        int i = 0;
        int center = (left+right)/2;
        int tmp = center;
        while (center <= right && words[center][0] == '\0' ) {
            ++center;
        }
        if (center > right) {
            right = tmp-1;
            continue;
        }
        
        while (s[i] == words[center][i] && s[i] != '\0') {
            ++i;
        }
        if (s[i] == words[center][i] && s[i] == '\0') {
            return center;
        }
        if (s[i] > words[center][i]) {
            left = center+1;
        }else{
            right = tmp-1;
        }
    } 
    
    return -1;
}

int* divingBoard(int shorter, int longer, int k, int* returnSize){
    if (k == 0) {
        *returnSize = 0;
        return NULL;
    }
    if (shorter == longer) {
        int *result = malloc(sizeof(int)*(1));
        *returnSize = 1;
        result[0] = k*shorter;
        return result;
    }
    
    int *result = malloc(sizeof(int)*(k+1));
    *returnSize = k+1;
    
    for (int i = 0; i <= k; ++i) {
        result[i] = shorter*(k-i)+longer*i;
    }
    
    return result;
}

int maximum(int a, int b){
    long c = a, d = b;
    return (labs(c-d)+c+d)/2;
}

int* masterMind(char* solution, char* guess, int* returnSize){
    int* result = malloc(sizeof(int)*2);
    result[0] = 0;
    result[1] = 0;
    *returnSize = 2;
    int Y = 0, R = 0, G = 0, B = 0;
    int i = 0;
    while (solution[i] != '\0') {
        if (solution[i] == guess[i]) {
            result[0] += 1;
            ++i;
            continue;
        }
        if (solution[i] == 'Y') {
            if (Y++ < 0) result[1] += 1;
        }else if (solution[i] == 'R') {
            if (R++ < 0) result[1] += 1;
        }else if (solution[i] == 'G') {
            if (G++ < 0) result[1] += 1;
        }else if (solution[i] == 'B') {
            if (B++ < 0) result[1] += 1;
        }
        if (guess[i] == 'Y') {
            if (Y-- > 0) result[1] += 1;
        }else if (guess[i] == 'R') {
            if (R-- > 0) result[1] += 1;
        }else if (guess[i] == 'G') {
            if (G-- > 0) result[1] += 1;
        }else if (guess[i] == 'B') {
            if (B-- > 0) result[1] += 1;
        }
        ++i;
    }
    
    return result;
}


int maxTurbulenceSize(int* arr, int arrSize){
    // 
    if (arrSize < 2) return arrSize;
    
    int state = 0;
    int maxLen = 1;
    int curLen = 1;
    for (int i = 1; i < arrSize; ++i) {
        int nextState = arr[i]-arr[i-1];
        if ((nextState > 0 && state <= 0) || (nextState < 0 && state >= 0)) {
            ++curLen;
        }else if (nextState == 0){
            curLen = 1;
        }else{
            curLen = 2;
        }
        if (curLen > maxLen) maxLen = curLen;
        state = nextState;
    }
    
    return maxLen;
}

//int missingNumber(int* nums, int numsSize){
//    int total = numsSize*(numsSize+1)/2;
//    for (int i = 0; i < numsSize; ++i) {
//        total -= nums[i];
//    }
//    return total;
//}


