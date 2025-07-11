# Chapter 3 - STM32
1. Quy trình buid firmware trong hệ thống nhúng
<img width="1392" height="572" alt="image" src="https://github.com/user-attachments/assets/01c273df-2896-484f-8805-ca44dea67ad5" />
Bao gồm các giai đoạn:
- Tiền xử lý (Pre-processing)
- Biên dịch (Compilation)
- Dịch mã máy (Assembly)
- Liên kết (Linking)
- Định vị và ánh xạ bộ nhớ (Locating)

1.1. Giai đoạn tiền xử lý (Pre-processing)
Tiền xử lý là bước đầu tiên trong quy trình biên dịch firmware. Ở giai đoạn này, mã nguồn sẽ trải qua một chuỗi các chuyển đổi nhằm chuẩn bị cho quá trình biên dịch tiếp theo.

Trong giai đoạn tiền xử lý, trình preprocessor thực hiện các thao tác chính sau:
- Loại bỏ phần chú thích (comments)
- Xử lý các chỉ thị tiền xử lý (preprocessor directives):
    Các dòng bắt đầu bằng dấu # như:
      #define → định nghĩa macro
      #ifdef, #ifndef, #endif → biên dịch có điều kiện
      #include → nhúng các tệp tiêu đề
    Trình tiền xử lý sẽ thay thế các chỉ thị này bằng giá trị thực tế hoặc đoạn mã tương ứng.
- Tạo file trung gian đầu ra (.i):
    Các tệp .i này chứa mã nguồn đã được loại bỏ chú thích và xử lý đầy đủ các chỉ thị, sẵn sàng cho bước biên dịch.

1.2. Biên dịch (Compilation)
Chuyển đổi các tệp nguồn đã tiền xử lý (.i) thành mã Assembly đặc thù của kiến trúc mục tiêu (ví dụ: ARM Cortex-M).

Đầu vào:
- Các tệp .i – là mã nguồn đã được xử lý bởi trình tiền xử lý
Quá trình xử lý:
- Trình biên dịch phân tích cấu trúc mã, kiểm tra cú pháp và logic
- Tối ưu hóa mã cho hiệu suất và sử dụng bộ nhớ hiệu quả
- Chuyển đổi các biểu thức, hàm và khối điều kiện trong C → thành mã Assembly phù hợp với vi xử lý mục tiêu
Đầu ra:
- Một tập hợp các tệp mã Assembly, thường có đuôi .s (ví dụ: main.s)

1.3. Dịch sang mã máy (Asembly)
Trong bước này, các tệp mã Assembly (.s) sẽ được chuyển đổi thành mã máy nhị phân, tạo ra các tệp đối tượng (object files).

Đầu vào:
- Các tệp mã Assembly có phần mở rộng .s
Xử lý: Trình biên dịch mã máy, gọi là assembler, sẽ:
- Phân tích từng lệnh Assembly
- Chuyển đổi từng lệnh thành mã nhị phân tương ứng, đúng theo kiến trúc vi xử lý (ví dụ ARM Cortex-M)
Đầu ra:
- Tạo ra các tệp đối tượng (object files) – thường có đuôi .o

1.4. Giai đoạn Linking – Ghép nối chương trình thành một thể thống nhất
Linking là giai đoạn mà tất cả các tệp đối tượng riêng lẻ (.o) được kết hợp lại để tạo thành một chương trình hoàn chỉnh. Đồng thời, bước này cũng tích hợp các thư viện tiêu chuẩn cần thiết và giải quyết các tham chiếu giữa các module mã nguồn.

Đầu vào:
- Các tệp đối tượng .o
- Các tệp thư viện ngôn ngữ C tiêu chuẩn (nếu cần)
Quá trình xử lý: Trình liên kết (linker) sẽ:
- Ghép nối tất cả các tệp .o
- Giải quyết các biểu tượng và địa chỉ tham chiếu giữa các module
- Thực hiện cấp phát vùng bộ nhớ cho biến và hàm
Đầu ra:
- Tạo ra tệp relocatable, chưa phải mã thực thi cuối cùng

Tệp relocatable (có thể định vị) là kết quả trung gian của quá trình linking. Nó chứa toàn bộ mã đối tượng và thư viện cần thiết, tuy nhiên:
- Các địa chỉ bộ nhớ vẫn còn ở dạng tương đối (relative)
- Chưa được ánh xạ vào các vị trí cụ thể trong bộ nhớ của vi điều khiển
Điều này đảm bảo rằng khi firmware được chạy trên thiết bị đích: Mỗi phần mã và dữ liệu đều nằm đúng vị trí bộ nhớ theo sơ đồ hệ thống

1.5. Giai đoạn Định vị (Locating)
Đây là giai đoạn cuối cùng trong quy trình biên dịch firmware, nơi tệp relocatable (tệp có thể định vị được) sẽ được chuyển đổi thành tệp thực thi nhị phân cuối cùng.
Giai đoạn này được hướng dẫn bởi một tệp linker script, giúp cung cấp thông tin quan trọng về cách tổ chức bộ nhớ của vi điều khiển mục tiêu.

Đầu vào:
- Một tệp relocatable (kết quả từ giai đoạn linking)
- Một tệp linker script – chứa sơ đồ bộ nhớ và cách ánh xạ vùng mã, dữ liệu
Quá trình xử lý: Công cụ định vị (locator) sử dụng linker script để:
- Đặt các đoạn mã và dữ liệu vào vị trí bộ nhớ quy định
- Điều chỉnh địa chỉ và offset để phù hợp với sơ đồ bộ nhớ của vi điều khiển
Đầu ra: Một tệp nhị phân thực thi (executable binary), thường có định dạng:
- ELF (Executable and Linkable Format)
- Hoặc định dạng nhị phân thuần túy .bin

2. GNU binary tools for embedded systems
arm-none-eabi-gcc
- none cho biết rằng mã được biên dịch để chạy trực tiếp trên phần cứng, không có hệ điều hành trung gian → đây chính là đặc điểm của lập trình bare-metal.
- eabi đảm bảo mã nhị phân được sinh ra tuân thủ chuẩn layout nhúng, giúp tương thích với mọi bộ xử lý Arm tuân thủ chuẩn EABI.
- gcc cho phép thực hiện tất cả các bước: tiền xử lý, biên dịch, dịch mã máy, liên kết – chỉ với một lệnh duy nhất.
<img width="1279" height="370" alt="image" src="https://github.com/user-attachments/assets/e9d6d603-1dce-4b9d-820b-8a4a3f0ab2d5" />

Các cờ(flag) thường dùng:

<img width="1324" height="832" alt="image" src="https://github.com/user-attachments/assets/ff64e93a-fd57-445a-9bac-53bdd70e03fe" />
<img width="1302" height="275" alt="image" src="https://github.com/user-attachments/assets/2a68e6bc-f362-4e8d-9511-b49efc69099c" />


4. 
