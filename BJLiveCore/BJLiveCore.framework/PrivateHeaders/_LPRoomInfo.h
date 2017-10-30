//
//  _LPRoomInfo.h
//  BJLiveCore
//
//  Created by 杨磊 on 16/4/29.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "_LPDataModel.h"

#import "_LPLivePlayerConstants.h"

@interface _LPRoomInfo : _LPDataModel

@property (copy, nonatomic) NSString *roomId;
@property (copy, nonatomic) NSString *title;
@property (assign , nonatomic) NSTimeInterval startTime;
@property (assign , nonatomic) NSTimeInterval endTime;
@property (nonatomic, assign) _LPClassType classType;
@property (nonatomic, assign) _LPMediaType mediaType;

@property (copy, nonatomic) NSString *partnerId;
@property (copy, nonatomic) NSString *masterIp;
@property (nonatomic) NSInteger masterPort;
@property (copy, nonatomic) NSArray<NSDictionary *> *masterProxies;
@property (nonatomic, readonly) BOOL isGSX; // TODO: MingLQ - should NOT be here

@property (copy, nonatomic) NSString *cover; // 啥
@property (nonatomic, copy) NSString *adminCode;
@property (nonatomic, copy) NSString *teacherCode;
@property (nonatomic, copy) NSString *userCode;

@end
