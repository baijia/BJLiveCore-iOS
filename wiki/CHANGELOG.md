Change Log
==========

- 标记为 **粗体** 的改动需要特别留意；
- 被标记 `DEPRECATED` 的代码 **将在 `1.0` 版本移除**；

## 0.1.0

- 此版本对 Block 的使用进行了全面升级，解决了使用中暴露出来的严重问题、改善了 API 调用，因此集成 SDK 的代码需要做一些升级；
- 原有使用 Block 进行 `KVO` 和 `监听方法调用` 的相关方法被标记 `DEPRECATED`，个别方法因为不合理被直接废弃、有更好的替代实现；
- 新方法参考的定义及使用，可参考 `NSObject+BJLObserving.h`、[Block 的使用](./blocks.md) 以及 [Demo](https://github.com/baijia/BJLiveCore-iOS) 中的源码；

##### 1. 重新实现 Block KVO

- KVO 调用方式：

属性名支持代码自动完成，而不再是 selector 或者 keypath，从而避免出错；
```objc
weakdef(self);
[self bjl_kvo:BJLMakeProperty(self.room.roomVM, // 对象
                              liveStarted) // 属性名
       filter:^BOOL(NSNumber *old, NSNumber *now) { // 过滤
           return old.boolValue != now.boolValue;  // 返回 NO 丢弃
       }
     observer:^BOOL(NSNumber *old, NSNumber *now) { // 处理
       strongdef(self);
       [self.console printFormat:@"liveStarted: %@", NSStringFromBOOL(now.boolValue)];
       return YES; // 返回 NO 停止监听
   }];
```
对比以前：
```objc
weakdef(self);
[self bjl_KVObserve:self.room.roomVM // 对象
             getter:@selector(liveStarted) // 属性对应的 selector，属性名和 getter 方法名不一样可使用带有 keypath: 的方法
             filter:^BOOL(NSNumber *old, NSNumber *now) { // 过滤
                 return old.boolValue != now.boolValue;
             }
         usingBlock:^BOOL(NSNumber *old, NSNumber *now) { // 处理
             strongdef(self);
             [self.console printFormat:@"liveStarted: %@", NSStringFromBOOL(now.boolValue)];
             return YES;
         }];
```

- 支持两种方式取消某次 KVO；
```objc
weakdef(self);
id<BJLObservation> observation =
    [self bjl_kvo:BJLMakeProperty(self.room.roomVM, liveStarted)
         observer:^BOOL(NSNumber *old, NSNumber *now) {
           strongdef(self);
           [self.console printFormat:@"liveStarted: %@", NSStringFromBOOL(now.boolValue)];
           return YES; // 1. 返回 NO 取消 KVO
       }];
[observation stopObserving]; // 2. 取消 KVO
```

- **不在支持** 通过 `object+keyPath` 取消 KVO 的方法，因为同一 `对象+属性` 可能被多次 KVO，该方法无法区分，很容易衍生 BUG：
```objc
- (void)bjl_stopKVObserving:(nullable NSObject *)object forKeyPath:(nullable NSString *)keyPath NS_UNAVAILABLE;
```

##### 2. 重新实现 Block 监听方法调用

- 监听方法调用，支持 filter - 可选：

`BJLMakeMethod(TARGET, METHOD)` 会断言 TARGET 是否实现了 METHOD 方法，以便发现错误；
```objc
weakdef(self);
[self bjl_observe:BJLMakeMethod(self.room, // 对象
                                roomWillExitWithError:) // 方法
           filter:^BOOL(BJLError *error) { // 过滤
               return !!error; // 返回 NO 丢弃
           }];
         observer:^BOOL(BJLError *error) { // 处理
             strongdef(self);
             [self.console printFormat:@"roomWillExitWithError: %@", error];
             return YES; // 返回 NO 停止监听
         }];
```
对比以前：
```objc
weakdef(self);
[self bjl_observe:self.room // 对象
            event:@selector(roomWillExitWithError:) // 事件 selector
       usingBlock:^(BJLError *error) { // 处理
           strongdef(self);
           if (error) {
               [self.console printFormat:@"roomWillExitWithError: %@", error];
           }
       }];
```

- 支持 **简单类型参数**：
> 使用 `BOOL`、`char`、`short`、`float` 等类型会产生警告，将 block 强转为 `BJLMethodFilter` 或 `BJLMethodObserver` 既可解决；
```objc
weakdef(self);
[self bjl_observe:BJLMakeMethod(self.room.speakingRequestVM, speakingBeRemoteEnabled:)
         observer:(BJLMethodObserver)^BOOL(BOOL enabled) {
             [self.console printFormat:@"发言状态被%@", enabled ? @"开启" : @"关闭"];
             return YES;
         }];
```
以前需要使用 `NSNumber` 包装：
```objc
weakdef(self);
[self bjl_KVObserve:self.room.speakingRequestVM
             getter:@selector(speakingDidRemoteEnabled:)
         usingBlock:^BOOL(NSNumber *enabled) {
             strongdef(self);
             [self.console printFormat:@"发言状态被%@", enabled.boolValue ? @"开启" : @"关闭"];
             return YES;
         }];
```

- 支持 **多个参数**：
```objc
weakdef(self);
[self bjl_observe:BJLMakeMethod(self.room.playingVM, playingUserDidUpdate:old:)
         observer:^BOOL(NSObject<BJLOnlineUser> *old,
                        NSObject<BJLOnlineUser> *now) {
             strongdef(self);
             [self.console printFormat:@"playingUserDidUpdate:old: %@ >> %@", old, now];
         }];
```
以前需要使用稍显晦涩的模拟元组：
```objc
weakdef(self);
[self bjl_observe:self.room.playingVM
            event:@selector(playingUserDidUpdate:)
       usingBlock:^BOOL(BJLTuple *tuple) {
           BJLTupleUnpack(tuple) = ^(NSObject<BJLOnlineUser> *old,
                                     NSObject<BJLOnlineUser> *now) {
               strongdef(self);
               [self.console printFormat:@"playingUserDidUpdate: %@ >> %@", old, now];
           };
       }];
```

- 支持两种方式取消某次监听；
```objc
weakdef(self);
id<BJLObservation> observation =
    [self bjl_observe:BJLMakeMethod(self.room, roomWillExitWithError:)
             observer:^BOOL(BJLError *error) {
                 strongdef(self);
                 [self.console printFormat:@"roomWillExitWithError: %@", error];
                 return YES; // 1. 返回 NO 取消监听
             }];
[observation stopObserving]; // 2. 取消监听
```

- **不再支持** 通过 `object+selector` 取消监听的方法，因为同一 `对象+方法` 可能被多次监听，该方法无法区分，很容易衍生 BUG：
```objc
- (void)bjl_stopObserving:(nullable id)object event:(nullable SEL)event NS_UNAVAILABLE;
```

- 个别 ViewModel 的方法升级：
```objc
// BJLHelpVM.h
- (BJLObservable)requestForHelpFinished:(BOOL)success;
// BJLPlayingVM.h
- (BJLObservable)playingUserDidUpdate:(NSObject<BJLOnlineUser> *)now
                                  old:(NSObject<BJLOnlineUser> *)old;
// BJLRecordingVM.h
- (BJLObservable)recordingDidRemoteChangedRecordingAudio:(BOOL)recordingAudio
                                          recordingVideo:(BOOL)recordingVideo
                                   recordingAudioChanged:(BOOL)recordingAudioChanged
                                   recordingVideoChanged:(BOOL)recordingVideoChanged;
// BJLSpeakingRequestVM.h
- (BJLObservable)speakingBeRemoteEnabled:(BOOL)enabled;
```
对应的原方法标记 `DEPRECATED`：
```objc
// BJLHelpVM.h
- (BJLObservable)requestForHelpDidFinished:(NSNumber *)success DEPRECATED_MSG_ATTRIBUTE("use `requestForHelpFinished:`");
// BJLPlayingVM.h
 - (BJLObservable)playingUserDidUpdate:(BJLTuple<void (^)(NSObject<BJLOnlineUser> *old,
                                                         NSObject<BJLOnlineUser> *now)> *)tuple DEPRECATED_MSG_ATTRIBUTE("use `playingUserDidUpdate:old:`");
// BJLRecordingVM.h
- (BJLObservable)recordingDidRemoteChanged:(BJLTuple<void (^)(BOOL recordingAudio,
                                                              BOOL recordingVideo,
                                                              BOOL recordingAudioChanged,
                                                              BOOL recordingVideoChanged)> *)tuple;
                                                              BOOL recordingVideoChanged)> *)tuple DEPRECATED_MSG_ATTRIBUTE("use `recordingDidRemoteChangedRecordingAudio:recordingVideo:recordingAudioChanged:recordingVideoChanged:`");
// BJLSpeakingRequestVM.h
- (BJLObservable)speakingDidRemoteEnabled:(NSNumber *)enabled DEPRECATED_MSG_ATTRIBUTE("use `speakingWasRemoteEnabled:`");
```

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

- **简化错误码**，参考 [NSError+BJLError.h](../BJLiveCore/Headers/NSError+BJLError.h)；

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

- 课件显示支持更多参数设置，参考 [BJLSlideshowUI.h](../BJLiveCore/Headers/BJLSlideshowUI.h)；

- `BJLMediaVM` 支持获取音视频流调试信息；
```objc
/** 调试: 获取音视频流信息 */
- (NSArray<NSString *> *)avDebugInfo;
```

- BUG 修复，主要解决音视频问题；

