//
//  _LPShapeLayer.h
//  BJLiveCore
//
//  Created by Randy on 16/4/22.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "_LPLayer.h"

NS_ASSUME_NONNULL_BEGIN

@interface _LPShapeLayer : _LPLayer

- (void)moveToRelativePoint:(CGPoint)point;
- (void)addLineToRelativePoint:(CGPoint)point;
- (void)removeAllPoints;

@end

NS_ASSUME_NONNULL_END
