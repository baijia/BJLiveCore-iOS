//
//  _LPShapeLayerFactory.h
//  BJLiveCore
//
//  Created by Randy on 16/4/22.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class _LPLayer;
@class _LPShape;

@interface _LPShapeLayerFactory : NSObject

+ (nullable _LPLayer *)shapeLayerWithModel:(_LPShape *)shape;

@end

NS_ASSUME_NONNULL_END
