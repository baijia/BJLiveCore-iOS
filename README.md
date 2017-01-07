BJLiveCore
==========

## 功能简介

- 教室：直播间；
- 老师：主讲人，拥有最高权限；
- 助教：管理员，拥有部分老师的权限，**移动端不支持助教登录**；
- 学生：听讲人，权限受限，不支持 设置上下课、发公告、处理他人举手、远程开关他人音视频、开关录课、开关聊天禁言；
- 上课、下课：上课中才能举手、发言、录课；
- 举手：学生申请发言，老师和管理员可以允许或拒绝；
- 发言：发布音频、视频，SDK 层面发言不要求举手状态；
- 录课：云端录制课程；
- 聊天/弹幕：目前只支持群发；
- 白板、课件、画笔：课件第一页是白板，后面是老师上传的课件，白板和每一页课件都支持画笔；

## 工程设置

- 隐私权限：在 `Info.plist` 中添加麦克风、摄像头、相册访问描述；
```
Privacy - Microphone Usage Description
Privacy - Camera Usage Description
Privacy - Photo Library Usage Description
```
- 后台任务：在 `Project > Target > Capabilities` 中打开 `Background Modes` 开关、选中 `Audio, AirPlay, and Picture in Picture`；

## 集成 SDK

BJLiveCore 会依赖一些第三方库，建议使用 CocoaPods 方式集成；
- Podfile 中设置 source
```ruby
source 'https://github.com/CocoaPods/Specs.git'
source 'https://github.com/baijia/specs.git'
```
- Podfile 中引入 BJLiveCore
```ruby
pod 'BJLiveCore'
```

## Hello World

参考 demo 中的 `BJRoomViewController`；
- 引入头文件
```objc
#import <BJLiveCore/BJLiveCore.h>
```
- 定义教室属性
```objc
@property (nonatomic) BJLRoom *room;
```
- 创建教室
```objc
self.room = [BJLRoom roomWithSecret:roomSecret
                           userName:userName
                         userAvatar:nil];
```
- 监听进入、退出教室的事件
```objc
weakdef(self);
[self bjl_observe:BJLMakeMethod(self.room, roomDidEnter)
         observer:^BOOL(id data) {
             strongdef(self);
             if (self.room.roomVM.loginUser.isTeacher) {
                 [self.room.roomVM sendLiveStarted:YES]; // 通知学生上课
             }
             else {
                 [self bjl_kvo:BJLMakeProperty(self.room.roomVM, liveStarted)
                        filter:^BOOL(NSNumber *old, NSNumber *now) {
                            return old.boolValue != now.boolValue;
                        }
                      observer:^(NSNumber *old, NSNumber *now) {
                        strongdef(self);
                        [self.console printFormat:@"liveStarted: %@", NSStringFromBOOL(now.boolValue)];
                    }];
             }
             [self didEnterRoom]; // 处理进教室后的逻辑
             return YES;
         }];
[self bjl_observe:BJLMakeMethod(self.room, roomWillExitWithError:)
         observer:^BOOL(BJLError *error) {
             strongdef(self);
             if (self.room.roomVM.loginUser.isTeacher) {
                 [self.room.roomVM sendLiveStarted:NO]; // 通知学生下课
             }
             return YES;
         }];
```
- 进入教室
```objc
[self.room enter];
```
- 老师发布音视频
```objc
// UI
[self.recordingView addSubview:self.room.recordingView];
[self.room.recordingView mas_makeConstraints:^(MASConstraintMaker *make) {
    make.edges.equalTo(self.recordingView);
}];
// 采集
[self.room.recordingVM setRecordingAudio:YES recordingVideo:YES];
```
- 学生获取音视频发言列表、打开老师视频
```objc
// UI
[self.playingView addSubview:self.room.playingView];
[self.room.playingView mas_makeConstraints:^(MASConstraintMaker *make) {
    make.edges.equalTo(self.playingView);
}];
// 播放
for (NSObject<BJLOnlineUser> *user in self.room.playingVM.playingUsers) {
    if (user.isTeacher) {
        [self.room.playingVM updateVideoPlayingUserWithID:user.ID];
        break;
    }
}
```
- 学生举手申请发言
```objc
[self.room.speakingRequestVM sendSpeakingRequest];
```
- 举手后老师同意/拒绝发言申请
```objc
weakdef(self);
[self bjl_observe:BJLMakeMethod(self.room.speakingRequestVM, receivedSpeakingRequestFromUser:)
         observer:^BOOL(NSObject<BJLUser> *user) {
             strongdef(self);
             [self.room.speakingRequestVM replySpeakingRequestToUserID:user.ID allowed:YES]; // 同意举手
             return YES;
         }];
```
- 老师同意后学生开始发言
```objc
weakdef(self);
[self bjl_observe:BJLMakeMethod(self.room.speakingRequestVM, speakingRequestDidReply:)
         observer:^BOOL(NSObject<BJLSpeakingReply> *reply) {
             strongdef(self);
             if (reply.speakingEnabled) {
                 [self.room.recordingVM setRecordingAudio:YES recordingVideo:NO]; // 发布音频
             }
             return YES;
         }];
```

## 设计

- `BJLRoom` 是直播功能的入口，用于处理创建、进入、退出教室；
- 调用 `enter` 方法后 `room` 变成 `active` 状态，之前的教室将被强制退出，退出后变为 `inactive` 状态；
- 教室内各个功能通过对应的 `ViewModel`（以下简称 `VM`）来管理，所有 VM 都可为空；
- 调用 `enter` 方法后 `room.loadingVM` 将被初始化，可用于显示加载度、成功和失败等；
- 成功进教室后其它 VM 将被初始化，在 `roomDidEnter` 时可用；
- 所有 VM 及其所有属性支持 `KVO` 以便监听状态变化，除非额外注释说明；
- 无法通过 `KVO` 实现的事件（如有用户退出教室）可监听方法调用，返回类型值为 `BJLObservable` 的方法表示可监听；

## Block 的使用

为了开发方便，这里大量的使用了 `block`（`RAC` 本是个很好的选择，但为避免依赖过多的第三方库而被放弃）：  
- KVO，参考 `NSObject+BJLObserving.h`
```objc
weakdef(self);
[self bjl_kvo:BJLMakeProperty(self.room.roomVM, // 对象
                              liveStarted) // 属性
       filter:^BOOL(NSNumber *old, NSNumber *now) { // 过滤
           return old.boolValue != now.boolValue;  // 返回 NO 丢弃
       }
     observer:^BOOL(NSNumber *old, NSNumber *now) { // 处理
       strongdef(self);
       [self.console printFormat:@"liveStarted: %@", NSStringFromBOOL(now.boolValue)];
       return YES; // 返回 NO 停止监听
   }];
```
- 监听方法调用，参考 `NSObject+BJLBlockNTO.h`
> 支持使用 **简单类型参数** 和 **多个参数**，使用 `BOOL`、`char`、`short`、`float` 等类型会产生警告，将 block 强转为 `BJLMethodFilter` 或 `BJLMethodObserver` 既可解决；
```objc
- (BJLObservable)roomWillExitWithError:(BJLError *)error;
```
```objc
weakdef(self);
[self bjl_observe:BJLMakeMethod(self.room, // 对象
                                roomWillExitWithError:) // 方法
           filter:(BJLMethodFilter)^BOOL(BJLError *error) { // 过滤
               return !!error; // 返回 NO 丢弃
           }];
         observer:(BJLMethodObserver)^BOOL(BJLError *error) { // 处理
             strongdef(self);
             [self.console printFormat:@"roomWillExitWithError: %@", error];
             return YES; // 返回 NO 停止监听
         }];
```
- 模拟元组，参考 `NSObject+BJL_M9Dev.h`
> 支持使用 **简单类型参数** 和 **多个参数**；
```objc
// 定义: 此方法返回一个包含两个 BOOL 型变量的元组
- (BJLTuple<void (^)(BOOL state1, BOOL state2> *)states;
```
```objc
// 拆包: 这个 block 会被立即执行，因此这里不需要 weakify&strongify
BJLTupleUnpack(tuple) = ^(BOOL state1, BOOL state2) {
    NSLog(@"state1: %d, state2: %d", state1, state2);
};
```

## API

**[ChangeLog](https://github.com/baijia/BJLiveCore-iOS/blob/master/wiki/CHANGELOG.md)**
**[Blocks](https://github.com/baijia/BJLiveCore-iOS/blob/master/wiki/blocks.md)**

- [BJLConstants.h](https://github.com/baijia/BJLiveCore-iOS/blob/master/BJLiveCore/BJLConstants.h) 枚举
- [NSError+BJLError.h](https://github.com/baijia/BJLiveCore-iOS/blob/master/BJLiveCore/NSError+BJLError.h) 错误码
- [BJLRoom.h](https://github.com/baijia/BJLiveCore-iOS/blob/master/BJLiveCore/BJLRoom.h) 教室管理
- [BJLLoadingVM.h](https://github.com/baijia/BJLiveCore-iOS/blob/master/BJLiveCore/BJLLoadingVM.h) 进教室的 loading 状态
- [BJLRoomVM.h](https://github.com/baijia/BJLiveCore-iOS/blob/master/BJLiveCore/BJLRoomVM.h) 教室信息、状态，用户信息，公告等
- [BJLOnlineUsersVM.h](https://github.com/baijia/BJLiveCore-iOS/blob/master/BJLiveCore/BJLOnlineUsersVM.h) 在线用户
- [BJLSpeakingRequestVM.h](https://github.com/baijia/BJLiveCore-iOS/blob/master/BJLiveCore/BJLSpeakingRequestVM.h) 发言申请/处理
- [BJLMediaVM.h](https://github.com/baijia/BJLiveCore-iOS/blob/master/BJLiveCore/BJLMediaVM.h) 音视频设置
- [BJLRecordingVM.h](https://github.com/baijia/BJLiveCore-iOS/blob/master/BJLiveCore/BJLRecordingVM.h) 音视频采集 - 个人
- [BJLPlayingVM.h](https://github.com/baijia/BJLiveCore-iOS/blob/master/BJLiveCore/BJLPlayingVM.h) 音视频播放 - 他人
- [BJLSlideVM.h](https://github.com/baijia/BJLiveCore-iOS/blob/master/BJLiveCore/BJLSlideVM.h) 课件管理
- [BJLSlideshowUI.h](https://github.com/baijia/BJLiveCore-iOS/blob/master/BJLiveCore/BJLSlideshowUI.h) 课件、画笔视图
- [BJLServerRecordingVM.h](https://github.com/baijia/BJLiveCore-iOS/blob/master/BJLiveCore/BJLServerRecordingVM.h) 云端录制
- [BJLChatVM.h](https://github.com/baijia/BJLiveCore-iOS/blob/master/BJLiveCore/BJLChatVM.h) 聊天/弹幕

