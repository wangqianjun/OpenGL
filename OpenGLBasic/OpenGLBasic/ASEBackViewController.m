//
//  ASEBackViewController.m
//  OpenGLBasic
//
//  Created by 王钱钧 on 15/4/9.
//  Copyright (c) 2015年 Arthur. All rights reserved.
//

#import "ASEBackViewController.h"

@implementation ASEBackViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    self.backButton = [[UIButton alloc]initWithFrame:CGRectMake(0, 30, 80, 40)];
    [self.backButton setTitle:@"< Back" forState:UIControlStateNormal];
    [self.backButton setTitleColor:[UIColor blueColor] forState:UIControlStateNormal];
    [self.backButton setTitleColor:[UIColor grayColor] forState:UIControlStateSelected];
    [self.backButton addTarget:self action:@selector(back:) forControlEvents:UIControlEventTouchUpInside];
    
//    self.backButton.layer.zPosition = 100;
    [self.view addSubview:self.backButton];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    [self.view bringSubviewToFront:self.backButton];
}

- (void)back:(id)sender
{
    [self dismissViewControllerAnimated:YES completion:nil];
}

@end
