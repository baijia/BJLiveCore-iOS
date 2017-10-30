//
//  _LPResForbidUserState.h
//  BJLiveCore
//
//  Created by MingLQ on 2017-01-11.
//  Copyright © 2017 Baijia Cloud. All rights reserved.
//

#import "_LPResRoomModel.h"

#import "_LPUser.h"

@interface _LPResForbidUserState : _LPResRoomModel

@property (nonatomic, readonly) _LPUser *fromUser;
@property (nonatomic, readonly, copy) NSString *toUserNumber;

@property (nonatomic, readonly) NSTimeInterval duration;

@end
