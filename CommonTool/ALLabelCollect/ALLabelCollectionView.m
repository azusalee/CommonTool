//
//  ALLabelCollectionView.m
//  CommonTool
//
//  Created by lizihong on 2020/2/17.
//  Copyright © 2020 AL. All rights reserved.
//

#import "ALLabelCollectionView.h"

@interface ALLabelCollectionView()<UICollectionViewDelegate, UICollectionViewDataSource, UICollectionViewDelegateFlowLayout>

@property (nonatomic, strong) NSString *cellClassName;

@end

@implementation ALLabelCollectionView

- (void)awakeFromNib{
    [super awakeFromNib];
    [self setup];
}

- (instancetype)initWithFrame:(CGRect)frame{
    if (self = [super initWithFrame:frame]) {
        [self setup];
    }
    return self;
}

- (void)setup{
    self.delegate = self;
    self.dataSource = self;
}

- (void)setCellClassName:(NSString *)cellClassName{
    _cellClassName = cellClassName;
    [self registerNib:[UINib nibWithNibName:cellClassName bundle:nil] forCellWithReuseIdentifier:cellClassName];
}

- (UICollectionViewCell *)collectionView:(UICollectionView *)collectionView cellForItemAtIndexPath:(NSIndexPath *)indexPath{
    ALLabelCollectionViewCell *cell = [collectionView dequeueReusableCellWithReuseIdentifier:self.cellClassName forIndexPath:indexPath];
    if (cell.deleteBlock == nil) {
        __weak typeof(self) weakself = self;
        [cell setDeleteBlock:^(ALLabelCollectionCellModel * _Nonnull model) {
            if (weakself.deleteBlock) {
                weakself.deleteBlock(model);
            }
        }];
    }
    cell.model = self.dataArray[indexPath.row];
    return cell;
}

- (NSInteger)collectionView:(nonnull UICollectionView *)collectionView numberOfItemsInSection:(NSInteger)section { 
    return self.dataArray.count;
}


- (CGSize)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout *)collectionViewLayout sizeForItemAtIndexPath:(NSIndexPath *)indexPath{
    // 返回计算好的cellsize
    ALLabelCollectionCellModel *model = self.dataArray[indexPath.row];
    return CGSizeMake(model.width, model.height);
}

@end
