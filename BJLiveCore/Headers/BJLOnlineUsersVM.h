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
 连接教室后、掉线重新连接后自动调用加载
 加载成功更新 `onlineUsers` */
// count: 传 0 默认 20、最多 30
- (nullable BJLError *)loadMoreOnlineUsersWithCount:(NSInteger)count;

/** 有用户进入房间
 同时更新 `onlineUsers` */
- (BJLObservable)onlineUserDidEnter:(NSObject<BJLOnlineUser> *)user;
/** 有用户退出房间
 同时更新 `onlineUsers` */
- (BJLObservable)onlineUserDidExit:(NSObject<BJLOnlineUser> *)user;

@end

NS_ASSUME_NONNULL_END
