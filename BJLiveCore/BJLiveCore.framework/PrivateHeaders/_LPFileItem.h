//
//  _LPFileItem.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-06-23.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "_LPDataModel.h"

@interface _LPFileItem : _LPDataModel

@property (nonatomic, copy) NSString *fileID, *fileName, *fileURL;

@end
