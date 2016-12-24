//
//  BJLOnlineUsersVM.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-11-15.
//
//

#import "BJLBaseVM.h"

#import "BJLUser.h"

NS_ASSUME_NONNULL_BEGIN

@interface BJLOnlineUsersVM : BJLBaseVM

/** 在线人数 */
@property (nonatomic, readonly) NSInteger onlineUsersTotalCount;
/** 在线用户，分页加载
 参考 `- loadMoreOnlineUsersWithCount:` */
@property (nonatomic, readonly, nullable, copy) NSArray<NSObject<BJLOnlineUser> *> *onlineUsers;
/** 是否有更多在线用户未加载 */
@property (nonatomic, readonly) BOOL hasMoreOnlineUsers;
/** 在线的老师 */
@property (nonatomic, readonly, nullable) NSObject<BJLOnlineUser> *onlineTeacher;

/** 加载更多在线用户
 加载成功更新 `onlineUsers`，内部不主动调用此方法 */
- (nullable BJLError *)loadMoreOnlineUsersWithCount:(NSInteger)count; // count 最多 30

/** 有用户进入房间
 同时更新 `onlineUsers` */
- (BJLOEvent)onlineUserDidEnter:(NSObject<BJLOnlineUser> *)user;
/** 有用户退出房间
 同时更新 `onlineUsers` */
- (BJLOEvent)onlineUserDidExit:(NSObject<BJLOnlineUser> *)user;

@end

NS_ASSUME_NONNULL_END
