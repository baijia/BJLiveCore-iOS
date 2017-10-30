//
//  _LPRoomServer+LPUser.h
//  BJLiveCore
//
//  Created by Randy on 16/3/30.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "_LPRoomServer.h"

/**
 *  用户相关信令服务
 */

@interface _LPRoomServer (_LPUser)

/**
 *  请求当前活跃用户: 老师(没发言也在)、管理员(没发言也在)、发言用户
 */
- (void)requestUserActives;
/**
 *  _LPResRoomActiveUserList
 *
 *  @return
 */
- (RACSignal *)signalOfUserActives;

/**
 *  请求用户的状态：禁言状态
 *
 *  @param number 用户number
 */
- (void)requestUserStateWithUserNumber:(NSString *)number;
/**
 *  _LPResRoomUserState
 *
 *  @return
 */
- (RACSignal *)signalOfUserState;

/**
 *  请求更多用户
 *
 *  @param count 请求数量
 *  @param cursor 客户端记录最近一次 userMore 里最后一个 userId 当作 cursor、第一页传 @"0"、默认传 @"0"
 */
- (void)requestUserMoreWithCount:(NSInteger)count cursor:(NSString *)cursor;
// 使用服务端记录的 cursor
- (void)requestUserMoreWithCount:(NSInteger)count;
/**
 *  _LPResRoomUserList
 *
 *  @return
 */
- (RACSignal *)signalOfUserMore;

/**
 *  _LPResRoomUserIn
 *
 *  @return
 */
- (RACSignal *)signalOfUserIn;
/**
 *  _LPResRoomUserOut
 *
 *  @return
 */
- (RACSignal *)signalOfUserOut;
/**
 *  _LPResRoomUserCountChange
 *
 *  隔几秒返回一次，如果count没变化也会返回
 *  @return
 */
- (RACSignal *)signalOfUserCountChange;

/**
 *  紧急呼叫
 */
- (void)requestUserCallServiceWithNumber:(NSString *)number userNumber:(NSString *)userNumber;
/**
 *  _LPResRoomCallService
 *
 *  @return
 */
- (RACSignal *)signalOfUserCallService;

@end
