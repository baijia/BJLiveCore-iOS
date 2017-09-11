//
//  BJLRecordingVM.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-12-10.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "BJLBaseVM.h"

NS_ASSUME_NONNULL_BEGIN

@interface BJLRecordingVM : BJLBaseVM

/** 音视频开关状态 */
@property (nonatomic, readonly) BOOL recordingAudio, recordingVideo;
/** 声音输入级别 */
@property (nonatomic, readonly) CGFloat inputVolumeLevel; // [0.0 - 1.0]
/** 采集视频宽高比 */
@property (nonatomic, readonly) CGFloat inputVideoAspectRatio;

/** 开关音视频
 上课状态才能打开音视频，参考 `roomVM.liveStarted`
 上层自行检查麦克风、摄像头开关权限
 上层可通过 BJLSpeakingRequestVM 实现学生发言需要举手的逻辑 */
- (nullable BJLError *)setRecordingAudio:(BOOL)recordingAudio
                          recordingVideo:(BOOL)recordingVideo;
/* TODO: set/send/... to update/request/req
- (nullable BJLError *)updateRecordingAudio:(BOOL)recordingAudio
                             recordingVideo:(BOOL)recordingVideo;
- (nullable BJLError *)updateRecordingAudio:(BOOL)recordingAudio;
- (nullable BJLError *)updateRecordingVideo:(BOOL)recordingVideo; */
- (void)restartRecording;

/** 音视频被远程开关通知
 对于学生，音视频有一个打开就开启发言、全部关闭就结束发言
 参考 `BJLSpeakingRequestVM` 的 `speakingDidRemoteControl:` */
- (BJLObservable)recordingDidRemoteChangedRecordingAudio:(BOOL)recordingAudio
                                          recordingVideo:(BOOL)recordingVideo
                                   recordingAudioChanged:(BOOL)recordingAudioChanged
                                   recordingVideoChanged:(BOOL)recordingVideoChanged;
- (BJLObservable)recordingDidRemoteChanged:(BJLTuple<void (^)(BOOL recordingAudio,
                                                              BOOL recordingVideo,
                                                              BOOL recordingAudioChanged,
                                                              BOOL recordingVideoChanged)> *)tuple DEPRECATED_MSG_ATTRIBUTE("use `recordingDidRemoteChangedRecordingAudio:recordingVideo:recordingAudioChanged:recordingVideoChanged:`");

#pragma mark - 音视频采集设置

/**
 以下设置
 - 开始采集之前、之后均可调用
 - 开关音视频后不被重置
 - 个别设置可能会导致视频流重新发布
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
