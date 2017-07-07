//
//  RtcViewManager.h
//  mediaplayer
//
//  Created by longli on 2017/2/24.
//  Copyright © 2017年 zhangnu. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "gsx_rtc_types.h"

#pragma GCC visibility push(default)

/**
 * \brief 多窗口支持RtcViewManager，API参数带playId区分视频流
 */
@interface RtcViewManager : NSObject

/**
 * \brief 返回流视频的分辨率
 */
- (CGSize)videoResolution:(int)playId;

/**
 * \brief 重置RTCView
 */
- (void)resetRtcView:(int)playId;

/**
 * \brief 获取view，视频数据在该view中渲染
 * \return GsxVideoRenderIosView对象(继承自UIView)
 */
- (id)rtcView:(int)playId;

/**
 * \brief 视频采集预览
 * \param data RTCEngine* pointer
 * \return GPUImageView对象
 */
- (id)previewCaptureVideo:(void *)data;

/**
 * \brief deprecated API，兼容
 */
- (void)setRender:(void *)data
       withPlayId:(int)playid;

/**
 * \brief 设置渲染窗口大小
 * \param cb 消息回调函数 eg: 视频size变化、播放成功等
 * \param playId 播放音视频接口返回的playId(streamId)
 * \param data RTCEngine* pointer
 */
- (void)setFrame:(CGRect)frame
    withCallback:(gsx_rtc_engine_msg_callback)cb
      withPlayId:(int)playId
        withSelf:(void *)pthis
         andData:(void *)data;

@end

#pragma GCC visibility pop
