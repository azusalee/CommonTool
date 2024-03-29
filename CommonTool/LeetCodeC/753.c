//
//  753.c
//  CommonTool
//
//  Created by lizihong on 2023/1/10.
//  Copyright © 2023 AL. All rights reserved.
//

#include "753.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

/*
 https://leetcode.cn/problems/cracking-the-safe/solution/po-jie-bao-xian-xiang-by-leetcode-solution/
 */


#define N 10000
int visited[N];
char str[N];
int len, k_rec;
int highest;

void dfs(int node) {
    for (int x = 0; x < k_rec; ++x) {
        int nei = node * 10 + x;
        if (!visited[nei]) {
            visited[nei] = 1;
            dfs(nei % highest);
            str[len++] = x + '0';
        }
    }
}

char *crackSafe(int n, int k) {
    memset(visited, 0, sizeof(visited));
    memset(str, 0, sizeof(str));
    k_rec = k, len = 0;
    visited[0] = true;
    highest = pow(10, n - 1);
    dfs(0);
    for (int i = 0; i < n; i++) {
        str[len++] = '0';
    }
    return str;
}

