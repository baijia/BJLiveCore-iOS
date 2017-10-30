//
//  BJLBaseVM+protected.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-12-05.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "BJLBaseVM.h"

#import "_BJLContext.h"

#import <ReactiveCocoa/ReactiveCocoa.h>

NS_ASSUME_NONNULL_BEGIN

@class BJLContext;

@interface BJLBaseVM ()

@property (nonatomic, readonly, nullable, weak) BJLContext *context;

+ (instancetype)instanceWithContext:(BJLContext *)context;
- (instancetype)initWithContext:(BJLContext *)context NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
