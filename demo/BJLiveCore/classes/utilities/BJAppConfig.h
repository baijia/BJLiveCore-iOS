//
//  BJAppConfig.h
//  LivePlayerApp
//
//  Created by MingLQ on 2016-08-19.
//  Copyright © 2016年 BaijiaYun. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <BJLiveCore/BJLiveCore.h>

@interface BJAppConfig : NSObject

+ (instancetype)sharedInstance;

#if DEBUG
@property (nonatomic) BJLDeployType deployType;
#else
@property (nonatomic, readonly) BJLDeployType deployType;
#endif

@end
