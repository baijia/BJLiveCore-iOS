//
//  _LPClassModel.h
//  BJLiveCore
//
//  Created by Randy on 16/4/5.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "_LPDataModel.h"

@interface _LPClassModel : _LPDataModel
@property (copy, nonatomic) NSString *classId;
@property (copy, nonatomic) NSString *number;
@property (copy, nonatomic) NSString *name;
@property (assign, nonatomic) NSInteger serialNumber;
@property (assign, nonatomic) NSInteger type;//教室类型 1/2   一对一/班课
@property (assign, nonatomic) NSInteger merged;//参数为1时是一对一课合成的班课
@property (assign, nonatomic) NSTimeInterval startTime;
@property (assign, nonatomic) NSTimeInterval endTime;
@property (assign, nonatomic) NSInteger signUpNumber;//报名人数

@property (copy, nonatomic) NSString *authUrl;
@property (copy, nonatomic) NSString *cover;
@property (assign, nonatomic) BOOL isChaban;
@property (assign, nonatomic) BOOL isFree;
@property (assign, nonatomic) NSInteger mode;
@property (assign, nonatomic) NSInteger roomNo;
@property (copy, nonatomic) NSString *scheduleName;

@end
