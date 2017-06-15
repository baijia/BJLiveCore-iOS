//
//  BJTableViewController.m
//  BJLiveUI
//
//  Created by MingLQ on 2017-02-13.
//  Copyright © 2017 Baijia Cloud. All rights reserved.
//

#import "BJTableViewController.h"

NS_ASSUME_NONNULL_BEGIN

@interface BJTableViewController ()

@property (nonatomic, readwrite) UITableView *tableView;

@end

@implementation BJTableViewController

- (instancetype)init {
    return [self initWithStyle:UITableViewStylePlain];
}

- (instancetype)initWithStyle:(UITableViewStyle)style {
    self = [super initWithNibName:nil bundle:nil];
    if (self) {
        self->_tableViewStyle = style;
        self.clearsSelectionOnViewWillAppear = YES;
    }
    return self;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    [self tableView];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    if (self.clearsSelectionOnViewWillAppear) {
        NSArray *indexPaths = [self.tableView indexPathsForSelectedRows];
        for (NSIndexPath *indexPath in indexPaths) {
            [self.tableView deselectRowAtIndexPath:indexPath animated:animated];
        }
    }
}

/*
- (void)didMoveToParentViewController:(nullable UIViewController *)parent {
    [super didMoveToParentViewController:parent];
    
    if (self.navigationController.interactivePopGestureRecognizer) {
        [_tableView.panGestureRecognizer requireGestureRecognizerToFail:
         self.navigationController.interactivePopGestureRecognizer];
    }
} // */

- (void)dealloc {
    _tableView.dataSource = nil;
    _tableView.delegate = nil;
}

#pragma mark -

@synthesize tableView = _tableView;
- (UITableView *)tableView {
    if (![self isViewLoaded]) {
        [self view];
    }
    if (_tableView) {
        return _tableView;
    }
    
    UITableView *tableView = [[UITableView alloc] initWithFrame:self.view.bounds style:self.tableViewStyle];
    if ([tableView respondsToSelector:@selector(setCellLayoutMarginsFollowReadableWidth:)]) {
        tableView.cellLayoutMarginsFollowReadableWidth = NO;
    }
    if ([self conformsToProtocol:@protocol(UITableViewDataSource)]) {
        tableView.dataSource = (id<UITableViewDataSource>)self;
    }
    if ([self conformsToProtocol:@protocol(UITableViewDelegate)]) {
        tableView.delegate = (id<UITableViewDelegate>)self;
    }
    
    [self.view addSubview:tableView];
    tableView.translatesAutoresizingMaskIntoConstraints = NO;
    [self.view
     addConstraints:@[[NSLayoutConstraint
                       constraintWithItem:tableView
                       attribute:NSLayoutAttributeLeft
                       relatedBy:NSLayoutRelationEqual
                       toItem:self.view
                       attribute:NSLayoutAttributeLeft
                       multiplier:1.0
                       constant:0.0],
                      [NSLayoutConstraint
                       constraintWithItem:tableView
                       attribute:NSLayoutAttributeTop
                       relatedBy:NSLayoutRelationEqual
                       toItem:self.view
                       attribute:NSLayoutAttributeTop
                       multiplier:1.0
                       constant:0.0],
                      [NSLayoutConstraint
                       constraintWithItem:tableView
                       attribute:NSLayoutAttributeWidth
                       relatedBy:NSLayoutRelationEqual
                       toItem:self.view
                       attribute:NSLayoutAttributeWidth
                       multiplier:1.0
                       constant:0.0],
                      [NSLayoutConstraint
                       constraintWithItem:tableView
                       attribute:NSLayoutAttributeHeight
                       relatedBy:NSLayoutRelationEqual
                       toItem:self.view
                       attribute:NSLayoutAttributeHeight
                       multiplier:1.0
                       constant:0.0]]];
    
    self.tableView = tableView;
    return _tableView;
}

- (void)setRefreshControl:(nullable UIRefreshControl *)refreshControl {
    NSString *key = NSStringFromSelector(@selector(refreshControl));
    [self willChangeValueForKey:key];
    if (self.refreshControl) {
        [self.refreshControl removeFromSuperview];
    }
    self->_refreshControl = refreshControl;
    if (refreshControl) {
        [self.tableView insertSubview:refreshControl atIndex:0];
    }
    [self didChangeValueForKey:key];
}

#pragma mark - <UITableViewDelegate>

- (CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section {
    return CGFLOAT_MIN;
}

- (CGFloat)tableView:(UITableView *)tableView heightForFooterInSection:(NSInteger)section {
    return CGFLOAT_MIN;
}

@end

NS_ASSUME_NONNULL_END
