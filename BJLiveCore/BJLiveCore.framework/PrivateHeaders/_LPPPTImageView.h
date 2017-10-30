//
//  _LPPPTImageView.h
//  BJLiveCore
//
//  Created by Randy on 16/4/13.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <ReactiveCocoa/ReactiveCocoa.h>

@class _LPShapesShowView;

@interface _LPPPTImageView : UIView
@property (strong, readonly, nonatomic) _LPShapesShowView *shapesView;
@property (strong, readonly, nonatomic) UIImageView *imageView;
@property (strong, readonly, nonatomic) RACCompoundDisposable *disposable;
@property (strong, readonly, nonatomic) UIScrollView *scrollView;

- (void)updateImageFrame:(CGRect)frame;

@end
