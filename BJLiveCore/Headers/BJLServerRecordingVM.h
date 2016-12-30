//
//  BJLServerRecordingVM.h
//  Pods
//
//  Created by MingLQ on 2016-12-06.
//
//

#import "BJLBaseVM.h"

NS_ASSUME_NONNULL_BEGIN

@interface BJLServerRecordingVM : BJLBaseVM

/** 云端录课状态 */
@property (nonatomic, readonly) BOOL serverRecording;

/** 开始/停止云端录课
 上课状态下才能录课
 此方法需要发起网络请求、检查云端录课是否可用
 - 如果可以录课则开始、并设置 `serverRecording`
 - 否则发送失败通知 `requestServerRecordingDidFailed:` */
- (nullable BJLError *)requestServerRecording:(BOOL)on;

/** 检查云端录课不可用的通知
 包括网络请求失败 */
- (BJLOEvent)requestServerRecordingDidFailed:(NSString *)message;

@end

NS_ASSUME_NONNULL_END
