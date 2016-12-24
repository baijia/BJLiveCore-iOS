//
//  BJLRoomVM.h
//  Pods
//
//  Created by MingLQ on 2016-12-05.
//
//

#import "BJLBaseVM.h"

#import "BJLRoomInfo.h"
#import "BJLUser.h"

NS_ASSUME_NONNULL_BEGIN

@interface BJLRoomVM : BJLBaseVM

/** 教室信息
 !!!: BJLiveCore 内部【不】读取此处 roomInfo */
@property (nonatomic, readonly, copy) NSObject<BJLRoomInfo> *roomInfo;
/** 当前登录用户信息
 !!!: BJLiveCore 内部【不】读取此处 loginUser */
@property (nonatomic, readonly, copy) NSObject<BJLUser> *loginUser;

/** 进入教室时间 */
@property (nonatomic, readonly) NSTimeInterval enteringTimeInterval; // seconds since 1970
/** 上课状态 */
@property (nonatomic, readonly) BOOL liveStarted;
/** 教室发言类型
 自由模式/举手模式 */
@property (nonatomic, readonly) BJLSpeakType speakType;
/** 教室公告 */
@property (nonatomic, readonly, copy) NSString *noticeText;

#pragma mark - for teacher

/** 老师: 设置上课状态
 设置成功后修改 `liveStarted` */
- (nullable BJLError *)sendLiveStarted:(BOOL)liveStarted;

/** 获取教室公告
 获取成功后修改 `noticeText` */
- (void)loadNoticeText;
/** 老师: 设置教室公告
 设置成功后修改 `noticeText` */
- (nullable BJLError *)sendNoticeText:(NSString *)noticeText;

@end

NS_ASSUME_NONNULL_END
