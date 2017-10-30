//
//  _LPDocContext.h
//  BJLiveCore
//
//  Created by Randy on 16/4/9.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ReactiveCocoa/ReactiveCocoa.h>

#import "_LPConstants.h"

#import "_LPRoomServer+Document.h"

@class _LPDocPageItem;
@class _LPDocument;

@interface _LPDocContext : NSObject

- (instancetype)initWithRoomServer:(_LPRoomServer *)roomServer;

/**
 *  如果doc有变化，可通过监听此属性是否有变化来得知
 */
@property (strong, readonly, nonatomic) NSArray<_LPDocPageItem *> *allDocsPageList;
@property (strong, readonly, nonatomic) NSArray<_LPDocument *> *allDocList;

/**
 *  针对allDocsPageList列表的
 */
@property (assign, readonly, nonatomic) NSUInteger curPageIndex;
- (void)setCurPageIndex:(NSUInteger)curPageIndex;

@property (assign, nonatomic) _LPPPTMode pptMode;

@property (nonatomic) BOOL studentCanPreviewForward;
@property (nonatomic) BOOL studentCanRemoteControl;

@property (nonatomic) UIImage *placeholderImage;

@end
