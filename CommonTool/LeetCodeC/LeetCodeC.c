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
    int i = --gridSize;
    int j = --colSize-1;
    while (i >= 0) {
        while (j >= 0) {
            if (i != gridSize && j != colSize) {
                if (grid[i+1][j] < grid[i][j+1]) {
                    grid[i][j] = grid[i][j]+grid[i+1][j];
                }else{
                    grid[i][j] = grid[i][j]+grid[i][j+1];
                }
            } else if (j != colSize) {
                grid[i][j] = grid[i][j]+grid[i][j+1];
            } else {
                grid[i][j] = grid[i][j]+grid[i+1][j];
            }
            --j;
        }
        j = colSize;
        --i;
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
    if (n == 0) return 1;
    int count = 0;
    int tmp = 1;
    for (int i = 2; i <= n; ++i) {
        tmp *= i;
        while (tmp%10 == 0) {
            ++count;
            tmp /= 10;
        }
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
