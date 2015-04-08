//
//  ViewController.m
//  OpenGLBasic
//
//  Created by 王钱钧 on 15/4/7.
//  Copyright (c) 2015年 Arthur. All rights reserved.
//

#import "ViewController.h"
#import "ASEOpenGLView.h"

@interface ViewController ()
{
    ASEOpenGLView *_openglView;
    UIView *_controlView;
}

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor whiteColor];
    
    [self initViews];
    // Do any additional setup after loading the view, typically from a nib.
}

- (void)initViews
{
    _openglView = [[ASEOpenGLView alloc]initWithFrame:CGRectMake(0, 0, self.view.bounds.size.width, 500)];
    [self.view addSubview:_openglView];
    
    _controlView = [[UIView alloc]initWithFrame:CGRectMake(0, CGRectGetMaxY(_openglView.frame),  self.view.bounds.size.width, CGRectGetHeight(self.view.bounds)-500)];
    [_controlView setBackgroundColor:[UIColor yellowColor]];
    [self.view addSubview:_controlView];
    
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
