#include <random>

// 簡單實作一個全域工具
class Random {
private:
  // 使用 inline static (C++17)，讓整個遊戲共享同一個亂數引擎，避免數字重複
  inline static std::random_device rd;
  inline static std::mt19937 gen{rd()};

public:
  // 取得區間 [min, max] 的整數
  static int getInt(int min, int max) {
    std::uniform_int_distribution<int> dis(min, max);
    return dis(gen);
  }

  // 取得機率是否成功 (例如機率 0.35 代表 35% 爆擊)
  static bool getChance(double probability) {
    std::uniform_real_distribution<double> dis(0.0, 1.0);
    return dis(gen) <= probability;
  }
};
