# CodeForces 3C MegaShow 2017.2.12

# init
$arr = [[]]

# input
for i in 0..2
    $arr[i] = gets
end

#------------------------------------------------------------------------------
# check win
def check_win(char)
    for i in 0..2
        if $arr[i][0] == char and $arr[i][1] == char and $arr[i][2] == char
            return true
        end
    end
    for i in 0..2
        if $arr[0][i] == char and $arr[1][i] == char and $arr[2][i] == char
            return true
        end
    end
    if $arr[0][0] == char and $arr[1][1] == char and $arr[2][2] == char
        return true
    end
    if $arr[0][2] == char and $arr[1][1] == char and $arr[2][0] == char
        return true
    end
    return false
end

#------------------------------------------------------------------------------
# main
def main
    first_x = second_0 = 0
    first_win = check_win('X')
    second_win = check_win('0')

    for i in 0..2
        for j in 0..2
            if $arr[i][j] == 'X'
                first_x += 1
            elsif $arr[i][j] == '0'
                second_0 += 1
            end
        end
    end

    # judge
    if (first_win and first_x == second_0) or (second_win and first_x == second_0 + 1) or
                        first_x - second_0 > 1 or first_x < second_0
        print "illegal\n"
    elsif first_win
        print "the first player won\n"
    elsif second_win
        print "the second player won\n"
    elsif first_x + second_0 == 9
        print "draw\n"
    elsif first_x == second_0
        print "first\n"
    elsif first_x - second_0 == 1
        print "second\n"
    end
end

#start
main
