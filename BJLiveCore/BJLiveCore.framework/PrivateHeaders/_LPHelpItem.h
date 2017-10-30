//
//  _LPHelpItem.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-06-16.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface _LPHelpItem : NSObject

@property (nonatomic, readonly, copy) NSString *companyName;
@property (nonatomic, readonly, copy) NSString *userPhoneNumber, *maskedUserPhoneNumber, *helpPhoneNumber;

+ (instancetype)helpItemWithCompanyName:(NSString *)companyName
                        userPhoneNumber:(NSString *)userPhoneNumber
                        helpPhoneNumber:(NSString *)helpPhoneNumber;

@end
