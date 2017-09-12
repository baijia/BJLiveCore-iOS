//
//  BJLUserAgent.h
//  BJLiveCore
//
//  Created by MingLQ on 2017-08-28.
//  Copyright © 2017 Baijia Cloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface BJLUserAgent : NSObject

@property (nonatomic, readonly) NSString *sdkUserAgent;
- (NSString *)userAgentWithDefault:(nullable NSString *)defaultUserAgent;

- (void)regitsterSDK:(NSString *)name version:(NSString *)version;
- (void)regitsterSDK:(NSString *)name version:(NSString *)version description:(nullable NSString *)description;

+ (instancetype)defaultInstance;

@end

NS_ASSUME_NONNULL_END
