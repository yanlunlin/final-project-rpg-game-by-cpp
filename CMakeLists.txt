# 1. 規定 CMake 的最低版本要求
cmake_minimum_required(VERSION 3.12)

# 2. 定義你的專案名稱與語言
project(FantasyRPG LANGUAGES CXX)

# 3. 強制要求編譯器使用 C++17 標準
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 4. 告訴 CMake 標頭檔（.h）藏在 include 資料夾裡
include_directories(include)

# 5. 自動把 src 資料夾裡面所有的 .cpp 檔案打包成一個變數，不用手動逐一寫名字
file(GLOB_RECURSE SRC_FILES "src/*.cpp")

# 6. 定義最終產生的執行檔名稱（叫做 Game），並指定要把 main.cpp 和所有 src 底下的 cpp 一起編譯進去
add_executable(Game main.cpp ${SRC_FILES})