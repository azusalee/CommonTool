//
//  1813.c
//  CommonTool
//
//  Created by lizihong on 2023/1/16.
//  Copyright © 2023 AL. All rights reserved.
//

#include "1813.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>


bool areSentencesSimilar(char * sentence1, char * sentence2){

    int len1 = strlen(sentence1);
    int len2 = strlen(sentence2);
    
    // 让sentence1始终是比较长的那个字符串
    if (len1 < len2) {
        int tmp = len2;
        len2 = len1;
        len1 = tmp;
        
        char *tmpS = sentence2;
        sentence2 = sentence1;
        sentence1 = tmpS;
    }
    
    int l1 = 0, l2 = 0, r1 = len1-1, r2 = len2-1;
    
    int frontIndex = 0;
    // 从前向后遍历，找出前半相同的句子
    while (l2 < len2) {
        if (sentence1[l1] != sentence2[l2]) {
            break;
        }
        if (sentence2[l2] == ' ') {
            frontIndex = l2;
        }
        ++l1;
        ++l2;
    }
    // 如果短句已经全部遍历了，判断长句在此处是否是一个完整句子(' ' 或 '\0' 结尾)
    if (l2 == len2 && (sentence1[l1] == ' ' || sentence1[l1] == '\0')) return true;
    
    // 从后向前 把剩余的字符遍历
    while (r2 >= frontIndex) {
        if (sentence1[r1] != sentence2[r2]) {
            return false;
        }
        
        --r1;
        --r2;
    }
    
    // 判断后半段是否完成句子
    return frontIndex > 0 || sentence1[r1] == ' ';
}
