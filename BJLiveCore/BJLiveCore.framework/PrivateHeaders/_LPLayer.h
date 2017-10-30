//
//  _LPLayer.h
//  BJLiveCore
//
//  Created by Randy on 16/4/26.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import <QuartzCore/QuartzCore.h>

NS_ASSUME_NONNULL_BEGIN

@class _LPShape;

@interface _LPLayer : NSObject
@property (strong, nullable, nonatomic) _LPShape *shape;
@property (assign, nonatomic) CGSize showSize;

- (instancetype)initWithShape:(_LPShape *)shape;

- (void)updateShapeDisplay;

/**
 *  override method
 */
- (void)drawInLayer;

- (CALayer *)layer;

- (CGPoint)layerPointWithRelativePoint:(CGPoint)point;
@end

NS_ASSUME_NONNULL_END
