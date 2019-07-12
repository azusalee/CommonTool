//
//  UIViewController+AZLTopController.m
//  ALExampleTest
//
//  Created by yangming on 2018/7/18.
//  Copyright © 2018年 Mac. All rights reserved.
//

#import "UIViewController+AZLTopController.h"

@implementation UIViewController (AZLTopController)

+ (UIViewController *)azl_topViewControllerInApp{
    UIViewController *controller = [UIApplication sharedApplication].keyWindow.rootViewController;
    
    while (controller.presentedViewController) {
        controller = controller.presentedViewController;
    }
    
    while (controller != controller.azl_topController) {
        controller = controller.azl_topController;
    }
    
    return controller;
}

+ (void)azl_pushViewController:(UIViewController *)pushController {
    UIViewController *topViewController = [self azl_topViewControllerInApp];
    if (topViewController.navigationController) {
        [topViewController.navigationController pushViewController:pushController animated:YES];
    }
}


- (UIViewController *)azl_topController{
    return self;
}

@end

@implementation UINavigationController (AZLTopController)

- (UIViewController *)azl_topController{
    return self.topViewController;
}

@end

@implementation UITabBarController (AZLTopController)

- (UIViewController *)azl_topController{
    return self.selectedViewController;
}

@end
