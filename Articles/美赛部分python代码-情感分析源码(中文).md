粗浅地突击学习了一点点自然语言处理，在文章里会分析python实现的文本情感分析代码，

**代码功能**：分析一句话(中文)里蕴含的正面情绪和负面情绪并评分，最后返回正负面情绪的总分，平均分，标准差


**写在前面**：
其实实现的思路很清晰：分词 - 词语分析(正面词/负面词/程度词/否定词)  - 按打分规则评分

 
 --------
|| 导入jieba库和numpy矩阵
```python
import jieba
import numpy as np
```
|| 打开词典文件，返回列表

```python
def open_dict(Dict = 'hahah', path=r'/Users/86133/乱七八糟的代码们/python/Textming/'):
    path = path + '%s.txt' % Dict
    dictionary = open(path, 'r', encoding='utf-8')
    dict = []
    for word in dictionary:
        word = word.strip('\n')
        dict.append(word)
    return dict
```

|| 将自己的中文语料文本导入（这里你要修改path路径）。
```python
deny_word = open_dict(Dict = '否定词', path= r'/Users/86133/乱七八糟的代码们/python/Textming/')
posdict = open_dict(Dict = 'positive', path= r'/Users/86133/乱七八糟的代码们/python/Textming/')
negdict = open_dict(Dict = 'negative', path= r'/Users/86133/乱七八糟的代码们/python/Textming/')
degree_word = open_dict(Dict = '程度级别词语', path= r'/Users/86133/乱七八糟的代码们/python/Textming/'
```

|| 针对程度词细分程度：extreme，very，more，ish，last  （tips：用以划分的标志词需要在程度词文本中写入）
```python
mostdict = degree_word[degree_word.index('extreme')+1 : degree_word.index('very')]#权重4，即在情感词前乘以4
verydict = degree_word[degree_word.index('very')+1 : degree_word.index('more')]#权重3
moredict = degree_word[degree_word.index('more')+1 : degree_word.index('ish')]#权重2
ishdict = degree_word[degree_word.index('ish')+1 : degree_word.index('last')]#权重0.5
```

|| 核心代码：评分逻辑
```python
def judgeodd(num):
    if (num % 2) == 0:
        return 'even'
    else:
        return 'odd'

def sentiment_score_list(dataset):
    seg_sentence = dataset.split('％％％')

    count1 = []
    count2 = []
    for sen in seg_sentence: #循环遍历每一个评论
        segtmp = jieba.lcut(sen, cut_all=False)  #把句子进行分词，以列表的形式返回
        i = 0 #记录扫描到的词的位置
        a = 0 #记录情感词的位置
        poscount = 0 #积极词的第一次分值
        poscount2 = 0 #积极词反转后的分值
        poscount3 = 0 #积极词的最后分值（包括叹号的分值）
        negcount = 0
        negcount2 = 0
        negcount3 = 0
        for word in segtmp:
            if word in posdict:  # 判断词语是否是情感词
                poscount += 1
                c = 0
                for w in segtmp[a:i]:  # 扫描情感词前的程度词
                    if w in mostdict:
                        poscount *= 4.0
                    elif w in verydict:
                        poscount *= 3.0
                    elif w in moredict:
                        poscount *= 2.0
                    elif w in ishdict:
                        poscount *= 0.5
                    elif w in deny_word:
                        c += 1
                if judgeodd(c) == 'odd':  # 扫描情感词前的否定词数
                    poscount *= -1.0
                    poscount2 += poscount
                    poscount = 0
                    poscount3 = poscount + poscount2 + poscount3
                    poscount2 = 0
                else:
                    poscount3 = poscount + poscount2 + poscount3
                    poscount = 0
                a = i + 1  # 情感词的位置变化

            elif word in negdict:  # 消极情感的分析，与上面一致
                negcount += 1
                d = 0
                for w in segtmp[a:i]:
                    if w in mostdict:
                        negcount *= 4.0
                    elif w in verydict:
                        negcount *= 3.0
                    elif w in moredict:
                        negcount *= 2.0
                    elif w in ishdict:
                        negcount *= 0.5
                    elif w in degree_word:
                        d += 1
                if judgeodd(d) == 'odd':
                    negcount *= -1.0
                    negcount2 += negcount
                    negcount = 0
                    negcount3 = negcount + negcount2 + negcount3
                    negcount2 = 0
                else:
                    negcount3 = negcount + negcount2 + negcount3
                    negcount = 0
                a = i + 1
            elif word == '！' or word == '!':  ##判断句子是否有感叹号
                for w2 in segtmp[::-1]:  # 扫描感叹号前的情感词，发现后权值+2，然后退出循环
                    if w2 in posdict or negdict:
                        poscount3 += 2
                        negcount3 += 2
                        break
            i += 1 # 扫描词位置前移


            # 以下是防止出现负数的情况
            pos_count = 0
            neg_count = 0
            if poscount3 < 0 and negcount3 > 0:
                neg_count += negcount3 - poscount3
                pos_count = 0
            elif negcount3 < 0 and poscount3 > 0:
                pos_count = poscount3 - negcount3
                neg_count = 0
            elif poscount3 < 0 and negcount3 < 0:
                neg_count = -poscount3
                pos_count = -negcount3
            else:
                pos_count = poscount3
                neg_count = negcount3

            count1.append([pos_count, neg_count])
        count2.append(count1)
        count1 = []

    return count2
```
|| 数据汇总

	为每句话创建一个矩阵，矩阵中每行代表一句话按规则划分出的一系列词组，每列代表这些词组的各项打分，
	对这些矩阵中的数据进行列求和操作( 即针对一句话的每一个部分的评分进行汇总），最后结果使用一维数组返回
	
>若将需要计算的数据放入二维数组中，将出现TypeError: list indices must be integers or slices, not tuple的报错因为在python中列表中的每一个元素大小可能不同，因此不能直接取其某一列进行操作应该利用numpy.array函数将其转变为标准矩阵，再对其进行取某一列的操作
```python
def sentiment_score(senti_score_list):
    score = []
    i = 0
    for review in senti_score_list:
        i = i + 1
        score_array = np.array(review)
        Pos = np.sum(score_array[:, 0])
        Neg = np.sum(score_array[:, 1])
        AvgPos = np.mean(score_array[:, 0])
        AvgPos = float('%.1f'%AvgPos)
        AvgNeg = np.mean(score_array[:, 1])
        AvgNeg = float('%.1f'%AvgNeg)
        StdPos = np.std(score_array[:, 0])
        StdPos = float('%.1f'%StdPos)
        StdNeg = np.std(score_array[:, 1])
        StdNeg = float('%.1f'%StdNeg)
        score.append([Pos, Neg, AvgPos, AvgNeg, StdPos, StdNeg])

    return score
```

|| 测试代码
```python
data = """这个做的不行！！"""
data2 = """你做的真好真不错！"""
arr = sentiment_score(sentiment_score_list(data))
for x in range(len(arr)):
        print(arr[x])
```
