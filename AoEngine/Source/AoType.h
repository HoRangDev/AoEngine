#pragma once
#include <string>
#include <cstdint>
#include <atomic>

using uint8 = unsigned char;
using int8 = signed char;
using uint16 = unsigned short;
using int16 = signed short;
using uint32 = unsigned int;
using int32 = signed int;
using uint64 = unsigned long long;
using int64 = long long;

using atomic_bool = std::atomic<bool>;
using atomic_uint8 = std::atomic<uint8>;
using atomic_int8 = std::atomic<int8>;
using atomic_uint16 = std::atomic<uint16>;
using atomic_int16 = std::atomic<int16>;
using atomic_uint32 = std::atomic<uint32>;
using atomic_int32 = std::atomic<int32>;
using atomic_uint64 = std::atomic<uint64>;
using atomic_int64 = std::atomic<int64>;
using atomic_float = std::atomic<float>;
using atomic_double = std::atomic<double>;

using string = std::wstring;
using stdstring = std::string;