//
//  _BJLContext.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-11-29.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "BJLRoom.h"

#import "_LPRoomInfo.h"
#import "_LPMasterUser.h"

#import "BJLFeatureConfig.h"

#import "_LPRoomServer.h"
#import "_LPChatServer.h"
#import "_LPMediaPlayer.h"

#import "_LPLoginModel.h"
#import "_LPRoomLoginModel.h"
#import "_LPChatServerLogin.h"

NS_ASSUME_NONNULL_BEGIN

/**
 BJLContext
 
 【不用于】管理各种状态、以及处理各种逻辑，那些事情放在 view-model 里；
 【仅用于】管理 音视频、WS 连接 等 <必须全局唯一的服务>；
 【禁止】任何代码持有 <必须全局唯一的服务> —— 必须通过 context.property 的方式访问；
 
 BJLContext 可能同时存在多个实例，但最多只有一个有效实例，无效实例所有属性将被置空，这样做有几个原因：
 1、音视频等服务不允许多份实例同时存在；
 2、单例弊端太多，这里不再举栗说明；
 3、不暴露获取唯一有效实例的方法，避免被当作单例使用；
 */
@interface BJLContext : NSObject

#pragma mark - lifecycle

+ (instancetype)alloc NS_UNAVAILABLE;

+ (nullable instancetype)createContextForRoom:(__kindof BJLRoom *)room;
/** 是否存在有效教室 */
+ (BOOL)hasActiveContext;
/** 当前教室是否有效 */
@property (nonatomic, readonly) BOOL isActiveContext;
- (void)destroy;

#pragma mark - context

/** 初始化 context 时传入的 room */
@property (nonatomic, readonly) __kindof BJLRoom *room;

/** !!!: 断开重连时以下参数可能被重新赋值、更改属性，方法可能被多次调用 */

/** KVO 非空时开始监听服务端信令 */
@property (nonatomic, readonly, nullable) _LPRoomServer *roomServer;
@property (nonatomic, readonly, nullable) _LPChatServer *chatServer;
@property (nonatomic, readonly, nullable) _LPMediaPlayer *mediaPlayer;
@property (nonatomic, readonly) UIView *recordingView, *playingView;

/** 加载教室信息 */
@property (nonatomic, readonly, nullable) _LPRoomInfo *roomInfo;
@property (nonatomic, readonly, nullable) _LPMasterUser *loginUser;
@property (nonatomic, readonly, nullable) NSString *token;
- (BOOL)didLoadRoomInfo:(_LPRoomInfo *)roomInfo
              loginUser:(_LPMasterUser *)loginUser
                  token:(NSString *)token;

/** 加载功能配置 */
@property (nonatomic, readonly, nullable) BJLFeatureConfig *featureConfig;
- (BOOL)didLoadFeatureConfig:(BJLFeatureConfig *)serverConfig;

/** 连接 MasterServer */
// @property (nonatomic, readonly, nullable) _LPLoginModel *masterModel;
- (BOOL)didLoginMasterServerWithModel:(_LPLoginModel *)masterModel;

/** 连接 RoomServer */
@property (nonatomic, readonly, nullable) _LPRoomLoginModel *roomModel;
- (nullable BJLError *)didLoginRoomServerWithModel:(_LPRoomLoginModel *)roomModel;

/** 连接 ChatServer */
@property (nonatomic, readonly, nullable) _LPChatServerLogin *chatModel;
- (nullable BJLError *)didLoginChatServerWithModel:(_LPChatServerLogin *)chatModel;

@end

NS_ASSUME_NONNULL_END
