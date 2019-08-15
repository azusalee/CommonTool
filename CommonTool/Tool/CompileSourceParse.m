//
//  CompileSourceParse.m
//  CommonTool
//
//  Created by lizihong on 2019/8/15.
//  Copyright © 2019 AL. All rights reserved.
//

#import "CompileSourceParse.h"

@implementation CompileSourceParse

+ (NSArray *)arrayFromCompileString:(NSString *)compileString {

    NSRegularExpression *regex = [[NSRegularExpression alloc] initWithPattern:@"\\S*(\\.)" options:NSRegularExpressionUseUnicodeWordBoundaries error:nil];
    //NSRegularExpression *regex = [[NSRegularExpression alloc] initWithPattern:@"(\\.m)" options:NSRegularExpressionUseUnicodeWordBoundaries error:nil];
    NSArray *matchs = [regex matchesInString:compileString options:0 range:NSMakeRange(0, compileString.length)];
    
    if (matchs.count > 0 ) {
        NSMutableArray *tmpArr = [[NSMutableArray alloc] init];
        for (int i = 0; i < matchs.count; ++i){
            NSTextCheckingResult *match = matchs[i];
            NSRange range = match.range;
            NSString *matchString = [compileString substringWithRange:range];
            [tmpArr addObject:matchString];
        }
        return tmpArr.copy;
    }
    return @[];
}

@end
