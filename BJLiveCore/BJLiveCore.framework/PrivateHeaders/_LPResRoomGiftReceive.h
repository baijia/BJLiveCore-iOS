//
//  _LPResRoomGIftReceive.h
//  BJLiveCore
//
//  Created by Randy on 16/3/30.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "_LPResRoomModel.h"

@class _LPUser;
@class _LPGiftModel;

@interface _LPResRoomGiftReceive : _LPResRoomModel
@property (strong, nonatomic) _LPUser *from;
@property (strong, nonatomic) _LPUser *to;
@property (strong, nonatomic) _LPGiftModel *gift;

@end
