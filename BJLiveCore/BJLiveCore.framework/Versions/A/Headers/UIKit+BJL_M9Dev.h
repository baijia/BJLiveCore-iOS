//
//  UIKit+BJL_M9Dev.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-04-21.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

#define BJLOnePixel ({ \
    static CGFloat _BJLOnePixel; \
    static dispatch_once_t onceToken; \
    dispatch_once(&onceToken, ^{ \
        _BJLOnePixel = 1.0 / [UIScreen mainScreen].scale; \
    }); \
    _BJLOnePixel; \
})

extern const UIPopoverArrowDirection UIPopoverArrowDirectionVertical;

static inline CGFloat BJLFloorWithScreenScale(CGFloat size) {
    CGFloat scale = [UIScreen mainScreen].scale;
    return floor(size * scale) / scale;
}

static inline CGFloat BJLCeilWithScreenScale(CGFloat size) {
    CGFloat scale = [UIScreen mainScreen].scale;
    return ceil(size * scale) / scale;
}

static inline CGSize BJLAspectFillSize(CGSize size, CGFloat aspectRatio) {
    return CGSizeMake(MAX(size.width, BJLCeilWithScreenScale(size.height * aspectRatio)),
                      MAX(size.height, BJLCeilWithScreenScale(size.width / aspectRatio)));
}
static inline CGSize BJLAspectFitSize(CGSize size, CGFloat aspectRatio) {
    return CGSizeMake(MIN(size.width, BJLCeilWithScreenScale(size.height * aspectRatio)),
                      MIN(size.height, BJLCeilWithScreenScale(size.width / aspectRatio)));
}

static inline CGRect BJLAspectFillFrame(CGRect frame, CGFloat aspectRatio) {
    CGSize size = BJLAspectFillSize(frame.size, aspectRatio);
    return CGRectMake(MIN(0.0, BJLFloorWithScreenScale((CGRectGetWidth(frame) - size.width) / 2)),
                      MIN(0.0, BJLFloorWithScreenScale((CGRectGetHeight(frame) - size.height) / 2)),
                      size.width,
                      size.height);
}
static inline CGRect BJLAspectFitFrame(CGRect frame, CGFloat aspectRatio) {
    CGSize size = BJLAspectFitSize(frame.size, aspectRatio);
    return CGRectMake(MAX(0.0, BJLFloorWithScreenScale((CGRectGetWidth(frame) - size.width) / 2)),
                      MAX(0.0, BJLFloorWithScreenScale((CGRectGetHeight(frame) - size.height) / 2)),
                      size.width,
                      size.height);
}

static inline CGSize BJLImageViewSize(CGSize imgSize, CGSize minSize, CGSize maxSize) {
    CGFloat minScale = MAX(imgSize.width / maxSize.width, imgSize.height / maxSize.height);
    CGFloat maxScale = MIN(imgSize.width / minSize.width, imgSize.height / minSize.height);
    CGFloat scale = MIN(MAX(minScale, 1.0), maxScale); // 等比显示、最少缩放
    return CGSizeMake(MIN(imgSize.width / scale, maxSize.width),
                      MIN(imgSize.height / scale, maxSize.height)); // 超出部分裁切
}

#pragma mark -

@interface UIResponder (BJL_M9Dev)

- (nullable UIResponder *)bjl_closestResponderOfClass:(Class)clazz; // NOT include self
- (nullable UIResponder *)bjl_closestResponderOfClass:(Class)clazz includeSelf:(BOOL)includeSelf;
- (nullable UIResponder *)bjl_findResponderWithBlock:(BOOL (^)(UIResponder *responder, BOOL *stop))enumerateBlock;

@end

#pragma mark -

@interface UIView (BJL_M9Dev)

- (nullable __kindof UIView *)bjl_closestViewOfClass:(Class)clazz; // NOT include self
- (nullable __kindof UIView *)bjl_closestViewOfClass:(Class)clazz includeSelf:(BOOL)includeSelf; // up to UIViewController
- (nullable __kindof UIView *)bjl_closestViewOfClass:(Class)clazz includeSelf:(BOOL)includeSelf upToResponder:(nullable UIResponder *)upToResponder; // NOT include the upToResponder, nil - up to UIViewController
- (nullable __kindof UIViewController *)bjl_closestViewController;

- (void)bjl_removeAllConstraints;

@end

#pragma mark -

@interface UIViewController (BJL_M9Dev)

- (void)bjl_addChildViewController:(UIViewController *)childViewController;
- (void)bjl_addChildViewController:(UIViewController *)childViewController superview:(UIView *)superview;
- (void)bjl_addChildViewController:(UIViewController *)childViewController superview:(UIView *)superview atIndex:(NSInteger)index;
- (void)bjl_addChildViewController:(UIViewController *)childViewController superview:(UIView *)superview belowSubview:(UIView *)siblingSubview;
- (void)bjl_addChildViewController:(UIViewController *)childViewController superview:(UIView *)superview aboveSubview:(UIView *)siblingSubview;
- (void)bjl_addChildViewController:(UIViewController *)childViewController addSubview:(void (^)(UIView *parentView, UIView *childView))addSubview; // synchronous
- (void)bjl_removeFromParentViewControllerAndSuperiew;

/**
 *  differences from dismissViewControllerAnimated:completion:
 *  1. always call completion although nothing to dismiss
 *  2. only dismiss self, but not parentViewController
 */
- (void)bjl_dismissAnimated:(BOOL)animated completion:(void (^ _Nullable)(void))completion;
/**
 *  differences from dismissViewControllerAnimated:completion:
 *  1. always call completion although nothing to dismiss
 *  2. only dismiss presentedViewController, but not self
 */
- (void)bjl_dismissPresentedViewControllerAnimated:(BOOL)animated completion:(void (^ _Nullable)(void))completion;
+ (nullable UIViewController *)bjl_gotoRootViewControllerAnimated:(BOOL)animated completion:(void (^ _Nullable)(void))completion DEPRECATED_MSG_ATTRIBUTE("should be implemented by apps");

+ (nullable UIViewController *)bjl_rootViewController;
+ (nullable UIViewController *)bjl_topViewController;

@end

#pragma mark -

@interface UINavigationController (BJL_M9Dev)

@property(nonatomic, strong, readonly, nullable) UIViewController *bjl_rootViewController;

- (void)bjl_pushViewController:(UIViewController *)viewController
                      animated:(BOOL)animated
                    completion:(void (^ _Nullable)(void))completion;

- (nullable UIViewController *)bjl_popViewControllerAnimated:(BOOL)animated
                                                  completion:(void (^ _Nullable)(void))completion;
- (nullable NSArray *)bjl_popToViewController:(UIViewController *)viewController
                                     animated:(BOOL)animated
                                   completion:(void (^ _Nullable)(void))completion;
- (nullable NSArray *)bjl_popToRootViewControllerAnimated:(BOOL)animated
                                               completion:(void (^ _Nullable)(void))completion;

@end

#pragma mark -

@interface UIColor (BJL_M9Dev)

// @"#FFFFFF"
+ (nullable UIColor *)bjl_colorWithHexString:(NSString *)hexString;
+ (nullable UIColor *)bjl_colorWithHexString:(NSString *)hexString alpha:(CGFloat)alpha;
// 0xFFFFFF
+ (nullable UIColor *)bjl_colorWithHex:(unsigned)hex;
+ (nullable UIColor *)bjl_colorWithHex:(unsigned)hex alpha:(CGFloat)alpha;

@end

#pragma mark -

@interface UIImage (BJL_M9Dev)

- (UIImage *)bjl_resizableImage;

/**
 @return UIImage with the scale factor of the device’s main screen
 */
- (UIImage *)bjl_imageFillSize:(CGSize)size; // enlarge: NO
- (UIImage *)bjl_imageFillSize:(CGSize)size enlarge:(BOOL)enlarge; // aspect fill & cropped

/**
 @return UIImage with the scale factor of the device’s main screen
 */
+ (nullable UIImage *)bjl_imageWithColor:(UIColor *)color;
+ (nullable UIImage *)bjl_imageWithColor:(UIColor *)color size:(CGSize)size;

@end

#pragma mark - AliIMG

/**
 Ali image aspect scale url params
 @param fill    fill, or fit
 @param width   * scale <> 1-4096
 @param height  * scale <> 1-4096
 @param scale   0 - mainScreen.scale
 @param ext     jpg, png, webp, bmp, gif, src
 @return        url params
 e.g.
 http://image-demo.img-cn-hangzhou.aliyuncs.com/example.jpg@100h_100w_0c_1e_1l_2o_2x.jpg - fill > 300*200
 http://image-demo.img-cn-hangzhou.aliyuncs.com/example.jpg@100h_100w_0c_0e_1l_2o_2x.jpg - fit  > 200*134
 @see
 whcel: https://help.aliyun.com/document_detail/32223.html?spm=5176.doc32228.6.969.IvVprX
 o:     https://help.aliyun.com/document_detail/32231.html?spm=5176.doc32223.6.977.fTzBHO
 ext:   https://help.aliyun.com/document_detail/32244.html?spm=5176.doc32223.2.2.fTzBHO
 */

static inline NSString *BJLAliIMGURLParams_aspectScale(BOOL fill, NSInteger width, NSInteger height, NSInteger scale, NSString * _Nullable ext) {
    static const NSInteger aliIMGMaxSize = 4096;
    scale = MAX(1.0, scale <= 0 ? round([UIScreen mainScreen].scale) : scale);
    NSInteger max = MAX(width, height) * scale;
    if (max > aliIMGMaxSize) {
        CGFloat maxScale = (CGFloat)aliIMGMaxSize / max;
        width = floor(width * maxScale);
        height = floor(height * maxScale);
    }
    width = MAX(1.0, width);
    height = MAX(1.0, height);
    // w: width, h: height, x: scale, c: 0 - no cut, e: 0 - fit, 1 - fill, l: 1 - no enlarge, o: 2 - routate then resize
    NSString *params = [NSString stringWithFormat:@"@%tdw_%tdh_%tdx_0c_%de_1l_2o",
                        width, height, scale, fill];
    return ext.length ? [params stringByAppendingPathExtension:ext] : params;
}

static inline NSString *BJLAliIMGURLString_aspectScale(BOOL fill, NSInteger width, NSInteger height, NSInteger scale, NSString *urlString, NSString * _Nullable ext) {
    NSUInteger atLocation = [urlString rangeOfString:@"@"].location;
    if (atLocation != NSNotFound) {
        urlString = [urlString substringToIndex:atLocation];
    }
    NSString *params = BJLAliIMGURLParams_aspectScale(fill, width, height, scale, ext ?: [urlString pathExtension]);
    return urlString.length ? [urlString stringByAppendingString:params] : params;
}

static inline NSString *BJLAliIMG_aspectFill(CGSize size, CGFloat scale, NSString *urlString, NSString * _Nullable ext) {
    return BJLAliIMGURLString_aspectScale(YES, round(size.width), round(size.height), scale, urlString, ext);
}

static inline NSString *BJLAliIMG_aspectFit(CGSize size, CGFloat scale, NSString *urlString, NSString * _Nullable ext) {
    return BJLAliIMGURLString_aspectScale(NO, round(size.width), round(size.height), scale, urlString, ext);
}

NS_ASSUME_NONNULL_END
