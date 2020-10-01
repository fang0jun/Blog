- [【写在前面】](#写在前面)
- [【项目有关】](#项目有关)
- [【工具与资源】](#工具与资源)
- [【运行步骤】](#运行步骤)

-------------------
# 【写在前面】
有时候对于开源项目来说能不能在自己电脑上跑起来, 直接决定了你有没有心情消化这些开源代码💢。很久以前就有过好几次阅读github开源项目的想法，但是由于有限的英文水平，有限的国内网络，和复杂庞大的代码，每次都是连代码都运行不了😥，看着一大片报错自然生不出读源码的念想，好几次被劝退。
因此这篇文章写给想要入坑github的新人们，帮助他们成功运行出第一个项目，获得入门的成就感

# 【项目有关】
halo，基于H2数据库的个人独立博客系统(可能是因为H2不需要单独安装，而MySQL得额外配置)，习惯写博客的同学可以把这个博客作为私人笔记本甚至是私人日记本

# 【工具与资源】
GitHub项目源码：https://github.com/halo-dev/halo
开发工具：IntelliJ IDEA
相关库与包与依赖：太多了...使用idea可以自动导入

# 【运行步骤】
**1**，登录github，尽量连接v/p/n，没有账号则进行注册

**2**，gihub界面左上角搜索 halo，而后选择最高星的首个项目
tip：这里有一个高级搜索的技巧：使用关键字 "in:description 关键词" + “star：>星数” 可以精准地搜索


![在这里插入图片描述](https://img-blog.csdnimg.cn/20200329161938752.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2ExMzM1MjkxMjYzMg==,size_16,color_FFFFFF,t_70)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200329162001765.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2ExMzM1MjkxMjYzMg==,size_16,color_FFFFFF,t_70)

**3**,  进入项目源码后，粗略地阅读代码文件，查看其项目结构和项目管理工具 
由倒数第4个文件bulid.gradle可以得知，halo系统是基于gradle管理的，其他项目管理工具还有xml

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200329162018942.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2ExMzM1MjkxMjYzMg==,size_16,color_FFFFFF,t_70)


**4**， 克隆源码
第一种方式：打开git命令行，输入：git clone https://github.com/halo-dev/halo.git
第二种方式：点击Download Zip，下载压缩包后解压


![在这里插入图片描述](https://img-blog.csdnimg.cn/20200329162053223.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2ExMzM1MjkxMjYzMg==,size_16,color_FFFFFF,t_70)
成功下载的最终项目文件：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200329162059999.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2ExMzM1MjkxMjYzMg==,size_16,color_FFFFFF,t_70)

**5**，打开idea，点击import project，输入项目文件的地址，再选择gradle启动（由第三步我们已经知道代码是基于gradle管理的）等待项目导入（第一次导入过程较慢）
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200329162316338.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2ExMzM1MjkxMjYzMg==,size_16,color_FFFFFF,t_70)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200329163558459.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2ExMzM1MjkxMjYzMg==,size_16,color_FFFFFF,t_70)
导入成功
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200329162125443.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2ExMzM1MjkxMjYzMg==,size_16,color_FFFFFF,t_70)

**6**，导入成功后点击右上角application(绿色箭头)，启动项目，启动时间长短与电脑配置好坏相关 

tip：若绿色箭头呈灰色无法点击 解决方案：右侧栏gradle ==》 Tasks ==》 application ==》 bootRun

![在这里插入图片描述](https://img-blog.csdnimg.cn/2020032916242883.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2ExMzM1MjkxMjYzMg==,size_16,color_FFFFFF,t_70)

**7**, 编译成功后，找到网址 ，在浏览器输入网址就大功告成了
tip：网址1：是供其他用户观看的网址。 网址2：是供自己(admin)管理博客的网址

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200329162406748.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2ExMzM1MjkxMjYzMg==,size_16,color_FFFFFF,t_70)



------------
**8**，我的报错与解决方案：

报错：打开网址后显示404![在这里插入图片描述](https://img-blog.csdnimg.cn/20200329162648868.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2ExMzM1MjkxMjYzMg==,size_16,color_FFFFFF,t_70)
bug位置：anatole子文件未成功下载导入
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200329162636232.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2ExMzM1MjkxMjYzMg==,size_16,color_FFFFFF,t_70)
解决方案：使用gitzip for githup(chrome插件) 或者 DownGit在原网站下载该文件后导入，这些工具可以指定只下载单个文件
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200329163726353.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2ExMzM1MjkxMjYzMg==,size_16,color_FFFFFF,t_70)

---------
【运行后展示】
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200329163001268.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2ExMzM1MjkxMjYzMg==,size_16,color_FFFFFF,t_70)![在这里插入图片描述](https://img-blog.csdnimg.cn/20200329162953913.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2ExMzM1MjkxMjYzMg==,size_16,color_FFFFFF,t_70)

-------
祝各位入坑愉快。