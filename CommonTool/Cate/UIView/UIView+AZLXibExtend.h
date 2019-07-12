//
//  UIView+AZLXibExtend.h
//  ALExampleTest
//
//  Created by yangming on 2018/7/27.
//  Copyright © 2018年 Mac. All rights reserved.
//

#import <UIKit/UIKit.h>

//給xib拉界面用的，不建議在代碼中調用
@interface UIView (AZLXibExtend)

// 边界宽
@property (nonatomic, assign) IBInspectable CGFloat xib_borderWidth;
// 边界颜色
@property (nonatomic, weak) IBInspectable UIColor *xib_borderColor;
// 圆角
@property (nonatomic, assign) IBInspectable CGFloat xib_cornerRadius;

//陰影
@property (nonatomic, assign) IBInspectable BOOL xib_shadow;
//阴影颜色
@property (nonatomic, weak) IBInspectable UIColor *xib_shadowColor;
//阴影偏移
@property (nonatomic, assign) IBInspectable CGFloat xib_shadowRadius;

@end
