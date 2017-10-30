//
//  _LPJSONAdapter.h
//  BJLiveCore
//
//  Created by Randy on 16/4/8.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface _LPJSONAdapter : NSObject

+ (id)modelOfClass:(Class)modelClass fromJSONDictionary:(NSDictionary *)JSONDictionary error:(NSError **)error;
+ (NSDictionary *)JSONDictionaryFromModel:(id)model error:(NSError **)error;

@end
