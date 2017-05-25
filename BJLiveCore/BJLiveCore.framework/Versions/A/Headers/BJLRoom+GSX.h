//
//  BJLRoom+GSX.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-11-28.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "BJLRoom.h"

#import "BJLFeatureConfig.h"

// #import "BJLGiftVM.h"
#import "BJLHelpVM.h"

NS_ASSUME_NONNULL_BEGIN

@interface BJLRoom (readonly)

/** 电话求助 */
@property (nonatomic, readonly, nullable) BJLHelpVM *helpVM;

/** 打赏 */
// @property (nonatomic, readonly, nullable) BJLGiftVM *giftVM;

@end

NS_ASSUME_NONNULL_END
