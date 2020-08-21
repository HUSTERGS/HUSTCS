.text
addi $s0,$0,0 # 0号寄存器用来存放当前预测的结果，即最终的数字，初始化为0
addi $s1,$0,-20000 # 1号寄存器用来存放10组中计算的最大值（目前为止），初始化为0
addi $s2,$0,0 # 2号寄存器用来存放当前正在计算的权重函数的累加值
addi $s3,$0,0 # 3号寄存器保存当前计算的权重值的偏移量[28, 28 + 10 * 784]
addi $s4,$0,0 # 用来存放当前计算的数字
# addi $s5,$0,0 # 5号寄存器存放全局计数器，[0 - 10 * 748)
addi $s6,$0,0 # 用户每一个输入的0/1值
addi $s7,$0,0 # 存放用户数据的偏移量[0, 784)
addi $t3,$0,0 
# --------------
addi $t1, $0, 3136 # t1初始值设置为784 * 4，t1的目的在于保存一个784 * 4常量

add $s3, $t1, $0 # s3设置为初始偏移量为784 * 4，即数字0所对应的第一个权重

start:
    lw $s6, 0($s7) # 载入用户像素点
    lw $t0, 0($s3) # 载入当前计算的权重
    beq $s6, $0, skip_add # 如果为0，则跳过加法
    add $s2, $s2, $t0 # 加上累加值
skip_add:
    addi $s7, $s7, 4 # 用户像素偏移量+1
    addi $s3, $s3, 4 # 数字权重偏移量+1
    bne $s7, $t1, start # 如果还没有到784，那么就继续

# 如果到了784的话，需要进行比较
slt $t2, $s2, $s1 # 如果当前值($s2)小于当前最大值($s1)
bne $t2, $0, continue # t2不等于0，说明确实小于，那么就需要跳过
add $s1, $s2, $0 # 更新当前最大值
add $s0, $s4, $0 # 更新预测数字

continue:
    addi $s2, $0, 0 # 重置累加值
    addi $s4, $s4, 1 # 当前计算的数字+1
    addi $t4, $0, 10 # t4存放常数10
    addi $s7, $0, 0 # 重置用户偏移量为0

    # -- 显示当前正在算哪一个数字
    add    $a0,$0,$s4       #display $s0
    addi   $v0,$0,34         # display hex
    syscall
    bne $s4, $t4, start # 如果当前计算的数字(s4)不等于10，也即还没有结束，那么就回到start，开始计算下一个数字的权重和

add    $a0,$0,$s0       #display $s0
addi   $v0,$0,34         # display hex
syscall

addi   $v0,$zero,50         # system call for exit
syscall                  # we are out of here.   


# single_num_weight_function: # 单个权重函数的计算
# single_byte: # 单行的计算
#     lw $s7,0($s4) # 保存第$s4行用户输入的数据（32位）到$s7
#     addi $s3,$s3,27 # 先取最低位
#     lw $t0,0($s3) # 目标权重的值放到$t0
#     andi $s6,$s7,1 # 通过与1进行与操作，取出当前位
#     beq $s6,$6, jump_add_action # 如果等于0，那么就直接跳过，不需要进行加法
#     add $s2,$s2,$t0 # 将$t0加到$s2
#     add $t1,$t1,1 
#     sub $s3,$s3,$t1 # s3减一
#     addi $t3,$t3,1 # t3加一
#     ; beq $t3,28, lulala # 如果t3的值到达28，说明结束
#     lw $t0,0($s3) # 目标权重的值放到$t0
#     srl $s7,$s7,1 # $7右移一位
#     andi $s6,$7,1 # 通过与1进行与操作，取出当前位
#     beq $s6,$6, jump_add_action
#     add $s2,$s2,$t0 # 将$t0加到$s2
#     add $t1,$t1,1
#     sub $s3,$s3,$t1 # s3减一
#     addi $t3,$t3,1 # t3加一


#     addi $t0,$0,0 # 偏移量
#     srl $6,$7,31 # 逻辑右移31位，由于没有实现SLRV，所以只能写字面量，5位立即数刚好可以支持32
#     andi $6,$6,1 
#     beq $6,$0, jump_add_action 
#     addi $s3
    
#     add $s2,$s2,$t0 # 将$t0加到$s2
# jump_add_action:
#     addi $s3,$s3,1 # $s3自增1
