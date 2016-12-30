//
//  BJLMediaVM.h
//  Pods
//
//  Created by MingLQ on 2016-12-17.
//
//

#import "BJLBaseVM.h"

@interface BJLMediaVM : BJLBaseVM

/** 上、下行链路类型 */
@property (nonatomic) BJLLinkType upLinkType, downLinkType;

// TODO: MingLQ - debug 信令处理

/** 调试: 获取音视频流信息 */
- (NSArray<NSString *> *)avDebugInfo;

@end
