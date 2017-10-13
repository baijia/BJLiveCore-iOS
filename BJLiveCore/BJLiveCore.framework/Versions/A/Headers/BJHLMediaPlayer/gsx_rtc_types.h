/*
 * gsx_rtc_types.h
 *
 * Created by yuqilin on 12/23/2015
 * Copyright (C) 2015 yuqilin <iyuqilin@foxmail.com>
 *
 */

#ifndef GSX_RTC_TYPES_H
#define GSX_RTC_TYPES_H

#include <stdint.h>

#define RTC_INVALID_CHANNEL -1

typedef enum {
    kRTCMediaTypeNone   = 0,
    kRTCMediaTypeAudio  = 0x1,
    kRTCMediaTypeVideo  = 0x2,
} RTCMediaType;

typedef enum {
    kRTCProtocolUnknown = 0,
    kRTCProtocolRTMP    = 1,
    kRTCProtocolRTP     = 2,    
} RTCProtocol;

typedef enum {
    kRTCStreamModeUnknown   = 0,
    kRTCStreamModePull      = 1,
    kRTCStreamModePush      = 2,
} RTCStreamMode;

typedef struct {
    int codec_type;
    int channels;
    int samplerate;
    int samplesize;
    int bitrate;
} RTCAudioDescription;

typedef struct {
    int codec_type;
    int width;
    int height;
    int framerate;
    int bitrate;
    int duration;
} RTCVideoDescription;

typedef enum {
    kRTCMsgNone = 0,
    kRTCMsgGetMediaInfo = 1,
    kRTCMsgGetFirstVideoFrame   = 0x11,
    kRTCMsgRenderVideoFrame     = 0xFF11,
    kRTCMsgAVPublishFail        = 0xFF301,
    
    kRTCMsgSpeechInLevel          = 20, // 声音输入级别[0-9]
    // 避免歧义或重复去除这些定义
    // kRTCMsgRtmpDownloadFailed   = 0x111,
    // kRTCMsgRtmpConnectError     = 0x112,
    // kRTCMsgRtmpConnectSuccess   = 0x113,

    // 以下消息均在回调函数参数param1中指定stream_id
    kRTCMsgAVConnectSuccess     = 100,  // 连接成功
    kRTCMsgAVConnectFail        = 101,  // 连接失败（前端切换不上报）
    kRTCMsgAVPlaySuccess        = 200,  // 播放成功，
    kRTCMsgAVPlayFail           = 201,  // 播放失败 （前端切换不上报）
    kRTCMsgAVPlayLag            = 202,  // 卡顿（上报）
    kRTCMsgAVPlaySwitch         = 203,  // 切换（前端切换并上报）
    kRTCMsgOpenAudioRecordFailed = 301, // 开启录音失败
    kRTCMsgOpenCameraFailed     = 302,  // 开启摄像头失败

    kRTCMsgStreamVideoSizeChanged = 400,    // 流视频宽高变化
} RTCEngineMsg;

typedef struct {
    int x;
    int y;
    int width;
    int height;
} RTCRect;

typedef enum {
    RTC_VIDEO_DISPLAY_MODE_DEFAULT,       // 默认显示比例，保持源片比例
    RTC_VIDEO_DISPLAY_MODE_FULL_RECT,     // 填充显示区域
    RTC_VIDEO_DISPLAY_MODE_FULL_RECT_KEEP_ASPECT_RATIO, // 保持原始比例情况下填充显示区域
    RTC_VIDEO_DISPLAY_MODE_4_3,           // 4:3
    RTC_VIDEO_DISPLAY_MODE_16_9,          // 16:9
    RTC_VIDEO_DISPLAY_MODE_MAX,           // unused
} RTCVideoDisplayMode;

typedef void (*gsx_rtc_engine_msg_callback)(void *priv, int msg, int param1, int param2);

//采集参数
typedef struct
{
    int32_t width;                  //采集宽
    int32_t height;                 //采集高
    int32_t maxFPS;                 //采集帧率
    int32_t bitrate;                //采集码率
    int32_t keyFrameInterval;       //采集关键帧间隔，单位s
} GsxVideoCaptureCapability;

//采集帧类型
typedef enum
{
    FrameType_Unknown           = 0,
    FrameType_MetaInfo          = 1, //meta 信息sps和pps
    FrameType_KeyFrame          = 2, //关键帧
    FrameType_UnkeyFrame        = 3  //非关键帧
    
} GsxCaptureFrameType;

#endif /* !GSX_RTC_TYPES_H */
