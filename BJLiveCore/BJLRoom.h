//
//  BJLRoom.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-11-15.
//
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "BJLBlockHelper.h"

#import "BJLConstants.h"
#import "BJLFeatureConfig.h"

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

#import "BJLChatVM.h"

#import "BJLHelpVM.h"
#import "BJLServerRecordingVM.h"
#import "BJLGiftVM.h"
// 评价 VM
// 公告 VM

/** UI */

#import "BJLSlideshowUI.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, BJLRoomExitReason) {
    BJLRoomExitReason_enterFailure,
    BJLRoomExitReason_anotherRoomEntered,
    BJLRoomExitReason_loginConflict
};

/**
 教室
 可同时存在多个实例，但最多只有一个教室处于进入状态，后执行 enter 的教室会把之前的教室踢掉
 */
@interface BJLRoom : NSObject

#pragma mark lifecycle

/**
 通过 ID 创建教室
 @param roomID          教室 ID
 @param user            用户
 @param apiSign         API sign
 @param deployType      部署环境，仅 Debug 模式下有效
 @param featureConfig   TODO: 功能配置，参考 BJLRoomVM.featureConfig
 @return                教室
 */
+ (__kindof instancetype)roomWithID:(NSString *)roomID
                            apiSign:(NSString *)apiSign
                               user:(BJLUser *)user
                         deployType:(BJLDeployType)deployType
                      featureConfig:(nullable BJLFeatureConfig *)featureConfig;

/**
 通过参加码创建教室
 @param roomSecret      教室参加码，目前只支持老师、学生角色
 @param userName        用户名
 @param userAvatar      用户头像 URL
 @param deployType      部署环境，仅 Debug 模式下有效
 @param featureConfig   TODO: 功能配置，参考 BJLRoomVM.featureConfig
 @return                教室
 */
+ (__kindof instancetype)roomWithSecret:(NSString *)roomSecret
                               userName:(NSString *)userName
                             userAvatar:(nullable NSString *)userAvatar
                             deployType:(BJLDeployType)deployType
                          featureConfig:(nullable BJLFeatureConfig *)featureConfig;

/** 进入教室 */
- (void)enter;

/** 退出教室 */
- (void)exit;

/** 成功进入教室 */
- (BJLOEvent)roomDidEnter;
/**
 退出教室事件，参考 BJLErrorDomain
 */
- (BJLOEvent)roomWillExitWithError:(BJLError *)error;
- (BJLOEvent)roomDidExitWithError:(BJLError *)error;

#pragma mark view-model

/**
 nullable：
    所有 VM 属性都可为空
    - loadingVM 在 loading 时非空，成功/失败后为空；
    - 其它 VM 在 loading 前为空，在 loading 过程中初始化，退出教室后为空（loading 失败自动退出）；
    - 当前端/后端配置关闭某功能、对应 VM 可能为空，参考 BJLRoomVM.featureConfig；
 KVO：
    所有 VM 支持 KVO，在检测到 VM 变为非 nil 时、或者 `roomDidEnter` 之后才能有效添加 observer；
    所有 VM 的所有属性支持 KVO，除非额外注释说明；
 block:
    这里需要较多的使用 block 进行 KVO、事件监听，RAC 是一个很好的选择，但为了避免依赖过多的开源库而被放弃；
    RAC 最多需要同时引入 ReactiveCocoa、ReactiveObjCBridge、ReactiveSwift 和 ReactiveObjC；
    使用 block 进行 KVO - NSObject+BJLBlockKVO.h；
    使用 block 进行事件监听 - NSObject+BJLBlockNTO.h；
    tuple pack&unpack - NSObject+BJL_M9Dev.h；
    参考 BJLiveUI；
 */

/**** 核心功能 ****/

/** 进教室的 loading 状态 */
@property (nonatomic, readonly, nullable) BJLLoadingVM *loadingVM;

/** 功能设置，教室信息、状态，用户信息，公告等 */
@property (nonatomic, readonly, nullable) BJLRoomVM *roomVM;

/** 在线用户 */
@property (nonatomic, readonly, nullable) BJLOnlineUsersVM *onlineUsersVM;

/** 发言申请/处理 */
@property (nonatomic, readonly, nullable) BJLSpeakingRequestVM *speakingRequestVM;

/** 音视频 设置 */
@property (nonatomic, readonly, nullable) BJLMediaVM *mediaVM;

/** 音视频 采集 - 个人 */
@property (nonatomic, readonly, nullable) BJLRecordingVM *recordingVM;
@property (nonatomic, readonly, nullable) UIView *recordingView;

/** 音视频 播放 - 他人 */
@property (nonatomic, readonly, nullable) BJLPlayingVM *playingVM;
@property (nonatomic, readonly, nullable) UIView *playingView;

/** 课件管理 */
@property (nonatomic, readonly, nullable) BJLSlideVM *slideVM;

/** 课件显示 */
// @property (nonatomic, readonly, nullable) BJLSlideshowVM *slideshowVM;
@property (nonatomic, readonly, nullable) UIViewController<BJLSlideshowUI> *slideshowViewController;

/** 聊天/弹幕 */
@property (nonatomic, readonly, nullable) BJLChatVM *chatVM;

/**** 辅助功能 ****/

/** 电话求助 */
@property (nonatomic, readonly, nullable) BJLHelpVM *helpVM;

/** 云端录制 */
@property (nonatomic, readonly, nullable) BJLServerRecordingVM *serverRecordingVM;

/** 打赏 */
@property (nonatomic, readonly, nullable) BJLGiftVM *giftVM;

#pragma mark properties

@property (nonatomic, readonly, nullable) BJLFeatureConfig *featureConfig;
@property (nonatomic, readonly) BJLDeployType deployType;

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
