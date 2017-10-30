//
//  _LPShapesShowViewController.h
//  BJLiveCore
//
//  Created by Randy on 16/4/22.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "_BJLContext.h"
#import "_LPDocContext.h"

@interface _LPBrushManagerViewController : UIViewController

- (instancetype)initWithContext:(BJLContext *)context docContext:(_LPDocContext *)docContext;

- (void)updateGatherViewFrame:(CGRect)rect;
- (void)clear;

@end
