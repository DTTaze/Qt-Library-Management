Thư viện: Ta tổ chức các danh sách sau: 
- Đầu sách : danh sách tuyến tính là 1 mảng con trỏ (ISBN , Tên sách, Số trang, Tác giả, năm xuất bản, thể loại, con trỏ dms): con trỏ sẽ trỏ đến các sách thuộc đầu sách tương ứng. Danh sách đầu sách luôn tăng dần theo tên sách.
- Danh mục sách : danh sách liên kết đơn( Mã sách,  trạng thái, vị trí   ). Mỗi cuốn sách chỉ có 1 mã duy nhất; trạng thái của sách bao gồm: 0: cho mượn được, 1: đã có độc giả mượn, 2: sách đã thanh lý . 
- Danh sách thẻ độc giả: cây nhị phân tìm kiếm (MATHE (số nguyên ngẫu nhiên tự động), Ho, Ten,  Phai, trạng thái của thẻ, con trỏ): con trỏ sẽ trỏ đến danh sách các cuốn sách đã và đang mượn.
- Danh sách MUONTRA : danh sách liên kết đơn ( MASACH,  NgayMuon, NgayTra, trạng thái): trạng thái =0 là sách đang mượn (chưa trả), =1 là đã trả, =2 : làm mất sách 

Chương trình có các chức năng sau: 
a. Nhập thẻ độc giả: thêm / xóa / hiệu chỉnh thông tin thẻ độc giả. Mã thẻ độc giả được chương trình tự động lấy ngẫu nhiên và không trùng với các mã thẻ độc giả cũ; Phái chỉ nhận ‘Nam’ hoặc ‘Nữ’; trạng thái thẻ = 0 khi thẻ bị khóa, trạng thái thẻ = 1 khi thẻ  đang hoạt động (được quyền mượn sách). 
b. In danh sách độc giả : in ra màn hình theo thứ tự tên+họ tăng dần hoặc theo thứ tự mã độc giả tăng dần theo yêu cầu của thủ thư.
c. Nhập thông tin đầu sách và đánh mã sách tự động 
d. In danh sách các đầu sách trong thư viện theo từng thể loại, trong từng thể loại thì in theo thứ tự tên sách tăng dần.
e. Tìm thông tin sách dựa vào tên sách : in ra các thông tin mã ISBN, tên sách, tác giả, năm xuất bản, thể loại, các mã sách , trạng thái mã sách trong thư viện.
f. Mượn sách : nhập vào mã thẻ độc giả, chương trình sẽ liệt kê các sách mà độc giả đang mượn. Mỗi độc giả chỉ được mượn tối đa 3 cuốn, không cho mượn khi giữ 1 sách quá hạn (7 ngày)
g. Trả sách 
h. Liệt kê danh sách các mã sách, tên sách mà 1 độc giả có số thẻ X đang mượn
i. In danh sách độc giả mượn sách quá hạn theo thứ tự thời gian quá hạn giảm dần
j. In 10 sách có số lượt mượn nhiều nhất

- Cần cài đặt Qt Creator để có thể chạy được app (Phiên bản mình đang sử dụng là Qt Creator 14.2.0)
- Đây là một đồ án cần làm để có thể qua môn Cấu trúc dữ liệu & Giải thuật của thầy Lưu Nguyễn Kỳ Thư
- Đây là một số hình ảnh của project:
- ![image](https://github.com/user-attachments/assets/72e2023e-4523-4df7-992c-0724b91aef61)
- ![image](https://github.com/user-attachments/assets/e3af2d1d-363a-4f30-8f79-3593e20aa178)
- ![image](https://github.com/user-attachments/assets/292fd76d-83ea-42e4-911b-9f186d91efd1)
- ![image](https://github.com/user-attachments/assets/9e145538-572e-4e02-ac8e-de34f820ac6a)
- ![image](https://github.com/user-attachments/assets/4cdf02de-24bb-45d3-a9d5-117f4c51c77f)
- Nhóm mình có 3 người và project này được tui mình chia thành 3 phần, và mỗi người sẽ đảm nhận mỗi phần:
  + Thẻ độc giả(a -> b)
  + Đầu sách(c -> d)
  + Mượn sách(e _> j)
- Mình đảm nhận phần thẻ độc giả:
  + Thẻ độc giả sẽ được lưu trữ dưới cấu trúc cây nhị phân tìm kiếm, khóa ở đây là mã thẻ, mã thẻ sẽ được sinh ngẫu nhiên tự động, với điều kiện là mã thẻ được sinh ra
khi thêm thẻ độc giả vào cây nhị phân sẽ tạo ra cây nhị phân tìm kiếm gần như là cân bằng hoàn toàn
  + Mã thẻ được tạo ra sẵn bằng phương pháp sinh số theo thứ từ trung vị khoảng 10000 mã thẻ 
  + Tiếp theo đó chính là in thông tin theo mã thẻ và theo tên(Mã thẻ được duyệt bằng Inorder để có thể sắp xếp theo thứ tự tăng dần, sau đó thẻ độc giả sẽ được chèn có thứ tự vào một liên kết đơn, từ liên kết dơn thì thông tin sẽ được in ra theo thứ tự tên
  + Dữ liệu được lưu/đọc từ file txt





