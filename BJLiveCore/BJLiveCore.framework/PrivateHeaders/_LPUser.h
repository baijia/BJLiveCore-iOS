//
//  _LPUser.h
//  BJLiveCore
//
//  Created by 杨磊 on 16/3/28.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "_LPDataModel.h"
#import "_LPConstants.h"

@interface _LPUser : _LPDataModel

@property (nonatomic, copy) NSString *userId;
@property (nonatomic, copy) NSString *number;
@property (nonatomic, assign) BJLUserRole type;
@property (nonatomic, copy) NSString *name;
@property (nonatomic, copy) NSString *avatar;
@property (nonatomic, assign) _LPUserOnlineStatus onlineStatus;
@property (nonatomic, assign) _LPEndType endType;

@property (nonatomic, readonly, assign) BOOL isTeacher, isStudent, isAssistant, isGuest, isManager;

@end
