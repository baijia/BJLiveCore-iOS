//
//  _LPLogStat.h
//  BJLiveCore
//
//  Created by Randy on 16/5/25.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "_BJLContext.h"
#import "_LPLogConstants.h"

extern NSString *const _LP_LOG_APP_TYPE;

@interface _LPLogStat : NSObject

+ (BJLContext *)context;
+ (void)setContextGetter:(BJLContext *(^)())getter;

/**
 *  发送Log event
 *
 *  @param eventId
 *  @param attributes
 */
+ (void)event:(NSInteger)eventId attributes:(NSDictionary *)attributes;

@end
