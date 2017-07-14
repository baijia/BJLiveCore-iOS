 
//
//  Created by zhangnu on 2017/2/23.
//  Copyright © 2017年 zhangnu. All rights reserved.
//
#import <Foundation/NSObject.h>
#import <Foundation/Foundation.h>

#include "gsx_rtc_types.h"
#include "gsx_live_play_info.h"

#pragma GCC visibility push(default)

@interface MediaPlayWrapper : NSObject

- (void) gsx_rtc_engine_set_upstream_support_udp:(int)support_udp;

- (void*) gsx_rtc_engine_init;

- (int) gsx_rtc_engine_uninit:(void*) in_pVoid;

// 底层回调接口，统计数据等
- (void) gsx_rtc_engine_set_msg_callback:(void *)in_pVoid :(gsx_rtc_engine_msg_callback)msg_cb :(void *)priv;

- (void) gsx_rtc_engine_set_local_user_id:(void *)in_pVoid :(int)user_id;

// 设置播放缓冲时长
-(int) gsx_rtc_engine_play_set_buffering_time:(void *)in_pVoid : (long) buffering_ms;

// 设置切换参数
- (int) gsx_rtc_engine_play_set_switch_params:(void *)in_pVoid : (int)first_switch_limit :(int) first_switch_offset :(int) play_switch_limit   :(int) play_switch_offset;

// 设置视频窗口
- (int) gsx_rtc_engine_play_set_video_display_window:(void *)in_pVoid :( int) in_nPlayId :( void *)in_pWindow :( RTCRect) in_WindowRect;

// 设置视频显示比例，默认按源片比例
-(int) gsx_rtc_engine_play_set_video_display_mode:(void *)in_pVoid :( int) in_nPlayId :( RTCVideoDisplayMode) in_DisplayMode;

// 播放音视频
//    GSX_RTC_API int gsx_rtc_engine_play_media_start(void *in_pVoid, const char *in_pPlayUrl, int in_nPlayType);
//    GSX_RTC_API int gsx_rtc_engine_play_media_stop(void *in_pVoid, int in_nPlayId);
-(int) gsx_rtc_engine_play_media_start:(void *)in_pVoid :( const char *)in_pUrl :( int) in_nMediaType :( int) in_nRemoteId :( const char *)in_pPublishIp :( int) in_nPublishPort;
- (int) gsx_rtc_engine_play_media_stop:(void *)in_pVoid :( int) in_nPlayId;

// 暂停音频播放
- (int) gsx_rtc_engine_play_audio_pause:(void *)in_pVoid :(int) in_nPlayId;
// 恢复音频播放
- (int)  gsx_rtc_engine_play_audio_resume:(void *)in_pVoid :(int) in_nPlayId;

// 暂停视频播放
- (int)  gsx_rtc_engine_play_video_pause:(void *)in_pVoid :(int) in_nPlayId;
// 恢复视频播放
- (int) gsx_rtc_engine_play_video_resume:(void *)in_pVoid :(int) in_nPlayId;

// 采集音频
- (int) gsx_rtc_engine_capture_audio_start:(void *)in_pVoid;
- (int)  gsx_rtc_engine_capture_audio_stop:(void *)in_pVoid;

// 采集视频
- (int) gsx_rtc_engine_capture_video_set_capability:(void *)in_pVoid :( GsxVideoCaptureCapability) capability;
- (int)  gsx_rtc_engine_capture_video_start:(void *)in_pVoid;
- (int)  gsx_rtc_engine_capture_video_stop:(void *)in_pVoid;
// 获取采集预览
 -(void*) gsx_rtc_engine_capture_video_get_preview:(void *)in_pVoid;
// 设置采集预览显示比例
- (int)  gsx_rtc_engine_capture_video_set_preview_display_mode:(void *)in_pVoid :(RTCVideoDisplayMode) in_DisplayMode;
// 设置采集输出角度:0,90,180,270
- (int)  gsx_rtc_engine_capture_video_set_rotation:(void *)in_pVoid :(int) degree;
// 切换前后置摄像头
- (int)  gsx_rtc_engine_capture_video_switch_camera:(void *)in_pVoid;
// 设置视频美颜(level:0~5, 0为去掉美颜)
- (int)  gsx_rtc_engine_capture_video_set_beauty_level:(void *)in_pVoid :(int) level;

// 预览本地声音采集
- (int)  gsx_rtc_engine_preview_captured_audio_start:(void *)in_pVoid;
- (int)  gsx_rtc_engine_preview_captured_audio_stop:(void *)in_pVoid;

// 预览本地视频采集 (not used)
- (int)  gsx_rtc_engine_preview_captured_video_set_display:(void *)in_pVoid : (void *)window :(int) x :(int) y :(int) width :(int) height;
- (int)  gsx_rtc_engine_preview_captured_video_start:(void *)in_pVoid;
- (int)  gsx_rtc_engine_preview_captured_video_stop:(void *)in_pVoid;

// 上传音视频数据
- (int)  gsx_rtc_engine_push_media_start:(void *)in_pVoid :( const char *)in_pPushUrl :(int) in_nPushType :(int) in_nRemoteId :(const char *)in_pStreamName;
- (int)  gsx_rtc_engine_push_media_stop:(void *)in_pVoid :(int) in_nPushId;

// 直播信息，用于统计
- (int)  gsx_rtc_engine_get_live_play_info:(void *)in_pVoid :(int) in_nPlayId : (GsxLivePlayInfo *)out_pPlayInfo;

@end

#pragma GCC visibility pop
