//
//  AppDelegate+util.h
//  LivePlayerApp
//
//  Created by MingLQ on 2016-11-22.
//  Copyright © 2016 BaijiaYun. All rights reserved.
//

#import "AppDelegate.h"

@interface AppDelegate (util)

- (void)setupReachability;

#if DEBUG
- (void)setupDeveloperTools;
#endif

@end
