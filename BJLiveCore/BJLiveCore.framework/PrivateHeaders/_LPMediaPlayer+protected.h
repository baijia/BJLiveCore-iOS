//
//  _LPMediaPlayer+protected.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-04-27.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import <BJHLMediaPlayer/MPRtcView.h>
#import "NSObject+BJL_M9Dev.h"

#import "_LPMediaPlayer.h"

// @compatibility_alias RTCViewManager RTCView;

@interface _LPMediaPlayer () {
@protected
    
    int _videoPlayId;
    
    bool _isAudioRecording, _isVideoRecording;
    bool _isAudioInterrupt, _isVideoInterrupt;
    bool _isRenderVideo;
    
    NSValue *_rtcEngine;
    MPRtcView *_rtcViewManager;
    NSMutableDictionary *_liveIds;
    
    RACSubject *_callbackSubject;
}

+ (instancetype)currentPlayer;

@property (nonatomic, readwrite) NSInteger volumeLevel;

@property (nonatomic, strong) UIView *myContainerView, *otherContainerView;

@end
