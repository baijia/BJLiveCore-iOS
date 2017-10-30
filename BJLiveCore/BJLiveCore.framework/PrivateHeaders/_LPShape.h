//
//  _LPShape.h
//  BJLiveCore
//
//  Created by Randy on 16/4/22.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "_LPPoint.h"
#import "_LPBaseKit.h"

@interface _LPShape : _LPDataModel
@property (strong, nonatomic) _LPPoint *startPoint;
@property (copy, nonatomic) NSString *shapeId;
@property (copy, nonatomic) NSString *localId;
@property (copy, nonatomic) NSString *name;

/**
 *  override method 子类实现移动
 *
 *  @param offset 移动的x、y的距离
 */
- (void)moveShapeWithOffset:(CGPoint)offset;

/**
 *  override method 子类实现缩放
 *
 *  @param scale 缩放级别
 */
- (void)scaleShape:(CGFloat)scale;

@end
