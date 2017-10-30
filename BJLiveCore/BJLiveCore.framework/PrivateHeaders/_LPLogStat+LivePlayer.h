//
//  _LPLogStat+LivePlayer.h
//  BJLiveCore
//
//  Created by Randy on 16/5/25.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "_LPLogStat.h"
#import "_LPLogConstants.h"

#import "_LPLogLinkInfo.h"
#import "_LPIpAddress.h"

NS_ASSUME_NONNULL_BEGIN

@interface _LPLogStat (LivePlayer)

// 记录时间、参数 ...
+ (void)eventOfStartEnterRoom;
+ (void)eventOfStartMasterServer:(_LPIpAddress *)server;
+ (void)eventOfEndMasterServer;
+ (void)eventOfStartRoomServer:(_LPIpAddress *)server;
+ (void)eventOfEndRoomServer;
+ (void)eventOfStartLoginRoom;
+ (void)eventOfEndLoginRoom;
+ (void)eventOfStartChatServer:(_LPIpAddress *)server;
+ (void)eventOfEndChatServer;
// 记录时间、参数 end

/**
 *  此方法失败的时候也需要调用
 */
+ (void)eventOfEndEnterRoom:(BOOL)hasError;

+ (void)eventOfLeaveRoom;
/**
 *  所有的链路信息
 *
 *  @param linkList 上下行的所有的链路
 */
+ (void)eventOfRoomHeartBeat:(NSArray<_LPLogLinkInfo *>*)linkList;

/**
 *  媒体服务器切换
 */
+ (void)eventOfMediaSwitchServer:(_LPLogLinkInfo *)link;
/**
 *  客户端上行、下行卡顿的时候调用
 *
 *  @param link 卡顿的链路
 */
+ (void)eventOfMediaBlockCount:(_LPLogLinkInfo *)link;
/**
 *  客户端掉线
 */
+ (void)eventOfRoomDisconnect:(_LPLogLinkInfo *)link;

/**
 *  老师端操作行为监控
 */
// + (void)eventOfClickWithOptType:(_LPLogClickOptType)type;

@end

NS_ASSUME_NONNULL_END
