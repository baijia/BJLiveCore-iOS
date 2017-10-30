//
//  _LPResMediaPublish.h
//  BJLiveCore
//
//  Created by Randy on 16/3/31.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "_LPResRoomModel.h"

@class _LPMediaServerModel;
@class _LPUser;

@interface _LPResMediaPublish : _LPResRoomModel

@property (strong, nonatomic) _LPMediaServerModel *mediaInfo;
@property (strong, nonatomic) _LPUser *user;

@end
