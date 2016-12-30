//
//  BJLDocument.h
//  Pods
//
//  Created by MingLQ on 2016-12-07.
//
//

#import <Foundation/Foundation.h>
#import <YYModel/YYModel.h>

NS_ASSUME_NONNULL_BEGIN

@protocol BJLDocumentPageInfo <NSObject, YYModel>

@property (nonatomic, readonly) BOOL isAlbum;
@property (nonatomic, readonly) NSInteger pageCount;
/**
 if isAlbum, file urls format: {pageURLPrefix}_{pageIndex+1}.png
 if !isAlbum, file url: {pageURLString} */
@property (nonatomic, readonly, copy) NSString *pageURLString, *pageURLPrefix;

@property (nonatomic, readonly) NSInteger width, height;

- (BOOL)containsPageIndex:(NSInteger)pageIndex;
- (nullable NSString *)pageURLStringStringWithPageIndex:(NSInteger)pageIndex;

@end

@interface BJLDocumentPageInfo : NSObject <BJLDocumentPageInfo>

@property (nonatomic, readwrite) BOOL isAlbum;
@property (nonatomic, readwrite) NSInteger pageCount;
@property (nonatomic, readwrite, copy) NSString *pageURLString, *pageURLPrefix;
@property (nonatomic, readwrite) NSInteger width, height;

@end

#pragma mark -

@protocol BJLDocument <NSObject, YYModel>

@property (nonatomic, readonly, copy) NSString *documentID, *fileID, *fileName, *fileExtension;
@property (nonatomic, readonly) NSObject<BJLDocumentPageInfo> *pageInfo;

@end

@interface BJLDocument : NSObject <BJLDocument>

@property (nonatomic, readwrite, copy) NSString *documentID, *fileID, *fileName, *fileExtension;
@property (nonatomic, readwrite) NSObject<BJLDocumentPageInfo> *pageInfo;

@end

NS_ASSUME_NONNULL_END
