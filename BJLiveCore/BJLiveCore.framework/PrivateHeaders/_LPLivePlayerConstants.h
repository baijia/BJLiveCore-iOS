//
//  _LPLivePlayerConstants.h
//  BJLiveCore
//
//  Created by Randy on 16/5/17.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "BJLConstants.h"

#ifndef _LPLivePlayerConstants_h
#define _LPLivePlayerConstants_h

/**
 *  教室类型
 */
typedef NS_ENUM(NSUInteger, _LPClassType) {
    /**
     *  1 对 1
     */
    _LPClassType_1to1 = BJLRoomType_1to1,
    /**
     *  多人班课
     */
    _LPClassType_1toN = BJLRoomType_1toN
};

typedef NS_ENUM(NSUInteger, _LPMediaType) {
    /**
     *  无限制
     */
    _LPMediaType_default = BJLMediaLimit_none,
    /**
     *  只支持音频
     */
    _LPMediaType_audioOnly = BJLMediaLimit_audioOnly
};

typedef NS_ENUM(NSUInteger, _LPSignUpReason) {
    _LPSignUpReason_raiseHand,   // 举手
    _LPSignUpReason_sendMessage, // 聊天
    _LPSignUpReason_evaluate,    // 评价
    _LPSignUpReason_sendGift,    // 打赏
    _LPSignUpReason_help         // 求助
};

/**
 *  打赏礼物类型
 */
typedef NS_ENUM(NSInteger, _LPGiftType) {
    /**
     *  可乐
     */
    _LPGiftType_cola = BJLGiftType_cola,
    /**
     *  咖啡
     */
    _LPGiftType_coffee = BJLGiftType_coffee,
    /**
     *  橙汁
     */
    _LPGiftType_orangeJuice = BJLGiftType_orangeJuice,
    /**
     *  冰红茶
     */
    _LPGiftType_tea = BJLGiftType_tea,
    /**
     *  大麦茶
     */
    _LPGiftType_barleyTea = BJLGiftType_barleyTea
};

#endif /* _LPLivePlayerConstants_h */
