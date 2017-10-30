//
//  _LPMediaPlayer+control.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-04-27.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "_LPMediaPlayer.h"

typedef struct _LPSwitchConfig {
    int firstSwitchLimit, firstSwitchOffset, playSwitchLimit, playSwitchOffset;
} _LPSwitchConfig;

static inline _LPSwitchConfig _LPSwitchConfigMake(int firstSwitchLimit,
                                                int firstSwitchOffset,
                                                int playSwitchLimit,
                                                int playSwitchOffset) {
    return (_LPSwitchConfig){firstSwitchLimit, firstSwitchOffset, playSwitchLimit, playSwitchOffset};
}

#pragma mark -

@interface _LPMediaPlayer (control)

@property (nonatomic, readonly) UIView *myPlayerView, *otherPlayerView;

#pragma mark - setup & config

- (void)setupPlayer;
- (void)teardownPlayer;

- (void)updateLocalUser;
- (void)updateSwitchConfig:(_LPSwitchConfig)switchConfig;
- (void)updatePlayingBuffer:(NSTimeInterval)seconds;

- (NSDictionary *)getStreamInfoWithUserID:(NSString *)userID streamName:(NSString *)streamName;
- (NSString *)getDebugInfoWithUserID:(NSString *)userID streamName:(NSString *)streamName;

#pragma mark - play

/**
 * playAV - 播放音视频
 @param  userID
 @param  playVideo
 @param  streamName
 @param  playURL          - for both TCP & UDP
 @param  userPublishIP    - for UDP only
 @param  userPublishPort  - for UDP only
 */
// - (void)toPlayAV:(NSDictionary *)payload;
- (int)playWithUserID:(int)userID
            playVideo:(BOOL)playVideo
           streamName:(NSString *)streamName
              playURL:(NSString *)playURL
        userPublishIP:(NSString *)userPublishIP
      userPublishPort:(NSUInteger)userPublishPort;
/**
 * playAVRelease - 销毁播放音视频的链路
 */
// - (void)toPlayAVRelease:(NSDictionary *)payload;
- (void)playReleaseWithStreamName:(NSString *)streamName;

#pragma mark - publish

/**
 * publishAV - 发布音视频
 * @param {string} options.streamName 需要发布的流名称
 * @param {string} options.publishIp 发布到的 live server
 * @param {number} options.publishPort 发布到的 live server
 */
// - (void)toPublishAV:(NSDictionary *)payload;
/* publishIp:(NSString *)publishIp
 * publishPort:(NSUInteger)publishPort */
- (void)publishWithStreamName:(NSString *)streamName
                   publishURL:(NSString *)publishURL;
/**
 * publishAVRelease - 停止发布音视频
 */
// - (void)toPublishAVRelease:(NSDictionary *)payload;
- (void)publishRelease;

- (void)attachAudio;
- (void)detachAudio;

- (void)attachVideo;
- (void)detachVideo;
- (void)switchCamera;
- (void)updateVideoBeautifyLevel;

@end
