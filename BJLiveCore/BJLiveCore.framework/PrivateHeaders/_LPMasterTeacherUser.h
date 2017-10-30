//
//  _LPMasterTeacherUser.h
//  BJLiveCore
//
//  Created by Randy on 16/4/9.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "_LPDataModel.h"

@interface _LPMasterTeacherUser : _LPDataModel

@property (nonatomic, copy) NSString *avatar;
@property (nonatomic, assign) BOOL cloudPlayback;
@property (nonatomic, copy) NSString *displayName;
@property (nonatomic, assign) BOOL hasMobile;
@property (nonatomic, assign) BOOL playback;
@property (nonatomic, copy) NSString *nickName;
@property (nonatomic, copy) NSString *number;
@property (nonatomic, assign) BJLUserRole type;
@property (nonatomic, copy) NSString *userId;

@end
