//
//  _LPRoomServer+Document.h
//  BJLiveCore
//
//  Created by 杨磊 on 16/3/30.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "_LPRoomServer.h"
#import "_LPDocument.h"
#import "_LPResDocAdd.h"
#import "_LPResDocDel.h"
#import "_LPResDocAll.h"
#import "_LPResPageChanged.h"

/**
 *  文档相关信令服务
 */
@interface _LPRoomServer (Document)

/**
 *  添加文档
 */
- (void)requestDocAdd:(_LPDocument *)document;
/**
 *  _LPResDocAdd
 *
 *  @return signal
 */
- (RACSignal *)signalOfDocAdd;

/**
 *  删除文档
 */
- (void)requestDocDelete:(NSString *)docId;
/**
 *  _LPResDocDel
 *
 *  @return
 */
- (RACSignal *)signalOfDocDelete;

/**
 *  获取所有文档
 */
- (void)requestDocAll;
/**
 *  _LPResDocAll
 *
 *  @return
 */
- (RACSignal *)signalOfDocAll;

/**
 *  文档翻页
 *
 *  @param docId
 *  @param page  页码
 */
- (void)requestDocPageChange:(NSString *)docId
                  pageNumber:(NSUInteger)page;
/**
 *  _LPResPageChanged
 *
 *  @return
 */
- (RACSignal *)signalOfDocPageChanged;

@end
