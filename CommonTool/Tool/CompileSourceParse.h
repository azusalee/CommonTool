//
//  CompileSourceParse.h
//  CommonTool
//
//  Created by lizihong on 2019/8/15.
//  Copyright © 2019 AL. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface CompileSourceParse : NSObject

// 获取关联文件数组
+ (NSArray *)arrayFromCompileString:(NSString *)compileString;

@end

NS_ASSUME_NONNULL_END
