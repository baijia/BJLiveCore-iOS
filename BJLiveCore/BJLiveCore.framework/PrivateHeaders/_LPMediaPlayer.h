//
//  _LPMediaPlayer.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-04-26.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <BJHLMediaPlayer/gsx_rtc_types.h>
#import <ReactiveCocoa/ReactiveCocoa.h>

#import "_LPMediaUser.h"
#import "_LPLoginModel.h"
#import "_LPMediaServerModel.h"
#import "_LPLinkInfo.h"

extern NSString * const _LP_DEFAULT_TCP_IP;
extern const NSUInteger _LP_DEFAULT_TCP_PORT;

typedef NS_ENUM(NSInteger, _LPVideoBeautifyLevel) {
    _LPVideoBeautifyLevel0 = BJLVideoBeautifyLevel0,
    _LPVideoBeautifyLevel1 = BJLVideoBeautifyLevel1,
    _LPVideoBeautifyLevel2 = BJLVideoBeautifyLevel2,
    _LPVideoBeautifyLevel3 = BJLVideoBeautifyLevel3,
    _LPVideoBeautifyLevel4 = BJLVideoBeautifyLevel4,
    _LPVideoBeautifyLevel5 = BJLVideoBeautifyLevel5,
    _LPVideoBeautifyLevel_default = BJLVideoBeautifyLevel_default,
    _LPVideoBeautifyLevel_close = BJLVideoBeautifyLevel_close,
    _LPVideoBeautifyLevel_min = BJLVideoBeautifyLevel_min,
    _LPVideoBeautifyLevel_max = BJLVideoBeautifyLevel_max
};

#pragma mark -

@interface _LPMediaPlayerCallback : NSObject

@property (nonatomic, readonly) RTCEngineMsg message;
@property (nonatomic, readonly) int param1, param2;

+ (instancetype)callbackWithMessage:(RTCEngineMsg)message param1:(int)param1 param2:(int)param2;

@end

#pragma mark -

@interface _LPMediaPlayer : NSObject

@property (nonatomic, readonly) NSInteger volumeLevel;
// _LPMediaPlayerCallback *playerCallback
@property (nonatomic, readonly) RACSignal *callbackSignal;

+ (instancetype)playerWithClassID:(NSString *)classID
                             user:(_LPUser *)user
                  myContainerView:(UIView *)myContainerView
               otherContainerView:(UIView *)otherContainerView;
- (void)destroyPlayer;

#pragma mark - config

@property (nonatomic, readonly, copy) NSString *classID;
@property (nonatomic, readonly, strong) _LPUser *user;

- (void)updateClassID:(NSString *)classID
                 user:(_LPUser *)user;

@property (nonatomic, readwrite) _LPLinkType         publishLinkType,    playLinkType;
// tcp
@property (nonatomic, readonly, copy) _LPIpAddress   *tcpPublishServer,  *tcpPlayServer;
@property (nonatomic, readonly) _LPCDNType           tcpPublishCDN,      tcpPlayCDN;
// udp
@property (nonatomic, readonly, copy) _LPIpAddress   *udpPublishServer,  *udpPlayServer;
@property (nonatomic, readonly, copy) NSArray<_LPIpAddress *> *udpPlayServerList;

@property (nonatomic, readonly) NSInteger publishIndex;

- (void)updateWithMasterModel:(_LPLoginModel *)masterModel;

#pragma mark - publish

@property (nonatomic, readonly) BOOL publishing;
// @property (nonatomic, readonly) BOOL publishAudio, publishVideo;

- (void)setPublishAudio:(BOOL)publishAudio publishVideo:(BOOL)publishVideo;

@property (nonatomic, readwrite) BOOL useRearCamera; // iSight Camera
@property (nonatomic, readwrite) _LPVideoCaptureCapability videoCaptureCapability;
@property (nonatomic, readwrite) _LPVideoBeautifyLevel videoBeautifyLevel;

#pragma mark - play

@property (nonatomic, readonly) BOOL playing;

// stopPlaying if no audio or video to play
- (void)updatePlayingForUser:(_LPMediaUser *)user playVideo:(BOOL)playVideo;
- (void)stopPlayingForUser:(_LPMediaUser *)user;
- (void)stopPlayingForAllUsers;

- (void)setPlayUser:(_LPMediaUser *)user playAudioOnly:(BOOL)playAudioOnly DEPRECATED_ATTRIBUTE;
- (void)removePlayUser:(_LPMediaUser *)user DEPRECATED_ATTRIBUTE;
- (void)removeAllPlayUsers DEPRECATED_ATTRIBUTE;

#pragma mark - debug

- (void)addBufferByStep:(NSTimeInterval)step;

@property (nonatomic, readonly, strong) _LPLinkInfo *teacherLinkInfo;
- (_LPLinkInfo *)linkInfoWithUserID:(NSString *)userID;
- (NSArray<_LPLinkInfo *> *)allLinkInfo;
- (NSString *)userIDWithPlayingVid:(NSInteger)vid;

- (NSString *)streamNameWithUser:(_LPMediaUser *)user;
- (NSDictionary *)getStreamInfoWithUser:(_LPMediaUser *)user;
- (NSString *)getDebugInfoWithUser:(_LPMediaUser *)user;

@end
