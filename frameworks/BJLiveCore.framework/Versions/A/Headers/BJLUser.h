//
//  BJLUser.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-11-15.
//  Copyright © 2016 BaijiaYun. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "BJLConstants.h"

NS_ASSUME_NONNULL_BEGIN

/** 用户 */
@interface BJLUser : NSObject

@property (nonatomic, readonly) NSString *number, *name, *ID;
@property (nonatomic, readonly, nullable) NSString *avatar;
@property (nonatomic, readonly) BJLUserRole role;
@property (nonatomic, readonly) BJLClientType clientType;
@property (nonatomic, readonly) BJLOnlineState onlineState;

@property (nonatomic, readonly) BOOL audioOn, videoOn; // 作为登录用户、在线用户时一直是 NO

@property (nonatomic, readonly) BOOL isTeacher, isStudent, isAssistant, isGuest;
@property (nonatomic, readonly) BOOL isTeacherOrAssistant;

- (BOOL)isSameUser:(BJLUser *)user;
- (BOOL)isSameUserWithID:(nullable NSString *)userID number:(nullable NSString *)userNumber;

+ (instancetype)userWithNumber:(NSString *)number
                          name:(NSString *)name
                        avatar:(nullable NSString *)avatar
                          role:(BJLUserRole)role;

@end

@compatibility_alias BJLOnlineUser BJLUser;

NS_ASSUME_NONNULL_END
