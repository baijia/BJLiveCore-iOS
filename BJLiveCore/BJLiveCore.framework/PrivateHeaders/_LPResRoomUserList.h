//
//  _LPResRoomUserList.h
//  BJLiveCore
//
//  Created by Randy on 16/3/30.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "_LPResRoomModel.h"

@class _LPRoomUser;

@interface _LPResRoomUserList : _LPResRoomModel
@property (copy, nonatomic) NSArray<_LPRoomUser *> *users;
@property (assign, nonatomic) BOOL hasMore;

@end
