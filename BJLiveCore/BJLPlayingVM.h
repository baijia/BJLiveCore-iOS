//
//  BJLPlayingVM.h
//  Pods
//
//  Created by MingLQ on 2016-12-16.
//
//

#import "BJLBaseVM.h"

#import "BJLUser.h"

NS_ASSUME_NONNULL_BEGIN

@interface BJLPlayingVM : BJLBaseVM

/** 音视频用户列表
 包含 `videoPlayingUser`
 连接教室后会自动加载、掉线后清空、重新连接后再次自动加载
 所有音频直接播放、视频需要调用 `updateVideoPlayingUser:` 打开
 参考 `loadPlayingUsers` */
@property (nonatomic, readonly, nullable, copy) NSArray<NSObject<BJLOnlineUser> *> *playingUsers;

/** 加载音视频用户列表
 连接教室后会自动调用、掉线后清空 `playingUsers`、重新连接后再次自动调用
 加载成功后更新 `playingUsers`、`videoPlayingUser`
 */
- (void)loadPlayingUsers;

/** 用户开关音、视频
 - 某个用户主动开关自己的音视频时发送此通知、不包含意外掉线等情况
 - 正在播放的视频用户 关闭视频时 `videoPlayingUser` 将被设置为 nil、同时发送此通知
 - `loadPlayingUsers` 导致批量更新 `playingUsers` 时『不』发送此通知
 - BJLTuple 用于将多个封装到一个参数里，使用 BJLTupleUnpack + unpack-block 还原，例如：
 *     BJLTupleUnpack(tuple) = ^(NSObject<BJLOnlineUser> *old, NSObject<BJLOnlineUser> *now) {
 *         BOOL audioChanged = old.audioOn != now.audioOn;
 *         NSString *audioAction = audioChanged ? (now.audioOn ? @"打开音频" : @"关闭音频") : nil;
 *         BOOL videoChanged = old.videoOn != now.videoOn;
 *         NSString *videoAction = videoChanged ? (now.videoOn ? @"打开视频" : @"关闭视频") : nil;
 *         // self 不需要 weakify&strongify，因为 unpack-block 会被立即执行、然后销毁
 *         [self displayUser:now audioAction:audioAction videoAction:videoAction];
 *     }
 */
- (BJLOEvent)playingUserDidUpdate:(BJLTuple<void (^)(NSObject<BJLOnlineUser> *old,
                                                     NSObject<BJLOnlineUser> *now)> *)tuple;

#pragma mark -

/** 正在播放的视频用户 */
@property (nonatomic, readonly, nullable) NSObject<BJLOnlineUser> *videoPlayingUser;

/** 设置播放用户的视频
 将导致当前正在播放的视频被关闭，传 nil 表示关闭正在播放的视频 */
- (nullable BJLError *)updateVideoPlayingUserWithID:(nullable NSString *)userID;

- (void)restartPlaying;

#pragma mark -

/** 老师: 远程开关用户音、视频
 打开音频、视频会导致对方发言状态开启
 同时关闭音频、视频会导致对方发言状态终止
 @see `speakingRequestVM.speakingEnabled` */
- (nullable BJLError *)remoteUpdatePlayingUserWithID:(NSString *)userID
                                             audioOn:(BOOL)audioOn
                                             videoOn:(BOOL)videoOn;

@end

NS_ASSUME_NONNULL_END
