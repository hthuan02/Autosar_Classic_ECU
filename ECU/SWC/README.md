# SWC (Software Component)

Đây là tầng trên cùng (Application) thực hiện các task (tính năng) của xe, ECU điều khiển động cơ như:

- Task 1. Điều khiển moment xoắn(Torque Control)

- Task 2. Điều khiển tốc độ động cơ (Speed Control)

- Task 3. Quản lý nhiệt động cơ (Thermal Management)

- Task 4. Điều khiển dòng điện và điện áp (Current and Voltage Control)

- Task 5. Quản lý phanh tái sinh (Regenerative Braking Control)

...

Các tính năng trong tầng SWC để xử lý logic tính toán dữ liệu, và gọi tầng RTE (Runtime Environment) để thực hiện tiếp các tác vụ