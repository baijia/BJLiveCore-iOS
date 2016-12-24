//
//  BJRoomViewController+users.m
//  BJLiveCore
//
//  Created by MingLQ on 2016-12-19.
//  Copyright © 2016 GSX. All rights reserved.
//

#import "BJRoomViewController+users.h"

@implementation BJRoomViewController (users)

- (void)makeUserEvents {
    weakdef(self);
    
    [self bjl_KVObserve:self.room.onlineUsersVM
                 getter:@selector(onlineUsersTotalCount)
                 filter:^BOOL(NSNumber *old, NSNumber *now) {
                     // strongdef(self);
                     return old.integerValue != now.integerValue;
                 }
             usingBlock:^(id old, id now) {
                 strongdef(self);
                 [self.console printFormat:@"onlineUsers count: %@", now];
             }];
    
    [self bjl_KVObserve:self.room.onlineUsersVM
                 getter:@selector(onlineTeacher)
             usingBlock:^(id old, NSObject<BJLOnlineUser> *now) {
                 strongdef(self);
                 [self.console printFormat:@"onlineUsers teacher: %@", now.name];
             }];
    
    [self bjl_KVObserve:self.room.onlineUsersVM
                 getter:@selector(onlineUsers)
             usingBlock:^(id old, NSArray<NSObject<BJLOnlineUser> *> *now) {
                 strongdef(self);
                 NSMutableArray *userNames = [NSMutableArray new];
                 for (NSObject<BJLOnlineUser> *user in now) {
                     [userNames addObjectOrNil:user.name];
                 }
                 [self.console printFormat:@"onlineUsers all: %@",
                  [userNames componentsJoinedByString:@", "]];
             }];
    
    [self bjl_observe:self.room.onlineUsersVM
                event:@selector(onlineUserDidEnter:)
           usingBlock:^(NSObject<BJLOnlineUser> *user/* , id object, BJLOEventType event */) {
               strongdef(self);
               [self.console printFormat:@"onlineUsers in: %@", user.name];
           }];
    
    [self bjl_observe:self.room.onlineUsersVM
                event:@selector(onlineUserDidExit:)
           usingBlock:^(NSObject<BJLOnlineUser> *user/* , id object, BJLOEventType event */) {
               strongdef(self);
               [self.console printFormat:@"onlineUsers out: %@", user.name];
           }];
    
    [self.room.onlineUsersVM loadMoreOnlineUsersWithCount:10];
}

@end
