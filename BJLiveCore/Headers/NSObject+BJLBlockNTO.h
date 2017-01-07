//
//  NSObject+BJLBlockNTO.h
//  M9Dev
//
//  Created by MingLQ on 2015-12-14.
//  Copyright © 2015年 MingLQ <minglq.9@gmail.com>. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "NSObject+BJLObserving.h"

NS_ASSUME_NONNULL_BEGIN

/**
 !!!: DEPRECATED
 @see NSObject+BJLObserving.h
 */
@interface NSObject (BJLBlockObserver)

- (void)bjl_observe:(id)object event:(SEL)event usingBlock:(BJLMethodObserver)block DEPRECATED_MSG_ATTRIBUTE("@see `NSObject+BJLObserving.h`");

- (void)bjl_stopObserving:(nullable id)object event:(nullable SEL)event NS_UNAVAILABLE;
- (void)bjl_stopAllObserving DEPRECATED_MSG_ATTRIBUTE("@see `NSObject+BJLObserving.h`");

@end

NS_ASSUME_NONNULL_END
