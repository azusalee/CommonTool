//
//  ALPageViewController.h
//  CommonTool
//
//  Created by lizihong on 2020/2/17.
//  Copyright © 2020 AL. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@protocol ALPageViewControllerDelegate <NSObject>

// 页面滑动会回调
- (void)alPageViewControllerPageDidScroll:(CGPoint)offset percentage:(double)percentage pageIndex:(NSInteger)pageIndex;

@end

@interface ALPageViewController : UIViewController

@property (nonatomic, strong) NSArray *vcArray;
@property (nonatomic, assign) CGSize cellSize;

@property (nonatomic, weak) id<ALPageViewControllerDelegate> pageDelegate;


@end

NS_ASSUME_NONNULL_END
