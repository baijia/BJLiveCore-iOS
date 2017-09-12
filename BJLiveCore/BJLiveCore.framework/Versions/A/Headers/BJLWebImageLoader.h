//
//  BJLWebImageLoader.h
//  Pods
//
//  Created by MingLQ on 2017-08-15.
//  Copyright © 2017 Baijia Cloud. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "BJLWebImage.h"

NS_ASSUME_NONNULL_BEGIN

@interface UIImageView (_BJLWebImage)

- (nullable NSURL *)bjl_currentImageURL;
- (void)bjl_setCurrentImageURL:(nullable NSURL *)url;

@end

@interface UIButton (_BJLWebImage)

- (nullable NSURL *)bjl_currentImageURLForState:(UIControlState)state;
- (void)bjl_setCurrentImageURL:(nullable NSURL *)url forState:(UIControlState)state;

- (nullable NSURL *)bjl_currentBackgroundImageURLForState:(UIControlState)state;
- (void)bjl_setCurrentBackgroundImageURL:(nullable NSURL *)url forState:(UIControlState)state;

@end

#pragma mark -

/**
 load image if failed and continue in background, DONOT avoid auto set image:
 AFNetworking: MUST set image when has completion
 SDWebImage: SDWebImageRetryFailed | SDWebImageContinueInBackground // NO SDWebImageAvoidAutoSetImage
 YYWebImage: YYWebImageOptionIgnoreFailedURL | YYWebImageOptionAllowBackgroundTask // NO YYWebImageOptionAvoidSetImage
 */
@protocol BJLWebImageLoader <NSObject>

- (BOOL)supportsWebP;

/* UIImageView */

- (nullable NSURL *)bjl_imageURLForImageView:(UIImageView *)imageView;

- (void)bjl_setImageWithURL:(nullable NSURL *)url
                placeholder:(nullable UIImage *)placeholder
                 completion:(nullable BJLWebImageCompletionBlock)completion
                  imageView:(UIImageView *)imageView;
- (void)bjl_cancelCurrentImageLoadingForImageView:(UIImageView *)imageView;

/* UIButton */

- (nullable NSURL *)bjl_imageURLForState:(UIControlState)state button:(UIButton *)button;
- (nullable NSURL *)bjl_backgroundImageURLForState:(UIControlState)state button:(UIButton *)button;

- (void)bjl_setImageWithURL:(nullable NSURL *)url
                   forState:(UIControlState)state
                placeholder:(nullable UIImage *)placeholder
                 completion:(nullable BJLWebImageCompletionBlock)completion
                     button:(UIButton *)button;
- (void)bjl_cancelCurrentImageLoadingForState:(UIControlState)state button:(UIButton *)button;

- (void)bjl_setBackgroundImageWithURL:(nullable NSURL *)url
                             forState:(UIControlState)state
                          placeholder:(nullable UIImage *)placeholder
                           completion:(nullable BJLWebImageCompletionBlock)completion
                               button:(UIButton *)button;
- (void)bjl_cancelCurrentBackgroundImageLoadingForState:(UIControlState)state button:(UIButton *)button;

/* download */

/*
 [SDWebImageManager.sharedManager loadImageWithURL:options:progress:completed:]
 */

/*
 YYWebImageManager *manager = [YYWebImageManager sharedManager];
 imageFromMemory = [manager.cache getImageForKey:[manager cacheKeyForURL:imageURL] withType:YYImageCacheTypeMemory];
 [manager requestImageWithURL:options:progress:transform:completion:] // also load image form disk cache
 */

/*
 [AFImageDownloader sharedImageDownloader]
 
 id <AFImageRequestCache> imageCache = downloader.imageCache;
 UIImage *cachedImage = [imageCache imageforRequest:urlRequest withAdditionalIdentifier:nil];
 
 NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:url];
 [request addValue:@"image/<#*#>" forHTTPHeaderField:@"Accept"]; // TODO: replace <#*#> with *
 AFImageDownloadReceipt *receipt = [downloader downloadImageForURLRequest:request withReceiptID:[NSUUID UUID] success: failure:];
 */

@end

#pragma mark -

@interface UIView (BJLWebImage)

/**
 pod 'BJLiveCore/SDWebImage' or 'BJLiveCore/YYWebImage' to use SDWebImage or YYWebImage
 pod 'SDWebImage/WebP' or 'YYImage/WebP' to use WebP
 BJLWebImageLoader_YY > BJLWebImageLoader_SD > BJLWebImageLoader_AF, set nil to reset
 */
@property (class,
           nonatomic,
           null_resettable,
           setter=bjl_setImageLoader:) id<BJLWebImageLoader> bjl_imageLoader;

@end

NS_ASSUME_NONNULL_END
