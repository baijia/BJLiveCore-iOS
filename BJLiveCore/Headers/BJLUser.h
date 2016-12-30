//
//  BJLUser.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-11-15.
//
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

@protocol BJLUser <NSObject>

@property (nonatomic, readonly) NSString *number, *name, *ID;
@property (nonatomic, readonly, nullable) NSString *avatar;
@property (nonatomic, readonly) BJLUserRole role;

@property (nonatomic, readonly) BOOL isTeacher, isStudent, isAssistant, isGuest;
@property (nonatomic, readonly) BOOL isManager; // isTeacher || isAssistant

@end

@protocol BJLOnlineUser <BJLUser>

@property (nonatomic, readonly) BOOL audioOn, videoOn;

@end

/* 
@protocol BJLSpeakingUser <BJLOnlineUser>

@property (nonatomic, readonly) NSString *classID;
@property (nonatomic, readonly) LPLinkType linkType;
@property (nonatomic, readonly) NSInteger publishIndex;
@property (nonatomic, readonly) LPIpAddress *publishServer;

@end // */

#pragma mark -

@interface BJLUser : NSObject <BJLUser, YYModel>

+ (instancetype)userWithNumber:(NSString *)number
                          name:(NSString *)name
                        avatar:(nullable NSString *)avatar
                          role:(BJLUserRole)role;

@end

NS_ASSUME_NONNULL_END
