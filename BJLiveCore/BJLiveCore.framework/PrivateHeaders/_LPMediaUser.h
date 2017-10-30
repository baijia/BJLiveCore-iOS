//
//  _LPMediaUser.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-04-28.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "_LPRoomUser.h"
#import "_LPIpAddress.h"
#import "_LPResMediaPublish.h"

@interface _LPMediaUser : _LPRoomUser

@property (nonatomic, copy) NSString *classId;
@property (nonatomic, assign) _LPLinkType linkType;
@property (assign, nonatomic) NSInteger publishIndex;
@property (strong, nonatomic) _LPIpAddress *publishServer;

+ (_LPMediaUser *)mediaUserFromMediaPublish:(_LPResMediaPublish *)mediaPublish;

@end
