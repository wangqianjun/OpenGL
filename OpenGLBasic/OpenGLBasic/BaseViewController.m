//
//  ViewController.m
//  OpenGLBasic
//
//  Created by 王钱钧 on 15/4/7.
//  Copyright (c) 2015年 Arthur. All rights reserved.
//

#import "BaseViewController.h"
#import "ASEOpenGLView.h"

@interface BaseViewController ()
{
    ASEOpenGLView *_openglView;
    UIView *_controlView;
    
    UISlider *_posXSlider;
    UISlider *_posYSlider;
    UISlider *_posZSlider;
    
    UISlider *_rotateXSlider;
    UISlider *_scaleZSlider;

}

@end

@implementation BaseViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor whiteColor];
    
    [self initViews];
    // Do any additional setup after loading the view, typically from a nib.
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
}

- (void)initViews
{
    _openglView = [[ASEOpenGLView alloc]initWithFrame:CGRectMake(0, 0, self.view.bounds.size.width, 500)];
    
    
    [self.view addSubview:_openglView];
    [self initControlView];

    [self resetControls];
}



- (void)initControlView
{
    _controlView = [[UIView alloc]initWithFrame:CGRectMake(0, CGRectGetMaxY(_openglView.frame),  self.view.bounds.size.width, CGRectGetHeight(self.view.bounds)-500)];
    [_controlView setBackgroundColor:[UIColor yellowColor]];
    [self.view addSubview:_controlView];
    
    _posXSlider = [[UISlider alloc]initWithFrame:CGRectMake(0, 0, 140, 40)];
    _posXSlider.minimumValue = -3.0f;
    _posXSlider.maximumValue = 3.0f;
    _posXSlider.value = 0;
    [_posXSlider addTarget:self action:@selector(xSliderValueChanged:) forControlEvents:UIControlEventValueChanged];
    [_controlView addSubview:_posXSlider];
    
    _posYSlider = [[UISlider alloc]initWithFrame:CGRectMake(0, CGRectGetMaxY(_posXSlider.frame), 140, 40)];
    _posYSlider.minimumValue = -3.0f;
    _posYSlider.maximumValue = 3.0f; 
    _posYSlider.value = 0;
    [_posYSlider addTarget:self action:@selector(ySliderValueChanged:) forControlEvents:UIControlEventValueChanged];
    [_controlView addSubview:_posYSlider];

    _posZSlider = [[UISlider alloc]initWithFrame:CGRectMake(0, CGRectGetMaxY(_posYSlider.frame), 140, 40)];
    _posZSlider.minimumValue = -10.0f;
    _posZSlider.maximumValue = -1.0f;
    _posZSlider.value = 0;
    [_posZSlider addTarget:self action:@selector(zSliderValueChanged:) forControlEvents:UIControlEventValueChanged];
    [_controlView addSubview:_posZSlider];
    
    UILabel *rotateXLabel = [[UILabel alloc]initWithFrame:CGRectMake(CGRectGetMaxX(_posXSlider.frame), 0, 50, 40)];
    rotateXLabel.text = @"Rotate X";
    rotateXLabel.textAlignment = NSTextAlignmentCenter;
    rotateXLabel.font = [UIFont systemFontOfSize:12];
    [_controlView addSubview:rotateXLabel];
    
    UILabel *scaleZLabel = [[UILabel alloc]initWithFrame:CGRectMake(CGRectGetMaxX(_posYSlider.frame), CGRectGetMinY(_posYSlider.frame), 50, 40)];
    scaleZLabel.text = @"Scale Z";
    scaleZLabel.textAlignment = NSTextAlignmentCenter;
    scaleZLabel.font = [UIFont systemFontOfSize:12];
    [_controlView addSubview:scaleZLabel];

    
    _rotateXSlider = [[UISlider alloc]initWithFrame:CGRectMake(CGRectGetMaxX(rotateXLabel.frame), 0, 140, 40)];
    _rotateXSlider.minimumValue = -180.0f;
    _rotateXSlider.maximumValue = 180.0f;
    _rotateXSlider.value = 0;
    [_rotateXSlider addTarget:self action:@selector(rotateXSliderValueChanged:) forControlEvents:UIControlEventValueChanged];
    [_controlView addSubview:_rotateXSlider];
    
    _scaleZSlider = [[UISlider alloc]initWithFrame:CGRectMake(CGRectGetMaxX(scaleZLabel.frame), CGRectGetMinY(_posYSlider.frame), 140, 40)];
    _scaleZSlider.minimumValue = 0.50f;
    _scaleZSlider.maximumValue = 2.0f;
    _scaleZSlider.value = 0;
    [_scaleZSlider addTarget:self action:@selector(scaleZSliderValueChanged:) forControlEvents:UIControlEventValueChanged];
    [_controlView addSubview:_scaleZSlider];
    
    
    UIButton *autoButton = [[UIButton alloc]initWithFrame:CGRectMake(CGRectGetMaxX(_posZSlider.frame), CGRectGetMaxY(_scaleZSlider.frame), 60, 40)];
    [autoButton setTitle:@"Auto" forState:UIControlStateNormal];
    [autoButton setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
    [autoButton addTarget:self action:@selector(autoClick:) forControlEvents:UIControlEventTouchUpInside];
    [_controlView addSubview:autoButton];
    
    UIButton *resetButton = [[UIButton alloc]initWithFrame:CGRectMake(CGRectGetMaxX(autoButton.frame) + 30, CGRectGetMaxY(_scaleZSlider.frame), 60, 40)];
    [resetButton setTitle:@"Reset" forState:UIControlStateNormal];
    [resetButton setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
    [resetButton addTarget:self action:@selector(resetClick:) forControlEvents:UIControlEventTouchUpInside];
    [_controlView addSubview:resetButton];

}

- (void)xSliderValueChanged:(id)sender
{
    UISlider *slider = (UISlider *)sender;
    float currentValue = [slider value];
    
    _openglView.posX = currentValue;
    
    NSLog(@">> current x is %f", currentValue);
}

- (void)ySliderValueChanged:(id)sender
{
    UISlider *slider = (UISlider *)sender;
    float currentValue = [slider value];
    
    _openglView.posY = currentValue;
    
    NSLog(@">> current y is %f", currentValue);
}

- (void)zSliderValueChanged:(id)sender
{
    UISlider *slider = (UISlider *)sender;
    float currentValue = [slider value];
    
    _openglView.posZ = currentValue;
    
    NSLog(@">> current z is %f", currentValue);
}

- (void)rotateXSliderValueChanged:(id)sender
{
    UISlider *slider = (UISlider *)sender;
    float currentValue = [slider value];
    
    _openglView.rotateX = currentValue;
    
    NSLog(@">> current x rotate is %f", currentValue);
}

- (void)scaleZSliderValueChanged:(id)sender
{
    UISlider *slider = (UISlider *)sender;
    float currentValue = [slider value];
    
    _openglView.scaleZ = currentValue;
    
    NSLog(@">> current z scale is %f", currentValue);
}

- (void)autoClick:(id)sender
{
    [_openglView toggleDisplayLink];
    
    UIButton * button = (UIButton *)sender;
    NSString * text = button.titleLabel.text;
    if ([text isEqualToString:@"Auto"]) {
        [button setTitle: @"Stop" forState: UIControlStateNormal];
    }
    else {
        [button setTitle: @"Auto" forState: UIControlStateNormal];
    }
}

- (void)resetClick:(id)sender
{
    [_openglView resetTransform];
    [_openglView render];
    [self resetControls];
}

- (void)resetControls
{
    
    [_posXSlider setValue:_openglView.posX];
    [_posYSlider setValue:_openglView.posY];
    [_posZSlider setValue:_openglView.posZ];
    
    [_scaleZSlider setValue:_openglView.scaleZ];
    [_rotateXSlider setValue:_openglView.rotateX];
}
//
- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
