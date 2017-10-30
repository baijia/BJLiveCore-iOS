//
//  _LPMasterServer.h
//  BJLiveCore
//
//  Created by 杨磊 on 16/3/25.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "_LPWSServerBase.h"

@class RACSignal;

/**
 *  master server 业务逻辑
 */
@interface _LPMasterServer : _LPWSServerBase

/**
 *  _LPLoginModel
 */
@property (nonatomic, strong, readonly) RACSignal *signalOfLogin;

/**
 *  登录 master 服务器
 *
 *  @param classId       <#classId description#>
 *  @param teacherNumber <#teacherNumber description#>
 *  @param userType      <#userType description#>
 *  @param classType     <#classType description#>
 *  @param clientIp      <#clientIp description#>
 */
// 预先设置登录信息、在连接成功后发送
- (void)loginWithClassId:(NSString *)classId
           teacherNumber:(NSString *)teacherNumber
                userType:(NSInteger)userType
               classType:(NSInteger)classType
                clientIp:(NSString *)clientIp;

@end
