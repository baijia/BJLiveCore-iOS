//
//  AppDelegate+ui.m
//  LivePlayerApp
//
//  Created by MingLQ on 2016-08-19.
//  Copyright © 2016年 BaijiaYun. All rights reserved.
//

#import <BJLiveCore/BJLiveCore.h>
#import <BJLiveBase/BJL_EXTScope.h>

#if DEBUG
#import <FLEX/FLEXManager.h>
#endif

#import "AppDelegate+ui.h"

#import "BJAppearance.h"
#import "UIViewController+BJUtil.h"
#import "UIWindow+motion.h"

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
        activeViewController = navigationController.viewControllers.firstObject;
    }
    
    if (![activeViewController isKindOfClass:viewControllerClass]) {
        UIViewController *viewController = [[UINavigationController alloc] initWithRootViewController:[viewControllerClass new]];
        if (rootViewController.presentedViewController) {
            [rootViewController dismissViewControllerAnimated:NO completion:^{
                [rootViewController switchViewController:viewController completion:nil];
            }];
        }
        else {
            [rootViewController switchViewController:viewController completion:nil];
        }
    }
}

#pragma mark - DeveloperTools

#if DEBUG

- (void)setupDeveloperTools {
    NSNotificationCenter *notificationCenter = [NSNotificationCenter defaultCenter];
    [notificationCenter addObserver:self
                           selector:@selector(didShakeWithNotification:)
                               name:UIEventSubtypeMotionShakeNotification
                             object:nil];
}

- (void)didShakeWithNotification:(NSNotification *)notification {
    UIEventSubtypeMotionShakeState shakeState = [notification.userInfo bjl_integerForKey:UIEventSubtypeMotionShakeStateKey];
    if (shakeState == UIEventSubtypeMotionShakeStateEnded) {
        [self showDeveloperTools];
    }
}

- (void)showDeveloperTools {
    // bjl_weakify(self);
    
    UIAlertController *alertController = [UIAlertController
                                          alertControllerWithTitle:@"Developer Tools"
                                          message:nil
                                          preferredStyle:UIAlertControllerStyleActionSheet];
    
    [alertController addAction:[UIAlertAction actionWithTitle:@"FLEX"
                                                        style:UIAlertActionStyleDefault
                                                      handler:^(UIAlertAction *action)
                                {
                                    // bjl_strongify(self);
                                    [[FLEXManager sharedManager] showExplorer];
                                }]];
    
    [alertController addAction:[UIAlertAction actionWithTitle:@"取消"
                                                        style:UIAlertActionStyleCancel
                                                      handler:^(UIAlertAction *action)
                                {
                                    // bjl_strongify(self);
                                }]];
    
    [[UIViewController topViewController] presentViewController:alertController
                                                       animated:YES
                                                     completion:nil];
}

#endif

@end
