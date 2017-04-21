//
//  BJLSlideVM.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-12-07.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "BJLBaseVM.h"

#import "BJLDocument.h"

NS_ASSUME_NONNULL_BEGIN

@interface BJLSlideVM : BJLBaseVM

/** 翻页课件 */
- (nullable BJLError *)requestTurnToDocumentID:(NSString *)documentID
                                     pageIndex:(NSInteger)pageIndex;

/** 添加课件
 添加成功将调用 `BJLSlideshowVM` 的 `didAddDocument:`
 */
- (nullable BJLError *)addDocument:(BJLDocument *)document;

/** 删除课件
 删除成功将调用 `BJLSlideshowVM` 的 `didDeleteDocument:`
 */
- (nullable BJLError *)deleteDocumentWithID:(NSString *)documentID;

/**
 上传图片
 @param fileURL     图片文件路径
 @param progress    上传进度
 - progress         0.0 ~ 1.0 单个图片进度，总进度 = (CGFloat)completed / total + progress
 @param finish      结束
 - document         非 nil 即为成功，用于 `addDocument:`
 - error            错误
 @return            upload task
 */
- (NSURLSessionUploadTask *)uploadImageFile:(NSURL *)fileURL
                                   progress:(nullable void (^)(CGFloat progress))progress
                                     finish:(void (^)(BJLDocument * _Nullable document, BJLError * _Nullable error))finish;

@end

NS_ASSUME_NONNULL_END
