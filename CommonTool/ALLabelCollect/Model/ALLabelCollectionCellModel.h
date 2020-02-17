//
//  ALLabelCollectionCellModel.h
//  CommonTool
//
//  Created by lizihong on 2020/2/17.
//  Copyright © 2020 AL. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface ALLabelCollectionCellModel : NSObject

/// 宽
@property (nonatomic, assign) double width;
/// 高
@property (nonatomic, assign) double height;
/// 标题
@property (nonatomic, strong) NSString *title;


@end

NS_ASSUME_NONNULL_END
