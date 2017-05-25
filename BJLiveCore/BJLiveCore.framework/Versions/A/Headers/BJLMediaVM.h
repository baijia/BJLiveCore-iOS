//
//  BJLMediaVM.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-12-17.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "BJLBaseVM.h"

NS_ASSUME_NONNULL_BEGIN

@interface BJLMediaVM : BJLBaseVM

/** 上、下行链路类型 */
@property (nonatomic) BJLLinkType upLinkType, downLinkType;

// TODO: MingLQ - debug 信令处理

/** 调试: 获取音视频流信息 */
- (NSArray<NSString *> *)avDebugInfo;

@end

NS_ASSUME_NONNULL_END
