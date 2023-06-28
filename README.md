# 🦉 CAW-FOC

## 📜 项目介绍

CAW FOC 项目由 3 部分组成，在 CAW-PACKAGES/FOC 目录下存放相关的代码。

- foc.h/foc.c：foc 相关的主要算法
- foc_hal.h/foc_hal.c：用于配置编码器
- foc_test.h/foc_test.c：测试程序

## 🎥 效果展示

https://www.bilibili.com/video/BV1Hh4y1M7nH/

https://www.bilibili.com/video/BV1BP411v7nA/

## ⏰ TODO

| 功能         | 状态   |
| ------------ | ------ |
| 开环速度控制 | ✔      |
| 闭环力矩控制 | ✔      |
| 闭环位置控制 | ✔      |
| 闭环速度控制 | 进行中 |

## 💾 函数声明

```c
/**
 * @description: 获取闭环控制电角度数据
 * @param {FOC_T} *hfoc foc句柄
 * @return {float} 电角度值
 */
float FOC_CloseloopElectricalAngle(FOC_T *hfoc);

/**
 * @description: 设置力矩
 * @param {FOC_T} *hfoc foc句柄
 * @param {float} Uq 力矩值
 * @param {float} angle_el 电角度
 * @return {*}
 */
void FOC_SetTorque(FOC_T *hfoc, float Uq, float angle_el);

/**
 * @description: FOC闭环控制初始化
 * @param {FOC_T} *hfoc foc句柄
 * @param {TIM_HandleTypeDef} *tim PWM定时器句柄
 * @param {float} pwm_period PWM的重装载值
 * @param {float} voltage 电源电压值
 * @param {int} dir 方向
 * @param {int} pp 极对数
 * @return {*}
 */
void FOC_Closeloop_Init(FOC_T *hfoc, TIM_HandleTypeDef *tim, float pwm_period,
                        float voltage, int dir, int pp);

/**
 * @description: 设置电压限制
 * @param {FOC_T} *hfoc foc句柄
 * @param {float} v 电压值
 * @return {*}
 */
void FOC_SetVoltageLimit(FOC_T *hfoc, float v);

/**
 * @description: 编码器零位较准（需要配置传感器相关函数指针）
 * @param {FOC_T} *hfoc foc句柄
 * @return {*}
 */
void FOC_AlignmentSensor(FOC_T *hfoc);

/**
 * @description: 绑定用于获取单圈弧度值的函数（0 - 6.28）
 * @param {FOC_T} *hfoc foc句柄
 * @param {FUNC_SENSOR_GET_ONCE_ANGLE} s 函数指针
 * @return {*}
 */
void FOC_Bind_SensorGetOnceAngle(FOC_T *hfoc, FUNC_SENSOR_GET_ONCE_ANGLE s);

/**
 * @description: 绑定用于获取累计弧度值的函数
 * @param {FOC_T} *hfoc foc句柄
 * @param {FUNC_SENSOR_GET_ANGLE} s 函数指针
 * @return {*}
 */
void FOC_Bind_SensorGetAngle(FOC_T *hfoc, FUNC_SENSOR_GET_ANGLE s);
```

## 👨‍💻 使用示例

```c
FOC_T foc1;
FOC_Closeloop_Init(&foc1, &htim1, PWM_PERIOD, 12.0, 1, 7);
FOC_SetVoltageLimit(&foc1, 10.0);
FOC_HAL_Init(&foc1, &hi2c1);
FOC_AlignmentSensor(&foc1);

while (1) {
    Foc_TestCloseloopAngle(&foc1, 0);
}
```

## 📚 参考资料

Park 变换：https://zhuanlan.zhihu.com/p/614244367

Clark 变换：https://zhuanlan.zhihu.com/p/613996592

DengFoc：http://dengfoc.com/#/

SimpleFOC 中文：http://simplefoc.cn/#/
