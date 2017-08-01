//
//  NSObject+BJL_M9Dev.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-04-20.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import <Foundation/Foundation.h>

// @see M9Dev - https://github.com/iwill/

NS_ASSUME_NONNULL_BEGIN

// for compound statement
#define bjl_return ;

// value to string
#define bjl_NSStringFromValue(VALUE)        [@(VALUE) description]

#define bjl_NSStringFromLiteral(LITERAL)    @#LITERAL // #LITERAL - LITERAL to CString

// !!!: use DEFAULT_VALUE if PREPROCESSOR is undefined or its value is same to itself
#define bjl_NSStringFromPreprocessor(PREPROCESSOR, DEFAULT_VALUE) ({ \
    NSString *string = bjl_NSStringFromLiteral(PREPROCESSOR); \
    bjl_return [string isEqualToString:@#PREPROCESSOR] ? DEFAULT_VALUE : string; \
})

// #define NSNULL [NSNull null]

// version comparison
// bjl_NSVersionLT(@"10", @"10.0"));    // YES - X
// bjl_NSVersionLT(@"10", @"10"));      // NO  - √
#define bjl_NSVersionEQ(A, B) ({ [A compare:B options:NSNumericSearch] == NSOrderedSame; })
#define bjl_NSVersionLT(A, B) ({ [A compare:B options:NSNumericSearch] <  NSOrderedSame; })
#define bjl_NSVersionGT(A, B) ({ [A compare:B options:NSNumericSearch] >  NSOrderedSame; })
#define bjl_NSVersionLE(A, B) ({ [A compare:B options:NSNumericSearch] <= NSOrderedSame; })
#define bjl_NSVersionGE(A, B) ({ [A compare:B options:NSNumericSearch] >= NSOrderedSame; })

// struct set
#define bjl_structSet(_STRUCT, STATEMENTS) ({ \
    __typeof__(_STRUCT) set = _STRUCT; \
    STATEMENTS \
    set; \
})

#define bjl_va_each(TYPE, FIRST, BLOCK) { \
    va_list args; \
    va_start(args, FIRST); \
    for (TYPE arg = FIRST; !!arg; arg = va_arg(args, TYPE)) { \
        BLOCK(arg); \
    } \
    va_end(args); \
}

// dispatch
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

// this class
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
 *      return BJLTuplePack((BOOL, BOOL), state1, state2);
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
#define BJLTuplePack(TYPE, ...) _BJLTuplePack(void (^)TYPE, __VA_ARGS__)
#define _BJLTuplePack(TYPE, ...) \
({[BJLTuple tupleWithPack:^(BJLTupleUnpackBlock unpack) { \
    if (unpack) ((TYPE)unpack)(__VA_ARGS__); \
}];})
/**
 *  这里不需要 weakify&strongify，unpack block 会被立即执行
 *  !!!: 用 ([BJLTuple defaultTuple], TUPLE) 而不是 (TUPLE ?: [BJLTuple defaultTuple])，因为后者会导致 TUPLE 被编译器认为是 nullable 的
 */
#define BJLTupleUnpack(TUPLE)   ([BJLTuple defaultTuple], TUPLE).unpack
typedef void (^BJLTupleUnpackBlock)(/* ... */);
typedef void (^BJLTuplePackBlock)(BJLTupleUnpackBlock unpack);
// - (BJLTuple<BJLTupleGeneric(NSString *string, NSInteger integer, ...)> *)aTuple;
#define BJLTupleGeneric         void (^)
// - (BJLTupleType(NSString *string, NSInteger integer))aTuple;
#define BJLTupleType(...)       BJLTuple<void (^)(__VA_ARGS__)> *
@interface BJLTuple<BJLTupleUnpackTypeGeneric> : NSObject
@property (nonatomic/* , writeonly */, assign, setter=unpack:) id/*<BJLTupleUnpackTypeGeneric>*/ unpack;
+ (instancetype)tupleWithPack:(BJLTuplePackBlock)pack;
+ (instancetype)defaultTuple;
@end

#pragma mark -

#define bjl_cast(CLASS, OBJECT) ({ (CLASS *)([OBJECT isKindOfClass:[CLASS class]] ? OBJECT : nil); })

@interface NSObject (BJL_M9Dev)

- (nullable id)bjl_if:(BOOL)condition;

- (nullable id)bjl_as:(Class)clazz;
- (nullable id)bjl_asMemberOfClass:(Class)clazz;
- (nullable id)bjl_asProtocol:(Protocol *)protocol;
- (nullable id)bjl_ifRespondsToSelector:(SEL)selector;

- (nullable NSArray *)bjl_asArray;
- (nullable NSDictionary *)bjl_asDictionary;

- (nullable id)bjl_performIfRespondsToSelector:(SEL)selector;
- (nullable id)bjl_performIfRespondsToSelector:(SEL)selector withObject:(nullable id)object;
- (nullable id)bjl_performIfRespondsToSelector:(SEL)selector withObject:(nullable id)object1 withObject:(nullable id)object2;

@end

#pragma mark -

@interface NSArray (BJL_M9Dev)

// indexOfObject:/containsObject:/removeObject: + compareSelector:/comparator:

- (nullable id)bjl_objectOrNilAtIndex:(NSUInteger)index;
- (BOOL)bjl_containsIndex:(NSUInteger)index;

@end

@interface NSMutableArray (BJL_M9Dev)

- (BOOL)bjl_addObjectOrNil:(nullable id)anObject;
- (BOOL)bjl_insertObjectOrNil:(nullable id)anObject atIndex:(NSUInteger)index;
- (BOOL)bjl_removeObjectOrNilAtIndex:(NSUInteger)index;
- (BOOL)bjl_replaceObjectAtIndex:(NSUInteger)index withObjectOrNil:(nullable id)anObject;

@end

#pragma mark -

@interface NSDictionary (BJL_M9Dev)

/**
 * ???: add int, remove unsignedXxxx
 *  @see NSString+NSStringExtensionMethods @ xxxValue
 *
 * NOTE: detect CGFloat is float or double:
 *  #if defined(__LP64__) && __LP64__
 *      CGFloat is double
 *  #elif
 #      CGFloat is float
 *  #endif
 */

/* C */
- (float)bjl_floatForKey:(id)aKey;
- (float)bjl_floatForKey:(id)aKey defaultValue:(float)defaultValue;
- (double)bjl_doubleForKey:(id)aKey;
- (double)bjl_doubleForKey:(id)aKey defaultValue:(double)defaultValue;
/* C More */
- (long long)bjl_longLongForKey:(id)aKey;
- (long long)bjl_longLongForKey:(id)aKey defaultValue:(long long)defaultValue;
- (unsigned long long)bjl_unsignedLongLongForKey:(id)aKey;
- (unsigned long long)bjl_unsignedLongLongForKey:(id)aKey defaultValue:(unsigned long long)defaultValue;

/* OC */
- (BOOL)bjl_boolForKey:(id)aKey;
- (BOOL)bjl_boolForKey:(id)aKey defaultValue:(BOOL)defaultValue;
- (NSInteger)bjl_integerForKey:(id)aKey;
- (NSInteger)bjl_integerOrNotFoundForKey:(id)aKey;
- (NSInteger)bjl_integerForKey:(id)aKey defaultValue:(NSInteger)defaultValue;

/* OC More */
- (NSUInteger)bjl_unsignedIntegerForKey:(id)aKey;
- (NSUInteger)bjl_unsignedIntegerOrNotFoundForKey:(id)aKey;
- (NSUInteger)bjl_unsignedIntegerForKey:(id)aKey defaultValue:(NSUInteger)defaultValue;

/* OC Object */
- (nullable NSNumber *)bjl_numberForKey:(id)aKey;
- (nullable NSNumber *)bjl_numberForKey:(id)aKey defaultValue:(nullable NSNumber *)defaultValue;
- (nullable NSString *)bjl_stringForKey:(id)aKey;
- (nullable NSString *)bjl_stringOrEmptyStringForKey:(id)akey;
- (nullable NSString *)bjl_stringForKey:(id)akey defaultValue:(nullable NSString *)defaultValue;
- (nullable NSArray *)bjl_arrayForKey:(id)aKey;
- (nullable NSArray *)bjl_arrayForKey:(id)aKey defaultValue:(nullable NSArray *)defaultValue;
- (nullable NSDictionary *)bjl_dictionaryForKey:(id)aKey;
- (nullable NSDictionary *)bjl_dictionaryForKey:(id)aKey defaultValue:(nullable NSDictionary *)defaultValue;
- (nullable NSData *)bjl_dataForKey:(id)aKey;
- (nullable NSData *)bjl_dataForKey:(id)aKey defaultValue:(nullable NSData *)defaultValue;
- (nullable NSDate *)bjl_dateForKey:(id)aKey;
- (nullable NSDate *)bjl_dateForKey:(id)aKey defaultValue:(nullable NSDate *)defaultValue;
- (nullable NSURL *)bjl_URLForKey:(id)aKey;
- (nullable NSURL *)bjl_URLForKey:(id)aKey defaultValue:(nullable NSURL *)defaultValue;

/* OC Object More */
/* !!!:
 *  @param clazz: Be careful when using this method on objects represented by a class cluster...
 *
 *      // DO NOT DO THIS! Use - objectForKey:callback: instead
 *      if ([myArray isKindOfClass:[NSMutableArray class]]) {
 *          // Modify the object
 *      }
 *
 *      @see NSObject - isKindOfClass:
 */
- (nullable id)bjl_objectForKey:(id)aKey class:(nullable Class)clazz;
- (nullable id)bjl_objectForKey:(id)aKey class:(nullable Class)clazz defaultValue:(nullable id)defaultValue;
- (nullable id)bjl_objectForKey:(id)aKey protocol:(nullable Protocol *)protocol;
- (nullable id)bjl_objectForKey:(id)aKey protocol:(nullable Protocol *)protocol defaultValue:(nullable id)defaultValue;
- (nullable id)bjl_objectForKey:(id)aKey class:(nullable Class)clazz protocol:(nullable Protocol *)protocol;
- (nullable id)bjl_objectForKey:(id)aKey class:(nullable Class)clazz protocol:(nullable Protocol *)protocol defaultValue:(nullable id)defaultValue;
- (nullable id)bjl_objectForKey:(id)aKey callback:(_Nullable id (^)(id object))callback;

@end

@interface NSMutableDictionary (BJL_M9Dev)

- (void)bjl_setObjectOrNil:(nullable id)anObject forKey:(nullable id<NSCopying>)aKey;
- (void)bjl_removeObjectForKeyOrNil:(nullable id<NSCopying>)aKey;

@end

#pragma mark -

@interface NSTimer (BJL_M9Dev)

+ (NSTimer *)bjl_timerWithTimeInterval:(NSTimeInterval)interval repeats:(BOOL)repeats block:(void (^)(NSTimer *timer))block;
+ (NSTimer *)bjl_scheduledTimerWithTimeInterval:(NSTimeInterval)interval repeats:(BOOL)repeats block:(void (^)(NSTimer *timer))block;

@end

/*
#pragma mark - YYModel

@interface NSObject (BJL_M9Dev_YYModel)

+ (nullable NSArray *)bjl_modelArrayWithJSON:(id)json;
+ (nullable NSDictionary *)bjl_modelDictionaryWithJSON:(id)json;

@end */

NS_ASSUME_NONNULL_END
