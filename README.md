# morse
# Morse Code Converter

## Giới thiệu
Dự án này cung cấp một công cụ đơn giản để chuyển đổi giữa Morse code và văn bản thông thường. Nó hỗ trợ cả mã hóa văn bản sang Morse code và giải mã Morse code thành văn bản.

## Tính năng
- Chuyển đổi văn bản sang Morse code.
- Giải mã Morse code thành văn bản.
- Hỗ trợ ký tự chữ cái, số và một số dấu câu cơ bản.

## Cách sử dụng
### 1. Cài đặt
Clone repository:
```bash
git clone https://github.com/your-username/morse-code-converter.git
cd morse-code-converter
```

### 2. Biên dịch chương trình
Sử dụng trình biên dịch GCC để biên dịch chương trình:
```bash
gcc -o morse_converter morse.c
```

### 3. Chạy chương trình
```bash
./morse_converter <input file> <output file>
```

### 4. Ví dụ sử dụng
#### Mã hóa văn bản sang Morse code
Nhập:
```
Hello World
```
Xuất ra:
```
.... . .-.. .-.. --- / .-- --- .-. .-.. -..
```

#### Giải mã Morse code sang văn bản
Nhập:
```
.... . .-.. .-.. --- / .-- --- .-. .-.. -..
```
Xuất ra:
```
HELLO WORLD
```

