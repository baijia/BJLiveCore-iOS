//
//  BJLBlockHelper.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-11-26.
//
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <libextobjc/EXTScope.h>

#import "NSError+BJLError.h"
#import "NSObject+BJLBlockKVO.h"
#import "NSObject+BJLBlockNTO.h"

NS_ASSUME_NONNULL_BEGIN

/**
 进度回调
 @param progress    0.0 ~ 1.0
 @param total       总数量，大于 0 时有效
 @param completed   已完成数量
 @param message     进度描述
 */
typedef void (^BJLProgress)(CGFloat progress, int64_t total, int64_t completed, NSString * _Nullable message);

/**
 成功回调
 @param data        数据
 */
typedef void (^BJLSuccess)(id _Nullable data);

/**
 失败回调
 @param error       参考 BJLErrorDomain
 */
typedef void (^BJLFailure)(BJLError * _Nullable error);

NS_ASSUME_NONNULL_END
