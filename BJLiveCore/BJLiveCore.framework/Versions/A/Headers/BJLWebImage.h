//
//  BJLWebImage.h
//  BJLiveCore
//
//  Created by MingLQ on 2017-03-31.
//  Copyright © 2017 Baijia Cloud. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

typedef void (^BJLWebImageCompletionBlock)(UIImage * _Nullable image, NSError * _Nullable error, NSURL * _Nullable imageURL);

#pragma mark -

@interface UIImageView (BJLWebImage)

@property (nonatomic, readonly, nullable) NSURL *bjl_imageURL;

- (void)bjl_setImageWithURL:(nullable NSURL *)url;
- (void)bjl_setImageWithURL:(nullable NSURL *)url
                placeholder:(nullable UIImage *)placeholder
                 completion:(nullable BJLWebImageCompletionBlock)completion;
- (void)bjl_cancelCurrentImageLoading;

@end

#pragma mark -

@interface UIButton (BJLWebImage)

- (nullable NSURL *)bjl_imageURLForState:(UIControlState)state;

- (void)bjl_setImageWithURL:(nullable NSURL *)url forState:(UIControlState)state;
- (void)bjl_setImageWithURL:(nullable NSURL *)url
                   forState:(UIControlState)state
                placeholder:(nullable UIImage *)placeholder
                 completion:(nullable BJLWebImageCompletionBlock)completion;
- (void)bjl_cancelCurrentImageLoadingForState:(UIControlState)state;

- (nullable NSURL *)bjl_backgroundImageURLForState:(UIControlState)state;

- (void)bjl_setBackgroundImageWithURL:(nullable NSURL *)url forState:(UIControlState)state;
- (void)bjl_setBackgroundImageWithURL:(nullable NSURL *)url
                             forState:(UIControlState)state
                          placeholder:(nullable UIImage *)placeholder
                           completion:(nullable BJLWebImageCompletionBlock)completion;
- (void)bjl_cancelCurrentBackgroundImageLoadingForState:(UIControlState)state;

@end

NS_ASSUME_NONNULL_END
