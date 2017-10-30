//
//  _LPIpAddress.h
//  BJLiveCore
//
//  Created by 杨磊 on 16/3/24.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "_LPDataModel.h" 

/**
 *  地址数据
 */
@interface _LPIpAddress : _LPDataModel

#pragma mark - 通用字段
@property (nonatomic, copy) NSString *ipAddr;
@property (nonatomic, assign) NSUInteger port;

@end

static inline _LPIpAddress *_LPIpAddressMake(NSString *ip, NSUInteger port) {
    _LPIpAddress *ipAddress = [_LPIpAddress new];
    ipAddress.ipAddr = ip;
    ipAddress.port = port;
    return ipAddress;
}
