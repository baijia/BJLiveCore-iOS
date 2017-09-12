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

/** 老师禁止学生举手 */
@property (nonatomic, readonly) BOOL forbidSpeakingRequest;
/**  */
- (nullable BJLError *)requestForbidSpeakingRequest:(BOOL)forbid;

/** 学生: 发言状态
 举手、邀请发言、远程开关音视频等事件会改变此状态
 上层需要根据这个状态开启/关闭音视频，上次开关音视频前需要判断当前音视频状态
 因为 `speakingDidRemoteControl:` 会直接开关音视频、然后再更新学生的 `speakingEnabled` */
@property (nonatomic, readonly) BOOL speakingEnabled;

/** 举手自动取消倒计时
 调用 `sendSpeakingRequest` 举手时设置为 `BJLSpeakingRequestTimeoutInterval` 秒
 每 `BJLSpeakingRequestCountdownStep` 秒更新，变为 0.0 表示举手超时，变为 - 1.0 表示计时被取消 */
@property (nonatomic, readonly) NSTimeInterval speakingRequestTimeRemaining;
/** 学生: 发送发言申请
 上课状态才能举手，参考 `roomVM.liveStarted`
 发言申请被允许/拒绝时会收到通知 `speakingRequestDidReply:` */
- (nullable BJLError *)sendSpeakingRequest;
/** 学生: 取消发言申请/结束发言
 更新 `speakingEnabled` */
- (void)stopSpeaking;

/** 老师: 正在申请发言的学生 */
@property (nonatomic, readonly, copy, nullable) NSArray<BJLUser *> *speakingRequestUsers;

/** 老师: 收到发言申请 */
- (BJLObservable)receivedSpeakingRequestFromUser:(BJLUser *)user;
/** 老师: 允许/拒绝发言申请
 允许发言后，关闭发言需要调用 `BJLPlayingVM` 的 `remoteUpdatePlayingUserWithID:audioOn:videoOn:` 方法 */
- (nullable BJLError *)replySpeakingRequestToUserID:(NSString *)userID allowed:(BOOL)allowed;

/** 学生&老师: 发言申请被允许/拒绝
 更新学生的 `speakingEnabled`
 老师可以收到所有人发言状态的变更，比如学生自己取消、助教协助允许/拒绝
 @param speakingEnabled 发言申请是否被允许、关闭
 @param isUserCancelled 学生本人取消/请求超时自动取消
 @param user            申请发言的用户
 */
- (BJLObservable)speakingRequestDidReplyEnabled:(BOOL)speakingEnabled
                                isUserCancelled:(BOOL)isUserCancelled
                                           user:(BJLUser *)user;
- (BJLObservable)speakingRequestDidReply:(NSObject<BJLSpeakingReply> *)reply DEPRECATED_MSG_ATTRIBUTE("use `speakingRequestDidReplyEnabled:isUserCancelled:user:`");

/** 学生: 收到邀请发言
 @param invite  YES 收到邀请、NO 邀请取消 */
- (BJLObservable)didReceiveSpeakingInvite:(BOOL)invite;
/** 学生: 接受或拒绝发言邀请
 接受后更新学生的 `speakingEnabled`
 @param accept  接受或拒绝 */
- (nullable BJLError *)responseSpeakingInvite:(BOOL)accept;

/** 音视频被远程开启、关闭，导致发言状态变化
 音视频有一个打开就开启发言、全部关闭就结束发言
 SDK 内部先开关音视频、然后再更更新学生的 `speakingEnabled` 的状态
 参考 `BJLRecordingVM` 的 `recordingDidRemoteChangedRecordingAudio:recordingVideo:recordingAudioChanged:recordingVideoChanged:` */
- (BJLObservable)speakingDidRemoteControl:(BOOL)enabled;
- (BJLObservable)speakingDidRemoteEnabled:(BOOL)enabled DEPRECATED_MSG_ATTRIBUTE("use `speakingDidRemoteControl:`");
- (BJLObservable)speakingBeRemoteEnabled:(BOOL)enabled DEPRECATED_MSG_ATTRIBUTE("use `speakingDidRemoteEnabled:`");

@end

#pragma mark -

DEPRECATED_ATTRIBUTE
@protocol BJLSpeakingReply <NSObject>

@property (nonatomic, readonly) BJLUser *user; // 申请发言的用户
@property (nonatomic, readonly) BOOL speakingEnabled; // 发言申请是否被允许、关闭
@property (nonatomic, readonly) BOOL isUserCancelled; // 学生本人取消/请求超时自动取消

@end

NS_ASSUME_NONNULL_END
