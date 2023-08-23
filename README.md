# What-s-up

北京理工 小学期 计算机基础实习 开发文档

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

- 开发环境：build_essential, cmake, QT 6.5.2

- QT文档：[Qt Overviews | Qt 6.5](https://doc.qt.io/qt-6/overviews-main.html)

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

- What's up取名来自著名即时通信软件Whatsapp，并不是wechat，谢谢。
