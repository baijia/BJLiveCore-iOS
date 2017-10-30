//
//  NSObject+BJLBlockKVO.h
//  M9Dev
//
//  Created by MingLQ on 2016-10-08.
//  Copyright © 2016 MingLQ <minglq.9@gmail.com>. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "NSObject+BJLObserving.h"

NS_ASSUME_NONNULL_BEGIN

#define BJLKeyPathMake(SEL) NSStringFromSelector(@selector(SEL))

#define BJLKVO_GOON !BJLStopObserving
#define BJLKVO_STOP BJLStopObserving

/**
 !!!: DEPRECATED
 @see NSObject+BJLObserving.h
 */
@interface NSObject (BJLBlockKVObserver)

- (void)bjl_KVObserve:(NSObject *)object
               getter:(SEL)getter
           usingBlock:(BJLPropertyObserver)block DEPRECATED_MSG_ATTRIBUTE("@see `NSObject+BJLObserving.h`");
- (void)bjl_KVObserve:(NSObject *)object
               getter:(SEL)getter
               filter:(nullable BJLPropertyFilter)filter
           usingBlock:(BJLPropertyObserver)block DEPRECATED_MSG_ATTRIBUTE("@see `NSObject+BJLObserving.h`");
- (void)bjl_KVObserve:(NSObject *)object
               getter:(SEL)getter
              options:(NSKeyValueObservingOptions)options
               filter:(nullable BJLPropertyFilter)filter
           usingBlock:(BJLPropertyObserver)block DEPRECATED_MSG_ATTRIBUTE("@see `NSObject+BJLObserving.h`");

- (void)bjl_KVObserve:(NSObject *)object
           forKeyPath:(NSString *)keyPath
              options:(NSKeyValueObservingOptions)options
           usingBlock:(BJLPropertyObserver)block DEPRECATED_MSG_ATTRIBUTE("@see `NSObject+BJLObserving.h`");

- (void)bjl_stopAllKVObserving DEPRECATED_MSG_ATTRIBUTE("@see `NSObject+BJLObserving.h`");
- (void)bjl_stopKVObserving:(nullable NSObject *)object DEPRECATED_MSG_ATTRIBUTE("@see `NSObject+BJLObserving.h`");
- (void)bjl_stopKVObserving:(nullable NSObject *)object forKeyPath:(nullable NSString *)keyPath NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
