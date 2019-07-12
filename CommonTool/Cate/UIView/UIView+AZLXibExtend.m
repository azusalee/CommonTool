//
//  UIView+AZLXibExtend.m
//  ALExampleTest
//
//  Created by yangming on 2018/7/27.
//  Copyright © 2018年 Mac. All rights reserved.
//

#import "UIView+AZLXibExtend.h"



@implementation UIView (AZLXibExtend)

@dynamic xib_borderWidth;
@dynamic xib_borderColor;
@dynamic xib_cornerRadius;

@dynamic xib_shadow;
@dynamic xib_shadowColor;
@dynamic xib_shadowRadius;

- (void)setXib_borderWidth:(CGFloat)borderWidth
{
    if(borderWidth < 0) return;
    self.layer.borderWidth = borderWidth;
}

- (void)setXib_borderColor:(UIColor *)borderColor
{
    self.layer.borderColor = borderColor.CGColor;
}

- (void)setXib_cornerRadius:(CGFloat)cornerRadius
{
    self.layer.cornerRadius = cornerRadius;
}

- (void)setXib_shadow:(BOOL)xib_shadow{
    if (xib_shadow) {
        self.layer.shadowOffset = CGSizeMake(3, 3);
        self.layer.shadowOpacity = 0.5;
        UIBezierPath *path = [UIBezierPath bezierPathWithRoundedRect:self.bounds cornerRadius:self.layer.cornerRadius];
        self.layer.shadowPath = path.CGPath;
    }
}

- (void)setXib_shadowColor:(UIColor *)xib_shadowColor{
    if (xib_shadowColor) {
        self.layer.shadowColor = xib_shadowColor.CGColor;
    }
}

- (void)setXib_shadowRadius:(CGFloat)xib_shadowRadius{
    self.layer.shadowRadius = xib_shadowRadius;
}

@end
