//
//  ALLabelCollectionViewCell.m
//  CommonTool
//
//  Created by lizihong on 2020/2/17.
//  Copyright © 2020 AL. All rights reserved.
//

#import "ALLabelCollectionViewCell.h"

@implementation ALLabelCollectionViewCell

- (void)awakeFromNib {
    [super awakeFromNib];
    // Initialization code
}

- (void)setModel:(ALLabelCollectionCellModel *)model{
    _model = model;
    self.titleLabel.text = model.title;
    
}

- (IBAction)deleteDidTap:(id)sender {
    if (self.deleteBlock) {
        self.deleteBlock(self.model);
    }
}


@end
