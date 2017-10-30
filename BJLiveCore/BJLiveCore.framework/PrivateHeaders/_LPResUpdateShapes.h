//
//  _LPResUpdateShape.h
//  BJLiveCore
//
//  Created by Randy on 16/5/3.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "_LPBaseKit.h"

@class _LPShape;

@interface _LPResUpdateShapes : _LPResRoomModel
@property (strong, nonatomic) NSArray<_LPShape *> *shapeList;
@property (copy, nonatomic) NSString *docId;
@property (assign, nonatomic) NSUInteger pageIndex;
@end
