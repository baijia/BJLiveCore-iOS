//
//  BJRoomViewController+users.m
//  BJLiveCore
//
//  Created by MingLQ on 2016-12-19.
//  Copyright © 2016 BaijiaYun. All rights reserved.
//

#import <BJLIveBase/BJLYYModel.h>

#import "BJRoomViewController+users.h"

@implementation BJRoomViewController (users)

- (void)makeUserEvents {
    @weakify(self);
    
    [self bjl_kvo:BJLMakeProperty(self.room.onlineUsersVM, onlineUsersTotalCount)
                       filter:^BOOL(NSNumber *old, NSNumber *now) {
                           // @strongify(self);
                           return old.integerValue != now.integerValue;
                       }
                     observer:^BOOL(id old, id now) {
                         @strongify(self);
                         [self.console printFormat:@"onlineUsers count: %@", now];
                         return YES;
                     }];
    
    [self bjl_kvo:BJLMakeProperty(self.room.onlineUsersVM, onlineTeacher)
                     observer:^BOOL(id old, BJLOnlineUser *now) {
                         @strongify(self);
                         [self.console printFormat:@"onlineUsers teacher: %@", now.name];
                         return YES;
                     }];
    
    [self bjl_kvo:BJLMakeProperty(self.room.onlineUsersVM, onlineUsers)
                     observer:^BOOL(id old, NSArray<BJLOnlineUser *> *now) {
                         @strongify(self);
                         NSMutableArray *userNames = [NSMutableArray new];
                         for (BJLOnlineUser *user in now) {
                             [userNames bjl_addObjectOrNil:user.name];
                         }
                         [self.console printFormat:@"onlineUsers all: %@",
                          [userNames componentsJoinedByString:@", "]];
                         return YES;
                     }];
    
    [self bjl_observe:BJLMakeMethod(self.room.onlineUsersVM, onlineUserDidEnter:)
             observer:^BOOL(BJLOnlineUser *user) {
                 @strongify(self);
                 [self.console printFormat:@"onlineUsers in: %@", user.name];
                 return YES;
             }];
    
    [self bjl_observe:BJLMakeMethod(self.room.onlineUsersVM, onlineUserDidExit:)
             observer:^BOOL(BJLOnlineUser *user) {
                 @strongify(self);
                 [self.console printFormat:@"onlineUsers out: %@", user.name];
                 return YES;
             }];
    
    [self bjl_observe:BJLMakeMethod(self.room.roomVM, didReceiveRollcallWithTimeout:)
             observer:^BOOL(NSTimeInterval timeout) {
                 @strongify(self);
                 
                 UIAlertController *actionSheet = [UIAlertController
                                                   alertControllerWithTitle:@"老师点名"
                                                   message:[NSString stringWithFormat:@"请在 %td 秒内答到", (NSInteger)timeout]
                                                   preferredStyle:UIAlertControllerStyleAlert];
                 
                 [actionSheet addAction:[UIAlertAction
                                         actionWithTitle:@"答到"
                                         style:UIAlertActionStyleDefault
                                         handler:^(UIAlertAction * _Nonnull action) {
                                             BJLError *error = [self.room.roomVM answerToRollcall];
                                             if (error) {
                                                 [self.console printFormat:@"答到失败: %@", [error localizedFailureReason]];
                                             }
                                         }]];
                 
                 [actionSheet addAction:[UIAlertAction
                                         actionWithTitle:@"无视"
                                         style:UIAlertActionStyleCancel
                                         handler:nil]];
                 
                 [self presentViewController:actionSheet
                                    animated:YES
                                  completion:nil];
                 
                 return YES;
             }];
    
    [self bjl_observe:BJLMakeMethod(self.room.roomVM, didReceiveSurveyHistory:rightCount:wrongCount:)
             observer:^BOOL(NSArray<BJLSurvey *> *surveyHistory, NSInteger rightCount, NSInteger wrongCount) {
                 @strongify(self);
                 [self.console printFormat:@"收到历史测验: %@ - 正确 %td, 错误 %td",
                  [surveyHistory bjlyy_modelToJSONObject], rightCount, wrongCount];
                 return YES;
             }];
    
    [self bjl_observe:BJLMakeMethod(self.room.roomVM, didReceiveSurvey:)
             observer:^BOOL(BJLSurvey *survey) {
                 @strongify(self);
                 UIAlertController *alert = [UIAlertController
                                             alertControllerWithTitle:[NSString stringWithFormat:@"测验-%td", survey.order]
                                             message:survey.question
                                             preferredStyle:UIAlertControllerStyleAlert];
                 __block BOOL hasAnswer = NO;
                 for (BJLSurveyOption *option in survey.options) {
                     [alert addAction:[UIAlertAction
                                       actionWithTitle:[NSString stringWithFormat:@"%@. %@", option.key, option.value]
                                       style:UIAlertActionStyleDefault
                                       handler:^(UIAlertAction * _Nonnull action) {
                                           BJLSurveyResult result = (hasAnswer
                                                                     ? (option.isAnswer ? BJLSurveyResultRight : BJLSurveyResultWrong)
                                                                     : BJLSurveyResultNA);
                                           [self.room.roomVM sendSurveyAnswers:@[option.key ?: @""]
                                                                        result:result
                                                                         order:survey.order];
                                       }]];
                     hasAnswer = hasAnswer || option.isAnswer;
                 }
                 if (!survey.options.count) {
                     [alert addAction:[UIAlertAction
                                       actionWithTitle:@"r u kidding me"
                                       style:UIAlertActionStyleCancel
                                       handler:nil]];
                 }
                 
                 [self presentViewController:alert
                                    animated:YES
                                  completion:nil];
                 
                 return YES;
             }];
    
    [self bjl_observe:BJLMakeMethod(self.room.roomVM, didReceiveSurveyResults:order:)
             observer:^BOOL(NSDictionary<NSString *, NSNumber *> *results, NSInteger order) {
                 @strongify(self);
                 [self.console printFormat:@"收到测验结果: %td - %@",
                  order, [results bjlyy_modelToJSONObject]];
                 return YES;
             }];
    
    [self.room.roomVM loadSurveyHistory];
    
    [self bjl_observe:BJLMakeMethod(self.room.roomVM, didReceiveCustomizedSignal:value:isCache:)
             observer:(BJLMethodObserver)^BOOL(NSString *key, id value, BOOL isCache) {
                 @strongify(self);
                 [self.console printFormat:@"客户定制信令 %@: %@ - %@", isCache ? @"cached" : @"received", key, value];
                 return YES;
             }];
    
    [self bjl_kvo:BJLMakeProperty(self.room.roomVM, rollcallTimeRemaining)
           filter:^BOOL(NSNumber * _Nullable old, NSNumber * _Nullable now) {
               // @strongify(self);
               return now.doubleValue != old.doubleValue;
           }
         observer:^BOOL(NSNumber * _Nullable old, NSNumber * _Nullable now) {
             @strongify(self);
             [self.console printFormat:@"答到倒计时: %f", now.doubleValue];
             return YES;
         }];
}

@end
