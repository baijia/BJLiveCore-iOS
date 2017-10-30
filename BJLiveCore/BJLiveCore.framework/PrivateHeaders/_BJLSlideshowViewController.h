//
//  _BJLSlideshowViewController.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-12-19.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "_BJLContext.h"
#import "BJLSlideshowUI.h"

@interface BJLSlideshowViewController : UIViewController <BJLSlideshowUI>

- (instancetype)initWithContext:(BJLContext *)context;

//本地图片路径
@property (nonatomic, nullable) NSArray *localPPTImagePaths;

@end
