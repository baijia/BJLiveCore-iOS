//
//  _LPError.h
//  BJLiveCore
//
//  Created by 杨磊 on 16/4/13.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "_LPErrorCodeDefines.h"

NS_ASSUME_NONNULL_BEGIN

@interface _LPError : NSObject<NSCopying>

@property (nonatomic, assign) _LPErrorCode code;
@property (nonatomic, copy)  NSString *message;
@property (nonatomic, copy, readonly) NSString *errorDetail;

+ (instancetype)errorWithCode:(_LPErrorCode)code;
+ (instancetype)errorWithCode:(_LPErrorCode)code exception:(nullable NSException *)exception;
+ (instancetype)errorWithCode:(_LPErrorCode)code error:(nullable NSError *)nserror;
+ (instancetype)errorWithCode:(_LPErrorCode)code message:(NSString *)message;
+ (NSString *)messageWithCode:(_LPErrorCode)code;

@end

NS_ASSUME_NONNULL_END
