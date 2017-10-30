//
//  _LPRectangleShape.h
//  BJLiveCore
//
//  Created by Randy on 16/4/22.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "_LPShape.h"

@interface _LPRectangleShape : _LPShape
@property (assign, nonatomic) CGFloat lineWidth;
@property (copy, nonatomic) NSString *strokeStyle;
@property (assign, nonatomic) CGFloat width;
@property (assign, nonatomic) CGFloat height;

@end
