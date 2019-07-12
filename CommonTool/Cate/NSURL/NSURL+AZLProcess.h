//
//  NSURL+AZLProcess.h
//  ALExampleTest
//
//  Created by yangming on 2018/8/7.
//  Copyright © 2018年 Mac. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSURL (AZLProcess)

/// 把url的参数转成字典，注意参数不能含有&和=，不然会有问题
- (NSDictionary *)azl_queryDict;

@end
