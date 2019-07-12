//
//  NSString+ALHelper.h
//  ALExampleTest
//
//  Created by 李梓洪 on 2018/5/24.
//  Copyright © 2018年 Mac. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSString (ALHelper)


- (NSString *)al_urlEncodeString;

/// 获取子字符串的range数组
- (NSArray *)al_rangesWithString:(NSString*)subString;

/// 强制解析为utf8（会把能解析为utf8的地方以utf8显示，不能则用latin来显示）
+ (NSString *)al_forceDecodeUtf8Data:(NSData *)data;

@end
