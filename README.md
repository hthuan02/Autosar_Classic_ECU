## (Autosar Classic: Project 2)
# ECU: Quản lý phanh tái sinh (Regenerative Braking Control)

---

## I. Giới thiệu dự án
### 1. Hệ thống phanh tái sinh (Regenerative Braking Control)

> Hệ thống quản lý hệ thống phanh tái sinh trong xe điện hoặc xe hybrid nhằm tận dụng chuyển động năng thành điện năng để nạp vào pin. Hệ thống bao gồm nhiều cảm biến để đo đạc tình trạng xe và điều chỉnh phanh tái sinh.

 <img src="https://github.com/hthuan02/Autosar_Classic_ECU/blob/main/img/regen_brake_control_in_car.jpeg" alt="Memory Layout" width="880"/>

 _**Nguồn ảnh**: https://community.vinfastauto.us/uncategorized/regenerative-braking-on-electric-vehicles-working-principles-and-benefits-of-application/_

### 2. Chức năng quản lý phanh tái sinh
#### 1. Thu hồi năng lượng

- Tận dụng chuyển động năng khi phanh hoặc nhả ga.  
- Biến chuyển động năng thành điện năng để nạp vào pin.  
- Cải thiện hiệu suất sử dụng năng lượng, tăng quãng đường di chuyển.  

#### 2. Giảm hao mòn

- Hạn chế sử dụng phanh truyền thống, giảm hao mòn phanh.  

---

## II. Nguyên lý hoạt động

- **Chuyển động năng thành điện năng**: Khi người lái nhả ga hoặc phanh, ECU kích hoạt chế độ phanh tái sinh. Động cơ điện chuyển động năng thành điện năng và nạp lại vào pin.

- **Kích hoạt phanh tái sinh**: Phanh tái sinh được kích hoạt khi nhả ga hoặc nhấn phanh để thu hồi năng lượng từ tốc độ di chuyển của xe.

- **Tái nạp vào pin**: Năng lượng tạo ra từ phanh tái sinh được nạp vào pin, kéo dài tuổi thọ và giảm nhu cầu sạc.

- **Lực phanh tái sinh**: ECU điều chỉnh lực phanh dựa trên tốc độ, độ nghiêng và mức độ nhấn phanh từ người lái để đảm bảo quá trình giảm tốc mượt mà và an toàn.

---

## III. Hệ thống cảm biến và điều chỉnh phanh tái sinh
### 1. Cảm biến tốc độ

- Đọc giá trị tốc độ hiện tại của xe.  
- Tính toán:  
  - Lực phanh tái sinh (Đơn vị: N).  
  - Công suất tái sinh (Đơn vị: W).  
  - Năng lượng tái sinh (Đơn vị: Wh).  
- Kiểm tra bàn đạp ga nhả hoặc phanh được nhấn, và tốc độ có đủ điều kiện.  

### 2. Cảm biến trạng thái pin

- Đo trạng thái sạc của pin (SOC).  
- Kiểm tra nhiệt độ pin.  
- Ngăn chặn tái nạp khi nhiệt độ pin quá cao.  
- Tính phần trăm pin được nạp từ năng lượng tái sinh.  

### 3. Cảm biến độ nghiêng

- Đo góc nghiêng xe (Đơn vị: °).  
- Xác định xe đang lên dốc, xuống dốc hoặc trên mặt phẳng.  
- Điều chỉnh lực phanh tái sinh dựa vào góc nghiêng.  

### 4. Cảm biến tải trọng

- Đo khối lượng xe hiện tại.  
- Điều chỉnh lực phanh tái sinh dựa vào tải trọng xe.  

---

## IV. Ba tầng chính trong hệ thống quản lý phanh tái sinh
Hệ thống quản lý phanh tái sinh (Regenerative Braking Control) được xây dựng dựa trên ba tầng chính của kiến trúc AUTOSAR:
- Software Component (SWC).
- Runtime Environment (RTE).
- Basic Software (BSW).

### 1. Application Layer
Đây là tầng nằm ở trên cùng, gồm nhiều khối phần mềm ứng dụng (Software Component - SWC). Mỗi SWC thực hiện 1 chức năng cụ thể trong hệ thống ECU.

 <img src="https://github.com/hthuan02/Autosar_Classic_ECU/blob/main/img/ECU_Task5.png" alt="Memory Layout" width="880"/>

Trong hệ thống này, tầng SWC thực hiện tính năng quản lý và điều khiển quá trình phanh tái sinh, bao gồm các chức năng như đọc dữ liệu từ cảm biến, tính toán lực phanh tái sinh, điều chỉnh các tham số liên quan, và tái nạp năng lượng vào pin. Dựa vào 2 hàm chính:

- `RegenBrakeControl_Init(void)`: Hàm khởi tạo các cảm biến cần thiết như cảm biến tốc độ, cảm biến trạng thái pin, cảm biến góc nghiêng, và cảm biến tải trọng. 

- `RegenBrakeControl_Update(void)`: Hàm cập nhật và điều khiển liên tục phanh tái sinh, tính toán lực và công suất phanh tái sinh dựa trên dữ liệu cảm biến và các điều kiện như nhả ga, nhấn phanh, và tốc độ xe.

- Trong hàm cập nhật, gồm các hàm nhỏ như:
   - Tái nạp năng lượng vào pin: Chuyển đổi năng lượng từ phanh tái sinh vào pin, đồng thời giám sát nhiệt độ pin để đảm bảo an toàn.

   - Điều chỉnh lực phanh tái sinh: Dựa trên góc nghiêng và tải trọng để đảm bảo hiệu quả và an toàn.

### 2. Runtime Environment (RTE)
RTE là tầng trung gian kết nối giữa tầng Software Component (SWC) và Bassic Software (BSW), nhằm cung cấp các API tiêu chuẩn để truy cập dữ liệu từ cảm biến ở tầng BSW và chuyển tiếp dữ liệu đó đến các hàm xử lý logic ở tầng SWC. 

Giới thiệu về vai trò của tầng RTE trong hệ thống phanh tái sinh:

- **Hàm khởi tạo**: Bao gồm việc chỉ định kênh ADC, giá trị tối đa, và các tham số cấu hình khác.
  
   - `Rte_Call_RpSpeedAccess_Init`: Cảm biến tốc độ.
     
   - `Rte_Call_RpBatterySOC_Init`: Cảm biến trạng thái pin.
 
   - `Rte_Call_RpInclinationSensor_Init`: Cảm biến góc nghiêng.
 
   - `Rte_Call_RpLoadAccess_Init`: Cảm biến tải trọng.

- **Hàm đọc dữ liệu từ cảm biến**:
   
   - `Rte_Read_RpSpeedAccess_Speed`: Đọc tốc độ hiện tại xe.

   - `Rte_Read_RpBatterySOC_BatterySOC`: Đọc trạng thái sạc pin và nhiệt độ.
 
   - `Rte_Read_RpInclinationSensor_Inclination`: Đọc góc nghiêng.
 
   - `Rte_Read_RpLoadAccess_Load`: Đọc tải trọng.
 
### 3. Bassic Software (BSW)
Basic Software (BSW) là tầng thấp nhất của kiến trúc AUTOSAR, đóng vai trò nền tảng để hỗ trợ phần mềm ứng dụng (SWC) hoạt động trên phần cứng. BSW cung cấp các dịch vụ cơ bản như quản lý phần cứng, giao tiếp, chẩn đoán, và các dịch vụ hệ thống.

Cấu trúc chính của BSW:

- **Service Layer**: Cung cấp các dịch vụ hệ thống như quản lý thời gian, lưu trữ dữ liệu, và giao tiếp mạng.

- **ECU Abstraction Layer**: Lớp này gồm ba thành phần
  
   - Communication Manager (ComM): Quản lý giao tiếp trên các giao thức truyền thông.
 
   - I/O Hardware Abstraction (IoHwAb): Cung cấp các API để truy cập và điều khiển phần cứng đầu vào/đầu ra.
 
   - Memory Interface (MemIf): Quản lý truy cập và lưu trữ dữ liệu trên bộ nhớ.

- **Microcontroller Abstraction Layer** (MCAL): Giao tiếp trực tiếp với vi điều khiển, cung cấp các driver như ADC, PWM, CAN, SPI,...


▶️▶️▶️ _**Trong tầng BSW ở dự án này, chỉ làm việc trực tiếp ở lớp I/O Hardware Abstraction (IoHwAb) của ECU quản lý phanh tái sinh.**_

Lớp IoHwAb (I/O Hardware Abstraction) thuộc tầng BSW, đóng vai trò trung gian giữa phần cứng và các tầng phần mềm cao hơn như RTE và SWC.

Nhiệm vụ chính là cung cấp API để khởi tạo và truy xuất dữ liệu từ các cảm biến (tốc độ, trạng thái pin, góc nghiêng, tải trọng), hỗ trợ tầng RTE truyền dữ liệu lên tầng xử lý logic (SWC), qua đó đảm bảo tính độc lập giữa phần cứng và phần mềm.

Các chức năng chính trong từng loại cảm biến:

- Cảm biến tốc độ:
  
   - `IoHwAb_SpeedAccess_Init`: Khởi tạo cảm biến tốc độ, cấu hình kênh ADC và tốc độ tối đa.

   - `IoHwAb_SpeedAccess_Read`: Đọc và trả về giá trị tốc độ hiện tại.

- Cảm biến trạng thái pin (SOC):

   - `IoHwAb_BatterySOC_Init`: Khởi tạo cảm biến pin, cấu hình SOC tối đa và nhiệt độ pin.

   -  `IoHwAb_BatterySOC_Read`: Đọc trạng thái pin (SOC) và nhiệt độ.

- Cảm biến góc nghiêng:

   - `IoHwAb_InclinationSensor_Init`: Khởi tạo cảm biến góc nghiêng, cấu hình kênh ADC và góc nghiêng tối đa.

   - `IoHwAb_InclinationSensor_Read`: Đọc và trả về góc nghiêng hiện tại.

- Cảm biến tải trọng:

   - `IoHwAb_LoadAccess_Init`: Khởi tạo cảm biến tải trọng, cấu hình tải trọng tối đa.
  
   - `IoHwAb_LoadAccess_Read`: Đọc và trả về giá trị tải trọng.
 
---

## V. Kết luận

> Hệ thống quản lý phanh tái sinh không chỉ cải thiện hiệu suất năng lượng mà còn giảm hao mòn phanh, tăng tuổi thọ của xe. Đây là một giải pháp bền vững, hỗ trợ phát triển các phương tiện giao thông thân thiện với môi trường.
