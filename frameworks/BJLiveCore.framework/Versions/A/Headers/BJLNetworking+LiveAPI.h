//
//  BJLNetworking+LiveAPI.h
//  BJLiveCore
//
//  Created by MingLQ on 2017-09-05.
//  Copyright © 2017 Baijia Cloud. All rights reserved.
//

#import <BJLiveBase/BJLNetworking.h>

NS_ASSUME_NONNULL_BEGIN

#define BJLNETWORKING [BJLNetworking bjl_liveManager]

@interface BJLNetworking (LiveAPI)

+ (instancetype)bjl_liveManager;

@end

#pragma mark -

typedef NS_ENUM(NSInteger, BJLResponseCode) {
    BJLResponseCodeSuccess = 0,
    BJLResponseCodeFailure = 1
};

@interface BJLJSONResponse : NSObject <BJLResponse>

@property (nonatomic, readonly) BJLResponseCode code;
@property (nonatomic, readonly, nullable) NSString *message;

@property (nonatomic, readonly) NSTimeInterval timestamp;
@property (nonatomic, readonly, nullable) NSDictionary *data;

@end

@interface BJLMutableJSONResponse : BJLJSONResponse

// isSuccess, responseObject: readonly, dynamic

@property (nonatomic, readwrite) BJLResponseCode code;
@property (nonatomic, readwrite, nullable) NSString *message;

@property (nonatomic, readwrite) NSTimeInterval timestamp;
@property (nonatomic, readwrite, nullable) NSDictionary *data;
@property (nonatomic, readwrite, nullable) NSError *error;

@end

NS_ASSUME_NONNULL_END
