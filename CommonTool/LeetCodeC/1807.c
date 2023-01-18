//
//  1807.c
//  CommonTool
//
//  Created by lizihong on 2023/1/12.
//  Copyright © 2023 AL. All rights reserved.
//

#include "1807.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "uthash.h"

/// 暴力法 超时
char * evaluate1(char * s, char *** knowledge, int knowledgeSize, int* knowledgeColSize){
    
    int index = 0;
    int left = -1;
    int len = strlen(s);
    char *result = malloc(sizeof(char)*(len+1));
    result[0] = '\0';
    while (s[index] != '\0') {
        if (s[index] == '(') {
            left = index;
        } else if (s[index] == ')') {
            char tmpStr[index-left];
            int j = 0;
            for (int i = left+1; i < index; ++i) {
                tmpStr[j++] = s[i];
            }
            tmpStr[j] = '\0';
            char *targetValue = NULL;
            for (int i = 0; i < knowledgeSize; ++i) {
                if (strcmp(tmpStr, knowledge[i][0]) == 0) {
                    targetValue = knowledge[i][1];
                    break;
                }
            }
            if (targetValue != NULL) {
                result = strcat(result, targetValue);
            } else{
                result = strcat(result, "?");
            }
            left = -1;
        } else if (left == -1) {
            char tmpStr[2];
            tmpStr[0] = s[index];
            tmpStr[1] = '\0';
            result = strcat(result, tmpStr);
        }
        ++index;
    }
    
    return result;
}



typedef struct {
    char *key;
    char *val;
    UT_hash_handle hh;
} HashItem;

HashItem *hashFindItem(HashItem **obj, const char *key) {
    HashItem *pEntry = NULL;
    HASH_FIND_STR(*obj, key, pEntry);
    return pEntry;
}

bool hashAddItem(HashItem **obj, char *key, char *val) {
    if (hashFindItem(obj, key)) {
        return false;
    }
    HashItem *pEntry = (HashItem *)malloc(sizeof(HashItem));
    pEntry->key = key;
    pEntry->val = val;
    HASH_ADD_STR(*obj, key, pEntry);
    return true;
}

void hashFree(HashItem **obj) {
    HashItem *curr = NULL, *tmp = NULL;
    HASH_ITER(hh, *obj, curr, tmp) {
        HASH_DEL(*obj, curr);
        free(curr);
    }
}

char * evaluate(char * s, char *** knowledge, int knowledgeSize, int* knowledgeColSize) {
    HashItem *dict = NULL;
    for (int i = 0; i < knowledgeSize; i++) {
        hashAddItem(&dict, knowledge[i][0], knowledge[i][1]);
    }
    bool addKey = false;
    int len = strlen(s);
    char key[16], *res = (char *)malloc(sizeof(char) * (len + 1));
    int keySize = 0, resSize = 0;
    memset(key, 0, sizeof(key));
    memset(res, 0, sizeof(char) * (len + 1));
    for (int i = 0; s[i] != '\0'; i++) {
        char c = s[i];
        if (c == '(') {
            addKey = true;
        } else if (c == ')') {
            HashItem *pEntry = hashFindItem(&dict, key);
            if (pEntry) {
                resSize += sprintf(res + resSize, "%s", pEntry->val);
            } else {
                res[resSize++] = '?';
            }
            addKey = false;
            keySize = 0;
        } else {
            if (addKey) {
                key[keySize++] = c;
                key[keySize] = '\0';
            } else {
                res[resSize++] = c;
            }
        }
    }
    hashFree(&dict);
    return res;
}
