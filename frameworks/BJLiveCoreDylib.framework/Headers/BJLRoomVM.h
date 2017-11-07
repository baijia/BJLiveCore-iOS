//
//  BJLRoomVM.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-12-05.
//  Copyright © 2016 BaijiaYun. All rights reserved.
//

#import "BJLBaseVM.h"

#import "BJLRoomInfo.h"
#import "BJLUser.h"
#import "BJLNotice.h"
#import "BJLSurvey.h"

NS_ASSUME_NONNULL_BEGIN

/** ### 教室信息、状态，用户信息，公告等 */
@interface BJLRoomVM : BJLBaseVM

/** 进入教室时间 */
@property (nonatomic, readonly) NSTimeInterval enteringTimeInterval; // seconds since 1970

#pragma mark - 上课状态

/** 上课状态 */
@property (nonatomic, readonly) BOOL liveStarted;

/** 老师: 设置上课状态
 #discussion 设置成功后修改 `liveStarted`
 #param liveStarted YES：上课，NO：下课
 #return BJLError：
 BJLErrorCode_invalidUserRole   错误权限，要求老师权限
 */
- (nullable BJLError *)sendLiveStarted:(BOOL)liveStarted;

#pragma mark - 公告

/** 教室公告 */
@property (nonatomic, readonly, copy, nullable) BJLNotice *notice;

/** 获取教室公告
 #discussion 连接教室后、掉线重新连接后自动调用加载
 #discussion 获取成功后修改 `notice`
 */
- (void)loadNotice;
/** 老师: 设置教室公告
 #discussion 最多 BJLTextMaxLength_notice 个字符
 #discussion `noticeText` = `noticeText.length` ? `noticeText` : `linkURL.absoluteString`
 #discussion 设置成功后修改 `notice`
 #param noticeText 公告文字内容
 #param linkURL 公告跳转链接
 #return BJLError：
 BJLErrorCode_invalidArguments  错误参数，如字数超过 `BJLTextMaxLength_notice`；
 BJLErrorCode_invalidUserRole   错误权限，要求老师或助教权限。
 */
- (nullable BJLError *)sendNoticeWithText:(nullable NSString *)noticeText linkURL:(nullable NSURL *)linkURL;

#pragma mark - 点名

/** 点名倒计时
 #discussion 每秒更新
 */
@property (nonatomic, readonly) NSTimeInterval rollcallTimeRemaining;

/** 学生: 收到点名
 #discussion 学生需要在规定时间内 `timeout` 答到 - 调用 `answerToRollcall`
 #discussion 参考 `rollcallTimeRemaining`
 #param timeout 超时时间
 */
- (BJLObservable)didReceiveRollcallWithTimeout:(NSTimeInterval)timeout;

/** 学生: 收到点名取消
 #discussion 可能是老师取消、或者倒计时结束
 #discussion 参考 `rollcallTimeRemaining`
 */
- (BJLObservable)rollcallDidFinish;

/** 学生: 答到
 #return BJLError：
 BJLErrorCode_invalidCalling    错误调用，如老师没有点名或者点名已过期；
 BJLErrorCode_invalidUserRole   错误权限，要求学生权限。
 */
- (nullable BJLError *)answerToRollcall;

#pragma mark - 测验

/** 请求历史题目 */
- (void)loadSurveyHistory;

/** 收到历史题目以及当前用户的答题情况
 #param surveyHistory 历史题目
 #param rightCount 回答正确个数
 #param wrongCount 回答错误个数
 */
- (BJLObservable)didReceiveSurveyHistory:(NSArray<BJLSurvey *> *)surveyHistory
                              rightCount:(NSInteger)rightCount
                              wrongCount:(NSInteger)wrongCount;

/** 老师: 发送题目 - 暂未实现
 #return BJLError：
 BJLErrorCode_invalidArguments  错误参数；
 BJLErrorCode_invalidUserRole   错误权限，要求老师或助教权限。
 - (nullable BJLError *)sendSurvey:(BJLSurvey *)survey; */

/** 学生: 收到新题目
 #param survey 题目
 */
- (BJLObservable)didReceiveSurvey:(BJLSurvey *)survey;

/**
 学生: 答题
 #param answers `BJLSurveyOption` 的 `key`
 #param result   与每个 `BJLSurveyOption` 的 `isAnswer` 比对得出，如果一个题目下所有 `BJLSurveyOption` 的 `isAnswer` 都是 NO 表示此题目没有标准答案
 #param order   `BJLSurvey` 的 `order`
 #return BJLError：
 BJLErrorCode_invalidArguments  错误参数；
 BJLErrorCode_invalidUserRole   错误权限，要求老师或助教权限。
 */
- (nullable BJLError *)sendSurveyAnswers:(NSArray<NSString *> *)answers
                                  result:(BJLSurveyResult)result
                                   order:(NSInteger)order;

/** 收到答题统计
 #param results `NSDictionary` 的 key-value 分别是 `BJLSurveyOption` 的 `key` 和选择该选项的人数
 #param order   `BJLSurvey` 的 `order`
 */
- (BJLObservable)didReceiveSurveyResults:(NSDictionary<NSString *, NSNumber *> *)results
                                   order:(NSInteger)order;

/** 老师: 收到答题用户统计 - 暂未实现
 #param results `NSDictionary` 的 key-value 分别是 `BJLSurveyOption` 的 `key` 和选择该选项的名单
 #param order   `BJLSurvey` 的 `order`
- (BJLObservable)didReceiveSurveyUserResults:(NSDictionary<NSString *, NSArray<NSString *> *> *)results
                                       order:(NSInteger)order; */

#pragma mark - 测验 V2

/**
 #return BJLError:
 BJLErrorCode_invalidCalling    错误调用
 */
- (nullable BJLError *)sendQuizMessage:(NSDictionary<NSString *, id> *)message;
- (BJLObservable)didReceiveQuizMessage:(NSDictionary<NSString *, id> *)message;
- (NSURLRequest *)quizRequestWithID:(NSString *)quizID error:(NSError *__autoreleasing *)error;

#pragma mark - 定制信令

/**
 收到定制信令
 #discussion 定制信令与 SDK 功能无关
 #param key     信令类型
 #param value   信令内容，类型可能是字符串或者字典等 JSON 数据类型
 #param isCache 是否为缓存
 */
- (BJLObservable)didReceiveCustomizedSignal:(NSString *)key value:(nullable id)value isCache:(BOOL)isCache;

@end

NS_ASSUME_NONNULL_END
