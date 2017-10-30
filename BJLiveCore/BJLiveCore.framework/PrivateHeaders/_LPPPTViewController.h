//
//  _LPPPTViewController.h
//  BJLiveCore
//
//  Created by Randy on 16/3/23.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <ReactiveCocoa/ReactiveCocoa.h>

#import "_BJLContext.h"
#import "_LPDocContext.h"

@interface _LPPPTViewController : UIViewController

- (instancetype)initWithContext:(BJLContext *)context docContext:(_LPDocContext *)docContext;

// NSValue<CGRect> *
@property (nonatomic, readonly) RACSignal *imageFrameInPPTViewChangedSignal;

//本地图片路径
@property (nonatomic, nullable) NSArray *localPPTImagePaths;

- (CGRect)imageFrameInPPTView;

- (void)setScrollAgentView:(UIView *)scrollAgentView;

@end
