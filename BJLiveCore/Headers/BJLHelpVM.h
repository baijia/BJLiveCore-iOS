//
//  BJLHelpVM.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-12-06.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "BJLBaseVM.h"

NS_ASSUME_NONNULL_BEGIN

@interface BJLHelpVM : BJLBaseVM

/** 发起求助 */
- (nullable BJLError *)requestForHelpWithUserPhoneNumber:(NSString *)userPhoneNumber;

/** 求助成功/失败回调 */
- (BJLObservable)requestForHelpFinished:(BOOL)success;

@end

NS_ASSUME_NONNULL_END
