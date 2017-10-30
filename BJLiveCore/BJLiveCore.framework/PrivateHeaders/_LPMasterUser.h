//
//  _LPMasterUser.h
//  BJLiveCore
//
//  Created by Randy on 16/4/9.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "_LPUser.h"
#import "_LPDataModel.h"
#import "_LPConstants.h"

@interface _LPMasterUser : _LPUser

@property (nonatomic, assign) BOOL isAbroad;
@property (nonatomic, copy) NSString *userIp;

@end
