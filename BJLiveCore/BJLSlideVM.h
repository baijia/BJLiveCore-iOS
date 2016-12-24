//
//  BJLSlideVM.h
//  Pods
//
//  Created by MingLQ on 2016-12-07.
//
//

#import "BJLBaseVM.h"

#import "BJLDocument.h"

NS_ASSUME_NONNULL_BEGIN

@interface BJLSlideVM : BJLBaseVM

/** 翻页课件 */
- (nullable BJLError *)requestTurnToDocumentID:(NSString *)documentID
                                     pageIndex:(NSInteger)pageIndex;

/** 添加课件 */
- (nullable BJLError *)addDocument:(NSObject<BJLDocument> *)document;

/** 删除课件 */
- (nullable BJLError *)deleteDocumentWithID:(NSString *)documentID;

/**
 上传图片并添加课件
 @param images      图片
 @param progress    进度
 @param finish      结束，completed == total 表示全部上传成功
 - total        总数量
 - completed    已完成数量
 - progress     0.0 ~ 1.0 单个图片进度，总进度 = (CGFloat)completed / total + progress
 - error        错误
 */
- (void)addImagesWithFileURLs:(NSArray<NSURL *> *)fileURLs
                     progress:(void (^)(NSInteger total, NSInteger completed, CGFloat progress))progress
                       finish:(void (^)(NSInteger total, NSInteger completed, BJLError * _Nullable error))finish;

@end

NS_ASSUME_NONNULL_END
