//
//  BJAppearance.m
//  LivePlayerApp
//
//  Created by MingLQ on 2016-08-20.
//  Copyright © 2016年 BaijiaYun. All rights reserved.
//

#import "BJAppearance.h"

@implementation UIColor (BJColors)

+ (instancetype)bj_brandColor {
    return [self bjl_colorWithHexString:@"#1694FF"];
}

+ (instancetype)bj_grayBackgroundColor {
    return [self bjl_colorWithHexString:@"#F2F4F5"];
}

+ (instancetype)bj_grayBorderColor {
    return [self bjl_colorWithHexString:@"#C1C1C1"]; // #DCDDDE
}

+ (instancetype)bj_navigationBarTintColor {
    return [self bj_darkGrayTextColor];
}

+ (instancetype)bj_darkGrayTextColor {
    return [self bjl_colorWithHexString:@"#3D3D3D"];
}

+ (instancetype)bj_midGrayTextColor {
    return [self bjl_colorWithHexString:@"#6D6E6E"];
}

+ (instancetype)bj_lightGrayTextColor {
    return [self bjl_colorWithHexString:@"#9D9E9E"];
}

+ (instancetype)bj_linkTextColor {
    return [self bjl_colorWithHexString:@"#1694FF"];
}

+ (instancetype)bj_redColor {
    return [self bjl_colorWithHexString:@"#EF3232"];
}

@end
