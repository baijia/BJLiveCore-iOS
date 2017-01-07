//
//  BJLSpeakingRequestVM.h
//  Pods
//
//  Created by MingLQ on 2016-12-07.
//
//

#import "BJLBaseVM.h"

#import "BJLUser.h"

@protocol BJLSpeakingReply;

NS_ASSUME_NONNULL_BEGIN

@interface BJLSpeakingRequestVM : BJLBaseVM

/** 学生: 发言是否被允许 */
@property (nonatomic, readonly) BOOL speakingEnabled;

/** 学生: 发送发言申请
 上课状态才能举手
 发言申请被允许/拒绝时会收到通知 `speakingRequestDidReply:` */
- (nullable BJLError *)sendSpeakingRequest;
/** 学生: 取消发言申请/结束发言
 更新 `speakingEnabled` */
- (void)stopSpeaking;

/** 老师: 正在申请发言的学生 */
@property (nonatomic, readonly, nullable, copy) NSArray<NSObject<BJLUser> *> *speakingRequestUsers;

/** 老师: 收到发言申请 */
- (BJLObservable)receivedSpeakingRequestFromUser:(NSObject<BJLUser> *)user;
/** 老师: 允许/拒绝发言申请 */
- (nullable BJLError *)replySpeakingRequestToUserID:(NSString *)userID allowed:(BOOL)allowed;

/** 学生&老师: 发言申请被允许/拒绝
 更新学生的 `speakingEnabled`
 老师可以收到所有人发言状态的变更，比如学生自己取消、助教协助允许/拒绝 */
- (BJLObservable)speakingRequestDidReply:(NSObject<BJLSpeakingReply> *)reply;
/** 发言状态被开启、关闭 */
- (BJLObservable)speakingDidRemoteEnabled:(BOOL)enabled;

@end

#pragma mark -

@protocol BJLSpeakingReply <NSObject>

@property (nonatomic, readonly) NSObject<BJLUser> *user; // 申请发言的用户
@property (nonatomic, readonly) BOOL speakingEnabled; // 发言申请是否被允许、关闭
@property (nonatomic, readonly) BOOL isUserCancelled; // 学生本人取消/请求超时自动取消

@end

NS_ASSUME_NONNULL_END
