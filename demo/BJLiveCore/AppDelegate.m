//
//  AppDelegate.m
//  BJLiveCore
//
//  Created by MingLQ on 2016-12-17.
//  Copyright © 2016 BaijiaYun. All rights reserved.
//

#import <BJLiveBase/BJLMotionWindow.h>

#import "AppDelegate.h"
#import "AppDelegate+ui.h"
#import "AppDelegate+util.h"

#import "BJRootViewController.h"

#import "BJAppConfig.h"

@interface AppDelegate ()

@end

@implementation AppDelegate

- (void)beforeVisible {
    BJLRoom.deployType = [BJAppConfig sharedInstance].deployType;
    
    [self setupReachability];
    
    [BJAppConfig initializeInstance];
    
    [self setupAppearance];
    [self setupViewControllers];
}

- (void)afterVisible {
#if DEBUG
    [self setupDeveloperTools];
#endif
}

#pragma mark - <UIApplicationDelegate>

void BJLUncaughtExceptionHandler(NSException *exception) {
    NSLog(@"CRASH: %@", exception);
    NSLog(@"Stack Trace: %@", [exception callStackSymbols]);
}

- (BOOL)application:(UIApplication *)application willFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // TODO: NSUncaughtExceptionHandler *prev = NSGetUncaughtExceptionHandler();
    NSSetUncaughtExceptionHandler(&BJLUncaughtExceptionHandler);
    return YES;
}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    self.window = [[BJLMotionWindow alloc] initWithFrame:[UIScreen mainScreen].bounds];
    self.window.backgroundColor = [UIColor whiteColor];
    self.window.rootViewController = [BJRootViewController sharedInstance];
    
    [self beforeVisible];
    [self.window makeKeyAndVisible];
    // !!!: after every thing is done
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.2 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        [self afterVisible];
    });
    
    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application {
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
}

- (void)applicationWillTerminate:(UIApplication *)application {
}

- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

@end
