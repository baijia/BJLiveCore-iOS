//
//  _LPUserModel.h
//  BJLiveCore
//
//  Created by Randy on 16/3/30.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "_LPResRoomModel.h"
NS_ASSUME_NONNULL_BEGIN

@class _LPRoomForbidModel;

@interface _LPRoomUserStateModel : _LPResRoomModel
@property (strong, nonatomic) _LPRoomForbidModel *forbid;

@end

NS_ASSUME_NONNULL_END
