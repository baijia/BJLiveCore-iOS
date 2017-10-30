//
//  _LPLoginModel.h
//  BJLiveCore
//
//  Created by 杨磊 on 16/3/28.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "_LPDataModel.h"
#import "_LPIpAddress.h"
#import "_LPConstants.h"

/**
 *  直播网络配置
 */

@interface _LPNetworkConfig : _LPDataModel

@property (nonatomic, assign) _LPCDNType cdn; // 目前不支持设置 CDN，因此 playCDN 和 publishCDN 一样
@property (nonatomic, assign) _LPLinkType upLinkType;
@property (nonatomic, assign) _LPLinkType downLinkType;

@end

#pragma mark -

@interface _LPLoginModel : _LPDataModel

@property (nonatomic, strong) _LPIpAddress *chatServer;
@property (nonatomic, strong) NSArray<_LPIpAddress *> *chatServerProxyList;

@property (nonatomic, strong) _LPIpAddress *roomServer;
@property (nonatomic, strong) NSArray<_LPIpAddress *> *roomServerProxyList;

@property (nonatomic, copy) NSString *userId;
@property (nonatomic, copy) NSString *userIp;

@property (nonatomic, strong) _LPNetworkConfig *config;
@property (nonatomic, strong) NSArray<_LPIpAddress *> *downlinkServerList;
@property (nonatomic, strong) NSArray<_LPIpAddress *> *uplinkServerList;

@end
