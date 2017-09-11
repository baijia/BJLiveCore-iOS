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

/** model **/

#import "BJLRoomInfo.h"
#import "BJLUser.h"
#import "BJLFeatureConfig.h"

/** view & vm **/

#import "BJLLoadingVM.h"

#import "BJLRoomVM.h"
#import "BJLOnlineUsersVM.h"
#import "BJLSpeakingRequestVM.h"

#import "BJLMediaVM.h"
#import "BJLRecordingVM.h"
#import "BJLPlayingVM.h"

#import "BJLSlideVM.h"
#import "BJLSlideshowVM.h"

#import "BJLServerRecordingVM.h"

#import "BJLChatVM.h"

/** ui */

#import "BJLSlideshowUI.h"

NS_ASSUME_NONNULL_BEGIN

/**
 nullable:
 SDK 中使用 `nullable` 来标记属性、参数是否可以为 nil，一般不再特别说明
 - 未标记 `nullable` 的属性、参数，调用时传入 nil 结果不可预期
 - 未标记 `nonnull` 的属性，读取时不保证非 nil —— 即使在 NS_ASSUME_NONNULL 内，因为可能没有初始化
 
 block:
 这里需要较多的使用 block 进行 KVO、方法监听等（RAC 本是个很好的选择、但为避免依赖过多的开源库而被放弃）
 - vm 所有属性支持 KVO，除非额外注释说明，参考 NSObject+BJLObserving.h
 - vm 返回值类型为 BJLObservable 的方法支持方法监听，参考 NSObject+BJLObserving.h
 - tuple pack&unpack，参考 NSObject+BJL_M9Dev.h
 更多应用实例参考 BJLiveUI - https://github.com/baijia/BJLiveUI-iOS
 
 vm: view-model
 vm 用于管理各功能模块的状态、数据等，参考 `BJLRoom` 的各 vm 属性
 
 lifecycle:
 0. 创建教室
 通过 `roomWithID:apiSign:user:` 或 `roomWithSecret:userName:userAvatar:` 方法获得 `BJLRoom`
 此时 `roomInfo`、`loginUser` 以及包括 `loadingVM` 在内所有 vm、view 为都为 nil，`vmsAvailable`、`inRoom` 为 NO
 1. 进入教室
 调用 `enter` 进入教室，开始 loading
 2. loading
 `loadingVM` 从 loading 开始可用，直到结束变为 nil，参考 `BJLLoadingVM`
 loading 每一步的正常完成、询问、出错都有回调，回调中可实现出错重试等逻辑，`loadingVM.suspendBlock`
 2.1. 检查网络是否可用、是否是 WWAN 网络
 2.2. 获取教室、用户及教室配置等信息，成功后 `roomInfo` 和 `loginUser` 变为可用、但 vm、view 为 nil
 2.3. 建立服务器连接，`vmsAvailable` 在开始连接之前变为 YES、各 vm、view 变为非 nil，可开始监听 vm 的属性、方法调用以及显示 view，
 但 vm 的状态、数据没有与服务端同步，调用 vm 方法时发起的网络请求会被丢弃、甚至产生不可预期的错误，断开重连时类似
 2.4. 进入教室成功、loading 状态结束，`loadingVM` 变为 nil、`inRoom` 变为 YES、调用 `enterRoomSuccess`，
 此时 vm 的数据已经和服务端同步、可调用 vm 方法
 因用户角色、帐户权限、客户端配置等原因，部分功能对应 vm 可能一直为 nil
 3. 进教室成功、失败
 进教室成功、失败分别调用 `enterRoomSuccess`、`enterRoomFailureWithError:`，失败原因参考 `BJLError`
 4. 断开、重连
 参考 `setReloadingBlock:`
 5. 主动/异常退出
 主动退出调用 `exit`、异常退出包括断开重连、在其它设备登录、主动退出等
 除进教室失败以外的退出都会调用 `roomWillExitWithError:` 和 `roomDidExitWithError:`，主动退出时 error 为 nil
 退出教室后各 vm、view、`vmsAvailable`、`inRoom` 均被重置
 */

/**
 教室状态
 TODO:
 1、网络检查放在 UI 层；
 2、roomInfo 和 featureConfig 合并；
 3、roomServer、chatServer、mediaPlayer 改在 roomInfo 后创建 —— 否则连接 masterServer 后创建、初始化 vmsAvailable 无法映射到 state；
 4、chatServer 从连接步骤移除，不阻塞进教室流程；
 */
typedef NS_ENUM(NSInteger, BJLRoomState) {
    /** 初始状态 */
    BJLRoomState_initialized,
    /** 教室信息加载中 */
    BJLRoomState_loadingInfo,
    /** 教室信息加载完成 */
    BJLRoomState_loadedInfo,
    /** 教室信息加载失败 */
    // BJLRoomState_loadedInfoFailed = BJLRoomState_initialized + loadInfoError
    /** 服务连接中 */
    BJLRoomState_connectingServer,
    /** 服务连接成功 */
    BJLRoomState_connectedServer,
    /** 服务连接失败/断开 */
    // BJLRoomState_connectServerFailed = BJLRoomState_loadedInfo + connectServerError
    /** 退出教室 */
    BJLRoomState_exited
    /** 异常退出教室 */
    // BJLRoomState_exitedWithError = BJLRoomState_exited + exitError
};

/**
 直播教室
 可同时存在多个实例，但最多只有一个教室处于进入状态，后执行 `enter` 的教室会把之前的教室踢掉
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

/**
 教室状态
 正常流程: initialized > loadingInfo > loadedInfo > connectingServer > connectedServer > exited
 加载教室信息出错: loadingInfo > initialized + loadInfoError
 服务器连接出错/断开: connectingServer > loadedInfo + connectServerError
 随时退出: any > exited
 `state` 属性支持 KVO、各种 `error` 不支持 KVO，`state` 发生变化时各 `error` 可用
 */
@property (nonatomic, readonly) BJLRoomState state;
@property (nonatomic, readonly, nullable) BJLError *loadInfoError, *connectServerError, *exitError; // NON-KVO
- (BJLObservable)loadingInfoDidStart;
- (BJLObservable)loadingInfoSuccess;
- (BJLObservable)loadingInfoFailureWithError:(BJLError *)error;
- (BJLObservable)connectingServerDidStart;
- (BJLObservable)connectingServerSuccess;
- (BJLObservable)connectingServerFailureWithError:(BJLError *)error;
- (BJLObservable)serverDidDisconnect;

/**
 在 `enterRoomSuccess` 和 `roomDidExitWithError:` 之间是 YES，包括断开重连
 */
@property (nonatomic, readonly) BOOL inRoom; // DEPRECATED_MSG_ATTRIBUTE("state != BJLRoomState_initialized && state != BJLRoomState_exited")

/** 进入教室 */
- (void)enter;

/** 进入教室成功/失败
 成功时所有初始化工作已经结束，vm 的状态、数据已经和服务端同步，并可调用 vm 方法
 */
- (BJLObservable)enterRoomSuccess;
- (BJLObservable)enterRoomFailureWithError:(BJLError *)error;

/** 断开、重连
 网络连接断开时回调，回调 callback 确认是否重连，YES 重连、NO 退出教室，也可延时或者手动调用 callback
 可通过 `reloadingVM` 监听重连的进度和结果
 默认（不设置此回调）在断开时自动重连、重连过程中遇到错误将 `异常退出`
 !!!: 断开重连过程中 vm 的状态、数据没有与服务端同步，调用其它 vm 方法时发起的网络请求会被丢弃、甚至产生不可预期的错误
 @param reloadingVM         重连 vm
 @param callback(reload)    调用 callback 是 reload 参数传 YES 重连，NO 将导致 `异常退出`
 */
- (void)setReloadingBlock:(void (^ _Nullable)(BJLLoadingVM *reloadingVM,
                                              void (^callback)(BOOL reload)))reloadingBlock;

/** 退出教室 */
- (void)exit;

/**
 退出教室 - 主动/异常
 主动退出 `error` 为 nil，否则为异常退出
 参考 `BJLErrorCode` */
- (BJLObservable)roomWillExitWithError:(nullable BJLError *)error;
- (BJLObservable)roomDidExitWithError:(nullable BJLError *)error;

#pragma mark metainfo

/** 教室信息
 BJLiveCore 内部【不】读取此处 `roomInfo` */
@property (nonatomic, readonly, copy, nullable) NSObject<BJLRoomInfo> *roomInfo;
/** 当前登录用户信息
 BJLiveCore 内部【不】读取此处 `loginUser`
 */
@property (nonatomic, readonly, copy, nullable) BJLUser *loginUser;
/** 当前登录用户是否是主讲人
 不支持 KVO */
@property (nonatomic, readonly) BOOL loginUserIsPresenter; // NON-KVO

/**
 功能设置
 BJLiveCore 内部【不】读取此处 featureConfig
 TODO: MingLQ - if nil
 */
@property (nonatomic, readonly, copy, nullable) BJLFeatureConfig *featureConfig;

#pragma mark view & view-model

/** vm、view 初始化状态，值为 YES 时 vm 可用
 在进教室 成功/失败 之前，vm、view 就已经可用，开始监听 vm 的属性、方法调用以及显示 view，但是之后可能进教室成功、也可能失败
 !!!: 但此时 `loadingVM` 以外的 vm 并没有与 server 建立连接，vm 的状态、数据没有与服务端同步，调用 vm 方法时发起的网络请求会被丢弃、甚至产生不可预期的错误，断开重连时类似
 KVO 此属性时 option 包含 initial(默认)，即使开始 KVO 时值已经是 YES 也会执行 KVO 回调，参考 NSObject+BJLObserving.h
 */
@property (nonatomic, readonly) BOOL vmsAvailable; // DEPRECATED_MSG_ATTRIBUTE("didLoginMasterServer, ???: state")

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
 参考 `BJLRecordingVM` 的 `recordingVideo`、`inputVideoAspectRatio` */
@property (nonatomic, readonly, nullable) UIView *recordingView;

/** 音视频 播放 - 他人 */
@property (nonatomic, readonly, nullable) BJLPlayingVM *playingVM;

/** 课件管理 */
@property (nonatomic, readonly, nullable) BJLSlideVM *slideVM;

/** 课件显示、控制 */
@property (nonatomic, readonly, nullable) BJLSlideshowVM *slideshowVM;
/**
 禁用 PPT 动画
 是否禁用 PPT 动画由两个参数控制，任意一个值为 YES 就禁止
 1、由服务端通过 `BJLFeatureConfig` 的 `disablePPTAnimation` 控制
 2、由上层设置这个 `disablePPTAnimation`
 */
@property (nonatomic) BOOL disablePPTAnimation;
/** 课件、画笔视图
 尺寸、位置随意设定 */
@property (nonatomic, readonly, nullable) UIViewController<BJLSlideshowUI> *slideshowViewController;

/** 云端录课 */
@property (nonatomic, readonly, nullable) BJLServerRecordingVM *serverRecordingVM;

/** 聊天/弹幕 */
@property (nonatomic, readonly, nullable) BJLChatVM *chatVM;

@end

NS_ASSUME_NONNULL_END
