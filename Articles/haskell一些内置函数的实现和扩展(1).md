
-- 取头元素
```haskell
head' :: [a] -> a
head' [] = error "empty list";
head' (x:xs) = x
```

取第二个元素
```haskell
headSecond :: [a] -> a
headSecond [] = error "empty list"
headSecond [x] = error "only one element"
headSecond [x,y] = y
headSecond (x:y:z) = headSecond [x,y]
```

-- 取最后一个元素
```haskell
last' :: [a] -> a
last' [] = error "empty list"
last' [x] = x
last' (x:xs) = last' xs
```

-- 注意：错误写法： last' (x:xs) = last' [xs]
-- 此处的被":" 的 xs 本来就是list

-- 取倒数第二个元素
```haskell
lastSecond :: [a] -> a
lastSecond [] = error "empty list"
lastSecond [x] = error "only one element"
lastSecond [x, y] = x
lastSecond (x:y:xs) = lastSecond (y:xs)
```

-- 此处的":" x,y是变量；xs是list
-- ch1 :: [a] ->  [b] 这里的变量必不能是一样的

-- 将头元素放至list的尾端
```haskell
ch1 :: [a] -> [a]
ch1 [] = error "empty list"
ch1 [x] = [x]
ch1 (x:xs) = xs ++ [x]
```

--删掉最后一个元素

```haskell
delLast :: [a] -> [a]
delLast [] = error "empty list"
delLast [x] = []
delLast (x:xs) = x : delLast xs
```

--将最后一个数字移至开头
```haskell
ch2 :: [a] -> [a]
ch2 [] = error "empty list"
ch2 [x] = [x]
ch2 (x:xs) = [last' xs] ++ delLast xs
```

--置换开头和最后一个元素

```haskell
ch3 :: [a] -> [a]
ch3 [] = error "empty list"
ch3 [x] = [x]
ch3 [x,y] = [y, x]
ch3 (x:y:xs) = [last' (y:xs)]  ++ delLast (y:xs) ++ [x]
```


```haskell
ch3' :: [a] -> [a]
ch3' [] = []
ch3' [x] = [x]
ch3' (x:xs) = 
    let (f, g) = swap x xs 
    in f:g
    where swap k [y] = (y, [k])
          swap k (y:ys) = let (n,m) = swap k ys in (n, y:m)
```

-- 删除数组中指定值

```haskell
delVal :: (Eq) a => a -> [a] -> [a]
delVal elem [] = []
delVal elem (x:xs)
 | elem == x = delVal elem xs
 | otherwise = x : delVal elem xs
```


--删除与第一个元素值相同的值

```haskell
get :: (Eq) a => [a] -> [a]
--get [] = error "empty list"
get [] = []
get (x:xs) = x : get ( delVal x xs )
```



```haskell
get1 :: (Eq) a => [a] -> [a]
--get [] = error "empty list"
get1 [] = []
get1 (x:xs)
 | delVal x xs == xs = x : get1 xs
 | otherwise = get1 ( delVal x xs )
```


```haskell
dump1 :: (Eq a) => [a] -> [a]
dump1 []  = []
dump1 [x] = [x]
dump1 (x:xs) = x: [k | k <- dump1(xs), k /= x]
```


--删除与第一个元素值相同的值,包括第一个元素

```haskell
dump2 :: (Eq a) => [a] -> [a]
dump2 [] = []
dump2 [x] = [x]
dump2 (x:xs)
    | [k | k <- xs, k==x] == []  =  x:(dump2 xs)
    | otherwise = dump2[k | k <- (xs) , k /= x]
```





