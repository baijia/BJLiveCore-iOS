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

/**
 发消息
 成功后会收到消息通知
 */
- (nullable BJLError *)sendMessage:(NSString *)content;

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
