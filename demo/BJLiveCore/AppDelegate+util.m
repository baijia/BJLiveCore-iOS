//
//  AppDelegate+util.m
//  LivePlayerApp
//
//  Created by MingLQ on 2016-11-22.
//  Copyright © 2016 BaijiaYun. All rights reserved.
//

#import <BJLiveBase/BJLAFNetworkReachabilityManager.h>
#import <BJLiveBase/BJLAFNetworkActivityIndicatorManager.h>

#import <BJLiveBase/BJLMotionWindow.h>
#import <BJLiveBase/NSInvocation+BJL_M9Dev.h>

#import <BJLiveBase/UIAlertController+BJLAddAction.h>

#if DEBUG
#import <FLEX/FLEXManager.h>
#endif

#import "AppDelegate+util.h"

#import "BJAppConfig.h"

static inline SEL setCheckedSelector() {
    return NSSelectorFromString([NSString stringWithFormat:@"_%@%@%@:", @"set", @"Check", @"ed"]);
}

@implementation AppDelegate (util)

- (void)setupReachability {
    [[BJLAFNetworkReachabilityManager sharedManager] startMonitoring];
    [BJLAFNetworkActivityIndicatorManager sharedManager].enabled = YES;
}

#pragma mark - DeveloperTools

#if DEBUG

- (void)setupDeveloperTools {
    NSNotificationCenter *notificationCenter = [NSNotificationCenter defaultCenter];
    [notificationCenter addObserver:self
                           selector:@selector(didShakeWithNotification:)
                               name:BJLEventSubtypeMotionShakeNotification
                             object:nil];
}

- (void)didShakeWithNotification:(NSNotification *)notification {
    BJLEventSubtypeMotionShakeState shakeState = [notification.userInfo bjl_integerForKey:BJLEventSubtypeMotionShakeStateKey];
    if (shakeState == BJLEventSubtypeMotionShakeStateEnded) {
        [self showDeveloperTools];
    }
}

- (void)showDeveloperTools {
    bjl_weakify(self);
    
    UIAlertController *alertController = [UIAlertController
                                          alertControllerWithTitle:@"Developer Tools"
                                          message:nil
                                          preferredStyle:UIAlertControllerStyleActionSheet];
    
    UIAlertAction *flexAction =
    [alertController bjl_addActionWithTitle:@"FLEX"
                                      style:UIAlertActionStyleDefault
                                    handler:^(UIAlertAction *action)
     {
         // bjl_strongify(self);
         [[FLEXManager sharedManager] toggleExplorer];
     }];
    if (![FLEXManager sharedManager].isHidden) {
        SEL sel = setCheckedSelector();
        if ([flexAction respondsToSelector:sel]) {
            BOOL checked = YES;
            [flexAction bjl_invokeWithSelector:sel argument:&checked];
        }
    }
    
    [alertController bjl_addActionWithTitle:[self nameOfDeployType:[BJAppConfig sharedInstance].deployType]
                                      style:UIAlertActionStyleDefault
                                    handler:^(UIAlertAction *action)
     {
         bjl_strongify(self);
         [self askToSwitchDeployType];
     }];
    
    [alertController bjl_addActionWithTitle:@"取消"
                                      style:UIAlertActionStyleCancel
                                    handler:^(UIAlertAction *action)
     {
         // bjl_strongify(self);
     }];
    
    alertController.popoverPresentationController.sourceView = self.window;
    alertController.popoverPresentationController.sourceRect = [UIApplication sharedApplication].statusBarFrame;
    alertController.popoverPresentationController.permittedArrowDirections = UIPopoverArrowDirectionUp | UIPopoverArrowDirectionDown;
    
    [[UIViewController bjl_topViewController] presentViewController:alertController
                                                           animated:YES
                                                         completion:nil];
}

- (void)askToSwitchDeployType {
    // bjl_weakify(self);
    
    BJLDeployType currentDeployType = [BJAppConfig sharedInstance].deployType;
    
    UIAlertController *alertController = [UIAlertController
                                          alertControllerWithTitle:@"切换环境"
                                          message:@"注意：切换环境需要重启应用！"
                                          preferredStyle:UIAlertControllerStyleActionSheet];
    
    for (BJLDeployType deployType = 0; deployType < _BJLDeployType_count; deployType++) {
        UIAlertAction *action =
        [alertController bjl_addActionWithTitle:[self nameOfDeployType:deployType]
                                          style:UIAlertActionStyleDestructive
                                        handler:^(UIAlertAction *action)
         {
             // bjl_strongify(self);
             [BJAppConfig sharedInstance].deployType = deployType;
         }];
        if (deployType == currentDeployType) {
            action.enabled = NO;
            SEL sel = setCheckedSelector();
            if ([action respondsToSelector:sel]) {
                BOOL checked = YES;
                [action bjl_invokeWithSelector:sel argument:&checked];
            }
        }
    }
    
    [alertController bjl_addActionWithTitle:@"取消"
                                      style:UIAlertActionStyleCancel
                                    handler:^(UIAlertAction *action)
     {
         // bjl_strongify(self);
     }];
    
    alertController.popoverPresentationController.sourceView = self.window;
    alertController.popoverPresentationController.sourceRect = [UIApplication sharedApplication].statusBarFrame;
    alertController.popoverPresentationController.permittedArrowDirections = UIPopoverArrowDirectionUp | UIPopoverArrowDirectionDown;
    
    [[UIViewController bjl_topViewController] presentViewController:alertController
                                                           animated:YES
                                                         completion:nil];
}

- (NSString *)nameOfDeployType:(BJLDeployType)deployType {
    switch (deployType) {
        case BJLDeployType_www:
            return @"WWW";
        case BJLDeployType_test:
            return @"TEST";
        case BJLDeployType_beta:
            return @"BETA";
        case BJLDeployType_96kr:
            return @"96kr";
        default:
            return bjl_NSStringFromValue(deployType, @"WWW");
    }
}

#endif

@end
