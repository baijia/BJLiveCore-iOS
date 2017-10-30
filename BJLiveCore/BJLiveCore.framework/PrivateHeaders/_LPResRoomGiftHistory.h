//
//  _LPResRoomGiftHistory.h
//  BJLiveCore
//
//  Created by Randy on 16/3/31.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "_LPResRoomModel.h"

@class _LPGiftMessageModel;

@interface _LPResRoomGiftHistory : _LPResRoomModel
@property (strong, nonatomic) NSArray<_LPGiftMessageModel *> *gifts;

@end
