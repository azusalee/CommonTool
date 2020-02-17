//
//  ALPageViewController.h
//  CommonTool
//
//  Created by lizihong on 2020/2/17.
//  Copyright © 2020 AL. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface ALPageViewController : UIViewController

@property (nonatomic, strong) NSArray *vcArray;
@property (nonatomic, assign) CGSize cellSize;
@end

NS_ASSUME_NONNULL_END
