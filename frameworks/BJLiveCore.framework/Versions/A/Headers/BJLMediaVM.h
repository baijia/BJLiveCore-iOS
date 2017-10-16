//
//  BJLMediaVM.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-12-17.
//  Copyright © 2016 BaijiaYun. All rights reserved.
//

#import "BJLBaseVM.h"

NS_ASSUME_NONNULL_BEGIN

/** ### 音视频设置 */
@interface BJLMediaVM : BJLBaseVM

/** 是否允许设置上、下行链路类型
 #discussion `upLinkTypeReadOnly`/`downLinkTypeReadOnly` 为 YES 时设置 `upLinkType`/`downLinkType` 无效
 */
@property (nonatomic, readonly) BOOL upLinkTypeReadOnly, downLinkTypeReadOnly;

/** 上、下行链路类型 */
@property (nonatomic) BJLLinkType upLinkType, downLinkType;

// TODO: MingLQ - debug 信令处理

/** 调试: 获取音视频流信息 */
- (NSArray<NSString *> *)avDebugInfo;

@end

NS_ASSUME_NONNULL_END
