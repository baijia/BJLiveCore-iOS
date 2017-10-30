//
//  _LPSurveyRes.h
//  Pods
//
//  Created by MingLQ on 2017-03-07.
//  Copyright © 2017 Baijia Cloud. All rights reserved.
//

#import "_LPResRoomModel.h"

#import "BJLSurvey.h"

@interface _LPSurveyRes : _LPResRoomModel

@property (nonatomic, readonly) NSArray<BJLSurvey *> *surveys;
@property (nonatomic, readonly) NSInteger rightCount, wrongCount;

@end

@interface _LPSurveyReceive : _LPResRoomModel

@property (nonatomic, readonly) BJLSurvey *survey;

@end

@interface _LPSurveyResult : _LPResRoomModel

@property (nonatomic, readonly) NSInteger order;
@property (nonatomic, readonly) NSDictionary<NSString *, NSNumber *> *result;

@end

@interface _LPSurveyUserResult : _LPResRoomModel

@property (nonatomic, readonly) NSInteger order;
@property (nonatomic, readonly) NSDictionary<NSString *, NSArray<NSString *> *> *result;

@end
