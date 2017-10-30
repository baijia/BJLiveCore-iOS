//
//  BJLLoadingVM+protected.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-12-05.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "BJLLoadingVM.h"

NS_ASSUME_NONNULL_BEGIN

@interface BJLLoadingVM ()

@property (nonatomic, readonly) BOOL isLoading;
- (void)startLoadingWithSteps:(BJLLoadingStep)steps;
- (void)stopLoading;

@end

typedef void (^BJLLoadingTaskCallback)(
BJLLoadingStep step,
BJLLoadingSuspendReason reason,
BJLError * _Nullable error,
BOOL ignorable);
typedef void (^BJLLoadingTask)(BJLLoadingTaskCallback taskCallback);

NS_ASSUME_NONNULL_END
