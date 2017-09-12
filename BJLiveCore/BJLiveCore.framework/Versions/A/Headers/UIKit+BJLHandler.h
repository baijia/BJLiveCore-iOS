//
//  UIKit+M9Handler.h
//  M9Dev
//
//  Created by MingLQ on 2015-08-11.
//  Copyright (c) 2015 MingLQ <minglq.9@gmail.com>.
//  Released under the MIT license.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface UIControl (BJLHandler)

- (id)bjl_addHandler:(void (^)(__kindof UIControl * _Nullable sender))handler
    forControlEvents:(UIControlEvents)controlEvents;

- (void)bjl_removeHandlerForTarget:(id)target forControlEvents:(UIControlEvents)controlEvents;

- (void)bjl_removeHandlerForControlEvents:(UIControlEvents)controlEvents;

@end

#pragma mark -

@interface UIGestureRecognizer (BJLHandler)

+ (instancetype)bjl_gestureWithHandler:(void (^)(__kindof UIGestureRecognizer * _Nullable gesture))handler;

- (id)bjl_addHandler:(void (^)(__kindof UIGestureRecognizer * _Nullable gesture))handler;

- (void)bjl_removeHandlerForTarget:(id)target;

@end

NS_ASSUME_NONNULL_END
