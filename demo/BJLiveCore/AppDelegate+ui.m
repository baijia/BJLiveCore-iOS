//
//  AppDelegate+ui.m
//  LivePlayerApp
//
//  Created by MingLQ on 2016-08-19.
//  Copyright © 2016年 Baijia Cloud. All rights reserved.
//

#import <BJLiveCore/BJLiveCore.h>
#import <libextobjc/EXTScope.h>

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
    @weakify(self);
    
    UIAlertController *alertController = [UIAlertController
                                          alertControllerWithTitle:@"Developer Tools"
                                          message:nil
                                          preferredStyle:UIAlertControllerStyleActionSheet];
    
    [alertController addAction:[UIAlertAction actionWithTitle:@"FLEX"
                                                        style:UIAlertActionStyleDefault
                                                      handler:^(UIAlertAction *action)
                                {
                                    // @strongify(self);
                                    [[FLEXManager sharedManager] showExplorer];
                                }]];
    
    [alertController addAction:[UIAlertAction actionWithTitle:@"切换环境"
                                                        style:UIAlertActionStyleDefault
                                                      handler:^(UIAlertAction *action)
                                {
                                    @strongify(self);
                                    [self askToSwitchDeployType];
                                }]];
    
    [alertController addAction:[UIAlertAction actionWithTitle:@"取消"
                                                        style:UIAlertActionStyleCancel
                                                      handler:^(UIAlertAction *action)
                                {
                                    // @strongify(self);
                                }]];
    
    [[UIViewController topViewController] presentViewController:alertController
                                                       animated:YES
                                                     completion:nil];
}

- (void)askToSwitchDeployType {
    // @weakify(self);
    
    BJLDeployType currentDeployType = [BJAppConfig sharedInstance].deployType;
    
    NSString *title = [NSString stringWithFormat:@"当前环境：%@",
                       [self nameOfDeployType:currentDeployType]];
    NSString *message = @"注意：切换环境需要重启应用！";
    
    UIAlertController *alertController = [UIAlertController
                                          alertControllerWithTitle:title
                                          message:message
                                          preferredStyle:UIAlertControllerStyleActionSheet];
    
    for (BJLDeployType deployType = 0; deployType < _BJLDeployType_count; deployType++) {
        if (deployType == currentDeployType) {
            continue;
        }
        [alertController addAction:[UIAlertAction actionWithTitle:[self nameOfDeployType:deployType]
                                                            style:UIAlertActionStyleDestructive
                                                          handler:^(UIAlertAction *action)
                                    {
                                        // @strongify(self);
                                        [BJAppConfig sharedInstance].deployType = deployType;
                                    }]];
    }
    
    [alertController addAction:[UIAlertAction actionWithTitle:@"取消"
                                                        style:UIAlertActionStyleCancel
                                                      handler:^(UIAlertAction *action)
                                {
                                    // @strongify(self);
                                }]];
    
    [[UIViewController topViewController] presentViewController:alertController
                                                       animated:YES
                                                     completion:nil];
}

- (NSString *)nameOfDeployType:(BJLDeployType)deployType {
    switch (deployType) {
        case BJLDeployType_test:
            return @"test";
        case BJLDeployType_beta:
            return @"beta";
        case BJLDeployType_www:
            return @"www";
        default:
            return [@(deployType) description];
    }
}

#endif

@end
