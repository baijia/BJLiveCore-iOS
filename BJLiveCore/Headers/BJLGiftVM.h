//
//  BJLGiftVM.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-12-06.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "BJLBaseVM.h"

#import "BJLGift.h"

NS_ASSUME_NONNULL_BEGIN

@interface BJLGiftVM : BJLBaseVM

/** 所有打赏记录
 参考 `- loadReceivedGifts` */
@property (nonatomic, readonly, nullable, copy) NSArray<NSObject<BJLReceivedGift> *> *receivedGifts;

/** 加载所有打赏记录
 连接教室后、掉线重新连接后自动调用加载
 加载成功后更新 `receivedGifts` */
- (void)loadReceivedGifts;

/**
 打赏
 成功后会收到打赏通知，只支持学生给老师打赏
 @param teacher 打赏对象，老师在教室内时使用老师信息、否则使用传入的 `teacher`
 @param gift    礼物
 */
- (nullable BJLError *)sendGift:(BJLGift *)gift toTeacher:(NSObject<BJLUser> *)teacher;

/** 收到打赏通知
 同时更新 `receivedGifts` */
- (BJLObservable)didReceiveGift:(NSObject<BJLReceivedGift> *)receivedGift;

@end

NS_ASSUME_NONNULL_END
