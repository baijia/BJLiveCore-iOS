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

/**
 功能设置
 分为 服务端配置权限 和 客户端配置开关；
 - 服务端配置权限：表示是否有权限使用某功能；
 - 客户端配置开关：表示是否开启某功能；
 当服务端配置某功能没有权限时，客户端配置开关将被忽略；
 当客户端配置为空时，所有服务端配置有权限的功能默认开启；
 此处 featureConfig 是综合了 服务端配置权限 和 客户端配置开关 后的结果；
 !!!: BJLiveCore 内部不读取此处 featureConfig，因此对其的属性值的更改无效，参考具体实现；
 */
@property (nonatomic, readonly, copy) BJLFeatureConfig *featureConfig;
/** 教室信息 */
@property (nonatomic, readonly) NSObject<BJLRoomInfo> *roomInfo;
/** 当前登录用户信息 */
@property (nonatomic, readonly) NSObject<BJLUser> *loginUser;

/** 进入教室时间 */
@property (nonatomic, readonly) NSTimeInterval enteringTimeInterval; // seconds since 1970
/** 上课状态 */
@property (nonatomic, readonly) BOOL liveStarted;
/** 教室发言类型
 自由模式/举手模式 */
@property (nonatomic, readonly) BJLSpeakType speakType;
/** 聊天全体禁言 */
// TODO: MingLQ - chatVM 发消息时检查此状态返回错误
// @property (nonatomic, readonly) BOOL chatForbidAll;
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
