//
//  NSObject+BJL_M9Dev.h
//  Pods
//
//  Created by MingLQ on 2016-04-20.
//
//

#import <Foundation/Foundation.h>
#import <YYModel/YYModel.h>

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
 *  pack:
 *      return BJLTuplePack(val1, val2, ...);
 *  unpack:
 *      BJLTuple *tuple = [self aTuple];
 *      BJLTupleUnpack(tuple) = ^(Type1 var1, Type2 var2, ...) {
 *          // ...
 *      };
 *  !!!: maybe need weakify & strongify in both pack & unpack
 */
#define BJLTuplePack(...)       ({[BJLTuple tupleWithPack:^(BJLTupleUnpackBlock unpack) { \
                                    if (unpack) unpack(__VA_ARGS__); \
                                }];})
#define BJLTupleUnpack(TUPLE)   (TUPLE ?: [BJLTuple new]).unpack
typedef void (^BJLTupleUnpackBlock)(/* ... */);
typedef void (^BJLTuplePackBlock)(BJLTupleUnpackBlock unpack);
@interface BJLTuple<BJLTupleUnpackTypeGeneric> : NSObject
@property (nonatomic, /* writeonly, */ setter=unpack:) BJLTupleUnpackBlock unpack;
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

#pragma mark - YYModel

@interface NSObject (BJL_M9Dev_YYModel)

+ (NSArray *)bjl_modelArrayWithJSON:(id)json;
+ (NSDictionary *)bjl_modelDictionaryWithJSON:(id)json;

@end
