--	实现len
```haskell
len' :: [a] -> a
len' [] = 0
len' (x: xs) = 1+len' xs
```

-- 实现求和Sum
```haskell
sum':: (Num a) => [a] -> a
sum' [] = 0;
sum' (x:xs) = x + sum' xs
```

-- 实现head,取list第一个数
```haskell
head' :: [a] -> a
head' [] = error "empty list"
head' (x:xs) = x
```

-- 取list第二个数

```haskell
headSecond' :: [a] -> a
headSecond' [] = error "empty list"
headSecond' [x] = error "only one element"
headSecond' [x, y] = [y]
headSecond' (x:y:xs) = y
```

-- 实现last 取最后一个数

```haskell
last' :: [a] -> a
last' [] = error "empty list"
last' [x] = [x]
last' (x:xs) = last' xs
```


-- 取list倒数第二个数

```haskell
lastSecond' :: [a] -> a
lastSecond' [] = error "empty list"
lastSecond' [x] = error "only one element"
lastSecond' [x,y] = x
lastSecond' (x:y:xs) =  lastSecond' (y:xs)
```

-- 将开头元素移至结尾部分

```haskell
ch1' :: [a] -> [a]
ch1' [] = []
ch1' [x] = [x]
ch1' (x:xs) = xs ++ [x]
```

-- 删除最后一个元素

```haskell
delLast' :: [a] -> [a]
delLast' [] = []
delLast' [x] = []
delLast' (x:xs) = x: delLast' xs
```

--将最后一个数字移至开头

```haskell
ch2 :: [a] -> [a]
ch2 [] = []
ch2 [x] = [x]
ch2 (x:xs) = [last' xs] ++ delLast(x:xs)
```

--置换开头和最后一个元素

```haskell
ch3 :: [a] -> [a]
ch3 [] = []
ch3 [x] = [x]
ch3 [x,y] = [y,x]
ch3 (x:y:xs) = [last' (y:xs)] ++ delLast(y:xs) ++ [x] 



-- 法二
ch3' :: [a] -> [a]
ch3' [] = []
ch3' [x] = [x]
ch3' (x:xs) = 
	let (f,g) = swap x xs in f:g -- 把xs 与 x 分别 放在(f, g)元组中（注意顺序）
    where swap k [y] = [y, [k]]
          swap k (y:ys) = let (n,m) = swap k ys in (n, y:m)

```

