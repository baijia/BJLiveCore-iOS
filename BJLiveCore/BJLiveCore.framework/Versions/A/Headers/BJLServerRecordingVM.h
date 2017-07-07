//
//  BJLServerRecordingVM.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-12-06.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "BJLBaseVM.h"

NS_ASSUME_NONNULL_BEGIN

@interface BJLServerRecordingVM : BJLBaseVM

/** 云端录制状态 */
@property (nonatomic, readonly) BOOL serverRecording;

/** 开始/停止云端录制
 主讲才能开启录制，参考 `BJLErrorCode_invalidUserRole`
 直播开始状态才能开启录制，参考 `roomVM.liveStarted`
 此方法需要发起网络请求、检查云端录制是否可用
 - 如果可以录制则开始、并设置 `serverRecording`
 - 否则发送失败通知 `requestServerRecordingDidFailed:` */
- (nullable BJLError *)requestServerRecording:(BOOL)on;

/** 检查云端录制不可用的通知
 包括网络请求失败 */
- (BJLObservable)requestServerRecordingDidFailed:(NSString *)message;

@end

NS_ASSUME_NONNULL_END
