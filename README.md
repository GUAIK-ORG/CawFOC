# 🦉 CAW-FOC

## 🎮 项目地址

Github: https://github.com/GUAIK-ORG/CawFOC

Gitee: https://gitee.com/GuaikOrg/CawFOC

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

## 🎮 配置 & 编译项目

### 安装 arm-none-eabi-gcc

**Windows**

- 下载 arm-none-eabi-gcc

  https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads

- 设置环境变量

  将`gcc-arm-none-eabi\bin`的绝对路径添加进系统变量的 Path 中

**Mac**

```bash
brew tap ArmMbed/homebrew-formulae
brew install arm-none-eabi-gcc
```

### 编译

切换到项目根目录然后运行: `mingw32-make`，即可在项目根目录中的 build 目录中找到编译生成的文件[CawFOC.elf | CawFOC.bin | CawFOC.hex]。

## 👨‍💻 使用示例

一下代码可以在`freertos.c`中查看

```c
FOC_T foc1;
PID_T velPID1;
PID_T anglePID1;
LOWPASS_FILTER_T velFilter1;
FOC_Closeloop_Init(&foc1, &htim1, PWM_PERIOD, 12.6, 1, 7);
FOC_SetVoltageLimit(&foc1, 10.0);
FOC_HAL_Init(&foc1, &hi2c1);

PID_Init(&velPID1, 2, 0, 0, 100000, foc1.voltage_power_supply / 2);
PID_Init(&anglePID1, 2, 0, 0, 100000, 100);
LOWPASS_FILTER_Init(&velFilter1, 0.01);

FOC_AlignmentSensor(&foc1);

for (;;) {
    // 闭环位置控制
    // Foc_TestCloseloopAngle(&foc1, &anglePID1, 3.141592654);

    // 闭环速度控制
    Foc_TestCloseloopVelocity(&foc1, &velFilter1, &velPID1, 10);
    FOC_SensorUpdate();
    osDelay(1);
}
```

## 📚 参考资料

Park 变换：https://zhuanlan.zhihu.com/p/614244367

Clark 变换：https://zhuanlan.zhihu.com/p/613996592

DengFoc：http://dengfoc.com/#/

SimpleFOC 中文：http://simplefoc.cn/#/
