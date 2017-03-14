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

@property (nonatomic, readonly, nullable, copy) NSObject<BJLRoomInfo> *roomInfo DEPRECATED_MSG_ATTRIBUTE("use `BJLRoom.roomInfo` instead");
@property (nonatomic, readonly, nullable, copy) NSObject<BJLUser> *loginUser DEPRECATED_MSG_ATTRIBUTE("use `BJLRoom.loginUser` instead");

/** 进入教室时间 */
@property (nonatomic, readonly) NSTimeInterval enteringTimeInterval; // seconds since 1970

/** 教室发言类型
 自由模式/举手模式 */
@property (nonatomic, readonly) BJLSpeakType speakType;

#pragma mark - 上课状态

/** 上课状态 */
@property (nonatomic, readonly) BOOL liveStarted;

/** 老师: 设置上课状态
 设置成功后修改 `liveStarted` */
- (nullable BJLError *)sendLiveStarted:(BOOL)liveStarted;

#pragma mark - 公告

/** 教室公告 */
@property (nonatomic, readonly, nullable, copy) BJLNotice *notice;
@property (nonatomic, readonly, nullable, copy) NSString *noticeText DEPRECATED_MSG_ATTRIBUTE("use `notice` instead");

/** 获取教室公告
 连接教室后、掉线重新连接后自动调用加载
 获取成功后修改 `notice` */
- (void)loadNotice;
- (void)loadNoticeText DEPRECATED_MSG_ATTRIBUTE("use `loadNotice` instead");
/** 老师: 设置教室公告
 最多 BJLTextMaxLength_notice 个字符
 `noticeText` = `noticeText.length` ? `noticeText` : `linkURL.absoluteString`
 设置成功后修改 `notice` */
- (nullable BJLError *)sendNoticeWithText:(nullable NSString *)noticeText linkURL:(nullable NSURL *)linkURL;
- (nullable BJLError *)sendNoticeText:(nullable NSString *)noticeText DEPRECATED_MSG_ATTRIBUTE("use `sendNoticeWithText:linkURL:` instead");

#pragma mark - 点名

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

#pragma mark - 测验

/** 请求历史题目 */
- (void)loadSurveyHistory;

/** 收到历史题目以及当前用户的答题情况
 */
- (BJLObservable)didReceiveSurveyHistory:(NSArray<BJLSurvey *> *)surveyHistory
                              rightCount:(NSInteger)rightCount
                              wrongCount:(NSInteger)wrongCount;

/** 老师: 发送题目 - 暂未实现
- (nullable BJLError *)sendSurvey:(BJLSurvey *)survey; */

/** 学生: 收到新题目 */
- (BJLObservable)didReceiveSurvey:(BJLSurvey *)survey;

/**
 学生: 答题
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

/** 老师: 收到答题用户统计 - 暂未实现
 @param results `NSDictionary` 的 key-value 分别是 `BJLSurveyOption` 的 `key` 和选择该选项的名单
 @param order   `BJLSurvey` 的 `order`
- (BJLObservable)didReceiveSurveyUserResults:(NSDictionary<NSString *, NSArray<NSString *> *> *)results
                                       order:(NSInteger)order; */

#pragma mark - 定制信令

/**
 收到定制信令
 定制信令与 SDK 功能无关
 @param key     信令类型
 @param value   信令内容，类型可能是字符串或者字典等 JSON 数据类型
 */
- (BJLObservable)didReceiveCustomizedSignal:(NSString *)key value:(nullable id)value;

@end

NS_ASSUME_NONNULL_END
