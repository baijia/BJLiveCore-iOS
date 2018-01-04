//
//  BJLDocument.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-12-07.
//  Copyright © 2016 BaijiaYun. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface BJLDocumentPageInfo : NSObject

@property (nonatomic, readonly) BOOL isAlbum;
@property (nonatomic, readonly) NSInteger pageCount;
/**
 if isAlbum, file urls format: {pageURLPrefix}_{pageIndex+1}.png
 if !isAlbum, file url: {pageURLString} */
@property (nonatomic, readonly, copy) NSString *pageURLString;
@property (nonatomic, readonly, copy, nullable) NSString *pageURLPrefix; // nil if NOT isAlbum

@property (nonatomic, readonly) NSInteger width, height;

- (BOOL)containsPageIndex:(NSInteger)pageIndex;

/** original pageURLString with pageIndex */
- (nullable NSString *)pageURLStringWithPageIndex:(NSInteger)pageIndex;

- (nullable NSString *)pageURLStringWithPageIndex:(NSInteger)pageIndex
                                         fillSize:(CGSize)size
                                           format:(nullable NSString *)ext DEPRECATED_MSG_ATTRIBUTE("use `BJLAliIMG_aspectFill`, `BJLAliIMG_aspectFit` or `BJLSlidePage - pageURLStringWithSize:fill:format:`");
- (nullable NSString *)pageURLStringWithPageIndex:(NSInteger)pageIndex
                                         fillSize:(CGSize)size
                                            scale:(CGFloat)scale
                                           format:(nullable NSString *)ext DEPRECATED_MSG_ATTRIBUTE("use `BJLAliIMG_aspectFill`, `BJLAliIMG_aspectFit` or `BJLSlidePage - pageURLStringWithSize:fill:format:`");

@end

#pragma mark -

@interface BJLDocument : NSObject

@property (nonatomic, readonly, copy, nullable) NSString *documentID;
@property (nonatomic, readonly, copy) NSString *fileID, *fileName, *fileExtension;
@property (nonatomic, readonly) BJLDocumentPageInfo *pageInfo;

- (BOOL)isSyncedWithServer; 
- (BOOL)isWhiteBoard;

+ (instancetype)documentWithUploadResponseData:(NSDictionary *)responseData;

@end

NS_ASSUME_NONNULL_END
