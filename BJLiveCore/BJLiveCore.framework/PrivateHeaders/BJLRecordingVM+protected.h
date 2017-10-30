//
//  BJLRecordingVM+protected.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-12-10.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "BJLBaseVM.h"

NS_ASSUME_NONNULL_BEGIN

@interface BJLRecordingVM ()

/** 切换链路后调用 Media-Re(WTF)-Publish */
- (void)restartRecordingForRepublish:(BOOL)republish;

@end

NS_ASSUME_NONNULL_END
