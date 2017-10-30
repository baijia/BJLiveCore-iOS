//
//  _LPResRoomUserIn.h
//  BJLiveCore
//
//  Created by Randy on 16/3/30.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "_LPResRoomModel.h"

@class _LPRoomUser;

@interface _LPResRoomUserIn : _LPResRoomModel
@property (assign, nonatomic) BOOL overrideIn;//覆盖进入
@property (strong, nonatomic) _LPRoomUser *user;

@end
