//
//  BJConsoleViewController.m
//  BJLiveCore
//
//  Created by MingLQ on 2016-12-13.
//
//

#import "BJConsoleViewController.h"

static NSString * const BJConsoleDefaultIdentifier = @"default";

@interface BJConsoleViewController ()

@property (nonatomic) NSMutableArray<NSString *> *lines;

@end

@implementation BJConsoleViewController

- (instancetype)initWithStyle:(UITableViewStyle)style {
    self = [super initWithStyle:UITableViewStyleGrouped];
    if (self) {
        self.lines = [NSMutableArray new];
    }
    return self;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor colorWithWhite:0.0 alpha:0.7];
    
    [self setupTableView];
}

- (void)printLine:(NSString *)line {
    [self.lines addObjectOrNil:line];
    
    while (self.lines.count > 1000) {
        [self.lines removeObjectAtIndex:0];
    }
    
    BOOL atTheBottom = [self atTheBottomOfTableView];
    [self.tableView reloadData];
    if (atTheBottom) {
        [self scrollToTheEndOfTableView];
    }
}

- (void)printFormat:(NSString *)format, ... {
    va_list args;
    va_start(args, format);
    NSString *line = [[NSString alloc] initWithFormat:format arguments:args];
    va_end(args);
    [self printLine:line];
}

- (void)setupTableView {
    self.tableView.delegate = self;
    self.tableView.dataSource = self;
    
    self.tableView.backgroundColor = [UIColor clearColor];
    self.tableView.separatorStyle = UITableViewCellSeparatorStyleNone;
    self.tableView.indicatorStyle = UIScrollViewIndicatorStyleBlack;
    
    self.tableView.allowsSelection = NO;
    
    [self.tableView registerClass:[UITableViewCell class]
           forCellReuseIdentifier:BJConsoleDefaultIdentifier];
    
    self.tableView.rowHeight = UITableViewAutomaticDimension;
    self.tableView.estimatedRowHeight = 44.0;
}

- (CGFloat)atTheBottomOfTableView {
    CGFloat contentOffsetY = self.tableView.contentOffset.y;
    CGFloat bottom = self.tableView.contentInset.bottom;
    CGFloat viewHeight = CGRectGetHeight(self.tableView.frame);
    CGFloat contentHeight = self.tableView.contentSize.height;
    CGFloat bottomOffset = contentOffsetY + viewHeight - bottom - contentHeight;
    CGFloat margin = 10;
    return bottomOffset >= 0 - margin;
}

- (void)scrollToTheEndOfTableView {
    [self.view setNeedsLayout];
    [self.view layoutIfNeeded];
    
    if (!self.lines.count) {
        return;
    }
    NSIndexPath *indexPath = [NSIndexPath indexPathForRow:self.lines.count - 1
                                                inSection:0];
    [self.tableView scrollToRowAtIndexPath:indexPath
                          atScrollPosition:UITableViewScrollPositionBottom
                                  animated:NO];
}

#pragma mark - <UITableViewDataSource>

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.lines.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:BJConsoleDefaultIdentifier
                                                            forIndexPath:indexPath];
    cell.backgroundColor = [UIColor clearColor];
    cell.textLabel.textColor = [UIColor greenColor];
    cell.textLabel.numberOfLines = 0;
    cell.textLabel.text = [self.lines objectOrNilAtIndex:indexPath.row];
    return cell;
}

#pragma mark - <UITableViewDelegate>

- (CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section {
    return DBL_EPSILON;
}

- (CGFloat)tableView:(UITableView *)tableView heightForFooterInSection:(NSInteger)section {
    return DBL_EPSILON;
}

@end
