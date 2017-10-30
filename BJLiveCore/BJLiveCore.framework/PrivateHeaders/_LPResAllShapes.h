//
//  _LPResAllShapes.h
//  BJLiveCore
//
//  Created by Randy on 16/4/28.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "_LPBaseKit.h"

@class _LPShape;

@interface _LPResAllShapes : _LPResRoomModel
@property (copy, nonatomic) NSString *docId;
@property (assign, nonatomic) NSUInteger pageIndex;
@property (strong, nonatomic) NSArray<_LPShape *> *shapeList;

@end
