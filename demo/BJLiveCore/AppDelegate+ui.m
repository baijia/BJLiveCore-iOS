//
//  AppDelegate+ui.m
//  LivePlayerApp
//
//  Created by MingLQ on 2016-08-19.
//  Copyright © 2016年 Baijia Cloud. All rights reserved.
//

#import <BJLiveCore/BJLiveCore.h>
#import <M9Dev/M9Dev.h>

#if DEBUG
#import <FLEX/FLEXManager.h>
#endif

#import "AppDelegate+ui.h"

#import "BJAppearance.h"
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
        activeViewController = navigationController.rootViewController;
    }
    
    if (![activeViewController isKindOfClass:viewControllerClass]) {
        UIViewController *viewController = [[viewControllerClass new] wrapWithNavigationController];
        if (rootViewController.presentedViewController) {
            [rootViewController dismissAllViewControllersAnimated:NO completion:^{
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
    UIEventSubtypeMotionShakeState shakeState = [notification.userInfo integerForKey:UIEventSubtypeMotionShakeStateKey];
    if (shakeState == UIEventSubtypeMotionShakeStateEnded) {
        [self showDeveloperTools];
    }
}

- (void)showDeveloperTools {
    @weakify(self);
    
    M9AlertController *alertController = [M9AlertController
                                          alertControllerWithTitle:@"Developer Tools"
                                          message:nil
                                          preferredStyle:M9AlertControllerStyleActionSheet];
    
    [alertController addActionWithTitle:@"FLEX"
                                  style:M9AlertActionStyleDefault
                                handler:^(id<M9AlertAction> action)
     {
         // @strongify(self);
         [[FLEXManager sharedManager] showExplorer];
     }];
    
    [alertController addActionWithTitle:@"切换环境"
                                  style:M9AlertActionStyleDefault
                                handler:^(id<M9AlertAction> action)
     {
         @strongify(self);
         [self askToSwitchDeployType];
     }];
    
    [alertController addActionWithTitle:@"取消"
                                  style:M9AlertActionStyleCancel
                                handler:^(id<M9AlertAction> action)
     {
         // @strongify(self);
     }];
    
    [alertController presentFromViewController:[UIViewController topViewController]
                                      animated:YES
                                    completion:nil];
}

- (void)askToSwitchDeployType {
    // @weakify(self);
    
    BJLDeployType currentDeployType = [BJAppConfig sharedInstance].deployType;
    
    NSString *title = [NSString stringWithFormat:@"当前环境：%@",
                       [self nameOfDeployType:currentDeployType]];
    NSString *message = @"注意：切换环境需要重启应用！";
    
    M9AlertController *alertController = [M9AlertController
                                          alertControllerWithTitle:title
                                          message:message
                                          preferredStyle:M9AlertControllerStyleActionSheet];
    
    for (BJLDeployType deployType = 0; deployType < _BJLDeployType_count; deployType++) {
        if (deployType == currentDeployType) {
            continue;
        }
        [alertController addActionWithTitle:[self nameOfDeployType:deployType]
                                      style:M9AlertActionStyleDestructive
                                    handler:^(id<M9AlertAction> action)
         {
             // @strongify(self);
             [BJAppConfig sharedInstance].deployType = deployType;
         }];
    }
    
    [alertController addActionWithTitle:@"取消"
                                  style:M9AlertActionStyleCancel
                                handler:^(id<M9AlertAction> action)
     {
         // @strongify(self);
     }];
    
    [alertController presentFromViewController:[UIViewController topViewController]
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
            return NSStringFromValue(deployType, nil);
    }
}

#endif

@end
