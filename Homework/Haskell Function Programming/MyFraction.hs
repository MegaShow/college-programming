-------------------------------------------------------------------
--作者：Mega Show
--时间：2016.10.11
--说明：该源文件定义分数类型Fraction，并实现了分数的加减乘除、以及
--      ratfloor、ratfloat、rateq等函数
-------------------------------------------------------------------
module MyFraction where
import Test.QuickCheck
import Prelude hiding ((<*>))

--定义分数类型(分子,分母)
type Fraction = (Integer,Integer)


--分数加法函数
ratplus :: Fraction -> Fraction -> Fraction
ratplus (a,b) (c,d) = (div (a*d+b*c) g,div (b*d) g)
    where g = gcd (a*d+b*c) (b*d)

--分数减法函数
ratminus :: Fraction -> Fraction -> Fraction
ratminus (a,b) (c,d) = (div (a*d-b*c) g,div (b*d) g)
    where g = gcd (a*d+b*c) (b*d)

--分数乘法函数
rattimes :: Fraction -> Fraction -> Fraction
rattimes (a,b) (c,d) = (div (a*c) g,div (b*d) g)
    where g = gcd (a*c) (b*d)

--分数除法函数
ratdiv :: Fraction -> Fraction -> Fraction
ratdiv (a,b) (c,d) = (div (a*d) g,div (b*c) g)
    where g = gcd (a*d) (b*c)


--将分数转换成不大于它的最大整数
ratfloor :: Fraction -> Integer
ratfloor (a,b) = (div a b)

--将分数转换成浮点数
ratfloat :: Fraction -> Float
ratfloat (a,b) = (fromInteger a / fromInteger b)

--判断分数是否相等
rateq :: Fraction -> Fraction -> Bool
rateq (a,b) (c,d) = if (a==c && b==d) then True else False


--中缀函数声明
(<+>) :: Fraction -> Fraction -> Fraction
(<+>) (a,b) (c,d) = ratplus (a,b) (c,d)

(<->) :: Fraction -> Fraction -> Fraction
(<->) (a,b) (c,d) = ratminus (a,b) (c,d)

(<*>) :: Fraction -> Fraction -> Fraction
(<*>) (a,b) (c,d) = rattimes (a,b) (c,d)

(</>) :: Fraction -> Fraction -> Fraction
(</>) (a,b) (c,d) = ratdiv (a,b) (c,d)

(<==>) :: Fraction -> Fraction -> Bool
(<==>) (a,b) (c,d) = rateq (a,b) (c,d)


------------------------------------------------------------------
--测试：
--  用(1,2),(2,5)对所有函数进行了操作
--困难：
--  不懂使用quickCheck
------------------------------------------------------------------
