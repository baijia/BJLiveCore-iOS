//
//  UIViewController+BJUtil.m
//  LivePlayerApp
//
//  Created by MingLQ on 2016-08-22.
//  Copyright © 2016年 BaijiaYun. All rights reserved.
//

#import <BJLiveCore/BJLiveCore.h>

#import "UIViewController+BJUtil.h"

@implementation UIViewController (BJBack)

- (void)addChildViewController:(UIViewController *)childViewController superview:(UIView *)superview {
    /* The addChildViewController: method automatically calls the willMoveToParentViewController: method
     * of the view controller to be added as a child before adding it.
     */
    [self addChildViewController:childViewController]; // 1
    [superview addSubview:childViewController.view]; // 2
    [childViewController didMoveToParentViewController:self]; // 3
}

- (void)removeFromParentViewControllerAndSuperiew {
    [self willMoveToParentViewController:nil]; // 1
    /* The removeFromParentViewController method automatically calls the didMoveToParentViewController: method
     * of the child view controller after it removes the child.
     */
    [self.view removeFromSuperview]; // 2
    [self removeFromParentViewController]; // 3
}

+ (UIViewController *)topViewController {
    UIViewController *topViewController = [UIApplication sharedApplication].keyWindow.rootViewController;
    UITabBarController *tabBarController = [topViewController bjl_as:[UITabBarController class]];
    if (tabBarController.selectedViewController) {
        topViewController = tabBarController.selectedViewController;
    }
    while (topViewController.presentedViewController) {
        topViewController = topViewController.presentedViewController;
    }
    UINavigationController *navigationController = [topViewController bjl_as:[UINavigationController class]];
    if ([navigationController.viewControllers count]) {
        topViewController = navigationController.viewControllers.lastObject;
    }
    return topViewController;
}

@end
