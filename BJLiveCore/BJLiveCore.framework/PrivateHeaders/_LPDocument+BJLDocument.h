//
//  _LPDocument+BJLDocument.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-12-07.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "_LPDocument.h"

#import "BJLDocument.h"

NS_ASSUME_NONNULL_BEGIN

@interface _LPDocumentPageInfo (BJLDocumentPageInfo) <BJLDocumentPageInfo>

+ (nullable instancetype)pageInfoWithPageInfo:(NSObject<BJLDocumentPageInfo> *)pageInfo;

@end

@interface _LPDocument (BJLDocument) <BJLDocument>

+ (nullable instancetype)documentWithDocument:(NSObject<BJLDocument> *)document;

@end

NS_ASSUME_NONNULL_END
