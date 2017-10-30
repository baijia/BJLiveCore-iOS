//
//  _LPLogLinkInfo.h
//  BJLiveCore
//
//  Created by Randy on 16/5/25.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "_LPConstants.h"

@class _LPLinkInfo, _LPIpAddress;

@interface _LPLogLinkInfo : NSObject

@property (assign, nonatomic) NSInteger linkType;//0：上行 1：下行
@property (assign, nonatomic) NSInteger useUDP;//0：未使用 1：使用
@property (assign, nonatomic) NSInteger avType;//0：音频 1：合流
@property (strong, nonatomic) _LPIpAddress *address;
@property (copy, nonatomic) NSString *fromNumber;//只有下行需要
@property (assign, nonatomic) BJLUserRole fromRole;//只有下行需要
@property (assign, nonatomic) NSInteger blockCount;

@property (strong, nonatomic) _LPIpAddress *oldAddress;//切换链路的时候 ，旧的链路信息

+ (instancetype)logLinkInfoWithLinkInfo:(_LPLinkInfo *)linkInfo;
+ (NSArray<_LPLogLinkInfo *> *)logLinkInfoArrayWithLinkInfoArray:(NSArray<_LPLinkInfo *> *)allLinkInfo;

@end
