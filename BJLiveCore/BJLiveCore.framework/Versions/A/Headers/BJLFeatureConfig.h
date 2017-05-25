//
//  BJLFeatureConfig.h
//  BJLiveCore
//
//  Created by 杨磊 on 16/7/18.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <YYModel/YYModel.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, BJLPointsCompressType) {
    BJLPointsCompressTypeNone = 0,
    BJLPointsCompressTypeCustomized = 1
};

@interface BJLFeatureConfig : NSObject <YYModel, NSCopying, NSCoding>

// 云端录课
@property (nonatomic, readonly) BOOL enableRecordCourse;

// 禁止举手
@property (nonatomic, readonly) BOOL disableSpeakingRequest;
@property (nonatomic, readonly, copy, nullable) NSString *disableSpeakingRequestReason;

// 自动打开视频
@property (nonatomic, readonly) BOOL enableVideoOn;

// 分享
@property (nonatomic, readonly) BOOL enableShare;

#pragma mark - internal

/**
 *  <画笔状态下两指滑动、翻页>
 *  画笔模式下支持两指手势 滑动 和 翻页，目前服务端不设置此参数，默认开启 - 非 disable 状态
 *  因为实现此功能时使用了非常规手段，万一日后 iOS 升级导致此功能引发其它问题，可通过此预留开关停掉该功能
 */
@property (nonatomic, readonly) BOOL disableTwoFingersGesture;

// 画笔压缩类型
@property (nonatomic, readonly) BJLPointsCompressType compressType;

@end

NS_ASSUME_NONNULL_END
