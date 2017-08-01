//
//  BJLConstants.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-11-26.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/** 毫秒 */

typedef long long BJLMilliseconds;

#define BJL_MSEC_PER_SEC            1000ull
#define BJLMillisecondsSince1970    BJLMillisecondsFromTimeInterval(NSTimeIntervalSince1970)

static inline BJLMilliseconds BJLMillisecondsFromTimeInterval(NSTimeInterval timeInterval) {
    return (BJLMilliseconds)(timeInterval * BJL_MSEC_PER_SEC);
}

static inline NSTimeInterval BJLTimeIntervalFromMilliseconds(BJLMilliseconds milliseconds) {
    return (NSTimeInterval)milliseconds / BJL_MSEC_PER_SEC;
}

/** WebSocket 请求超时时间 */
extern const NSTimeInterval BJLWebSocketTimeoutInterval;

/** 部署环境 */
typedef NS_ENUM(NSInteger, BJLDeployType){
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
    BJLUserRole_guest = 3 // 内部使用
};

/** 教室类型 */
typedef NS_ENUM(NSInteger, BJLRoomType) {
    /** 1 对 1 */
    BJLRoomType_1to1 = 1,
    /** 小班课 */
    BJLRoomType_1toM = 3,
    /** 大班课 */
    BJLRoomType_1toN = 2
    // 小班课是 2、大班课是 3，没错
};

/** 客户端类型 */
typedef NS_ENUM(NSUInteger, BJLClientType) {
    /** PC 网页 */
    BJLClientType_PCWeb = 0,
    /** PC 客户端 */
    BJLClientType_PCApp = 1,
    /** M 站 */
    BJLClientType_MobileWeb = 2,
    /** iOS 客户端 */
    BJLClientType_iOSApp = 3,
    /** Android 客户端 */
    BJLClientType_AndroidApp = 4
};

/** 在线状态 */
typedef NS_ENUM(NSInteger, BJLOnlineState) {
    /** 在线 */
    BJLOnlineState_visible = 0,
    /** 隐身 */
    BJLOnlineState_invisible = 1,
    /** 离线 */
    BJLOnlineState_offline = 2 
};

/** 媒体类型限制 */
typedef NS_ENUM(NSInteger, BJLMediaLimit) {
    /** 无限制 */
    BJLMediaLimit_none = 0,
    /** 只支持音频 */
    BJLMediaLimit_audioOnly = 1
};

/** 链路类型 */
typedef NS_ENUM(NSInteger, BJLLinkType) {
    /** TCP */
    BJLLinkType_TCP = 0,
    /** UDP */
    BJLLinkType_UDP = 1
};
static inline BOOL BJL_isValidLinkType(BJLLinkType linkType) {
    return linkType == BJLLinkType_TCP || linkType == BJLLinkType_UDP;
}

/** 视频方向 */
typedef NS_ENUM(NSInteger, BJLVideoOrientation) {
    /** 自动 - 使用设备方向 */
    BJLVideoOrientation_auto,
    /** 纵向 */
    BJLVideoOrientation_portrait,
    /** 横向 */
    BJLVideoOrientation_landscape
};

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
    BJLVideoBeautifyLevel_0,
    BJLVideoBeautifyLevel_1,
    BJLVideoBeautifyLevel_2,
    BJLVideoBeautifyLevel_3,
    BJLVideoBeautifyLevel_4,
    BJLVideoBeautifyLevel_5,
    BJLVideoBeautifyLevel_off = BJLVideoBeautifyLevel_0,
    BJLVideoBeautifyLevel_on  = BJLVideoBeautifyLevel_5,
    BJLVideoBeautifyLevel_default = BJLVideoBeautifyLevel_off,
    BJLVideoBeautifyLevel0 DEPRECATED_ATTRIBUTE = BJLVideoBeautifyLevel_0,
    BJLVideoBeautifyLevel1 DEPRECATED_ATTRIBUTE = BJLVideoBeautifyLevel_1,
    BJLVideoBeautifyLevel2 DEPRECATED_ATTRIBUTE = BJLVideoBeautifyLevel_2,
    BJLVideoBeautifyLevel3 DEPRECATED_ATTRIBUTE = BJLVideoBeautifyLevel_3,
    BJLVideoBeautifyLevel4 DEPRECATED_ATTRIBUTE = BJLVideoBeautifyLevel_4,
    BJLVideoBeautifyLevel5 DEPRECATED_ATTRIBUTE = BJLVideoBeautifyLevel_5,
    BJLVideoBeautifyLevel_close DEPRECATED_ATTRIBUTE = BJLVideoBeautifyLevel_off,
    BJLVideoBeautifyLevel_min DEPRECATED_ATTRIBUTE = BJLVideoBeautifyLevel_1,
    BJLVideoBeautifyLevel_max DEPRECATED_ATTRIBUTE = BJLVideoBeautifyLevel_5
};

/** 课件显示模式 */
typedef NS_ENUM(NSInteger, BJLContentMode) {
    /** 完整 */
    BJLContentMode_scaleAspectFit,
    /** 铺满 */
    BJLContentMode_scaleAspectFill,
    /** 拉伸 */
    BJLContentMode_scaleToFill
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

typedef NS_ENUM(NSInteger, BJLTextMaxLength) {
    BJLTextMaxLength_chat = 140,
    BJLTextMaxLength_notice = 140
};

NS_ASSUME_NONNULL_END
