//
//  BJLRoomVM.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-12-05.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "BJLBaseVM.h"

#import "BJLRoomInfo.h"
#import "BJLUser.h"

NS_ASSUME_NONNULL_BEGIN

@interface BJLRoomVM : BJLBaseVM

@property (nonatomic, readonly, nullable, copy) NSObject<BJLRoomInfo> *roomInfo DEPRECATED_MSG_ATTRIBUTE("use `BJLRoom.roomInfo` instead");
@property (nonatomic, readonly, nullable, copy) NSObject<BJLUser> *loginUser DEPRECATED_MSG_ATTRIBUTE("use `BJLRoom.loginUser` instead");

/** 进入教室时间 */
@property (nonatomic, readonly) NSTimeInterval enteringTimeInterval; // seconds since 1970

/** 教室发言类型
 自由模式/举手模式 */
@property (nonatomic, readonly) BJLSpeakType speakType;

#pragma mark -

/** 上课状态 */
@property (nonatomic, readonly) BOOL liveStarted;

/** 老师: 设置上课状态
 设置成功后修改 `liveStarted` */
- (nullable BJLError *)sendLiveStarted:(BOOL)liveStarted;

#pragma mark -

/** 教室公告 */
@property (nonatomic, readonly, nullable, copy) NSString *noticeText;

/** 获取教室公告
 获取成功后修改 `noticeText` */
- (void)loadNoticeText;
/** 老师: 设置教室公告
 设置成功后修改 `noticeText` */
- (nullable BJLError *)sendNoticeText:(NSString *)noticeText;

#pragma mark -

/** 点名倒计时
 每秒更新 */
@property (nonatomic, readonly) NSTimeInterval rollcallTimeRemaining;

/** 学生: 收到点名
 学生需要在规定时间内 `timeout` 答到 - 调用 `answerToRollcall`
 参考 `rollcallTimeRemaining`
 */
- (BJLObservable)didReceiveRollcallWithTimeout:(NSTimeInterval)timeout;

/** 学生: 收到点名取消
 可能是老师取消、或者倒计时结束，参考 `rollcallTimeRemaining` */
- (BJLObservable)rollcallDidCancel;

/** 学生: 答到 */
- (nullable BJLError *)answerToRollcall;

#pragma mark -

/**
 收到定制信令
 定制信令与 SDK 功能无关
 @param key     信令类型
 @param value   信令内容，类型可能是字符串或者字典等 JSON 数据类型
 */
- (BJLObservable)didReceiveCustomizedSignal:(NSString *)key value:(nullable id)value;

@end

NS_ASSUME_NONNULL_END
