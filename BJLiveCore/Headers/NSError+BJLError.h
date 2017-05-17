//
//  NSError+BJLError.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-11-30.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 BJLError 可用属性
 .domain                    BJLErrorDomain
 .code                      BJLErrorCode - 错误码
 .localizedDescription      NSString * - 错误描述
 .localizedFailureReason    NSString * - 错误原因，可能为空 - TODO: 干掉，如果有具体错误信息则替换调默认的错误描述
 .bjl_sourceError           NSError * - 引起当前错误的错误，可能为空
 TODO: server errorCode, message
 */
@protocol BJLError <NSObject>

@property (nonatomic, readonly, nullable) NSError *bjl_sourceError;

@end

typedef NSError<BJLError> BJLError;

#pragma mark -

extern const NSErrorDomain BJLErrorDomain;

extern NSString * const BJLErrorSourceErrorKey;

typedef NS_ENUM(NSInteger, BJLErrorCode) {
    BJLErrorCode_success = 0,       // 成功
    /* common */
    BJLErrorCode_networkError,      // 网络请求出错
    BJLErrorCode_cancelled,         // 主动调用取消
    BJLErrorCode_invalidUserRole,   // 非法用户角色
    BJLErrorCode_invalidCalling,    // 非法调用
    BJLErrorCode_invalidArguments,  // 参数错误
    BJLErrorCode_areYouRobot,       // 操作过于频繁
    /* enter & exit room */
    BJLErrorCode_enterRoom_roomIsFull,      // 房间已满
    BJLErrorCode_exitRoom_disconnected,     // 连接断开
    BJLErrorCode_exitRoom_loginConflict,    // 用户在其它设备登录
    /* !!!: 
     1、在此之前增加错误码；
     2、不要设置错误码取值；
     3、同步增删 BJLErrorDescriptions； */
    BJLErrorCode_unknown    // 未知错误
};

extern NSString * const BJLErrorDescription_unknown;
extern NSString * _Nonnull const BJLErrorDescriptions[];

static inline BJLError * _Nullable BJLErrorMakeFromError(BJLErrorCode errorCode, NSString * _Nullable reason, NSError * _Nullable sourceError) {
    if (errorCode == BJLErrorCode_success) {
        return nil;
    }
    BJLErrorCode titleIndex = (BJLErrorCode)MIN(MAX(0, errorCode), BJLErrorCode_unknown);
    NSMutableDictionary *userInfo = [NSMutableDictionary new];
    [userInfo setObject:BJLErrorDescriptions[titleIndex] ?: BJLErrorDescription_unknown forKey:NSLocalizedDescriptionKey];
    if (reason) {
        [userInfo setObject:reason forKey:NSLocalizedFailureReasonErrorKey];
    }
    if (sourceError) {
        [userInfo setObject:sourceError forKey:BJLErrorSourceErrorKey];
    }
    return (BJLError *)[NSError errorWithDomain:BJLErrorDomain code:errorCode userInfo:userInfo];
}

static inline BJLError * _Nullable BJLErrorMake(BJLErrorCode errorCode, NSString * _Nullable reason) {
    return BJLErrorMakeFromError(errorCode, reason, nil);
}

#define bjl_isRobot(LIMIT) ({ \
    static NSTimeInterval LAST = 0; \
    NSTimeInterval NOW = [NSDate timeIntervalSinceReferenceDate]; \
    BOOL isRobot = NOW - LAST < LIMIT; \
    if (!isRobot) { \
        LAST = NOW; \
    } \
    isRobot; \
})

#define bjl_returnIfRobot(LIMIT) { \
    static NSTimeInterval LAST = 0; \
    NSTimeInterval NOW = [NSDate timeIntervalSinceReferenceDate]; \
    if (NOW - LAST < LIMIT) { \
        return; \
    } \
    LAST = NOW; \
}

#define bjl_returnErrorIfRobot(LIMIT) { \
    static NSTimeInterval LAST = 0; \
    NSTimeInterval NOW = [NSDate timeIntervalSinceReferenceDate]; \
    if (NOW - LAST < LIMIT) { \
        return BJLErrorMake(BJLErrorCode_areYouRobot, \
                            [NSString stringWithFormat:@"每%.1f秒只能操作1次", LIMIT]); \
    } \
    LAST = NOW; \
}

NS_ASSUME_NONNULL_END
