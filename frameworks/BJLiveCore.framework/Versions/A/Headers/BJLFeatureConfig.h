//
//  BJLFeatureConfig.h
//  BJLiveCore
//
//  Created by 杨磊 on 16/7/18.
//  Copyright © 2016 BaijiaYun. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "BJLConstants.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, BJLPointsCompressType) {
    BJLPointsCompressTypeNone           = 0,
    BJLPointsCompressTypeCustomized     = 1,
    BJLPointsCompressTypeCustomizedV2   = 2
};

@interface BJLFeatureConfig : NSObject <NSCopying, NSCoding>

// 禁止举手
@property (nonatomic, readonly) BOOL disableSpeakingRequest;
@property (nonatomic, readonly, copy, nullable) NSString *disableSpeakingRequestReason;
// 举手通过后自动打开摄像头
@property (nonatomic, readonly) BOOL autoPublishVideoStudent;

// 分享
@property (nonatomic, readonly) BOOL enableShare;

#pragma mark - from class_data

@property (nonatomic, readonly) BJLMediaLimit mediaLimit;
@property (nonatomic, readonly) BOOL autoStartServerRecording;

#pragma mark - from partner_config

// 隐藏技术支持消息
@property (nonatomic, readonly) BOOL hideSupportMessage;
// 隐藏用户列表
@property (nonatomic, readonly) BOOL hideUserList;
// 禁用 H5 实现的 PPT 动画
@property (nonatomic, readonly) BOOL disablePPTAnimation;
// 支持私聊
@property (nonatomic, readonly) BOOL enableWhisper;
// 举手超时时间
@property (nonatomic, readonly) NSTimeInterval speakingRequestTimeoutInterval;
// 最大发言用户数
@property (nonatomic, readonly) NSInteger maxSpeakerCount;

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
