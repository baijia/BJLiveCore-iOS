//
//  _LPArrowBezierPath.h
//  BJLiveCore
//
//  Created by Randy on 16/5/3.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//
 
#import <UIKit/UIKit.h>

@interface _LPArrowBezierPath : UIBezierPath

+ (UIBezierPath *)bezierPathWithArrowFromPoint:(CGPoint)startPoint
                                       toPoint:(CGPoint)endPoint
                                     tailWidth:(CGFloat)tailWidth
                                     headWidth:(CGFloat)headWidth
                                    headLength:(CGFloat)headLength;

@end
