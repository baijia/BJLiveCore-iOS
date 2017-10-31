//
//  BJLRoom+GSX.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-11-28.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "BJLRoom.h"

#import "BJLFeatureConfig.h"

// #import "BJLGiftVM.h"
#import "BJLHelpVM.h"

NS_ASSUME_NONNULL_BEGIN

@interface BJLRoom ()

/** 部署环境
 调用 enter 之后设置无效
 仅 Debug 模式下有效 */
@property (nonatomic) BJLDeployType deployType;

@end

@interface BJLRoom (readonly)

/**
 功能设置
 分为 服务端配置权限 和 客户端配置开关；
 - 服务端配置权限：表示是否有权限使用某功能；
 - 客户端配置开关：表示是否开启某功能；
 当服务端配置某功能没有权限时，客户端配置开关将被忽略；
 当客户端配置为空时，所有服务端配置有权限的功能默认开启；
 此处 featureConfig 是综合了 服务端配置权限 和 客户端配置开关 后的结果；
 BJLiveCore 内部【不】读取此处 featureConfig
 */
@property (nonatomic, readonly, nullable, copy) BJLFeatureConfig *featureConfig;

/** 电话求助 */
@property (nonatomic, readonly, nullable) BJLHelpVM *helpVM;

/** 打赏 */
// @property (nonatomic, readonly, nullable) BJLGiftVM *giftVM;

@end

NS_ASSUME_NONNULL_END
