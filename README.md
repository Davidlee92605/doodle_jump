# doodle_jump
  Use C++ implement a game named Doodle jump
# 1.應用名稱:
  Noodle Jump - 麵團跳躍
# 2.細節描述:

玩家操控一隻名為“Noodle”(​麵團，表NTHU出產的doodle​ )之四腳動物，在一個永無休止的平台上一直跳高。如果Noodle落下，則遊戲結束;跳得越高，分數便越高。
# 3.主架構:
![image](https://github.com/Davidlee92605/doodle_jump/blob/master/%E8%9E%A2%E5%B9%95%E5%BF%AB%E7%85%A7%202019-09-17%20%E4%B8%8B%E5%8D%8811.01.53.png)
 
# 4.Class 列表與簡介:
  1. Noodler:角色的父類別，將來會產生多個子類別(不同造型)
  2. Platform:大平台的父類別，將會帶來產生滿滿的子類別(不同特性的平台ex:
  斷裂、變色)
  3. Tool : 遊戲中的道具，對遊戲進行有不同功能(ex:火箭筒)
  4. Menu: 選單類別，負責處理遊戲內部的參數調控，以及反應前端圖形畫面
  5. Level: 關卡類別，負責關卡的參數設定(難度、場景等等)
  6. Slider: 調控類別，設置在遊戲中，負責調整背景音樂與效果音樂
 
