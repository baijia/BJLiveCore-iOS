//
//  gsx_rtc_view.h
//  webrtc_engine
//
//  Created by wangqiangqiang on 15/7/8.
//  Copyright (c) 2015年 wangqiangqiang. All rights reserved.
//

#ifndef webrtc_engine_gsx_rtc_view_h
#define webrtc_engine_gsx_rtc_view_h

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "gsx_rtc_engine2.h"

@interface RTCView : NSObject

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

#endif
