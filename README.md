# 五子棋AI

## 项目内容

本项目是一个基于Alpha-beta剪枝算法的五子棋博弈程序，前端使用EGE图形库实现

![运行截图](https://github.com/wtupdl/Minimum_Spanning_Tree_Application_Examples/blob/master/img/%E6%9C%80%E5%B0%8F%E7%94%9F%E6%88%90%E6%A0%91.png)

## 操作方式

鼠标滚轮选择对抗模式，左键落子，右键悔棋

## 使用环境

CLion，EGE图形库

## 环境配置

运行前需要修改CMakeLists.txt文件中的ege图形库路径
[EGE图形库下载](https://xege.org/download/ege20.08_all.7z)
下载后解压，将文件夹拷贝到本地然后添加

```
#ege图形库导入，我的是F:/My_Clion/mycenv/EGE20.08
include_directories(F:/My_Clion/mycenv/EGE20.08/include)
link_directories(F:/My_Clion/mycenv/EGE20.08/lib/mingw64)
```

和

```
#ege图形库的包
target_link_libraries(Minimum_Spanning_Tree_Application_Examples libgraphics64.a
        libgdi32.a libimm32.a libmsimg32.a libole32.a
        liboleaut32.a libwinmm.a libuuid.a libgdiplus.a)
````

这个已经在CMakeLists.txt文中设置好了，只需修改下文件夹路径即可

