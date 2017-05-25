//
//  BJLNotice.h
//  BJLiveCore
//
//  Created by MingLQ on 2017-03-09.
//  Copyright © 2017 Baijia Cloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <YYModel/YYModel.h>

NS_ASSUME_NONNULL_BEGIN

@interface BJLNotice : NSObject <YYModel>

@property (nonatomic, readonly, nullable) NSString *noticeText;
@property (nonatomic, readonly, nullable) NSURL *linkURL;

@end

NS_ASSUME_NONNULL_END
