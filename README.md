# 字节跳动算法刷题路线
> 来源：[CodeJeet 字节跳动题库](https://codejeet.com/company/bytedance)（64 题，6 Easy / 49 Medium / 9 Hard）。
> 编排逻辑：**按算法范式分阶段，每阶段内由易到难**。同类套路集中练，形成模式识别能力，比按频率乱刷高效得多。
> 适用：字节实习 / 校招算法面（Medium 是绝对主力区间，正好对应本题库 77% 的题）。

---

## 阶段 0 · 热身：基础结构与一招鲜（先建立手感）

这些题代码量小、套路单一，目的是熟悉链表/数组/栈的基本操作和边界处理，建立"我能 AC"的信心。

| 题号 | 题目 | 难度 | 背景 & 学到什么 |
|---|---|---|---|
| 1 | [Two Sum 两数之和](https://leetcode.com/problems/two-sum/) | Easy | 算法面的"Hello World"。核心是**用哈希表把 O(n²) 暴力降到 O(n)**——一边遍历一边查"另一半是否出现过"。哈希换空间省时间的思维起点。 |
| 121 | [Best Time to Buy and Sell Stock 买卖股票最佳时机](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/) | Easy | 一次遍历维护"历史最低价"。是**贪心/一次扫描**的入门，也是后面动态规划状态机的雏形。 |
| 20 | [Valid Parentheses 有效的括号](https://leetcode.com/problems/valid-parentheses/) | Easy | **栈**的最经典应用：后进先出天然匹配嵌套结构。是所有"括号类""表达式类"题的地基。 |
| 70 | [Climbing Stairs 爬楼梯](https://leetcode.com/problems/climbing-stairs/) | Easy | **动态规划第一题**，本质是斐波那契。让你第一次体会"当前状态由前几个状态推出"。 |
| 206 | [Reverse Linked List 反转链表](https://leetcode.com/problems/reverse-linked-list/) | Easy | 链表面试出现率最高的操作，没有之一。务必把**迭代（三指针）和递归**两种写法都背到能默写。 |
| 160 | [Intersection of Two Linked Lists 相交链表](https://leetcode.com/problems/intersection-of-two-linked-lists/) | Easy | 双指针走两条链的巧妙构造（走到头切换到对方起点）。训练"用指针消除长度差"的思路。 |

---

## 阶段 1 · 双指针 & 滑动窗口（数组/字符串的核心武器）

字节非常爱考滑动窗口。掌握"右指针扩张、左指针收缩、窗口内维护一个统计量"这个模板，能一口气解决一大批题。

| 题号 | 题目 | 难度 | 背景 & 学到什么 |
|---|---|---|---|
| 3 | [Longest Substring Without Repeating Characters 无重复字符的最长子串](https://leetcode.com/problems/longest-substring-without-repeating-characters/) | Medium | **滑动窗口的标杆题**，字节高频中的高频。窗口内用哈希记录字符位置，遇重复就收缩左边界。必须滚瓜烂熟。 |
| 424 | [Longest Repeating Character Replacement 替换后的最长重复字符](https://leetcode.com/problems/longest-repeating-character-replacement/) | Medium | 进阶滑窗：窗口内允许 k 次替换。引入"窗口长度 - 最多字符出现次数 ≤ k"的判定，训练更抽象的窗口条件。 |
| 2134 | [Minimum Swaps to Group All 1's Together II 最少交换次数（环形）](https://leetcode.com/problems/minimum-swaps-to-group-all-1s-together-ii/) | Medium | 固定窗口大小 = 1 的总数，在**环形数组**上滑动找窗口内 0 最少。训练"环形 = 数组复制一份/取模"的处理技巧。 |

---

## 阶段 2 · 前缀和 & 区间（数组上的预处理思维）

| 题号 | 题目 | 难度 | 背景 & 学到什么 |
|---|---|---|---|
| 56 | [Merge Intervals 合并区间](https://leetcode.com/problems/merge-intervals/) | Medium | **区间题的母题**。先按起点排序，再线性扫描合并。所有区间合并/插入/重叠类问题都从这里派生。 |
| 560 | [Subarray Sum Equals K 和为 K 的子数组](https://leetcode.com/problems/subarray-sum-equals-k/) | Medium | **前缀和 + 哈希**的经典组合："和为 K 的子数组个数" = 查"前缀和之差等于 K"。把区间和问题转成两数之和。 |
| 939 | [Minimum Area Rectangle 最小面积矩形](https://leetcode.com/problems/minimum-area-rectangle/) | Medium | 用哈希存点集，枚举对角线两点反查另两点是否存在。训练"用集合做存在性查询"的建模。 |
| 1352 | [Product of the Last K Numbers 最后 K 个数的乘积](https://leetcode.com/problems/product-of-the-last-k-numbers/) | Medium | **前缀积**的设计题：用前缀乘积数组 O(1) 回答区间乘积，并巧妙处理 0。前缀和思想在乘法上的迁移。 |

---

## 阶段 3 · 栈（含单调栈，字节重点）

从普通栈过渡到**单调栈**——这是中高频考点，也是很多人的难点。

| 题号 | 题目 | 难度 | 背景 & 学到什么 |
|---|---|---|---|
| 394 | [Decode String 字符串解码](https://leetcode.com/problems/decode-string/) | Medium | 嵌套结构 `3[a2[c]]` 用栈处理。训练"遇到 `[` 入栈、遇到 `]` 出栈结算"的嵌套解析范式。 |
| 227 | [Basic Calculator II 基本计算器 II](https://leetcode.com/problems/basic-calculator-ii/) | Medium | 带 `+ - * × ÷` 的表达式求值。用栈处理运算符优先级。表达式求值是栈的硬核应用。 |
| 224 | [Basic Calculator 基本计算器](https://leetcode.com/problems/basic-calculator/) | Hard | 在上一题基础上加**括号**。用栈保存括号外的状态。两题连做，彻底吃透表达式求值。 |
| 402 | [Remove K Digits 移掉 K 位数字](https://leetcode.com/problems/remove-k-digits/) | Medium | **单调栈入门**：要让结果最小，就维护一个单调递增栈，遇到更小的就弹出前面更大的。 |
| 316 / 1081 | [Remove Duplicate Letters](https://leetcode.com/problems/remove-duplicate-letters/) / [Smallest Subsequence](https://leetcode.com/problems/smallest-subsequence-of-distinct-characters/) 去除重复字母 | Medium | 单调栈 + 去重 + "后面还有没有"的判断。难度陡升，是单调栈的综合训练。（两题是同一题的不同表述，做一道即可。） |
| 42 | [Trapping Rain Water 接雨水](https://leetcode.com/problems/trapping-rain-water/) | Hard | **算法面试史诗级名题**。三种解法（动态规划预处理、双指针、单调栈）都值得掌握，是双指针与单调栈的集大成者。 |

---

## 阶段 4 · 链表进阶（含设计题）

| 题号 | 题目 | 难度 | 背景 & 学到什么 |
|---|---|---|---|
| 92 | [Reverse Linked List II 反转链表 II](https://leetcode.com/problems/reverse-linked-list-ii/) | Medium | 反转**指定区间**。在 206 的基础上处理边界拼接，训练对链表指针的精细控制。 |
| 2 | [Add Two Numbers 两数相加](https://leetcode.com/problems/add-two-numbers/) | Medium | 链表模拟大数加法，处理进位。训练"哑结点（dummy head）"这个简化链表代码的关键技巧。 |
| 1171 | [Remove Zero Sum Consecutive Nodes 删除和为零的连续节点](https://leetcode.com/problems/remove-zero-sum-consecutive-nodes-from-linked-list/) | Medium | 前缀和思想搬到链表上 + 哈希存前缀和节点。把阶段 2 的思维和链表结合。 |
| 148 | [Sort List 排序链表](https://leetcode.com/problems/sort-list/) | Medium | 链表上做**归并排序**（要求 O(n log n)、O(1) 空间）。训练快慢指针找中点 + 归并。 |
| 146 | [LRU Cache LRU 缓存](https://leetcode.com/problems/lru-cache/) | Medium | **设计题之王，字节超高频**。哈希表 + 双向链表实现 O(1) 的 get/put。务必能徒手写出双向链表。面试常单独考。 |

---

## 阶段 4.5 · 设计题（O(1) 数据结构设计）

| 题号 | 题目 | 难度 | 背景 & 学到什么 |
|---|---|---|---|
| 380 | [Insert Delete GetRandom O(1)](https://leetcode.com/problems/insert-delete-getrandom-o1/) | Medium | 哈希表 + 动态数组的组合，实现增删查随机全 O(1)。关键技巧：**删除时把元素与末尾交换再弹出**。 |
| 2502 | [Design Memory Allocator 设计内存分配器](https://leetcode.com/problems/design-memory-allocator/) | Medium | 模拟内存分配/释放。考察你能否把一个工程问题翻译成清晰的数据结构操作，代码组织能力 > 算法难度。 |

---

## 阶段 5 · 二分查找（不只是"找一个数"）

| 题号 | 题目 | 难度 | 背景 & 学到什么 |
|---|---|---|---|
| 33 | [Search in Rotated Sorted Array 搜索旋转排序数组](https://leetcode.com/problems/search-in-rotated-sorted-array/) | Medium | **旋转数组二分**，字节高频。核心是"每次判断哪半边有序，再决定去哪边"。理解二分的本质是"排除一半"。 |
| 162 | [Find Peak Element 寻找峰值](https://leetcode.com/problems/find-peak-element/) | Medium | 在无序数组里二分找峰值——颠覆"二分必须有序"的认知。训练**用单调趋势做二分判定**。 |
| 240 | [Search a 2D Matrix II 搜索二维矩阵 II](https://leetcode.com/problems/search-a-2d-matrix-ii/) | Medium | 从右上角出发的"阶梯式查找"，每步排除一行或一列。训练换个起点把二维问题降维。 |

---

## 阶段 6 · 二叉树 & BST

| 题号 | 题目 | 难度 | 背景 & 学到什么 |
|---|---|---|---|
| 662 | [Maximum Width of Binary Tree 二叉树最大宽度](https://leetcode.com/problems/maximum-width-of-binary-tree/) | Medium | BFS 层序遍历 + 给节点编号（堆式下标）算宽度。训练把"位置信息"带进遍历。 |
| 450 | [Delete Node in a BST 删除二叉搜索树节点](https://leetcode.com/problems/delete-node-in-a-bst/) | Medium | BST 删除是经典难点：分"叶子/单子/双子"三种情况，双子时用后继替换。彻底理解 BST 性质。 |
| 1530 | [Number of Good Leaf Nodes Pairs 好叶子节点对的数量](https://leetcode.com/problems/number-of-good-leaf-nodes-pairs/) | Medium | 后序遍历 + 自底向上传递"各叶子到当前节点的距离分布"。训练较复杂的树形信息汇总。 |

---

## 阶段 7 · BFS / DFS / 图论（字节大重点，题量最多）

这是本题库占比最大的板块。先把网格 BFS/DFS 练熟，再上拓扑排序和并查集。

| 题号 | 题目 | 难度 | 背景 & 学到什么 |
|---|---|---|---|
| 200 | [Number of Islands 岛屿数量](https://leetcode.com/problems/number-of-islands/) | Medium | **网格搜索的母题**。遍历网格，遇到陆地就 DFS/BFS 淹没整片。所有"连通块"问题的起点。 |
| 994 | [Rotting Oranges 腐烂的橘子](https://leetcode.com/problems/rotting-oranges/) | Medium | **多源 BFS**：所有烂橘子同时入队，一层层扩散计时间。理解 BFS 天然算最短"层数"。 |
| 934 | [Shortest Bridge 最短的桥](https://leetcode.com/problems/shortest-bridge/) | Medium | DFS 标记一座岛 + BFS 向外扩张找最近的另一座岛。DFS 与 BFS 组合使用。 |
| 752 | [Open the Lock 打开转盘锁](https://leetcode.com/problems/open-the-lock/) | Medium | 把"密码状态"抽象成图的节点，BFS 找最短转动次数。训练**状态空间搜索**的建模思维（很重要）。 |
| 127 | [Word Ladder 单词接龙](https://leetcode.com/problems/word-ladder/) | Hard | 同样是状态图 BFS，节点是单词、边是"差一个字母"。建图与剪枝是难点，双向 BFS 可优化。 |
| 133 | [Clone Graph 克隆图](https://leetcode.com/problems/clone-graph/) | Medium | DFS/BFS 遍历 + 哈希表记录"原节点→新节点"映射防止重复。训练带备忘的图遍历。 |
| 207 | [Course Schedule 课程表](https://leetcode.com/problems/course-schedule/) | Medium | **拓扑排序入门**（判断有向图是否有环）。入度表 + BFS（Kahn 算法）。依赖关系类问题必备。 |
| 721 | [Accounts Merge 账户合并](https://leetcode.com/problems/accounts-merge/) | Medium | **并查集（Union-Find）经典题**：把同一人的邮箱合并成连通分量。务必掌握并查集模板（含路径压缩）。 |
| 128 | [Longest Consecutive Sequence 最长连续序列](https://leetcode.com/problems/longest-consecutive-sequence/) | Medium | 要求 O(n)。用哈希集合，只从"序列起点"开始数。也可用并查集。训练用哈希避免排序。 |
| 317 | [Shortest Distance from All Buildings 建筑物间最短距离](https://leetcode.com/problems/shortest-distance-from-all-buildings/) | Hard | 从每栋楼做一次 BFS，累加到每块空地的距离。多次 BFS + 剪枝，是网格 BFS 的综合应用。 |
| 1997 | [First Day Where You Have Been in All the Rooms 访问所有房间的首日](https://leetcode.com/problems/first-day-where-you-have-been-in-all-the-rooms/) | Medium | 表面是模拟，实则是**前缀和型动态规划**（推导每个房间被二次访问的天数递推式）。偏思维推导，可放靠后。 |

---

## 阶段 8 · 回溯（搜索所有可能解）

回溯有固定模板：**选择 → 递归 → 撤销选择**。四道题难度递进，吃透模板即可批量解决。

| 题号 | 题目 | 难度 | 背景 & 学到什么 |
|---|---|---|---|
| 78 | [Subsets 子集](https://leetcode.com/problems/subsets/) | Medium | **回溯模板的最干净示范**。枚举所有子集，理解"每个元素选或不选"的决策树。 |
| 39 | [Combination Sum 组合总和](https://leetcode.com/problems/combination-sum/) | Medium | 元素可重复选。引入"从当前下标开始"避免重复组合。回溯中"起始位置"的控制。 |
| 40 | [Combination Sum II 组合总和 II](https://leetcode.com/problems/combination-sum-ii/) | Medium | 元素不可重选 + **需要去重**（先排序，同层跳过相同值）。回溯去重是高频考点。 |
| 93 | [Restore IP Addresses 复原 IP 地址](https://leetcode.com/problems/restore-ip-addresses/) | Medium | 在字符串上回溯切分成 4 段并做合法性剪枝。训练带约束的分割型回溯。 |

---

## 阶段 9 · 动态规划（从线性到二维，循序渐进）

DP 是中高频且区分度高的板块。按"线性 → 序列 → 二维 → 区间 → 困难"的顺序爬。

| 题号 | 题目 | 难度 | 背景 & 学到什么 |
|---|---|---|---|
| 53 | [Maximum Subarray 最大子数组和](https://leetcode.com/problems/maximum-subarray/) | Medium | **Kadane 算法**：`dp[i] = max(nums[i], dp[i-1]+nums[i])`。最经典的线性 DP，必背。 |
| 198 | [House Robber 打家劫舍](https://leetcode.com/problems/house-robber/) | Medium | 经典"选或不选"线性 DP：`dp[i]=max(dp[i-1], dp[i-2]+nums[i])`。DP 状态转移的标准示范。 |
| 213 | [House Robber II 打家劫舍 II](https://leetcode.com/problems/house-robber-ii/) | Medium | 房子成环 → 拆成"偷第一间/不偷第一间"两次线性 DP。训练"环形问题拆成两个线性"。 |
| 55 | [Jump Game 跳跃游戏](https://leetcode.com/problems/jump-game/) | Medium | 贪心维护"能到达的最远位置"。DP 与贪心的分界点，理解何时贪心更优。 |
| 221 | [Maximal Square 最大正方形](https://leetcode.com/problems/maximal-square/) | Medium | **二维 DP 入门**：`dp[i][j]` = 以该点为右下角的最大正方形边长，由左/上/左上三者取 min+1。 |
| 1143 | [Longest Common Subsequence 最长公共子序列](https://leetcode.com/problems/longest-common-subsequence/) | Medium | **二维 DP 的标杆**，是编辑距离等一大类字符串 DP 的基础。务必理解二维状态表的填表过程。 |
| 5 | [Longest Palindromic Substring 最长回文子串](https://leetcode.com/problems/longest-palindromic-substring/) | Medium | 区间 DP 或"中心扩展"。字节高频。两种解法都建议掌握。 |
| 1235 | [Maximum Profit in Job Scheduling 规划工作以获最大收益](https://leetcode.com/problems/maximum-profit-in-job-scheduling/) | Hard | **DP + 二分 + 排序**的综合题：按结束时间排序，对每个工作二分找上一个不冲突的。区间 DP 进阶。 |
| 10 | [Regular Expression Matching 正则表达式匹配](https://leetcode.com/problems/regular-expression-matching/) | Hard | 二维 DP 困难题，`*` 和 `.` 的状态转移繁琐，是 DP 的硬骨头。建议全套路熟练后再攻。 |

---

## 阶段 10 · 堆 / Top K（优先队列）

| 题号 | 题目 | 难度 | 背景 & 学到什么 |
|---|---|---|---|
| 215 | [Kth Largest Element in an Array 数组中第 K 大](https://leetcode.com/problems/kth-largest-element-in-an-array/) | Medium | **Top K 母题**。小根堆（容量 K）或快速选择（quickselect）。两种解法都是高频考点。 |
| 347 | [Top K Frequent Elements 前 K 个高频元素](https://leetcode.com/problems/top-k-frequent-elements/) | Medium | 哈希计数 + 堆（或桶排序）。Top K 思路 + 频率统计的组合。 |
| 23 | [Merge k Sorted Lists 合并 K 个升序链表](https://leetcode.com/problems/merge-k-sorted-lists/) | Hard | 用最小堆每次取 K 条链表的最小头节点。堆在链表上的经典应用，字节高频。 |
| 407 | [Trapping Rain Water II 接雨水 II](https://leetcode.com/problems/trapping-rain-water-ii/) | Hard | 接雨水的二维版，用最小堆从边界向内"灌水"。三维空间想象 + 堆，难度高，放最后。 |

---

## 阶段 11 · 数学 & 字符串模拟（杂项收尾）

这类题算法不深，但**细节多、易写错**，考的是代码严谨度。

| 题号 | 题目 | 难度 | 背景 & 学到什么 |
|---|---|---|---|
| 3043 | [Find the Length of the Longest Common Prefix 最长公共前缀长度](https://leetcode.com/problems/find-the-length-of-the-longest-common-prefix/) | Medium | 用字典树（Trie）或哈希存前缀。可作为 **Trie** 的入门接触。 |
| 43 | [Multiply Strings 字符串相乘](https://leetcode.com/problems/multiply-strings/) | Medium | 大数乘法模拟，处理每位相乘的下标关系与进位。纯模拟，考耐心和细节。 |
| 68 | [Text Justification 文本左右对齐](https://leetcode.com/problems/text-justification/) | Hard | 难在繁琐的空格分配细节而非算法。是有名的"模拟地狱"，考代码组织与边界处理。 |

