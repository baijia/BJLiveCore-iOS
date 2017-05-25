//
//  BJLUser.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-11-15.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <YYModel/YYModel.h>

#import "BJLConstants.h"

NS_ASSUME_NONNULL_BEGIN

/**
 BJLUser: 当前登录用户
 BJLOnlineUser: 教室内在线用户
 BJLSpeakingUser: 发言用户
 */

@interface BJLUser : NSObject <YYModel>

@property (nonatomic, readonly) NSString *number, *name, *ID;
@property (nonatomic, readonly, nullable) NSString *avatar;
@property (nonatomic, readonly) BJLUserRole role;
@property (nonatomic, readonly) BJLClientType clientType;
@property (nonatomic, readonly) BJLOnlineState onlineState;

@property (nonatomic, readonly) BOOL isTeacher, isStudent, isAssistant, isGuest;
@property (nonatomic, readonly) BOOL isTeacherOrAssistant;

+ (instancetype)userWithNumber:(NSString *)number
                          name:(NSString *)name
                        avatar:(nullable NSString *)avatar
                          role:(BJLUserRole)role;

@end

#pragma mark -

@interface BJLOnlineUser : BJLUser

@property (nonatomic, readonly) BOOL audioOn, videoOn;

@end

#pragma mark -

/* 
@interface BJLSpeakingUser : BJLOnlineUser

@property (nonatomic, readonly) NSString *classID;
@property (nonatomic, readonly) BJLLinkType linkType;
@property (nonatomic, readonly) NSInteger publishIndex;
@property (nonatomic, readonly) BJLServerAddress *publishServer;

@end // */

NS_ASSUME_NONNULL_END
