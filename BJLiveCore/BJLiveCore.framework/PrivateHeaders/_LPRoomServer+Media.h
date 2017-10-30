//
//  _LPRoomServer+Media.h
//  BJLiveCore
//
//  Created by 杨磊 on 16/3/30.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "_LPRoomServer.h"
#import "_LPResMediaPublish.h"
#import "_LPResMediaRePublish.h"
#import "_LPResMediaRemoteControl.h"
#import "_LPResMediaSpeakApply.h"

@class _LPMediaServerModel;
@class _LPMediaRemoteControlModel;

@interface _LPRoomServer () {
    id _prevMediaPublishTriggerObject;
}
@end

/**
 *  多媒体相关信令服务
 */
@interface _LPRoomServer (Media)

/**d
 *  音视频信息发布
 */
- (void)requestMediaPublishTriggerWithMediaServer:(_LPMediaServerModel *)mediaServer
                                           user:(_LPUser *)user;
/**
 *  _LPResMediaPublish
 *
 *  @return
 */
- (RACSignal *)signalOfMediaPublish;

/**
 *  音视频信息重新发布
 */
- (void)requestMediaRePublishTriggerWithMediaServer:(_LPMediaServerModel *)mediaServer
                                           user:(_LPUser *)user;
/**
 *  _LPResMediaRePublish
 *
 *  @return
 */
- (RACSignal *)signalOfMediaRePublish;

/**
 *  关闭学生音视频
 */
- (void)requestMediaRemoteControl:(_LPMediaRemoteControlModel *)control
                             user:(_LPUser *)user;
/**
 *  _LPResMediaRemoteControl
 *
 *  @return
 */
- (RACSignal *)signalOfMediaRemoteControl;

/**
 *  申请发言
 */
- (void)requestMediaSpeakApplyAskWithUser:(_LPUser *)user;
/**
 *  _LPResMediaSpeakApply
 *
 *  @return
 */
- (RACSignal *)signalOfMediaSpeakApplyAsk;

/**
 *  允许/拒绝发言
 */
- (void)requestMediaSpeakApplyAllow:(BOOL)allow user:(_LPUser *)user;
/**
 *  _LPResMediaSpeakApply
 *
 *  @return
 */
- (RACSignal *)signalOfMediaSpeakApplyAllow;

@end
