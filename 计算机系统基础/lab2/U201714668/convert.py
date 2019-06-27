import binascii
string = '0x20656854      0x6e6f6f6d        0x696e7520      0x69772074 \
      	0x62206c6c      0x69642065        0x65646976      0x6e692064 \
      0x74206f74      0x64206f77        0x73697669      0x736e6f69 \
      0x0000002e      0x21776f57        0x756f5920      0x20657627 \
      0x75666564      0x20646573        0x20656874      0x72636573'
for item in string.split():
	temp = hex(eval(item))[2:]
	print(str(binascii.a2b_hex(temp).decode())[::-1], end='')