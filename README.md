# What-s-up

北京理工 小学期 计算机基础实习 开发文档

成员：
- 彭程（项目管理，团队协调，文件与多媒体）
- 陈驭祺（前端框架，消息格式约定，前端通信）
- 李嘉政（后端通信，功能测试， debug）
- 黄子芯（后端框架，后端通信，个性化内容）
- 王奕诚（UI设计，功能测试，界面美化）

注：

- .gitignore中应当包含所有团队成员的个人配置文件和临时文件，使得个人配置和临时文件不会上传到公共仓库上。

  请各位自觉**将个人配置文件和临时文件的路径放入.gitignore中**。

  如何写.gitignore请见：[[Git\].gitignore文件的配置使用 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/52885189)

- 为了防止错误提交，已经开启main和dev分支的保护，**开发新功能应当使用feature/xxx分支**。

  在开发时，应当先把feature/xxx分支与dev分支同步，然后对feature/xxx分支进行开发。

  开发完毕时，应当再次把feature/xxx分支与dev分支同步，然后对dev分支发起pull request。

  若代码没问题，则pull request会通过，你的代码就会添加入dev分支。

  此时应当删除已经结束开发的feature/xxx分支。

  在dev分支到达一个大版本后，就会将其推送至main分支，作为正式的一个版本。

  具体细节请见：[一种适合小团队的Git协作流程 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/383067606)

- 开发环境：build_essential, cmake, QT 6.5.2, SQLite，QT MultiMedia，libpulse-dev（多媒体支持）。

  qt5以上自带SQLite驱动，因此不需安装SQLite驱动。

- QT文档：[Qt Overviews | Qt 6.5](https://doc.qt.io/qt-6/overviews-main.html)

  SQLite文档：[SQLite Documentation](https://www.sqlite.org/docs.html)

- 代码规范请参考[C++ 风格指南 - 内容目录 — Google 开源项目风格指南 (zh-google-styleguide.readthedocs.io)](https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/contents/)。

  由于该规范很长，不需要全部看完，只需**在不确定时参考文档**。

  一个例子：

  ```c++
  // .h 文件
  namespace mynamespace {
  
  // 所有声明都置于命名空间中
  // 注意不要使用缩进
  class MyClass {
      public:
      ...
      void Foo();
  };
  
  } // namespace mynamespace
  // .cc 文件（.cpp文件）
  namespace mynamespace {
  
  // 函数定义都置于命名空间中
  void MyClass::Foo() {
      ...
  }
  
  } // namespace mynamespace
  ```

- 老师提到了一些编程规范，请遵守：

  1. 传入数组时，**必须**判断数组长度是否超出缓冲区长度。
  2. 注意不要产生野指针。
  3. 使用双等号比较（如3==4）时，**必须**把右值写在左侧（如a==3应写成3==a）。
  4. 命名对象、变量等需要采用清晰明了的名字（英文单词组合），使得能够通过名字就推断出其功能。
  5. 写代码时请加入详细的代码注释。

- 测试文档：需要写的比较细，能够排查出各种问题。

  事先应当写好测试文档，并在测试过程中逐步完善测试文档。

- 团队协作：老师提到可以采用一个模块 **一人写代码+一人补充注释与测试** 的方法，可以考虑能力较强的同学写代码和简单注释，能力较弱的另一个同学补充注释与测试。前后端模块都可以采取这种模式。

  同一个模块的同学需要共同完成此模块的文档。

- What's up取名来自著名即时通信软件Whatsapp，并不是wechat，谢谢。
