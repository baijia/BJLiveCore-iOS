//
//  _LPDocAllModel.h
//  BJLiveCore
//
//  Created by 杨磊 on 16/3/30.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "_LPResRoomModel.h"
#import "_LPDocument.h"

@interface _LPResDocAll : _LPResRoomModel


@property (nonatomic, copy) NSString *currentDocId;
@property (nonatomic, assign) NSUInteger currentPage;

@property (nonatomic, strong) NSArray<_LPDocument *> *docList;

@end
