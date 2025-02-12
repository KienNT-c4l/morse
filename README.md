# morse
# Morse Code Converter

## Giới thiệu
Dự án chuyển đổi giữa văn bản sang mã morse và ngược lại

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

