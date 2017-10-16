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
#import "gsx_rtc_types.h"

@interface RTCView : NSObject

/**
 * \brief 返回视频的分辨率
 */
- (CGSize)videoResolution;

/**
 * \brief 释放view
 */
- (void)reset;

/**
 * \brief 获取view，视频数据在该view中渲染
 * \return GsxVideoRenderIosView对象(继承自UIView)
 */
- (id)view;

/**
 * @note API兼容，空实现
 */
- (void)setRender:(void *)data
       withPlayId:(int)playid;

/**
 * \brief 视频采集预览
 * \param data RTCEngine* pointer
 * \return GPUImageView对象
 */
- (id)preview:(void *)data;

/**
 * \brief 设置渲染窗口大小
 * \param cb 消息回调函数 eg: 视频size变化、播放成功等
 * \param play_id 播放音视频接口返回的play_id(stream_id)
 * \param data RTCEngine* pointer
 */
- (void)setFrame:(CGRect)frame
    withCallback:(gsx_rtc_engine_msg_callback)cb
      withPlayId:(int)play_id
        withSelf:(void *)pthis
         andData:(void *)data;

@end

#endif
