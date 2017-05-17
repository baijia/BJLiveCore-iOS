//
//  BJLOnlineUsersVM.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-11-15.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "BJLBaseVM.h"

#import "BJLUser.h"

NS_ASSUME_NONNULL_BEGIN

@interface BJLOnlineUsersVM : BJLBaseVM

/** 在线人数 */
@property (nonatomic, readonly) NSInteger onlineUsersTotalCount;
/** 在线用户，分页加载
 `loadMoreOnlineUsersWithCount:` 导致的更新会先重置为 nil，然后再赋值，可用来区分单个更新
 参考 `loadMoreOnlineUsersWithCount:`
 */
@property (nonatomic, readonly, copy, nullable) NSArray<BJLOnlineUser *> *onlineUsers;

/** `onlineUsers` 被覆盖更新
 覆盖更新才调用，增量更新不调用
 `loadMoreOnlineUsersWithCount:` 会导致覆盖更新
 */
- (BJLObservable)onlineUsersDidOverwrite:(nullable NSArray<BJLOnlineUser *> *)onlineUsers;

/** 是否有更多在线用户未加载 */
@property (nonatomic, readonly) BOOL hasMoreOnlineUsers;
/** 在线的老师 */
@property (nonatomic, readonly, nullable) BJLOnlineUser *onlineTeacher;

/** 加载更多在线用户
 连接教室后、掉线重新连接后自动调用加载
 加载成功更新 `onlineUsers`
 @param count 传 0 默认 20、最多 30
 */
- (nullable BJLError *)loadMoreOnlineUsersWithCount:(NSInteger)count;

/** 有用户进入房间
 同时更新 `onlineUsers` */
- (BJLObservable)onlineUserDidEnter:(BJLOnlineUser *)user;
/** 有用户退出房间
 同时更新 `onlineUsers` */
- (BJLObservable)onlineUserDidExit:(BJLOnlineUser *)user;

@end

NS_ASSUME_NONNULL_END
