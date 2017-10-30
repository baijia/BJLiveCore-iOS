//
//  _LPResCommandUpLink.h
//  BJLiveCore
//
//  Created by Randy on 16/5/18.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "_LPResCommandModel.h"

@class _LPIpAddress;

@interface _LPResCommandLinkInfo : _LPResCommandModel
@property (strong, nonatomic) _LPIpAddress *server;

@end
