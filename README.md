# Midgard Defense RPG (C++)

一款使用 **C++** 製作的文字版 RPG 遊戲，採用 **CLI（Command Line Interface）** 操作。玩家可以招募不同職業角色組成隊伍，利用普通攻擊、技能及道具擊敗怪物，體驗回合制戰鬥的樂趣。

---

## 專案介紹

本專案為 **計算機程式設計實習（二）期末專案**。

遊戲以文字介面呈現，透過 **物件導向程式設計（Object-Oriented Programming, OOP）**，將玩家、怪物、技能與物品等功能分別設計成不同 Class，使程式架構更清楚、更容易維護與擴充。

---

## 專案目標

- 熟悉 C++ 物件導向程式設計
- 練習 Class 的設計與應用
- 學習 Git 與 GitHub 團隊協作
- 完成一款可遊玩的文字版 RPG 遊戲

---

## 遊戲特色

- 多種職業角色
- 回合制戰鬥系統
- 技能與 MP 消耗機制
- 道具使用系統
- 多關卡怪物挑戰
- Boss 戰
- 劇情開場

---

## 遊戲流程

1. 開始遊戲
2. 閱讀劇情
3. 招募隊伍
4. 進入戰鬥
5. 選擇行動
   - 普通攻擊
   - 使用技能
   - 使用物品
6. 擊敗所有怪物
7. 挑戰最終 Boss
8. 完成遊戲

---

## 職業介紹

| 職業 | 特色 |
|------|------|
| Swordman | 高生命值、高攻擊力 |
| Warrior | 高防禦能力 |
| Wizard | 高魔法輸出 |
| Priest | 回復與支援 |
| Archer | 穩定遠距攻擊 |
| Thief | 高速度、高爆發輸出 |

---

## 技能系統

每個角色皆擁有專屬技能，每項技能包含：

- 技能名稱
- 技能傷害
- MP 消耗

### 範例技能

- Bash
- Fire Ball
- Double Shot

---

## 道具系統

玩家可於戰鬥中使用道具恢復狀態或提升能力。

### 道具

- HP Potion
- MP Potion
- Strength Potion
- Weapon

---

## 怪物介紹

| 怪物 | 說明 |
|------|------|
| Slime | 初階怪物，血量較低 |
| Goblin | 中階怪物，攻擊力提升 |
| Succubus | 最終 Boss，擁有高血量與高攻擊力 |

---

## 遊戲規則

### 勝利條件

- 擊敗所有關卡怪物
- 打倒最終 Boss

### 失敗條件

- 玩家 HP 歸零
- 隊伍全滅

### 戰鬥規則

- 採用回合制戰鬥
- 玩家先行動
- 怪物於玩家行動後反擊
- 使用技能需消耗 MP
- 使用道具需確認是否仍有數量

---

## 程式架構

```text
Project
│
├── Player
├── Monster
├── Skill
├── Item
└── main.cpp
```

### Class 功能

#### Player

- 玩家資料
- 普通攻擊
- 受傷判定
- 使用物品
- 存活判斷

#### Monster

- 怪物資料
- 攻擊
- 掉落獎勵
- 存活判斷

#### Skill

- 技能名稱
- 技能傷害
- MP 消耗

#### Item

- 道具名稱
- 道具效果
- 數量管理

---

## 使用技術

- C++
- Object-Oriented Programming (OOP)
- Class
- Vector
- String
- Function
- Git
- GitHub

---

## 執行方式

### 編譯

```bash
g++ main.cpp -o RPG
```

### 執行

```bash
./RPG
```

---

## 專案畫面

可將遊戲截圖放入 `images` 資料夾。

```text
images/
├── start.png
├── recruit.png
├── battle.png
├── boss.png
└── victory.png
```

README 顯示方式：

```md
## Screenshot

![Start](images/start.png)

![Recruit](images/recruit.png)

![Battle](images/battle.png)

![Boss](images/boss.png)

![Victory](images/victory.png)
```

---

## 未來可擴充功能

- 經驗值（EXP）系統
- 等級提升系統
- 商店系統
- 更多職業角色
- 更多技能
- 更多怪物與 Boss
- 地圖探索
- 存檔／讀檔功能

---

## 專案成員

| 成員 | 負責內容 |
|------|----------|
| 吳佳晟 | Player Class |
| 張榮豐 | Skill Class |
| 林彥侖 | Monster Class |
| 毛植陞 | Item Class |
| 全體成員 | 程式整合、測試、除錯、Git 協作、報告撰寫 |

---

## License

This project is for educational purposes only.
