//
//  _LPLivePlayerInfoModel.h
//  BJLiveCore
//
//  Created by Randy on 16/3/29.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "_LPDataModel.h"

@class _LPMasterUser;
@class _LPMasterTeacherUser;
@class _LPClassModel;

@interface _LPLivePlayerInfoModel : _LPDataModel
@property (strong, nonatomic) NSDictionary *user;
@property (strong, nonatomic) _LPMasterTeacherUser *teacher;
@property (strong, nonatomic) _LPClassModel *classData;

@end
