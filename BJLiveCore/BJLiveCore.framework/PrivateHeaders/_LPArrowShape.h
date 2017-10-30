//
//  _LPLineShape.h
//  BJLiveCore
//
//  Created by Randy on 16/4/22.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//
#import "_LPShape.h"

@class _LPPoint;

@interface _LPArrowShape : _LPShape
@property (strong, nonatomic) _LPPoint *endPoint;
@property (copy, nonatomic) NSString *fillStyle;
@property (assign, nonatomic) CGFloat thickness;

@end
