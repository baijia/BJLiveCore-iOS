//
//  _LPRoomLoginModel.h
//  BJLiveCore
//
//  Created by 杨磊 on 16/3/30.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import  "_LPResRoomModel.h"

/**
 *  room server 登录返回数据
 */
@interface _LPRoomLoginModel : _LPResRoomModel

@property (nonatomic, assign) NSInteger code;
@property (nonatomic, assign) BOOL started; // 上课状态
@property (nonatomic, assign) _LPSpeakState speakState;
@property (nonatomic, assign) NSInteger userCount;
@property (nonatomic, assign) NSInteger timestamp; // seconds since 1970

@end
