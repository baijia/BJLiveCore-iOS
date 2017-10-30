//
//  BJLChatVM.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-12-10.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "BJLBaseVM.h"

#import "BJLMessage.h"

NS_ASSUME_NONNULL_BEGIN

@interface BJLChatVM : BJLBaseVM

/** 所有消息 */
@property (nonatomic, readonly, nullable, copy) NSArray<NSObject<BJLMessage> *> *receivedMessages;

/** `receivedMessages` 被覆盖更新
 覆盖更新才调用，增量更新不调用
 首次连接 server 或断开重连会导致覆盖更新
 */
- (BJLObservable)receivedMessagesDidOverwrite:(nullable NSArray<NSObject<BJLMessage> *> *)receivedMessages;

/**
 发消息
 最多 BJLTextMaxLength_chat 个字符
 成功后会收到消息通知
 @param content 消息，不能是空字符串或 nil
 @param channel 频道
 参考 `BJLMessage`
 */
- (nullable BJLError *)sendMessage:(NSString *)content;
- (nullable BJLError *)sendMessage:(NSString *)content channel:(nullable NSString *)channel;

/** 收到消息
 同时更新 `receivedMessages` */
- (BJLObservable)didReceiveMessage:(NSObject<BJLMessage> *)message;

/** 全体禁言状态 */
@property (nonatomic, readonly) BOOL forbidAll;

/** 老师: 设置全体禁言状态
 设置成功后修改 `forbidAll` */
- (nullable BJLError *)sendForbidAll:(BOOL)forbidAll;

/** 学生: 当前用户被禁言状态 */
@property (nonatomic, readonly) BOOL forbidMe;

/** 所有人: 收到某人被禁言通知
 `duration` 为禁言时间
 可能是他人、也可能是当前用户
 当前用户被禁言、禁言结束时会自动更新 `forbidMe` */
- (BJLObservable)didReceiveForbidUser:(NSObject<BJLUser> *)user
                             fromUser:(nullable NSObject<BJLUser> *)fromUser
                             duration:(NSTimeInterval)duration;

/** 老师: 对某人禁言
 `duration` 为禁言时间 */
- (nullable BJLError *)sendForbidUser:(NSObject<BJLUser> *)user
                             duration:(NSTimeInterval)duration;

@end

NS_ASSUME_NONNULL_END
