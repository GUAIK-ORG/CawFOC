# 🦉 CAW-FOC

## 🎮 项目地址

Github: https://github.com/GUAIK-ORG/CAWFoc

Gitee: https://gitee.com/GuaikOrg/cawfoc

## 📜 项目介绍

CAW FOC 项目由 3 部分组成，在 CAW-PACKAGES/ControlSystem/FOC 目录下存放相关的代码。

- foc.h/foc.c：foc 相关的主要算法
- foc_hal.h/foc_hal.c：用于配置编码器
- foc_test.h/foc_test.c：测试程序

## 🎥 效果展示

https://www.bilibili.com/video/BV1Hh4y1M7nH/

https://www.bilibili.com/video/BV1BP411v7nA/

## ⏰ TODO

| 功能         | 状态 |
| ------------ | ---- |
| 开环速度控制 | ✔    |
| 闭环力矩控制 | ✔    |
| 闭环位置控制 | ✔    |
| 闭环速度控制 | ✔    |

## 👨‍💻 使用示例

一下代码可以在`freertos.c`中看到

```c
FOC_T foc1;
FOC_Closeloop_Init(&foc1, &htim1, PWM_PERIOD, 12.0, 1, 7);
FOC_SetVoltageLimit(&foc1, 10.0);
FOC_HAL_Init(&foc1, &hi2c1);
FOC_AlignmentSensor(&foc1);

while (1) {
    Foc_TestCloseloopAngle(&foc1, 0);
    FOC_SensorUpdate();
}
```

## 📚 参考资料

Park 变换：https://zhuanlan.zhihu.com/p/614244367

Clark 变换：https://zhuanlan.zhihu.com/p/613996592

DengFoc：http://dengfoc.com/#/

SimpleFOC 中文：http://simplefoc.cn/#/
