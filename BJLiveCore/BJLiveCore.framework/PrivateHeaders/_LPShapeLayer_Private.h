//
//  _LPShapeLayer_Private.h
//  BJLiveCore
//
//  Created by Randy on 16/4/27.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//


#import "_LPShapeLayer.h"

@interface _LPShapeLayer ()
@property (strong, nonatomic) UIBezierPath *bezierPath;
/**
 *  和父类- (CALayer *)layer;方法返回的是同一个
 */
@property (strong, nonatomic) CAShapeLayer *shapeLayer;

@end
