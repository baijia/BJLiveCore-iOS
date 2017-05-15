//
//  MPRtcView.h
//  mediaplayer
//
//  Created by longli on 2017/2/24.
//  Copyright © 2017年 zhangnu. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "gsx_rtc_view.h"

@interface MPRtcView : RTCView

- (CGSize)videoResolution;

//reset view
- (void)reset;

//get view
- (id)view;

//get capture preview
- (id)preview:(void *)data;

//set render
- (void)setRender:(void *)data
       withPlayId:(int)playid;

//set view frame
- (void)setFrame:(CGRect)frame
    withCallback:(gsx_rtc_engine_msg_callback)cb
      withPlayId:(int)play_id
        withSelf:(void *)pthis
         andData:(void *)data;

@end
