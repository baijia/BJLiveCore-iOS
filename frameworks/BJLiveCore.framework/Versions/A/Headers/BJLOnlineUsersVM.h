//
//  BJLOnlineUsersVM.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-11-15.
//  Copyright © 2016 BaijiaYun. All rights reserved.
//

#import "BJLBaseVM.h"

#import "BJLUser.h"

NS_ASSUME_NONNULL_BEGIN

/** ### 在线用户 */
@interface BJLOnlineUsersVM : BJLBaseVM

/** 在线人数 */
@property (nonatomic, readonly) NSInteger onlineUsersTotalCount;
/** 在线用户，分页加载
 #discussion `loadMoreOnlineUsersWithCount:` 导致的更新会先重置为 nil，然后再赋值，可用来区分单个更新
 #discussion 参考 `loadMoreOnlineUsersWithCount:`
 */
@property (nonatomic, readonly, copy, nullable) NSArray<BJLUser *> *onlineUsers;

/** `onlineTeacher`、`currentPresenter` 是否加载完成
 #discussion 1、连接教室后、掉线重新连接后，都会重置为 NO
 #discussion 2、然后重置 `onlineTeacher`、`currentPresenter`
 #discussion 3、然后自动加载 `onlineTeacher`、`currentPresenter`
 #discussion 4、加载完成后为 YES，`onlineTeacher`、`currentPresenter` 可能为 nil
 */
@property (nonatomic, readonly) BOOL activeUsersSynced;
/** 在线的老师 */
@property (nonatomic, readonly, nullable) BJLUser *onlineTeacher;
/** 当前主讲，可能和 `onlineTeacher` 相同、也可能不同 */
@property (nonatomic, readonly, nullable) BJLUser *currentPresenter;

/** 是否有更多在线用户未加载 */
@property (nonatomic, readonly) BOOL hasMoreOnlineUsers; // NON-KVO
/** 加载更多在线用户
 #discussion 连接教室后、掉线重新连接后自动调用加载
 #discussion 加载成功更新 `onlineUsers`
 #discussion 参考 `hasMoreOnlineUsers`
 #param count 传 0 默认 20、最多 30
 #return BJLError：
 BJLErrorCode_invalidCalling    错误调用，如 `hasMoreOnlineUsers` 为 NO 时调用此方法
 */
- (nullable BJLError *)loadMoreOnlineUsersWithCount:(NSInteger)count;

/** 有用户进入教室
 #discussion 批量更新时不会调用
 #discussion 同时更新 `onlineUsers`
 #param user 用户
 */
- (BJLObservable)onlineUserDidEnter:(BJLUser *)user;
/** 有用户退出教室
 #discussion 批量更新时不会调用
 #discussion 同时更新 `onlineUsers`
 #param user 用户
 */
- (BJLObservable)onlineUserDidExit:(BJLUser *)user;

@end

NS_ASSUME_NONNULL_END
