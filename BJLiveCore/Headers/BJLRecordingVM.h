//
//  BJLRecordingVM.h
//  Pods
//
//  Created by MingLQ on 2016-12-10.
//
//

#import "BJLBaseVM.h"

NS_ASSUME_NONNULL_BEGIN

@interface BJLRecordingVM : BJLBaseVM

/** 音视频开关状态 */
@property (nonatomic, readonly) BOOL recordingAudio, recordingVideo;
/** 声音输入级别 */
@property (nonatomic, readonly) NSInteger inputVolumeLevel; // [0 - 9]

/** 开关音视频
 上课状态才能打开音视频
 上层自行检查麦克风、摄像头开关权限
 上层可通过 BJLSpeakingRequestVM 实现学生发言需要举手的逻辑 */
- (nullable BJLError *)setRecordingAudio:(BOOL)recordingAudio
                          recordingVideo:(BOOL)recordingVideo;
- (void)restartRecording;

/** 音视频被远程开关通知 */
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

/** 是否使用后置摄像头 */
@property (nonatomic) BOOL usingRearCamera;

/** 清晰度 */
@property (nonatomic) BJLVideoDefinition videoDefinition;
/** 美颜 */
@property (nonatomic) BJLVideoBeautifyLevel videoBeautifyLevel;

@end

NS_ASSUME_NONNULL_END
