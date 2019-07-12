//
//  UIView+ALInController.m
//  tasker
//
//  Created by yangming on 2019/6/10.
//  Copyright © 2019 BT. All rights reserved.
//

#import "UIView+ALInController.h"

@implementation UIView (ALInController)

- (UIViewController *)al_inViewController{
    for (UIView* next = [self superview]; next; next = next.superview) {
        UIResponder *nextResponder = [next nextResponder];
        if ([nextResponder isKindOfClass:[UIViewController class]]) {
            return (UIViewController *)nextResponder;
        }
    }
    return nil;
}

@end
