//
//  NSError+BJLError.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-11-30.
//
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 BJLError 可用属性
 .domain                    BJLErrorDomain
 .code                      BJLErrorCode - 错误码
 .localizedDescription      BJLErrorDescriptions[BJLErrorCode] - 错误描述
 .localizedFailureReason    NSString *reason - 错误原因，可能为空
 .bjl_sourceError           NSError * - 引起当前错误的错误，可能为空
 */
@protocol BJLError <NSObject>

@property (nonatomic, readonly) NSError *bjl_sourceError;

@end

typedef NSError<BJLError> BJLError;

#pragma mark -

extern NSErrorDomain const BJLErrorDomain;

extern NSString * const BJLErrorSourceErrorKey;

typedef NS_ENUM(NSInteger, BJLErrorCode) {
    BJLErrorCode_success = 0,
    /* common */
    BJLErrorCode_networkError,
    BJLErrorCode_cancelled,
    BJLErrorCode_invalidUserRole,
    BJLErrorCode_invalidCalling,
    BJLErrorCode_invalidArguments,
    BJLErrorCode_areYouRobot,
    /* exit room */
    BJLErrorCode_exitRoom_enterRoomFailed,
    BJLErrorCode_exitRoom_anotherRoomEntered,
    BJLErrorCode_exitRoom_exitRoom,
    BJLErrorCode_exitRoom_loginConflict,
    /* !!!: 
     1、在此之前增加错误码；
     2、不要手动指定错误码；
     3、同步增删 BJLErrorDescriptions； */
    BJLErrorCode_unknown
};

extern NSString * const BJLErrorDescriptions[];

NS_INLINE BJLError * _Nullable BJLErrorMakeFromError(BJLErrorCode errorCode, NSString * _Nullable reason, NSError * _Nullable sourceError) {
    if (errorCode == BJLErrorCode_success) {
        return nil;
    }
    BJLErrorCode titleIndex = MIN(MAX(0, errorCode), BJLErrorCode_unknown);
    NSMutableDictionary *userInfo = [NSMutableDictionary new];
    [userInfo setObject:BJLErrorDescriptions[titleIndex] forKey:NSLocalizedDescriptionKey];
    if (reason) {
        [userInfo setObject:reason forKey:NSLocalizedFailureReasonErrorKey];
    }
    if (sourceError) {
        [userInfo setObject:sourceError forKey:BJLErrorSourceErrorKey];
    }
    return (BJLError *)[NSError errorWithDomain:BJLErrorDomain code:errorCode userInfo:userInfo];
}

NS_INLINE BJLError * _Nullable BJLErrorMake(BJLErrorCode errorCode, NSString * _Nullable reason) {
    return BJLErrorMakeFromError(errorCode, reason, nil);
}

#define BJLError_static_returnIfRobot(LIMIT) { \
    static NSTimeInterval LAST = 0; \
    BJLError_returnIfRobot(LAST, LIMIT); \
}

#define BJLError_returnIfRobot(LAST, LIMIT) { \
    NSTimeInterval NOW = [NSDate timeIntervalSinceReferenceDate]; \
    if (NOW - LAST < LIMIT) { \
        return BJLErrorMake(BJLErrorCode_areYouRobot, \
                            [NSString stringWithFormat:@"每%.1f秒只能操作1次", LIMIT]); \
    } \
    LAST = NOW; \
}

NS_ASSUME_NONNULL_END
