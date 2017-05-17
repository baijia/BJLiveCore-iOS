//
//  BJRoomViewController+users.m
//  BJLiveCore
//
//  Created by MingLQ on 2016-12-19.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "BJRoomViewController+users.h"

@implementation BJRoomViewController (users)

- (void)makeUserEvents {
    weakdef(self);
    
    [self bjl_kvo:BJLMakeProperty(self.room.onlineUsersVM, onlineUsersTotalCount)
                       filter:^BOOL(NSNumber *old, NSNumber *now) {
                           // strongdef(self);
                           return old.integerValue != now.integerValue;
                       }
                     observer:^BOOL(id old, id now) {
                         strongdef(self);
                         [self.console printFormat:@"onlineUsers count: %@", now];
                         return YES;
                     }];
    
    [self bjl_kvo:BJLMakeProperty(self.room.onlineUsersVM, onlineTeacher)
                     observer:^BOOL(id old, BJLOnlineUser *now) {
                         strongdef(self);
                         [self.console printFormat:@"onlineUsers teacher: %@", now.name];
                         return YES;
                     }];
    
    [self bjl_kvo:BJLMakeProperty(self.room.onlineUsersVM, onlineUsers)
                     observer:^BOOL(id old, NSArray<BJLOnlineUser *> *now) {
                         strongdef(self);
                         NSMutableArray *userNames = [NSMutableArray new];
                         for (BJLOnlineUser *user in now) {
                             [userNames addObjectOrNil:user.name];
                         }
                         [self.console printFormat:@"onlineUsers all: %@",
                          [userNames componentsJoinedByString:@", "]];
                         return YES;
                     }];
    
    [self bjl_observe:BJLMakeMethod(self.room.onlineUsersVM, onlineUserDidEnter:)
             observer:^BOOL(BJLOnlineUser *user) {
                 strongdef(self);
                 [self.console printFormat:@"onlineUsers in: %@", user.name];
                 return YES;
             }];
    
    [self bjl_observe:BJLMakeMethod(self.room.onlineUsersVM, onlineUserDidExit:)
             observer:^BOOL(BJLOnlineUser *user) {
                 strongdef(self);
                 [self.console printFormat:@"onlineUsers out: %@", user.name];
                 return YES;
             }];
    
    [self bjl_observe:BJLMakeMethod(self.room.roomVM, didReceiveRollcallWithTimeout:)
             observer:^BOOL(NSTimeInterval timeout) {
                 strongdef(self);
                 
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
                 strongdef(self);
                 [self.console printFormat:@"收到历史测验: %@ - 正确 %td, 错误 %td",
                  [surveyHistory yy_modelToJSONObject], rightCount, wrongCount];
                 return YES;
             }];
    
    [self bjl_observe:BJLMakeMethod(self.room.roomVM, didReceiveSurvey:)
             observer:^BOOL(BJLSurvey *survey) {
                 strongdef(self);
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
                 strongdef(self);
                 [self.console printFormat:@"收到测验结果: %td - %@",
                  order, [results yy_modelToJSONObject]];
                 return YES;
             }];
    
    [self.room.roomVM loadSurveyHistory];
    
    [self bjl_observe:BJLMakeMethod(self.room.roomVM, didReceiveCustomizedSignal:value:)
             observer:^BOOL(NSString *key, id value) {
                 strongdef(self);
                 [self.console printFormat:@"客户定制信令: %@ - %@", key, value];
                 return YES;
             }];
    
    [self bjl_kvo:BJLMakeProperty(self.room.roomVM, rollcallTimeRemaining)
           filter:^BOOL(NSNumber * _Nullable old, NSNumber * _Nullable now) {
               // strongdef(self);
               return now.doubleValue != old.doubleValue;
           }
         observer:^BOOL(NSNumber * _Nullable old, NSNumber * _Nullable now) {
             strongdef(self);
             [self.console printFormat:@"答到倒计时: %f", now.doubleValue];
             return YES;
         }];
}

@end
