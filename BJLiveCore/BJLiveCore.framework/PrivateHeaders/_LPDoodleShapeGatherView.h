//
//  _LPDoodleShapeGatherView.h
//  BJLiveCore
//
//  Created by Randy on 16/4/22.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <ReactiveCocoa/ReactiveCocoa.h>

#import "BJLFeatureConfig.h"

@interface _LPDoodleShapeGatherView : UIView

@property (nonatomic) BJLPointsCompressType compressType;

/**
 *  _LPDoodleShape 值
 */
@property (strong, readonly, nonatomic) RACSignal *gatherSignal;

- (void)clearGather;
- (void)cancelGather;

@end
