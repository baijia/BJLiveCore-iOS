//
//  _LPWSServerBase.h
//  BJLiveCore
//
//  Created by 杨磊 on 16/3/24.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import <BJHL-Websocket-iOS/BJWebSocketBase.h>
#import "_LPIpAddress.h"

extern NSString *const _LP_WS_KEY_MESSAGE_TYPE;
/**
 包装 _LPWSServerInterface 类， 
 1、增加备用地址列表功能。
 2、请求队列， 连接成功前发出的请求会缓存下来。待连接成功后自动重新发送. 防止中间断开重连时消息丢失
 
 供外界调用或继承的类。 以便于总要需要修改成 mm 文件。
 */
@interface _LPWSServerBase : BJWebSocketBase

@property (nonatomic, copy) NSArray<_LPIpAddress *> *backupAddrs;

/**
 *  @param backupAddrs 重连备用地址列表
 */
- (instancetype)initWithIpAddr:(NSString *)ipAddr port:(NSUInteger)port backupAddrs:(NSArray<_LPIpAddress *> *)backupAddrs NS_DESIGNATED_INITIALIZER;
- (void)updateIpAddr:(NSString *)ipAddr port:(NSUInteger)port backupAddrs:(NSArray<_LPIpAddress *> *)backupAddrs;

- (NSString *)getCurrentIpAddress;

@end
