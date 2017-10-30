//
//  _LPShapeShowView.h
//  BJLiveCore
//
//  Created by Randy on 16/4/22.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface _LPShapesShowView : UIView

- (void)addBrushLayers:(NSArray<CALayer *> *)layers;
- (void)removeBrushLayers:(NSArray<CALayer *> *)layers;
- (void)removeAllBrushLayers;

@end
