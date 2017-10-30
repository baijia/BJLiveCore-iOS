//
//  _LPAppConfig.h
//
//  Created by Randy on 16/3/21.
//  Copyright © 2016年 Randy. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#define _LPAppConfigInstance [_LPAppConfig sharedInstance]

@interface _LPAppConfig : NSObject

/**
 *  设备信息
 */
@property (nonatomic, copy, readonly) NSString *systemName;
@property (nonatomic, copy, readonly) NSString *systemVersion;
@property (nonatomic, copy, readonly) NSString *deviceUUID;

/**
 *  应用信息
 */
@property (nonatomic, copy, readonly) NSString *appVersion;
@property (nonatomic, copy, readonly) NSString *appKey;
@property (nonatomic, assign, readonly) int16_t appType;

+ (instancetype)sharedInstance;

@end
