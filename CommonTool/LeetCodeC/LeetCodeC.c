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
