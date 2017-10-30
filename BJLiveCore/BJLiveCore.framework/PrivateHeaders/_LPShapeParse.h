//
//  _LPShapeParse.h
//  BJLiveCore
//
//  Created by Randy on 16/4/22.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class _LPShape;

@interface _LPShapeParse : NSObject

/**
 *  根据不同的shape Name创建不同的LPShape子类对象
 *
 *  @param dictionary shape 信息
 *  @param error      错误信息
 *
 *  @return 可能为空 _LPShape的子类对象
 */
+ (nullable _LPShape *)shapeFromJsonDictionary:(NSDictionary *)dictionary error:(NSError *__autoreleasing *)error;

/**
 *  根据LPShape的子类对象转换成字典保存，转换字段根据各子类的JSONModel模型转换
 *
 *  @param shape _LPShape的子类对象
 *  @param error 错误信息
 *
 *  @return 可能为空 字段参照LPShape的JSONModel模型
 */
+ (nullable NSDictionary *)jsonDictionaryFromShape:(_LPShape *)shape error:(NSError *__autoreleasing *)error;

+ (nullable NSArray<_LPShape *> *)shapesFromJsonArray:(NSArray *)array error:(NSError *__autoreleasing *)error;

+ (nullable NSArray *)jsonArrayFromShapes:(NSArray<_LPShape *> *)shapes error:(NSError *__autoreleasing *)error;

@end

NS_ASSUME_NONNULL_END
