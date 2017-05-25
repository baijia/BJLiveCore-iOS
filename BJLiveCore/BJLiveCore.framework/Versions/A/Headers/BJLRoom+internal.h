//
//  BJLRoom+internal.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-11-28.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "BJLRoom.h"

NS_ASSUME_NONNULL_BEGIN

@interface BJLRoom ()

/** 部署环境
 调用 enter 之后设置无效
 仅 Debug 模式下有效 */
@property (class, nonatomic) BJLDeployType deployType;

@end

NS_ASSUME_NONNULL_END
