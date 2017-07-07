//
//  NSObject+M9Observing.h
//  M9Dev
//
//  Created by MingLQ on 2017-01-04.
//  Copyright © 2017 MingLQ <minglq.9@gmail.com>. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 *  !!!: avoid retain cycle - bjl_kvo:..., bjl_kvoMerge:..., bjl_observe:..., bjl_observeMerge:...
 *  // recommended: observation as property
 *  @weakify(self); // weakify self
 *  self.observation = // observation property
 *  [self bjl_kvo:@[..., ...]
 *       observer:^(id _Nullable old, id _Nullable now) {
 *           @strongify(self); // strongify self
 *           [self.observation stopObserving];
 *           self.observation = nil;
 *           return YES;
 *       }];
 *  // deprecated: observation as __block ivar
 *  __block id<BJLObservation> observation = // __block observation
 *  [self bjl_kvo:@[..., ...]
 *       // !!!: this observer block MUST be called at least once
 *       observer:^(id _Nullable old, id _Nullable now) {
 *           // !!!: these two statements MUST be called
 *           [observation stopObserving];
 *           observation = nil;
 *           return YES;
 *       }];
 *
 *  TODO: default filter: ifChanged, ifNumberChanged - isEqualToNumber:
 */

@protocol BJLObservation;
@class BJLPropertyMeta, BJLMethodMeta;

typedef BOOL (^BJLPropertyFilter)(id _Nullable old, id _Nullable now);
typedef BOOL (^BJLPropertyObserver)(id _Nullable old, id _Nullable now);
typedef void (^BJLPropertiesObserver)(id _Nullable old, id _Nullable now);

typedef BOOL (^BJLMethodFilter)();
typedef BOOL (^BJLMethodObserver)();
typedef void (^BJLMethodsObserver)();

#define BJLStopObserving NO

#define BJLMakeProperty(TARGET, PROPERTY) ({ \
    (void)(NO && ((void)TARGET.PROPERTY, NO)); /* copied from libextobjc/EXTKeyPathCoding.h */ \
    [BJLPropertyMeta instanceWithTarget:TARGET name:@#PROPERTY]; \
})

#define BJLMakeMethod(TARGET, METHOD) ({ \
    NSParameterAssert([TARGET respondsToSelector:@selector(METHOD)]); \
    [BJLMethodMeta instanceWithTarget:TARGET name:@#METHOD]; \
})

typedef void BJLObservable;
#define BJLMethodNotify(TYPE, ...) _BJLMethodNotify(BOOL (^)TYPE, __VA_ARGS__)
#define _BJLMethodNotify(TYPE, ...) do { \
    _Pragma("clang diagnostic push") \
    _Pragma("clang diagnostic ignored \"-Wdeprecated-declarations\"") \
    [self bjl_notifyMethodForSelector:_cmd callback:^BOOL(BJLMethodFilter filter, BJLMethodObserver observer, BOOL ignoreReturnValue) { \
        return (!filter || ((TYPE)filter)(__VA_ARGS__)) && (((TYPE)observer)(__VA_ARGS__) || ignoreReturnValue); \
    }]; \
    _Pragma("clang diagnostic pop") \
} \
while (NO)
// #define BJLMethodNotify_NoArgs() BJLMethodNotify((void))

extern const NSKeyValueObservingOptions BJLKVODefaultOptions;

/**
 KVO with block.
 Auto stop observing before either self or the observing object is deallocated.
 */
@interface NSObject (BJLKeyValueObserving)

/**
 @param meta        target-property, @see `BJLMakeProperty(TARGET, PROPERTY)`
 @param options     default now | old | initial
 @param filter      return NO to ignore, retaind by self, target and returned id<BJLObservation>
 @param observer    return NO to stop observing, retaind by self, target and returned id<BJLObservation>
 @return id<BJLObservation> for `stopObserving`
 */
- (id<BJLObservation>)bjl_kvo:(BJLPropertyMeta *)meta
                     observer:(BJLPropertyObserver)observer;
- (id<BJLObservation>)bjl_kvo:(BJLPropertyMeta *)meta
                       filter:(nullable BJLPropertyFilter)filter
                     observer:(BJLPropertyObserver)observer;
- (id<BJLObservation>)bjl_kvo:(BJLPropertyMeta *)meta
                      options:(NSKeyValueObservingOptions)options
                     observer:(BJLPropertyObserver)observer;
- (id<BJLObservation>)bjl_kvo:(BJLPropertyMeta *)meta
                      options:(NSKeyValueObservingOptions)options
                       filter:(nullable BJLPropertyFilter)filter
                     observer:(BJLPropertyObserver)observer;

- (nullable id<BJLObservation>)bjl_kvoMerge:(NSArray<BJLPropertyMeta *> *)metas
                                   observer:(BJLPropertiesObserver)observer;
- (nullable id<BJLObservation>)bjl_kvoMerge:(NSArray<BJLPropertyMeta *> *)metas
                                     filter:(nullable BJLPropertyFilter)filter
                                   observer:(BJLPropertiesObserver)observer;
- (nullable id<BJLObservation>)bjl_kvoMerge:(NSArray<BJLPropertyMeta *> *)metas
                                    options:(NSKeyValueObservingOptions)options
                                   observer:(BJLPropertiesObserver)observer;
- (nullable id<BJLObservation>)bjl_kvoMerge:(NSArray<BJLPropertyMeta *> *)metas
                                    options:(NSKeyValueObservingOptions)options
                                     filter:(nullable BJLPropertyFilter)filter
                                   observer:(BJLPropertiesObserver)observer;

- (void)bjl_stopAllKeyValueObservingOfTarget:(nullable id)target;
- (void)bjl_stopAllKeyValueObserving;

@end

/**
 Method-Arguments observing with block.
 Auto stop observing before either self or the observing object is deallocated.
 */
@interface NSObject (BJLMethodArgumentsObserving)

/**
 @param meta        target-method, @see `BJLMakeMethod(TARGET, METHOD)`
 @param filter      return NO to ignore, retaind by self, target and returned id<BJLObservation>
 @param observer    return NO to stop observing, retaind by self, target and returned id<BJLObservation>
 @return id<BJLObservation> for `stopObserving`
 */
- (id<BJLObservation>)bjl_observe:(BJLMethodMeta *)meta
                         observer:(BJLMethodObserver)observer;
- (id<BJLObservation>)bjl_observe:(BJLMethodMeta *)meta
                           filter:(nullable BJLMethodFilter)filter
                         observer:(BJLMethodObserver)observer;

/**
 merged methods should have same arguments
 */
- (nullable id<BJLObservation>)bjl_observeMerge:(NSArray<BJLMethodMeta *> *)metas
                                       observer:(BJLMethodsObserver)observer;
- (nullable id<BJLObservation>)bjl_observeMerge:(NSArray<BJLMethodMeta *> *)metas
                                         filter:(nullable BJLMethodFilter)filter
                                       observer:(BJLMethodsObserver)observer;

- (void)bjl_stopAllMethodArgumentsObservingOfTarget:(nullable id)target;
- (void)bjl_stopAllMethodArgumentsObserving;

- (void)bjl_notifyMethodForSelector:(SEL)selector callback:(BOOL (^)(BJLMethodFilter filter, BJLMethodObserver observer, BOOL ignoreReturnValue))callback DEPRECATED_MSG_ATTRIBUTE("use `BJLMethodNotify(TYPE, ...)`");

@end

#pragma mark -

@protocol BJLObservation <NSObject>
- (void)stopObserving;
@end

@interface BJLObservingMeta : NSObject
+ (instancetype)instanceWithTarget:(id)target name:(NSString *)name;
@end

@interface BJLPropertyMeta : BJLObservingMeta
@end

@interface BJLMethodMeta : BJLObservingMeta
@end

NS_ASSUME_NONNULL_END
