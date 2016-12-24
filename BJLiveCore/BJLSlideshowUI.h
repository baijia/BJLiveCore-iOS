//
//  BJLSlideshowUI.h
//  Pods
//
//  Created by MingLQ on 2016-12-19.
//
//

#import <Foundation/Foundation.h>

@protocol BJLSlideshowUI <NSObject>

@property (nonatomic) BJLSlideshowContentMode contentMode;
@property (nonatomic) BOOL whiteboardEnabled;

- (void)clearWhiteboard;

@end
