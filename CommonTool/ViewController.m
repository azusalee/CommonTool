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
    
    romanToInt("IV");
    
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


@end
