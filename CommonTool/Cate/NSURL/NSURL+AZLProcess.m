//
//  NSURL+AZLProcess.m
//  ALExampleTest
//
//  Created by yangming on 2018/8/7.
//  Copyright © 2018年 Mac. All rights reserved.
//

#import "NSURL+AZLProcess.h"

@implementation NSURL (AZLProcess)

- (NSDictionary *)azl_queryDict{
    NSString *query = self.query;
    NSArray *array = [query componentsSeparatedByString:@"&"];
    NSMutableDictionary *queryDict = [[NSMutableDictionary alloc] init];
    
    [array enumerateObjectsUsingBlock:^(NSString * _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
        NSArray *keyValue = [obj componentsSeparatedByString:@"="];
        if (keyValue.count > 1) {
            queryDict[keyValue[0]] = keyValue[1];
        }
    }];
    
    return queryDict.copy;
}

@end
