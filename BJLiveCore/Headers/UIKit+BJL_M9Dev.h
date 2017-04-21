//
//  UIKit+BJL_M9Dev.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-04-21.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import <UIKit/UIKit.h>
// #import <Masonry/Masonry.h>

static inline UIEdgeInsets BJLEdgeInset(CGFloat inset) {
    return UIEdgeInsetsMake(inset, inset, inset, inset);
}

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

#pragma mark - AliIMG

/**
 Ali image aspect scale url params
 @param width   * scale <> 1-4096
 @param height  * scale <> 1-4096
 @param fill    fill, or fit
 @param ext     ext
 @return        url params
 e.g.
 http://image-demo.img-cn-hangzhou.aliyuncs.com/example.jpg@100h_100w_0c_1e_1l_2o_2x.jpg - fill > 300*200
 http://image-demo.img-cn-hangzhou.aliyuncs.com/example.jpg@100h_100w_0c_0e_1l_2o_2x.jpg - fit  > 200*134
 @see
 https://help.aliyun.com/document_detail/32223.html?spm=5176.doc32228.6.969.IvVprX
 https://help.aliyun.com/document_detail/32231.html?spm=5176.doc32223.6.977.fTzBHO
 https://help.aliyun.com/document_detail/32244.html?spm=5176.doc32223.2.2.fTzBHO
 */

NS_INLINE NSString *BJLAliIMGURLParams_aspectScale(BOOL fill, NSInteger width, NSInteger height, NSString * _Nullable ext) {
    static const NSInteger limit = 4096;
    NSInteger scale = round([UIScreen mainScreen].scale);
    NSInteger max = MAX(width, height) * scale;
    if (max > limit) {
        CGFloat limitScale = (CGFloat)limit / max;
        width = floor(width * limitScale);
        height = floor(height * limitScale);
    }
    width = MAX(1, width);
    height = MAX(1, height);
    NSString *params = [NSString stringWithFormat:@"@%tdw_%tdh_%tdx_0c_%de_1l_2o",
                        width, height, scale, fill];
    return ext.length ? [params stringByAppendingPathExtension:ext] : params;
}

NS_INLINE NSString *BJLAliIMGURLString_aspectScale(BOOL fill, NSInteger width, NSInteger height, NSString *urlString) {
    NSUInteger atLocation = [urlString rangeOfString:@"@"].location;
    if (atLocation != NSNotFound) {
        urlString = [urlString substringToIndex:atLocation];
    }
    NSString *params = BJLAliIMGURLParams_aspectScale(fill, width, height, [urlString pathExtension]);
    return urlString.length ? [urlString stringByAppendingString:params] : params;
}

NS_INLINE NSString *BJLAliIMG_aspectFill(CGSize size, NSString *urlString) {
    return BJLAliIMGURLString_aspectScale(YES, ceil(size.width), ceil(size.height), urlString);
}

NS_INLINE NSString *BJLAliIMG_aspectFit(CGSize size, NSString *urlString) {
    return BJLAliIMGURLString_aspectScale(NO, ceil(size.width), ceil(size.height), urlString);
}
