//
//  _LPRunTimeInfo.h
//  BJLiveCore
//
//  Created by Randy on 16/5/18.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "_LPDataModel.h"

@class _LPNetworkConfig;
@class _LPIpAddress;

@interface _LPRunTimeInfo : _LPDataModel
@property (assign, nonatomic) NSInteger base;
@property (strong, nonatomic) _LPNetworkConfig *config;
@property (copy, nonatomic) NSString *ip;
@property (strong, nonatomic) _LPIpAddress *masterServer;
@property (strong, nonatomic) _LPIpAddress *roomServer;
@property (strong, nonatomic) _LPIpAddress *chatServer;

@end
