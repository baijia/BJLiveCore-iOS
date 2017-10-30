//
//  BJLLoadingVM+task3-connectMasterServer.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-11-30.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "BJLBaseVM+protected.h"
#import "BJLLoadingVM.h"

NS_ASSUME_NONNULL_BEGIN

@interface BJLLoadingVM (connectMasterServer)

- (BJLLoadingTask)connectMasterServerTask;

@end

NS_ASSUME_NONNULL_END
