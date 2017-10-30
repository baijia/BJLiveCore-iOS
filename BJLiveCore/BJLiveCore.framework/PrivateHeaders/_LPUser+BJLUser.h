//
//  _LPUser+BJLUser.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-12-05.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "_LPUser.h"
#import "_LPMasterUser.h"
#import "_LPRoomUser.h"

#import "BJLUser.h"

// also _LPMasterUser
@interface _LPUser (BJLUser) <BJLUser>

@end

@interface _LPRoomUser (BJLUser) <BJLOnlineUser>

@end

// _LPMediaUser?
