//
//  ViewController.m
//  testapp
//
//  Created by lizihong on 2021/10/28.
//  Copyright © 2021 AL. All rights reserved.
//

#import "ViewController.h"

struct AlphabetTree {
    int count;
    int level;
    char c;
    struct AlphabetTree *parentTree; 
    struct AlphabetTree *nextTrees[26];
};

struct AlphabetTree * createAlphabetTree(char c) {
    struct AlphabetTree *tree = malloc(sizeof(struct AlphabetTree));
    tree->count = 0;
    tree->level = 0;
    tree->c = c;
    tree->parentTree = NULL;
    for (int i = 0; i < 26; ++i) {
        tree->nextTrees[i] = NULL;
    }
    return tree;
}

// 1044. 最长重复子串
char * longestDupSubstring(char * s){
    // 用字母树
    int length = strlen(s);
    
    struct AlphabetTree *trees[26];
    for (int i = 0; i < 26; ++i) {
        trees[i] = NULL;
    }
    
    struct AlphabetTree *resultTree = NULL;
    
    // 把所有子串历遍，时间复杂度O(n^2)，超时
    for (int i = 0; i < length; ++i) {
        if (resultTree != NULL && length-i-1 <= resultTree->level) {
            break;
        }
        struct AlphabetTree *curTree = trees[s[i]-'a'];
        if (curTree == NULL) {
            curTree = createAlphabetTree(s[i]);
            trees[s[i]-'a'] = curTree;
        }
        curTree->count += 1;
        if (curTree->count >= 2) {
            if (resultTree == NULL) {
                resultTree = curTree;
            } else if (curTree->level > resultTree->level) {
                resultTree = curTree;
            }
        }
        for (int j = i+1; j < length; ++j) {
            int index = s[j]-'a';
            struct AlphabetTree *nextTree = curTree->nextTrees[index];
            if (nextTree == NULL) {
                nextTree = createAlphabetTree(s[j]);
                nextTree->parentTree = curTree;
                nextTree->level = curTree->level+1;
                curTree->nextTrees[index] = nextTree;
            }
            curTree = nextTree;
            curTree->count += 1;
            if (curTree->count >= 2) {
                if (resultTree == NULL) {
                    resultTree = curTree;
                } else if (curTree->level > resultTree->level) {
                    resultTree = curTree;
                }
            }
        }
    }
    char *resultString;
    if (resultTree != NULL) {
        resultString = malloc(sizeof(char)*(resultTree->level+2));
        int index = resultTree->level;
        resultString[index+1] = '\0';
        while (resultTree) {
            resultString[index] = resultTree->c;
            resultTree = resultTree->parentTree;
            index -= 1;
        }
        return resultString;
    } else {
        resultString = "";
    }
    // 要释放所有AlphabetTree
    
    return resultString;
}


@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    longestDupSubstring("banana");
}


@end
