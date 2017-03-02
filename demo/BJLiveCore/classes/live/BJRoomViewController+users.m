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
                     observer:^BOOL(id old, NSObject<BJLOnlineUser> *now) {
                         strongdef(self);
                         [self.console printFormat:@"onlineUsers teacher: %@", now.name];
                         return YES;
                     }];
    
    [self bjl_kvo:BJLMakeProperty(self.room.onlineUsersVM, onlineUsers)
                     observer:^BOOL(id old, NSArray<NSObject<BJLOnlineUser> *> *now) {
                         strongdef(self);
                         NSMutableArray *userNames = [NSMutableArray new];
                         for (NSObject<BJLOnlineUser> *user in now) {
                             [userNames addObjectOrNil:user.name];
                         }
                         [self.console printFormat:@"onlineUsers all: %@",
                          [userNames componentsJoinedByString:@", "]];
                         return YES;
                     }];
    
    [self bjl_observe:BJLMakeMethod(self.room.onlineUsersVM, onlineUserDidEnter:)
             observer:^BOOL(NSObject<BJLOnlineUser> *user) {
                 strongdef(self);
                 [self.console printFormat:@"onlineUsers in: %@", user.name];
                 return YES;
             }];
    
    [self bjl_observe:BJLMakeMethod(self.room.onlineUsersVM, onlineUserDidExit:)
             observer:^BOOL(NSObject<BJLOnlineUser> *user) {
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
