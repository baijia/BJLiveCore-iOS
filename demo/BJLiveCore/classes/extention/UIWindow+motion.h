//
//  UIWindow+motion.h
//  LivePlayerApp
//
//  Created by MingLQ on 2016-08-19.
//  Copyright © 2016年 BaijiaYun. All rights reserved.
//

#import <UIKit/UIKit.h>

extern NSString * const UIEventSubtypeMotionShakeNotification;
extern NSString * const UIEventSubtypeMotionShakeStateKey;

typedef NS_ENUM(NSInteger, UIEventSubtypeMotionShakeState) {
    UIEventSubtypeMotionShakeStateBegan,
    UIEventSubtypeMotionShakeStateEnded,
    UIEventSubtypeMotionShakeStateCancelled
};

@interface UIWindow (motion)

@end
