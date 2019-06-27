
./bufbomb:     file format elf32-i386


Disassembly of section .init:

08048878 <_init>:
 8048878:	55                   	push   %ebp
 8048879:	89 e5                	mov    %esp,%ebp
 804887b:	53                   	push   %ebx
 804887c:	83 ec 04             	sub    $0x4,%esp
 804887f:	e8 00 00 00 00       	call   8048884 <_init+0xc>
 8048884:	5b                   	pop    %ebx
 8048885:	81 c3 7c 28 00 00    	add    $0x287c,%ebx
 804888b:	8b 93 fc ff ff ff    	mov    -0x4(%ebx),%edx
 8048891:	85 d2                	test   %edx,%edx
 8048893:	74 05                	je     804889a <_init+0x22>
 8048895:	e8 e6 00 00 00       	call   8048980 <__gmon_start__@plt>
 804889a:	58                   	pop    %eax
 804889b:	5b                   	pop    %ebx
 804889c:	c9                   	leave  
 804889d:	c3                   	ret    

Disassembly of section .plt:

080488a0 <.plt>:
 80488a0:	ff 35 04 b1 04 08    	pushl  0x804b104
 80488a6:	ff 25 08 b1 04 08    	jmp    *0x804b108
 80488ac:	00 00                	add    %al,(%eax)
	...

080488b0 <read@plt>:
 80488b0:	ff 25 0c b1 04 08    	jmp    *0x804b10c
 80488b6:	68 00 00 00 00       	push   $0x0
 80488bb:	e9 e0 ff ff ff       	jmp    80488a0 <.plt>

080488c0 <srandom@plt>:
 80488c0:	ff 25 10 b1 04 08    	jmp    *0x804b110
 80488c6:	68 08 00 00 00       	push   $0x8
 80488cb:	e9 d0 ff ff ff       	jmp    80488a0 <.plt>

080488d0 <printf@plt>:
 80488d0:	ff 25 14 b1 04 08    	jmp    *0x804b114
 80488d6:	68 10 00 00 00       	push   $0x10
 80488db:	e9 c0 ff ff ff       	jmp    80488a0 <.plt>

080488e0 <memcpy@plt>:
 80488e0:	ff 25 18 b1 04 08    	jmp    *0x804b118
 80488e6:	68 18 00 00 00       	push   $0x18
 80488eb:	e9 b0 ff ff ff       	jmp    80488a0 <.plt>

080488f0 <signal@plt>:
 80488f0:	ff 25 1c b1 04 08    	jmp    *0x804b11c
 80488f6:	68 20 00 00 00       	push   $0x20
 80488fb:	e9 a0 ff ff ff       	jmp    80488a0 <.plt>

08048900 <alarm@plt>:
 8048900:	ff 25 20 b1 04 08    	jmp    *0x804b120
 8048906:	68 28 00 00 00       	push   $0x28
 804890b:	e9 90 ff ff ff       	jmp    80488a0 <.plt>

08048910 <_IO_getc@plt>:
 8048910:	ff 25 24 b1 04 08    	jmp    *0x804b124
 8048916:	68 30 00 00 00       	push   $0x30
 804891b:	e9 80 ff ff ff       	jmp    80488a0 <.plt>

08048920 <fwrite@plt>:
 8048920:	ff 25 28 b1 04 08    	jmp    *0x804b128
 8048926:	68 38 00 00 00       	push   $0x38
 804892b:	e9 70 ff ff ff       	jmp    80488a0 <.plt>

08048930 <bcopy@plt>:
 8048930:	ff 25 2c b1 04 08    	jmp    *0x804b12c
 8048936:	68 40 00 00 00       	push   $0x40
 804893b:	e9 60 ff ff ff       	jmp    80488a0 <.plt>

08048940 <strcpy@plt>:
 8048940:	ff 25 30 b1 04 08    	jmp    *0x804b130
 8048946:	68 48 00 00 00       	push   $0x48
 804894b:	e9 50 ff ff ff       	jmp    80488a0 <.plt>

08048950 <getpid@plt>:
 8048950:	ff 25 34 b1 04 08    	jmp    *0x804b134
 8048956:	68 50 00 00 00       	push   $0x50
 804895b:	e9 40 ff ff ff       	jmp    80488a0 <.plt>

08048960 <gethostname@plt>:
 8048960:	ff 25 38 b1 04 08    	jmp    *0x804b138
 8048966:	68 58 00 00 00       	push   $0x58
 804896b:	e9 30 ff ff ff       	jmp    80488a0 <.plt>

08048970 <puts@plt>:
 8048970:	ff 25 3c b1 04 08    	jmp    *0x804b13c
 8048976:	68 60 00 00 00       	push   $0x60
 804897b:	e9 20 ff ff ff       	jmp    80488a0 <.plt>

08048980 <__gmon_start__@plt>:
 8048980:	ff 25 40 b1 04 08    	jmp    *0x804b140
 8048986:	68 68 00 00 00       	push   $0x68
 804898b:	e9 10 ff ff ff       	jmp    80488a0 <.plt>

08048990 <exit@plt>:
 8048990:	ff 25 44 b1 04 08    	jmp    *0x804b144
 8048996:	68 70 00 00 00       	push   $0x70
 804899b:	e9 00 ff ff ff       	jmp    80488a0 <.plt>

080489a0 <srand@plt>:
 80489a0:	ff 25 48 b1 04 08    	jmp    *0x804b148
 80489a6:	68 78 00 00 00       	push   $0x78
 80489ab:	e9 f0 fe ff ff       	jmp    80488a0 <.plt>

080489b0 <mmap@plt>:
 80489b0:	ff 25 4c b1 04 08    	jmp    *0x804b14c
 80489b6:	68 80 00 00 00       	push   $0x80
 80489bb:	e9 e0 fe ff ff       	jmp    80488a0 <.plt>

080489c0 <__libc_start_main@plt>:
 80489c0:	ff 25 50 b1 04 08    	jmp    *0x804b150
 80489c6:	68 88 00 00 00       	push   $0x88
 80489cb:	e9 d0 fe ff ff       	jmp    80488a0 <.plt>

080489d0 <write@plt>:
 80489d0:	ff 25 54 b1 04 08    	jmp    *0x804b154
 80489d6:	68 90 00 00 00       	push   $0x90
 80489db:	e9 c0 fe ff ff       	jmp    80488a0 <.plt>

080489e0 <getopt@plt>:
 80489e0:	ff 25 58 b1 04 08    	jmp    *0x804b158
 80489e6:	68 98 00 00 00       	push   $0x98
 80489eb:	e9 b0 fe ff ff       	jmp    80488a0 <.plt>

080489f0 <strcasecmp@plt>:
 80489f0:	ff 25 5c b1 04 08    	jmp    *0x804b15c
 80489f6:	68 a0 00 00 00       	push   $0xa0
 80489fb:	e9 a0 fe ff ff       	jmp    80488a0 <.plt>

08048a00 <__isoc99_sscanf@plt>:
 8048a00:	ff 25 60 b1 04 08    	jmp    *0x804b160
 8048a06:	68 a8 00 00 00       	push   $0xa8
 8048a0b:	e9 90 fe ff ff       	jmp    80488a0 <.plt>

08048a10 <memset@plt>:
 8048a10:	ff 25 64 b1 04 08    	jmp    *0x804b164
 8048a16:	68 b0 00 00 00       	push   $0xb0
 8048a1b:	e9 80 fe ff ff       	jmp    80488a0 <.plt>

08048a20 <__strdup@plt>:
 8048a20:	ff 25 68 b1 04 08    	jmp    *0x804b168
 8048a26:	68 b8 00 00 00       	push   $0xb8
 8048a2b:	e9 70 fe ff ff       	jmp    80488a0 <.plt>

08048a30 <__errno_location@plt>:
 8048a30:	ff 25 6c b1 04 08    	jmp    *0x804b16c
 8048a36:	68 c0 00 00 00       	push   $0xc0
 8048a3b:	e9 60 fe ff ff       	jmp    80488a0 <.plt>

08048a40 <rand@plt>:
 8048a40:	ff 25 70 b1 04 08    	jmp    *0x804b170
 8048a46:	68 c8 00 00 00       	push   $0xc8
 8048a4b:	e9 50 fe ff ff       	jmp    80488a0 <.plt>

08048a50 <munmap@plt>:
 8048a50:	ff 25 74 b1 04 08    	jmp    *0x804b174
 8048a56:	68 d0 00 00 00       	push   $0xd0
 8048a5b:	e9 40 fe ff ff       	jmp    80488a0 <.plt>

08048a60 <sprintf@plt>:
 8048a60:	ff 25 78 b1 04 08    	jmp    *0x804b178
 8048a66:	68 d8 00 00 00       	push   $0xd8
 8048a6b:	e9 30 fe ff ff       	jmp    80488a0 <.plt>

08048a70 <socket@plt>:
 8048a70:	ff 25 7c b1 04 08    	jmp    *0x804b17c
 8048a76:	68 e0 00 00 00       	push   $0xe0
 8048a7b:	e9 20 fe ff ff       	jmp    80488a0 <.plt>

08048a80 <random@plt>:
 8048a80:	ff 25 80 b1 04 08    	jmp    *0x804b180
 8048a86:	68 e8 00 00 00       	push   $0xe8
 8048a8b:	e9 10 fe ff ff       	jmp    80488a0 <.plt>

08048a90 <gethostbyname@plt>:
 8048a90:	ff 25 84 b1 04 08    	jmp    *0x804b184
 8048a96:	68 f0 00 00 00       	push   $0xf0
 8048a9b:	e9 00 fe ff ff       	jmp    80488a0 <.plt>

08048aa0 <connect@plt>:
 8048aa0:	ff 25 88 b1 04 08    	jmp    *0x804b188
 8048aa6:	68 f8 00 00 00       	push   $0xf8
 8048aab:	e9 f0 fd ff ff       	jmp    80488a0 <.plt>

08048ab0 <close@plt>:
 8048ab0:	ff 25 8c b1 04 08    	jmp    *0x804b18c
 8048ab6:	68 00 01 00 00       	push   $0x100
 8048abb:	e9 e0 fd ff ff       	jmp    80488a0 <.plt>

08048ac0 <calloc@plt>:
 8048ac0:	ff 25 90 b1 04 08    	jmp    *0x804b190
 8048ac6:	68 08 01 00 00       	push   $0x108
 8048acb:	e9 d0 fd ff ff       	jmp    80488a0 <.plt>

Disassembly of section .text:

08048ad0 <_start>:
 8048ad0:	31 ed                	xor    %ebp,%ebp
 8048ad2:	5e                   	pop    %esi
 8048ad3:	89 e1                	mov    %esp,%ecx
 8048ad5:	83 e4 f0             	and    $0xfffffff0,%esp
 8048ad8:	50                   	push   %eax
 8048ad9:	54                   	push   %esp
 8048ada:	52                   	push   %edx
 8048adb:	68 20 a0 04 08       	push   $0x804a020
 8048ae0:	68 30 a0 04 08       	push   $0x804a030
 8048ae5:	51                   	push   %ecx
 8048ae6:	56                   	push   %esi
 8048ae7:	68 19 90 04 08       	push   $0x8049019
 8048aec:	e8 cf fe ff ff       	call   80489c0 <__libc_start_main@plt>
 8048af1:	f4                   	hlt    
 8048af2:	90                   	nop
 8048af3:	90                   	nop
 8048af4:	90                   	nop
 8048af5:	90                   	nop
 8048af6:	90                   	nop
 8048af7:	90                   	nop
 8048af8:	90                   	nop
 8048af9:	90                   	nop
 8048afa:	90                   	nop
 8048afb:	90                   	nop
 8048afc:	90                   	nop
 8048afd:	90                   	nop
 8048afe:	90                   	nop
 8048aff:	90                   	nop

08048b00 <deregister_tm_clones>:
 8048b00:	b8 d7 c1 04 08       	mov    $0x804c1d7,%eax
 8048b05:	2d d4 c1 04 08       	sub    $0x804c1d4,%eax
 8048b0a:	83 f8 06             	cmp    $0x6,%eax
 8048b0d:	77 02                	ja     8048b11 <deregister_tm_clones+0x11>
 8048b0f:	f3 c3                	repz ret 
 8048b11:	b8 00 00 00 00       	mov    $0x0,%eax
 8048b16:	85 c0                	test   %eax,%eax
 8048b18:	74 f5                	je     8048b0f <deregister_tm_clones+0xf>
 8048b1a:	55                   	push   %ebp
 8048b1b:	89 e5                	mov    %esp,%ebp
 8048b1d:	83 ec 18             	sub    $0x18,%esp
 8048b20:	c7 04 24 d4 c1 04 08 	movl   $0x804c1d4,(%esp)
 8048b27:	ff d0                	call   *%eax
 8048b29:	c9                   	leave  
 8048b2a:	c3                   	ret    
 8048b2b:	90                   	nop
 8048b2c:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi

08048b30 <register_tm_clones>:
 8048b30:	b8 d4 c1 04 08       	mov    $0x804c1d4,%eax
 8048b35:	2d d4 c1 04 08       	sub    $0x804c1d4,%eax
 8048b3a:	c1 f8 02             	sar    $0x2,%eax
 8048b3d:	89 c2                	mov    %eax,%edx
 8048b3f:	c1 ea 1f             	shr    $0x1f,%edx
 8048b42:	01 d0                	add    %edx,%eax
 8048b44:	d1 f8                	sar    %eax
 8048b46:	75 02                	jne    8048b4a <register_tm_clones+0x1a>
 8048b48:	f3 c3                	repz ret 
 8048b4a:	ba 00 00 00 00       	mov    $0x0,%edx
 8048b4f:	85 d2                	test   %edx,%edx
 8048b51:	74 f5                	je     8048b48 <register_tm_clones+0x18>
 8048b53:	55                   	push   %ebp
 8048b54:	89 e5                	mov    %esp,%ebp
 8048b56:	83 ec 18             	sub    $0x18,%esp
 8048b59:	89 44 24 04          	mov    %eax,0x4(%esp)
 8048b5d:	c7 04 24 d4 c1 04 08 	movl   $0x804c1d4,(%esp)
 8048b64:	ff d2                	call   *%edx
 8048b66:	c9                   	leave  
 8048b67:	c3                   	ret    
 8048b68:	90                   	nop
 8048b69:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi

08048b70 <__do_global_dtors_aux>:
 8048b70:	80 3d 04 c2 04 08 00 	cmpb   $0x0,0x804c204
 8048b77:	75 13                	jne    8048b8c <__do_global_dtors_aux+0x1c>
 8048b79:	55                   	push   %ebp
 8048b7a:	89 e5                	mov    %esp,%ebp
 8048b7c:	83 ec 08             	sub    $0x8,%esp
 8048b7f:	e8 7c ff ff ff       	call   8048b00 <deregister_tm_clones>
 8048b84:	c6 05 04 c2 04 08 01 	movb   $0x1,0x804c204
 8048b8b:	c9                   	leave  
 8048b8c:	f3 c3                	repz ret 
 8048b8e:	66 90                	xchg   %ax,%ax

08048b90 <frame_dummy>:
 8048b90:	a1 08 b0 04 08       	mov    0x804b008,%eax
 8048b95:	85 c0                	test   %eax,%eax
 8048b97:	74 1e                	je     8048bb7 <frame_dummy+0x27>
 8048b99:	b8 00 00 00 00       	mov    $0x0,%eax
 8048b9e:	85 c0                	test   %eax,%eax
 8048ba0:	74 15                	je     8048bb7 <frame_dummy+0x27>
 8048ba2:	55                   	push   %ebp
 8048ba3:	89 e5                	mov    %esp,%ebp
 8048ba5:	83 ec 18             	sub    $0x18,%esp
 8048ba8:	c7 04 24 08 b0 04 08 	movl   $0x804b008,(%esp)
 8048baf:	ff d0                	call   *%eax
 8048bb1:	c9                   	leave  
 8048bb2:	e9 79 ff ff ff       	jmp    8048b30 <register_tm_clones>
 8048bb7:	e9 74 ff ff ff       	jmp    8048b30 <register_tm_clones>
 8048bbc:	90                   	nop
 8048bbd:	90                   	nop
 8048bbe:	90                   	nop
 8048bbf:	90                   	nop

08048bc0 <usage>:
 8048bc0:	55                   	push   %ebp
 8048bc1:	89 e5                	mov    %esp,%ebp
 8048bc3:	83 ec 18             	sub    $0x18,%esp
 8048bc6:	89 44 24 04          	mov    %eax,0x4(%esp)
 8048bca:	c7 04 24 b0 a0 04 08 	movl   $0x804a0b0,(%esp)
 8048bd1:	e8 fa fc ff ff       	call   80488d0 <printf@plt>
 8048bd6:	c7 04 24 ce a0 04 08 	movl   $0x804a0ce,(%esp)
 8048bdd:	e8 8e fd ff ff       	call   8048970 <puts@plt>
 8048be2:	c7 04 24 e4 a0 04 08 	movl   $0x804a0e4,(%esp)
 8048be9:	e8 82 fd ff ff       	call   8048970 <puts@plt>
 8048bee:	c7 04 24 ec a1 04 08 	movl   $0x804a1ec,(%esp)
 8048bf5:	e8 76 fd ff ff       	call   8048970 <puts@plt>
 8048bfa:	c7 04 24 28 a2 04 08 	movl   $0x804a228,(%esp)
 8048c01:	e8 6a fd ff ff       	call   8048970 <puts@plt>
 8048c06:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
 8048c0d:	e8 7e fd ff ff       	call   8048990 <exit@plt>

08048c12 <illegalhandler>:
 8048c12:	55                   	push   %ebp
 8048c13:	89 e5                	mov    %esp,%ebp
 8048c15:	83 ec 18             	sub    $0x18,%esp
 8048c18:	c7 04 24 50 a2 04 08 	movl   $0x804a250,(%esp)
 8048c1f:	e8 4c fd ff ff       	call   8048970 <puts@plt>
 8048c24:	c7 04 24 fd a0 04 08 	movl   $0x804a0fd,(%esp)
 8048c2b:	e8 40 fd ff ff       	call   8048970 <puts@plt>
 8048c30:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
 8048c37:	e8 54 fd ff ff       	call   8048990 <exit@plt>

08048c3c <seghandler>:
 8048c3c:	55                   	push   %ebp
 8048c3d:	89 e5                	mov    %esp,%ebp
 8048c3f:	83 ec 18             	sub    $0x18,%esp
 8048c42:	c7 04 24 7c a2 04 08 	movl   $0x804a27c,(%esp)
 8048c49:	e8 22 fd ff ff       	call   8048970 <puts@plt>
 8048c4e:	c7 04 24 fd a0 04 08 	movl   $0x804a0fd,(%esp)
 8048c55:	e8 16 fd ff ff       	call   8048970 <puts@plt>
 8048c5a:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
 8048c61:	e8 2a fd ff ff       	call   8048990 <exit@plt>

08048c66 <bushandler>:
 8048c66:	55                   	push   %ebp
 8048c67:	89 e5                	mov    %esp,%ebp
 8048c69:	83 ec 18             	sub    $0x18,%esp
 8048c6c:	c7 04 24 a4 a2 04 08 	movl   $0x804a2a4,(%esp)
 8048c73:	e8 f8 fc ff ff       	call   8048970 <puts@plt>
 8048c78:	c7 04 24 fd a0 04 08 	movl   $0x804a0fd,(%esp)
 8048c7f:	e8 ec fc ff ff       	call   8048970 <puts@plt>
 8048c84:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
 8048c8b:	e8 00 fd ff ff       	call   8048990 <exit@plt>

08048c90 <smoke>:
 8048c90:	55                   	push   %ebp
 8048c91:	89 e5                	mov    %esp,%ebp
 8048c93:	83 ec 18             	sub    $0x18,%esp
 8048c96:	c7 04 24 13 a1 04 08 	movl   $0x804a113,(%esp)
 8048c9d:	e8 ce fc ff ff       	call   8048970 <puts@plt>
 8048ca2:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
 8048ca9:	e8 96 06 00 00       	call   8049344 <validate>
 8048cae:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
 8048cb5:	e8 d6 fc ff ff       	call   8048990 <exit@plt>

08048cba <fizz>:
 8048cba:	55                   	push   %ebp
 8048cbb:	89 e5                	mov    %esp,%ebp
 8048cbd:	83 ec 18             	sub    $0x18,%esp
 8048cc0:	8b 45 08             	mov    0x8(%ebp),%eax
 8048cc3:	3b 05 20 c2 04 08    	cmp    0x804c220,%eax
 8048cc9:	75 1e                	jne    8048ce9 <fizz+0x2f>
 8048ccb:	89 44 24 04          	mov    %eax,0x4(%esp)
 8048ccf:	c7 04 24 2e a1 04 08 	movl   $0x804a12e,(%esp)
 8048cd6:	e8 f5 fb ff ff       	call   80488d0 <printf@plt>
 8048cdb:	c7 04 24 01 00 00 00 	movl   $0x1,(%esp)
 8048ce2:	e8 5d 06 00 00       	call   8049344 <validate>
 8048ce7:	eb 10                	jmp    8048cf9 <fizz+0x3f>
 8048ce9:	89 44 24 04          	mov    %eax,0x4(%esp)
 8048ced:	c7 04 24 c4 a2 04 08 	movl   $0x804a2c4,(%esp)
 8048cf4:	e8 d7 fb ff ff       	call   80488d0 <printf@plt>
 8048cf9:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
 8048d00:	e8 8b fc ff ff       	call   8048990 <exit@plt>

08048d05 <bang>:
 8048d05:	55                   	push   %ebp
 8048d06:	89 e5                	mov    %esp,%ebp
 8048d08:	83 ec 18             	sub    $0x18,%esp
 8048d0b:	a1 18 c2 04 08       	mov    0x804c218,%eax
 8048d10:	3b 05 20 c2 04 08    	cmp    0x804c220,%eax
 8048d16:	75 1e                	jne    8048d36 <bang+0x31>
 8048d18:	89 44 24 04          	mov    %eax,0x4(%esp)
 8048d1c:	c7 04 24 e4 a2 04 08 	movl   $0x804a2e4,(%esp)
 8048d23:	e8 a8 fb ff ff       	call   80488d0 <printf@plt>
 8048d28:	c7 04 24 02 00 00 00 	movl   $0x2,(%esp)
 8048d2f:	e8 10 06 00 00       	call   8049344 <validate>
 8048d34:	eb 10                	jmp    8048d46 <bang+0x41>
 8048d36:	89 44 24 04          	mov    %eax,0x4(%esp)
 8048d3a:	c7 04 24 4c a1 04 08 	movl   $0x804a14c,(%esp)
 8048d41:	e8 8a fb ff ff       	call   80488d0 <printf@plt>
 8048d46:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
 8048d4d:	e8 3e fc ff ff       	call   8048990 <exit@plt>

08048d52 <Gets>:
 8048d52:	55                   	push   %ebp
 8048d53:	89 e5                	mov    %esp,%ebp
 8048d55:	57                   	push   %edi
 8048d56:	56                   	push   %esi
 8048d57:	53                   	push   %ebx
 8048d58:	83 ec 1c             	sub    $0x1c,%esp
 8048d5b:	8b 75 08             	mov    0x8(%ebp),%esi
 8048d5e:	c7 05 14 c2 04 08 00 	movl   $0x0,0x804c214
 8048d65:	00 00 00 
 8048d68:	89 f3                	mov    %esi,%ebx
 8048d6a:	eb 48                	jmp    8048db4 <Gets+0x62>
 8048d6c:	89 d1                	mov    %edx,%ecx
 8048d6e:	88 13                	mov    %dl,(%ebx)
 8048d70:	83 c3 01             	add    $0x1,%ebx
 8048d73:	a1 14 c2 04 08       	mov    0x804c214,%eax
 8048d78:	3d ff 03 00 00       	cmp    $0x3ff,%eax
 8048d7d:	7f 35                	jg     8048db4 <Gets+0x62>
 8048d7f:	8d 3c 40             	lea    (%eax,%eax,2),%edi
 8048d82:	c0 e9 04             	shr    $0x4,%cl
 8048d85:	0f be c9             	movsbl %cl,%ecx
 8048d88:	0f b6 89 30 a4 04 08 	movzbl 0x804a430(%ecx),%ecx
 8048d8f:	88 8f 60 c2 04 08    	mov    %cl,0x804c260(%edi)
 8048d95:	83 e2 0f             	and    $0xf,%edx
 8048d98:	0f b6 92 30 a4 04 08 	movzbl 0x804a430(%edx),%edx
 8048d9f:	88 97 61 c2 04 08    	mov    %dl,0x804c261(%edi)
 8048da5:	c6 87 62 c2 04 08 20 	movb   $0x20,0x804c262(%edi)
 8048dac:	83 c0 01             	add    $0x1,%eax
 8048daf:	a3 14 c2 04 08       	mov    %eax,0x804c214
 8048db4:	a1 24 c2 04 08       	mov    0x804c224,%eax
 8048db9:	89 04 24             	mov    %eax,(%esp)
 8048dbc:	e8 4f fb ff ff       	call   8048910 <_IO_getc@plt>
 8048dc1:	89 c2                	mov    %eax,%edx
 8048dc3:	83 f8 ff             	cmp    $0xffffffff,%eax
 8048dc6:	74 05                	je     8048dcd <Gets+0x7b>
 8048dc8:	83 f8 0a             	cmp    $0xa,%eax
 8048dcb:	75 9f                	jne    8048d6c <Gets+0x1a>
 8048dcd:	c6 03 00             	movb   $0x0,(%ebx)
 8048dd0:	a1 14 c2 04 08       	mov    0x804c214,%eax
 8048dd5:	c6 84 40 60 c2 04 08 	movb   $0x0,0x804c260(%eax,%eax,2)
 8048ddc:	00 
 8048ddd:	89 f0                	mov    %esi,%eax
 8048ddf:	83 c4 1c             	add    $0x1c,%esp
 8048de2:	5b                   	pop    %ebx
 8048de3:	5e                   	pop    %esi
 8048de4:	5f                   	pop    %edi
 8048de5:	5d                   	pop    %ebp
 8048de6:	c3                   	ret    

08048de7 <uniqueval>:
 8048de7:	55                   	push   %ebp
 8048de8:	89 e5                	mov    %esp,%ebp
 8048dea:	83 ec 18             	sub    $0x18,%esp
 8048ded:	e8 5e fb ff ff       	call   8048950 <getpid@plt>
 8048df2:	89 04 24             	mov    %eax,(%esp)
 8048df5:	e8 c6 fa ff ff       	call   80488c0 <srandom@plt>
 8048dfa:	e8 81 fc ff ff       	call   8048a80 <random@plt>
 8048dff:	c9                   	leave  
 8048e00:	c3                   	ret    

08048e01 <testn>:
 8048e01:	55                   	push   %ebp
 8048e02:	89 e5                	mov    %esp,%ebp
 8048e04:	53                   	push   %ebx
 8048e05:	83 ec 24             	sub    $0x24,%esp
 8048e08:	e8 da ff ff ff       	call   8048de7 <uniqueval>
 8048e0d:	89 45 f4             	mov    %eax,-0xc(%ebp)
 8048e10:	e8 ef 03 00 00       	call   8049204 <getbufn>
 8048e15:	89 c3                	mov    %eax,%ebx
 8048e17:	e8 cb ff ff ff       	call   8048de7 <uniqueval>
 8048e1c:	8b 55 f4             	mov    -0xc(%ebp),%edx
 8048e1f:	39 d0                	cmp    %edx,%eax
 8048e21:	74 0e                	je     8048e31 <testn+0x30>
 8048e23:	c7 04 24 0c a3 04 08 	movl   $0x804a30c,(%esp)
 8048e2a:	e8 41 fb ff ff       	call   8048970 <puts@plt>
 8048e2f:	eb 36                	jmp    8048e67 <testn+0x66>
 8048e31:	3b 1d 20 c2 04 08    	cmp    0x804c220,%ebx
 8048e37:	75 1e                	jne    8048e57 <testn+0x56>
 8048e39:	89 5c 24 04          	mov    %ebx,0x4(%esp)
 8048e3d:	c7 04 24 38 a3 04 08 	movl   $0x804a338,(%esp)
 8048e44:	e8 87 fa ff ff       	call   80488d0 <printf@plt>
 8048e49:	c7 04 24 04 00 00 00 	movl   $0x4,(%esp)
 8048e50:	e8 ef 04 00 00       	call   8049344 <validate>
 8048e55:	eb 10                	jmp    8048e67 <testn+0x66>
 8048e57:	89 5c 24 04          	mov    %ebx,0x4(%esp)
 8048e5b:	c7 04 24 6a a1 04 08 	movl   $0x804a16a,(%esp)
 8048e62:	e8 69 fa ff ff       	call   80488d0 <printf@plt>
 8048e67:	83 c4 24             	add    $0x24,%esp
 8048e6a:	5b                   	pop    %ebx
 8048e6b:	5d                   	pop    %ebp
 8048e6c:	c3                   	ret    

08048e6d <test>:
 8048e6d:	55                   	push   %ebp
 8048e6e:	89 e5                	mov    %esp,%ebp
 8048e70:	53                   	push   %ebx
 8048e71:	83 ec 24             	sub    $0x24,%esp
 8048e74:	e8 6e ff ff ff       	call   8048de7 <uniqueval>
 8048e79:	89 45 f4             	mov    %eax,-0xc(%ebp)
 8048e7c:	e8 6b 03 00 00       	call   80491ec <getbuf>
 8048e81:	89 c3                	mov    %eax,%ebx
 8048e83:	e8 5f ff ff ff       	call   8048de7 <uniqueval>
 8048e88:	8b 55 f4             	mov    -0xc(%ebp),%edx
 8048e8b:	39 d0                	cmp    %edx,%eax
 8048e8d:	74 0e                	je     8048e9d <test+0x30>
 8048e8f:	c7 04 24 0c a3 04 08 	movl   $0x804a30c,(%esp)
 8048e96:	e8 d5 fa ff ff       	call   8048970 <puts@plt>
 8048e9b:	eb 36                	jmp    8048ed3 <test+0x66>
 8048e9d:	3b 1d 20 c2 04 08    	cmp    0x804c220,%ebx
 8048ea3:	75 1e                	jne    8048ec3 <test+0x56>
 8048ea5:	89 5c 24 04          	mov    %ebx,0x4(%esp)
 8048ea9:	c7 04 24 86 a1 04 08 	movl   $0x804a186,(%esp)
 8048eb0:	e8 1b fa ff ff       	call   80488d0 <printf@plt>
 8048eb5:	c7 04 24 03 00 00 00 	movl   $0x3,(%esp)
 8048ebc:	e8 83 04 00 00       	call   8049344 <validate>
 8048ec1:	eb 10                	jmp    8048ed3 <test+0x66>
 8048ec3:	89 5c 24 04          	mov    %ebx,0x4(%esp)
 8048ec7:	c7 04 24 a3 a1 04 08 	movl   $0x804a1a3,(%esp)
 8048ece:	e8 fd f9 ff ff       	call   80488d0 <printf@plt>
 8048ed3:	83 c4 24             	add    $0x24,%esp
 8048ed6:	5b                   	pop    %ebx
 8048ed7:	5d                   	pop    %ebp
 8048ed8:	c3                   	ret    

08048ed9 <launch>:
 8048ed9:	55                   	push   %ebp
 8048eda:	89 e5                	mov    %esp,%ebp
 8048edc:	53                   	push   %ebx
 8048edd:	83 ec 54             	sub    $0x54,%esp
 8048ee0:	89 c3                	mov    %eax,%ebx
 8048ee2:	8d 4d b8             	lea    -0x48(%ebp),%ecx
 8048ee5:	81 e1 f0 3f 00 00    	and    $0x3ff0,%ecx
 8048eeb:	8d 44 11 1e          	lea    0x1e(%ecx,%edx,1),%eax
 8048eef:	83 e0 f0             	and    $0xfffffff0,%eax
 8048ef2:	29 c4                	sub    %eax,%esp
 8048ef4:	8d 44 24 1b          	lea    0x1b(%esp),%eax
 8048ef8:	83 e0 f0             	and    $0xfffffff0,%eax
 8048efb:	89 4c 24 08          	mov    %ecx,0x8(%esp)
 8048eff:	c7 44 24 04 f4 00 00 	movl   $0xf4,0x4(%esp)
 8048f06:	00 
 8048f07:	89 04 24             	mov    %eax,(%esp)
 8048f0a:	e8 01 fb ff ff       	call   8048a10 <memset@plt>
 8048f0f:	c7 04 24 be a1 04 08 	movl   $0x804a1be,(%esp)
 8048f16:	e8 b5 f9 ff ff       	call   80488d0 <printf@plt>
 8048f1b:	85 db                	test   %ebx,%ebx
 8048f1d:	74 07                	je     8048f26 <launch+0x4d>
 8048f1f:	e8 dd fe ff ff       	call   8048e01 <testn>
 8048f24:	eb 05                	jmp    8048f2b <launch+0x52>
 8048f26:	e8 42 ff ff ff       	call   8048e6d <test>
 8048f2b:	83 3d 1c c2 04 08 00 	cmpl   $0x0,0x804c21c
 8048f32:	75 16                	jne    8048f4a <launch+0x71>
 8048f34:	c7 04 24 fd a0 04 08 	movl   $0x804a0fd,(%esp)
 8048f3b:	e8 30 fa ff ff       	call   8048970 <puts@plt>
 8048f40:	c7 05 1c c2 04 08 00 	movl   $0x0,0x804c21c
 8048f47:	00 00 00 
 8048f4a:	8b 5d fc             	mov    -0x4(%ebp),%ebx
 8048f4d:	c9                   	leave  
 8048f4e:	c3                   	ret    

08048f4f <launcher>:
 8048f4f:	55                   	push   %ebp
 8048f50:	89 e5                	mov    %esp,%ebp
 8048f52:	83 ec 28             	sub    $0x28,%esp
 8048f55:	8b 45 08             	mov    0x8(%ebp),%eax
 8048f58:	a3 10 c2 04 08       	mov    %eax,0x804c210
 8048f5d:	8b 45 0c             	mov    0xc(%ebp),%eax
 8048f60:	a3 0c c2 04 08       	mov    %eax,0x804c20c
 8048f65:	c7 44 24 14 00 00 00 	movl   $0x0,0x14(%esp)
 8048f6c:	00 
 8048f6d:	c7 44 24 10 00 00 00 	movl   $0x0,0x10(%esp)
 8048f74:	00 
 8048f75:	c7 44 24 0c 32 01 00 	movl   $0x132,0xc(%esp)
 8048f7c:	00 
 8048f7d:	c7 44 24 08 07 00 00 	movl   $0x7,0x8(%esp)
 8048f84:	00 
 8048f85:	c7 44 24 04 00 00 10 	movl   $0x100000,0x4(%esp)
 8048f8c:	00 
 8048f8d:	c7 04 24 00 60 58 55 	movl   $0x55586000,(%esp)
 8048f94:	e8 17 fa ff ff       	call   80489b0 <mmap@plt>
 8048f99:	3d 00 60 58 55       	cmp    $0x55586000,%eax
 8048f9e:	74 31                	je     8048fd1 <launcher+0x82>
 8048fa0:	a1 e0 c1 04 08       	mov    0x804c1e0,%eax
 8048fa5:	89 44 24 0c          	mov    %eax,0xc(%esp)
 8048fa9:	c7 44 24 08 47 00 00 	movl   $0x47,0x8(%esp)
 8048fb0:	00 
 8048fb1:	c7 44 24 04 01 00 00 	movl   $0x1,0x4(%esp)
 8048fb8:	00 
 8048fb9:	c7 04 24 58 a3 04 08 	movl   $0x804a358,(%esp)
 8048fc0:	e8 5b f9 ff ff       	call   8048920 <fwrite@plt>
 8048fc5:	c7 04 24 01 00 00 00 	movl   $0x1,(%esp)
 8048fcc:	e8 bf f9 ff ff       	call   8048990 <exit@plt>
 8048fd1:	c7 05 40 c2 04 08 f8 	movl   $0x55685ff8,0x804c240
 8048fd8:	5f 68 55 
 8048fdb:	ba f8 5f 68 55       	mov    $0x55685ff8,%edx
 8048fe0:	89 e0                	mov    %esp,%eax
 8048fe2:	89 d4                	mov    %edx,%esp
 8048fe4:	89 c2                	mov    %eax,%edx
 8048fe6:	89 15 08 c2 04 08    	mov    %edx,0x804c208
 8048fec:	8b 15 0c c2 04 08    	mov    0x804c20c,%edx
 8048ff2:	a1 10 c2 04 08       	mov    0x804c210,%eax
 8048ff7:	e8 dd fe ff ff       	call   8048ed9 <launch>
 8048ffc:	a1 08 c2 04 08       	mov    0x804c208,%eax
 8049001:	89 c4                	mov    %eax,%esp
 8049003:	c7 44 24 04 00 00 10 	movl   $0x100000,0x4(%esp)
 804900a:	00 
 804900b:	c7 04 24 00 60 58 55 	movl   $0x55586000,(%esp)
 8049012:	e8 39 fa ff ff       	call   8048a50 <munmap@plt>
 8049017:	c9                   	leave  
 8049018:	c3                   	ret    

08049019 <main>:
 8049019:	55                   	push   %ebp
 804901a:	89 e5                	mov    %esp,%ebp
 804901c:	57                   	push   %edi
 804901d:	56                   	push   %esi
 804901e:	53                   	push   %ebx
 804901f:	83 e4 f0             	and    $0xfffffff0,%esp
 8049022:	83 ec 20             	sub    $0x20,%esp
 8049025:	8b 75 08             	mov    0x8(%ebp),%esi
 8049028:	8b 5d 0c             	mov    0xc(%ebp),%ebx
 804902b:	c7 44 24 04 3c 8c 04 	movl   $0x8048c3c,0x4(%esp)
 8049032:	08 
 8049033:	c7 04 24 0b 00 00 00 	movl   $0xb,(%esp)
 804903a:	e8 b1 f8 ff ff       	call   80488f0 <signal@plt>
 804903f:	c7 44 24 04 66 8c 04 	movl   $0x8048c66,0x4(%esp)
 8049046:	08 
 8049047:	c7 04 24 07 00 00 00 	movl   $0x7,(%esp)
 804904e:	e8 9d f8 ff ff       	call   80488f0 <signal@plt>
 8049053:	c7 44 24 04 12 8c 04 	movl   $0x8048c12,0x4(%esp)
 804905a:	08 
 804905b:	c7 04 24 04 00 00 00 	movl   $0x4,(%esp)
 8049062:	e8 89 f8 ff ff       	call   80488f0 <signal@plt>
 8049067:	a1 e4 c1 04 08       	mov    0x804c1e4,%eax
 804906c:	a3 24 c2 04 08       	mov    %eax,0x804c224
 8049071:	bf 01 00 00 00       	mov    $0x1,%edi
 8049076:	c7 44 24 1c 00 00 00 	movl   $0x0,0x1c(%esp)
 804907d:	00 
 804907e:	eb 71                	jmp    80490f1 <main+0xd8>
 8049080:	83 e8 67             	sub    $0x67,%eax
 8049083:	3c 0e                	cmp    $0xe,%al
 8049085:	77 56                	ja     80490dd <main+0xc4>
 8049087:	0f b6 c0             	movzbl %al,%eax
 804908a:	ff 24 85 f4 a3 04 08 	jmp    *0x804a3f4(,%eax,4)
 8049091:	8b 03                	mov    (%ebx),%eax
 8049093:	e8 28 fb ff ff       	call   8048bc0 <usage>
 8049098:	a1 00 c2 04 08       	mov    0x804c200,%eax
 804909d:	89 04 24             	mov    %eax,(%esp)
 80490a0:	e8 7b f9 ff ff       	call   8048a20 <__strdup@plt>
 80490a5:	a3 30 c2 04 08       	mov    %eax,0x804c230
 80490aa:	89 04 24             	mov    %eax,(%esp)
 80490ad:	e8 38 0f 00 00       	call   8049fea <gencookie>
 80490b2:	a3 20 c2 04 08       	mov    %eax,0x804c220
 80490b7:	eb 38                	jmp    80490f1 <main+0xd8>
 80490b9:	c7 04 24 a0 a3 04 08 	movl   $0x804a3a0,(%esp)
 80490c0:	e8 ab f8 ff ff       	call   8048970 <puts@plt>
 80490c5:	c7 05 2c c2 04 08 00 	movl   $0x0,0x804c22c
 80490cc:	00 00 00 
 80490cf:	eb 20                	jmp    80490f1 <main+0xd8>
 80490d1:	c7 05 28 c2 04 08 01 	movl   $0x1,0x804c228
 80490d8:	00 00 00 
 80490db:	eb 14                	jmp    80490f1 <main+0xd8>
 80490dd:	8b 03                	mov    (%ebx),%eax
 80490df:	e8 dc fa ff ff       	call   8048bc0 <usage>
 80490e4:	bf 05 00 00 00       	mov    $0x5,%edi
 80490e9:	c7 44 24 1c 01 00 00 	movl   $0x1,0x1c(%esp)
 80490f0:	00 
 80490f1:	c7 44 24 08 cb a1 04 	movl   $0x804a1cb,0x8(%esp)
 80490f8:	08 
 80490f9:	89 5c 24 04          	mov    %ebx,0x4(%esp)
 80490fd:	89 34 24             	mov    %esi,(%esp)
 8049100:	e8 db f8 ff ff       	call   80489e0 <getopt@plt>
 8049105:	3c ff                	cmp    $0xff,%al
 8049107:	0f 85 73 ff ff ff    	jne    8049080 <main+0x67>
 804910d:	83 3d 30 c2 04 08 00 	cmpl   $0x0,0x804c230
 8049114:	75 19                	jne    804912f <main+0x116>
 8049116:	8b 03                	mov    (%ebx),%eax
 8049118:	89 44 24 04          	mov    %eax,0x4(%esp)
 804911c:	c7 04 24 c8 a3 04 08 	movl   $0x804a3c8,(%esp)
 8049123:	e8 a8 f7 ff ff       	call   80488d0 <printf@plt>
 8049128:	8b 03                	mov    (%ebx),%eax
 804912a:	e8 91 fa ff ff       	call   8048bc0 <usage>
 804912f:	e8 f0 00 00 00       	call   8049224 <initialize_bomb>
 8049134:	a1 30 c2 04 08       	mov    0x804c230,%eax
 8049139:	89 44 24 04          	mov    %eax,0x4(%esp)
 804913d:	c7 04 24 d2 a1 04 08 	movl   $0x804a1d2,(%esp)
 8049144:	e8 87 f7 ff ff       	call   80488d0 <printf@plt>
 8049149:	a1 20 c2 04 08       	mov    0x804c220,%eax
 804914e:	89 44 24 04          	mov    %eax,0x4(%esp)
 8049152:	c7 04 24 de a1 04 08 	movl   $0x804a1de,(%esp)
 8049159:	e8 72 f7 ff ff       	call   80488d0 <printf@plt>
 804915e:	a1 20 c2 04 08       	mov    0x804c220,%eax
 8049163:	89 04 24             	mov    %eax,(%esp)
 8049166:	e8 55 f7 ff ff       	call   80488c0 <srandom@plt>
 804916b:	e8 10 f9 ff ff       	call   8048a80 <random@plt>
 8049170:	25 f0 0f 00 00       	and    $0xff0,%eax
 8049175:	05 00 01 00 00       	add    $0x100,%eax
 804917a:	89 44 24 18          	mov    %eax,0x18(%esp)
 804917e:	c7 44 24 04 04 00 00 	movl   $0x4,0x4(%esp)
 8049185:	00 
 8049186:	89 3c 24             	mov    %edi,(%esp)
 8049189:	e8 32 f9 ff ff       	call   8048ac0 <calloc@plt>
 804918e:	89 c6                	mov    %eax,%esi
 8049190:	c7 00 00 00 00 00    	movl   $0x0,(%eax)
 8049196:	bb 01 00 00 00       	mov    $0x1,%ebx
 804919b:	eb 17                	jmp    80491b4 <main+0x19b>
 804919d:	e8 de f8 ff ff       	call   8048a80 <random@plt>
 80491a2:	25 f0 00 00 00       	and    $0xf0,%eax
 80491a7:	ba 80 00 00 00       	mov    $0x80,%edx
 80491ac:	29 c2                	sub    %eax,%edx
 80491ae:	89 14 9e             	mov    %edx,(%esi,%ebx,4)
 80491b1:	83 c3 01             	add    $0x1,%ebx
 80491b4:	39 fb                	cmp    %edi,%ebx
 80491b6:	7c e5                	jl     804919d <main+0x184>
 80491b8:	bb 00 00 00 00       	mov    $0x0,%ebx
 80491bd:	eb 1a                	jmp    80491d9 <main+0x1c0>
 80491bf:	8b 44 24 18          	mov    0x18(%esp),%eax
 80491c3:	03 04 9e             	add    (%esi,%ebx,4),%eax
 80491c6:	89 44 24 04          	mov    %eax,0x4(%esp)
 80491ca:	8b 44 24 1c          	mov    0x1c(%esp),%eax
 80491ce:	89 04 24             	mov    %eax,(%esp)
 80491d1:	e8 79 fd ff ff       	call   8048f4f <launcher>
 80491d6:	83 c3 01             	add    $0x1,%ebx
 80491d9:	39 fb                	cmp    %edi,%ebx
 80491db:	7c e2                	jl     80491bf <main+0x1a6>
 80491dd:	b8 00 00 00 00       	mov    $0x0,%eax
 80491e2:	8d 65 f4             	lea    -0xc(%ebp),%esp
 80491e5:	5b                   	pop    %ebx
 80491e6:	5e                   	pop    %esi
 80491e7:	5f                   	pop    %edi
 80491e8:	5d                   	pop    %ebp
 80491e9:	c3                   	ret    
 80491ea:	90                   	nop
 80491eb:	90                   	nop

080491ec <getbuf>:
 80491ec:	55                   	push   %ebp
 80491ed:	89 e5                	mov    %esp,%ebp
 80491ef:	83 ec 38             	sub    $0x38,%esp
 80491f2:	8d 45 d8             	lea    -0x28(%ebp),%eax
 80491f5:	89 04 24             	mov    %eax,(%esp)
 80491f8:	e8 55 fb ff ff       	call   8048d52 <Gets>
 80491fd:	b8 01 00 00 00       	mov    $0x1,%eax
 8049202:	c9                   	leave  
 8049203:	c3                   	ret    

08049204 <getbufn>:
 8049204:	55                   	push   %ebp
 8049205:	89 e5                	mov    %esp,%ebp
 8049207:	81 ec 18 02 00 00    	sub    $0x218,%esp
 804920d:	8d 85 f8 fd ff ff    	lea    -0x208(%ebp),%eax
 8049213:	89 04 24             	mov    %eax,(%esp)
 8049216:	e8 37 fb ff ff       	call   8048d52 <Gets>
 804921b:	b8 01 00 00 00       	mov    $0x1,%eax
 8049220:	c9                   	leave  
 8049221:	c3                   	ret    
 8049222:	90                   	nop
 8049223:	90                   	nop

08049224 <initialize_bomb>:
 8049224:	55                   	push   %ebp
 8049225:	89 e5                	mov    %esp,%ebp
 8049227:	56                   	push   %esi
 8049228:	53                   	push   %ebx
 8049229:	81 ec 10 24 00 00    	sub    $0x2410,%esp
 804922f:	83 3d 28 c2 04 08 00 	cmpl   $0x0,0x804c228
 8049236:	74 0c                	je     8049244 <initialize_bomb+0x20>
 8049238:	c7 04 24 ff ff ff ff 	movl   $0xffffffff,(%esp)
 804923f:	e8 ce 0a 00 00       	call   8049d12 <init_timeout>
 8049244:	83 3d 2c c2 04 08 00 	cmpl   $0x0,0x804c22c
 804924b:	0f 84 e9 00 00 00    	je     804933a <initialize_bomb+0x116>
 8049251:	c7 44 24 04 00 04 00 	movl   $0x400,0x4(%esp)
 8049258:	00 
 8049259:	8d 85 f8 fb ff ff    	lea    -0x408(%ebp),%eax
 804925f:	89 04 24             	mov    %eax,(%esp)
 8049262:	e8 f9 f6 ff ff       	call   8048960 <gethostname@plt>
 8049267:	85 c0                	test   %eax,%eax
 8049269:	75 19                	jne    8049284 <initialize_bomb+0x60>
 804926b:	a1 c0 b1 04 08       	mov    0x804b1c0,%eax
 8049270:	bb 00 00 00 00       	mov    $0x0,%ebx
 8049275:	8d b5 f8 fb ff ff    	lea    -0x408(%ebp),%esi
 804927b:	85 c0                	test   %eax,%eax
 804927d:	75 1d                	jne    804929c <initialize_bomb+0x78>
 804927f:	e9 95 00 00 00       	jmp    8049319 <initialize_bomb+0xf5>
 8049284:	c7 04 24 40 a4 04 08 	movl   $0x804a440,(%esp)
 804928b:	e8 e0 f6 ff ff       	call   8048970 <puts@plt>
 8049290:	c7 04 24 08 00 00 00 	movl   $0x8,(%esp)
 8049297:	e8 f4 f6 ff ff       	call   8048990 <exit@plt>
 804929c:	89 74 24 04          	mov    %esi,0x4(%esp)
 80492a0:	89 04 24             	mov    %eax,(%esp)
 80492a3:	e8 48 f7 ff ff       	call   80489f0 <strcasecmp@plt>
 80492a8:	85 c0                	test   %eax,%eax
 80492aa:	74 59                	je     8049305 <initialize_bomb+0xe1>
 80492ac:	83 c3 01             	add    $0x1,%ebx
 80492af:	8b 04 9d c0 b1 04 08 	mov    0x804b1c0(,%ebx,4),%eax
 80492b6:	85 c0                	test   %eax,%eax
 80492b8:	75 e2                	jne    804929c <initialize_bomb+0x78>
 80492ba:	eb 5d                	jmp    8049319 <initialize_bomb+0xf5>
 80492bc:	bb 00 00 00 00       	mov    $0x0,%ebx
 80492c1:	89 04 24             	mov    %eax,(%esp)
 80492c4:	e8 a7 f6 ff ff       	call   8048970 <puts@plt>
 80492c9:	83 c3 01             	add    $0x1,%ebx
 80492cc:	8b 04 9d c0 b1 04 08 	mov    0x804b1c0(,%ebx,4),%eax
 80492d3:	85 c0                	test   %eax,%eax
 80492d5:	75 ea                	jne    80492c1 <initialize_bomb+0x9d>
 80492d7:	c7 04 24 08 00 00 00 	movl   $0x8,(%esp)
 80492de:	e8 ad f6 ff ff       	call   8048990 <exit@plt>
 80492e3:	8d 85 f8 db ff ff    	lea    -0x2408(%ebp),%eax
 80492e9:	89 44 24 04          	mov    %eax,0x4(%esp)
 80492ed:	c7 04 24 ae a5 04 08 	movl   $0x804a5ae,(%esp)
 80492f4:	e8 d7 f5 ff ff       	call   80488d0 <printf@plt>
 80492f9:	c7 04 24 08 00 00 00 	movl   $0x8,(%esp)
 8049300:	e8 8b f6 ff ff       	call   8048990 <exit@plt>
 8049305:	8d 85 f8 db ff ff    	lea    -0x2408(%ebp),%eax
 804930b:	89 04 24             	mov    %eax,(%esp)
 804930e:	e8 38 0a 00 00       	call   8049d4b <init_driver>
 8049313:	85 c0                	test   %eax,%eax
 8049315:	79 23                	jns    804933a <initialize_bomb+0x116>
 8049317:	eb ca                	jmp    80492e3 <initialize_bomb+0xbf>
 8049319:	8d 85 f8 fb ff ff    	lea    -0x408(%ebp),%eax
 804931f:	89 44 24 04          	mov    %eax,0x4(%esp)
 8049323:	c7 04 24 78 a4 04 08 	movl   $0x804a478,(%esp)
 804932a:	e8 a1 f5 ff ff       	call   80488d0 <printf@plt>
 804932f:	a1 c0 b1 04 08       	mov    0x804b1c0,%eax
 8049334:	85 c0                	test   %eax,%eax
 8049336:	75 84                	jne    80492bc <initialize_bomb+0x98>
 8049338:	eb 9d                	jmp    80492d7 <initialize_bomb+0xb3>
 804933a:	81 c4 10 24 00 00    	add    $0x2410,%esp
 8049340:	5b                   	pop    %ebx
 8049341:	5e                   	pop    %esi
 8049342:	5d                   	pop    %ebp
 8049343:	c3                   	ret    

08049344 <validate>:
 8049344:	55                   	push   %ebp
 8049345:	89 e5                	mov    %esp,%ebp
 8049347:	81 ec 28 40 00 00    	sub    $0x4028,%esp
 804934d:	89 5d f8             	mov    %ebx,-0x8(%ebp)
 8049350:	89 7d fc             	mov    %edi,-0x4(%ebp)
 8049353:	8b 5d 08             	mov    0x8(%ebp),%ebx
 8049356:	83 3d 30 c2 04 08 00 	cmpl   $0x0,0x804c230
 804935d:	75 11                	jne    8049370 <validate+0x2c>
 804935f:	c7 04 24 b4 a4 04 08 	movl   $0x804a4b4,(%esp)
 8049366:	e8 05 f6 ff ff       	call   8048970 <puts@plt>
 804936b:	e9 10 01 00 00       	jmp    8049480 <validate+0x13c>
 8049370:	83 fb 04             	cmp    $0x4,%ebx
 8049373:	76 11                	jbe    8049386 <validate+0x42>
 8049375:	c7 04 24 e0 a4 04 08 	movl   $0x804a4e0,(%esp)
 804937c:	e8 ef f5 ff ff       	call   8048970 <puts@plt>
 8049381:	e9 fa 00 00 00       	jmp    8049480 <validate+0x13c>
 8049386:	c7 05 1c c2 04 08 01 	movl   $0x1,0x804c21c
 804938d:	00 00 00 
 8049390:	8b 04 9d c0 c1 04 08 	mov    0x804c1c0(,%ebx,4),%eax
 8049397:	83 e8 01             	sub    $0x1,%eax
 804939a:	89 04 9d c0 c1 04 08 	mov    %eax,0x804c1c0(,%ebx,4)
 80493a1:	85 c0                	test   %eax,%eax
 80493a3:	7e 11                	jle    80493b6 <validate+0x72>
 80493a5:	c7 04 24 c3 a5 04 08 	movl   $0x804a5c3,(%esp)
 80493ac:	e8 bf f5 ff ff       	call   8048970 <puts@plt>
 80493b1:	e9 ca 00 00 00       	jmp    8049480 <validate+0x13c>
 80493b6:	c7 04 24 ce a5 04 08 	movl   $0x804a5ce,(%esp)
 80493bd:	e8 ae f5 ff ff       	call   8048970 <puts@plt>
 80493c2:	83 3d 2c c2 04 08 00 	cmpl   $0x0,0x804c22c
 80493c9:	0f 84 a5 00 00 00    	je     8049474 <validate+0x130>
 80493cf:	bf 60 c2 04 08       	mov    $0x804c260,%edi
 80493d4:	b8 00 00 00 00       	mov    $0x0,%eax
 80493d9:	b9 ff ff ff ff       	mov    $0xffffffff,%ecx
 80493de:	f2 ae                	repnz scas %es:(%edi),%al
 80493e0:	f7 d1                	not    %ecx
 80493e2:	83 c1 1f             	add    $0x1f,%ecx
 80493e5:	81 f9 00 20 00 00    	cmp    $0x2000,%ecx
 80493eb:	76 11                	jbe    80493fe <validate+0xba>
 80493ed:	c7 04 24 08 a5 04 08 	movl   $0x804a508,(%esp)
 80493f4:	e8 77 f5 ff ff       	call   8048970 <puts@plt>
 80493f9:	e9 82 00 00 00       	jmp    8049480 <validate+0x13c>
 80493fe:	c7 44 24 10 60 c2 04 	movl   $0x804c260,0x10(%esp)
 8049405:	08 
 8049406:	a1 20 c2 04 08       	mov    0x804c220,%eax
 804940b:	89 44 24 0c          	mov    %eax,0xc(%esp)
 804940f:	89 5c 24 08          	mov    %ebx,0x8(%esp)
 8049413:	c7 44 24 04 d4 a5 04 	movl   $0x804a5d4,0x4(%esp)
 804941a:	08 
 804941b:	8d 9d f8 df ff ff    	lea    -0x2008(%ebp),%ebx
 8049421:	89 1c 24             	mov    %ebx,(%esp)
 8049424:	e8 37 f6 ff ff       	call   8048a60 <sprintf@plt>
 8049429:	8d 85 f8 bf ff ff    	lea    -0x4008(%ebp),%eax
 804942f:	89 44 24 0c          	mov    %eax,0xc(%esp)
 8049433:	c7 44 24 08 00 00 00 	movl   $0x0,0x8(%esp)
 804943a:	00 
 804943b:	89 5c 24 04          	mov    %ebx,0x4(%esp)
 804943f:	a1 30 c2 04 08       	mov    0x804c230,%eax
 8049444:	89 04 24             	mov    %eax,(%esp)
 8049447:	e8 9c 0a 00 00       	call   8049ee8 <driver_post>
 804944c:	85 c0                	test   %eax,%eax
 804944e:	75 0e                	jne    804945e <validate+0x11a>
 8049450:	c7 04 24 40 a5 04 08 	movl   $0x804a540,(%esp)
 8049457:	e8 14 f5 ff ff       	call   8048970 <puts@plt>
 804945c:	eb 16                	jmp    8049474 <validate+0x130>
 804945e:	8d 85 f8 bf ff ff    	lea    -0x4008(%ebp),%eax
 8049464:	89 44 24 04          	mov    %eax,0x4(%esp)
 8049468:	c7 04 24 70 a5 04 08 	movl   $0x804a570,(%esp)
 804946f:	e8 5c f4 ff ff       	call   80488d0 <printf@plt>
 8049474:	c7 04 24 dd a5 04 08 	movl   $0x804a5dd,(%esp)
 804947b:	e8 f0 f4 ff ff       	call   8048970 <puts@plt>
 8049480:	8b 5d f8             	mov    -0x8(%ebp),%ebx
 8049483:	8b 7d fc             	mov    -0x4(%ebp),%edi
 8049486:	89 ec                	mov    %ebp,%esp
 8049488:	5d                   	pop    %ebp
 8049489:	c3                   	ret    
 804948a:	90                   	nop
 804948b:	90                   	nop
 804948c:	90                   	nop
 804948d:	90                   	nop
 804948e:	90                   	nop
 804948f:	90                   	nop

08049490 <rio_readlineb>:
 8049490:	55                   	push   %ebp
 8049491:	89 e5                	mov    %esp,%ebp
 8049493:	57                   	push   %edi
 8049494:	56                   	push   %esi
 8049495:	53                   	push   %ebx
 8049496:	83 ec 4c             	sub    $0x4c,%esp
 8049499:	83 f9 01             	cmp    $0x1,%ecx
 804949c:	0f 86 c2 00 00 00    	jbe    8049564 <rio_readlineb+0xd4>
 80494a2:	89 c3                	mov    %eax,%ebx
 80494a4:	89 4d c4             	mov    %ecx,-0x3c(%ebp)
 80494a7:	89 55 d0             	mov    %edx,-0x30(%ebp)
 80494aa:	c7 45 d4 01 00 00 00 	movl   $0x1,-0x2c(%ebp)
 80494b1:	8d 78 0c             	lea    0xc(%eax),%edi
 80494b4:	eb 36                	jmp    80494ec <rio_readlineb+0x5c>
 80494b6:	c7 44 24 08 00 20 00 	movl   $0x2000,0x8(%esp)
 80494bd:	00 
 80494be:	89 7c 24 04          	mov    %edi,0x4(%esp)
 80494c2:	8b 03                	mov    (%ebx),%eax
 80494c4:	89 04 24             	mov    %eax,(%esp)
 80494c7:	e8 e4 f3 ff ff       	call   80488b0 <read@plt>
 80494cc:	89 43 04             	mov    %eax,0x4(%ebx)
 80494cf:	85 c0                	test   %eax,%eax
 80494d1:	79 12                	jns    80494e5 <rio_readlineb+0x55>
 80494d3:	e8 58 f5 ff ff       	call   8048a30 <__errno_location@plt>
 80494d8:	83 38 04             	cmpl   $0x4,(%eax)
 80494db:	74 0f                	je     80494ec <rio_readlineb+0x5c>
 80494dd:	8d 76 00             	lea    0x0(%esi),%esi
 80494e0:	e9 91 00 00 00       	jmp    8049576 <rio_readlineb+0xe6>
 80494e5:	85 c0                	test   %eax,%eax
 80494e7:	74 63                	je     804954c <rio_readlineb+0xbc>
 80494e9:	89 7b 08             	mov    %edi,0x8(%ebx)
 80494ec:	8b 73 04             	mov    0x4(%ebx),%esi
 80494ef:	85 f6                	test   %esi,%esi
 80494f1:	7e c3                	jle    80494b6 <rio_readlineb+0x26>
 80494f3:	85 f6                	test   %esi,%esi
 80494f5:	0f 95 c0             	setne  %al
 80494f8:	0f b6 c0             	movzbl %al,%eax
 80494fb:	89 45 cc             	mov    %eax,-0x34(%ebp)
 80494fe:	8b 53 08             	mov    0x8(%ebx),%edx
 8049501:	89 55 c8             	mov    %edx,-0x38(%ebp)
 8049504:	89 44 24 08          	mov    %eax,0x8(%esp)
 8049508:	89 54 24 04          	mov    %edx,0x4(%esp)
 804950c:	8d 45 e7             	lea    -0x19(%ebp),%eax
 804950f:	89 04 24             	mov    %eax,(%esp)
 8049512:	e8 c9 f3 ff ff       	call   80488e0 <memcpy@plt>
 8049517:	8b 45 c8             	mov    -0x38(%ebp),%eax
 804951a:	03 45 cc             	add    -0x34(%ebp),%eax
 804951d:	89 43 08             	mov    %eax,0x8(%ebx)
 8049520:	2b 75 cc             	sub    -0x34(%ebp),%esi
 8049523:	89 73 04             	mov    %esi,0x4(%ebx)
 8049526:	83 7d cc 01          	cmpl   $0x1,-0x34(%ebp)
 804952a:	75 15                	jne    8049541 <rio_readlineb+0xb1>
 804952c:	0f b6 45 e7          	movzbl -0x19(%ebp),%eax
 8049530:	8b 55 d0             	mov    -0x30(%ebp),%edx
 8049533:	88 02                	mov    %al,(%edx)
 8049535:	83 c2 01             	add    $0x1,%edx
 8049538:	89 55 d0             	mov    %edx,-0x30(%ebp)
 804953b:	3c 0a                	cmp    $0xa,%al
 804953d:	75 17                	jne    8049556 <rio_readlineb+0xc6>
 804953f:	eb 2d                	jmp    804956e <rio_readlineb+0xde>
 8049541:	83 7d cc 00          	cmpl   $0x0,-0x34(%ebp)
 8049545:	75 38                	jne    804957f <rio_readlineb+0xef>
 8049547:	8b 45 d4             	mov    -0x2c(%ebp),%eax
 804954a:	eb 03                	jmp    804954f <rio_readlineb+0xbf>
 804954c:	8b 45 d4             	mov    -0x2c(%ebp),%eax
 804954f:	83 f8 01             	cmp    $0x1,%eax
 8049552:	75 1a                	jne    804956e <rio_readlineb+0xde>
 8049554:	eb 32                	jmp    8049588 <rio_readlineb+0xf8>
 8049556:	83 45 d4 01          	addl   $0x1,-0x2c(%ebp)
 804955a:	8b 45 c4             	mov    -0x3c(%ebp),%eax
 804955d:	39 45 d4             	cmp    %eax,-0x2c(%ebp)
 8049560:	75 8a                	jne    80494ec <rio_readlineb+0x5c>
 8049562:	eb 0a                	jmp    804956e <rio_readlineb+0xde>
 8049564:	89 55 d0             	mov    %edx,-0x30(%ebp)
 8049567:	c7 45 d4 01 00 00 00 	movl   $0x1,-0x2c(%ebp)
 804956e:	8b 55 d0             	mov    -0x30(%ebp),%edx
 8049571:	c6 02 00             	movb   $0x0,(%edx)
 8049574:	eb 19                	jmp    804958f <rio_readlineb+0xff>
 8049576:	c7 45 d4 ff ff ff ff 	movl   $0xffffffff,-0x2c(%ebp)
 804957d:	eb 10                	jmp    804958f <rio_readlineb+0xff>
 804957f:	c7 45 d4 ff ff ff ff 	movl   $0xffffffff,-0x2c(%ebp)
 8049586:	eb 07                	jmp    804958f <rio_readlineb+0xff>
 8049588:	c7 45 d4 00 00 00 00 	movl   $0x0,-0x2c(%ebp)
 804958f:	8b 45 d4             	mov    -0x2c(%ebp),%eax
 8049592:	83 c4 4c             	add    $0x4c,%esp
 8049595:	5b                   	pop    %ebx
 8049596:	5e                   	pop    %esi
 8049597:	5f                   	pop    %edi
 8049598:	5d                   	pop    %ebp
 8049599:	c3                   	ret    

0804959a <sigalrm_handler>:
 804959a:	55                   	push   %ebp
 804959b:	89 e5                	mov    %esp,%ebp
 804959d:	83 ec 18             	sub    $0x18,%esp
 80495a0:	c7 44 24 04 02 00 00 	movl   $0x2,0x4(%esp)
 80495a7:	00 
 80495a8:	c7 04 24 4c a6 04 08 	movl   $0x804a64c,(%esp)
 80495af:	e8 1c f3 ff ff       	call   80488d0 <printf@plt>
 80495b4:	c7 04 24 01 00 00 00 	movl   $0x1,(%esp)
 80495bb:	e8 d0 f3 ff ff       	call   8048990 <exit@plt>

080495c0 <submitr>:
 80495c0:	55                   	push   %ebp
 80495c1:	89 e5                	mov    %esp,%ebp
 80495c3:	57                   	push   %edi
 80495c4:	56                   	push   %esi
 80495c5:	53                   	push   %ebx
 80495c6:	81 ec 6c a0 00 00    	sub    $0xa06c,%esp
 80495cc:	8b 7d 08             	mov    0x8(%ebp),%edi
 80495cf:	8b 5d 1c             	mov    0x1c(%ebp),%ebx
 80495d2:	c7 85 c8 7f ff ff 00 	movl   $0x0,-0x8038(%ebp)
 80495d9:	00 00 00 
 80495dc:	c7 44 24 08 00 00 00 	movl   $0x0,0x8(%esp)
 80495e3:	00 
 80495e4:	c7 44 24 04 01 00 00 	movl   $0x1,0x4(%esp)
 80495eb:	00 
 80495ec:	c7 04 24 02 00 00 00 	movl   $0x2,(%esp)
 80495f3:	e8 78 f4 ff ff       	call   8048a70 <socket@plt>
 80495f8:	89 85 b4 5f ff ff    	mov    %eax,-0xa04c(%ebp)
 80495fe:	85 c0                	test   %eax,%eax
 8049600:	79 51                	jns    8049653 <submitr+0x93>
 8049602:	8b 45 20             	mov    0x20(%ebp),%eax
 8049605:	c7 00 45 72 72 6f    	movl   $0x6f727245,(%eax)
 804960b:	c7 40 04 72 3a 20 43 	movl   $0x43203a72,0x4(%eax)
 8049612:	c7 40 08 6c 69 65 6e 	movl   $0x6e65696c,0x8(%eax)
 8049619:	c7 40 0c 74 20 75 6e 	movl   $0x6e752074,0xc(%eax)
 8049620:	c7 40 10 61 62 6c 65 	movl   $0x656c6261,0x10(%eax)
 8049627:	c7 40 14 20 74 6f 20 	movl   $0x206f7420,0x14(%eax)
 804962e:	c7 40 18 63 72 65 61 	movl   $0x61657263,0x18(%eax)
 8049635:	c7 40 1c 74 65 20 73 	movl   $0x73206574,0x1c(%eax)
 804963c:	c7 40 20 6f 63 6b 65 	movl   $0x656b636f,0x20(%eax)
 8049643:	66 c7 40 24 74 00    	movw   $0x74,0x24(%eax)
 8049649:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 804964e:	e9 b4 06 00 00       	jmp    8049d07 <submitr+0x747>
 8049653:	89 3c 24             	mov    %edi,(%esp)
 8049656:	e8 35 f4 ff ff       	call   8048a90 <gethostbyname@plt>
 804965b:	85 c0                	test   %eax,%eax
 804965d:	75 2f                	jne    804968e <submitr+0xce>
 804965f:	89 7c 24 08          	mov    %edi,0x8(%esp)
 8049663:	c7 44 24 04 70 a6 04 	movl   $0x804a670,0x4(%esp)
 804966a:	08 
 804966b:	8b 55 20             	mov    0x20(%ebp),%edx
 804966e:	89 14 24             	mov    %edx,(%esp)
 8049671:	e8 ea f3 ff ff       	call   8048a60 <sprintf@plt>
 8049676:	8b 85 b4 5f ff ff    	mov    -0xa04c(%ebp),%eax
 804967c:	89 04 24             	mov    %eax,(%esp)
 804967f:	e8 2c f4 ff ff       	call   8048ab0 <close@plt>
 8049684:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049689:	e9 79 06 00 00       	jmp    8049d07 <submitr+0x747>
 804968e:	8d 75 d8             	lea    -0x28(%ebp),%esi
 8049691:	c7 45 d8 00 00 00 00 	movl   $0x0,-0x28(%ebp)
 8049698:	c7 45 dc 00 00 00 00 	movl   $0x0,-0x24(%ebp)
 804969f:	c7 45 e0 00 00 00 00 	movl   $0x0,-0x20(%ebp)
 80496a6:	c7 45 e4 00 00 00 00 	movl   $0x0,-0x1c(%ebp)
 80496ad:	66 c7 45 d8 02 00    	movw   $0x2,-0x28(%ebp)
 80496b3:	8b 50 0c             	mov    0xc(%eax),%edx
 80496b6:	89 54 24 08          	mov    %edx,0x8(%esp)
 80496ba:	8d 55 dc             	lea    -0x24(%ebp),%edx
 80496bd:	89 54 24 04          	mov    %edx,0x4(%esp)
 80496c1:	8b 40 10             	mov    0x10(%eax),%eax
 80496c4:	8b 00                	mov    (%eax),%eax
 80496c6:	89 04 24             	mov    %eax,(%esp)
 80496c9:	e8 62 f2 ff ff       	call   8048930 <bcopy@plt>
 80496ce:	0f b7 45 0c          	movzwl 0xc(%ebp),%eax
 80496d2:	66 c1 c8 08          	ror    $0x8,%ax
 80496d6:	66 89 45 da          	mov    %ax,-0x26(%ebp)
 80496da:	c7 44 24 08 10 00 00 	movl   $0x10,0x8(%esp)
 80496e1:	00 
 80496e2:	89 74 24 04          	mov    %esi,0x4(%esp)
 80496e6:	8b 85 b4 5f ff ff    	mov    -0xa04c(%ebp),%eax
 80496ec:	89 04 24             	mov    %eax,(%esp)
 80496ef:	e8 ac f3 ff ff       	call   8048aa0 <connect@plt>
 80496f4:	85 c0                	test   %eax,%eax
 80496f6:	79 2f                	jns    8049727 <submitr+0x167>
 80496f8:	89 7c 24 08          	mov    %edi,0x8(%esp)
 80496fc:	c7 44 24 04 9c a6 04 	movl   $0x804a69c,0x4(%esp)
 8049703:	08 
 8049704:	8b 55 20             	mov    0x20(%ebp),%edx
 8049707:	89 14 24             	mov    %edx,(%esp)
 804970a:	e8 51 f3 ff ff       	call   8048a60 <sprintf@plt>
 804970f:	8b 85 b4 5f ff ff    	mov    -0xa04c(%ebp),%eax
 8049715:	89 04 24             	mov    %eax,(%esp)
 8049718:	e8 93 f3 ff ff       	call   8048ab0 <close@plt>
 804971d:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049722:	e9 e0 05 00 00       	jmp    8049d07 <submitr+0x747>
 8049727:	ba ff ff ff ff       	mov    $0xffffffff,%edx
 804972c:	89 df                	mov    %ebx,%edi
 804972e:	b8 00 00 00 00       	mov    $0x0,%eax
 8049733:	89 d1                	mov    %edx,%ecx
 8049735:	f2 ae                	repnz scas %es:(%edi),%al
 8049737:	f7 d1                	not    %ecx
 8049739:	89 8d ac 5f ff ff    	mov    %ecx,-0xa054(%ebp)
 804973f:	8b 7d 10             	mov    0x10(%ebp),%edi
 8049742:	89 d1                	mov    %edx,%ecx
 8049744:	f2 ae                	repnz scas %es:(%edi),%al
 8049746:	89 8d a8 5f ff ff    	mov    %ecx,-0xa058(%ebp)
 804974c:	8b 7d 14             	mov    0x14(%ebp),%edi
 804974f:	89 d1                	mov    %edx,%ecx
 8049751:	f2 ae                	repnz scas %es:(%edi),%al
 8049753:	89 ce                	mov    %ecx,%esi
 8049755:	f7 d6                	not    %esi
 8049757:	8b 7d 18             	mov    0x18(%ebp),%edi
 804975a:	89 d1                	mov    %edx,%ecx
 804975c:	f2 ae                	repnz scas %es:(%edi),%al
 804975e:	2b b5 a8 5f ff ff    	sub    -0xa058(%ebp),%esi
 8049764:	29 ce                	sub    %ecx,%esi
 8049766:	8b 95 ac 5f ff ff    	mov    -0xa054(%ebp),%edx
 804976c:	8d 44 52 fd          	lea    -0x3(%edx,%edx,2),%eax
 8049770:	8d 44 06 7b          	lea    0x7b(%esi,%eax,1),%eax
 8049774:	3d 00 20 00 00       	cmp    $0x2000,%eax
 8049779:	76 7c                	jbe    80497f7 <submitr+0x237>
 804977b:	8b 4d 20             	mov    0x20(%ebp),%ecx
 804977e:	c7 01 45 72 72 6f    	movl   $0x6f727245,(%ecx)
 8049784:	c7 41 04 72 3a 20 52 	movl   $0x52203a72,0x4(%ecx)
 804978b:	c7 41 08 65 73 75 6c 	movl   $0x6c757365,0x8(%ecx)
 8049792:	c7 41 0c 74 20 73 74 	movl   $0x74732074,0xc(%ecx)
 8049799:	c7 41 10 72 69 6e 67 	movl   $0x676e6972,0x10(%ecx)
 80497a0:	c7 41 14 20 74 6f 6f 	movl   $0x6f6f7420,0x14(%ecx)
 80497a7:	c7 41 18 20 6c 61 72 	movl   $0x72616c20,0x18(%ecx)
 80497ae:	c7 41 1c 67 65 2e 20 	movl   $0x202e6567,0x1c(%ecx)
 80497b5:	c7 41 20 49 6e 63 72 	movl   $0x72636e49,0x20(%ecx)
 80497bc:	c7 41 24 65 61 73 65 	movl   $0x65736165,0x24(%ecx)
 80497c3:	c7 41 28 20 53 55 42 	movl   $0x42555320,0x28(%ecx)
 80497ca:	c7 41 2c 4d 49 54 52 	movl   $0x5254494d,0x2c(%ecx)
 80497d1:	c7 41 30 5f 4d 41 58 	movl   $0x58414d5f,0x30(%ecx)
 80497d8:	c7 41 34 42 55 46 00 	movl   $0x465542,0x34(%ecx)
 80497df:	8b 85 b4 5f ff ff    	mov    -0xa04c(%ebp),%eax
 80497e5:	89 04 24             	mov    %eax,(%esp)
 80497e8:	e8 c3 f2 ff ff       	call   8048ab0 <close@plt>
 80497ed:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 80497f2:	e9 10 05 00 00       	jmp    8049d07 <submitr+0x747>
 80497f7:	8d 95 cc 9f ff ff    	lea    -0x6034(%ebp),%edx
 80497fd:	b9 00 08 00 00       	mov    $0x800,%ecx
 8049802:	b8 00 00 00 00       	mov    $0x0,%eax
 8049807:	89 d7                	mov    %edx,%edi
 8049809:	f3 ab                	rep stos %eax,%es:(%edi)
 804980b:	89 df                	mov    %ebx,%edi
 804980d:	b9 ff ff ff ff       	mov    $0xffffffff,%ecx
 8049812:	f2 ae                	repnz scas %es:(%edi),%al
 8049814:	f7 d1                	not    %ecx
 8049816:	89 cf                	mov    %ecx,%edi
 8049818:	83 ef 01             	sub    $0x1,%edi
 804981b:	0f 84 0d 04 00 00    	je     8049c2e <submitr+0x66e>
 8049821:	89 d6                	mov    %edx,%esi
 8049823:	0f b6 03             	movzbl (%ebx),%eax
 8049826:	3c 2d                	cmp    $0x2d,%al
 8049828:	74 24                	je     804984e <submitr+0x28e>
 804982a:	3c 2a                	cmp    $0x2a,%al
 804982c:	74 20                	je     804984e <submitr+0x28e>
 804982e:	3c 2e                	cmp    $0x2e,%al
 8049830:	74 1c                	je     804984e <submitr+0x28e>
 8049832:	3c 5f                	cmp    $0x5f,%al
 8049834:	74 18                	je     804984e <submitr+0x28e>
 8049836:	8d 50 d0             	lea    -0x30(%eax),%edx
 8049839:	80 fa 09             	cmp    $0x9,%dl
 804983c:	76 10                	jbe    804984e <submitr+0x28e>
 804983e:	8d 50 bf             	lea    -0x41(%eax),%edx
 8049841:	80 fa 19             	cmp    $0x19,%dl
 8049844:	76 08                	jbe    804984e <submitr+0x28e>
 8049846:	8d 50 9f             	lea    -0x61(%eax),%edx
 8049849:	80 fa 19             	cmp    $0x19,%dl
 804984c:	77 07                	ja     8049855 <submitr+0x295>
 804984e:	88 06                	mov    %al,(%esi)
 8049850:	83 c6 01             	add    $0x1,%esi
 8049853:	eb 59                	jmp    80498ae <submitr+0x2ee>
 8049855:	3c 20                	cmp    $0x20,%al
 8049857:	75 08                	jne    8049861 <submitr+0x2a1>
 8049859:	c6 06 2b             	movb   $0x2b,(%esi)
 804985c:	83 c6 01             	add    $0x1,%esi
 804985f:	eb 4d                	jmp    80498ae <submitr+0x2ee>
 8049861:	8d 50 e0             	lea    -0x20(%eax),%edx
 8049864:	80 fa 5f             	cmp    $0x5f,%dl
 8049867:	76 08                	jbe    8049871 <submitr+0x2b1>
 8049869:	3c 09                	cmp    $0x9,%al
 804986b:	0f 85 18 04 00 00    	jne    8049c89 <submitr+0x6c9>
 8049871:	0f b6 c0             	movzbl %al,%eax
 8049874:	89 44 24 08          	mov    %eax,0x8(%esp)
 8049878:	c7 44 24 04 b0 a7 04 	movl   $0x804a7b0,0x4(%esp)
 804987f:	08 
 8049880:	8d 95 c0 5f ff ff    	lea    -0xa040(%ebp),%edx
 8049886:	89 14 24             	mov    %edx,(%esp)
 8049889:	e8 d2 f1 ff ff       	call   8048a60 <sprintf@plt>
 804988e:	0f b6 85 c0 5f ff ff 	movzbl -0xa040(%ebp),%eax
 8049895:	88 06                	mov    %al,(%esi)
 8049897:	0f b6 85 c1 5f ff ff 	movzbl -0xa03f(%ebp),%eax
 804989e:	88 46 01             	mov    %al,0x1(%esi)
 80498a1:	0f b6 85 c2 5f ff ff 	movzbl -0xa03e(%ebp),%eax
 80498a8:	88 46 02             	mov    %al,0x2(%esi)
 80498ab:	83 c6 03             	add    $0x3,%esi
 80498ae:	83 c3 01             	add    $0x1,%ebx
 80498b1:	83 ef 01             	sub    $0x1,%edi
 80498b4:	0f 85 69 ff ff ff    	jne    8049823 <submitr+0x263>
 80498ba:	e9 6f 03 00 00       	jmp    8049c2e <submitr+0x66e>
 80498bf:	89 bd b0 5f ff ff    	mov    %edi,-0xa050(%ebp)
 80498c5:	8b bd b4 5f ff ff    	mov    -0xa04c(%ebp),%edi
 80498cb:	89 5c 24 08          	mov    %ebx,0x8(%esp)
 80498cf:	89 74 24 04          	mov    %esi,0x4(%esp)
 80498d3:	89 3c 24             	mov    %edi,(%esp)
 80498d6:	e8 f5 f0 ff ff       	call   80489d0 <write@plt>
 80498db:	85 c0                	test   %eax,%eax
 80498dd:	7f 0f                	jg     80498ee <submitr+0x32e>
 80498df:	e8 4c f1 ff ff       	call   8048a30 <__errno_location@plt>
 80498e4:	83 38 04             	cmpl   $0x4,(%eax)
 80498e7:	75 15                	jne    80498fe <submitr+0x33e>
 80498e9:	b8 00 00 00 00       	mov    $0x0,%eax
 80498ee:	01 c6                	add    %eax,%esi
 80498f0:	29 c3                	sub    %eax,%ebx
 80498f2:	75 d7                	jne    80498cb <submitr+0x30b>
 80498f4:	8b bd b0 5f ff ff    	mov    -0xa050(%ebp),%edi
 80498fa:	85 ff                	test   %edi,%edi
 80498fc:	79 67                	jns    8049965 <submitr+0x3a5>
 80498fe:	8b 4d 20             	mov    0x20(%ebp),%ecx
 8049901:	c7 01 45 72 72 6f    	movl   $0x6f727245,(%ecx)
 8049907:	c7 41 04 72 3a 20 43 	movl   $0x43203a72,0x4(%ecx)
 804990e:	c7 41 08 6c 69 65 6e 	movl   $0x6e65696c,0x8(%ecx)
 8049915:	c7 41 0c 74 20 75 6e 	movl   $0x6e752074,0xc(%ecx)
 804991c:	c7 41 10 61 62 6c 65 	movl   $0x656c6261,0x10(%ecx)
 8049923:	c7 41 14 20 74 6f 20 	movl   $0x206f7420,0x14(%ecx)
 804992a:	c7 41 18 77 72 69 74 	movl   $0x74697277,0x18(%ecx)
 8049931:	c7 41 1c 65 20 74 6f 	movl   $0x6f742065,0x1c(%ecx)
 8049938:	c7 41 20 20 74 68 65 	movl   $0x65687420,0x20(%ecx)
 804993f:	c7 41 24 20 73 65 72 	movl   $0x72657320,0x24(%ecx)
 8049946:	c7 41 28 76 65 72 00 	movl   $0x726576,0x28(%ecx)
 804994d:	8b 85 b4 5f ff ff    	mov    -0xa04c(%ebp),%eax
 8049953:	89 04 24             	mov    %eax,(%esp)
 8049956:	e8 55 f1 ff ff       	call   8048ab0 <close@plt>
 804995b:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049960:	e9 a2 03 00 00       	jmp    8049d07 <submitr+0x747>
 8049965:	8b 85 b4 5f ff ff    	mov    -0xa04c(%ebp),%eax
 804996b:	89 85 cc df ff ff    	mov    %eax,-0x2034(%ebp)
 8049971:	c7 85 d0 df ff ff 00 	movl   $0x0,-0x2030(%ebp)
 8049978:	00 00 00 
 804997b:	8d 85 d8 df ff ff    	lea    -0x2028(%ebp),%eax
 8049981:	89 85 d4 df ff ff    	mov    %eax,-0x202c(%ebp)
 8049987:	b9 00 20 00 00       	mov    $0x2000,%ecx
 804998c:	8d 95 cc bf ff ff    	lea    -0x4034(%ebp),%edx
 8049992:	8d 85 cc df ff ff    	lea    -0x2034(%ebp),%eax
 8049998:	e8 f3 fa ff ff       	call   8049490 <rio_readlineb>
 804999d:	85 c0                	test   %eax,%eax
 804999f:	7f 7b                	jg     8049a1c <submitr+0x45c>
 80499a1:	8b 55 20             	mov    0x20(%ebp),%edx
 80499a4:	c7 02 45 72 72 6f    	movl   $0x6f727245,(%edx)
 80499aa:	c7 42 04 72 3a 20 43 	movl   $0x43203a72,0x4(%edx)
 80499b1:	c7 42 08 6c 69 65 6e 	movl   $0x6e65696c,0x8(%edx)
 80499b8:	c7 42 0c 74 20 75 6e 	movl   $0x6e752074,0xc(%edx)
 80499bf:	c7 42 10 61 62 6c 65 	movl   $0x656c6261,0x10(%edx)
 80499c6:	c7 42 14 20 74 6f 20 	movl   $0x206f7420,0x14(%edx)
 80499cd:	c7 42 18 72 65 61 64 	movl   $0x64616572,0x18(%edx)
 80499d4:	c7 42 1c 20 66 69 72 	movl   $0x72696620,0x1c(%edx)
 80499db:	c7 42 20 73 74 20 68 	movl   $0x68207473,0x20(%edx)
 80499e2:	c7 42 24 65 61 64 65 	movl   $0x65646165,0x24(%edx)
 80499e9:	c7 42 28 72 20 66 72 	movl   $0x72662072,0x28(%edx)
 80499f0:	c7 42 2c 6f 6d 20 73 	movl   $0x73206d6f,0x2c(%edx)
 80499f7:	c7 42 30 65 72 76 65 	movl   $0x65767265,0x30(%edx)
 80499fe:	66 c7 42 34 72 00    	movw   $0x72,0x34(%edx)
 8049a04:	8b 85 b4 5f ff ff    	mov    -0xa04c(%ebp),%eax
 8049a0a:	89 04 24             	mov    %eax,(%esp)
 8049a0d:	e8 9e f0 ff ff       	call   8048ab0 <close@plt>
 8049a12:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049a17:	e9 eb 02 00 00       	jmp    8049d07 <submitr+0x747>
 8049a1c:	8d 85 c8 5f ff ff    	lea    -0xa038(%ebp),%eax
 8049a22:	89 44 24 10          	mov    %eax,0x10(%esp)
 8049a26:	8d 85 c8 7f ff ff    	lea    -0x8038(%ebp),%eax
 8049a2c:	89 44 24 0c          	mov    %eax,0xc(%esp)
 8049a30:	8d 85 cc 7f ff ff    	lea    -0x8034(%ebp),%eax
 8049a36:	89 44 24 08          	mov    %eax,0x8(%esp)
 8049a3a:	c7 44 24 04 b7 a7 04 	movl   $0x804a7b7,0x4(%esp)
 8049a41:	08 
 8049a42:	8d 85 cc bf ff ff    	lea    -0x4034(%ebp),%eax
 8049a48:	89 04 24             	mov    %eax,(%esp)
 8049a4b:	e8 b0 ef ff ff       	call   8048a00 <__isoc99_sscanf@plt>
 8049a50:	8b 85 c8 7f ff ff    	mov    -0x8038(%ebp),%eax
 8049a56:	3d c8 00 00 00       	cmp    $0xc8,%eax
 8049a5b:	0f 84 c5 00 00 00    	je     8049b26 <submitr+0x566>
 8049a61:	8d 95 c8 5f ff ff    	lea    -0xa038(%ebp),%edx
 8049a67:	89 54 24 0c          	mov    %edx,0xc(%esp)
 8049a6b:	89 44 24 08          	mov    %eax,0x8(%esp)
 8049a6f:	c7 44 24 04 c4 a6 04 	movl   $0x804a6c4,0x4(%esp)
 8049a76:	08 
 8049a77:	8b 55 20             	mov    0x20(%ebp),%edx
 8049a7a:	89 14 24             	mov    %edx,(%esp)
 8049a7d:	e8 de ef ff ff       	call   8048a60 <sprintf@plt>
 8049a82:	8b 85 b4 5f ff ff    	mov    -0xa04c(%ebp),%eax
 8049a88:	89 04 24             	mov    %eax,(%esp)
 8049a8b:	e8 20 f0 ff ff       	call   8048ab0 <close@plt>
 8049a90:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049a95:	e9 6d 02 00 00       	jmp    8049d07 <submitr+0x747>
 8049a9a:	b9 00 20 00 00       	mov    $0x2000,%ecx
 8049a9f:	8d 95 cc bf ff ff    	lea    -0x4034(%ebp),%edx
 8049aa5:	8d 85 cc df ff ff    	lea    -0x2034(%ebp),%eax
 8049aab:	e8 e0 f9 ff ff       	call   8049490 <rio_readlineb>
 8049ab0:	85 c0                	test   %eax,%eax
 8049ab2:	7f 72                	jg     8049b26 <submitr+0x566>
 8049ab4:	8b 55 20             	mov    0x20(%ebp),%edx
 8049ab7:	c7 02 45 72 72 6f    	movl   $0x6f727245,(%edx)
 8049abd:	c7 42 04 72 3a 20 43 	movl   $0x43203a72,0x4(%edx)
 8049ac4:	c7 42 08 6c 69 65 6e 	movl   $0x6e65696c,0x8(%edx)
 8049acb:	c7 42 0c 74 20 75 6e 	movl   $0x6e752074,0xc(%edx)
 8049ad2:	c7 42 10 61 62 6c 65 	movl   $0x656c6261,0x10(%edx)
 8049ad9:	c7 42 14 20 74 6f 20 	movl   $0x206f7420,0x14(%edx)
 8049ae0:	c7 42 18 72 65 61 64 	movl   $0x64616572,0x18(%edx)
 8049ae7:	c7 42 1c 20 68 65 61 	movl   $0x61656820,0x1c(%edx)
 8049aee:	c7 42 20 64 65 72 73 	movl   $0x73726564,0x20(%edx)
 8049af5:	c7 42 24 20 66 72 6f 	movl   $0x6f726620,0x24(%edx)
 8049afc:	c7 42 28 6d 20 73 65 	movl   $0x6573206d,0x28(%edx)
 8049b03:	c7 42 2c 72 76 65 72 	movl   $0x72657672,0x2c(%edx)
 8049b0a:	c6 42 30 00          	movb   $0x0,0x30(%edx)
 8049b0e:	8b 85 b4 5f ff ff    	mov    -0xa04c(%ebp),%eax
 8049b14:	89 04 24             	mov    %eax,(%esp)
 8049b17:	e8 94 ef ff ff       	call   8048ab0 <close@plt>
 8049b1c:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049b21:	e9 e1 01 00 00       	jmp    8049d07 <submitr+0x747>
 8049b26:	80 bd cc bf ff ff 0d 	cmpb   $0xd,-0x4034(%ebp)
 8049b2d:	0f 85 67 ff ff ff    	jne    8049a9a <submitr+0x4da>
 8049b33:	80 bd cd bf ff ff 0a 	cmpb   $0xa,-0x4033(%ebp)
 8049b3a:	0f 85 5a ff ff ff    	jne    8049a9a <submitr+0x4da>
 8049b40:	80 bd ce bf ff ff 00 	cmpb   $0x0,-0x4032(%ebp)
 8049b47:	0f 85 4d ff ff ff    	jne    8049a9a <submitr+0x4da>
 8049b4d:	b9 00 20 00 00       	mov    $0x2000,%ecx
 8049b52:	8d 95 cc bf ff ff    	lea    -0x4034(%ebp),%edx
 8049b58:	8d 85 cc df ff ff    	lea    -0x2034(%ebp),%eax
 8049b5e:	e8 2d f9 ff ff       	call   8049490 <rio_readlineb>
 8049b63:	85 c0                	test   %eax,%eax
 8049b65:	7f 7c                	jg     8049be3 <submitr+0x623>
 8049b67:	8b 55 20             	mov    0x20(%ebp),%edx
 8049b6a:	c7 02 45 72 72 6f    	movl   $0x6f727245,(%edx)
 8049b70:	c7 42 04 72 3a 20 43 	movl   $0x43203a72,0x4(%edx)
 8049b77:	c7 42 08 6c 69 65 6e 	movl   $0x6e65696c,0x8(%edx)
 8049b7e:	c7 42 0c 74 20 75 6e 	movl   $0x6e752074,0xc(%edx)
 8049b85:	c7 42 10 61 62 6c 65 	movl   $0x656c6261,0x10(%edx)
 8049b8c:	c7 42 14 20 74 6f 20 	movl   $0x206f7420,0x14(%edx)
 8049b93:	c7 42 18 72 65 61 64 	movl   $0x64616572,0x18(%edx)
 8049b9a:	c7 42 1c 20 73 74 61 	movl   $0x61747320,0x1c(%edx)
 8049ba1:	c7 42 20 74 75 73 20 	movl   $0x20737574,0x20(%edx)
 8049ba8:	c7 42 24 6d 65 73 73 	movl   $0x7373656d,0x24(%edx)
 8049baf:	c7 42 28 61 67 65 20 	movl   $0x20656761,0x28(%edx)
 8049bb6:	c7 42 2c 66 72 6f 6d 	movl   $0x6d6f7266,0x2c(%edx)
 8049bbd:	c7 42 30 20 73 65 72 	movl   $0x72657320,0x30(%edx)
 8049bc4:	c7 42 34 76 65 72 00 	movl   $0x726576,0x34(%edx)
 8049bcb:	8b 85 b4 5f ff ff    	mov    -0xa04c(%ebp),%eax
 8049bd1:	89 04 24             	mov    %eax,(%esp)
 8049bd4:	e8 d7 ee ff ff       	call   8048ab0 <close@plt>
 8049bd9:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049bde:	e9 24 01 00 00       	jmp    8049d07 <submitr+0x747>
 8049be3:	8d 85 cc bf ff ff    	lea    -0x4034(%ebp),%eax
 8049be9:	89 44 24 04          	mov    %eax,0x4(%esp)
 8049bed:	8b 55 20             	mov    0x20(%ebp),%edx
 8049bf0:	89 14 24             	mov    %edx,(%esp)
 8049bf3:	e8 48 ed ff ff       	call   8048940 <strcpy@plt>
 8049bf8:	8b 85 b4 5f ff ff    	mov    -0xa04c(%ebp),%eax
 8049bfe:	89 04 24             	mov    %eax,(%esp)
 8049c01:	e8 aa ee ff ff       	call   8048ab0 <close@plt>
 8049c06:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049c0b:	8b 55 20             	mov    0x20(%ebp),%edx
 8049c0e:	80 3a 4f             	cmpb   $0x4f,(%edx)
 8049c11:	0f 85 f0 00 00 00    	jne    8049d07 <submitr+0x747>
 8049c17:	80 7a 01 4b          	cmpb   $0x4b,0x1(%edx)
 8049c1b:	0f 85 e6 00 00 00    	jne    8049d07 <submitr+0x747>
 8049c21:	80 7a 02 01          	cmpb   $0x1,0x2(%edx)
 8049c25:	19 c0                	sbb    %eax,%eax
 8049c27:	f7 d0                	not    %eax
 8049c29:	e9 d9 00 00 00       	jmp    8049d07 <submitr+0x747>
 8049c2e:	8d 85 cc 9f ff ff    	lea    -0x6034(%ebp),%eax
 8049c34:	89 44 24 14          	mov    %eax,0x14(%esp)
 8049c38:	8b 4d 18             	mov    0x18(%ebp),%ecx
 8049c3b:	89 4c 24 10          	mov    %ecx,0x10(%esp)
 8049c3f:	8b 45 14             	mov    0x14(%ebp),%eax
 8049c42:	89 44 24 0c          	mov    %eax,0xc(%esp)
 8049c46:	8b 55 10             	mov    0x10(%ebp),%edx
 8049c49:	89 54 24 08          	mov    %edx,0x8(%esp)
 8049c4d:	c7 44 24 04 f4 a6 04 	movl   $0x804a6f4,0x4(%esp)
 8049c54:	08 
 8049c55:	8d bd cc bf ff ff    	lea    -0x4034(%ebp),%edi
 8049c5b:	89 3c 24             	mov    %edi,(%esp)
 8049c5e:	e8 fd ed ff ff       	call   8048a60 <sprintf@plt>
 8049c63:	b8 00 00 00 00       	mov    $0x0,%eax
 8049c68:	b9 ff ff ff ff       	mov    $0xffffffff,%ecx
 8049c6d:	f2 ae                	repnz scas %es:(%edi),%al
 8049c6f:	f7 d1                	not    %ecx
 8049c71:	8d 79 ff             	lea    -0x1(%ecx),%edi
 8049c74:	89 fb                	mov    %edi,%ebx
 8049c76:	8d b5 cc bf ff ff    	lea    -0x4034(%ebp),%esi
 8049c7c:	85 ff                	test   %edi,%edi
 8049c7e:	0f 85 3b fc ff ff    	jne    80498bf <submitr+0x2ff>
 8049c84:	e9 dc fc ff ff       	jmp    8049965 <submitr+0x3a5>
 8049c89:	8b 7d 20             	mov    0x20(%ebp),%edi
 8049c8c:	be 40 a7 04 08       	mov    $0x804a740,%esi
 8049c91:	b8 43 00 00 00       	mov    $0x43,%eax
 8049c96:	f7 c7 01 00 00 00    	test   $0x1,%edi
 8049c9c:	74 19                	je     8049cb7 <submitr+0x6f7>
 8049c9e:	0f b6 05 40 a7 04 08 	movzbl 0x804a740,%eax
 8049ca5:	88 07                	mov    %al,(%edi)
 8049ca7:	8b 7d 20             	mov    0x20(%ebp),%edi
 8049caa:	83 c7 01             	add    $0x1,%edi
 8049cad:	be 41 a7 04 08       	mov    $0x804a741,%esi
 8049cb2:	b8 42 00 00 00       	mov    $0x42,%eax
 8049cb7:	f7 c7 02 00 00 00    	test   $0x2,%edi
 8049cbd:	74 0f                	je     8049cce <submitr+0x70e>
 8049cbf:	0f b7 16             	movzwl (%esi),%edx
 8049cc2:	66 89 17             	mov    %dx,(%edi)
 8049cc5:	83 c7 02             	add    $0x2,%edi
 8049cc8:	83 c6 02             	add    $0x2,%esi
 8049ccb:	83 e8 02             	sub    $0x2,%eax
 8049cce:	89 c1                	mov    %eax,%ecx
 8049cd0:	c1 e9 02             	shr    $0x2,%ecx
 8049cd3:	f3 a5                	rep movsl %ds:(%esi),%es:(%edi)
 8049cd5:	ba 00 00 00 00       	mov    $0x0,%edx
 8049cda:	a8 02                	test   $0x2,%al
 8049cdc:	74 0b                	je     8049ce9 <submitr+0x729>
 8049cde:	0f b7 16             	movzwl (%esi),%edx
 8049ce1:	66 89 17             	mov    %dx,(%edi)
 8049ce4:	ba 02 00 00 00       	mov    $0x2,%edx
 8049ce9:	a8 01                	test   $0x1,%al
 8049ceb:	74 07                	je     8049cf4 <submitr+0x734>
 8049ced:	0f b6 04 16          	movzbl (%esi,%edx,1),%eax
 8049cf1:	88 04 17             	mov    %al,(%edi,%edx,1)
 8049cf4:	8b 85 b4 5f ff ff    	mov    -0xa04c(%ebp),%eax
 8049cfa:	89 04 24             	mov    %eax,(%esp)
 8049cfd:	e8 ae ed ff ff       	call   8048ab0 <close@plt>
 8049d02:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049d07:	81 c4 6c a0 00 00    	add    $0xa06c,%esp
 8049d0d:	5b                   	pop    %ebx
 8049d0e:	5e                   	pop    %esi
 8049d0f:	5f                   	pop    %edi
 8049d10:	5d                   	pop    %ebp
 8049d11:	c3                   	ret    

08049d12 <init_timeout>:
 8049d12:	55                   	push   %ebp
 8049d13:	89 e5                	mov    %esp,%ebp
 8049d15:	53                   	push   %ebx
 8049d16:	83 ec 14             	sub    $0x14,%esp
 8049d19:	8b 5d 08             	mov    0x8(%ebp),%ebx
 8049d1c:	85 db                	test   %ebx,%ebx
 8049d1e:	74 25                	je     8049d45 <init_timeout+0x33>
 8049d20:	85 db                	test   %ebx,%ebx
 8049d22:	79 05                	jns    8049d29 <init_timeout+0x17>
 8049d24:	bb 02 00 00 00       	mov    $0x2,%ebx
 8049d29:	c7 44 24 04 9a 95 04 	movl   $0x804959a,0x4(%esp)
 8049d30:	08 
 8049d31:	c7 04 24 0e 00 00 00 	movl   $0xe,(%esp)
 8049d38:	e8 b3 eb ff ff       	call   80488f0 <signal@plt>
 8049d3d:	89 1c 24             	mov    %ebx,(%esp)
 8049d40:	e8 bb eb ff ff       	call   8048900 <alarm@plt>
 8049d45:	83 c4 14             	add    $0x14,%esp
 8049d48:	5b                   	pop    %ebx
 8049d49:	5d                   	pop    %ebp
 8049d4a:	c3                   	ret    

08049d4b <init_driver>:
 8049d4b:	55                   	push   %ebp
 8049d4c:	89 e5                	mov    %esp,%ebp
 8049d4e:	57                   	push   %edi
 8049d4f:	56                   	push   %esi
 8049d50:	53                   	push   %ebx
 8049d51:	83 ec 2c             	sub    $0x2c,%esp
 8049d54:	8b 75 08             	mov    0x8(%ebp),%esi
 8049d57:	c7 44 24 04 01 00 00 	movl   $0x1,0x4(%esp)
 8049d5e:	00 
 8049d5f:	c7 04 24 0d 00 00 00 	movl   $0xd,(%esp)
 8049d66:	e8 85 eb ff ff       	call   80488f0 <signal@plt>
 8049d6b:	c7 44 24 04 01 00 00 	movl   $0x1,0x4(%esp)
 8049d72:	00 
 8049d73:	c7 04 24 1d 00 00 00 	movl   $0x1d,(%esp)
 8049d7a:	e8 71 eb ff ff       	call   80488f0 <signal@plt>
 8049d7f:	c7 44 24 04 01 00 00 	movl   $0x1,0x4(%esp)
 8049d86:	00 
 8049d87:	c7 04 24 1d 00 00 00 	movl   $0x1d,(%esp)
 8049d8e:	e8 5d eb ff ff       	call   80488f0 <signal@plt>
 8049d93:	c7 44 24 08 00 00 00 	movl   $0x0,0x8(%esp)
 8049d9a:	00 
 8049d9b:	c7 44 24 04 01 00 00 	movl   $0x1,0x4(%esp)
 8049da2:	00 
 8049da3:	c7 04 24 02 00 00 00 	movl   $0x2,(%esp)
 8049daa:	e8 c1 ec ff ff       	call   8048a70 <socket@plt>
 8049daf:	89 c3                	mov    %eax,%ebx
 8049db1:	85 c0                	test   %eax,%eax
 8049db3:	79 4e                	jns    8049e03 <init_driver+0xb8>
 8049db5:	c7 06 45 72 72 6f    	movl   $0x6f727245,(%esi)
 8049dbb:	c7 46 04 72 3a 20 43 	movl   $0x43203a72,0x4(%esi)
 8049dc2:	c7 46 08 6c 69 65 6e 	movl   $0x6e65696c,0x8(%esi)
 8049dc9:	c7 46 0c 74 20 75 6e 	movl   $0x6e752074,0xc(%esi)
 8049dd0:	c7 46 10 61 62 6c 65 	movl   $0x656c6261,0x10(%esi)
 8049dd7:	c7 46 14 20 74 6f 20 	movl   $0x206f7420,0x14(%esi)
 8049dde:	c7 46 18 63 72 65 61 	movl   $0x61657263,0x18(%esi)
 8049de5:	c7 46 1c 74 65 20 73 	movl   $0x73206574,0x1c(%esi)
 8049dec:	c7 46 20 6f 63 6b 65 	movl   $0x656b636f,0x20(%esi)
 8049df3:	66 c7 46 24 74 00    	movw   $0x74,0x24(%esi)
 8049df9:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049dfe:	e9 dd 00 00 00       	jmp    8049ee0 <init_driver+0x195>
 8049e03:	c7 04 24 c8 a7 04 08 	movl   $0x804a7c8,(%esp)
 8049e0a:	e8 81 ec ff ff       	call   8048a90 <gethostbyname@plt>
 8049e0f:	85 c0                	test   %eax,%eax
 8049e11:	75 2a                	jne    8049e3d <init_driver+0xf2>
 8049e13:	c7 44 24 08 c8 a7 04 	movl   $0x804a7c8,0x8(%esp)
 8049e1a:	08 
 8049e1b:	c7 44 24 04 70 a6 04 	movl   $0x804a670,0x4(%esp)
 8049e22:	08 
 8049e23:	89 34 24             	mov    %esi,(%esp)
 8049e26:	e8 35 ec ff ff       	call   8048a60 <sprintf@plt>
 8049e2b:	89 1c 24             	mov    %ebx,(%esp)
 8049e2e:	e8 7d ec ff ff       	call   8048ab0 <close@plt>
 8049e33:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049e38:	e9 a3 00 00 00       	jmp    8049ee0 <init_driver+0x195>
 8049e3d:	8d 7d d8             	lea    -0x28(%ebp),%edi
 8049e40:	c7 45 d8 00 00 00 00 	movl   $0x0,-0x28(%ebp)
 8049e47:	c7 45 dc 00 00 00 00 	movl   $0x0,-0x24(%ebp)
 8049e4e:	c7 45 e0 00 00 00 00 	movl   $0x0,-0x20(%ebp)
 8049e55:	c7 45 e4 00 00 00 00 	movl   $0x0,-0x1c(%ebp)
 8049e5c:	66 c7 45 d8 02 00    	movw   $0x2,-0x28(%ebp)
 8049e62:	8b 50 0c             	mov    0xc(%eax),%edx
 8049e65:	89 54 24 08          	mov    %edx,0x8(%esp)
 8049e69:	8d 55 dc             	lea    -0x24(%ebp),%edx
 8049e6c:	89 54 24 04          	mov    %edx,0x4(%esp)
 8049e70:	8b 40 10             	mov    0x10(%eax),%eax
 8049e73:	8b 00                	mov    (%eax),%eax
 8049e75:	89 04 24             	mov    %eax,(%esp)
 8049e78:	e8 b3 ea ff ff       	call   8048930 <bcopy@plt>
 8049e7d:	66 c7 45 da 47 26    	movw   $0x2647,-0x26(%ebp)
 8049e83:	c7 44 24 08 10 00 00 	movl   $0x10,0x8(%esp)
 8049e8a:	00 
 8049e8b:	89 7c 24 04          	mov    %edi,0x4(%esp)
 8049e8f:	89 1c 24             	mov    %ebx,(%esp)
 8049e92:	e8 09 ec ff ff       	call   8048aa0 <connect@plt>
 8049e97:	85 c0                	test   %eax,%eax
 8049e99:	79 2f                	jns    8049eca <init_driver+0x17f>
 8049e9b:	c7 44 24 0c 26 47 00 	movl   $0x4726,0xc(%esp)
 8049ea2:	00 
 8049ea3:	c7 44 24 08 c8 a7 04 	movl   $0x804a7c8,0x8(%esp)
 8049eaa:	08 
 8049eab:	c7 44 24 04 84 a7 04 	movl   $0x804a784,0x4(%esp)
 8049eb2:	08 
 8049eb3:	89 34 24             	mov    %esi,(%esp)
 8049eb6:	e8 a5 eb ff ff       	call   8048a60 <sprintf@plt>
 8049ebb:	89 1c 24             	mov    %ebx,(%esp)
 8049ebe:	e8 ed eb ff ff       	call   8048ab0 <close@plt>
 8049ec3:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049ec8:	eb 16                	jmp    8049ee0 <init_driver+0x195>
 8049eca:	89 1c 24             	mov    %ebx,(%esp)
 8049ecd:	e8 de eb ff ff       	call   8048ab0 <close@plt>
 8049ed2:	66 c7 06 4f 4b       	movw   $0x4b4f,(%esi)
 8049ed7:	c6 46 02 00          	movb   $0x0,0x2(%esi)
 8049edb:	b8 00 00 00 00       	mov    $0x0,%eax
 8049ee0:	83 c4 2c             	add    $0x2c,%esp
 8049ee3:	5b                   	pop    %ebx
 8049ee4:	5e                   	pop    %esi
 8049ee5:	5f                   	pop    %edi
 8049ee6:	5d                   	pop    %ebp
 8049ee7:	c3                   	ret    

08049ee8 <driver_post>:
 8049ee8:	55                   	push   %ebp
 8049ee9:	89 e5                	mov    %esp,%ebp
 8049eeb:	53                   	push   %ebx
 8049eec:	83 ec 24             	sub    $0x24,%esp
 8049eef:	8b 45 08             	mov    0x8(%ebp),%eax
 8049ef2:	8b 5d 14             	mov    0x14(%ebp),%ebx
 8049ef5:	83 7d 10 00          	cmpl   $0x0,0x10(%ebp)
 8049ef9:	74 23                	je     8049f1e <driver_post+0x36>
 8049efb:	8b 45 0c             	mov    0xc(%ebp),%eax
 8049efe:	89 44 24 04          	mov    %eax,0x4(%esp)
 8049f02:	c7 04 24 d6 a7 04 08 	movl   $0x804a7d6,(%esp)
 8049f09:	e8 c2 e9 ff ff       	call   80488d0 <printf@plt>
 8049f0e:	66 c7 03 4f 4b       	movw   $0x4b4f,(%ebx)
 8049f13:	c6 43 02 00          	movb   $0x0,0x2(%ebx)
 8049f17:	b8 00 00 00 00       	mov    $0x0,%eax
 8049f1c:	eb 4c                	jmp    8049f6a <driver_post+0x82>
 8049f1e:	85 c0                	test   %eax,%eax
 8049f20:	74 3a                	je     8049f5c <driver_post+0x74>
 8049f22:	80 38 00             	cmpb   $0x0,(%eax)
 8049f25:	74 35                	je     8049f5c <driver_post+0x74>
 8049f27:	89 5c 24 18          	mov    %ebx,0x18(%esp)
 8049f2b:	8b 55 0c             	mov    0xc(%ebp),%edx
 8049f2e:	89 54 24 14          	mov    %edx,0x14(%esp)
 8049f32:	c7 44 24 10 ed a7 04 	movl   $0x804a7ed,0x10(%esp)
 8049f39:	08 
 8049f3a:	89 44 24 0c          	mov    %eax,0xc(%esp)
 8049f3e:	c7 44 24 08 f4 a7 04 	movl   $0x804a7f4,0x8(%esp)
 8049f45:	08 
 8049f46:	c7 44 24 04 26 47 00 	movl   $0x4726,0x4(%esp)
 8049f4d:	00 
 8049f4e:	c7 04 24 c8 a7 04 08 	movl   $0x804a7c8,(%esp)
 8049f55:	e8 66 f6 ff ff       	call   80495c0 <submitr>
 8049f5a:	eb 0e                	jmp    8049f6a <driver_post+0x82>
 8049f5c:	66 c7 03 4f 4b       	movw   $0x4b4f,(%ebx)
 8049f61:	c6 43 02 00          	movb   $0x0,0x2(%ebx)
 8049f65:	b8 00 00 00 00       	mov    $0x0,%eax
 8049f6a:	83 c4 24             	add    $0x24,%esp
 8049f6d:	5b                   	pop    %ebx
 8049f6e:	5d                   	pop    %ebp
 8049f6f:	c3                   	ret    

08049f70 <hash>:
 8049f70:	55                   	push   %ebp
 8049f71:	89 e5                	mov    %esp,%ebp
 8049f73:	8b 4d 08             	mov    0x8(%ebp),%ecx
 8049f76:	0f b6 11             	movzbl (%ecx),%edx
 8049f79:	84 d2                	test   %dl,%dl
 8049f7b:	74 19                	je     8049f96 <hash+0x26>
 8049f7d:	b8 00 00 00 00       	mov    $0x0,%eax
 8049f82:	6b c0 67             	imul   $0x67,%eax,%eax
 8049f85:	0f be d2             	movsbl %dl,%edx
 8049f88:	01 d0                	add    %edx,%eax
 8049f8a:	83 c1 01             	add    $0x1,%ecx
 8049f8d:	0f b6 11             	movzbl (%ecx),%edx
 8049f90:	84 d2                	test   %dl,%dl
 8049f92:	75 ee                	jne    8049f82 <hash+0x12>
 8049f94:	eb 05                	jmp    8049f9b <hash+0x2b>
 8049f96:	b8 00 00 00 00       	mov    $0x0,%eax
 8049f9b:	5d                   	pop    %ebp
 8049f9c:	c3                   	ret    

08049f9d <check>:
 8049f9d:	55                   	push   %ebp
 8049f9e:	89 e5                	mov    %esp,%ebp
 8049fa0:	8b 55 08             	mov    0x8(%ebp),%edx
 8049fa3:	89 d1                	mov    %edx,%ecx
 8049fa5:	c1 e9 1c             	shr    $0x1c,%ecx
 8049fa8:	b8 00 00 00 00       	mov    $0x0,%eax
 8049fad:	85 c9                	test   %ecx,%ecx
 8049faf:	74 37                	je     8049fe8 <check+0x4b>
 8049fb1:	80 fa 0a             	cmp    $0xa,%dl
 8049fb4:	74 1f                	je     8049fd5 <check+0x38>
 8049fb6:	0f b6 c6             	movzbl %dh,%eax
 8049fb9:	83 f8 0a             	cmp    $0xa,%eax
 8049fbc:	74 1e                	je     8049fdc <check+0x3f>
 8049fbe:	89 d0                	mov    %edx,%eax
 8049fc0:	c1 e8 10             	shr    $0x10,%eax
 8049fc3:	3c 0a                	cmp    $0xa,%al
 8049fc5:	74 1c                	je     8049fe3 <check+0x46>
 8049fc7:	c1 ea 18             	shr    $0x18,%edx
 8049fca:	83 fa 0a             	cmp    $0xa,%edx
 8049fcd:	0f 95 c0             	setne  %al
 8049fd0:	0f b6 c0             	movzbl %al,%eax
 8049fd3:	eb 13                	jmp    8049fe8 <check+0x4b>
 8049fd5:	b8 00 00 00 00       	mov    $0x0,%eax
 8049fda:	eb 0c                	jmp    8049fe8 <check+0x4b>
 8049fdc:	b8 00 00 00 00       	mov    $0x0,%eax
 8049fe1:	eb 05                	jmp    8049fe8 <check+0x4b>
 8049fe3:	b8 00 00 00 00       	mov    $0x0,%eax
 8049fe8:	5d                   	pop    %ebp
 8049fe9:	c3                   	ret    

08049fea <gencookie>:
 8049fea:	55                   	push   %ebp
 8049feb:	89 e5                	mov    %esp,%ebp
 8049fed:	53                   	push   %ebx
 8049fee:	83 ec 14             	sub    $0x14,%esp
 8049ff1:	8b 45 08             	mov    0x8(%ebp),%eax
 8049ff4:	89 04 24             	mov    %eax,(%esp)
 8049ff7:	e8 74 ff ff ff       	call   8049f70 <hash>
 8049ffc:	89 04 24             	mov    %eax,(%esp)
 8049fff:	e8 9c e9 ff ff       	call   80489a0 <srand@plt>
 804a004:	e8 37 ea ff ff       	call   8048a40 <rand@plt>
 804a009:	89 c3                	mov    %eax,%ebx
 804a00b:	89 04 24             	mov    %eax,(%esp)
 804a00e:	e8 8a ff ff ff       	call   8049f9d <check>
 804a013:	85 c0                	test   %eax,%eax
 804a015:	74 ed                	je     804a004 <gencookie+0x1a>
 804a017:	89 d8                	mov    %ebx,%eax
 804a019:	83 c4 14             	add    $0x14,%esp
 804a01c:	5b                   	pop    %ebx
 804a01d:	5d                   	pop    %ebp
 804a01e:	c3                   	ret    
 804a01f:	90                   	nop

0804a020 <__libc_csu_fini>:
 804a020:	55                   	push   %ebp
 804a021:	89 e5                	mov    %esp,%ebp
 804a023:	5d                   	pop    %ebp
 804a024:	c3                   	ret    
 804a025:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
 804a029:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

0804a030 <__libc_csu_init>:
 804a030:	55                   	push   %ebp
 804a031:	89 e5                	mov    %esp,%ebp
 804a033:	57                   	push   %edi
 804a034:	56                   	push   %esi
 804a035:	53                   	push   %ebx
 804a036:	e8 4f 00 00 00       	call   804a08a <__i686.get_pc_thunk.bx>
 804a03b:	81 c3 c5 10 00 00    	add    $0x10c5,%ebx
 804a041:	83 ec 1c             	sub    $0x1c,%esp
 804a044:	e8 2f e8 ff ff       	call   8048878 <_init>
 804a049:	8d bb 04 ff ff ff    	lea    -0xfc(%ebx),%edi
 804a04f:	8d 83 00 ff ff ff    	lea    -0x100(%ebx),%eax
 804a055:	29 c7                	sub    %eax,%edi
 804a057:	c1 ff 02             	sar    $0x2,%edi
 804a05a:	85 ff                	test   %edi,%edi
 804a05c:	74 24                	je     804a082 <__libc_csu_init+0x52>
 804a05e:	31 f6                	xor    %esi,%esi
 804a060:	8b 45 10             	mov    0x10(%ebp),%eax
 804a063:	89 44 24 08          	mov    %eax,0x8(%esp)
 804a067:	8b 45 0c             	mov    0xc(%ebp),%eax
 804a06a:	89 44 24 04          	mov    %eax,0x4(%esp)
 804a06e:	8b 45 08             	mov    0x8(%ebp),%eax
 804a071:	89 04 24             	mov    %eax,(%esp)
 804a074:	ff 94 b3 00 ff ff ff 	call   *-0x100(%ebx,%esi,4)
 804a07b:	83 c6 01             	add    $0x1,%esi
 804a07e:	39 fe                	cmp    %edi,%esi
 804a080:	72 de                	jb     804a060 <__libc_csu_init+0x30>
 804a082:	83 c4 1c             	add    $0x1c,%esp
 804a085:	5b                   	pop    %ebx
 804a086:	5e                   	pop    %esi
 804a087:	5f                   	pop    %edi
 804a088:	5d                   	pop    %ebp
 804a089:	c3                   	ret    

0804a08a <__i686.get_pc_thunk.bx>:
 804a08a:	8b 1c 24             	mov    (%esp),%ebx
 804a08d:	c3                   	ret    
 804a08e:	90                   	nop
 804a08f:	90                   	nop

Disassembly of section .fini:

0804a090 <_fini>:
 804a090:	55                   	push   %ebp
 804a091:	89 e5                	mov    %esp,%ebp
 804a093:	53                   	push   %ebx
 804a094:	83 ec 04             	sub    $0x4,%esp
 804a097:	e8 00 00 00 00       	call   804a09c <_fini+0xc>
 804a09c:	5b                   	pop    %ebx
 804a09d:	81 c3 64 10 00 00    	add    $0x1064,%ebx
 804a0a3:	59                   	pop    %ecx
 804a0a4:	5b                   	pop    %ebx
 804a0a5:	c9                   	leave  
 804a0a6:	c3                   	ret    
