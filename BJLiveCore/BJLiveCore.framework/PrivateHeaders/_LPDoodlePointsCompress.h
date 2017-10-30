//
//  _LPDoodleShapeDeflate.h
//  BJLiveCore
//
//  Created by Randy on 16/4/28.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import <Foundation/Foundation.h>

@class _LPPoint;

@interface _LPDoodlePointsCompress : NSObject

/*
    NSString *string = [_LPDoodlePointsCompress
                        compressPoints:@[[_LPPoint pointWithCGPoint:CGPointMake(0.1401, 1.1401)],
                                         [_LPPoint pointWithCGPoint:CGPointMake(-0.1401, 0.0114)],
                                         [_LPPoint pointWithCGPoint:CGPointMake(0.0, 0.5)]]];
    NSLog(@"string: %@", string); // 1$"1$!1$$1##U#
    NSArray<_LPPoint *> *points = [_LPDoodlePointsCompress extractPoints:string];
    NSLog(@"points: %@", points); // [{0.1401, 1.1401}, {-0.1401, 0.0114}, {0.0000, 0.5000}]
 */

+ (NSString *)compressPoints:(NSArray<_LPPoint *> *)points;
+ (NSArray<_LPPoint *> *)extractPoints:(NSString *)string;

// + (NSString *)compress:(NSString *)string;
// + (NSString *)uncompress:(NSString *)string;

@end
