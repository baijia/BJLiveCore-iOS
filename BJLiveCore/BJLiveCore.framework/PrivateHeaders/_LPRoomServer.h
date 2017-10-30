//
//  _LPRoomServer.h
//  BJLiveCore
//
//  Created by 杨磊 on 16/3/25.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "_LPWSServerBase.h"
#import "_LPUser.h"
#import "_LPBroadcastOptions.h"
#import "_LPResBroadcastReceive.h"
#import "_LPRoomLoginConflict.h"

@class RACSignal;

extern NSString *const _LP_ROOM_SERVER_BROADCAST_SEND;
extern NSString *const _LP_ROOM_SERVER_BROADCAST_RECEIVE;
extern NSString *const _LP_ROOM_SERVER_BROADCAST_CACHE_REQ;
extern NSString *const _LP_ROOM_SERVER_BROADCAST_CACHE_RES;

extern NSString *const _LP_BROADCAST_KEY_ALL;
extern NSString *const _LP_BROADCAST_KEY_TEACHER_UPLINK;
extern NSString *const _LP_BROADCAST_KEY_CLOUD_RECORD;
extern NSString *const _LP_BROADCAST_KEY_CLASS_TIME;
extern NSString *const _LP_BROADCAST_KEY_TEACHER_ABROAD;
extern NSString *const _LP_BROADCAST_KEY_FORBID_ALL;

/**
 *  Room Server
 */
@interface _LPRoomServer : _LPWSServerBase

/**
 *  请求公共参数
 */
@property (nonatomic, copy) NSDictionary *commonParams;

@property (nonatomic, readonly) BOOL isOnline;

// 预先设置登录信息、在连接成功后发送
- (void)loginWithUser:(_LPUser *)user
            className:(NSString *)className
           speakState:(_LPSpeakState)speakState
                token:(NSString *)token;

/**
 *  请求服务器缓存的广播
 *
 *  @param key 缓存的广播 key
 */
- (void)requestBroadcastCache:(NSString *)key;

/**
 *  发送广播
 *
 *  @param key     广播key
 *  @param value   广播值
 *  @param options 选项
 */
- (void)requestBroadcastSendKey:(NSString *)key
                          value:(NSDictionary *)value
                        options:(_LPBroadcastOptions *)options;



/**
 *  _LPRoomLoginModel
 *  登录成功需要判断 res && res.code == _LP_CODE_ERROR_SUC
 *
 *  @return
 */
- (RACSignal *)signalOfLogin;

/**
 *  _LPRoomLoginConflict
 *
 *  @return
 */
- (RACSignal *)signalOfLoginConflict;
/**
 *  Dictionary
 *
 *  @return
 */
- (RACSignal *)signalOfBroadcastCache;
/**
 *  _LPResBroadcastReceive
 *
 *  @return 
 */
- (RACSignal *)signalOfBroadcastReceive;

@end
