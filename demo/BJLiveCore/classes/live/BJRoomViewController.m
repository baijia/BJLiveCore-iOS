//
//  BJRoomViewController.m
//  BJLiveCore
//
//  Created by MingLQ on 2016-12-18.
//  Copyright © 2016 GSX. All rights reserved.
//

#import <M9Dev/M9Dev.h>
#import <Masonry/Masonry.h>

#import "BJRoomViewController.h"
#import "BJRoomViewController+media.h"
#import "BJRoomViewController+users.h"

#import "BJAppearance.h"
#import "BJAppConfig.h"

static CGFloat const margin = 10.0;

@interface BJRoomViewController ()

@property (nonatomic) UIView *topBarGroupView;
@property (nonatomic) UIButton *backButton, *doneButton;
@property (nonatomic) UITextField *textField;

@property (nonatomic) UIView *dashboardGroupView;

@end

@implementation BJRoomViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.view.backgroundColor = [UIColor bj_grayBackgroundColor];
    
    [self makeTopBar];
    [self makeDashboard];
    [self makeConsole];
    
    [self makeEvents];
}

- (void)enterRoomWithSecret:(NSString *)roomSecret
                   userName:(NSString *)userName {
    self.room = [BJLRoom roomWithSecret:roomSecret
                               userName:userName
                             userAvatar:nil];
    
    weakdef(self);
    
    [self bjl_observe:self.room
                event:@selector(roomDidEnter)
           usingBlock:^(id data/* , id object, BJLOEventType event */) {
               strongdef(self);
               if (self.room.roomVM.loginUser.isTeacher) {
                   [self.room.roomVM sendLiveStarted:YES]; // 上课
               }
               [self didEnterRoom];
           }];
    
    [self bjl_observe:self.room
                event:@selector(roomWillExitWithError:)
           usingBlock:^(BJLError *error/* , id object, BJLOEventType event */) {
               strongdef(self);
               if (self.room.roomVM.loginUser.isTeacher) {
                   [self.room.roomVM sendLiveStarted:NO]; // 下课
               }
           }];
    
    [self bjl_observe:self.room
                event:@selector(roomDidExitWithError:)
           usingBlock:^(BJLError *error/* , id object, BJLOEventType event */) {
               strongdef(self);
               
               if (error.code == BJLErrorCode_exitRoom_exitRoom) {
                   [self goBack];
                   return;
               }
               
               NSString *message = error ? [NSString stringWithFormat:@"%@ - %@",
                                            error.localizedDescription,
                                            error.localizedFailureReason] : @"错误";
               UIAlertController *alert = [UIAlertController
                                           alertControllerWithTitle:@"错误"
                                           message:message
                                           preferredStyle:UIAlertControllerStyleAlert];
               [alert addAction:[UIAlertAction
                                 actionWithTitle:@"退出"
                                 style:UIAlertActionStyleDestructive
                                 handler:^(UIAlertAction * _Nonnull action) {
                                     [self goBack];
                                 }]];
               [alert addAction:[UIAlertAction
                                 actionWithTitle:@"知道了"
                                 style:UIAlertActionStyleCancel
                                 handler:nil]];
               [self presentViewController:alert animated:YES completion:nil];
           }];
    
    [self makeLoadingEvents];
    
    [self.room enter];
}

#pragma mark - subviews

- (void)makeTopBar {
    self.topBarGroupView = ({
        UIView *view = [UIView new];
        view.clipsToBounds = YES;
        view;
    });
    [self.view addSubview:self.topBarGroupView];
    [self.topBarGroupView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.right.equalTo(self.view);
        make.top.equalTo(self.mas_topLayoutGuide).offset(margin);
        make.height.equalTo(@32);
    }];
    
    UIImage *backImage = [UIImage imageNamed:@"back-dark"];
    self.backButton = ({
        UIButton *button = [[UIButton alloc] initWithFrame:CGRectMake(0, 0, backImage.size.width, backImage.size.height)];
        button.tintColor = [UIBarButtonItem appearanceWhenContainedIn:[UINavigationBar class], nil].tintColor;
        [button setImage:backImage forState:UIControlStateNormal];
        button;
    });
    [self.topBarGroupView addSubview:self.backButton];
    
    self.textField = ({
        UITextField *textField = [UITextField new];
        textField.backgroundColor = [UIColor whiteColor];
        textField.layer.cornerRadius = 2.0;
        textField.layer.masksToBounds = YES;
        textField.returnKeyType = UIReturnKeySend;
        textField.delegate = self;
        textField;
    });
    [self.topBarGroupView addSubview:self.textField];
    
    self.doneButton = ({
        UIButton *button = [UIButton new];
        button.backgroundColor = [UIColor bj_brandColor];
        button.layer.cornerRadius = 2.0;
        button.layer.masksToBounds = YES;
        button.titleLabel.font = [UIFont systemFontOfSize:16.0];
        [button setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
        [button setTitleColor:[UIColor colorWithWhite:1.0 alpha:0.5] forState:UIControlStateDisabled];
        [button setTitle:@"发送" forState:UIControlStateNormal];
        button;
    });
    [self.topBarGroupView addSubview:self.doneButton];
    
    [self.backButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.equalTo(self.topBarGroupView).offset(margin);
        make.top.bottom.equalTo(self.topBarGroupView);
        make.width.equalTo(self.backButton.mas_height);
    }];
    
    [self.doneButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.right.equalTo(self.topBarGroupView).offset(- margin);
        make.width.equalTo(@64);
        make.top.bottom.equalTo(self.topBarGroupView);
    }];
    
    [self.textField mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.equalTo(self.backButton.mas_right).offset(margin);
        make.right.equalTo(self.doneButton.mas_left).offset(- margin);
        make.top.bottom.equalTo(self.topBarGroupView);
    }];
}

- (void)makeDashboard {
    self.dashboardGroupView = ({
        UIView *view = [UIView new];
        view.clipsToBounds = YES;
        view;
    });
    [self.view addSubview:self.dashboardGroupView];
    [self.dashboardGroupView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.right.equalTo(self.view);
        make.top.equalTo(self.topBarGroupView.mas_bottom).offset(margin);
    }];
    
    self.recordingView = ({
        UIButton *button = [UIButton new];
        button.clipsToBounds = YES;
        button;
    });
    [self.recordingView setTitle:@"采集" forState:UIControlStateNormal];
    self.recordingView.backgroundColor = [[UIColor redColor] colorWithAlphaComponent:0.2];
    [self.view addSubview:self.recordingView];
    [self.recordingView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.top.bottom.equalTo(self.dashboardGroupView);
        make.height.equalTo(self.recordingView.mas_width).multipliedBy(4.0 / 3.0);
    }];
    
    self.playingView = ({
        UIButton *button = [UIButton new];
        button.clipsToBounds = YES;
        button;
    });
    [self.playingView setTitle:@"播放" forState:UIControlStateNormal];
    self.playingView.backgroundColor = [[UIColor greenColor] colorWithAlphaComponent:0.2];
    [self.view addSubview:self.playingView];
    [self.playingView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.bottom.equalTo(self.dashboardGroupView);
        make.left.equalTo(self.recordingView.mas_right);
        make.width.equalTo(self.recordingView);
        make.height.equalTo(self.playingView.mas_width).multipliedBy(4.0 / 3.0);
    }];
    
    self.slideshowAndWhiteboardView = ({
        UIView *view = [UIView new];
        view.clipsToBounds = YES;
        UILabel *label = [UILabel new];
        label.text = @"白板";
        label.textColor = [UIColor whiteColor];
        label.textAlignment = NSTextAlignmentCenter;
        [view addSubview:label];
        [label mas_makeConstraints:^(MASConstraintMaker *make) {
            make.edges.equalTo(view);
        }];
        view;
    });
    self.slideshowAndWhiteboardView.backgroundColor = [[UIColor blueColor] colorWithAlphaComponent:0.2];
    [self.view addSubview:self.slideshowAndWhiteboardView];
    [self.slideshowAndWhiteboardView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.right.bottom.equalTo(self.dashboardGroupView);
        make.left.equalTo(self.playingView.mas_right);
        make.height.equalTo(self.slideshowAndWhiteboardView.mas_width).multipliedBy(3.0 / 4.0);
    }];
}

- (void)makeConsole {
    self.console = [BJConsoleViewController new];
    [self addChildViewController:self.console superview:self.view];
    [self.console.view mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(self.dashboardGroupView.mas_bottom);
        make.left.right.bottom.equalTo(self.view);
    }];
}

#pragma mark - VM

- (void)didEnterRoom {
    [self.console printFormat:@"roomInfo ID: %@, title: %@",
     self.room.roomVM.roomInfo.ID,
     self.room.roomVM.roomInfo.title];
    
    [self.console printFormat:@"loginUser ID: %@, number: %@, name: %@",
     self.room.roomVM.loginUser.ID,
     self.room.roomVM.loginUser.number,
     self.room.roomVM.loginUser.name];
    
    // if (!self.room.roomVM.loginUser.isTeacher) {
    weakdef(self);
    [self bjl_KVObserve:self.room.roomVM
                 getter:@selector(liveStarted)
                 filter:^BOOL(NSNumber *old, NSNumber *now) {
                     // strongdef(self);
                     return old.integerValue != now.integerValue;
                 }
             usingBlock:^(id old, id now) {
                 strongdef(self);
                 [self.console printFormat:@"liveStarted: %@", NSStringFromBOOL(self.room.roomVM.liveStarted)];
             }];
    // }
    
    [self makeUserEvents];
    [self makeMediaEvents];
    [self makeChatEvents];
}

- (void)makeLoadingEvents {
    weakdef(self);
    
    [self bjl_KVObserve:self.room
                 getter:@selector(loadingVM)
                 filter:^BOOL(id old, id now) {
                     // strongdef(self);
                     return !!now;
                 }
             usingBlock:^(id old, id now) {
                 strongdef(self);
                 
                 self.room.loadingVM.suspendBlock = ^(BJLLoadingStep step,
                                                      BJLLoadingSuspendReason reason,
                                                      BJLError *error,
                                                      BOOL ignorable,
                                                      BJLLoadingSuspendCallback suspendCallback) {
                     strongdef(self);
                     
                     if (reason == BJLLoadingSuspendReason_stepOver) {
                         [self.console printFormat:@"loading step over: %td", step];
                         suspendCallback(YES);
                         return;
                     }
                     [self.console printFormat:@"loading step suspend: %td", step];
                     
                     NSString *message = nil;
                     if (reason == BJLLoadingSuspendReason_askForWWANNetwork) {
                         message = @"WWAN 网络";
                     }
                     else if (reason == BJLLoadingSuspendReason_errorOccurred) {
                         message = error ? [NSString stringWithFormat:@"%@ - %@",
                                            error.localizedDescription,
                                            error.localizedFailureReason] : @"错误";
                     }
                     if (message) {
                         UIAlertController *alert = [UIAlertController
                                                     alertControllerWithTitle:ignorable ? @"提示" : @"错误"
                                                     message:message
                                                     preferredStyle:UIAlertControllerStyleAlert];
                         [alert addAction:[UIAlertAction
                                           actionWithTitle:ignorable ? @"继续" : @"重试"
                                           style:UIAlertActionStyleDefault
                                           handler:^(UIAlertAction * _Nonnull action) {
                                               suspendCallback(YES);
                                           }]];
                         [alert addAction:[UIAlertAction
                                           actionWithTitle:@"取消"
                                           style:UIAlertActionStyleCancel
                                           handler:^(UIAlertAction * _Nonnull action) {
                                               suspendCallback(NO);
                                           }]];
                         [self presentViewController:alert animated:YES completion:nil];
                     }
                 };
                 
                 [self bjl_observe:self.room.loadingVM
                             event:@selector(loadingDidUpdateProgress:)
                        usingBlock:^(NSNumber *progress/* , id object, BJLOEventType event */) {
                            strongdef(self);
                            [self.console printFormat:@"loading progress: %f", progress.doubleValue];
                        }];
                 
                 [self bjl_observe:self.room.loadingVM
                             event:@selector(loadingDidSuccess)
                        usingBlock:^(id data/* , id object, BJLOEventType event */) {
                            strongdef(self);
                            [self.console printLine:@"loading success"];
                        }];
                 
                 [self bjl_observe:self.room.loadingVM
                             event:@selector(loadingDidFailureWithError:)
                        usingBlock:^(BJLError *error/* , id object, BJLOEventType event */) {
                            strongdef(self);
                            [self.console printLine:@"loading failure"];
                        }];
             }];
}

- (void)makeChatEvents {
    weakdef(self);
    
    [self bjl_observe:self.room.chatVM
                event:@selector(didReceiveMessage:)
           usingBlock:^(NSObject<BJLMessage> *message/* , id object, BJLOEventType event */) {
               strongdef(self);
               [self.console printFormat:@"chat %@: %@", message.fromUser.name, message.content];
           }];
}

#pragma mark - events

- (void)makeEvents {
    weakdef(self);
    
    [[self.backButton rac_signalForControlEvents:UIControlEventTouchUpInside]
     subscribeNext:^(id x) {
         strongdef(self);
         [self goBack];
     }];
    
    [[self.doneButton rac_signalForControlEvents:UIControlEventTouchUpInside]
     subscribeNext:^(id x) {
         strongdef(self);
         [self sendMessage];
     }];
}

- (void)goBack {
    [self.room exit];
    [self dismissViewControllerAnimated:YES completion:^{
        self.room = nil;
    }];
}

- (void)sendMessage {
    [self.view endEditing:YES];
    [self.room.chatVM sendMessage:self.textField.text];
    self.textField.text = nil;
}

#pragma mark - <UITextFieldDelegate>

- (BOOL)textFieldShouldReturn:(UITextField *)textField {
    [self sendMessage];
    return NO;
}

@end