//
//  NSObject+BJL_M9Dev.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-04-20.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import <Foundation/Foundation.h>

// @see M9Dev - https://github.com/iwill/

// for compound statement
#define bjl_return ;

// value to string
#define bjl_NSStringFromValue(value) [@(value) description]

// set struct
#define bjl_SetStruct(_struct, statements) ({ \
    __typeof__(_struct) set = _struct; \
    statements \
    set; \
})

/** dispatch */
static inline dispatch_time_t bjl_dispatch_time_in_seconds(NSTimeInterval seconds) {
    return dispatch_time(DISPATCH_TIME_NOW, (int64_t)(seconds * NSEC_PER_SEC));
}
static inline void bjl_dispatch_after_seconds(NSTimeInterval seconds, dispatch_queue_t queue, dispatch_block_t block) {
    dispatch_after(bjl_dispatch_time_in_seconds(seconds), queue ?: dispatch_get_main_queue(), block);
}
static inline void bjl_dispatch_sync_main_queue(dispatch_block_t block) {
    if ([NSThread isMainThread]) block();
    else dispatch_sync(dispatch_get_main_queue(), block);
}
static inline void bjl_dispatch_async_main_queue(dispatch_block_t block) {
    dispatch_async(dispatch_get_main_queue(), block);
}
static inline void bjl_dispatch_async_background_queue(dispatch_block_t block) {
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_BACKGROUND, 0), block);
}    

// safe range
static inline NSRange BJL_NSMakeSafeRange(NSUInteger loc, NSUInteger len, NSUInteger length) {
    loc = MIN(loc, length);
    len = MIN(len, length - loc);
    return NSMakeRange(loc, len);
}

#define BJL_THIS_CLASS_NAME ({ \
static NSString *ClassName = nil; \
    if (!ClassName) {\
        NSString *prettyFunction = [NSString stringWithUTF8String:__PRETTY_FUNCTION__]; \
        NSUInteger loc = [prettyFunction rangeOfString:@"["].location + 1; \
        NSUInteger len = [prettyFunction rangeOfString:@" "].location - loc; \
        NSRange range = BJL_NSMakeSafeRange(loc, len, prettyFunction.length); \
        ClassName = [prettyFunction substringWithRange:range]; \
    } \
    ClassName; \
})
#define BJL_THIS_CLASS NSClassFromString(BJL_THIS_CLASS_NAME)

// RACTupleUnpack without unused warning
#define BJL_RACTupleUnpack(...) \
_Pragma("GCC diagnostic push") \
_Pragma("GCC diagnostic ignored \"-Wunused-variable\"") \
RACTupleUnpack(__VA_ARGS__) \
_Pragma("GCC diagnostic pop")

/**
 *  M9TuplePack & M9TupleUnpack
 *  define:
 *      - (BJLTuple<void (^)(BOOL state1, BOOL state2> *)states;
 *  pack:
 *      BOOL state1 = self.state1, state2 = self.state2;
 *      return BJLTuplePack(void (^)(BOOL, BOOL), state1, state2);
 *  unpack:
 *      BJLTupleUnpack(tuple) = ^(BOOL state1, BOOL state2) {
 *          // ...
 *      };
 */
/* !!!: BJLTuplePack(void (^)(BOOL), self.state)
 *  1. BJLTuplePack 中使用到的对象将被 tuple 持有、直到 tuple 被释放，例如上面的 self；
 *  2. self.state 的值将在拆包时读取、而不是打包时；
 *      BJLTuple *tuple = BJLTuplePack(void (^)(BOOL, BOOL), self.state1, self.state2);
 *  因此【强烈建议】定义临时变量提前读取属性值，以避免出现不可预期的结果！
 *      BOOL state1 = self.state1, state2 = self.state2;
 *      BJLTuple *tuple = BJLTuplePack(void (^)(BOOL, BOOL), state1, state2);
 */
#define BJLTuplePack(TYPE, ...) _BJLTuplePack(void (^)TYPE, ...)
#define _BJLTuplePack(TYPE, ...) \
({[BJLTuple tupleWithPack:^(BJLTupleUnpackBlock unpack) { \
    if (unpack) ((TYPE)unpack)(__VA_ARGS__); \
}];})
/**
 *  这里不需要 weakify&strongify，unpack block 会被立即执行
 */
#define BJLTupleUnpack(TUPLE)   (TUPLE ?: [BJLTuple new]).unpack
typedef void (^BJLTupleUnpackBlock)(/* ... */);
typedef void (^BJLTuplePackBlock)(BJLTupleUnpackBlock unpack);
@interface BJLTuple<BJLTupleUnpackTypeGeneric> : NSObject
@property (nonatomic, /* writeonly, */ setter=unpack:) id/*<BJLTupleUnpackTypeGeneric>*/ unpack;
+ (instancetype)tupleWithPack:(BJLTuplePackBlock)pack;
@end

#pragma mark -

@interface NSObject (BJL_M9Dev)

- (id)bjl_if:(BOOL)condition;

- (id)bjl_as:(Class)clazz;
- (id)bjl_asMemberOfClass:(Class)clazz;
- (id)bjl_asProtocol:(Protocol *)protocol;
- (id)bjl_ifRespondsToSelector:(SEL)selector;

- (NSArray *)bjl_asArray;
- (NSDictionary *)bjl_asDictionary;

- (id)bjl_performIfRespondsToSelector:(SEL)selector;
- (id)bjl_performIfRespondsToSelector:(SEL)selector withObject:(id)object;
- (id)bjl_performIfRespondsToSelector:(SEL)selector withObject:(id)object1 withObject:(id)object2;

@end

#pragma mark -

@interface NSArray (BJL_M9Dev)

- (id)bjl_objectOrNilAtIndex:(NSUInteger)index;
- (BOOL)bjl_containsIndex:(NSUInteger)index;

@end

@interface NSMutableArray (BJL_M9Dev)

- (BOOL)bjl_addObjectOrNil:(id)anObject;
- (BOOL)bjl_insertObjectOrNil:(id)anObject atIndex:(NSUInteger)index;
- (BOOL)bjl_removeObjectOrNilAtIndex:(NSUInteger)index;
- (BOOL)bjl_replaceObjectAtIndex:(NSUInteger)index withObjectOrNil:(id)anObject;

@end

#pragma mark -

@interface NSTimer (BJL_M9Dev)

+ (NSTimer *)bjl_timerWithTimeInterval:(NSTimeInterval)interval repeats:(BOOL)repeats block:(void (^)(NSTimer *timer))block;
+ (NSTimer *)bjl_scheduledTimerWithTimeInterval:(NSTimeInterval)interval repeats:(BOOL)repeats block:(void (^)(NSTimer *timer))block;

@end

/*
#pragma mark - YYModel

@interface NSObject (BJL_M9Dev_YYModel)

+ (NSArray *)bjl_modelArrayWithJSON:(id)json;
+ (NSDictionary *)bjl_modelDictionaryWithJSON:(id)json;

@end */
