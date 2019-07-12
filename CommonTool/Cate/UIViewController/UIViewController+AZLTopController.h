//
//  UIViewController+AZLTopController.h
//  ALExampleTest
//
//  Created by yangming on 2018/7/18.
//  Copyright © 2018年 Mac. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface UIViewController (AZLTopController)

///獲取當前最頂層的controller
+ (UIViewController *)azl_topViewControllerInApp;
///用最頂層的vc取push一個controller
+ (void)azl_pushViewController:(UIViewController *)pushController;


///獲取自己最頂層的controller
- (UIViewController *)azl_topController;

@end
