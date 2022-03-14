# The-17th-Zhongkong-Cup-2022

This is the code repository of the 17th Zhongkong Cup robot competition of Zhejiang University in 2022.

### Function realization of lower computer (STM32)

1. **Brushless motor drive**

   Drive, speed regulation and speed feedback.

2. **Seven way tracing module**

3. **Steering engine control**

4. **bonus**

   - IMU odometer
   - Visual line tracing
   - Ultrasonic positioning

### Function realization of upper computer (Jetson nano)

1. **Yolo dataset training**

2. **Object recognition**

   Identify objects such as cans, cubes and tennis balls, and give feedback on whether there are objects in six positions

3. **Use ROS to communicate with lower computer**