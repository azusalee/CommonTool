//
//  ALLabelCollectionViewCell.h
//  CommonTool
//
//  Created by lizihong on 2020/2/17.
//  Copyright © 2020 AL. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ALLabelCollectionCellModel.h"

NS_ASSUME_NONNULL_BEGIN

typedef void(^ALLabelCollectionCellDeleteBlock)(ALLabelCollectionCellModel *model);

@interface ALLabelCollectionViewCell : UICollectionViewCell
@property (weak, nonatomic) IBOutlet UILabel *titleLabel;
@property (nonatomic, strong) ALLabelCollectionCellModel *model;

@property (nonatomic, copy) ALLabelCollectionCellDeleteBlock deleteBlock;

@end

NS_ASSUME_NONNULL_END
