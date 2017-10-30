//
//  _LPRoomResponseModel.h
//  BJLiveCore
//
//  Created by Randy on 16/3/30.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "_LPDataModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface _LPResRoomModel : _LPDataModel
@property (copy, nonatomic) NSString *classId;
@property (copy, nonatomic) NSString *userId;
@property (copy, nonatomic) NSString *messageType;

@end

NS_ASSUME_NONNULL_END
