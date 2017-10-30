//
//  _LPDocPageItem.h
//  BJLiveCore
//
//  Created by Randy on 16/4/9.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "_LPDataModel.h"

@interface _LPDocPageItem : _LPDataModel
@property (nonatomic, copy) NSString *docId;
@property (nonatomic, assign) NSUInteger docPageIndex;

@property (nonatomic, copy) NSString *url; // 图片
@property (nonatomic, assign) NSInteger width; //原始宽
@property (nonatomic, assign) NSInteger height; //原始高

@end
