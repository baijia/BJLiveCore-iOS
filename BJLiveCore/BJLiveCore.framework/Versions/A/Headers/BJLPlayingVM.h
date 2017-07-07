//
//  BJLPlayingVM.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-12-16.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "BJLBaseVM.h"

#import "BJLUser.h"

NS_ASSUME_NONNULL_BEGIN

extern const NSInteger BJLVideoPlayingMaxCount;

@interface BJLPlayingVM : BJLBaseVM

/** 音视频用户列表
 包含 `videoPlayingUser`
 所有音频直接播放，视频需要调用 `updateVideoPlayingUser:` 打开
 SDK 会处理音视频打断、恢复、前后台切换等情况
 */
@property (nonatomic, readonly, copy, nullable) NSArray<BJLUser *> *playingUsers;

/** 用户开关音、视频
 - 某个用户主动开关自己的音视频时发送此通知、不包含意外掉线等情况
 - 正在播放的视频用户 关闭视频时 `videoPlayingUser` 将被设置为 nil、同时发送此通知
 - 进房间后批量更新 `playingUsers` 时『不』发送此通知
 */
- (BJLObservable)playingUserDidUpdate:(nullable BJLUser *)now
                                  old:(nullable BJLUser *)old;
/** 用户希望被全屏显示
 比如在 PC 上共享桌面、播放本地视频
 目前只支持主讲（不支持主讲） */
- (BJLObservable)playingUserWantsShowInFullScreen:(BJLUser *)user;

/** `playingUsers` 被覆盖更新
 进房间后批量更新才调用，增量更新不调用
 */
- (BJLObservable)playingUsersDidOverwrite:(nullable NSArray<BJLUser *> *)playingUsers;

/**
 BJLTuple 用于将多个封装到一个参数里，使用 BJLTupleUnpack + unpack-block 还原，例如：
 *     BJLTupleUnpack(tuple) = ^(BJLUser *old, BJLUser *now) {
 *         BOOL audioChanged = old.audioOn != now.audioOn;
 *         NSString *audioAction = audioChanged ? (now.audioOn ? @"打开音频" : @"关闭音频") : nil;
 *         BOOL videoChanged = old.videoOn != now.videoOn;
 *         NSString *videoAction = videoChanged ? (now.videoOn ? @"打开视频" : @"关闭视频") : nil;
 *         // self 不需要 weakify&strongify，因为 unpack-block 会被立即执行、然后销毁
 *         [self displayUser:now audioAction:audioAction videoAction:videoAction];
 *     }
 */
- (BJLObservable)playingUserDidUpdate:(BJLTuple<void (^)(BJLUser *old,
                                                         BJLUser *now)> *)tuple DEPRECATED_MSG_ATTRIBUTE("use `playingUserDidUpdate:old:`");

#pragma mark -

/** 正在播放的视频用户
 `playingUsers` 的子集
 断开重连、暂停恢复等操作不自动重置 `videoPlayingUsers`，除非对方用户关闭摄像头、离线、掉线等 */
@property (nonatomic, readonly, copy, nullable) NSArray<BJLUser *> *videoPlayingUsers;

/** 设置播放用户的视频
 同时打开他人视频个数不超过 `BJLVideoPlayingMaxCount` */
- (nullable BJLError *)updatePlayingUserWithID:(NSString *)userID videoOn:(BOOL)videoOn;

/** 获取播放用户的视频视图 */
- (nullable UIView *)playingViewForUserWithID:(NSString *)userID;
/** 获取播放用户的视频视图宽高比 */
- (CGFloat)playingViewAspectRatioForUserWithID:(NSString *)userID;
- (BJLObservable)playingViewAspectRatioChanged:(CGFloat)videoAspectRatio forUserWithID:(NSString *)userID;

- (void)restartPlaying;

#pragma mark -

/** 主讲: 远程开关用户音、视频
 打开音频、视频会导致对方发言状态开启
 同时关闭音频、视频会导致对方发言状态终止
 @see `speakingRequestVM.speakingEnabled`
 TODO: 移至 `BJLSpeakingRequestVM` */
- (nullable BJLError *)remoteUpdatePlayingUserWithID:(NSString *)userID
                                             audioOn:(BOOL)audioOn
                                             videoOn:(BOOL)videoOn;

@end

NS_ASSUME_NONNULL_END
