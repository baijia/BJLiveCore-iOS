//
//  _LPRoomServer+Command.h
//  BJLiveCore
//
//  Created by Randy on 16/5/18.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "_LPRoomServer.h"

@class _LPRunTimeInfo;
@class _LPLinkInfo;
@class _LPIpAddress;

@interface _LPRoomServer (Command)

/**
 *  上传当前运行信息
 */
- (BOOL)requestSendRunTimeInfo:(_LPRunTimeInfo *)info
                          from:(NSString *)fromId
                            to:(NSString *)toId;
/**
 *  收到此信号时，调用requestSendRunTimeInfo 上传信息
 *  _LPResCommandModel
 *  @return
 */
- (RACSignal *)signalOfCommandRunTimeInfo;

/**
 *  上传链路信息
 */
- (BOOL)requestSendLinkInfo:(NSArray<_LPLinkInfo *> *)infos
                       from:(NSString *)fromId
                         to:(NSString *)toId;

/**
 *  收到此信号时，调用requestSendLinkInfo 上传信息
 *  _LPResCommandModel
 *  @return
 */
- (RACSignal *)signalOfCommandLinkInfo;

/**
 *  切换上行链路 - TCP，安晨说不需要处理
 *
 *  _LPResCommandLinkInfo
 *  @return
 */
- (RACSignal *)signalOfCommandSwitchUpLink;

/**
 *  切换下行链路 - TCP，安晨说不需要处理
 *
 *  _LPResCommandLinkInfo
 *  @return
 */
- (RACSignal *)signalOfCommandSwitchDownLink;

/**
 *  开关用户 音视频
 *  audioOn, videoOn
 *
 *  _LPResCommandMediaControl
 *  @return
 */
- (RACSignal *)signalOfCommandMediaControl;

/**
 *  增加buffer - 学生端用、老师端不处理
 *
 *  @return
 */
- (RACSignal *)signalOfCommandPlayBuffer; // NSNumber *buffer

/**
 *  修改用户上行链路类型
 *  _LPLinkType
 *
 *  _LPResCommandLinkType
 *  @return
 */
- (RACSignal *)signalOfCommandChangeUplinkType;

/**
 *  修改用户下行链路类型
 *  _LPLinkType
 *
 *  _LPResCommandLinkType
 *  @return
 */
- (RACSignal *)signalOfCommandChangeDownlinkType;

/**
 *  修改用户上行udp服务器
 *  UDP _LPIpAddress
 *
 *  _LPResCommandUDPServer
 *  @return
 */
- (RACSignal *)signalOfCommandChangeUplinkServer;

/**
 *  修改用户下行udp服务器
 *  UDP _LPIpAddress
 *
 *  _LPResCommandUDPServer
 *  @return
 */
- (RACSignal *)signalOfCommandChangeDownlinkServer;

@end
