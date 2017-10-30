//
//  _LPPageChangedModel.h
//  BJLiveCore
//
//  Created by 杨磊 on 16/3/30.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "_LPResRoomModel.h"

@interface _LPResPageChanged : _LPResRoomModel

@property (nonatomic, copy) NSString *docId;
@property (nonatomic, assign) NSUInteger page;

@end
