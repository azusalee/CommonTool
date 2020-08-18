//
//  ViewController.m
//  CommonTool
//
//  Created by yangming on 2019/6/21.
//  Copyright © 2019 AL. All rights reserved.
//

#import "ViewController.h"
#import <CoreLocation/CoreLocation.h>
#import "LeetCodeC.h"
#import "CompileSourceParse.h"
#import "ALLabelCollectionDemoViewController.h"

@interface ViewController ()
@property (weak, nonatomic) IBOutlet UILabel *distanceLabel;
@property (weak, nonatomic) IBOutlet UITextField *lat1TextField;
@property (weak, nonatomic) IBOutlet UITextField *lon1TextField;
@property (weak, nonatomic) IBOutlet UITextField *lat2TextField;
@property (weak, nonatomic) IBOutlet UITextField *lon2TextField;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
//    int b = 100;
//    int a = -(b < 128);
//    printf("%d", a);
//    b = ~a&b;
//    printf("%d", b);

    struct TreeNode *node1 = malloc(sizeof(struct TreeNode));
    node1->val = 1;
    node1->right = NULL;
    node1->left = NULL;
    
    struct TreeNode *node2 = malloc(sizeof(struct TreeNode));
    node2->val = 3;
    node2->right = NULL;
    node2->left = NULL;
    node1->left = node2;
    
    struct TreeNode *node3 = malloc(sizeof(struct TreeNode));
    node3->val = 2;
    node3->right = NULL;
    node3->left = NULL;
    node2->right = node3;
    recoverTree(node1);
    
    int tmpSize;
    int* tmpColumnSizes;
    partition("cdd", &tmpSize, &tmpColumnSizes);
    int size = 0;
    grayCode(3, &size);
    diffWaysToCompute("1+1+1+1+1+1+1+1+1+1", &size);
    
    rotatedDigits(857);
    int nums[] = {1,3};
    lastStoneWeight(nums, 2);
//    nextPermutation(nums, 3);
//    isMatch("aasdfasdfasdfasdfas", "aasdf.*asdf.*asdf.*asdf.*s");
    getPermutation(4, 10);
    //threeSumClosest(nums, 4, 100);
    int returnSize;
    int *returnColumnSizes;
//    fourSum(nums, 6, 0, &returnSize, &returnColumnSizes);
   // int returnSize = 0;
    //findOcurrences("we will we will rock you", "we", "will", &returnSize);
    //allCellsDistOrder(3, 3, 0, 2, &returnSize, &returnColumnSizes);
    
    NSArray *arr = [[NSUserDefaults standardUserDefaults] objectForKey:@"AppleLanguages"];
    NSString *languageName = arr.firstObject;
    NSLog(@"语言:%@", languageName);
    
    NSString *testString = NSLocalizedString(@"Hello", nil);
    NSLog(@"%@", testString);
    NSString *testString2 = NSLocalizedString(@"Haha", nil);
    NSLog(@"%@", testString2);
    NSString *testString3 = NSLocalizedString(@"Hehe", nil);
    NSLog(@"%@", testString3);
    self.distanceLabel.text = [NSString stringWithFormat:@"%@ %@ %@", testString, testString2, testString3];
    
    NSString *string1 = [[NSString alloc] initWithContentsOfFile:[[NSBundle mainBundle] pathForResource:@"sourceString1" ofType:@"txt"] encoding:NSUTF8StringEncoding error:nil];
    NSString *string2 = [[NSString alloc] initWithContentsOfFile:[[NSBundle mainBundle] pathForResource:@"sourceString2" ofType:@"txt"] encoding:NSUTF8StringEncoding error:nil];
    NSArray *array1 = [CompileSourceParse arrayFromCompileString:string1];
    NSArray *array2 = [CompileSourceParse arrayFromCompileString:string2];
    
    NSMutableArray *diffArray = [[NSMutableArray alloc] init];
    NSLog(@"对比Array2");
    for (int i = 0; i < array2.count; ++i) {
        if (![array1 containsObject:array2[i]]) {
            NSLog(@"%@", array2[i]);
            if (![diffArray containsObject:array2[i]]) {
                [diffArray addObject:array2[i]];
            }
        }
    }
    
    NSLog(@"对比Array1");
    for (int i = 0; i < array1.count; ++i) {
        if (![array2 containsObject:array1[i]]) {
            NSLog(@"%@", array1[i]);
            if (![diffArray containsObject:array1[i]]) {
                [diffArray addObject:array1[i]];
            }
        }
    }
    
    NSLog(@"差别 %@", diffArray);
    
}

- (IBAction)caculateDidTap:(id)sender {
    CLLocationCoordinate2D coor1 = CLLocationCoordinate2DMake(self.lat1TextField.text.doubleValue, self.lon1TextField.text.doubleValue);
    CLLocationCoordinate2D coor2 = CLLocationCoordinate2DMake(self.lat2TextField.text.doubleValue, self.lon2TextField.text.doubleValue);
    
    double distance = [self distanceBetweenCoordinate1:coor1 coordinate2:coor2];
    self.distanceLabel.text = [NSString stringWithFormat:@"%f", distance];

}


//計算兩個坐標間的距離
- (double)distanceBetweenCoordinate1:(CLLocationCoordinate2D)coor1 coordinate2:(CLLocationCoordinate2D)coor2
{
//    CLLocation *location1 = [[CLLocation alloc] initWithLatitude:coor1.latitude longitude:coor2.longitude];
//    CLLocation *location2 = [[CLLocation alloc] initWithLatitude:coor2.latitude longitude:coor2.longitude];
//    double dis = [location1 distanceFromLocation:location2];
//
//    return dis;
    double lat1 = coor1.latitude;
    double lon1 = coor1.longitude;

    double lat2 = coor2.latitude;
    double lon2 = coor2.longitude;

    double er = 6378137; // 6378700.0f;
    //ave. radius = 6371.315 (someone said more accurate is 6366.707)
    //equatorial radius = 6378.388
    //nautical mile = 1.15078
    double radlat1 = M_PI*lat1/180.0f;
    double radlat2 = M_PI*lat2/180.0f;
    //now long.
    double radlong1 = M_PI*lon1/180.0f;
    double radlong2 = M_PI*lon2/180.0f;
    if( radlat1 < 0 ) radlat1 = M_PI/2 + fabs(radlat1);// south
    if( radlat1 > 0 ) radlat1 = M_PI/2 - fabs(radlat1);// north
    if( radlong1 < 0 ) radlong1 = M_PI*2 - fabs(radlong1);//west
    if( radlat2 < 0 ) radlat2 = M_PI/2 + fabs(radlat2);// south
    if( radlat2 > 0 ) radlat2 = M_PI/2 - fabs(radlat2);// north
    if( radlong2 < 0 ) radlong2 = M_PI*2 - fabs(radlong2);// west
    //spherical coordinates x=r*cos(ag)sin(at), y=r*sin(ag)*sin(at), z=r*cos(at)
    //zero ag is up so reverse lat
    double x1 = er * cos(radlong1) * sin(radlat1);
    double y1 = er * sin(radlong1) * sin(radlat1);
    double z1 = er * cos(radlat1);
    double x2 = er * cos(radlong2) * sin(radlat2);
    double y2 = er * sin(radlong2) * sin(radlat2);
    double z2 = er * cos(radlat2);
    double d = sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)+(z1-z2)*(z1-z2));
    //side, side, side, law of cosines and arccos
    double theta = acos((er*er+er*er-d*d)/(2*er*er));
    double dist  = theta*er;
    return dist;
}

- (IBAction)jumptoDemo:(id)sender {
   UIViewController *controller = [[ALLabelCollectionDemoViewController alloc] init];
   [self.navigationController pushViewController:controller animated:YES];
}

@end
