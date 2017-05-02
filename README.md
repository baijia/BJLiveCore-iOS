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

## 工程设置

- 隐私权限：在 `Info.plist` 中添加麦克风、摄像头、相册访问描述；
```
Privacy - Microphone Usage Description       用于语音上课、发言
Privacy - Camera Usage Description           用于视频上课、发言，拍照上传课件、聊天发图
Privacy - Photo Library Usage Description    用于上传课件、聊天发图
```
- 后台任务：在 `Project > Target > Capabilities` 中打开 `Background Modes` 开关、选中 `Audio, AirPlay, and Picture in Picture`；

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
// 教室 ID 方式
BJLUser *user = [BJLUser userWithNumber:userNumber
                                   name:userName
                                 avatar:userAvatar
                                   role:userRole];
self.room = [BJLRoom roomWithID:roomID
                        apiSign:apiSign
                           user:user];
// 参加码方式
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
             if (self.room.loginUser.isTeacher) {
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
             if (self.room.loginUser.isTeacher) {
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
- 调用 `enter` 方法后 `room.loadingVM` 将被初始化，可用于显示加载度、成功和失败等，成功/失败后为空；
- 其它 VM 在 loading 过程被初始化，当 `vmsAvailable` 变为 YES 时 **可开始监听 VM 的属性、方法调用**，在进入教室后、`inRoom` 变为 YES 时可用 —— **可调用方法、发起请求**；
- 所有 VM 及其所有属性支持 `KVO` 以便监听状态变化，除非额外注释说明；
- 无法通过 `KVO` 实现的事件（如有用户退出教室）可监听方法调用，返回类型值为 `BJLObservable` 的方法表示可监听；

## WIKI

- **[ChangeLog](./wiki/CHANGELOG.md)**
- **[Block 的使用](./wiki/blocks.md)**

## API

- [BJLConstants.h](./BJLiveCore/Headers/BJLConstants.h) 枚举
- [NSError+BJLError.h](./BJLiveCore/Headers/NSError+BJLError.h) 错误码
- [BJLRoom.h](./BJLiveCore/Headers/BJLRoom.h) 教室管理
- [BJLLoadingVM.h](./BJLiveCore/Headers/BJLLoadingVM.h) 进教室的 loading 状态
- [BJLRoomVM.h](./BJLiveCore/Headers/BJLRoomVM.h) 教室信息、状态，用户信息，公告等
- [BJLOnlineUsersVM.h](./BJLiveCore/Headers/BJLOnlineUsersVM.h) 在线用户
- [BJLSpeakingRequestVM.h](./BJLiveCore/Headers/BJLSpeakingRequestVM.h) 发言申请/处理
- [BJLMediaVM.h](./BJLiveCore/Headers/BJLMediaVM.h) 音视频设置
- [BJLRecordingVM.h](./BJLiveCore/Headers/BJLRecordingVM.h) 音视频采集 - 个人
- [BJLPlayingVM.h](./BJLiveCore/Headers/BJLPlayingVM.h) 音视频播放 - 他人
- [BJLSlideVM.h](./BJLiveCore/Headers/BJLSlideVM.h) 课件管理
- [BJLSlideshowUI.h](./BJLiveCore/Headers/BJLSlideshowUI.h) 课件、画笔视图
- [BJLServerRecordingVM.h](./BJLiveCore/Headers/BJLServerRecordingVM.h) 云端录制
- [BJLChatVM.h](./BJLiveCore/Headers/BJLChatVM.h) 聊天/弹幕

