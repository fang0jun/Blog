- [报错原因](#报错原因)
- [解决方案一](#解决方案一)
- [解决方案二](#解决方案二)
- [解决方案三](#解决方案三)



## 报错原因
 ! [rejected]        master -> master (fetch first)
error: failed to push some refs to 'https://github.com/fang0jun/myLeetCode.git'
hint: Updates were rejected because the remote contains work that you do
hint: not have locally. This is usually caused by another repository pushing
hint: to the same ref. You may want to first integrate the remote changes
hint: (e.g., 'git pull ...') before pushing again.
hint: See the 'Note about fast-forwards' in 'git push --help' for details.

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200917105757461.png#pic_center)

<font color='red'>**这本地仓库与线上仓库不一致产生的报错！**</font>


-------------

## 解决方案一
产生的原因是本地仓库与线上仓库的内容不匹配，或者说本地相对于远程不是最新，先pull更新本地，再把自己的push上去。** ps：如果不想代码清光光的话,切忌使用-f 强制push（希望人没事🙏）
<br/>
命令：
```cpp
git pull xxx(网址或者别名) xxx分支
```

## 解决方案二
若方案一为解决push仍然失败，尝试使用以下代码重新pull

命令：
```bash
git pull xxx(网址或者别名) xxx分支 --allow-unrelated-histories
```

## 解决方案三
若github项目提交失败，报错： master -> master (non-fast-forward)

命令
- 先执行git pull
- 然后再执行 git push --force origin master（代替git push origin master）