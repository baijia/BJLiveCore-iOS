//
//  _LPConstants.h
//  BJLiveCore
//
//  Created by 杨磊 on 16/3/28.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#ifndef _LPConstants_h
#define _LPConstants_h

#define _LP_USER_MORE_PAGE_COUNT 30

#import "_LPLivePlayerConstants.h"

/**
 *  终端类型
 */
typedef NS_ENUM(NSUInteger, _LPEndType) {
    /**
     *  PC 网页
     */
    _LPEndType_pc_html = BJLClient_PCWeb,
    /**
     * PC 客户端
     */
    _LPEndType_pc_client = BJLClient_PCApp,
    /**
     *  M 站
     */
    _LPEndType_pc_h5 = BJLClient_MobileWeb,
    /**
     *  iOS 客户端
     */
    _LPEndType_ios = BJLClient_iOSApp,
    /**
     *  Android 客户端
     */
    _LPEndType_android = BJLClient_AndroidApp
};

/**
 *  学生发言模式
 */
typedef NS_ENUM(NSUInteger, _LPSpeakState) {
    /**
     *  自由模式（一般在1对1模式下）
     */
    _LPSpeakState_free = BJLSpeakType_free,
    /**
     *  限制模式。 默认值， 需要举手才能发言
     */
    _LPSpeakState_limit = BJLSpeakType_limit
};

/**
 *  学生举手状态
 */
typedef NS_ENUM(NSUInteger, _LPSpeakingState) {
    _LPSpeakingState_normal = 0, // 未举手，默认
    _LPSpeakingState_waiting = 1, // 举手中
    _LPSpeakingState_speaking = 2 // 发言中
};

/**
 *  用户状态
 */
typedef NS_ENUM(NSUInteger, _LPUserOnlineStatus) {
    /**
     *  在线
     */
    _LPUserOnlineStatus_visible = 0,
    /**
     *  隐身
     */
    _LPUserOnlineStatus_invisible = 1,
    /**
     *  离线（SDK 处理的。 收到 userOut 即为离线）
     */
    _LPUserOnlineStatus_offline = 2
};

/**
 *  分辨率
 *  本地定义，取值为数组坐标，因此必须从 0 开始、不能间断、不能超出数组范围
 */
typedef NS_ENUM(NSInteger, _LPVideoCaptureCapability) {
    _LPVideoCaptureCapability_low = BJLVideoDefinition_low,
    _LPVideoCaptureCapability_high = BJLVideoDefinition_high
};

/**
 *  连接类型
 */
typedef NS_ENUM(NSInteger, _LPLinkType) {
    /**
     *  TCP
     */
    _LPLinkType_TCP = BJLLinkType_TCP,
    /**
     *  UDP
     */
    _LPLinkType_UDP = BJLLinkType_UDP
};
static inline BOOL _LP_isValidLinkType(_LPLinkType linkType) {
    return linkType == _LPLinkType_TCP || linkType == _LPLinkType_UDP;
}

/**
 *  CDN 类型
 */
typedef NS_ENUM(NSInteger, _LPCDNType) {
    /**
     *  帝联
     */
    _LPCDNType_DL = 0,
    /**
     *  网宿
     */
    _LPCDNType_WS = 1,
    /**
     *  腾讯
     */
    // _LPCDNType_TX = 2,
    /**
     *  蓝汛
     */
    _LPCDNType_LX = 3
};
static inline NSString *_LPCDNName(_LPCDNType cdnType) {
    switch (cdnType) {
        case _LPCDNType_DL:
            return @"dl";
        case _LPCDNType_WS:
            return @"ws";
        case _LPCDNType_LX:
            return @"lx";
        default:
            return nil;
    }
}

typedef NS_ENUM(NSInteger, _LPPPTMode) {
    _LPPPTMode_fit = BJLSlideshowContentMode_scaleAspectFit,
    _LPPPTMode_fill = BJLSlideshowContentMode_scaleAspectFill
};

#endif /* _LPConstants_h */
