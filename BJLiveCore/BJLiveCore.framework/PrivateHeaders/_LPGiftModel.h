//
//  _LPGiftModel.h
//  BJLiveCore
//
//  Created by Randy on 16/3/30.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "_LPDataModel.h"
#import "_LPLivePlayerConstants.h"

@interface _LPGiftModel : _LPDataModel

@property (assign, nonatomic) _LPGiftType type;
@property (copy, nonatomic) NSString *amount;
@property (assign, nonatomic) NSTimeInterval timestamp;

@property (copy, nonatomic) NSString *name;

@end
