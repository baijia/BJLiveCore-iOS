//
//  NSObject+BJLBlockKVO.h
//  M9Dev
//
//  Created by MingLQ on 2016-10-08.
//  Copyright © 2016 MingLQ <minglq.9@gmail.com>. All rights reserved.
//

#import <Foundation/Foundation.h>

#define BJLKeyPathMake(sel) NSStringFromSelector(@selector(sel))

/** @return NO to ignore */
typedef BOOL (^BJLKVOFilter)(id old, id now);

/** @return mapped value
typedef id   (^BJLKVOMap)   (id old, id now); */

/** @return BJLKVO_STOP(aka NO) to stop observing */
#define BJLKVO_GOON YES
#define BJLKVO_STOP NO
typedef BOOL (^BJLKVOBlock) (id old, id now);

/**
 KVO with block
 */
@interface NSObject (BJLBlockKVObserver)

/**
 @param object  object
 @param getter  getter of property, use keyPath if the getter is different from its property name
 @param options default old | now | initial
 @param filter  call block if filter returns YES or filter is nil, retaind by self and object
 @param block   retaind by self and object
 */
- (void)bjl_KVObserve:(NSObject *)object
               getter:(SEL)getter
           usingBlock:(BJLKVOBlock)block;
- (void)bjl_KVObserve:(NSObject *)object
               getter:(SEL)getter
               filter:(BJLKVOFilter)filter
           usingBlock:(BJLKVOBlock)block;
- (void)bjl_KVObserve:(NSObject *)object
               getter:(SEL)getter
              options:(NSKeyValueObservingOptions)options
               filter:(BJLKVOFilter)filter
           usingBlock:(BJLKVOBlock)block;

- (void)bjl_KVObserve:(NSObject *)object
           forKeyPath:(NSString *)keyPath
              options:(NSKeyValueObservingOptions)options
           usingBlock:(BJLKVOBlock)block;

/**
 auto called before either self or the observing object is deallocated
 */
- (void)bjl_stopAllKVObserving;
- (void)bjl_stopKVObserving:(NSObject *)object;
- (void)bjl_stopKVObserving:(NSObject *)object forKeyPath:(NSString *)keyPath;

@end
