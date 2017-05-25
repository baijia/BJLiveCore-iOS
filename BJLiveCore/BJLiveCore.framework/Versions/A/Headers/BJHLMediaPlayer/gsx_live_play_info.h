#ifndef _GSX_LIVE_PLAYER_INFO_H_
#define _GSX_LIVE_PLAYER_INFO_H_

/*连接状态*/
typedef enum tagGsxLiveConnectStatus {
    GSX_CONNECT_STATUS_NON_CONNECTED = 0,               // 未连接
    GSX_CONNECT_STATUS_CONNECTING = 1,                  // 正在连接
    GSX_CONNECT_STATUS_CONNECTED = 2,                   // 已连接
} GsxLiveConnectStatus;

/*统计参数*/
typedef struct tagGsxLivePlayInfo {
//  char                        watchId;                // 收看的视频源用户ID
    GsxLiveConnectStatus        connectStatus;          // 网络连接状态
    char                        connectIp[128];         // 服务器的ip地址
    int                         totalBytes;             // 服务器转发的总包数
    int                         dropBytes;              // 服务器转发的丢包数
    int                         upKbits;                // 本链接的上行带宽
    
    int                         audioTotalBytes;      // 服务器转发的音频总包数
    int                         audioDropBytes;       // 服务器转发的音频丢包数
    int                         audioUpKbits;         // 本链接的音频上行带宽
    
    int                         videoTotalBytes;      // 服务器转发的视频总包数
    int                         videoDropBytes;       // 服务器转发的视频丢包数
    int                         videoUpKbits;         // 本链接的上行视频带宽
    /* stream */
    int                         currentBytesPerSecond;  // 总码流（下载速度）
    int                         droppedFrames;          // 丢包数
    int                         maxBytesPerSecond;      // 最大码流
    int                         bufferTimeMax;          // 设置的最大缓冲时间
    int                         liveDelay;              // 延迟（可选）
    int                         videoBufferLength;      // 视频瞬时缓冲时长
    int                         videoBufferByteLength;  // 视频瞬时缓冲字节（可选）
    int                         videoBytesPerSecond;    // 视频码流
    int                         videoLossRate;          // 视频丢包率（可选）
    int                         videoCodec;             // 视频编码器（编号）
    int                         audioBufferLength;      // 音频瞬时缓冲时长
    int                         audioBufferByteLength;  // 音频瞬时缓冲字节（可选）
    int                         audioBytesPerSecond;    // 音频码流
    int                         audioLossRate;          // 音频丢包率（可选）
    int                         audioCodec;             // 音频编码器（编号）
} GsxLivePlayInfo;

#endif