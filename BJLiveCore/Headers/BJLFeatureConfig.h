//
//  BJLFeatureConfig.h
//  BJLiveCore
//
//  Created by 杨磊 on 16/7/18.
//
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
@property (nonatomic) BOOL enableRecordCourse;
// 打赏
@property (nonatomic) BOOL enableGift;
// 评论
@property (nonatomic) BOOL enableComment;

// 资料库
@property (nonatomic) BOOL enableDataWarehouse;

// 分享
@property (nonatomic) BOOL enableShare;
// 求助
@property (nonatomic) BOOL enableCallHelp;

// 自动打开视频
@property (nonatomic) BOOL enableVideoOn;

// 禁止举手
@property (nonatomic) BOOL disableSpeakingRequest;
@property (nonatomic, nullable, copy) NSString *disableSpeakingRequestReason;

/**
 *  <画笔状态下两指滑动、翻页>
 *  画笔模式下支持两指手势 滑动 和 翻页，目前服务端不设置此参数，默认开启 - 非 disable 状态
 *  因为实现此功能时使用了非常规手段，万一日后 iOS 升级导致此功能引发其它问题，可通过此预留开关停掉该功能
 */
@property (nonatomic) BOOL disableTwoFingersGesture;

#pragma mark - 以下配置不支持外部设置

// 画笔压缩类型
@property (nonatomic) BJLPointsCompressType compressType;

@end

NS_ASSUME_NONNULL_END
