//
//  LeetCodeC.c
//  CommonTool
//
//  Created by yangming on 2019/8/8.
//  Copyright © 2019 AL. All rights reserved.
//

#include "LeetCodeC.h"

/// 罗马数字转整数(1~3999)
int romanToInt(char * s){
    int result = 0, lastIncrease = 0, curIncrease = 0, i = 0;
    while (1) {
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
