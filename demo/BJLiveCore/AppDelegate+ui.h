//
//  AppDelegate+ui.h
//  LivePlayerApp
//
//  Created by MingLQ on 2016-08-19.
//  Copyright © 2016年 BaijiaYun. All rights reserved.
//

#import "AppDelegate.h"

@interface AppDelegate (ui)

- (void)setupAppearance;
- (void)setupViewControllers;

#if DEBUG
- (void)setupDeveloperTools;
#endif

@end
