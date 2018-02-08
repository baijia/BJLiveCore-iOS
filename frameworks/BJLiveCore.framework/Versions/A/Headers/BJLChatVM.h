//
//  BJLChatVM.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-12-10.
//  Copyright © 2016 BaijiaYun. All rights reserved.
//

#import "BJLBaseVM.h"

#import "BJLMessage.h"

NS_ASSUME_NONNULL_BEGIN

/** ### 聊天 */
@interface BJLChatVM : BJLBaseVM

/** 所有消息 */
@property (nonatomic, readonly, copy, nullable) NSArray<BJLMessage *> *receivedMessages;

/** `receivedMessages` 被覆盖更新
 #discussion 覆盖更新才调用，增量更新不调用
 #discussion 首次连接 server 或断开重连会导致覆盖更新
 #param receivedMessages 收到的所有消息
 */
- (BJLObservable)receivedMessagesDidOverwrite:(nullable NSArray<BJLMessage *> *)receivedMessages;

/**
 发送文字消息，参考 `sendMessage:channel:` 方法
 #param text 消息，不能是空字符串或 nil
 #return BJLError：
 BJLErrorCode_invalidArguments  参数错误；
 BJLErrorCode_invalidCalling    错误调用，如禁言状态时调用此方法发送消息。
 */
- (nullable BJLError *)sendMessage:(NSString *)text;

/**
 指定对象，发送文字消息
 */
- (nullable BJLError *)sendMessage:(NSString *)text toUser:(nullable BJLUser *)user;

/**
 指定频道，发送文字消息
 #discussion 最多 BJLTextMaxLength_chat 个字符
 #discussion 成功后会收到消息通知
 #discussion 学生在禁言状态不能发送消息，参考 `forbidMe`、`forbidAll`
 #discussion 参考 `BJLMessage`
 #param text 消息，不能是空字符串或 nil
 #param channel 频道
 */
- (nullable BJLError *)sendMessage:(NSString *)text channel:(nullable NSString *)channel;

/**
 发送图片、表情等其它类型的消息
 #discussion 发送图片需事先调用 `uploadImageFile:progress:finish:` 方法上传
 #discussion 发送表情和图片需将 `(NSString *)emoticon.key` 或 `(NSString *)imageURLString` 转换成 (NSDictionary *)data，参考 `BJLMessage` 的 `messageDataWithEmoticonKey:` 和 `messageDataWithImageURLString:imageWidth:imageHeight:` 方法
 #param data 消息内容
 */
- (nullable BJLError *)sendMessageData:(NSDictionary *)data;

/**
 指定对象，发送图片、表情等其它类型的消息
 */
- (nullable BJLError *)sendMessageData:(NSDictionary *)data toUser:(nullable BJLUser *)user;

/**
 指定频道，发送图片、表情等其它类型的消息
 #param data 消息内容
 #param channel 频道
 */
- (nullable BJLError *)sendMessageData:(NSDictionary *)data channel:(nullable NSString *)channel;

/**
 上传图片，用于发送消息
 #param fileURL     图片文件路径
 #param progress    上传进度，非主线程回调、可能过于频繁
 - progress         0.0 ~ 1.0
 #param finish      结束
 - imageURLString   非 nil 即为成功
 - error            错误
 #return            upload task
 */
- (NSURLSessionUploadTask *)uploadImageFile:(NSURL *)fileURL
                                   progress:(nullable void (^)(CGFloat progress))progress
                                     finish:(void (^)(NSString * _Nullable imageURLString, BJLError * _Nullable error))finish;

/** 收到消息
 #discussion 同时更新 `receivedMessages`
 #param message 消息
 */
- (BJLObservable)didReceiveMessage:(BJLMessage *)message;

/** 全体禁言状态 */
@property (nonatomic, readonly) BOOL forbidAll;

/** 老师: 设置全体禁言状态
 #discussion 设置成功后修改 `forbidAll`
 #param forbidAll YES：全体禁言，NO：取消禁言
 #return BJLError：
 BJLErrorCode_invalidUserRole   错误权限，要求老师或助教权限
 */
- (nullable BJLError *)sendForbidAll:(BOOL)forbidAll;

/** 学生: 当前用户被禁言状态 */
@property (nonatomic, readonly) BOOL forbidMe;

/** 所有人: 收到某人被禁言通知
 #discussion `duration` 为禁言时间
 #discussion 被禁言用户可能是他人、也可能是当前用户
 #discussion 当前用户被禁言、禁言结束时会自动更新 `forbidMe`
 #param user     被禁言用户
 #param fromUser 发起禁言用户
 #param duration 禁言时长
 */
- (BJLObservable)didReceiveForbidUser:(BJLUser *)user
                             fromUser:(nullable BJLUser *)fromUser
                             duration:(NSTimeInterval)duration;

/** 老师: 对某人禁言
 #discussion `duration` 为禁言时间
 #param user     禁言对象
 #param duration 禁言时长
 #return BJLError：
 BJLErrorCode_invalidUserRole   错误权限，要求老师或助教权限
 */
- (nullable BJLError *)sendForbidUser:(BJLUser *)user
                             duration:(NSTimeInterval)duration;

@end

NS_ASSUME_NONNULL_END
