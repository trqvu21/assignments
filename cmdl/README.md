# FPT Bootcamp - Table Pattern Command

Bài tập có 2 phần:

1. `ex01_cmd_line_unit_test`: unit test cho parser dạng `cmd_line`.
2. `ex02_my_cmd`: tự viết lại command parser riêng, vẫn dùng pattern **Table**.

## Cách chạy

```bash
make test
```

## Flow chính

- Tạo bảng command: `{ "cmd", handler, "info" }`.
- Parser lấy token đầu tiên trong chuỗi input.
- Duyệt bảng để tìm command trùng tên.
- Nếu tìm thấy thì gọi đúng handler.
- Nếu không tìm thấy thì trả mã lỗi.
