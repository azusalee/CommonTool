//
//  UIView+ALInController.h
//  tasker
//
//  Created by yangming on 2019/6/10.
//  Copyright © 2019 BT. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface UIView (ALInController)

/// 获取视图所在的controller
- (nullable UIViewController *)al_inViewController;

@end

NS_ASSUME_NONNULL_END
