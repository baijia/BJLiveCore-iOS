//
//  BJLServerRecordingVM+GSX.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-12-06.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "BJLBaseVM.h"

NS_ASSUME_NONNULL_BEGIN

@interface BJLServerRecordingVM ()

/** 检查云端录课是否可用
 e.g.
 room.serverRecordingVM = ^(void (^callback)(BOOL canRecord, NSString *message)) {
     [BJNetworking get:@"xxxx" success:^(id response) {
          callback(response.status, response.reason);
      } failure:^(id error) {
          callback(NO, error.reason);
      }];
 } */
@property (nonatomic, copy) void (^checkServerRecordingBlock)(void (^callback)(BOOL canRecord, NSString *message));

@end

NS_ASSUME_NONNULL_END
