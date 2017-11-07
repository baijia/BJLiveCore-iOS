//
//  BJLRecordingVM.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-12-10.
//  Copyright © 2016 BaijiaYun. All rights reserved.
//

#import "BJLBaseVM.h"

NS_ASSUME_NONNULL_BEGIN

/** ### 音视频采集 */
@interface BJLRecordingVM : BJLBaseVM

/** 音视频开关状态 */
@property (nonatomic, readonly) BOOL recordingAudio, recordingVideo;
/** 声音输入级别 */
@property (nonatomic, readonly) CGFloat inputVolumeLevel; // [0.0 - 1.0]
/** 采集视频宽高比 */
@property (nonatomic, readonly) CGFloat inputVideoAspectRatio;

/** 开关音视频
 #discussion 上课状态才能打开音视频，参考 `roomVM.liveStarted`
 #discussion 上层自行检查麦克风、摄像头开关权限
 #discussion 上层可通过 BJLSpeakingRequestVM 实现学生发言需要举手的逻辑
 #param recordingAudio YES：打开音频采集，NO：关闭音频采集
 #param recordingVideo YES：打开视频采集，NO：关闭视频采集
 #return BJLError：
 BJLErrorCode_invalidCalling    错误调用，如学生在非上课状态下开启音视频、在音频教室开启摄像头
 */
- (nullable BJLError *)setRecordingAudio:(BOOL)recordingAudio
                          recordingVideo:(BOOL)recordingVideo;
/* TODO: set/send/... to update/request/req
- (nullable BJLError *)updateRecordingAudio:(BOOL)recordingAudio
                             recordingVideo:(BOOL)recordingVideo;
- (nullable BJLError *)updateRecordingAudio:(BOOL)recordingAudio;
- (nullable BJLError *)updateRecordingVideo:(BOOL)recordingVideo; */

/** 重新开始采集 */
- (void)restartRecording;

/** 音视频被远程开关通知
 #discussion 对于学生，音、视频有一个打开就开启发言、全部关闭就结束发言
 #discussion 参考 `BJLSpeakingRequestVM` 的 `speakingDidRemoteControl:`
 #param recordingAudio YES：打开音频采集，NO：关闭音频采集
 #param recordingVideo YES：打开视频采集，NO：关闭视频采集
 #param recordingAudioChanged 音频采集状态是否发生变化
 #param recordingVideoChanged 视频采集状态是否发生变化
 */
- (BJLObservable)recordingDidRemoteChangedRecordingAudio:(BOOL)recordingAudio
                                          recordingVideo:(BOOL)recordingVideo
                                   recordingAudioChanged:(BOOL)recordingAudioChanged
                                   recordingVideoChanged:(BOOL)recordingVideoChanged;

/** 老师: 远程开关学生音、视频
 #discussion 打开音频、视频会导致对方发言状态开启
 #discussion 同时关闭音频、视频会导致对方发言状态终止
 @see `speakingRequestVM.speakingEnabled`
 #param user 对象用户
 #param audioOn YES：打开音频采集，NO：关闭音频采集
 #param videoOn YES：打开视频采集，NO：关闭视频采集
 #return BJLError：
 BJLErrorCode_invalidArguments  错误参数；
 BJLErrorCode_invalidUserRole   错误权限，要求老师或助教权限。
 */
- (nullable BJLError *)remoteChangeRecordingWithUser:(BJLUser *)user
                                             audioOn:(BOOL)audioOn
                                             videoOn:(BOOL)videoOn;

#pragma mark - 音视频采集设置

/**
 以下设置
 #discussion - 开始采集之前、之后均可调用
 #discussion - 开关音视频后不被重置
 #discussion - 个别设置可能会导致视频流重新发布
 */

/** 使用后置摄像头，默认使用前置摄像头 */
@property (nonatomic) BOOL usingRearCamera; // NO: Front, YES Rear(iSight)
/** 视频方向，默认自动 */
@property (nonatomic) BJLVideoOrientation videoOrientation;
/** 清晰度，默认标清 */
@property (nonatomic) BJLVideoDefinition videoDefinition;
/** 美颜，默认关闭 */
@property (nonatomic) BJLVideoBeautifyLevel videoBeautifyLevel;

@end

NS_ASSUME_NONNULL_END
