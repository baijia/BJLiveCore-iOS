//
//  BJLSpeakingRequestVM.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-12-07.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "BJLBaseVM.h"

#import "BJLUser.h"

@protocol BJLSpeakingReply;

NS_ASSUME_NONNULL_BEGIN

extern const NSTimeInterval BJLSpeakingRequestTimeoutInterval, BJLSpeakingRequestCountdownStep;

@interface BJLSpeakingRequestVM : BJLBaseVM

/** 主讲禁止观众举手 */
@property (nonatomic, readonly) BOOL forbidSpeakingRequest;
/**  */
- (nullable BJLError *)requestForbidSpeakingRequest:(BOOL)forbid;

/** 观众: 发言状态 */
@property (nonatomic, readonly) BOOL speakingEnabled;

/** 举手自动取消倒计时
 调用 `sendSpeakingRequest` 举手时设置为 `BJLSpeakingRequestTimeoutInterval` 秒
 每 `BJLSpeakingRequestCountdownStep` 秒更新，变为 0.0 表示举手超时，变为 - 1.0 表示计时被取消 */
@property (nonatomic, readonly) NSTimeInterval speakingRequestTimeRemaining;
/** 观众: 发送发言申请
 开始直播状态才能举手，参考 `roomVM.liveStarted`
 发言申请被允许/拒绝时会收到通知 `speakingRequestDidReply:` */
- (nullable BJLError *)sendSpeakingRequest;
/** 观众: 取消发言申请/结束发言
 更新 `speakingEnabled` */
- (void)stopSpeaking;

/** 主讲: 正在申请发言的观众 */
@property (nonatomic, readonly, copy, nullable) NSArray<BJLUser *> *speakingRequestUsers;

/** 主讲: 收到发言申请 */
- (BJLObservable)receivedSpeakingRequestFromUser:(BJLUser *)user;
/** 主讲: 允许/拒绝发言申请
 允许发言后关闭发言调用 `BJLPlayingVM` 的 `remoteUpdatePlayingUserWithID:audioOn:videoOn:` 方法 */
- (nullable BJLError *)replySpeakingRequestToUserID:(NSString *)userID allowed:(BOOL)allowed;

/** 观众&主讲: 发言申请被允许/拒绝
 更新观众的 `speakingEnabled`
 主讲可以收到所有人发言状态的变更，比如观众自己取消、助理协助允许/拒绝
 @param speakingEnabled 发言申请是否被允许、关闭
 @param isUserCancelled 观众本人取消/请求超时自动取消
 @param user            申请发言的用户
 */
- (BJLObservable)speakingRequestDidReplyEnabled:(BOOL)speakingEnabled
                                isUserCancelled:(BOOL)isUserCancelled
                                           user:(BJLUser *)user;
- (BJLObservable)speakingRequestDidReply:(NSObject<BJLSpeakingReply> *)reply DEPRECATED_MSG_ATTRIBUTE("use `speakingRequestDidReplyEnabled:isUserCancelled:user:`");

/** 发言状态被开启、关闭
 参考 `BJLPlayingVM` 的 `remoteUpdatePlayingUserWithID:audioOn:videoOn:` */
- (BJLObservable)speakingDidRemoteEnabled:(BOOL)enabled;
- (BJLObservable)speakingBeRemoteEnabled:(BOOL)enabled DEPRECATED_MSG_ATTRIBUTE("use `speakingDidRemoteEnabled:`");

@end

#pragma mark -

DEPRECATED_ATTRIBUTE
@protocol BJLSpeakingReply <NSObject>

@property (nonatomic, readonly) BJLUser *user; // 申请发言的用户
@property (nonatomic, readonly) BOOL speakingEnabled; // 发言申请是否被允许、关闭
@property (nonatomic, readonly) BOOL isUserCancelled; // 观众本人取消/请求超时自动取消

@end

NS_ASSUME_NONNULL_END