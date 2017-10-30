//
//  _LPBroadcastOptions.h
//  BJLiveCore
//
//  Created by 杨磊 on 16/3/31.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "_LPDataModel.h"

@interface _LPBroadcastOptions : _LPDataModel

@property (nonatomic, assign) BOOL cache;//是否需要缓存，进教室的时候发送 broadcast_cache_req 获取
@property (nonatomic, assign) BOOL all; //是否全员广播

@end
