//
//  BJLServerRecordingVM.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-12-06.
//  Copyright © 2016 BaijiaYun. All rights reserved.
//

#import "BJLBaseVM.h"

NS_ASSUME_NONNULL_BEGIN

/** ### 云端录课 */
@interface BJLServerRecordingVM : BJLBaseVM

/** 云端录课状态 */
@property (nonatomic, readonly) BOOL serverRecording;

/** 开始/停止云端录课
 #discussion 老师才能开启录课，参考 `BJLErrorCode_invalidUserRole`
 #discussion 上课状态才能开启录课，参考 `roomVM.liveStarted`
 #discussion 此方法需要发起网络请求、检查云端录课是否可用
 #discussion - 如果可以录课则开始、并设置 `serverRecording`
 #discussion - 否则发送失败通知 `requestServerRecordingDidFailed:`
 #param on YES：打开录制，NO：关闭录制
 #return BJLError：
 BJLErrorCode_invalidCalling    错误调用，如在非上课状态下调用此方法；
 BJLErrorCode_invalidUserRole   错误权限，要求老师或助教权限。
 */
- (nullable BJLError *)requestServerRecording:(BOOL)on;

/** 检查云端录课不可用的通知
 #discussion 包括网络请求失败
 #param message 错误信息
 */
- (BJLObservable)requestServerRecordingDidFailed:(NSString *)message;

@end

NS_ASSUME_NONNULL_END
