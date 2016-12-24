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
 上课状态下才能录课 */
// TODO: MingLQ - request can record
- (nullable BJLError *)requestServerRecording:(BOOL)on;

@end

NS_ASSUME_NONNULL_END
