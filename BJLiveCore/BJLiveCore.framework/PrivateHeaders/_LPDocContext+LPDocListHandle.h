//
//  _LPDocContext+LPDocListHandle.h
//  BJLiveCore
//
//  Created by Randy on 16/4/9.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "_LPDocContext.h"

@class _LPDocPageItem;
@class _LPDocument;

@interface _LPDocContext (_LPDocListHandle)

- (_LPDocPageItem *)docPageWithdocId:(NSString *)docId page:(NSUInteger)page;

- (NSArray<_LPDocPageItem *> *)createDocPagesWithDoc:(_LPDocument *)doc;

- (_LPDocument *)docmentItemWithDocId:(NSString *)docId;

- (NSArray<_LPDocPageItem *> *)docPagesWithDocId:(NSString *)docId;

@end
