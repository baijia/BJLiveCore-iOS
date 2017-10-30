//
//  _LPWSResponseItem.h
//  BJLiveCore
//
//  Created by 杨磊 on 16/3/30.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface _LPWSResponseItem : NSObject
@property (nonatomic, copy) Class class;
@property (nonatomic, assign) SEL selector;

- (instancetype)initWithClass:(Class)class selector:(SEL)selector;
@end
