//
//  _LPDocument.h
//  BJLiveCore
//
//  Created by 杨磊 on 16/3/30.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "_LPDataModel.h"

@interface _LPDocumentPageInfo : _LPDataModel

@property (nonatomic, assign) NSInteger totalPages; // 文档总页数
@property (nonatomic, copy) NSString *urlPrefix; // 图片前缀
@property (nonatomic, copy) NSString *url;
@property (nonatomic, assign) BOOL isDoc;
@property (nonatomic, assign) NSInteger width; //原始宽
@property (nonatomic, assign) NSInteger height; //原始高

@end

@interface _LPDocument : _LPDataModel

@property (nonatomic, copy) NSString *docId;
@property (nonatomic, copy) NSString *number; // id 是信令服务器分配的，number 是文档服务器分配的 (fid)
@property (nonatomic, copy) NSString *ext; // 扩展名，如 pdf，小写
@property (nonatomic, copy) NSString *name; // 文件名，不包括扩展名
@property (nonatomic, strong) _LPDocumentPageInfo *pageInfo;

@end
