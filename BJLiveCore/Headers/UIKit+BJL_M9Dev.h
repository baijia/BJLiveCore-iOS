//
//  UIKit+BJL_M9Dev.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-04-21.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import <UIKit/UIKit.h>
// #import <Masonry/Masonry.h>

static inline CGFloat bjl_screenFloor(CGFloat size) {
    CGFloat scale = [UIScreen mainScreen].scale;
    return floor(size * scale) / scale;
}

static inline CGFloat bjl_screenCeil(CGFloat size) {
    CGFloat scale = [UIScreen mainScreen].scale;
    return ceil(size * scale) / scale;
}

static inline CGRect bjl_fillFrameWithScale(CGRect frame, CGFloat scale) {
    CGFloat width = CGRectGetWidth(frame), height = CGRectGetHeight(frame);
    CGFloat innerHeight = width / scale;
    CGFloat innerWidth = height * scale;
    if (ABS(width - innerWidth) < 2
        || ABS(height - innerHeight) < 2) {
        return frame;
    }
    return CGRectMake(MIN(0, bjl_screenFloor((width - innerWidth) / 2)),
                      MIN(0, bjl_screenFloor((height - innerHeight) / 2)),
                      MAX(width, bjl_screenCeil(innerWidth)),
                      MAX(height, bjl_screenCeil(innerHeight)));
}

static inline CGRect bjl_fitFrameWithScale(CGRect frame, CGFloat scale) {
    CGFloat width = CGRectGetWidth(frame), height = CGRectGetHeight(frame);
    CGFloat innerHeight = width / scale;
    CGFloat innerWidth = height * scale;
    if (ABS(width - innerWidth) < 2
        || ABS(height - innerHeight) < 2) {
        return frame;
    }
    return CGRectMake(MAX(0, bjl_screenFloor((width - innerWidth) / 2)),
                      MAX(0, bjl_screenFloor((height - innerHeight) / 2)),
                      MIN(width, bjl_screenCeil(innerWidth)),
                      MIN(height, bjl_screenCeil(innerHeight)));
}

#pragma mark -

@interface UIResponder (BJL_M9Dev)

- (UIResponder *)bjl_closestResponderOfClass:(Class)clazz; // NOT include self
- (UIResponder *)bjl_closestResponderOfClass:(Class)clazz includeSelf:(BOOL)includeSelf;
- (UIResponder *)bjl_findResponderWithBlock:(BOOL (^)(UIResponder *responder, BOOL *stop))enumerateBlock;

@end

#pragma mark -

@interface UIView (BJL_M9Dev)

- (__kindof UIView *)bjl_closestViewOfClass:(Class)clazz; // NOT include self
- (__kindof UIView *)bjl_closestViewOfClass:(Class)clazz includeSelf:(BOOL)includeSelf; // up to UIViewController
- (__kindof UIView *)bjl_closestViewOfClass:(Class)clazz includeSelf:(BOOL)includeSelf upToResponder:(UIResponder *)upToResponder; // not include the upToResponder, nil - up to UIViewController
- (__kindof UIViewController *)bjl_closestViewController;

- (void)bjl_removeAllConstraints;

@end

#pragma mark -

@interface UIViewController (BJL_M9Dev)

- (void)bjl_addChildViewController:(UIViewController *)childViewController;
- (void)bjl_addChildViewController:(UIViewController *)childViewController superview:(UIView *)superview;
- (void)bjl_addChildViewController:(UIViewController *)childViewController superview:(UIView *)superview atIndex:(NSInteger)index;
- (void)bjl_addChildViewController:(UIViewController *)childViewController superview:(UIView *)superview belowSubview:(UIView *)siblingSubview;
- (void)bjl_addChildViewController:(UIViewController *)childViewController superview:(UIView *)superview aboveSubview:(UIView *)siblingSubview;
- (void)bjl_addChildViewController:(UIViewController *)childViewController addSubview:(void (^)(UIView *parentView, UIView *childView))addSubview;
- (void)bjl_removeFromParentViewControllerAndSuperiew;

- (void)bjl_dismissAllViewControllersAnimated:(BOOL)animated completion:(void (^)(void))completion;

+ (UIViewController *)bjl_gotoRootViewControllerAnimated:(BOOL)animated completion:(void (^)(void))completion;

+ (UIViewController *)bjl_topViewController;
+ (UIViewController *)bjl_rootViewController;

@end

#pragma mark -

@interface UINavigationController (BJL_M9Dev)

@property(nonatomic, strong, readonly, nullable) UIViewController *bjl_rootViewController;

- (void)bjl_pushViewController:(nullable UIViewController *)viewController
                      animated:(BOOL)animated
                    completion:(void (^ __nullable)(void))completion;

- (nullable UIViewController *)bjl_popViewControllerAnimated:(BOOL)animated
                                                  completion:(void (^ __nullable)(void))completion;
- (nullable NSArray *)bjl_popToViewController:(UIViewController *)viewController
                                     animated:(BOOL)animated
                                   completion:(void (^ __nullable)(void))completion;
- (nullable NSArray *)bjl_popToRootViewControllerAnimated:(BOOL)animated
                                               completion:(void (^ __nullable)(void))completion;

@end

#pragma mark -

@interface UIColor (BJL_M9Dev)

// @"#FFFFFF"
+ (UIColor *)bjl_colorWithHexString:(NSString *)hexString;
+ (UIColor *)bjl_colorWithHexString:(NSString *)hexString alpha:(CGFloat)alpha;
// 0xFFFFFF
+ (UIColor *)bjl_colorWithHex:(unsigned)hex;
+ (UIColor *)bjl_colorWithHex:(unsigned)hex alpha:(CGFloat)alpha;

@end

#pragma mark -

@interface UIImage (BJL_M9Dev)

- (UIImage *)bjl_resizableImage;

+ (UIImage *)bjl_imageWithColor:(UIColor *)color;
+ (UIImage *)bjl_imageWithColor:(UIColor *)color size:(CGSize)size;

@end

/*
#pragma mark - Masonry

@interface MASConstraint (BJL_M9Dev)

- (MASConstraint *(^)(CGFloat))bjl_inset;

@end */
