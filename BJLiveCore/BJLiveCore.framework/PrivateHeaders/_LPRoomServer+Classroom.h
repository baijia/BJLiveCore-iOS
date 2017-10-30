//
//  _LPRoomServer+Classroom.h
//  BJLiveCore
//
//  Created by 杨磊 on 16/3/30.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "_LPRoomServer.h"
#import "_LPResClassNotice.h"
#import "_LPReqRollcall.h"
#import "_LPSurveyRes.h"
#import "_LPResClassStart.h"
#import "_LPResClassEnd.h"
#import "_LPResForbidUser.h"
#import "_LPResForbidUserState.h"

/**
 *  教室相关信令服务
 */
@interface _LPRoomServer (Classroom)

/**
 *  上课
 */
- (void)requestClassStart;
/**
 *  _LPResClassStart
 */
- (RACSignal *)signalOfClassStart;

/**
 *  下课
 */
- (void)requestClassEnd;
/**
 *  _LPResClassEnd
 */
- (RACSignal *)signalOfClassEnd;

/**
 *  修改公告栏
 */
- (void)requestClassNoticeChange:(NSString *)content link:(NSString *)link;
/**
 *  _LPResClassNotice
 */
- (RACSignal *)signalOfClassNoticeChanged;

/**
 *  请求公告
 */
- (void)requestNotice;

/**
 *  _LPResClassNotice
 */
- (RACSignal *)signalOfClassNoticeResponse;

- (void)requestRollcallWithTimeout:(NSTimeInterval)timeout;

#pragma mark -

/**
 *  收到点名
 *  _LPReqRollcall
 */
- (RACSignal *)signalOfRollcall;

/**
 *  答到
 */
- (void)requestAnswerToRollcall;

#pragma mark -

/** 请求历史题目 */
- (void)loadSurveyHistoryWithUserNumber:(NSString *)userNumber;
/**
 *  收到历史题目以及当前用户的答题情况
 *  _LPSurveyRes
 */
- (RACSignal *)signalOfSurveyHistory;

/**
 *  老师: 发送题目
 */
- (void)sendSurvey:(BJLSurvey *)survey;

/**
 *  学生: 收到新题目
 *  _LPSurveyReceive
 */
- (RACSignal *)signalOfReceiveSurvey;
/**
 学生: 答题
 */
- (void)sendSurveyAnswerAnswers:(NSArray<NSString *> *)answers
                         result:(NSInteger)result
                          order:(NSInteger)order
                     userNumber:(NSString *)userNumber
                       userName:(NSString *)userName;

/**
 *  收到答题统计
 *  _LPSurveyResult
 */
- (RACSignal *)signalOfReceiveSurveyResults;

/**
 *  老师&管理员: 收到答题用户统计
 *  _LPSurveyUserResult
 */
- (RACSignal *)signalOfReceiveSurveyUserResults;

#pragma mark -

/** 禁言单个用户 */
- (void)requestForbidUser:(_LPUser *)user
                 duration:(NSTimeInterval)duration
                     from:(_LPUser *)user;

/** 单个用户被禁言 */
// _LPResForbidUser
- (RACSignal *)signalOfForbidUser;

/** 获取用户禁言状态 */
- (void)requestForbidUserStateWithUserNumber:(NSString *)userNumber;

/** 返回用户禁言状态 */
// _LPResForbidUserState
- (RACSignal *)signalOfForbidUserState;

@end
