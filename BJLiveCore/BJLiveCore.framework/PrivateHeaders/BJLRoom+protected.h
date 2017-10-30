//
//  BJLRoom+protected.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-11-28.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "BJLRoom.h"

#import "_BJLWhiteboardVM.h"

NS_ASSUME_NONNULL_BEGIN

@class BJLContext;

@interface BJLRoom () {
    BJLContext * __weak _context;
}

@property (nonatomic, readonly, weak) BJLContext *context; // NON KVO

#pragma mark protected view-model

/**
 !!!: 如果要改为 public
 - 在 BJLRoom.h 里添加 readonly 定义、然后把 readwrite 定义移到 BJLRoom.m
 - vm 内 _LP 开头的 model 等需要重新封装，参考
    BJLGiftVM.h、BJLGift.h、LPGift+BJLGift.h
    BJLDocumentVM.h、BJLDocument.h、LPDocument+BJLDocument.h
 */

/** 标注 */
@property (nonatomic, readwrite, nullable) BJLWhiteboardVM *whiteboardVM;

@end

#pragma mark -

/** 通过 ID 创建的教室 */
@interface BJLRoom_ID : BJLRoom

@property (nonatomic, readonly, copy) NSString *ID, *apiSign;
@property (nonatomic, readonly) BJLUser *user;

@end

/** 通过参加码创建的教室 */
@interface BJLRoom_Secret : BJLRoom

@property (nonatomic, readonly, copy) NSString *roomSecret, *userName;
@property (nonatomic, readonly, nullable, copy) NSString *userAvatar;

@end

NS_ASSUME_NONNULL_END
