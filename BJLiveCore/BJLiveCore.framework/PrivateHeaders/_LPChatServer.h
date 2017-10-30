//
//  _LPChatServer.h
//  BJLiveCore
//
//  Created by 杨磊 on 16/3/25.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "_LPWSServerBase.h"

@class _LPUser, RACSignal;

/**
 *  Chat Server
 */
@interface _LPChatServer : _LPWSServerBase

// 预先设置登录信息、在连接成功后发送
- (void)loginWithRoomId:(NSString *)roomId
                   user:(_LPUser *)user;

/**
 *  登录返回
 *
 *  @return _LPChatServerLogin
 */
- (RACSignal *)signalOfLogin;

/**
 *  发送消息
 *      _LPMessageSend
 */
- (void)requestMessageSend:(NSString *)content
                   channel:(NSString *)channel
                      from:(_LPUser *)user;
/**
 *  接收消息
 *      _LPMessage
 */
- (RACSignal *)signalOfMessageReceive;

@end
