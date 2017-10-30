//
//  _LPDoodleShape.h
//  BJLiveCore
//
//  Created by Randy on 16/4/22.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "_LPShape.h"
#import "_LPPoint.h"

@interface _LPDoodleShape : _LPShape

@property (nonatomic) CGFloat lineWidth;
@property (nonatomic) BOOL smooth;
@property (nonatomic, copy) NSString *strokeStyle;
@property (nonatomic) BJLPointsCompressType compressType;
@property (nonatomic, copy) NSArray<_LPPoint *> *points;

- (void)addPoints:(NSArray<_LPPoint *> *)points;

@end
