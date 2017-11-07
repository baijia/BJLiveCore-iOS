//
//  BJLHelpVM.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-12-06.
//  Copyright © 2016 BaijiaYun. All rights reserved.
//

#import "BJLBaseVM.h"

NS_ASSUME_NONNULL_BEGIN

/** ### 求助 */
@interface BJLHelpVM : BJLBaseVM

/** 发起求助
 #param userPhoneNumber 用户手机号
 #return BJLError：
 BJLErrorCode_invalidArguments  错误参数
 */
- (nullable BJLError *)requestForHelpWithUserPhoneNumber:(NSString *)userPhoneNumber;

/** 求助成功/失败回调
 #param success YES：成功，NO：失败
 */
- (BJLObservable)requestForHelpDidFinish:(BOOL)success;

@end

NS_ASSUME_NONNULL_END
