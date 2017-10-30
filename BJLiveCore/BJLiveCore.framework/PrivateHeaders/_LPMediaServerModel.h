//
//  _LPMediaServerModel.h
//  BJLiveCore
//
//  Created by Randy on 16/3/31.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "_LPDataModel.h"
#import "_LPIpAddress.h"

NS_ASSUME_NONNULL_BEGIN

@interface _LPMediaServerModel : _LPDataModel
@property (strong, nullable, nonatomic) NSNumber *videoOn;
@property (strong, nullable, nonatomic) NSNumber *audioOn;
@property (strong, nonatomic) _LPIpAddress *publishServer;
@property (assign, nonatomic) NSInteger publishIndex;
@property (nonatomic, assign) _LPLinkType linkType;

@end

NS_ASSUME_NONNULL_END
