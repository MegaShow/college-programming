---------------------------------------------------------------------------------------
-- Name: Lab3.hs
-- Author: Mega Show
-- About:
---------------------------------------------------------------------------------------

module Lab3 where
import Data.List

--定义Prop类型
data Prop = Const Bool | Var Char | Not Prop | And Prop Prop
    | Or Prop Prop | Imply Prop Prop
    deriving Eq

--定义Subst类型
type Subst = [(Char, Bool)]

--test,测试使用的数据
lis :: Subst
lis = [('A', True),('B', False)]


--------------------------------------------------------------------------------
-- 习题1  将Prop定义成类Show的实例
--------------------------------------------------------------------------------
--Show实例
instance Show Prop where
    show (Const n) = show n
    show (Var n) = [n]
    show (Not n) = "~" ++ show n
    show (And e1 e2) = (show e1) ++ " && " ++ (show e2)
    show (Or e1 e2) = (show e1) ++ " || " ++ (show e2)
    show (Imply e1 e2) = (show e1) ++ " => " ++ (show e2)


--------------------------------------------------------------------------------
-- 习题2  定义p1 p2 p3值
--------------------------------------------------------------------------------
--let p1,p2,p3
p1,p2,p3 :: Prop
p1 = (And (Var 'A') (Not (Var 'A')))
p2 = (Or (Var 'A') (Not (Var 'A')))
p3 = (Imply (Var 'A') (And (Var 'A') (Var 'B')))


--------------------------------------------------------------------------------
-- 习题3  定义eval函数
--------------------------------------------------------------------------------
--在Subst里面通过Char取值Bool
getvar :: Subst -> Char -> Bool
getvar (x:xs) c = if (fst x) == c then (snd x) else (getvar xs c)
--getvar (x:xs) (fst x) = snd x
--getvar (x:xs) c = getvar xs c

--求最终真值
eval :: Subst -> Prop -> Bool
eval xs (Const n) = n
eval xs (Var n) = getvar xs n
eval xs (Not n) =  not (eval xs n)
eval xs (And e1 e2) = (eval xs e1) && (eval xs e2)
eval xs (Or e1 e2) = (eval xs e1) || (eval xs e2)
eval xs (Imply e1 e2) = if (eval xs e1) == (eval xs e2) then True else False


--------------------------------------------------------------------------------
-- 习题4  定义vars substs函数
--------------------------------------------------------------------------------
--获取Prop里面的所有变元(可重复)
getarr :: Prop -> [Char]
getarr (Const n) = []
getarr (Var n) = [n]
getarr (Not n) = vars n
getarr (And e1 e2) = (vars e1) ++ (vars e2)
getarr (Or e1 e2) = (vars e1) ++ (vars e2)
getarr (Imply e1 e2) = (vars e1) ++ (vars e2)

--获取Prop里面的所有不同的变元
vars :: Prop -> [Char]
vars n = nub (getarr n)

--获取Prop里面的所有可能的代换(真正函数)
getsubst :: [Char] -> [Subst]
getsubst [c] = [ [ (c,True) ] ] ++ [ [ (c,False) ] ]
getsubst (c:str) = [ (c,True):n | n <- (getsubst str)]
               ++ [ (c,False):n | n <- (getsubst str)]

--获取Prop里面的所有可能的代换
substs :: Prop -> [Subst]
substs n = getsubst (vars n)


--------------------------------------------------------------------------------
-- 习题5  定义isTaut函数
--------------------------------------------------------------------------------
--判断是否永远为真
judge :: Prop -> [Subst] -> Bool
judge n [] = True
judge n (x:xs) = (eval x n) && (judge n xs)

--判断是否永远为真的函数入口
isTaut :: Prop -> Bool
isTaut n = judge n (substs n)
