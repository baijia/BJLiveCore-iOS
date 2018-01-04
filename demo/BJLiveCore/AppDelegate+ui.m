//
//  AppDelegate+ui.m
//  LivePlayerApp
//
//  Created by MingLQ on 2016-08-19.
//  Copyright © 2016年 BaijiaYun. All rights reserved.
//

#import "AppDelegate+ui.h"

#import "BJAppearance.h"

#import "BJRootViewController.h"
#import "BJLoginViewController.h"

#import "BJAppConfig.h"

@implementation AppDelegate (ui)

- (void)setupAppearance {
    UINavigationBar *navigationBar = [UINavigationBar appearance];
    [navigationBar setTintColor:[UIColor bj_navigationBarTintColor]];
    [navigationBar setTitleTextAttributes:@{ NSFontAttributeName: [UIFont systemFontOfSize:18],
                                             NSForegroundColorAttributeName: [UIColor bj_navigationBarTintColor] }];
}

- (void)setupViewControllers {
    [self showViewController];
}

- (void)showViewController {
    Class viewControllerClass = [BJLoginViewController class];
    
    BJRootViewController *rootViewController = [BJRootViewController sharedInstance];
    
    UIViewController *activeViewController = rootViewController.activeViewController;
    if ([activeViewController isKindOfClass:[UINavigationController class]]) {
        UINavigationController *navigationController = (UINavigationController *)activeViewController;
        activeViewController = navigationController.bjl_rootViewController;
    }
    
    if (![activeViewController isKindOfClass:viewControllerClass]) {
        UINavigationController *viewController = [[viewControllerClass new] bjl_wrapWithNavigationController];
        viewController.delegate = [viewController bjl_asDelegate];
        if (rootViewController.presentedViewController) {
            [rootViewController bjl_dismissPresentedViewControllerAnimated:NO completion:^{
                [rootViewController switchViewController:viewController
                                              completion:nil];
            }];
        }
        else {
            [rootViewController switchViewController:viewController
                                          completion:nil];
        }
    }
}

@end
