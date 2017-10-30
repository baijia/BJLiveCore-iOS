//
//  _LPResMediaSpeakApply.h
//  BJLiveCore
//
//  Created by Randy on 16/3/31.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "_LPResRoomModel.h"
#import "_LPConstants.h"

@class _LPUser;

@interface _LPResMediaSpeakApply : _LPResRoomModel
@property (strong, nonatomic) _LPUser *user;
@property (assign, nonatomic) _LPSpeakState speakState;

@end
