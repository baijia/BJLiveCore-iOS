//
//  _LPPoint.h
//  BJLiveCore
//
//  Created by Randy on 16/4/26.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "_LPBaseKit.h"

@interface _LPPoint : _LPDataModel

@property (nonatomic) CGFloat x, y;

@property (nonatomic, readonly) CGPoint CGPoint;
@property (nonatomic, readonly) NSString *xString, *yString;

- (instancetype)initWithCGPoint:(CGPoint)point;
+ (instancetype)pointWithCGPoint:(CGPoint)point;

@end
