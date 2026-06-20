# 1. 規定 CMake 的最低版本要求
cmake_minimum_required(VERSION 3.12)

# 2. 定義你的專案名稱與語言
project(FantasyRPG LANGUAGES CXX)

# 3. 強制要求編譯器使用 C++17 標準
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 4. 自動把「當前目錄」下所有的 .cpp 檔案打包成 SRC_FILES 變數
file(GLOB SRC_FILES "*.cpp")

# 5. 定義最終產生的執行檔名稱（叫做 Game），並把抓到的所有 cpp 編譯進去
add_executable(Game ${SRC_FILES})
