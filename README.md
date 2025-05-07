# GAME FLAPPY DUCK

## Thông tin sinh viên
- **Tên:** Phạm Đức Hiệu
- **MSV:** 24022790

## Giới thiệu
Game Flappy Duck là một trò chơi lấy cảm hứng từ Flappy Bird nổi tiếng, trong đó người chơi điều khiển một chú vịt vượt qua các chướng ngại vật là những cái ống. Mục tiêu là giúp chú vịt bay qua càng nhiều ống càng tốt để đạt điểm cao nhất.

## Cách chơi
- Nhấn **Space** hoặc **click chuột** để điều khiển chú vịt bay lên
- Nhấn **Esc** để tạm dừng trò chơi
- Tránh va chạm với các ống và mặt đất
- Thu thập các hộp năng lượng để kích hoạt các hiệu ứng đặc biệt

## Tính năng đặc biệt
1. **Hộp năng lượng:**
   - **Hộp ma:** Cho phép chú vịt đi xuyên qua các ống trong 3 giây
   - **Hộp tăng tốc:** Làm các ống di chuyển nhanh hơn trong 3 giây, tăng độ khó và cơ hội ghi điểm

2. **Hệ thống huy chương:**
   - **Huy chương Đồng:** Đạt được khi vượt qua một ngưỡng điểm cơ bản
   - **Huy chương Bạc:** Đạt được khi vượt qua ngưỡng điểm trung bình
   - **Huy chương Vàng:** Đạt được khi vượt qua ngưỡng điểm cao

## Đồ họa & Âm thanh
- Đồ họa đơn giản, dễ nhìn
- Hiệu ứng âm thanh khi:
  - Chú vịt bay lên
  - Thu thập hộp năng lượng
  - Vượt qua ống
  - Va chạm và kết thúc trò chơi
  - Đạt được huy chương

## Cấu trúc mã nguồn
- **character.cpp/.h:** Xử lý logic nhân vật (vịt), bao gồm di chuyển và va chạm
- **pipe.cpp/.h:** Quản lý các ống chướng ngại vật
- **powerup.cpp/.h:** Quản lý các hộp năng lượng đặc biệt
- **game.cpp/.h:** Điều khiển luồng chính của trò chơi
- **texture.cpp/.h:** Xử lý đồ họa và hiển thị
- **main.cpp:** Điểm khởi đầu của chương trình

## Logic va chạm
Game sử dụng cơ chế kiểm tra va chạm đơn giản dựa trên hình chữ nhật bao quanh các đối tượng:
- Kiểm tra va chạm giữa vịt và các ống
- Kiểm tra va chạm với mặt đất và trần nhà
- Kiểm tra va chạm với các hộp năng lượng

## Cơ chế vật lý
- Chú vịt chịu tác động của trọng lực, rơi xuống khi không có đầu vào từ người chơi
- Khi người chơi tương tác, chú vịt nhảy lên với một lực ban đầu
- Cơ chế tính toán dựa trên phương trình bậc hai, mô phỏng chuyển động parabol
- Góc xoay của vịt thay đổi theo hướng chuyển động, tạo cảm giác thực tế

## Kỳ vọng đánh giá
- **Điểm kỳ vọng:** 7.0-7.5
- **Lý do:**
  - Có đồ họa đơn giản
  - Có hiển thị văn bản (điểm số, hướng dẫn)
  - Có âm thanh
  - Có các cơ chế chơi sáng tạo (hộp năng lượng, huy chương)
  - Có xử lý vật lý và va chạm cơ bản

## Cài đặt & Chạy game
1. Tải xuống mã nguồn từ repository
2. Cài đặt các thư viện cần thiết (SDL2, SDL2_image, SDL2_ttf, SDL2_mixer)
3. Biên dịch mã nguồn
4. Chạy file thực thi

## Thư viện sử dụng
- SDL2
- SDL2_image
- SDL2_ttf
- SDL2_mixer


