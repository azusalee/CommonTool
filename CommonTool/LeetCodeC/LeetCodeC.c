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
