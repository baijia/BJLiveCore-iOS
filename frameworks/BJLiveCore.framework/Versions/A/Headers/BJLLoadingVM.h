//
//  BJLLoadingVM.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-11-28.
//  Copyright © 2016 BaijiaYun. All rights reserved.
//

#import "BJLBaseVM.h"

NS_ASSUME_NONNULL_BEGIN

/** 加载步骤 */
typedef NS_OPTIONS(NSInteger, BJLLoadingStep) {
    /** 检查网络连接 */
    BJLLoadingStep_checkNetwork         = 1 << 0,
    /** 加载房间信息 */
    BJLLoadingStep_loadRoomInfo         = 1 << 1,
    /** 连接 MasterServer */
    BJLLoadingStep_connectMasterServer  = 1 << 2,
    /** 连接 RoomServer */
    BJLLoadingStep_connectRoomServer    = 1 << 3,
    /** 最后一步：连接 RoomServer */
    BJLLoadingStep_last                 = BJLLoadingStep_connectRoomServer,
    /** 所有步骤 */
    BJLLoadingStep_all                  = NSIntegerMax,
    /** 重连 */
    BJLLoadingStep_reconnect            = (BJLLoadingStep_all ^ (BJLLoadingStep_loadRoomInfo))
};

/**
 - stepOver: 单步完成，无错误
 - askForWWANNetwork: 蜂窝网络，无错误
 - errorOccurred: 发生错误，参考 BJLErrorCode
 */
typedef NS_ENUM(NSInteger, BJLLoadingSuspendReason) {
    /** 单步完成，无错误 */
    BJLLoadingSuspendReason_stepOver,
    /** 发生错误 */
    BJLLoadingSuspendReason_errorOccurred
};

/**
 加载任务回调，在 suspendBlock 中调用 callback(BOOL isContinue) 决定是否继续
 #param step        步骤
 #param reason      暂停原因
 #param error       具体错误
 #param callback(BOOL isContinue)   回调
 isContinue: reason 为 BJLLoadingSuspendReason_errorOccurred 时 isContinue 表示是否重试当前步骤，否则表示是否执行下一步骤
 suspendBlock 为 nil 时使用 isContinue = (reason != BJLLoadingSuspendReason_errorOccurred)
 */
typedef void (^BJLLoadingSuspendBlock)(
BJLLoadingStep step,
BJLLoadingSuspendReason reason,
BJLError * _Nullable error,
void (^continueCallback)(BOOL isContinue));

/** ### 进教室的加载状态 */
@interface BJLLoadingVM : BJLBaseVM

/**
 加载任务回调，在 suspendBlock 中调用 callback(BOOL isContinue) 决定是否继续
 #param step        步骤
 #param reason      暂停原因
 #param error       具体错误
 #param callback    callback(BOOL isContinue)回调
 isContinue: reason 为 `BJLLoadingSuspendReason_errorOccurred` 时 isContinue 表示是否重试当前步骤，否则表示是否执行下一步骤
 suspendBlock 为 nil 时使用 isContinue = (reason != BJLLoadingSuspendReason_errorOccurred)
 */
@property (nonatomic, copy, nullable) BJLLoadingSuspendBlock suspendBlock;

/** 加载进度
 #param progress 进度
 */
- (BJLObservable)loadingUpdateProgress:(CGFloat)progress; // progress: 0.0 ~ 1.0
/** 加载成功 */
- (BJLObservable)loadingSuccess;
/** 加载失败
 参考 `BJLErrorCode`
 #param error 错误信息
 */
// TODO: MingLQ - 错误，要明确步骤、原因，错误 key 支持国际化、定制化
- (BJLObservable)loadingFailureWithError:(nullable BJLError *)error;

@end

NS_ASSUME_NONNULL_END
