//
//  _LPLinkInfo.h
//  BJLiveCore
//
//  Created by Randy on 16/5/18.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "_LPDataModel.h"
#import "_LPConstants.h"

@class _LPIpAddress;

@interface _LPLinkInfo : _LPDataModel

@property (nonatomic) _LPLinkType linkType;
@property (nonatomic) NSInteger blockCount;
@property (nonatomic) NSInteger linkIndex;
@property (nonatomic, copy) _LPIpAddress *linkServer;
@property (nonatomic, copy) NSString *streamName;
@property (nonatomic, copy) NSDictionary *streamInfo;

+ (instancetype)upLinkInfo;
+ (instancetype)downLinkInfo;

#pragma mark - local use

@property (nonatomic) NSInteger vid;

#pragma mark - _LPLogStat use

@property (nonatomic, copy) NSString *userNumber;
@property (nonatomic) BJLUserRole userRole;
@property (nonatomic, readonly) BOOL isUpLink;
@property (nonatomic) BOOL audioOn, videoOn;

@end
