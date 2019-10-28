import sys
import os
def transform(filename):
    with open(filename, "r") as f:
        with open(filename + '.result', "w") as result:
            for line in f.readlines():
                temp = " ".join([str(x.strip().encode("gbk"))[2:-1].replace(r"\x", "") for x in line])
                result.writelines(temp)

if __name__ == "__main__":
    filename = sys.argv[1]
    if os.path.exists(filename) and os.path.isfile(filename):
        transform(filename)
        print("转换成功")
    else:
        print("文件不存在")