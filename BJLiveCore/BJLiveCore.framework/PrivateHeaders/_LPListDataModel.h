//
//  _LPListDataModel.h
//  BJLiveCore
//
//  Created by Randy on 16/4/12.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "_LPDataModel.h"

@class BJCKPageModel;

@interface _LPListDataModel : _LPDataModel
@property (strong, nonatomic) NSArray *list;
@property (strong, nonatomic) BJCKPageModel *pageModel;

@end
