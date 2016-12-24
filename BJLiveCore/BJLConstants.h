//
//  BJLConstants.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-11-26.
//
//

#import <Foundation/Foundation.h>

#import "NSError+BJLError.h"

NS_ASSUME_NONNULL_BEGIN

/** 毫秒 */

typedef long BJLMilliseconds;

#define BJL_MSEC_PER_SEC            1000ull
#define BJLMillisecondsSince1970    BJLMillisecondsFromTimeInterval(NSTimeIntervalSince1970)

NS_INLINE BJLMilliseconds BJLMillisecondsFromTimeInterval(NSTimeInterval timeInterval) {
    return (BJLMilliseconds)(timeInterval * BJL_MSEC_PER_SEC);
}

NS_INLINE NSTimeInterval BJLTimeIntervalFromMilliseconds(BJLMilliseconds milliseconds) {
    return (NSTimeInterval)milliseconds / BJL_MSEC_PER_SEC;
}

/** 部署环境 */
typedef NS_ENUM (NSInteger, BJLDeployType){
    /** 正式环境 */
    BJLDeployType_www,
    BJLDeployType_test,
    BJLDeployType_beta,
    _BJLDeployType_count
};

/** 用户角色 */
typedef NS_ENUM(NSInteger, BJLUserRole) {
    /** 学生 */
    BJLUserRole_student = 0,
    /** 老师 */
    BJLUserRole_teacher = 1,
    /** 助教 */
    BJLUserRole_assistant = 2,
    /** 游客 */
    BJLUserRole_guest = 3
};

/** 教室类型 */
typedef NS_ENUM(NSInteger, BJLRoomType) {
    /** 1 对 1 */
    BJLRoomType_1to1 = 1,
    /** 多人班课 */
    BJLRoomType_1toN = 2
};

/** 媒体类型限制 */
typedef NS_ENUM(NSInteger, BJLMediaLimit) {
    /** 无限制 */
    BJLMediaLimit_none = 0,
    /** 只支持音频 */
    BJLMediaLimit_audioOnly = 1
};

/** 学生发言方式 */
typedef NS_ENUM(NSUInteger, BJLSpeakType) {
    /** 自由模式（一般在1对1模式下） */
    BJLSpeakType_free = 0,
    /** 限制模式。 默认值， 需要举手才能发言 */
    BJLSpeakType_limit = 1
};

/** 链路类型 */
typedef NS_ENUM(NSInteger, BJLLinkType) {
    /** TCP */
    BJLLinkType_TCP = 0,
    /** UDP */
    BJLLinkType_UDP = 1
};
NS_INLINE BOOL BJL_isValidLinkType(BJLLinkType linkType) {
    return linkType == BJLLinkType_TCP || linkType == BJLLinkType_UDP;
}

/** 视频清晰度 */
typedef NS_ENUM(NSInteger, BJLVideoDefinition) {
    /** 流畅 */
    BJLVideoDefinition_low,
    /** 高清 */
    BJLVideoDefinition_high,
    /** 默认 */
    BJLVideoDefinition_default = BJLVideoDefinition_low
};

/** 美颜 */
typedef NS_ENUM(NSInteger, BJLVideoBeautifyLevel) {
    BJLVideoBeautifyLevel0,
    BJLVideoBeautifyLevel1,
    BJLVideoBeautifyLevel2,
    BJLVideoBeautifyLevel3,
    BJLVideoBeautifyLevel4,
    BJLVideoBeautifyLevel5,
    /** 默认 */
    BJLVideoBeautifyLevel_default = BJLVideoBeautifyLevel0,
    /** 关闭 */
    BJLVideoBeautifyLevel_close = BJLVideoBeautifyLevel0,
    /** 最小 */
    BJLVideoBeautifyLevel_min = BJLVideoBeautifyLevel1,
    /** 最大 */
    BJLVideoBeautifyLevel_max = BJLVideoBeautifyLevel5
};

typedef NS_ENUM(NSInteger, BJLSlideshowContentMode) {
    BJLSlideshowContentMode_scaleAspectFit,
    BJLSlideshowContentMode_scaleAspectFill
};

/** 礼物类型 */
typedef NS_ENUM(NSInteger, BJLGiftType) {
    /** 可乐 */
    BJLGiftType_cola = 1,
    /** 咖啡 */
    BJLGiftType_coffee = 2,
    /** 橙汁 */
    BJLGiftType_orangeJuice = 3,
    /** 冰红茶 */
    BJLGiftType_tea = 4,
    /** 大麦茶 */
    BJLGiftType_barleyTea = 5
};

NS_ASSUME_NONNULL_END
