-------------------------------------------------------------------
--作者：Mega Show
--时间：2016.10.11
--说明：该源文件声明并定义了多个计算近似平方根的函数
-------------------------------------------------------------------
module NewtonRaphson where

--计算2的近似平方根，参数：x初值，n迭代次数
squareroot2 :: Float -> Integer -> Float
squareroot2 x 0 = x
squareroot2 x n = squareroot2 ((x+2/x)/2) (n-1)

--计算r的近似平方根，参数：r需开根数，x初值，n迭代次数
squareroot :: Float -> Float -> Integer -> Float
squareroot _ x 0 = x
squareroot r x n = squareroot r ((x+r/x)/2) (n-1)

--计算r的近似平方根，并将所有迭代结果作为序列返回
--参数：r需开根数，x初值
sqrtSeq :: Float -> Float -> [Float]
sqrtSeq r x = x : (sqrtSeq r ((x+r/x)/2))

--计算r的近似平方根，返回第一个前后近似值之差小于近似误差的近似平方根
--参数：r需开根数，x初值，epsilon近似误差
squareroot' :: Float -> Float -> Float -> Float
squareroot' r x 0 = ((x+r/x)/2)
squareroot' r x epsilon = if abs (x-(squareroot' r x 0))>epsilon
    then (squareroot' r (squareroot' r x 0) epsilon) else x


---------------------------------------------------------------------
--测试：
--  用r=2、r=3，x=1，n=3、n=4，epsilon=0.00005对所有函数进行了操作
---------------------------------------------------------------------
