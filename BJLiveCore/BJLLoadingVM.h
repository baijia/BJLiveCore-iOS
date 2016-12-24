//
//  BJLLoadingVM.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-11-28.
//
//

#import "BJLBaseVM.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, BJLLoadingStep) {
    BJLLoadingStep_checkNetwork         = 1 << 0,
    BJLLoadingStep_loadRoomInfo         = 1 << 1,
    BJLLoadingStep_loadFeatureConfig    = 1 << 2,
    BJLLoadingStep_connectMasterServer  = 1 << 3,
    BJLLoadingStep_connectRoomServer    = 1 << 4,
    BJLLoadingStep_connectChatServer    = 1 << 5
};
typedef BJLLoadingStep BJLLoadingSteps;
static BJLLoadingSteps const BJLLoadingSteps_all = NSIntegerMax;

/**
 - stepOver: 单步完成，无错误 ignorable
 - askForWWANNetwork: 蜂窝网络，ignorable
 - errorOccurred: 发生错误，unignorable，参考 BJLErrorCode
 */
typedef NS_ENUM(NSInteger, BJLLoadingSuspendReason) {
    BJLLoadingSuspendReason_stepOver,
    BJLLoadingSuspendReason_askForWWANNetwork,
    BJLLoadingSuspendReason_errorOccurred
};

typedef void (^BJLLoadingSuspendCallback)(BOOL isContinue);
typedef void (^BJLLoadingSuspendBlock)(
BJLLoadingStep step,
BJLLoadingSuspendReason reason,
BJLError *error,
BOOL ignorable,
BJLLoadingSuspendCallback suspendCallback);

@interface BJLLoadingVM : BJLBaseVM

/**
 加载任务回调，在 suspendBlock 中调用 callback(BOOL isContinue) 决定是否继续
 @param reason      暂停原因
 @param error       具体错误
 @param ignorable   错误是否可以被忽略
 @param callback(BOOL isContinue)   回调，suspendBlock 为 nil 时使用 ignorable 当作 isContinue
    isContinue: ignorable 为 YES 时表示是否忽略该错误、执行下一步骤，否则表示是否重试当前步骤
 */
@property (nonatomic, nullable, copy) BJLLoadingSuspendBlock suspendBlock;

// TODO: MingLQ - 断开重连

/** 加载进度 */
- (BJLOEvent)loadingDidUpdateProgress:(CGFloat)progress; // progress: 0.0 ~ 1.0
/** 加载成功 */
- (BJLOEvent)loadingDidSuccess;
/** 加载失败 */
// TODO: MingLQ - 错误，要明确步骤、原因
- (BJLOEvent)loadingDidFailureWithError:(nullable BJLError *)error;

@end

NS_ASSUME_NONNULL_END
