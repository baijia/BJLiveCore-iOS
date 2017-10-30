//
//  _LPResRoomUserState.h
//  BJLiveCore
//
//  Created by Randy on 16/3/30.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "_LPResRoomModel.h"

@class _LPRoomUserStateModel;

@interface _LPResRoomUserState : _LPResRoomModel
@property (copy, nonatomic) NSString *userNumber;
@property (strong, nonatomic) _LPRoomUserStateModel *userState;

@end
