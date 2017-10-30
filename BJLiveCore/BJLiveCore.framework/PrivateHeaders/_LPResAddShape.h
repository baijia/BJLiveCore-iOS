//
//  _LPResAddShape.h
//  BJLiveCore
//
//  Created by Randy on 16/5/3.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "_LPBaseKit.h"

@class _LPShape;

@interface _LPResAddShape : _LPResRoomModel
@property (strong, nonatomic) _LPShape *shape;
@property (copy, nonatomic) NSString *docId;
@property (assign, nonatomic) NSUInteger pageIndex;

- (instancetype)initWithShape:(_LPShape *)shape docId:(NSString *)docId pageIndex:(NSUInteger)pageIndex;

@end
