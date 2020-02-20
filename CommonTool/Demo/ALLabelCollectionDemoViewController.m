//
//  ALLabelCollectionDemoViewController.m
//  CommonTool
//
//  Created by lizihong on 2020/2/17.
//  Copyright © 2020 AL. All rights reserved.
//

#import "ALLabelCollectionDemoViewController.h"
#import "ALLabelCollectionView.h"

@interface ALLabelCollectionDemoViewController ()
@property (weak, nonatomic) IBOutlet ALLabelCollectionView *labelCollectionView;

@end

@implementation ALLabelCollectionDemoViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    [self.labelCollectionView setCellClassName:@"ALLabelCollectionViewCell"];
    
    NSMutableArray *array = [[NSMutableArray alloc] init];
    
    for (int i = 0; i < 2; ++i) {
        ALLabelCollectionCellModel *model = [ALLabelCollectionCellModel new];
        model.width = 30+5*i;
        model.title = [NSString stringWithFormat:@"l%d", i];
        [array addObject:model];
    }
    self.labelCollectionView.dataArray = array.copy;
    
    [self.labelCollectionView setDeleteBlock:^(ALLabelCollectionCellModel * _Nonnull model) {
        NSLog(@"删除%@", model.title);
    }];
    
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
