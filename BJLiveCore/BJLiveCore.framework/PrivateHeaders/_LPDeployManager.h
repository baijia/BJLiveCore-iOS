//
//  _LPDeployManager.h
//  BJLiveCore
//
//  Created by Randy on 16/3/29.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "_LPLivePlayerConstants.h"

@interface _LPDeployManager : NSObject

+ (BJLDeployType)deployType;
+ (void)setDeployType:(BJLDeployType)type;

+ (NSString *)baseURLString;
+ (NSString *)masterServerURLString;
+ (NSUInteger)masterServerPort;

@end
