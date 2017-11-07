//
//  BJLGiftVM.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-12-06.
//  Copyright © 2016 BaijiaYun. All rights reserved.
//

#import "BJLBaseVM.h"

#import "BJLGift.h"

NS_ASSUME_NONNULL_BEGIN

/** ### 打赏 */
@interface BJLGiftVM : BJLBaseVM

/** 所有打赏记录
 #discussion 参考 `loadReceivedGifts`
 */
@property (nonatomic, readonly, copy, nullable) NSArray<NSObject<BJLReceivedGift> *> *receivedGifts;

/** `receivedGifts` 被覆盖更新
 #discussion 覆盖更新才调用，增量更新不调用
 #discussion 首次连接 server 或断开重连会导致覆盖更新
 #param receivedGifts 打赏记录
 */
- (BJLObservable)receivedGiftsDidOverwrite:(nullable NSArray<NSObject<BJLReceivedGift> *> *)receivedGifts;

/** 加载所有打赏记录
 #discussion 连接教室后、掉线重新连接后自动调用加载
 #discussion 加载成功后更新 `receivedGifts`、调用 `receivedMessagesDidOverwrite:`
 */
- (void)loadReceivedGifts;

/**
 打赏
 #discussion 成功后会收到打赏通知，只支持学生给老师打赏
 #param teacher 打赏对象，老师在教室内时使用老师信息、否则使用传入的 `teacher`
 #param gift    礼物
 #return BJLError：
 BJLErrorCode_invalidArguments  错误参数；
 BJLErrorCode_invalidCalling    错误调用，如老师和助教调用此方法、老师不在教室、打赏对象不是老师等；
 BJLErrorCode_invalidUserRole   错误权限，要求学生权限。
 */
- (nullable BJLError *)sendGift:(BJLGift *)gift toTeacher:(BJLUser *)teacher;

/** 收到打赏通知
 #discussion 同时更新 `receivedGifts`
 #param receivedGift 打赏内容
 */
- (BJLObservable)didReceiveGift:(NSObject<BJLReceivedGift> *)receivedGift;

@end

NS_ASSUME_NONNULL_END
