//
//  _LPResCommandModel.h
//  BJLiveCore
//
//  Created by Randy on 16/5/18.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "_LPDataModel.h"

@class _LPUser, _LPResCommandModel;

@interface _LPResCommandModel : _LPDataModel
@property (copy, nonatomic) NSString *messageType;
@property (copy, nonatomic) NSString *commandType;
@property (copy, nonatomic) NSDictionary *data;
@property (copy, nonatomic) NSString *from;

- (instancetype)initWithCommandModel:(_LPResCommandModel *)model;

@end
