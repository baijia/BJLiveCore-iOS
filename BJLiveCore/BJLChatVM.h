//
//  BJLChatVM.h
//  Pods
//
//  Created by MingLQ on 2016-12-10.
//
//

#import "BJLBaseVM.h"

#import "BJLMessage.h"

NS_ASSUME_NONNULL_BEGIN

@interface BJLChatVM : BJLBaseVM

// TODO: MingLQ - 禁言

/** 所有消息
 TODO: 连接服务器后自动加载历史消息并存储到本地 */
@property (nonatomic, readonly, nullable, copy) NSArray<NSObject<BJLMessage> *> *receivedMessages;

/**
 发消息
 MingLQ - 成功后会收到消息通知
 */
- (nullable BJLError *)sendMessage:(NSString *)content;

/** 收到消息
 同时更新 `receivedMessages` */
- (BJLOEvent)didReceiveMessage:(NSObject<BJLMessage> *)message;

@end

NS_ASSUME_NONNULL_END
