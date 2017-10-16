//
//  BJLPlayingVM.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-12-16.
//  Copyright © 2016 BaijiaYun. All rights reserved.
//

#import "BJLBaseVM.h"

#import "BJLUser.h"

NS_ASSUME_NONNULL_BEGIN

/** ### 音视频播放 */
@interface BJLPlayingVM : BJLBaseVM

/** 音视频用户列表
 #discussion 包含 `videoPlayingUser`
 #discussion 所有音频直接播放，视频需要调用 `updateVideoPlayingUser:` 打开
 #discussion SDK 会处理音视频打断、恢复、前后台切换等情况
 */
@property (nonatomic, readonly, copy, nullable) NSArray<BJLUser *> *playingUsers;
/** 从 `playingUsers` 查找用户
 #param userID 用户 ID
 #param userNumber 用户编号
 */
- (nullable __kindof BJLUser *)userWithID:(nullable NSString *)userID number:(nullable NSString *)userNumber;

/** 用户开关音、视频
 #discussion - 某个用户主动开关自己的音视频时发送此通知、不包含意外掉线等情况
 #discussion - 正在播放的视频用户 关闭视频时 `videoPlayingUser` 将被设置为 nil、同时发送此通知
 #discussion - 进教室后批量更新 `playingUsers` 时『不』发送此通知
 #discussion - 音视频开关状态通过 `BJLUser` 的 `audioOn`、`videoOn` 获得
 #param now 新用户信息
 #param old 旧用户信息
 */
- (BJLObservable)playingUserDidUpdate:(nullable BJLUser *)now
                                  old:(nullable BJLUser *)old;
/** 用户希望被全屏显示
 #discussion 比如在 PC 上共享桌面、播放本地视频
 #discussion 目前只支持老师（不支持主讲）
 #param user 对象用户
 */
- (BJLObservable)playingUserWantsShowInFullScreen:(BJLUser *)user;

/** `playingUsers` 被覆盖更新
 #discussion 进教室后批量更新才调用，增量更新不调用
 #param playingUsers 音视频用户列表
 */
- (BJLObservable)playingUsersDidOverwrite:(nullable NSArray<BJLUser *> *)playingUsers;

#pragma mark -

/** 正在播放的视频用户
 #discussion `playingUsers` 的子集
 #discussion 断开重连、暂停恢复等操作不自动重置 `videoPlayingUsers`，除非对方用户掉线、离线等 */
@property (nonatomic, readonly, copy, nullable) NSArray<BJLUser *> *videoPlayingUsers;

/** 设置播放用户的视频
 #param userID 用户 ID
 #param videoOn YES：打开视频，NO：关闭视频
 #return BJLError：
 BJLErrorCode_invalidArguments  错误参数，如 `playingUsers` 中不存在此用户；
 BJLErrorCode_invalidCalling    错误调用，如用户视频已经在播放、或用户没有开启摄像头。
 */
- (nullable BJLError *)updatePlayingUserWithID:(NSString *)userID videoOn:(BOOL)videoOn;

/** 获取播放用户的视频视图
 #param userID 用户 ID
 */
- (nullable UIView *)playingViewForUserWithID:(NSString *)userID;

/** 获取播放用户的视频视图宽高比
 #param userID 用户 ID
 */
- (CGFloat)playingViewAspectRatioForUserWithID:(NSString *)userID;

/** 用户视频宽高比发生变化的通知
 #param videoAspectRatio 视频宽高比
 #param userID 用户 ID
 */
- (BJLObservable)playingViewAspectRatioChanged:(CGFloat)videoAspectRatio forUserWithID:(NSString *)userID;

/** 重新开始播放视频 */
- (void)restartPlaying;

@end

NS_ASSUME_NONNULL_END
