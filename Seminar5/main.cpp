#include <iostream>
#include <vector>

class BitsWriter {
 public:
  void WriteBit(bool bit);
  void WriteByte(unsigned char byte);

  std::vector<unsigned char> GetResult();

 private:
  std::vector<unsigned char> buffer_;
  unsigned char accumulator_ = 0;
  int bits_count_ = 0;
};

void BitsWriter::WriteBit(bool bit) {
  // Ставим бит в аккумулятор на нужное место
  accumulator_ |= static_cast<unsigned char>(bit) << bits_count_;
  ++bits_count_;
  if (bits_count_ == 8) {
    bits_count_ = 0;
    buffer_.push_back(accumulator_);
    accumulator_ = 0;
  }
}

void BitsWriter::WriteByte(unsigned char byte) {
  if (bits_count_ == 0) {
    buffer_.push_back(byte);
  } else {
    accumulator_ |= byte << bits_count_;
    buffer_.push_back(accumulator_);
    accumulator_ = byte >> (8 - bits_count_);
  }
}

std::vector<unsigned char> BitsWriter::GetResult() {
  if (bits_count_ != 0) {
    // Добавляем в буфер аккумулятор, если в нем что-то есть.
    buffer_.push_back(accumulator_);
  }
  buffer_.push_back(static_cast<unsigned char>(bits_count_));
  return std::move(buffer_);
}

int main() {
  BitsWriter bits_writer;

  bits_writer.WriteBit(true);
  bits_writer.WriteBit(false);
  bits_writer.WriteByte(0xFF);
  bits_writer.WriteBit(false);
  bits_writer.WriteBit(true);
  bits_writer.WriteBit(false);
  bits_writer.WriteBit(false);
  bits_writer.WriteBit(false);
  bits_writer.WriteBit(false);
  bits_writer.WriteByte(0xFE);
  bits_writer.WriteBit(true);
  bits_writer.WriteBit(false);
  std::vector<unsigned char> result =
      std::move(bits_writer.GetResult());

  for (unsigned char byte : result) {
    for (int i = 0; i < 8; ++i) {
      std::cout << ((byte >> i) & 1);
    }
    std::cout << " ";
  }
  return 0;
}