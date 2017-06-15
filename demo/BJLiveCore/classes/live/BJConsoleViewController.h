//
//  BJConsoleViewController.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-12-13.
//
//

#import "BJTableViewController.h"

@interface BJConsoleViewController : BJTableViewController <UITableViewDataSource, UITableViewDelegate>

- (void)printLine:(NSString *)line;
- (void)printFormat:(NSString *)format, ... NS_FORMAT_FUNCTION(1, 2);

@end
