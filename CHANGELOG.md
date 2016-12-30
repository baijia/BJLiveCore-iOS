Change Log
=========

标记为 **粗体** 的改动需要特别留意；

## 0.0.4

- **`BJLBlockKVO` 重要升级**：  
`BJLKVOBlock` 返回值类型由 `void` 改为 `BOOL`，以便更容易地取消 KVO；  
解决一个对象对自己 KVO 时可能会产生崩溃的问题；  
解决取消 KVO 时可能出现 `Exception` 的问题；  

- **新增进教室成功、失败回调，原成功事件方法废弃，原失败事件方法只用于退出教室**；
```objc
- (BJLOEvent)enterRoomSuccess;
- (BJLOEvent)enterRoomFailureWithError:(BJLError *)error;
```

- **优化错处理，主动退出教室时 `error` 为 `nil`**，删除原来表示主动退出教室的错误码 ~~`BJLErrorCode_exitRoom_exitRoom`~~；

- **简化错误码**，参考 [NSError+BJLError.h](https://github.com/baijia/BJLiveCore-iOS/blob/master/BJLiveCore/NSError+BJLError.h)；

- **内部不主动调用的一些方法，改为进入教室后、掉线重连成功后自动调用一次**，包括
```objc
- [BJLGiftVM loadReceivedGifts];
- [BJLOnlineUsersVM loadMoreOnlineUsersWithCount:];
- [BJLPlayingVM loadPlayingUsers];
- [BJLSlideshowVM loadAllDocuments];
```

- 方法命名优化，**几个标记 `DEPRECATED` 的方法将在正式发版时移除、请及时改用正确的方法**；

- **支持教室连接断开重连**，上层可自由决定是否重连，监听重连进度、结果；

- 完善云端录课逻辑，开始录课时将发起网络请求、检查云端录课是否可用；
```objc
 /** 开始/停止云端录课
 上课状态下才能录课
 此方法需要发起网络请求、检查云端录课是否可用
 - 如果可以录课则开始、并设置 serverRecording
 - 否则发送失败通知 requestServerRecordingDidFailed: */
- (nullable BJLError *)requestServerRecording:(BOOL)on;
/** 检查云端录课不可用的通知
 包括网络请求失败 */
- (BJLOEvent)requestServerRecordingDidFailed:(NSString *)message;
```

- 课件显示支持更多参数设置，参考 [BJLSlideshowUI.h](https://github.com/baijia/BJLiveCore-iOS/blob/master/BJLiveCore/BJLSlideshowUI.h)；

- `BJLMediaVM` 支持获取音视频流调试信息；
```objc
/** 调试: 获取音视频流信息 */
- (NSArray<NSString *> *)avDebugInfo;
```

- BUG 修复，主要解决音视频问题；

- Demo: 增加发言被关闭的提示、完善举手逻辑、增加 TCP&UDP 切换、增加断开重连提示、聊天输入框内输入 `-av` 开启音视频流信息打印、其它改进；

