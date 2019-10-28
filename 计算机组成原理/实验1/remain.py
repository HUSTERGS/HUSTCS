def divide(divide_num, Gx):
    Gx = [int(x) for x in Gx]
    if divide_num[0] == 1:
        return [divide_num[i] ^ Gx[i] for i in range(len(Gx))][1:]
    else:
        return [divide_num[i] ^ 0 for i in range(len(Gx))][1:]

def gen(digit, Gx):
    # 一共有digit位
    g_len = len(Gx) # Gx的位数
    result = [1, ] + (g_len - 1) * [0, ]
    
    for i in range(digit):
        print(i+1)
        temp = "".join(str(x) for x in ([0, ] * (digit - i - 1) + [1, ] + [0, ] * i))
        print(temp, end=': ')
        result = divide(result + [0, ], Gx)
        
        # print(result)
        print("".join(str(x) for x in result), end=': ')
        print(hex(eval('0b' + "".join(str(x) for x in result))))
gen(16, '100101')
