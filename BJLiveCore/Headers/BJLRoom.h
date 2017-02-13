//
//  BJLRoom.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-11-15.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "BJLBlockHelper.h"

#import "BJLConstants.h"

/** Model **/

#import "BJLUser.h"

/** VM **/

#import "BJLLoadingVM.h"

#import "BJLRoomVM.h"
#import "BJLOnlineUsersVM.h"
#import "BJLSpeakingRequestVM.h"

#import "BJLMediaVM.h"
#import "BJLRecordingVM.h"
#import "BJLPlayingVM.h"

#import "BJLSlideVM.h"
#import "BJLSlideshowVM.h"
// #import "BJLSlideshowView.h"

#import "BJLServerRecordingVM.h"

#import "BJLChatVM.h"

/** UI */

#import "BJLSlideshowUI.h"

NS_ASSUME_NONNULL_BEGIN

/*
typedef NS_ENUM(NSInteger, BJLRoomState) {
    BJLRoomState_offline,
    BJLRoomState_connecting,
    BJLRoomState_connected
}; */

/**
 直播教室
 可同时存在多个实例，但最多只有一个教室处于进入状态，后执行 `enter` 的教室会把之前的教室踢掉
 不建议退出教室后再次调用 `enter` 方法，未经测试、结果不可预期
 */
@interface BJLRoom : NSObject

#pragma mark lifecycle

/**
 通过 ID 创建教室
 @param roomID          教室 ID
 @param user            用户
 @param apiSign         API sign
 @return                教室
 */
+ (__kindof instancetype)roomWithID:(NSString *)roomID
                            apiSign:(NSString *)apiSign
                               user:(BJLUser *)user;

/**
 通过参加码创建教室
 @param roomSecret      教室参加码，目前只支持老师、学生角色
 @param userName        用户名
 @param userAvatar      用户头像 URL
 @return                教室
 */
+ (__kindof instancetype)roomWithSecret:(NSString *)roomSecret
                               userName:(NSString *)userName
                             userAvatar:(nullable NSString *)userAvatar;

/** 进入教室 */
- (void)enter;

/** 进入教室 - 成功/失败 */
- (BJLObservable)enterRoomSuccess;
- (BJLObservable)enterRoomFailureWithError:(BJLError *)error;
- (BJLObservable)roomDidEnter DEPRECATED_MSG_ATTRIBUTE("use `enterRoomSuccess` instead");

/** 断开、重连
 网络连接断开时回调，回调 callback 确认是否重连、可通过 `reloadingVM` 监听重连的进度和结果
 默认（不设置此回调）在断开时自动重连、重连过程中遇到错误将 `异常退出`
 !!!: 重连过程中通过其它 VM 发起的网络请求会被丢弃
 @param reloadingVM         重连的 loading 状态
 @param callback(reload)    调用 callback 是 reload 参数传 YES 重连，NO 将导致 `异常退出`
 */
- (void)setReloadingBlock:(void (^)(BJLLoadingVM *reloadingVM,
                                    void (^callback)(BOOL reload)))reloadingBlock;

/** 退出教室 */
- (void)exit;

/**
 退出教室 - 正常/异常
 正常退出 `error` 为 nil，否则为异常退出
 参考 `BJLErrorCode` */
- (BJLObservable)roomWillExitWithError:(nullable BJLError *)error;
- (BJLObservable)roomDidExitWithError:(nullable BJLError *)error;

#pragma mark view-model

/**
 nullable:
    所有 VM 属性都可为空
    `loadingVM` 在 loading 时非空，成功/失败后为空
    其它 VM
    - 在 loading 前为空，在 loading 过程中初始化 - 可开始监听 VM 的属性、方法调用
    - 进入教室后、`vmsAvailable` 变为 YES 时可用 - 可调用方法、发起请求
    - 退出教室后为空（loading 失败自动退出）
    - 因用户角色、帐户权限、当前端配置等原因，部分功能对应 VM 可能为空
 KVO:
    VM 所有属性支持 KVO，除非额外注释说明
 block:
    这里需要较多的使用 block 进行 KVO、事件监听，RAC 本是个很好的选择，但为避免依赖过多的开源库而被放弃
    使用 block 进行 KVO - NSObject+BJLObserving.h
    使用 block 监听方法调用 - NSObject+BJLObserving.h
    tuple pack&unpack - NSObject+BJL_M9Dev.h
    更多实用实例参考 BJLiveUI - https://github.com/baijia/BJLiveUI-iOS
 */

/** VM 初始化状态，值为 YES 时 VM 可用
 KVO 此属性时 option 包含 initial(默认包含)，即使开始 KVO 时值已经是 YES 也会执行 KVO 回调
 参考 NSObject+BJLObserving.h */
@property (nonatomic, readonly) BOOL vmsAvailable;

/** 进教室的 loading 状态 */
@property (nonatomic, readonly, nullable) BJLLoadingVM *loadingVM;

/** 教室信息、状态，用户信息，公告等 */
@property (nonatomic, readonly, nullable) BJLRoomVM *roomVM;

/** 在线用户 */
@property (nonatomic, readonly, nullable) BJLOnlineUsersVM *onlineUsersVM;

/** 发言申请/处理 */
@property (nonatomic, readonly, nullable) BJLSpeakingRequestVM *speakingRequestVM;

/** 音视频 设置 */
@property (nonatomic, readonly, nullable) BJLMediaVM *mediaVM;

/** 音视频 采集 - 个人 */
@property (nonatomic, readonly, nullable) BJLRecordingVM *recordingVM;
/** 视频采集视图 - 个人
 尺寸、位置随意设定，建议横屏 4:3、竖屏 3:4 */
@property (nonatomic, readonly, nullable) UIView *recordingView;

/** 音视频 播放 - 他人 */
@property (nonatomic, readonly, nullable) BJLPlayingVM *playingVM;
/** 视频播放视图 - 他人
 尺寸、位置随意设定，建议横屏 4:3、竖屏 3:4 */
@property (nonatomic, readonly, nullable) UIView *playingView;

/** 课件管理 */
@property (nonatomic, readonly, nullable) BJLSlideVM *slideVM;

/** 课件显示、控制 */
// @property (nonatomic, readonly, nullable) BJLSlideshowVM *slideshowVM;
/** 课件、画笔视图
 尺寸、位置随意设定 */
@property (nonatomic, readonly, nullable) UIViewController<BJLSlideshowUI> *slideshowViewController;

/** 云端录制 */
@property (nonatomic, readonly, nullable) BJLServerRecordingVM *serverRecordingVM;

/** 聊天/弹幕 */
@property (nonatomic, readonly, nullable) BJLChatVM *chatVM;

@end

#pragma mark -

/** 通过 ID 创建的教室 */
@interface BJLRoom_ID : BJLRoom

@property (nonatomic, readonly, copy) NSString *ID, *apiSign;
@property (nonatomic, readonly) BJLUser *user;

@end

/** 通过参加码创建的教室 */
@interface BJLRoom_Secret : BJLRoom

@property (nonatomic, readonly, copy) NSString *roomSecret, *userName;
@property (nonatomic, readonly, nullable, copy) NSString *userAvatar;

@end

NS_ASSUME_NONNULL_END
