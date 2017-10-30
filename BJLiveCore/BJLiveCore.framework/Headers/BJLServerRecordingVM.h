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

/** 云端录课状态 */
@property (nonatomic, readonly) BOOL serverRecording;

/** 开始/停止云端录课
 老师才能开启录课，参考 `BJLErrorCode_invalidUserRole`
 上课状态才能开启录课，参考 `roomVM.liveStarted`、`BJLErrorCode_serverRecording_not_liveStarted`
 此方法需要发起网络请求、检查云端录课是否可用
 - 如果可以录课则开始、并设置 `serverRecording`
 - 否则发送失败通知 `requestServerRecordingDidFailed:` */
- (nullable BJLError *)requestServerRecording:(BOOL)on;

/** 检查云端录课不可用的通知
 包括网络请求失败 */
- (BJLObservable)requestServerRecordingDidFailed:(NSString *)message;

@end

NS_ASSUME_NONNULL_END
