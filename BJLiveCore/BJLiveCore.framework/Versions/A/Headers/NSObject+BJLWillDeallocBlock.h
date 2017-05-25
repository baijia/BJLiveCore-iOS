//
//  NSObject+BJLWillDeallocBlock.h
//  M9Dev
//
//  Created by MingLQ on 2016-11-28.
//  Copyright © 2016 MingLQ <minglq.9@gmail.com>. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef void (^BJLWillDeallocBlock)(id instance);

@interface NSObject (BJLWillDeallocBlock)

@property (nonatomic, readonly, nullable) BJLWillDeallocBlock bjl_willDeallocBlock;
- (void)bjl_setWillDeallocBlock:(void (^ _Nullable)(id instance))willDeallocBlock;

@end

NS_ASSUME_NONNULL_END
