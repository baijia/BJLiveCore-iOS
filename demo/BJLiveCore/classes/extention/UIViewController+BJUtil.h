//
//  UIViewController+BJUtil.h
//  LivePlayerApp
//
//  Created by MingLQ on 2016-08-22.
//  Copyright © 2016年 BaijiaYun. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface UIViewController (BJBack)

- (void)addChildViewController:(UIViewController *)childController superview:(UIView *)superview;
- (void)removeFromParentViewControllerAndSuperiew;

+ (UIViewController *)topViewController;

@end
