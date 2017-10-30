//
//  _LPRoomForbidModel.h
//  BJLiveCore
//
//  Created by Randy on 16/3/30.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "_LPDataModel.h"

@class _LPUser;

NS_ASSUME_NONNULL_BEGIN

@interface _LPRoomForbidModel : _LPDataModel
@property (strong, nonatomic) _LPUser *from;
@property (assign, nonatomic) NSTimeInterval dration;

@end

NS_ASSUME_NONNULL_END
