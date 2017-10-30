//
//  _LPRoomServer+LPGift.h
//  BJLiveCore
//
//  Created by Randy on 16/3/30.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "_LPRoomServer.h"

@class _LPGiftModel;

/**
 *  礼物相关信令服务
 */

@interface _LPRoomServer (_LPGift)

/**
 *  请求当前课的打赏记录
 */
- (void)requestGiftMyHistory;
/**
 *  _LPResRoomGiftHistory
 *
 *  @return
 */
- (RACSignal *)signalOfGiftMyHistory;

/**
 *  _LPResRoomGiftReceive
 *
 *  @return
 */
- (RACSignal *)signalOfGiftReceive;

/**
 *  给老师打赏
 */
- (void)requestGiftSend:(_LPGiftModel *)gift from:(_LPUser *)user to:(_LPUser *)teacher;

@end
