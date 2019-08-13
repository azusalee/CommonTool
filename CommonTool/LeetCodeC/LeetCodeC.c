//
//  LeetCodeC.c
//  CommonTool
//
//  Created by yangming on 2019/8/8.
//  Copyright © 2019 AL. All rights reserved.
//

#include "LeetCodeC.h"
#include <string.h>
#include <stdlib.h>

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
