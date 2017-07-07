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
#import "BJLNotice.h"
#import "BJLSurvey.h"

NS_ASSUME_NONNULL_BEGIN

@interface BJLRoomVM : BJLBaseVM

@property (nonatomic, readonly, copy, nullable) NSObject<BJLRoomInfo> *roomInfo DEPRECATED_MSG_ATTRIBUTE("use `BJLRoom.roomInfo` instead");
@property (nonatomic, readonly, copy, nullable) BJLUser *loginUser DEPRECATED_MSG_ATTRIBUTE("use `BJLRoom.loginUser` instead");

/** 进入房间时间 */
@property (nonatomic, readonly) NSTimeInterval enteringTimeInterval; // seconds since 1970

#pragma mark - 直播开始状态

/** 直播开始状态 */
@property (nonatomic, readonly) BOOL liveStarted;

/** 主讲: 设置直播状态
 设置成功后修改 `liveStarted` */
- (nullable BJLError *)sendLiveStarted:(BOOL)liveStarted;

#pragma mark - 公告

/** 房间公告 */
@property (nonatomic, readonly, copy, nullable) BJLNotice *notice;
@property (nonatomic, readonly, copy, nullable) NSString *noticeText DEPRECATED_MSG_ATTRIBUTE("use `notice` instead");

/** 获取房间公告
 连接房间后、掉线重新连接后自动调用加载
 获取成功后修改 `notice` */
- (void)loadNotice;
- (void)loadNoticeText DEPRECATED_MSG_ATTRIBUTE("use `loadNotice` instead");
/** 主讲: 设置房间公告
 最多 BJLTextMaxLength_notice 个字符
 `noticeText` = `noticeText.length` ? `noticeText` : `linkURL.absoluteString`
 设置成功后修改 `notice` */
- (nullable BJLError *)sendNoticeWithText:(nullable NSString *)noticeText linkURL:(nullable NSURL *)linkURL;
- (nullable BJLError *)sendNoticeText:(nullable NSString *)noticeText DEPRECATED_MSG_ATTRIBUTE("use `sendNoticeWithText:linkURL:` instead");

#pragma mark - 点名

/** 点名倒计时
 每秒更新 */
@property (nonatomic, readonly) NSTimeInterval rollcallTimeRemaining;

/** 观众: 收到点名
 观众需要在规定时间内 `timeout` 答到 - 调用 `answerToRollcall`
 参考 `rollcallTimeRemaining`
 */
- (BJLObservable)didReceiveRollcallWithTimeout:(NSTimeInterval)timeout;

/** 观众: 收到点名取消
 可能是主讲取消、或者倒计时结束
 参考 `rollcallTimeRemaining` */
- (BJLObservable)rollcallDidFinish;
- (BJLObservable)rollcallDidCancel DEPRECATED_MSG_ATTRIBUTE("use `rollcallDidFinish` instead");

/** 观众: 答到 */
- (nullable BJLError *)answerToRollcall;

#pragma mark - 问卷

/** 请求历史题目 */
- (void)loadSurveyHistory;

/** 收到历史题目以及当前用户的答题情况
 */
- (BJLObservable)didReceiveSurveyHistory:(NSArray<BJLSurvey *> *)surveyHistory
                              rightCount:(NSInteger)rightCount
                              wrongCount:(NSInteger)wrongCount;

/** 主讲: 发送题目 - 暂未实现
- (nullable BJLError *)sendSurvey:(BJLSurvey *)survey; */

/** 观众: 收到新题目 */
- (BJLObservable)didReceiveSurvey:(BJLSurvey *)survey;

/**
 观众: 答题
 @param answers `BJLSurveyOption` 的 `key`
 @param result   与每个 `BJLSurveyOption` 的 `isAnswer` 比对得出，如果一个题目下所有 `BJLSurveyOption` 的 `isAnswer` 都是 NO 表示此题目没有标准答案
 @param order   `BJLSurvey` 的 `order`
 */
- (nullable BJLError *)sendSurveyAnswers:(NSArray<NSString *> *)answers
                                  result:(BJLSurveyResult)result
                                   order:(NSInteger)order;

/** 收到答题统计
 @param results `NSDictionary` 的 key-value 分别是 `BJLSurveyOption` 的 `key` 和选择该选项的人数
 @param order   `BJLSurvey` 的 `order`
 */
- (BJLObservable)didReceiveSurveyResults:(NSDictionary<NSString *, NSNumber *> *)results
                                   order:(NSInteger)order;

/** 主讲: 收到答题用户统计 - 暂未实现
 @param results `NSDictionary` 的 key-value 分别是 `BJLSurveyOption` 的 `key` 和选择该选项的名单
 @param order   `BJLSurvey` 的 `order`
- (BJLObservable)didReceiveSurveyUserResults:(NSDictionary<NSString *, NSArray<NSString *> *> *)results
                                       order:(NSInteger)order; */

#pragma mark - 问卷 V2

- (nullable BJLError *)sendQuizMessage:(NSDictionary<NSString *, id> *)message;
- (BJLObservable)didReceiveQuizMessage:(NSDictionary<NSString *, id> *)message;
- (NSURLRequest *)quizRequestWithID:(NSString *)quizID error:(NSError *__autoreleasing *)error;

#pragma mark - 定制信令

/**
 收到定制信令
 定制信令与 SDK 功能无关
 @param key     信令类型
 @param value   信令内容，类型可能是字符串或者字典等 JSON 数据类型
 */
- (BJLObservable)didReceiveCustomizedSignal:(NSString *)key value:(nullable id)value isCache:(BOOL)isCache;
- (BJLObservable)didReceiveCustomizedSignal:(NSString *)key value:(nullable id)value DEPRECATED_MSG_ATTRIBUTE("use `didReceiveCustomizedSignal:value:isCache:` instead");

@end

NS_ASSUME_NONNULL_END
