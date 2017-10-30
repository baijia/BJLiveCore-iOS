//
//  _LPTextShape.h
//  BJLiveCore
//
//  Created by Randy on 16/4/22.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "_LPShape.h"

@interface _LPTextShape : _LPShape
@property (assign, nonatomic) CGFloat lineHeight;
@property (assign, nonatomic) CGFloat fontSize;
@property (copy, nonatomic) NSString *fillStyle;
@property (copy, nonatomic) NSString *fontName;
@property (copy, nonatomic) NSString *text;
@property (copy, nonatomic) NSString *textAlign;
@property (copy, nonatomic) NSString *textBaseline;

@end
