/* #include "hmac_sha256.hpp" */

#pragma once

#ifndef HMAC_SHA256_HPP
#define HMAC_SHA256_HPP

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iomanip>
#include <map>
#include <sstream>
#include <string>
#include <vector>

// Right Rotate a 32-bit word by 'n' bits
constexpr inline uint32_t rotr(uint32_t x, int n) {
  return (x >> n) | (x << (32 - n));
}

// Right Shift a 32-bit word by 'n' bits
constexpr inline uint32_t shr(uint32_t x, int n) { return x >> n; }

// SHA-256 Constants (represent the first 32 bits of the fractional parts of the
// cube roots of the first 64 primes 2..311)
constexpr uint32_t K[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
    0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
    0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
    0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
    0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
    0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

// SHA-256 Message Schedule (Wt represents the expanded message schedule)
void prepare_schedule(const uint8_t* data, uint32_t* Wt) {
  for (int t = 0; t < 16; ++t) {
    Wt[t] = static_cast<uint32_t>(data[t * 4]) << 24;
    Wt[t] |= static_cast<uint32_t>(data[t * 4 + 1]) << 16;
    Wt[t] |= static_cast<uint32_t>(data[t * 4 + 2]) << 8;
    Wt[t] |= static_cast<uint32_t>(data[t * 4 + 3]);
  }

  for (int t = 16; t < 64; ++t) {
    const uint32_t s0 =
        rotr(Wt[t - 15], 7) ^ rotr(Wt[t - 15], 18) ^ shr(Wt[t - 15], 3);
    const uint32_t s1 =
        rotr(Wt[t - 2], 17) ^ rotr(Wt[t - 2], 19) ^ shr(Wt[t - 2], 10);
    Wt[t] = Wt[t - 16] + s0 + Wt[t - 7] + s1;
  }
}

// SHA-256 Hashing Function
std::string sha256(const std::string& input_string) {
  uint32_t H[8] = {0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
                   0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};

  uint64_t input_length = input_string.length() * 8;

  // Pre-processing: Padding the input string
  const int padding_length = (448 - (input_length + 1)) % 512;
  const int total_length = input_length + 1 + padding_length + 64;
  uint8_t* padded_data = new uint8_t[total_length / 8]{};
  std::memcpy(padded_data, input_string.c_str(), input_string.length());
  padded_data[input_string.length()] = 0x80;
  for (int i = 0; i < 8; ++i) {
    padded_data[total_length / 8 - i - 1] =
        static_cast<uint8_t>(input_length >> (i * 8));
  }

  // Hash computation
  for (int i = 0; i < total_length / 512; ++i) {
    const uint8_t* data_chunk = padded_data + (i * 64);
    uint32_t Wt[64];
    prepare_schedule(data_chunk, Wt);

    uint32_t a = H[0];
    uint32_t b = H[1];
    uint32_t c = H[2];
    uint32_t d = H[3];
    uint32_t e = H[4];
    uint32_t f = H[5];
    uint32_t g = H[6];
    uint32_t h = H[7];

    for (int t = 0; t < 64; ++t) {
      const uint32_t S1 = rotr(e, 6) ^ rotr(e, 11) ^ rotr(e, 25);
      const uint32_t ch = (e & f) ^ ((~e) & g);
      const uint32_t temp1 = h + S1 + ch + K[t] + Wt[t];
      const uint32_t S0 = rotr(a, 2) ^ rotr(a, 13) ^ rotr(a, 22);
      const uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
      const uint32_t temp2 = S0 + maj;

      h = g;
      g = f;
      f = e;
      e = d + temp1;
      d = c;
      c = b;
      b = a;
      a = temp1 + temp2;
    }

    H[0] += a;
    H[1] += b;
    H[2] += c;
    H[3] += d;
    H[4] += e;
    H[5] += f;
    H[6] += g;
    H[7] += h;
  }

  delete[] padded_data;

  // Output the hash as a string
  std::ostringstream result;
  for (int i = 0; i < 8; ++i) {
    result << std::hex << std::setfill('0') << std::setw(8) << H[i];
  }

  return result.str();
}

std::string hmac_sha256(const std::string& key, const std::string& message) {
  const int block_size = 64;  // Block size for SHA-256 is 64 bytes

  std::string key_padded;
  if (key.length() > block_size) {
    key_padded = sha256(key);
  } else {
    key_padded = key;
  }

  if (key_padded.length() < block_size) {
    key_padded.resize(block_size, 0x00);
  }

  std::string inner_key(block_size, 0x36);
  std::string outer_key(block_size, 0x5c);

  // XOR the keys with the padded key
  for (int i = 0; i < block_size; ++i) {
    inner_key[i] ^= key_padded[i];
    outer_key[i] ^= key_padded[i];
  }

  // Inner hash (SHA256(inner_key || message))
  std::string inner_hash = sha256(inner_key + message);

  // Final hash (SHA256(outer_key || inner_hash))
  std::string final_hash = sha256(outer_key + inner_hash);

  return final_hash;
}

#endif