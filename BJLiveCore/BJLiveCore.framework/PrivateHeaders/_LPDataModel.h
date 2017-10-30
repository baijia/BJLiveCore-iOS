//
//  _LPDataModel.h
//  BJLiveCore
//
//  Created by Randy on 16/3/23.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import <BJHL-Foundation-iOS/BJHL-Foundation-iOS.h>
#import <YYModel/YYModel.h>
#import "NSObject+BJL_M9Dev.h"
#import "_LPConstants.h"

@interface _LPDataModel : NSObject <YYModel, NSCopying, NSCoding>

+ (instancetype)modelWithDictionary:(NSDictionary *)dictionaryValue;

+ (NSDictionary *)JSONKeyPathsByPropertyKey;
- (void)mergeValuesForKeysFromModel:(id)model;

@end
