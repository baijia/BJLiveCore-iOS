//
//  _LPGiftMessage.h
//  BJLiveCore
//
//  Created by Randy on 16/3/31.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "_LPDataModel.h"

@class _LPGiftModel;
@class _LPUser;

@interface _LPGiftMessageModel : _LPDataModel
@property (strong, nonatomic) _LPGiftModel *gift;
@property (strong, nonatomic) _LPUser *from;
@property (strong, nonatomic) _LPUser *to;//to为nil是发送给自己的

@end
