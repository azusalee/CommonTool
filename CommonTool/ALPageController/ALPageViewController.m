//
//  ALPageViewController.m
//  CommonTool
//
//  Created by lizihong on 2020/2/17.
//  Copyright © 2020 AL. All rights reserved.
//

#import "ALPageViewController.h"
#import "ALControllerCollectionViewCell.h"

@interface ALPageViewController ()<UICollectionViewDelegateFlowLayout, UICollectionViewDataSource>

@property (nonatomic, strong) UICollectionView *collectionView;
@end

@implementation ALPageViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    UICollectionViewFlowLayout *layout = [UICollectionViewFlowLayout new];
    layout.minimumLineSpacing = 0;
    layout.minimumInteritemSpacing = 0;
    layout.scrollDirection = UICollectionViewScrollDirectionHorizontal;
    layout.sectionInset = UIEdgeInsetsZero;
    self.collectionView = [[UICollectionView alloc] initWithFrame:CGRectMake(0, 0, self.cellSize.width, self.cellSize.height)];
    self.collectionView.pagingEnabled = YES;
    self.collectionView.backgroundColor = [UIColor clearColor];
    self.collectionView.bounces = NO;
    [self.collectionView registerClass:[ALControllerCollectionViewCell class] forCellWithReuseIdentifier:@"ALControllerCollectionViewCell"];
    [self.view addSubview:self.collectionView];
}

- (void)scrollViewDidScroll:(UIScrollView *)scrollView{
    
}

- (UICollectionViewCell *)collectionView:(UICollectionView *)collectionView cellForItemAtIndexPath:(NSIndexPath *)indexPath{
    ALControllerCollectionViewCell *cell = [collectionView dequeueReusableCellWithReuseIdentifier:@"ALControllerCollectionViewCell" forIndexPath:indexPath];
    if (cell.controller != nil) {
        [cell.controller.view removeFromSuperview];
    }
    UIViewController *controller = self.vcArray[indexPath.row];
    cell.controller = controller;
    [cell.contentView addSubview:controller.view];
    return cell;
}

- (NSInteger)collectionView:(nonnull UICollectionView *)collectionView numberOfItemsInSection:(NSInteger)section { 
    return self.vcArray.count;
}


- (CGSize)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout *)collectionViewLayout sizeForItemAtIndexPath:(NSIndexPath *)indexPath{
    // 返回计算好的cellsize
    return self.cellSize;
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
