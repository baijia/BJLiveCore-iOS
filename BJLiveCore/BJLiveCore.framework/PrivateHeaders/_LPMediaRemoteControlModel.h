//
//  _LPMediaRemoteControlModel.h
//  BJLiveCore
//
//  Created by Randy on 16/3/31.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "_LPDataModel.h"
#import "_LPConstants.h"

@interface _LPMediaRemoteControlModel : _LPDataModel
@property (strong, nonatomic) NSNumber *videoOn;
@property (strong, nonatomic) NSNumber *audioOn;
@property (assign, nonatomic) _LPSpeakState state;

@end
