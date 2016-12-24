//
//  BJLoginView.m
//  LivePlayerApp
//
//  Created by MingLQ on 2016-07-01.
//  Copyright © 2016年 Baijiahulian. All rights reserved.
//

#import <Masonry/Masonry.h>
// #import <NBKit/NBKit.h>
#import <ReactiveCocoa/ReactiveCocoa.h>

#import "BJLoginView.h"

#import "BJAppearance.h"

static CGFloat const margin = 10.0/* , textLeftMargin = 5.0 */;

@interface BJLoginView ()

@property (nonatomic) UIImageView *backgroundView;

@property (nonatomic) UIImageView *appLogoView, *logoView;

@property (nonatomic) UIView *inputContainerView, *inputSeparatorLine;

// code
@property (nonatomic, readwrite) UITextField *codeTextField, *nameTextField;

// both
@property (nonatomic, readwrite) UIButton *doneButton;

@end

@implementation BJLoginView

- (instancetype)init {
    self = [super initWithFrame:CGRectZero];
    if (self) {
        [self makeSubviews];
        [self makeConstraints];
    }
    return self;
}

- (void)makeSubviews {
    self.backgroundView = ({
        UIImageView *imageView = [UIImageView new];
        imageView.contentMode = UIViewContentModeScaleAspectFill;
        imageView.image = [UIImage imageNamed:@"login-bg"];
        imageView;
    });
    [self addSubview:self.backgroundView];
    
    self.appLogoView = ({
        UIImageView *imageView = [UIImageView new];
        imageView.image = [UIImage imageNamed:@"login-logo-app"];
        imageView;
    });
    [self addSubview:self.appLogoView];
    
    self.logoView = ({
        UIImageView *imageView = [UIImageView new];
        imageView.image = [UIImage imageNamed:@"login-logo"];
        imageView;
    });
    [self addSubview:self.logoView];
    
    self.inputContainerView = ({
        UIView *view = [UIView new];
        view.backgroundColor = [UIColor colorWithWhite:1.0 alpha:0.3];
        view.layer.cornerRadius = 3.0;
        view.layer.masksToBounds = YES;
        view;
    });
    [self addSubview:self.inputContainerView];
    
    self.inputSeparatorLine = ({
        UIView *view = [UIView new];
        view.backgroundColor = [UIColor colorWithWhite:1.0 alpha:0.5];
        view;
    });
    [self.inputContainerView addSubview:self.inputSeparatorLine];
    
    self.codeTextField = [self textFieldWithIcon:[UIImage imageNamed:@"login-icon-code"]
                                     placeholder:@"请输入参加码"];
    self.codeTextField.returnKeyType = UIReturnKeyNext;
    [self.inputContainerView addSubview:self.codeTextField];
    
    self.nameTextField = [self textFieldWithIcon:[UIImage imageNamed:@"login-icon-name"]
                                     placeholder:@"请输入昵称"];
    self.nameTextField.returnKeyType = UIReturnKeyDone;
    [self.inputContainerView addSubview:self.nameTextField];
    
    self.doneButton = ({
        UIButton *button = [UIButton new];
        button.backgroundColor = [UIColor bj_brandColor];
        button.layer.cornerRadius = 2.0;
        button.layer.masksToBounds = YES;
        button.titleLabel.font = [UIFont systemFontOfSize:16.0];
        [button setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
        [button setTitleColor:[UIColor colorWithWhite:1.0 alpha:0.5] forState:UIControlStateDisabled];
        [button setTitle:@"登录" forState:UIControlStateNormal];
        button;
    });
    [self addSubview:self.doneButton];
}

- (void)makeConstraints {
    [self.backgroundView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(self);
    }];
    
    [self.inputContainerView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerX.equalTo(self);
        make.bottom.equalTo(self.mas_centerY).offset(- 32.0);
        make.left.right.equalTo(self).insets(UIEdgeInsetsMake(0.0, 15.0, 0.0, 15.0));
        make.height.equalTo(@100.0);
    }];
    
    [self.inputSeparatorLine mas_makeConstraints:^(MASConstraintMaker *make) {
        make.center.equalTo(self.inputContainerView);
        make.left.right.equalTo(self.inputContainerView).with.insets(UIEdgeInsetsMake(0.0, margin, 0.0, margin));
        make.height.equalTo(@(BJOnePixel));
    }];
    
    [self.codeTextField mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.left.right.equalTo(self.inputContainerView).with.insets(UIEdgeInsetsMake(0.0, 12.0, 0.0, 12.0));
    }];
    
    [self.nameTextField mas_makeConstraints:^(MASConstraintMaker *make) {
        make.bottom.left.right.equalTo(self.inputContainerView).with.insets(UIEdgeInsetsMake(0.0, 12.0, 0.0, 12.0));
        make.top.equalTo(self.codeTextField.mas_bottom);
        make.height.equalTo(self.codeTextField);
    }];
    
    [self.appLogoView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerX.equalTo(self);
        make.bottom.equalTo(self.inputContainerView.mas_top).with.offset(- 32.0);
    }];
    
    [self.logoView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerX.equalTo(self);
        make.bottom.equalTo(self).with.offset(- 40.0);
    }];
    
    [self.doneButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerX.equalTo(self);
        make.top.equalTo(self.inputContainerView.mas_bottom).with.offset(32.0);
        make.width.equalTo(self.inputContainerView);
        make.height.equalTo(@50.0);
    }];
}

- (UITextField *)textFieldWithIcon:(UIImage *)icon placeholder:(NSString *)placeholder {
    CGFloat fontSize = 14.0;
    
    // NBTextField *textField = [NBTextField new];
    // textField.textInsets = textField.editingInsets = UIEdgeInsetsMake(0.0, textLeftMargin, 0.0, 0.0);
    UITextField *textField = [UITextField new];
    textField.font = [UIFont systemFontOfSize:fontSize];
    textField.textColor = [UIColor whiteColor];
    textField.clearButtonMode = UITextFieldViewModeWhileEditing;
    textField.attributedPlaceholder = [[NSAttributedString alloc]
                                       initWithString:placeholder
                                       attributes:@{ NSFontAttributeName:
                                                         [UIFont systemFontOfSize:fontSize],
                                                     NSForegroundColorAttributeName:
                                                         [UIColor colorWithWhite:1.0 alpha:0.69] }];
    
    UIButton *button = [UIButton new];
    [button setImage:icon forState:UIControlStateNormal];
    textField.leftView = button;
    textField.leftViewMode = UITextFieldViewModeAlways;
    
    [button mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(27.0, 27.0));
    }];
    
    @weakify(/* self, */ textField);
    [[button rac_signalForControlEvents:UIControlEventTouchUpInside]
     subscribeNext:^(id x) {
         @strongify(/* self, */ textField);
         [textField becomeFirstResponder];
     }];
    
    return textField;
}

@end
