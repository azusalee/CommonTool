//
//  ALLabelCollectionView.h
//  CommonTool
//
//  Created by lizihong on 2020/2/17.
//  Copyright © 2020 AL. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ALLabelCollectionViewCell.h"

NS_ASSUME_NONNULL_BEGIN

@interface ALLabelCollectionView : UICollectionView

- (void)setCellClassName:(NSString *)cellClassName;

@property (nonatomic, copy) ALLabelCollectionCellDeleteBlock deleteBlock;
@property (nonatomic, strong) NSArray<ALLabelCollectionCellModel*> *dataArray;

@end

NS_ASSUME_NONNULL_END
