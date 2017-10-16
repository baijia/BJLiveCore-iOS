//
//  UIWindow+motion.m
//  LivePlayerApp
//
//  Created by MingLQ on 2016-08-19.
//  Copyright © 2016年 BaijiaYun. All rights reserved.
//

#import "UIWindow+motion.h"

NSString * const UIEventSubtypeMotionShakeNotification = @"UIEventSubtypeMotionShakeNotification";
NSString * const UIEventSubtypeMotionShakeStateKey = @"UIEventSubtypeMotionShakeState";

@implementation UIWindow (motion)

#pragma mark -

- (BOOL)canBecomeFirstResponder {
    return YES;
}

- (void)motionBegan:(UIEventSubtype)motion withEvent:(UIEvent *)event {
    [super motionBegan:motion withEvent:event];
    
    if (motion == UIEventSubtypeMotionShake) {
        [[NSNotificationCenter defaultCenter]
         postNotificationName:UIEventSubtypeMotionShakeNotification
         object:self
         userInfo:@{ UIEventSubtypeMotionShakeStateKey: @(UIEventSubtypeMotionShakeStateBegan) }];
    }
}

- (void)motionEnded:(UIEventSubtype)motion withEvent:(UIEvent *)event {
    [super motionEnded:motion withEvent:event];
    
    if (motion == UIEventSubtypeMotionShake) {
        [[NSNotificationCenter defaultCenter]
         postNotificationName:UIEventSubtypeMotionShakeNotification
         object:self
         userInfo:@{ UIEventSubtypeMotionShakeStateKey: @(UIEventSubtypeMotionShakeStateEnded) }];
    }
}

- (void)motionCancelled:(UIEventSubtype)motion withEvent:(UIEvent *)event {
    [super motionCancelled:motion withEvent:event];
    
    if (motion == UIEventSubtypeMotionShake) {
        [[NSNotificationCenter defaultCenter]
         postNotificationName:UIEventSubtypeMotionShakeNotification
         object:self
         userInfo:@{ UIEventSubtypeMotionShakeStateKey: @(UIEventSubtypeMotionShakeStateCancelled) }];
    }
}

@end
