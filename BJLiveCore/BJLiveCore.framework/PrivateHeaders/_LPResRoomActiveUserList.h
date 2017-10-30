//
//  _LPResRoomActiveUsers.h
//  BJLiveCore
//
//  Created by Randy on 16/3/30.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "_LPResRoomModel.h"

@class _LPMediaUser;

@interface _LPResRoomActiveUserList : _LPResRoomModel
@property (copy, nonatomic) NSArray<_LPMediaUser *> *users;

@end
