//
//  BJLoginViewController.m
//  LivePlayerApp
//
//  Created by MingLQ on 2016-07-01.
//  Copyright © 2016年 BaijiaYun. All rights reserved.
//

#import "BJLoginViewController.h"
#import "BJLoginView.h"

#import "BJViewControllerImports.h"

#import "BJRoomViewController.h"

// #import "BJLivePlayerAgent.h"

static NSString * const BJLoginCodeKey = @"BJLoginCode";
static NSString * const BJLoginNameKey = @"BJLoginName";

@interface BJLoginViewController () <UITextFieldDelegate>

@property (nonatomic) BJLoginView *codeLoginView;

@end

@implementation BJLoginViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor whiteColor];
    
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
    
    self.codeLoginView = [self createLoginView];
    
    [self setCode:[userDefaults stringForKey:BJLoginCodeKey]
             name:[userDefaults stringForKey:BJLoginNameKey]];
    
    [self makeSignals];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    [self.navigationController setNavigationBarHidden:YES animated:animated];
}

- (void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];
    [self.navigationController setNavigationBarHidden:NO animated:animated];
}

- (BOOL)shouldAutorotate {
    return ([UIApplication sharedApplication].statusBarOrientation
            != UIInterfaceOrientationPortrait);
}

- (UIInterfaceOrientationMask)supportedInterfaceOrientations {
    return UIInterfaceOrientationMaskPortrait;
}

#pragma mark - subview

- (BJLoginView *)createLoginView {
    BJLoginView *loginView = [BJLoginView new];
    [self.view addSubview:loginView];
    [loginView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(self.view);
    }];
    return loginView;
}

- (void)makeSignals {
    @weakify(self);
    
    // endEditing
    UITapGestureRecognizer *tapGesture = [UITapGestureRecognizer new];
    [self.view addGestureRecognizer:tapGesture];
    UIPanGestureRecognizer *panGesture = [UIPanGestureRecognizer new];
    [self.view addGestureRecognizer:panGesture];
    [[RACSignal merge:@[ tapGesture.rac_gestureSignal,
                         panGesture.rac_gestureSignal ]]
     subscribeNext:^(UIGestureRecognizer *gesture) {
         @strongify(self);
         [self.view endEditing:YES];
     }];
    
    // clear cache if changed
    [[[self.codeLoginView.codeTextField.rac_textSignal
       distinctUntilChanged]
      skip:1]
     subscribeNext:^(NSString *codeText) {
         // @strongify(self);
         NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
         [userDefaults removeObjectForKey:BJLoginCodeKey];
         [userDefaults synchronize];
     }];
    [[[self.codeLoginView.nameTextField.rac_textSignal
       distinctUntilChanged]
      skip:1]
     subscribeNext:^(NSString *nameText) {
         // @strongify(self);
         NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
         [userDefaults removeObjectForKey:BJLoginNameKey];
         [userDefaults synchronize];
     }];
    
    // delegate
    self.codeLoginView.codeTextField.delegate = self;
    self.codeLoginView.nameTextField.delegate = self;
    
    // doneButton.enabled
    [[RACSignal
      combineLatest:@[ [RACSignal merge:@[ self.codeLoginView.codeTextField.rac_textSignal,
                                           RACObserve(self.codeLoginView.codeTextField, text) ]],
                       [RACSignal merge:@[ self.codeLoginView.nameTextField.rac_textSignal,
                                           RACObserve(self.codeLoginView.nameTextField, text) ]] ]
      reduce:^id(NSString *codeText, NSString *nameText) {
          // @strongify(self);
          return @(codeText.length && nameText.length);
      }]
     subscribeNext:^(NSNumber *enabled) {
         @strongify(self);
         self.codeLoginView.doneButton.enabled = enabled.boolValue;
     }];
    
    // login
    [[self.codeLoginView.doneButton rac_signalForControlEvents:UIControlEventTouchUpInside]
     subscribeNext:^(UIButton *button) {
         @strongify(self);
         [self doneWithButton:button];
     }];
}

#pragma mark - events

- (void)doneWithButton:(UIButton *)button {
    [self.view endEditing:YES];
    
    [self enterRoomWithJoinCode:self.codeLoginView.codeTextField.text
                       userName:self.codeLoginView.nameTextField.text];
}

#pragma mark - actions

- (void)enterRoomWithJoinCode:(NSString *)joinCode userName:(NSString *)userName {
    [self storeCodeAndName];
    
    BJRoomViewController *roomViewController = [BJRoomViewController new];
    [self presentViewController:roomViewController
                       animated:YES
                     completion:^{
                         [roomViewController enterRoomWithSecret:joinCode userName:userName];
                     }];
}

#pragma mark - state

- (void)setCode:(NSString *)code name:(NSString *)name {
    BJLoginView *loginView = self.codeLoginView;
    loginView.codeTextField.text = code;
    loginView.nameTextField.text = name;
    loginView.doneButton.enabled = code.length && name.length;
}

- (void)storeCodeAndName {
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
    [userDefaults setObject:self.codeLoginView.codeTextField.text
                     forKey:BJLoginCodeKey];
    [userDefaults setObject:self.codeLoginView.nameTextField.text
                     forKey:BJLoginNameKey];
    [userDefaults synchronize];
}

#pragma mark - <UITextFieldDelegate>

- (BOOL)textFieldShouldReturn:(UITextField *)textField {
    if (textField == self.codeLoginView.codeTextField) {
        [self.codeLoginView.nameTextField becomeFirstResponder];
    }
    else if (textField == self.codeLoginView.nameTextField) {
        if (self.codeLoginView.doneButton.enabled) {
            [self doneWithButton:self.codeLoginView.doneButton];
        }
    }
    return NO;
}

@end
