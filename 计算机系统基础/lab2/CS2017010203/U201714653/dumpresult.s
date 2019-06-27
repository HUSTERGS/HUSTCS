
./bomb:     file format elf32-i386


Disassembly of section .init:

080486f4 <_init>:
 80486f4:	53                   	push   %ebx
 80486f5:	83 ec 08             	sub    $0x8,%esp
 80486f8:	e8 13 02 00 00       	call   8048910 <__x86.get_pc_thunk.bx>
 80486fd:	81 c3 03 39 00 00    	add    $0x3903,%ebx
 8048703:	8b 83 fc ff ff ff    	mov    -0x4(%ebx),%eax
 8048709:	85 c0                	test   %eax,%eax
 804870b:	74 05                	je     8048712 <_init+0x1e>
 804870d:	e8 be 01 00 00       	call   80488d0 <__gmon_start__@plt>
 8048712:	83 c4 08             	add    $0x8,%esp
 8048715:	5b                   	pop    %ebx
 8048716:	c3                   	ret    

Disassembly of section .plt:

08048720 <.plt>:
 8048720:	ff 35 04 c0 04 08    	pushl  0x804c004
 8048726:	ff 25 08 c0 04 08    	jmp    *0x804c008
 804872c:	00 00                	add    %al,(%eax)
	...

08048730 <read@plt>:
 8048730:	ff 25 0c c0 04 08    	jmp    *0x804c00c
 8048736:	68 00 00 00 00       	push   $0x0
 804873b:	e9 e0 ff ff ff       	jmp    8048720 <.plt>

08048740 <fflush@plt>:
 8048740:	ff 25 10 c0 04 08    	jmp    *0x804c010
 8048746:	68 08 00 00 00       	push   $0x8
 804874b:	e9 d0 ff ff ff       	jmp    8048720 <.plt>

08048750 <fgets@plt>:
 8048750:	ff 25 14 c0 04 08    	jmp    *0x804c014
 8048756:	68 10 00 00 00       	push   $0x10
 804875b:	e9 c0 ff ff ff       	jmp    8048720 <.plt>

08048760 <signal@plt>:
 8048760:	ff 25 18 c0 04 08    	jmp    *0x804c018
 8048766:	68 18 00 00 00       	push   $0x18
 804876b:	e9 b0 ff ff ff       	jmp    8048720 <.plt>

08048770 <sleep@plt>:
 8048770:	ff 25 1c c0 04 08    	jmp    *0x804c01c
 8048776:	68 20 00 00 00       	push   $0x20
 804877b:	e9 a0 ff ff ff       	jmp    8048720 <.plt>

08048780 <alarm@plt>:
 8048780:	ff 25 20 c0 04 08    	jmp    *0x804c020
 8048786:	68 28 00 00 00       	push   $0x28
 804878b:	e9 90 ff ff ff       	jmp    8048720 <.plt>

08048790 <__stack_chk_fail@plt>:
 8048790:	ff 25 24 c0 04 08    	jmp    *0x804c024
 8048796:	68 30 00 00 00       	push   $0x30
 804879b:	e9 80 ff ff ff       	jmp    8048720 <.plt>

080487a0 <strcpy@plt>:
 80487a0:	ff 25 28 c0 04 08    	jmp    *0x804c028
 80487a6:	68 38 00 00 00       	push   $0x38
 80487ab:	e9 70 ff ff ff       	jmp    8048720 <.plt>

080487b0 <getenv@plt>:
 80487b0:	ff 25 2c c0 04 08    	jmp    *0x804c02c
 80487b6:	68 40 00 00 00       	push   $0x40
 80487bb:	e9 60 ff ff ff       	jmp    8048720 <.plt>

080487c0 <puts@plt>:
 80487c0:	ff 25 30 c0 04 08    	jmp    *0x804c030
 80487c6:	68 48 00 00 00       	push   $0x48
 80487cb:	e9 50 ff ff ff       	jmp    8048720 <.plt>

080487d0 <__memmove_chk@plt>:
 80487d0:	ff 25 34 c0 04 08    	jmp    *0x804c034
 80487d6:	68 50 00 00 00       	push   $0x50
 80487db:	e9 40 ff ff ff       	jmp    8048720 <.plt>

080487e0 <exit@plt>:
 80487e0:	ff 25 38 c0 04 08    	jmp    *0x804c038
 80487e6:	68 58 00 00 00       	push   $0x58
 80487eb:	e9 30 ff ff ff       	jmp    8048720 <.plt>

080487f0 <__libc_start_main@plt>:
 80487f0:	ff 25 3c c0 04 08    	jmp    *0x804c03c
 80487f6:	68 60 00 00 00       	push   $0x60
 80487fb:	e9 20 ff ff ff       	jmp    8048720 <.plt>

08048800 <write@plt>:
 8048800:	ff 25 40 c0 04 08    	jmp    *0x804c040
 8048806:	68 68 00 00 00       	push   $0x68
 804880b:	e9 10 ff ff ff       	jmp    8048720 <.plt>

08048810 <__isoc99_sscanf@plt>:
 8048810:	ff 25 44 c0 04 08    	jmp    *0x804c044
 8048816:	68 70 00 00 00       	push   $0x70
 804881b:	e9 00 ff ff ff       	jmp    8048720 <.plt>

08048820 <fopen@plt>:
 8048820:	ff 25 48 c0 04 08    	jmp    *0x804c048
 8048826:	68 78 00 00 00       	push   $0x78
 804882b:	e9 f0 fe ff ff       	jmp    8048720 <.plt>

08048830 <__errno_location@plt>:
 8048830:	ff 25 4c c0 04 08    	jmp    *0x804c04c
 8048836:	68 80 00 00 00       	push   $0x80
 804883b:	e9 e0 fe ff ff       	jmp    8048720 <.plt>

08048840 <__printf_chk@plt>:
 8048840:	ff 25 50 c0 04 08    	jmp    *0x804c050
 8048846:	68 88 00 00 00       	push   $0x88
 804884b:	e9 d0 fe ff ff       	jmp    8048720 <.plt>

08048850 <socket@plt>:
 8048850:	ff 25 54 c0 04 08    	jmp    *0x804c054
 8048856:	68 90 00 00 00       	push   $0x90
 804885b:	e9 c0 fe ff ff       	jmp    8048720 <.plt>

08048860 <__fprintf_chk@plt>:
 8048860:	ff 25 58 c0 04 08    	jmp    *0x804c058
 8048866:	68 98 00 00 00       	push   $0x98
 804886b:	e9 b0 fe ff ff       	jmp    8048720 <.plt>

08048870 <gethostbyname@plt>:
 8048870:	ff 25 5c c0 04 08    	jmp    *0x804c05c
 8048876:	68 a0 00 00 00       	push   $0xa0
 804887b:	e9 a0 fe ff ff       	jmp    8048720 <.plt>

08048880 <strtol@plt>:
 8048880:	ff 25 60 c0 04 08    	jmp    *0x804c060
 8048886:	68 a8 00 00 00       	push   $0xa8
 804888b:	e9 90 fe ff ff       	jmp    8048720 <.plt>

08048890 <connect@plt>:
 8048890:	ff 25 64 c0 04 08    	jmp    *0x804c064
 8048896:	68 b0 00 00 00       	push   $0xb0
 804889b:	e9 80 fe ff ff       	jmp    8048720 <.plt>

080488a0 <close@plt>:
 80488a0:	ff 25 68 c0 04 08    	jmp    *0x804c068
 80488a6:	68 b8 00 00 00       	push   $0xb8
 80488ab:	e9 70 fe ff ff       	jmp    8048720 <.plt>

080488b0 <__ctype_b_loc@plt>:
 80488b0:	ff 25 6c c0 04 08    	jmp    *0x804c06c
 80488b6:	68 c0 00 00 00       	push   $0xc0
 80488bb:	e9 60 fe ff ff       	jmp    8048720 <.plt>

080488c0 <__sprintf_chk@plt>:
 80488c0:	ff 25 70 c0 04 08    	jmp    *0x804c070
 80488c6:	68 c8 00 00 00       	push   $0xc8
 80488cb:	e9 50 fe ff ff       	jmp    8048720 <.plt>

Disassembly of section .plt.got:

080488d0 <__gmon_start__@plt>:
 80488d0:	ff 25 fc bf 04 08    	jmp    *0x804bffc
 80488d6:	66 90                	xchg   %ax,%ax

Disassembly of section .text:

080488e0 <_start>:
 80488e0:	31 ed                	xor    %ebp,%ebp
 80488e2:	5e                   	pop    %esi
 80488e3:	89 e1                	mov    %esp,%ecx
 80488e5:	83 e4 f0             	and    $0xfffffff0,%esp
 80488e8:	50                   	push   %eax
 80488e9:	54                   	push   %esp
 80488ea:	52                   	push   %edx
 80488eb:	68 c0 9e 04 08       	push   $0x8049ec0
 80488f0:	68 60 9e 04 08       	push   $0x8049e60
 80488f5:	51                   	push   %ecx
 80488f6:	56                   	push   %esi
 80488f7:	68 db 89 04 08       	push   $0x80489db
 80488fc:	e8 ef fe ff ff       	call   80487f0 <__libc_start_main@plt>
 8048901:	f4                   	hlt    
 8048902:	66 90                	xchg   %ax,%ax
 8048904:	66 90                	xchg   %ax,%ax
 8048906:	66 90                	xchg   %ax,%ax
 8048908:	66 90                	xchg   %ax,%ax
 804890a:	66 90                	xchg   %ax,%ax
 804890c:	66 90                	xchg   %ax,%ax
 804890e:	66 90                	xchg   %ax,%ax

08048910 <__x86.get_pc_thunk.bx>:
 8048910:	8b 1c 24             	mov    (%esp),%ebx
 8048913:	c3                   	ret    
 8048914:	66 90                	xchg   %ax,%ax
 8048916:	66 90                	xchg   %ax,%ax
 8048918:	66 90                	xchg   %ax,%ax
 804891a:	66 90                	xchg   %ax,%ax
 804891c:	66 90                	xchg   %ax,%ax
 804891e:	66 90                	xchg   %ax,%ax

08048920 <deregister_tm_clones>:
 8048920:	b8 a3 c3 04 08       	mov    $0x804c3a3,%eax
 8048925:	2d a0 c3 04 08       	sub    $0x804c3a0,%eax
 804892a:	83 f8 06             	cmp    $0x6,%eax
 804892d:	76 1a                	jbe    8048949 <deregister_tm_clones+0x29>
 804892f:	b8 00 00 00 00       	mov    $0x0,%eax
 8048934:	85 c0                	test   %eax,%eax
 8048936:	74 11                	je     8048949 <deregister_tm_clones+0x29>
 8048938:	55                   	push   %ebp
 8048939:	89 e5                	mov    %esp,%ebp
 804893b:	83 ec 14             	sub    $0x14,%esp
 804893e:	68 a0 c3 04 08       	push   $0x804c3a0
 8048943:	ff d0                	call   *%eax
 8048945:	83 c4 10             	add    $0x10,%esp
 8048948:	c9                   	leave  
 8048949:	f3 c3                	repz ret 
 804894b:	90                   	nop
 804894c:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi

08048950 <register_tm_clones>:
 8048950:	b8 a0 c3 04 08       	mov    $0x804c3a0,%eax
 8048955:	2d a0 c3 04 08       	sub    $0x804c3a0,%eax
 804895a:	c1 f8 02             	sar    $0x2,%eax
 804895d:	89 c2                	mov    %eax,%edx
 804895f:	c1 ea 1f             	shr    $0x1f,%edx
 8048962:	01 d0                	add    %edx,%eax
 8048964:	d1 f8                	sar    %eax
 8048966:	74 1b                	je     8048983 <register_tm_clones+0x33>
 8048968:	ba 00 00 00 00       	mov    $0x0,%edx
 804896d:	85 d2                	test   %edx,%edx
 804896f:	74 12                	je     8048983 <register_tm_clones+0x33>
 8048971:	55                   	push   %ebp
 8048972:	89 e5                	mov    %esp,%ebp
 8048974:	83 ec 10             	sub    $0x10,%esp
 8048977:	50                   	push   %eax
 8048978:	68 a0 c3 04 08       	push   $0x804c3a0
 804897d:	ff d2                	call   *%edx
 804897f:	83 c4 10             	add    $0x10,%esp
 8048982:	c9                   	leave  
 8048983:	f3 c3                	repz ret 
 8048985:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
 8048989:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

08048990 <__do_global_dtors_aux>:
 8048990:	80 3d c8 c3 04 08 00 	cmpb   $0x0,0x804c3c8
 8048997:	75 13                	jne    80489ac <__do_global_dtors_aux+0x1c>
 8048999:	55                   	push   %ebp
 804899a:	89 e5                	mov    %esp,%ebp
 804899c:	83 ec 08             	sub    $0x8,%esp
 804899f:	e8 7c ff ff ff       	call   8048920 <deregister_tm_clones>
 80489a4:	c6 05 c8 c3 04 08 01 	movb   $0x1,0x804c3c8
 80489ab:	c9                   	leave  
 80489ac:	f3 c3                	repz ret 
 80489ae:	66 90                	xchg   %ax,%ax

080489b0 <frame_dummy>:
 80489b0:	b8 10 bf 04 08       	mov    $0x804bf10,%eax
 80489b5:	8b 10                	mov    (%eax),%edx
 80489b7:	85 d2                	test   %edx,%edx
 80489b9:	75 05                	jne    80489c0 <frame_dummy+0x10>
 80489bb:	eb 93                	jmp    8048950 <register_tm_clones>
 80489bd:	8d 76 00             	lea    0x0(%esi),%esi
 80489c0:	ba 00 00 00 00       	mov    $0x0,%edx
 80489c5:	85 d2                	test   %edx,%edx
 80489c7:	74 f2                	je     80489bb <frame_dummy+0xb>
 80489c9:	55                   	push   %ebp
 80489ca:	89 e5                	mov    %esp,%ebp
 80489cc:	83 ec 14             	sub    $0x14,%esp
 80489cf:	50                   	push   %eax
 80489d0:	ff d2                	call   *%edx
 80489d2:	83 c4 10             	add    $0x10,%esp
 80489d5:	c9                   	leave  
 80489d6:	e9 75 ff ff ff       	jmp    8048950 <register_tm_clones>

080489db <main>:
 80489db:	8d 4c 24 04          	lea    0x4(%esp),%ecx
 80489df:	83 e4 f0             	and    $0xfffffff0,%esp
 80489e2:	ff 71 fc             	pushl  -0x4(%ecx)
 80489e5:	55                   	push   %ebp
 80489e6:	89 e5                	mov    %esp,%ebp
 80489e8:	53                   	push   %ebx
 80489e9:	51                   	push   %ecx
 80489ea:	8b 01                	mov    (%ecx),%eax
 80489ec:	8b 59 04             	mov    0x4(%ecx),%ebx
 80489ef:	83 f8 01             	cmp    $0x1,%eax
 80489f2:	0f 84 01 01 00 00    	je     8048af9 <main+0x11e>
 80489f8:	83 f8 02             	cmp    $0x2,%eax
 80489fb:	0f 85 24 01 00 00    	jne    8048b25 <main+0x14a>
 8048a01:	83 ec 08             	sub    $0x8,%esp
 8048a04:	68 e0 9e 04 08       	push   $0x8049ee0
 8048a09:	ff 73 04             	pushl  0x4(%ebx)
 8048a0c:	e8 0f fe ff ff       	call   8048820 <fopen@plt>
 8048a11:	a3 d0 c3 04 08       	mov    %eax,0x804c3d0
 8048a16:	83 c4 10             	add    $0x10,%esp
 8048a19:	85 c0                	test   %eax,%eax
 8048a1b:	0f 84 e7 00 00 00    	je     8048b08 <main+0x12d>
 8048a21:	e8 67 06 00 00       	call   804908d <initialize_bomb>
 8048a26:	83 ec 0c             	sub    $0xc,%esp
 8048a29:	68 64 9f 04 08       	push   $0x8049f64
 8048a2e:	e8 8d fd ff ff       	call   80487c0 <puts@plt>
 8048a33:	c7 04 24 a0 9f 04 08 	movl   $0x8049fa0,(%esp)
 8048a3a:	e8 81 fd ff ff       	call   80487c0 <puts@plt>
 8048a3f:	e8 39 07 00 00       	call   804917d <read_line>
 8048a44:	89 04 24             	mov    %eax,(%esp)
 8048a47:	e8 f6 00 00 00       	call   8048b42 <phase_1>
 8048a4c:	e8 2b 08 00 00       	call   804927c <phase_defused>
 8048a51:	c7 04 24 cc 9f 04 08 	movl   $0x8049fcc,(%esp)
 8048a58:	e8 63 fd ff ff       	call   80487c0 <puts@plt>
 8048a5d:	e8 1b 07 00 00       	call   804917d <read_line>
 8048a62:	89 04 24             	mov    %eax,(%esp)
 8048a65:	e8 fb 00 00 00       	call   8048b65 <phase_2>
 8048a6a:	e8 0d 08 00 00       	call   804927c <phase_defused>
 8048a6f:	c7 04 24 19 9f 04 08 	movl   $0x8049f19,(%esp)
 8048a76:	e8 45 fd ff ff       	call   80487c0 <puts@plt>
 8048a7b:	e8 fd 06 00 00       	call   804917d <read_line>
 8048a80:	89 04 24             	mov    %eax,(%esp)
 8048a83:	e8 44 01 00 00       	call   8048bcc <phase_3>
 8048a88:	e8 ef 07 00 00       	call   804927c <phase_defused>
 8048a8d:	c7 04 24 37 9f 04 08 	movl   $0x8049f37,(%esp)
 8048a94:	e8 27 fd ff ff       	call   80487c0 <puts@plt>
 8048a99:	e8 df 06 00 00       	call   804917d <read_line>
 8048a9e:	89 04 24             	mov    %eax,(%esp)
 8048aa1:	e8 42 02 00 00       	call   8048ce8 <phase_4>
 8048aa6:	e8 d1 07 00 00       	call   804927c <phase_defused>
 8048aab:	c7 04 24 f8 9f 04 08 	movl   $0x8049ff8,(%esp)
 8048ab2:	e8 09 fd ff ff       	call   80487c0 <puts@plt>
 8048ab7:	e8 c1 06 00 00       	call   804917d <read_line>
 8048abc:	89 04 24             	mov    %eax,(%esp)
 8048abf:	e8 98 02 00 00       	call   8048d5c <phase_5>
 8048ac4:	e8 b3 07 00 00       	call   804927c <phase_defused>
 8048ac9:	c7 04 24 46 9f 04 08 	movl   $0x8049f46,(%esp)
 8048ad0:	e8 eb fc ff ff       	call   80487c0 <puts@plt>
 8048ad5:	e8 a3 06 00 00       	call   804917d <read_line>
 8048ada:	89 04 24             	mov    %eax,(%esp)
 8048add:	e8 fc 02 00 00       	call   8048dde <phase_6>
 8048ae2:	e8 95 07 00 00       	call   804927c <phase_defused>
 8048ae7:	83 c4 10             	add    $0x10,%esp
 8048aea:	b8 00 00 00 00       	mov    $0x0,%eax
 8048aef:	8d 65 f8             	lea    -0x8(%ebp),%esp
 8048af2:	59                   	pop    %ecx
 8048af3:	5b                   	pop    %ebx
 8048af4:	5d                   	pop    %ebp
 8048af5:	8d 61 fc             	lea    -0x4(%ecx),%esp
 8048af8:	c3                   	ret    
 8048af9:	a1 c0 c3 04 08       	mov    0x804c3c0,%eax
 8048afe:	a3 d0 c3 04 08       	mov    %eax,0x804c3d0
 8048b03:	e9 19 ff ff ff       	jmp    8048a21 <main+0x46>
 8048b08:	ff 73 04             	pushl  0x4(%ebx)
 8048b0b:	ff 33                	pushl  (%ebx)
 8048b0d:	68 e2 9e 04 08       	push   $0x8049ee2
 8048b12:	6a 01                	push   $0x1
 8048b14:	e8 27 fd ff ff       	call   8048840 <__printf_chk@plt>
 8048b19:	c7 04 24 08 00 00 00 	movl   $0x8,(%esp)
 8048b20:	e8 bb fc ff ff       	call   80487e0 <exit@plt>
 8048b25:	83 ec 04             	sub    $0x4,%esp
 8048b28:	ff 33                	pushl  (%ebx)
 8048b2a:	68 ff 9e 04 08       	push   $0x8049eff
 8048b2f:	6a 01                	push   $0x1
 8048b31:	e8 0a fd ff ff       	call   8048840 <__printf_chk@plt>
 8048b36:	c7 04 24 08 00 00 00 	movl   $0x8,(%esp)
 8048b3d:	e8 9e fc ff ff       	call   80487e0 <exit@plt>

08048b42 <phase_1>:
 8048b42:	83 ec 14             	sub    $0x14,%esp
 8048b45:	68 1c a0 04 08       	push   $0x804a01c
 8048b4a:	ff 74 24 1c          	pushl  0x1c(%esp)
 8048b4e:	e8 d5 04 00 00       	call   8049028 <strings_not_equal>
 8048b53:	83 c4 10             	add    $0x10,%esp
 8048b56:	85 c0                	test   %eax,%eax
 8048b58:	75 04                	jne    8048b5e <phase_1+0x1c>
 8048b5a:	83 c4 0c             	add    $0xc,%esp
 8048b5d:	c3                   	ret    
 8048b5e:	e8 ba 05 00 00       	call   804911d <explode_bomb>
 8048b63:	eb f5                	jmp    8048b5a <phase_1+0x18>

08048b65 <phase_2>:
 8048b65:	56                   	push   %esi
 8048b66:	53                   	push   %ebx
 8048b67:	83 ec 2c             	sub    $0x2c,%esp
 8048b6a:	65 a1 14 00 00 00    	mov    %gs:0x14,%eax
 8048b70:	89 44 24 24          	mov    %eax,0x24(%esp)
 8048b74:	31 c0                	xor    %eax,%eax
 8048b76:	8d 44 24 0c          	lea    0xc(%esp),%eax
 8048b7a:	50                   	push   %eax
 8048b7b:	ff 74 24 3c          	pushl  0x3c(%esp)
 8048b7f:	e8 be 05 00 00       	call   8049142 <read_six_numbers>
 8048b84:	83 c4 10             	add    $0x10,%esp
 8048b87:	83 7c 24 04 01       	cmpl   $0x1,0x4(%esp)
 8048b8c:	74 05                	je     8048b93 <phase_2+0x2e>
 8048b8e:	e8 8a 05 00 00       	call   804911d <explode_bomb>
 8048b93:	8d 5c 24 04          	lea    0x4(%esp),%ebx
 8048b97:	8d 74 24 18          	lea    0x18(%esp),%esi
 8048b9b:	eb 07                	jmp    8048ba4 <phase_2+0x3f>
 8048b9d:	83 c3 04             	add    $0x4,%ebx
 8048ba0:	39 f3                	cmp    %esi,%ebx
 8048ba2:	74 10                	je     8048bb4 <phase_2+0x4f>
 8048ba4:	8b 03                	mov    (%ebx),%eax
 8048ba6:	01 c0                	add    %eax,%eax
 8048ba8:	39 43 04             	cmp    %eax,0x4(%ebx)
 8048bab:	74 f0                	je     8048b9d <phase_2+0x38>
 8048bad:	e8 6b 05 00 00       	call   804911d <explode_bomb>
 8048bb2:	eb e9                	jmp    8048b9d <phase_2+0x38>
 8048bb4:	8b 44 24 1c          	mov    0x1c(%esp),%eax
 8048bb8:	65 33 05 14 00 00 00 	xor    %gs:0x14,%eax
 8048bbf:	75 06                	jne    8048bc7 <phase_2+0x62>
 8048bc1:	83 c4 24             	add    $0x24,%esp
 8048bc4:	5b                   	pop    %ebx
 8048bc5:	5e                   	pop    %esi
 8048bc6:	c3                   	ret    
 8048bc7:	e8 c4 fb ff ff       	call   8048790 <__stack_chk_fail@plt>

08048bcc <phase_3>:
 8048bcc:	83 ec 1c             	sub    $0x1c,%esp
 8048bcf:	65 a1 14 00 00 00    	mov    %gs:0x14,%eax
 8048bd5:	89 44 24 0c          	mov    %eax,0xc(%esp)
 8048bd9:	31 c0                	xor    %eax,%eax
 8048bdb:	8d 44 24 08          	lea    0x8(%esp),%eax
 8048bdf:	50                   	push   %eax
 8048be0:	8d 44 24 08          	lea    0x8(%esp),%eax
 8048be4:	50                   	push   %eax
 8048be5:	68 bb a1 04 08       	push   $0x804a1bb
 8048bea:	ff 74 24 2c          	pushl  0x2c(%esp)
 8048bee:	e8 1d fc ff ff       	call   8048810 <__isoc99_sscanf@plt>
 8048bf3:	83 c4 10             	add    $0x10,%esp
 8048bf6:	83 f8 01             	cmp    $0x1,%eax
 8048bf9:	7e 16                	jle    8048c11 <phase_3+0x45>
 8048bfb:	83 7c 24 04 07       	cmpl   $0x7,0x4(%esp)
 8048c00:	0f 87 8e 00 00 00    	ja     8048c94 <phase_3+0xc8>
 8048c06:	8b 44 24 04          	mov    0x4(%esp),%eax
 8048c0a:	ff 24 85 7c a0 04 08 	jmp    *0x804a07c(,%eax,4)
 8048c11:	e8 07 05 00 00       	call   804911d <explode_bomb>
 8048c16:	eb e3                	jmp    8048bfb <phase_3+0x2f>
 8048c18:	b8 28 01 00 00       	mov    $0x128,%eax
 8048c1d:	eb 05                	jmp    8048c24 <phase_3+0x58>
 8048c1f:	b8 00 00 00 00       	mov    $0x0,%eax
 8048c24:	2d 5d 01 00 00       	sub    $0x15d,%eax
 8048c29:	05 9f 02 00 00       	add    $0x29f,%eax
 8048c2e:	2d fc 00 00 00       	sub    $0xfc,%eax
 8048c33:	05 fc 00 00 00       	add    $0xfc,%eax
 8048c38:	2d fc 00 00 00       	sub    $0xfc,%eax
 8048c3d:	05 fc 00 00 00       	add    $0xfc,%eax
 8048c42:	2d fc 00 00 00       	sub    $0xfc,%eax
 8048c47:	83 7c 24 04 05       	cmpl   $0x5,0x4(%esp)
 8048c4c:	7f 06                	jg     8048c54 <phase_3+0x88>
 8048c4e:	3b 44 24 08          	cmp    0x8(%esp),%eax
 8048c52:	74 05                	je     8048c59 <phase_3+0x8d>
 8048c54:	e8 c4 04 00 00       	call   804911d <explode_bomb>
 8048c59:	8b 44 24 0c          	mov    0xc(%esp),%eax
 8048c5d:	65 33 05 14 00 00 00 	xor    %gs:0x14,%eax
 8048c64:	75 3a                	jne    8048ca0 <phase_3+0xd4>
 8048c66:	83 c4 1c             	add    $0x1c,%esp
 8048c69:	c3                   	ret    
 8048c6a:	b8 00 00 00 00       	mov    $0x0,%eax
 8048c6f:	eb b8                	jmp    8048c29 <phase_3+0x5d>
 8048c71:	b8 00 00 00 00       	mov    $0x0,%eax
 8048c76:	eb b6                	jmp    8048c2e <phase_3+0x62>
 8048c78:	b8 00 00 00 00       	mov    $0x0,%eax
 8048c7d:	eb b4                	jmp    8048c33 <phase_3+0x67>
 8048c7f:	b8 00 00 00 00       	mov    $0x0,%eax
 8048c84:	eb b2                	jmp    8048c38 <phase_3+0x6c>
 8048c86:	b8 00 00 00 00       	mov    $0x0,%eax
 8048c8b:	eb b0                	jmp    8048c3d <phase_3+0x71>
 8048c8d:	b8 00 00 00 00       	mov    $0x0,%eax
 8048c92:	eb ae                	jmp    8048c42 <phase_3+0x76>
 8048c94:	e8 84 04 00 00       	call   804911d <explode_bomb>
 8048c99:	b8 00 00 00 00       	mov    $0x0,%eax
 8048c9e:	eb a7                	jmp    8048c47 <phase_3+0x7b>
 8048ca0:	e8 eb fa ff ff       	call   8048790 <__stack_chk_fail@plt>

08048ca5 <func4>:
 8048ca5:	57                   	push   %edi
 8048ca6:	56                   	push   %esi
 8048ca7:	53                   	push   %ebx
 8048ca8:	8b 5c 24 10          	mov    0x10(%esp),%ebx
 8048cac:	8b 7c 24 14          	mov    0x14(%esp),%edi
 8048cb0:	85 db                	test   %ebx,%ebx
 8048cb2:	7e 2d                	jle    8048ce1 <func4+0x3c>
 8048cb4:	89 f8                	mov    %edi,%eax
 8048cb6:	83 fb 01             	cmp    $0x1,%ebx
 8048cb9:	74 22                	je     8048cdd <func4+0x38>
 8048cbb:	83 ec 08             	sub    $0x8,%esp
 8048cbe:	57                   	push   %edi
 8048cbf:	8d 43 ff             	lea    -0x1(%ebx),%eax
 8048cc2:	50                   	push   %eax
 8048cc3:	e8 dd ff ff ff       	call   8048ca5 <func4>
 8048cc8:	83 c4 08             	add    $0x8,%esp
 8048ccb:	8d 34 07             	lea    (%edi,%eax,1),%esi
 8048cce:	57                   	push   %edi
 8048ccf:	83 eb 02             	sub    $0x2,%ebx
 8048cd2:	53                   	push   %ebx
 8048cd3:	e8 cd ff ff ff       	call   8048ca5 <func4>
 8048cd8:	83 c4 10             	add    $0x10,%esp
 8048cdb:	01 f0                	add    %esi,%eax
 8048cdd:	5b                   	pop    %ebx
 8048cde:	5e                   	pop    %esi
 8048cdf:	5f                   	pop    %edi
 8048ce0:	c3                   	ret    
 8048ce1:	b8 00 00 00 00       	mov    $0x0,%eax
 8048ce6:	eb f5                	jmp    8048cdd <func4+0x38>

08048ce8 <phase_4>:
 8048ce8:	83 ec 1c             	sub    $0x1c,%esp
 8048ceb:	65 a1 14 00 00 00    	mov    %gs:0x14,%eax
 8048cf1:	89 44 24 0c          	mov    %eax,0xc(%esp)
 8048cf5:	31 c0                	xor    %eax,%eax
 8048cf7:	8d 44 24 04          	lea    0x4(%esp),%eax
 8048cfb:	50                   	push   %eax
 8048cfc:	8d 44 24 0c          	lea    0xc(%esp),%eax
 8048d00:	50                   	push   %eax
 8048d01:	68 bb a1 04 08       	push   $0x804a1bb
 8048d06:	ff 74 24 2c          	pushl  0x2c(%esp)
 8048d0a:	e8 01 fb ff ff       	call   8048810 <__isoc99_sscanf@plt>
 8048d0f:	83 c4 10             	add    $0x10,%esp
 8048d12:	83 f8 02             	cmp    $0x2,%eax
 8048d15:	74 32                	je     8048d49 <phase_4+0x61>
 8048d17:	e8 01 04 00 00       	call   804911d <explode_bomb>
 8048d1c:	83 ec 08             	sub    $0x8,%esp
 8048d1f:	ff 74 24 0c          	pushl  0xc(%esp)
 8048d23:	6a 07                	push   $0x7
 8048d25:	e8 7b ff ff ff       	call   8048ca5 <func4>
 8048d2a:	83 c4 10             	add    $0x10,%esp
 8048d2d:	3b 44 24 08          	cmp    0x8(%esp),%eax
 8048d31:	74 05                	je     8048d38 <phase_4+0x50>
 8048d33:	e8 e5 03 00 00       	call   804911d <explode_bomb>
 8048d38:	8b 44 24 0c          	mov    0xc(%esp),%eax
 8048d3c:	65 33 05 14 00 00 00 	xor    %gs:0x14,%eax
 8048d43:	75 12                	jne    8048d57 <phase_4+0x6f>
 8048d45:	83 c4 1c             	add    $0x1c,%esp
 8048d48:	c3                   	ret    
 8048d49:	8b 44 24 04          	mov    0x4(%esp),%eax
 8048d4d:	83 e8 02             	sub    $0x2,%eax
 8048d50:	83 f8 02             	cmp    $0x2,%eax
 8048d53:	76 c7                	jbe    8048d1c <phase_4+0x34>
 8048d55:	eb c0                	jmp    8048d17 <phase_4+0x2f>
 8048d57:	e8 34 fa ff ff       	call   8048790 <__stack_chk_fail@plt>

08048d5c <phase_5>:
 8048d5c:	53                   	push   %ebx
 8048d5d:	83 ec 24             	sub    $0x24,%esp
 8048d60:	8b 5c 24 2c          	mov    0x2c(%esp),%ebx
 8048d64:	65 a1 14 00 00 00    	mov    %gs:0x14,%eax
 8048d6a:	89 44 24 18          	mov    %eax,0x18(%esp)
 8048d6e:	31 c0                	xor    %eax,%eax
 8048d70:	53                   	push   %ebx
 8048d71:	e8 93 02 00 00       	call   8049009 <string_length>
 8048d76:	83 c4 10             	add    $0x10,%esp
 8048d79:	83 f8 06             	cmp    $0x6,%eax
 8048d7c:	74 05                	je     8048d83 <phase_5+0x27>
 8048d7e:	e8 9a 03 00 00       	call   804911d <explode_bomb>
 8048d83:	b8 00 00 00 00       	mov    $0x0,%eax
 8048d88:	0f b6 14 03          	movzbl (%ebx,%eax,1),%edx
 8048d8c:	83 e2 0f             	and    $0xf,%edx
 8048d8f:	0f b6 92 9c a0 04 08 	movzbl 0x804a09c(%edx),%edx
 8048d96:	88 54 04 05          	mov    %dl,0x5(%esp,%eax,1)
 8048d9a:	83 c0 01             	add    $0x1,%eax
 8048d9d:	83 f8 06             	cmp    $0x6,%eax
 8048da0:	75 e6                	jne    8048d88 <phase_5+0x2c>
 8048da2:	c6 44 24 0b 00       	movb   $0x0,0xb(%esp)
 8048da7:	83 ec 08             	sub    $0x8,%esp
 8048daa:	68 72 a0 04 08       	push   $0x804a072
 8048daf:	8d 44 24 11          	lea    0x11(%esp),%eax
 8048db3:	50                   	push   %eax
 8048db4:	e8 6f 02 00 00       	call   8049028 <strings_not_equal>
 8048db9:	83 c4 10             	add    $0x10,%esp
 8048dbc:	85 c0                	test   %eax,%eax
 8048dbe:	75 12                	jne    8048dd2 <phase_5+0x76>
 8048dc0:	8b 44 24 0c          	mov    0xc(%esp),%eax
 8048dc4:	65 33 05 14 00 00 00 	xor    %gs:0x14,%eax
 8048dcb:	75 0c                	jne    8048dd9 <phase_5+0x7d>
 8048dcd:	83 c4 18             	add    $0x18,%esp
 8048dd0:	5b                   	pop    %ebx
 8048dd1:	c3                   	ret    
 8048dd2:	e8 46 03 00 00       	call   804911d <explode_bomb>
 8048dd7:	eb e7                	jmp    8048dc0 <phase_5+0x64>
 8048dd9:	e8 b2 f9 ff ff       	call   8048790 <__stack_chk_fail@plt>

08048dde <phase_6>:
 8048dde:	56                   	push   %esi
 8048ddf:	53                   	push   %ebx
 8048de0:	83 ec 4c             	sub    $0x4c,%esp
 8048de3:	65 a1 14 00 00 00    	mov    %gs:0x14,%eax
 8048de9:	89 44 24 44          	mov    %eax,0x44(%esp)
 8048ded:	31 c0                	xor    %eax,%eax
 8048def:	8d 44 24 14          	lea    0x14(%esp),%eax
 8048df3:	50                   	push   %eax
 8048df4:	ff 74 24 5c          	pushl  0x5c(%esp)
 8048df8:	e8 45 03 00 00       	call   8049142 <read_six_numbers>
 8048dfd:	83 c4 10             	add    $0x10,%esp
 8048e00:	be 00 00 00 00       	mov    $0x0,%esi
 8048e05:	eb 1c                	jmp    8048e23 <phase_6+0x45>
 8048e07:	83 c6 01             	add    $0x1,%esi
 8048e0a:	83 fe 06             	cmp    $0x6,%esi
 8048e0d:	74 2e                	je     8048e3d <phase_6+0x5f>
 8048e0f:	89 f3                	mov    %esi,%ebx
 8048e11:	8b 44 9c 0c          	mov    0xc(%esp,%ebx,4),%eax
 8048e15:	39 44 b4 08          	cmp    %eax,0x8(%esp,%esi,4)
 8048e19:	74 1b                	je     8048e36 <phase_6+0x58>
 8048e1b:	83 c3 01             	add    $0x1,%ebx
 8048e1e:	83 fb 05             	cmp    $0x5,%ebx
 8048e21:	7e ee                	jle    8048e11 <phase_6+0x33>
 8048e23:	8b 44 b4 0c          	mov    0xc(%esp,%esi,4),%eax
 8048e27:	83 e8 01             	sub    $0x1,%eax
 8048e2a:	83 f8 05             	cmp    $0x5,%eax
 8048e2d:	76 d8                	jbe    8048e07 <phase_6+0x29>
 8048e2f:	e8 e9 02 00 00       	call   804911d <explode_bomb>
 8048e34:	eb d1                	jmp    8048e07 <phase_6+0x29>
 8048e36:	e8 e2 02 00 00       	call   804911d <explode_bomb>
 8048e3b:	eb de                	jmp    8048e1b <phase_6+0x3d>
 8048e3d:	8d 44 24 0c          	lea    0xc(%esp),%eax
 8048e41:	8d 5c 24 24          	lea    0x24(%esp),%ebx
 8048e45:	b9 07 00 00 00       	mov    $0x7,%ecx
 8048e4a:	89 ca                	mov    %ecx,%edx
 8048e4c:	2b 10                	sub    (%eax),%edx
 8048e4e:	89 10                	mov    %edx,(%eax)
 8048e50:	83 c0 04             	add    $0x4,%eax
 8048e53:	39 c3                	cmp    %eax,%ebx
 8048e55:	75 f3                	jne    8048e4a <phase_6+0x6c>
 8048e57:	bb 00 00 00 00       	mov    $0x0,%ebx
 8048e5c:	89 de                	mov    %ebx,%esi
 8048e5e:	8b 4c 9c 0c          	mov    0xc(%esp,%ebx,4),%ecx
 8048e62:	b8 01 00 00 00       	mov    $0x1,%eax
 8048e67:	ba 3c c1 04 08       	mov    $0x804c13c,%edx
 8048e6c:	83 f9 01             	cmp    $0x1,%ecx
 8048e6f:	7e 0a                	jle    8048e7b <phase_6+0x9d>
 8048e71:	8b 52 08             	mov    0x8(%edx),%edx
 8048e74:	83 c0 01             	add    $0x1,%eax
 8048e77:	39 c8                	cmp    %ecx,%eax
 8048e79:	75 f6                	jne    8048e71 <phase_6+0x93>
 8048e7b:	89 54 b4 24          	mov    %edx,0x24(%esp,%esi,4)
 8048e7f:	83 c3 01             	add    $0x1,%ebx
 8048e82:	83 fb 06             	cmp    $0x6,%ebx
 8048e85:	75 d5                	jne    8048e5c <phase_6+0x7e>
 8048e87:	8b 5c 24 24          	mov    0x24(%esp),%ebx
 8048e8b:	89 d9                	mov    %ebx,%ecx
 8048e8d:	b8 01 00 00 00       	mov    $0x1,%eax
 8048e92:	8b 54 84 24          	mov    0x24(%esp,%eax,4),%edx
 8048e96:	89 51 08             	mov    %edx,0x8(%ecx)
 8048e99:	83 c0 01             	add    $0x1,%eax
 8048e9c:	89 d1                	mov    %edx,%ecx
 8048e9e:	83 f8 06             	cmp    $0x6,%eax
 8048ea1:	75 ef                	jne    8048e92 <phase_6+0xb4>
 8048ea3:	c7 42 08 00 00 00 00 	movl   $0x0,0x8(%edx)
 8048eaa:	be 05 00 00 00       	mov    $0x5,%esi
 8048eaf:	eb 08                	jmp    8048eb9 <phase_6+0xdb>
 8048eb1:	8b 5b 08             	mov    0x8(%ebx),%ebx
 8048eb4:	83 ee 01             	sub    $0x1,%esi
 8048eb7:	74 10                	je     8048ec9 <phase_6+0xeb>
 8048eb9:	8b 43 08             	mov    0x8(%ebx),%eax
 8048ebc:	8b 00                	mov    (%eax),%eax
 8048ebe:	39 03                	cmp    %eax,(%ebx)
 8048ec0:	7d ef                	jge    8048eb1 <phase_6+0xd3>
 8048ec2:	e8 56 02 00 00       	call   804911d <explode_bomb>
 8048ec7:	eb e8                	jmp    8048eb1 <phase_6+0xd3>
 8048ec9:	8b 44 24 3c          	mov    0x3c(%esp),%eax
 8048ecd:	65 33 05 14 00 00 00 	xor    %gs:0x14,%eax
 8048ed4:	75 06                	jne    8048edc <phase_6+0xfe>
 8048ed6:	83 c4 44             	add    $0x44,%esp
 8048ed9:	5b                   	pop    %ebx
 8048eda:	5e                   	pop    %esi
 8048edb:	c3                   	ret    
 8048edc:	e8 af f8 ff ff       	call   8048790 <__stack_chk_fail@plt>

08048ee1 <fun7>:
 8048ee1:	53                   	push   %ebx
 8048ee2:	83 ec 08             	sub    $0x8,%esp
 8048ee5:	8b 54 24 10          	mov    0x10(%esp),%edx
 8048ee9:	8b 4c 24 14          	mov    0x14(%esp),%ecx
 8048eed:	85 d2                	test   %edx,%edx
 8048eef:	74 3a                	je     8048f2b <fun7+0x4a>
 8048ef1:	8b 1a                	mov    (%edx),%ebx
 8048ef3:	39 cb                	cmp    %ecx,%ebx
 8048ef5:	7f 21                	jg     8048f18 <fun7+0x37>
 8048ef7:	b8 00 00 00 00       	mov    $0x0,%eax
 8048efc:	39 cb                	cmp    %ecx,%ebx
 8048efe:	74 13                	je     8048f13 <fun7+0x32>
 8048f00:	83 ec 08             	sub    $0x8,%esp
 8048f03:	51                   	push   %ecx
 8048f04:	ff 72 08             	pushl  0x8(%edx)
 8048f07:	e8 d5 ff ff ff       	call   8048ee1 <fun7>
 8048f0c:	83 c4 10             	add    $0x10,%esp
 8048f0f:	8d 44 00 01          	lea    0x1(%eax,%eax,1),%eax
 8048f13:	83 c4 08             	add    $0x8,%esp
 8048f16:	5b                   	pop    %ebx
 8048f17:	c3                   	ret    
 8048f18:	83 ec 08             	sub    $0x8,%esp
 8048f1b:	51                   	push   %ecx
 8048f1c:	ff 72 04             	pushl  0x4(%edx)
 8048f1f:	e8 bd ff ff ff       	call   8048ee1 <fun7>
 8048f24:	83 c4 10             	add    $0x10,%esp
 8048f27:	01 c0                	add    %eax,%eax
 8048f29:	eb e8                	jmp    8048f13 <fun7+0x32>
 8048f2b:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8048f30:	eb e1                	jmp    8048f13 <fun7+0x32>

08048f32 <secret_phase>:
 8048f32:	53                   	push   %ebx
 8048f33:	83 ec 08             	sub    $0x8,%esp
 8048f36:	e8 42 02 00 00       	call   804917d <read_line>
 8048f3b:	83 ec 04             	sub    $0x4,%esp
 8048f3e:	6a 0a                	push   $0xa
 8048f40:	6a 00                	push   $0x0
 8048f42:	50                   	push   %eax
 8048f43:	e8 38 f9 ff ff       	call   8048880 <strtol@plt>
 8048f48:	89 c3                	mov    %eax,%ebx
 8048f4a:	8d 40 ff             	lea    -0x1(%eax),%eax
 8048f4d:	83 c4 10             	add    $0x10,%esp
 8048f50:	3d e8 03 00 00       	cmp    $0x3e8,%eax
 8048f55:	77 32                	ja     8048f89 <secret_phase+0x57>
 8048f57:	83 ec 08             	sub    $0x8,%esp
 8048f5a:	53                   	push   %ebx
 8048f5b:	68 88 c0 04 08       	push   $0x804c088
 8048f60:	e8 7c ff ff ff       	call   8048ee1 <fun7>
 8048f65:	83 c4 10             	add    $0x10,%esp
 8048f68:	83 f8 02             	cmp    $0x2,%eax
 8048f6b:	74 05                	je     8048f72 <secret_phase+0x40>
 8048f6d:	e8 ab 01 00 00       	call   804911d <explode_bomb>
 8048f72:	83 ec 0c             	sub    $0xc,%esp
 8048f75:	68 4c a0 04 08       	push   $0x804a04c
 8048f7a:	e8 41 f8 ff ff       	call   80487c0 <puts@plt>
 8048f7f:	e8 f8 02 00 00       	call   804927c <phase_defused>
 8048f84:	83 c4 18             	add    $0x18,%esp
 8048f87:	5b                   	pop    %ebx
 8048f88:	c3                   	ret    
 8048f89:	e8 8f 01 00 00       	call   804911d <explode_bomb>
 8048f8e:	eb c7                	jmp    8048f57 <secret_phase+0x25>

08048f90 <sig_handler>:
 8048f90:	83 ec 18             	sub    $0x18,%esp
 8048f93:	68 ac a0 04 08       	push   $0x804a0ac
 8048f98:	e8 23 f8 ff ff       	call   80487c0 <puts@plt>
 8048f9d:	c7 04 24 03 00 00 00 	movl   $0x3,(%esp)
 8048fa4:	e8 c7 f7 ff ff       	call   8048770 <sleep@plt>
 8048fa9:	83 c4 08             	add    $0x8,%esp
 8048fac:	68 6e a1 04 08       	push   $0x804a16e
 8048fb1:	6a 01                	push   $0x1
 8048fb3:	e8 88 f8 ff ff       	call   8048840 <__printf_chk@plt>
 8048fb8:	83 c4 04             	add    $0x4,%esp
 8048fbb:	ff 35 c4 c3 04 08    	pushl  0x804c3c4
 8048fc1:	e8 7a f7 ff ff       	call   8048740 <fflush@plt>
 8048fc6:	c7 04 24 01 00 00 00 	movl   $0x1,(%esp)
 8048fcd:	e8 9e f7 ff ff       	call   8048770 <sleep@plt>
 8048fd2:	c7 04 24 76 a1 04 08 	movl   $0x804a176,(%esp)
 8048fd9:	e8 e2 f7 ff ff       	call   80487c0 <puts@plt>
 8048fde:	c7 04 24 10 00 00 00 	movl   $0x10,(%esp)
 8048fe5:	e8 f6 f7 ff ff       	call   80487e0 <exit@plt>

08048fea <invalid_phase>:
 8048fea:	83 ec 10             	sub    $0x10,%esp
 8048fed:	ff 74 24 14          	pushl  0x14(%esp)
 8048ff1:	68 7e a1 04 08       	push   $0x804a17e
 8048ff6:	6a 01                	push   $0x1
 8048ff8:	e8 43 f8 ff ff       	call   8048840 <__printf_chk@plt>
 8048ffd:	c7 04 24 08 00 00 00 	movl   $0x8,(%esp)
 8049004:	e8 d7 f7 ff ff       	call   80487e0 <exit@plt>

08049009 <string_length>:
 8049009:	8b 54 24 04          	mov    0x4(%esp),%edx
 804900d:	80 3a 00             	cmpb   $0x0,(%edx)
 8049010:	74 10                	je     8049022 <string_length+0x19>
 8049012:	b8 00 00 00 00       	mov    $0x0,%eax
 8049017:	83 c0 01             	add    $0x1,%eax
 804901a:	80 3c 02 00          	cmpb   $0x0,(%edx,%eax,1)
 804901e:	75 f7                	jne    8049017 <string_length+0xe>
 8049020:	f3 c3                	repz ret 
 8049022:	b8 00 00 00 00       	mov    $0x0,%eax
 8049027:	c3                   	ret    

08049028 <strings_not_equal>:
 8049028:	57                   	push   %edi
 8049029:	56                   	push   %esi
 804902a:	53                   	push   %ebx
 804902b:	8b 5c 24 10          	mov    0x10(%esp),%ebx
 804902f:	8b 74 24 14          	mov    0x14(%esp),%esi
 8049033:	53                   	push   %ebx
 8049034:	e8 d0 ff ff ff       	call   8049009 <string_length>
 8049039:	89 c7                	mov    %eax,%edi
 804903b:	89 34 24             	mov    %esi,(%esp)
 804903e:	e8 c6 ff ff ff       	call   8049009 <string_length>
 8049043:	83 c4 04             	add    $0x4,%esp
 8049046:	ba 01 00 00 00       	mov    $0x1,%edx
 804904b:	39 c7                	cmp    %eax,%edi
 804904d:	74 06                	je     8049055 <strings_not_equal+0x2d>
 804904f:	89 d0                	mov    %edx,%eax
 8049051:	5b                   	pop    %ebx
 8049052:	5e                   	pop    %esi
 8049053:	5f                   	pop    %edi
 8049054:	c3                   	ret    
 8049055:	0f b6 03             	movzbl (%ebx),%eax
 8049058:	84 c0                	test   %al,%al
 804905a:	74 23                	je     804907f <strings_not_equal+0x57>
 804905c:	3a 06                	cmp    (%esi),%al
 804905e:	75 26                	jne    8049086 <strings_not_equal+0x5e>
 8049060:	83 c3 01             	add    $0x1,%ebx
 8049063:	83 c6 01             	add    $0x1,%esi
 8049066:	0f b6 03             	movzbl (%ebx),%eax
 8049069:	84 c0                	test   %al,%al
 804906b:	74 0b                	je     8049078 <strings_not_equal+0x50>
 804906d:	3a 06                	cmp    (%esi),%al
 804906f:	74 ef                	je     8049060 <strings_not_equal+0x38>
 8049071:	ba 01 00 00 00       	mov    $0x1,%edx
 8049076:	eb d7                	jmp    804904f <strings_not_equal+0x27>
 8049078:	ba 00 00 00 00       	mov    $0x0,%edx
 804907d:	eb d0                	jmp    804904f <strings_not_equal+0x27>
 804907f:	ba 00 00 00 00       	mov    $0x0,%edx
 8049084:	eb c9                	jmp    804904f <strings_not_equal+0x27>
 8049086:	ba 01 00 00 00       	mov    $0x1,%edx
 804908b:	eb c2                	jmp    804904f <strings_not_equal+0x27>

0804908d <initialize_bomb>:
 804908d:	83 ec 14             	sub    $0x14,%esp
 8049090:	68 90 8f 04 08       	push   $0x8048f90
 8049095:	6a 02                	push   $0x2
 8049097:	e8 c4 f6 ff ff       	call   8048760 <signal@plt>
 804909c:	83 c4 1c             	add    $0x1c,%esp
 804909f:	c3                   	ret    

080490a0 <initialize_bomb_solve>:
 80490a0:	f3 c3                	repz ret 

080490a2 <blank_line>:
 80490a2:	56                   	push   %esi
 80490a3:	53                   	push   %ebx
 80490a4:	83 ec 04             	sub    $0x4,%esp
 80490a7:	8b 74 24 10          	mov    0x10(%esp),%esi
 80490ab:	0f b6 1e             	movzbl (%esi),%ebx
 80490ae:	84 db                	test   %bl,%bl
 80490b0:	74 1b                	je     80490cd <blank_line+0x2b>
 80490b2:	e8 f9 f7 ff ff       	call   80488b0 <__ctype_b_loc@plt>
 80490b7:	83 c6 01             	add    $0x1,%esi
 80490ba:	0f be db             	movsbl %bl,%ebx
 80490bd:	8b 00                	mov    (%eax),%eax
 80490bf:	f6 44 58 01 20       	testb  $0x20,0x1(%eax,%ebx,2)
 80490c4:	75 e5                	jne    80490ab <blank_line+0x9>
 80490c6:	b8 00 00 00 00       	mov    $0x0,%eax
 80490cb:	eb 05                	jmp    80490d2 <blank_line+0x30>
 80490cd:	b8 01 00 00 00       	mov    $0x1,%eax
 80490d2:	83 c4 04             	add    $0x4,%esp
 80490d5:	5b                   	pop    %ebx
 80490d6:	5e                   	pop    %esi
 80490d7:	c3                   	ret    

080490d8 <skip>:
 80490d8:	53                   	push   %ebx
 80490d9:	83 ec 08             	sub    $0x8,%esp
 80490dc:	83 ec 04             	sub    $0x4,%esp
 80490df:	ff 35 d0 c3 04 08    	pushl  0x804c3d0
 80490e5:	6a 50                	push   $0x50
 80490e7:	a1 cc c3 04 08       	mov    0x804c3cc,%eax
 80490ec:	8d 04 80             	lea    (%eax,%eax,4),%eax
 80490ef:	c1 e0 04             	shl    $0x4,%eax
 80490f2:	05 e0 c3 04 08       	add    $0x804c3e0,%eax
 80490f7:	50                   	push   %eax
 80490f8:	e8 53 f6 ff ff       	call   8048750 <fgets@plt>
 80490fd:	89 c3                	mov    %eax,%ebx
 80490ff:	83 c4 10             	add    $0x10,%esp
 8049102:	85 c0                	test   %eax,%eax
 8049104:	74 10                	je     8049116 <skip+0x3e>
 8049106:	83 ec 0c             	sub    $0xc,%esp
 8049109:	50                   	push   %eax
 804910a:	e8 93 ff ff ff       	call   80490a2 <blank_line>
 804910f:	83 c4 10             	add    $0x10,%esp
 8049112:	85 c0                	test   %eax,%eax
 8049114:	75 c6                	jne    80490dc <skip+0x4>
 8049116:	89 d8                	mov    %ebx,%eax
 8049118:	83 c4 08             	add    $0x8,%esp
 804911b:	5b                   	pop    %ebx
 804911c:	c3                   	ret    

0804911d <explode_bomb>:
 804911d:	83 ec 18             	sub    $0x18,%esp
 8049120:	68 8f a1 04 08       	push   $0x804a18f
 8049125:	e8 96 f6 ff ff       	call   80487c0 <puts@plt>
 804912a:	c7 04 24 98 a1 04 08 	movl   $0x804a198,(%esp)
 8049131:	e8 8a f6 ff ff       	call   80487c0 <puts@plt>
 8049136:	c7 04 24 08 00 00 00 	movl   $0x8,(%esp)
 804913d:	e8 9e f6 ff ff       	call   80487e0 <exit@plt>

08049142 <read_six_numbers>:
 8049142:	83 ec 0c             	sub    $0xc,%esp
 8049145:	8b 44 24 14          	mov    0x14(%esp),%eax
 8049149:	8d 50 14             	lea    0x14(%eax),%edx
 804914c:	52                   	push   %edx
 804914d:	8d 50 10             	lea    0x10(%eax),%edx
 8049150:	52                   	push   %edx
 8049151:	8d 50 0c             	lea    0xc(%eax),%edx
 8049154:	52                   	push   %edx
 8049155:	8d 50 08             	lea    0x8(%eax),%edx
 8049158:	52                   	push   %edx
 8049159:	8d 50 04             	lea    0x4(%eax),%edx
 804915c:	52                   	push   %edx
 804915d:	50                   	push   %eax
 804915e:	68 af a1 04 08       	push   $0x804a1af
 8049163:	ff 74 24 2c          	pushl  0x2c(%esp)
 8049167:	e8 a4 f6 ff ff       	call   8048810 <__isoc99_sscanf@plt>
 804916c:	83 c4 20             	add    $0x20,%esp
 804916f:	83 f8 05             	cmp    $0x5,%eax
 8049172:	7e 04                	jle    8049178 <read_six_numbers+0x36>
 8049174:	83 c4 0c             	add    $0xc,%esp
 8049177:	c3                   	ret    
 8049178:	e8 a0 ff ff ff       	call   804911d <explode_bomb>

0804917d <read_line>:
 804917d:	57                   	push   %edi
 804917e:	56                   	push   %esi
 804917f:	53                   	push   %ebx
 8049180:	e8 53 ff ff ff       	call   80490d8 <skip>
 8049185:	85 c0                	test   %eax,%eax
 8049187:	74 4b                	je     80491d4 <read_line+0x57>
 8049189:	8b 15 cc c3 04 08    	mov    0x804c3cc,%edx
 804918f:	8d 1c 92             	lea    (%edx,%edx,4),%ebx
 8049192:	c1 e3 04             	shl    $0x4,%ebx
 8049195:	81 c3 e0 c3 04 08    	add    $0x804c3e0,%ebx
 804919b:	b8 00 00 00 00       	mov    $0x0,%eax
 80491a0:	b9 ff ff ff ff       	mov    $0xffffffff,%ecx
 80491a5:	89 df                	mov    %ebx,%edi
 80491a7:	f2 ae                	repnz scas %es:(%edi),%al
 80491a9:	f7 d1                	not    %ecx
 80491ab:	83 e9 01             	sub    $0x1,%ecx
 80491ae:	83 f9 4e             	cmp    $0x4e,%ecx
 80491b1:	0f 8f 8d 00 00 00    	jg     8049244 <read_line+0xc7>
 80491b7:	8d 04 92             	lea    (%edx,%edx,4),%eax
 80491ba:	c1 e0 04             	shl    $0x4,%eax
 80491bd:	c6 84 01 df c3 04 08 	movb   $0x0,0x804c3df(%ecx,%eax,1)
 80491c4:	00 
 80491c5:	83 c2 01             	add    $0x1,%edx
 80491c8:	89 15 cc c3 04 08    	mov    %edx,0x804c3cc
 80491ce:	89 d8                	mov    %ebx,%eax
 80491d0:	5b                   	pop    %ebx
 80491d1:	5e                   	pop    %esi
 80491d2:	5f                   	pop    %edi
 80491d3:	c3                   	ret    
 80491d4:	a1 c0 c3 04 08       	mov    0x804c3c0,%eax
 80491d9:	39 05 d0 c3 04 08    	cmp    %eax,0x804c3d0
 80491df:	74 40                	je     8049221 <read_line+0xa4>
 80491e1:	83 ec 0c             	sub    $0xc,%esp
 80491e4:	68 df a1 04 08       	push   $0x804a1df
 80491e9:	e8 c2 f5 ff ff       	call   80487b0 <getenv@plt>
 80491ee:	83 c4 10             	add    $0x10,%esp
 80491f1:	85 c0                	test   %eax,%eax
 80491f3:	75 45                	jne    804923a <read_line+0xbd>
 80491f5:	a1 c0 c3 04 08       	mov    0x804c3c0,%eax
 80491fa:	a3 d0 c3 04 08       	mov    %eax,0x804c3d0
 80491ff:	e8 d4 fe ff ff       	call   80490d8 <skip>
 8049204:	85 c0                	test   %eax,%eax
 8049206:	75 81                	jne    8049189 <read_line+0xc>
 8049208:	83 ec 0c             	sub    $0xc,%esp
 804920b:	68 c1 a1 04 08       	push   $0x804a1c1
 8049210:	e8 ab f5 ff ff       	call   80487c0 <puts@plt>
 8049215:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
 804921c:	e8 bf f5 ff ff       	call   80487e0 <exit@plt>
 8049221:	83 ec 0c             	sub    $0xc,%esp
 8049224:	68 c1 a1 04 08       	push   $0x804a1c1
 8049229:	e8 92 f5 ff ff       	call   80487c0 <puts@plt>
 804922e:	c7 04 24 08 00 00 00 	movl   $0x8,(%esp)
 8049235:	e8 a6 f5 ff ff       	call   80487e0 <exit@plt>
 804923a:	83 ec 0c             	sub    $0xc,%esp
 804923d:	6a 00                	push   $0x0
 804923f:	e8 9c f5 ff ff       	call   80487e0 <exit@plt>
 8049244:	83 ec 0c             	sub    $0xc,%esp
 8049247:	68 ea a1 04 08       	push   $0x804a1ea
 804924c:	e8 6f f5 ff ff       	call   80487c0 <puts@plt>
 8049251:	a1 cc c3 04 08       	mov    0x804c3cc,%eax
 8049256:	8d 50 01             	lea    0x1(%eax),%edx
 8049259:	89 15 cc c3 04 08    	mov    %edx,0x804c3cc
 804925f:	6b c0 50             	imul   $0x50,%eax,%eax
 8049262:	05 e0 c3 04 08       	add    $0x804c3e0,%eax
 8049267:	ba 05 a2 04 08       	mov    $0x804a205,%edx
 804926c:	b9 04 00 00 00       	mov    $0x4,%ecx
 8049271:	89 c7                	mov    %eax,%edi
 8049273:	89 d6                	mov    %edx,%esi
 8049275:	f3 a5                	rep movsl %ds:(%esi),%es:(%edi)
 8049277:	e8 a1 fe ff ff       	call   804911d <explode_bomb>

0804927c <phase_defused>:
 804927c:	83 ec 6c             	sub    $0x6c,%esp
 804927f:	65 a1 14 00 00 00    	mov    %gs:0x14,%eax
 8049285:	89 44 24 5c          	mov    %eax,0x5c(%esp)
 8049289:	31 c0                	xor    %eax,%eax
 804928b:	83 3d cc c3 04 08 06 	cmpl   $0x6,0x804c3cc
 8049292:	74 11                	je     80492a5 <phase_defused+0x29>
 8049294:	8b 44 24 5c          	mov    0x5c(%esp),%eax
 8049298:	65 33 05 14 00 00 00 	xor    %gs:0x14,%eax
 804929f:	75 7b                	jne    804931c <phase_defused+0xa0>
 80492a1:	83 c4 6c             	add    $0x6c,%esp
 80492a4:	c3                   	ret    
 80492a5:	83 ec 0c             	sub    $0xc,%esp
 80492a8:	8d 44 24 18          	lea    0x18(%esp),%eax
 80492ac:	50                   	push   %eax
 80492ad:	8d 44 24 18          	lea    0x18(%esp),%eax
 80492b1:	50                   	push   %eax
 80492b2:	8d 44 24 18          	lea    0x18(%esp),%eax
 80492b6:	50                   	push   %eax
 80492b7:	68 15 a2 04 08       	push   $0x804a215
 80492bc:	68 d0 c4 04 08       	push   $0x804c4d0
 80492c1:	e8 4a f5 ff ff       	call   8048810 <__isoc99_sscanf@plt>
 80492c6:	83 c4 20             	add    $0x20,%esp
 80492c9:	83 f8 03             	cmp    $0x3,%eax
 80492cc:	74 12                	je     80492e0 <phase_defused+0x64>
 80492ce:	83 ec 0c             	sub    $0xc,%esp
 80492d1:	68 44 a1 04 08       	push   $0x804a144
 80492d6:	e8 e5 f4 ff ff       	call   80487c0 <puts@plt>
 80492db:	83 c4 10             	add    $0x10,%esp
 80492de:	eb b4                	jmp    8049294 <phase_defused+0x18>
 80492e0:	83 ec 08             	sub    $0x8,%esp
 80492e3:	68 1e a2 04 08       	push   $0x804a21e
 80492e8:	8d 44 24 18          	lea    0x18(%esp),%eax
 80492ec:	50                   	push   %eax
 80492ed:	e8 36 fd ff ff       	call   8049028 <strings_not_equal>
 80492f2:	83 c4 10             	add    $0x10,%esp
 80492f5:	85 c0                	test   %eax,%eax
 80492f7:	75 d5                	jne    80492ce <phase_defused+0x52>
 80492f9:	83 ec 0c             	sub    $0xc,%esp
 80492fc:	68 e4 a0 04 08       	push   $0x804a0e4
 8049301:	e8 ba f4 ff ff       	call   80487c0 <puts@plt>
 8049306:	c7 04 24 0c a1 04 08 	movl   $0x804a10c,(%esp)
 804930d:	e8 ae f4 ff ff       	call   80487c0 <puts@plt>
 8049312:	e8 1b fc ff ff       	call   8048f32 <secret_phase>
 8049317:	83 c4 10             	add    $0x10,%esp
 804931a:	eb b2                	jmp    80492ce <phase_defused+0x52>
 804931c:	e8 6f f4 ff ff       	call   8048790 <__stack_chk_fail@plt>

08049321 <sigalrm_handler>:
 8049321:	83 ec 0c             	sub    $0xc,%esp
 8049324:	6a 00                	push   $0x0
 8049326:	68 74 a2 04 08       	push   $0x804a274
 804932b:	6a 01                	push   $0x1
 804932d:	ff 35 a0 c3 04 08    	pushl  0x804c3a0
 8049333:	e8 28 f5 ff ff       	call   8048860 <__fprintf_chk@plt>
 8049338:	c7 04 24 01 00 00 00 	movl   $0x1,(%esp)
 804933f:	e8 9c f4 ff ff       	call   80487e0 <exit@plt>

08049344 <rio_readlineb>:
 8049344:	55                   	push   %ebp
 8049345:	57                   	push   %edi
 8049346:	56                   	push   %esi
 8049347:	53                   	push   %ebx
 8049348:	83 ec 1c             	sub    $0x1c,%esp
 804934b:	83 f9 01             	cmp    $0x1,%ecx
 804934e:	76 79                	jbe    80493c9 <rio_readlineb+0x85>
 8049350:	89 d7                	mov    %edx,%edi
 8049352:	89 c3                	mov    %eax,%ebx
 8049354:	89 4c 24 0c          	mov    %ecx,0xc(%esp)
 8049358:	bd 01 00 00 00       	mov    $0x1,%ebp
 804935d:	8d 70 0c             	lea    0xc(%eax),%esi
 8049360:	eb 0a                	jmp    804936c <rio_readlineb+0x28>
 8049362:	e8 c9 f4 ff ff       	call   8048830 <__errno_location@plt>
 8049367:	83 38 04             	cmpl   $0x4,(%eax)
 804936a:	75 66                	jne    80493d2 <rio_readlineb+0x8e>
 804936c:	8b 43 04             	mov    0x4(%ebx),%eax
 804936f:	85 c0                	test   %eax,%eax
 8049371:	7f 23                	jg     8049396 <rio_readlineb+0x52>
 8049373:	83 ec 04             	sub    $0x4,%esp
 8049376:	68 00 20 00 00       	push   $0x2000
 804937b:	56                   	push   %esi
 804937c:	ff 33                	pushl  (%ebx)
 804937e:	e8 ad f3 ff ff       	call   8048730 <read@plt>
 8049383:	89 43 04             	mov    %eax,0x4(%ebx)
 8049386:	83 c4 10             	add    $0x10,%esp
 8049389:	85 c0                	test   %eax,%eax
 804938b:	78 d5                	js     8049362 <rio_readlineb+0x1e>
 804938d:	85 c0                	test   %eax,%eax
 804938f:	74 48                	je     80493d9 <rio_readlineb+0x95>
 8049391:	89 73 08             	mov    %esi,0x8(%ebx)
 8049394:	eb d6                	jmp    804936c <rio_readlineb+0x28>
 8049396:	8b 4b 08             	mov    0x8(%ebx),%ecx
 8049399:	0f b6 11             	movzbl (%ecx),%edx
 804939c:	83 c1 01             	add    $0x1,%ecx
 804939f:	89 4b 08             	mov    %ecx,0x8(%ebx)
 80493a2:	83 e8 01             	sub    $0x1,%eax
 80493a5:	89 43 04             	mov    %eax,0x4(%ebx)
 80493a8:	83 c7 01             	add    $0x1,%edi
 80493ab:	88 57 ff             	mov    %dl,-0x1(%edi)
 80493ae:	80 fa 0a             	cmp    $0xa,%dl
 80493b1:	74 09                	je     80493bc <rio_readlineb+0x78>
 80493b3:	83 c5 01             	add    $0x1,%ebp
 80493b6:	3b 6c 24 0c          	cmp    0xc(%esp),%ebp
 80493ba:	75 b0                	jne    804936c <rio_readlineb+0x28>
 80493bc:	c6 07 00             	movb   $0x0,(%edi)
 80493bf:	89 e8                	mov    %ebp,%eax
 80493c1:	83 c4 1c             	add    $0x1c,%esp
 80493c4:	5b                   	pop    %ebx
 80493c5:	5e                   	pop    %esi
 80493c6:	5f                   	pop    %edi
 80493c7:	5d                   	pop    %ebp
 80493c8:	c3                   	ret    
 80493c9:	89 d7                	mov    %edx,%edi
 80493cb:	bd 01 00 00 00       	mov    $0x1,%ebp
 80493d0:	eb ea                	jmp    80493bc <rio_readlineb+0x78>
 80493d2:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 80493d7:	eb 05                	jmp    80493de <rio_readlineb+0x9a>
 80493d9:	b8 00 00 00 00       	mov    $0x0,%eax
 80493de:	85 c0                	test   %eax,%eax
 80493e0:	75 0c                	jne    80493ee <rio_readlineb+0xaa>
 80493e2:	83 fd 01             	cmp    $0x1,%ebp
 80493e5:	75 d5                	jne    80493bc <rio_readlineb+0x78>
 80493e7:	bd 00 00 00 00       	mov    $0x0,%ebp
 80493ec:	eb d1                	jmp    80493bf <rio_readlineb+0x7b>
 80493ee:	bd ff ff ff ff       	mov    $0xffffffff,%ebp
 80493f3:	eb ca                	jmp    80493bf <rio_readlineb+0x7b>

080493f5 <submitr>:
 80493f5:	55                   	push   %ebp
 80493f6:	57                   	push   %edi
 80493f7:	56                   	push   %esi
 80493f8:	53                   	push   %ebx
 80493f9:	81 ec 60 a0 00 00    	sub    $0xa060,%esp
 80493ff:	8b 9c 24 74 a0 00 00 	mov    0xa074(%esp),%ebx
 8049406:	8b 84 24 7c a0 00 00 	mov    0xa07c(%esp),%eax
 804940d:	89 44 24 0c          	mov    %eax,0xc(%esp)
 8049411:	8b 84 24 80 a0 00 00 	mov    0xa080(%esp),%eax
 8049418:	89 44 24 10          	mov    %eax,0x10(%esp)
 804941c:	8b 84 24 84 a0 00 00 	mov    0xa084(%esp),%eax
 8049423:	89 44 24 14          	mov    %eax,0x14(%esp)
 8049427:	8b b4 24 88 a0 00 00 	mov    0xa088(%esp),%esi
 804942e:	8b 84 24 8c a0 00 00 	mov    0xa08c(%esp),%eax
 8049435:	89 44 24 18          	mov    %eax,0x18(%esp)
 8049439:	65 a1 14 00 00 00    	mov    %gs:0x14,%eax
 804943f:	89 84 24 50 a0 00 00 	mov    %eax,0xa050(%esp)
 8049446:	31 c0                	xor    %eax,%eax
 8049448:	c7 44 24 30 00 00 00 	movl   $0x0,0x30(%esp)
 804944f:	00 
 8049450:	6a 00                	push   $0x0
 8049452:	6a 01                	push   $0x1
 8049454:	6a 02                	push   $0x2
 8049456:	e8 f5 f3 ff ff       	call   8048850 <socket@plt>
 804945b:	83 c4 10             	add    $0x10,%esp
 804945e:	85 c0                	test   %eax,%eax
 8049460:	0f 88 04 01 00 00    	js     804956a <submitr+0x175>
 8049466:	89 c5                	mov    %eax,%ebp
 8049468:	83 ec 0c             	sub    $0xc,%esp
 804946b:	53                   	push   %ebx
 804946c:	e8 ff f3 ff ff       	call   8048870 <gethostbyname@plt>
 8049471:	83 c4 10             	add    $0x10,%esp
 8049474:	85 c0                	test   %eax,%eax
 8049476:	0f 84 40 01 00 00    	je     80495bc <submitr+0x1c7>
 804947c:	8d 5c 24 30          	lea    0x30(%esp),%ebx
 8049480:	c7 44 24 30 00 00 00 	movl   $0x0,0x30(%esp)
 8049487:	00 
 8049488:	c7 44 24 34 00 00 00 	movl   $0x0,0x34(%esp)
 804948f:	00 
 8049490:	c7 44 24 38 00 00 00 	movl   $0x0,0x38(%esp)
 8049497:	00 
 8049498:	c7 44 24 3c 00 00 00 	movl   $0x0,0x3c(%esp)
 804949f:	00 
 80494a0:	66 c7 44 24 30 02 00 	movw   $0x2,0x30(%esp)
 80494a7:	6a 0c                	push   $0xc
 80494a9:	ff 70 0c             	pushl  0xc(%eax)
 80494ac:	8b 40 10             	mov    0x10(%eax),%eax
 80494af:	ff 30                	pushl  (%eax)
 80494b1:	8d 44 24 40          	lea    0x40(%esp),%eax
 80494b5:	50                   	push   %eax
 80494b6:	e8 15 f3 ff ff       	call   80487d0 <__memmove_chk@plt>
 80494bb:	0f b7 84 24 84 a0 00 	movzwl 0xa084(%esp),%eax
 80494c2:	00 
 80494c3:	66 c1 c8 08          	ror    $0x8,%ax
 80494c7:	66 89 44 24 42       	mov    %ax,0x42(%esp)
 80494cc:	83 c4 0c             	add    $0xc,%esp
 80494cf:	6a 10                	push   $0x10
 80494d1:	53                   	push   %ebx
 80494d2:	55                   	push   %ebp
 80494d3:	e8 b8 f3 ff ff       	call   8048890 <connect@plt>
 80494d8:	83 c4 10             	add    $0x10,%esp
 80494db:	85 c0                	test   %eax,%eax
 80494dd:	0f 88 49 01 00 00    	js     804962c <submitr+0x237>
 80494e3:	ba ff ff ff ff       	mov    $0xffffffff,%edx
 80494e8:	b8 00 00 00 00       	mov    $0x0,%eax
 80494ed:	89 d1                	mov    %edx,%ecx
 80494ef:	89 f7                	mov    %esi,%edi
 80494f1:	f2 ae                	repnz scas %es:(%edi),%al
 80494f3:	89 cb                	mov    %ecx,%ebx
 80494f5:	f7 d3                	not    %ebx
 80494f7:	89 d1                	mov    %edx,%ecx
 80494f9:	8b 7c 24 08          	mov    0x8(%esp),%edi
 80494fd:	f2 ae                	repnz scas %es:(%edi),%al
 80494ff:	89 4c 24 18          	mov    %ecx,0x18(%esp)
 8049503:	89 d1                	mov    %edx,%ecx
 8049505:	8b 7c 24 0c          	mov    0xc(%esp),%edi
 8049509:	f2 ae                	repnz scas %es:(%edi),%al
 804950b:	89 cf                	mov    %ecx,%edi
 804950d:	f7 d7                	not    %edi
 804950f:	89 7c 24 1c          	mov    %edi,0x1c(%esp)
 8049513:	89 d1                	mov    %edx,%ecx
 8049515:	8b 7c 24 10          	mov    0x10(%esp),%edi
 8049519:	f2 ae                	repnz scas %es:(%edi),%al
 804951b:	8b 54 24 1c          	mov    0x1c(%esp),%edx
 804951f:	2b 54 24 18          	sub    0x18(%esp),%edx
 8049523:	29 ca                	sub    %ecx,%edx
 8049525:	8d 44 5b fd          	lea    -0x3(%ebx,%ebx,2),%eax
 8049529:	8d 44 02 7b          	lea    0x7b(%edx,%eax,1),%eax
 804952d:	3d 00 20 00 00       	cmp    $0x2000,%eax
 8049532:	0f 87 56 01 00 00    	ja     804968e <submitr+0x299>
 8049538:	8d 94 24 4c 40 00 00 	lea    0x404c(%esp),%edx
 804953f:	b9 00 08 00 00       	mov    $0x800,%ecx
 8049544:	b8 00 00 00 00       	mov    $0x0,%eax
 8049549:	89 d7                	mov    %edx,%edi
 804954b:	f3 ab                	rep stos %eax,%es:(%edi)
 804954d:	b9 ff ff ff ff       	mov    $0xffffffff,%ecx
 8049552:	89 f7                	mov    %esi,%edi
 8049554:	f2 ae                	repnz scas %es:(%edi),%al
 8049556:	f7 d1                	not    %ecx
 8049558:	89 cb                	mov    %ecx,%ebx
 804955a:	83 eb 01             	sub    $0x1,%ebx
 804955d:	0f 84 07 06 00 00    	je     8049b6a <submitr+0x775>
 8049563:	89 d7                	mov    %edx,%edi
 8049565:	e9 b0 01 00 00       	jmp    804971a <submitr+0x325>
 804956a:	8b 44 24 14          	mov    0x14(%esp),%eax
 804956e:	c7 00 45 72 72 6f    	movl   $0x6f727245,(%eax)
 8049574:	c7 40 04 72 3a 20 43 	movl   $0x43203a72,0x4(%eax)
 804957b:	c7 40 08 6c 69 65 6e 	movl   $0x6e65696c,0x8(%eax)
 8049582:	c7 40 0c 74 20 75 6e 	movl   $0x6e752074,0xc(%eax)
 8049589:	c7 40 10 61 62 6c 65 	movl   $0x656c6261,0x10(%eax)
 8049590:	c7 40 14 20 74 6f 20 	movl   $0x206f7420,0x14(%eax)
 8049597:	c7 40 18 63 72 65 61 	movl   $0x61657263,0x18(%eax)
 804959e:	c7 40 1c 74 65 20 73 	movl   $0x73206574,0x1c(%eax)
 80495a5:	c7 40 20 6f 63 6b 65 	movl   $0x656b636f,0x20(%eax)
 80495ac:	66 c7 40 24 74 00    	movw   $0x74,0x24(%eax)
 80495b2:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 80495b7:	e9 d0 04 00 00       	jmp    8049a8c <submitr+0x697>
 80495bc:	8b 44 24 14          	mov    0x14(%esp),%eax
 80495c0:	c7 00 45 72 72 6f    	movl   $0x6f727245,(%eax)
 80495c6:	c7 40 04 72 3a 20 44 	movl   $0x44203a72,0x4(%eax)
 80495cd:	c7 40 08 4e 53 20 69 	movl   $0x6920534e,0x8(%eax)
 80495d4:	c7 40 0c 73 20 75 6e 	movl   $0x6e752073,0xc(%eax)
 80495db:	c7 40 10 61 62 6c 65 	movl   $0x656c6261,0x10(%eax)
 80495e2:	c7 40 14 20 74 6f 20 	movl   $0x206f7420,0x14(%eax)
 80495e9:	c7 40 18 72 65 73 6f 	movl   $0x6f736572,0x18(%eax)
 80495f0:	c7 40 1c 6c 76 65 20 	movl   $0x2065766c,0x1c(%eax)
 80495f7:	c7 40 20 73 65 72 76 	movl   $0x76726573,0x20(%eax)
 80495fe:	c7 40 24 65 72 20 61 	movl   $0x61207265,0x24(%eax)
 8049605:	c7 40 28 64 64 72 65 	movl   $0x65726464,0x28(%eax)
 804960c:	66 c7 40 2c 73 73    	movw   $0x7373,0x2c(%eax)
 8049612:	c6 40 2e 00          	movb   $0x0,0x2e(%eax)
 8049616:	83 ec 0c             	sub    $0xc,%esp
 8049619:	55                   	push   %ebp
 804961a:	e8 81 f2 ff ff       	call   80488a0 <close@plt>
 804961f:	83 c4 10             	add    $0x10,%esp
 8049622:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049627:	e9 60 04 00 00       	jmp    8049a8c <submitr+0x697>
 804962c:	8b 44 24 14          	mov    0x14(%esp),%eax
 8049630:	c7 00 45 72 72 6f    	movl   $0x6f727245,(%eax)
 8049636:	c7 40 04 72 3a 20 55 	movl   $0x55203a72,0x4(%eax)
 804963d:	c7 40 08 6e 61 62 6c 	movl   $0x6c62616e,0x8(%eax)
 8049644:	c7 40 0c 65 20 74 6f 	movl   $0x6f742065,0xc(%eax)
 804964b:	c7 40 10 20 63 6f 6e 	movl   $0x6e6f6320,0x10(%eax)
 8049652:	c7 40 14 6e 65 63 74 	movl   $0x7463656e,0x14(%eax)
 8049659:	c7 40 18 20 74 6f 20 	movl   $0x206f7420,0x18(%eax)
 8049660:	c7 40 1c 74 68 65 20 	movl   $0x20656874,0x1c(%eax)
 8049667:	c7 40 20 73 65 72 76 	movl   $0x76726573,0x20(%eax)
 804966e:	66 c7 40 24 65 72    	movw   $0x7265,0x24(%eax)
 8049674:	c6 40 26 00          	movb   $0x0,0x26(%eax)
 8049678:	83 ec 0c             	sub    $0xc,%esp
 804967b:	55                   	push   %ebp
 804967c:	e8 1f f2 ff ff       	call   80488a0 <close@plt>
 8049681:	83 c4 10             	add    $0x10,%esp
 8049684:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049689:	e9 fe 03 00 00       	jmp    8049a8c <submitr+0x697>
 804968e:	8b 44 24 14          	mov    0x14(%esp),%eax
 8049692:	c7 00 45 72 72 6f    	movl   $0x6f727245,(%eax)
 8049698:	c7 40 04 72 3a 20 52 	movl   $0x52203a72,0x4(%eax)
 804969f:	c7 40 08 65 73 75 6c 	movl   $0x6c757365,0x8(%eax)
 80496a6:	c7 40 0c 74 20 73 74 	movl   $0x74732074,0xc(%eax)
 80496ad:	c7 40 10 72 69 6e 67 	movl   $0x676e6972,0x10(%eax)
 80496b4:	c7 40 14 20 74 6f 6f 	movl   $0x6f6f7420,0x14(%eax)
 80496bb:	c7 40 18 20 6c 61 72 	movl   $0x72616c20,0x18(%eax)
 80496c2:	c7 40 1c 67 65 2e 20 	movl   $0x202e6567,0x1c(%eax)
 80496c9:	c7 40 20 49 6e 63 72 	movl   $0x72636e49,0x20(%eax)
 80496d0:	c7 40 24 65 61 73 65 	movl   $0x65736165,0x24(%eax)
 80496d7:	c7 40 28 20 53 55 42 	movl   $0x42555320,0x28(%eax)
 80496de:	c7 40 2c 4d 49 54 52 	movl   $0x5254494d,0x2c(%eax)
 80496e5:	c7 40 30 5f 4d 41 58 	movl   $0x58414d5f,0x30(%eax)
 80496ec:	c7 40 34 42 55 46 00 	movl   $0x465542,0x34(%eax)
 80496f3:	83 ec 0c             	sub    $0xc,%esp
 80496f6:	55                   	push   %ebp
 80496f7:	e8 a4 f1 ff ff       	call   80488a0 <close@plt>
 80496fc:	83 c4 10             	add    $0x10,%esp
 80496ff:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049704:	e9 83 03 00 00       	jmp    8049a8c <submitr+0x697>
 8049709:	88 17                	mov    %dl,(%edi)
 804970b:	8d 7f 01             	lea    0x1(%edi),%edi
 804970e:	83 c6 01             	add    $0x1,%esi
 8049711:	83 eb 01             	sub    $0x1,%ebx
 8049714:	0f 84 50 04 00 00    	je     8049b6a <submitr+0x775>
 804971a:	0f b6 16             	movzbl (%esi),%edx
 804971d:	8d 4a d6             	lea    -0x2a(%edx),%ecx
 8049720:	b8 01 00 00 00       	mov    $0x1,%eax
 8049725:	80 f9 0f             	cmp    $0xf,%cl
 8049728:	77 0d                	ja     8049737 <submitr+0x342>
 804972a:	b8 d9 ff 00 00       	mov    $0xffd9,%eax
 804972f:	d3 e8                	shr    %cl,%eax
 8049731:	83 f0 01             	xor    $0x1,%eax
 8049734:	83 e0 01             	and    $0x1,%eax
 8049737:	80 fa 5f             	cmp    $0x5f,%dl
 804973a:	74 cd                	je     8049709 <submitr+0x314>
 804973c:	84 c0                	test   %al,%al
 804973e:	74 c9                	je     8049709 <submitr+0x314>
 8049740:	89 d0                	mov    %edx,%eax
 8049742:	83 e0 df             	and    $0xffffffdf,%eax
 8049745:	83 e8 41             	sub    $0x41,%eax
 8049748:	3c 19                	cmp    $0x19,%al
 804974a:	76 bd                	jbe    8049709 <submitr+0x314>
 804974c:	80 fa 20             	cmp    $0x20,%dl
 804974f:	74 58                	je     80497a9 <submitr+0x3b4>
 8049751:	8d 42 e0             	lea    -0x20(%edx),%eax
 8049754:	3c 5f                	cmp    $0x5f,%al
 8049756:	76 09                	jbe    8049761 <submitr+0x36c>
 8049758:	80 fa 09             	cmp    $0x9,%dl
 804975b:	0f 85 c5 03 00 00    	jne    8049b26 <submitr+0x731>
 8049761:	83 ec 0c             	sub    $0xc,%esp
 8049764:	0f b6 d2             	movzbl %dl,%edx
 8049767:	52                   	push   %edx
 8049768:	68 80 a3 04 08       	push   $0x804a380
 804976d:	6a 08                	push   $0x8
 804976f:	6a 01                	push   $0x1
 8049771:	8d 84 24 68 80 00 00 	lea    0x8068(%esp),%eax
 8049778:	50                   	push   %eax
 8049779:	e8 42 f1 ff ff       	call   80488c0 <__sprintf_chk@plt>
 804977e:	0f b6 84 24 6c 80 00 	movzbl 0x806c(%esp),%eax
 8049785:	00 
 8049786:	88 07                	mov    %al,(%edi)
 8049788:	0f b6 84 24 6d 80 00 	movzbl 0x806d(%esp),%eax
 804978f:	00 
 8049790:	88 47 01             	mov    %al,0x1(%edi)
 8049793:	0f b6 84 24 6e 80 00 	movzbl 0x806e(%esp),%eax
 804979a:	00 
 804979b:	88 47 02             	mov    %al,0x2(%edi)
 804979e:	83 c4 20             	add    $0x20,%esp
 80497a1:	8d 7f 03             	lea    0x3(%edi),%edi
 80497a4:	e9 65 ff ff ff       	jmp    804970e <submitr+0x319>
 80497a9:	c6 07 2b             	movb   $0x2b,(%edi)
 80497ac:	8d 7f 01             	lea    0x1(%edi),%edi
 80497af:	e9 5a ff ff ff       	jmp    804970e <submitr+0x319>
 80497b4:	01 c6                	add    %eax,%esi
 80497b6:	29 c3                	sub    %eax,%ebx
 80497b8:	74 24                	je     80497de <submitr+0x3e9>
 80497ba:	83 ec 04             	sub    $0x4,%esp
 80497bd:	53                   	push   %ebx
 80497be:	56                   	push   %esi
 80497bf:	55                   	push   %ebp
 80497c0:	e8 3b f0 ff ff       	call   8048800 <write@plt>
 80497c5:	83 c4 10             	add    $0x10,%esp
 80497c8:	85 c0                	test   %eax,%eax
 80497ca:	7f e8                	jg     80497b4 <submitr+0x3bf>
 80497cc:	e8 5f f0 ff ff       	call   8048830 <__errno_location@plt>
 80497d1:	83 38 04             	cmpl   $0x4,(%eax)
 80497d4:	0f 85 b0 00 00 00    	jne    804988a <submitr+0x495>
 80497da:	89 f8                	mov    %edi,%eax
 80497dc:	eb d6                	jmp    80497b4 <submitr+0x3bf>
 80497de:	83 7c 24 08 00       	cmpl   $0x0,0x8(%esp)
 80497e3:	0f 88 a1 00 00 00    	js     804988a <submitr+0x495>
 80497e9:	89 6c 24 40          	mov    %ebp,0x40(%esp)
 80497ed:	c7 44 24 44 00 00 00 	movl   $0x0,0x44(%esp)
 80497f4:	00 
 80497f5:	8d 44 24 4c          	lea    0x4c(%esp),%eax
 80497f9:	89 44 24 48          	mov    %eax,0x48(%esp)
 80497fd:	b9 00 20 00 00       	mov    $0x2000,%ecx
 8049802:	8d 94 24 4c 20 00 00 	lea    0x204c(%esp),%edx
 8049809:	8d 44 24 40          	lea    0x40(%esp),%eax
 804980d:	e8 32 fb ff ff       	call   8049344 <rio_readlineb>
 8049812:	85 c0                	test   %eax,%eax
 8049814:	0f 8e d6 00 00 00    	jle    80498f0 <submitr+0x4fb>
 804981a:	83 ec 0c             	sub    $0xc,%esp
 804981d:	8d 84 24 58 80 00 00 	lea    0x8058(%esp),%eax
 8049824:	50                   	push   %eax
 8049825:	8d 44 24 3c          	lea    0x3c(%esp),%eax
 8049829:	50                   	push   %eax
 804982a:	8d 84 24 60 60 00 00 	lea    0x6060(%esp),%eax
 8049831:	50                   	push   %eax
 8049832:	68 87 a3 04 08       	push   $0x804a387
 8049837:	8d 84 24 68 20 00 00 	lea    0x2068(%esp),%eax
 804983e:	50                   	push   %eax
 804983f:	e8 cc ef ff ff       	call   8048810 <__isoc99_sscanf@plt>
 8049844:	8b 44 24 4c          	mov    0x4c(%esp),%eax
 8049848:	83 c4 20             	add    $0x20,%esp
 804984b:	3d c8 00 00 00       	cmp    $0xc8,%eax
 8049850:	0f 84 a6 01 00 00    	je     80499fc <submitr+0x607>
 8049856:	83 ec 08             	sub    $0x8,%esp
 8049859:	8d 94 24 54 80 00 00 	lea    0x8054(%esp),%edx
 8049860:	52                   	push   %edx
 8049861:	50                   	push   %eax
 8049862:	68 98 a2 04 08       	push   $0x804a298
 8049867:	6a ff                	push   $0xffffffff
 8049869:	6a 01                	push   $0x1
 804986b:	ff 74 24 30          	pushl  0x30(%esp)
 804986f:	e8 4c f0 ff ff       	call   80488c0 <__sprintf_chk@plt>
 8049874:	83 c4 14             	add    $0x14,%esp
 8049877:	55                   	push   %ebp
 8049878:	e8 23 f0 ff ff       	call   80488a0 <close@plt>
 804987d:	83 c4 10             	add    $0x10,%esp
 8049880:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049885:	e9 02 02 00 00       	jmp    8049a8c <submitr+0x697>
 804988a:	8b 44 24 14          	mov    0x14(%esp),%eax
 804988e:	c7 00 45 72 72 6f    	movl   $0x6f727245,(%eax)
 8049894:	c7 40 04 72 3a 20 43 	movl   $0x43203a72,0x4(%eax)
 804989b:	c7 40 08 6c 69 65 6e 	movl   $0x6e65696c,0x8(%eax)
 80498a2:	c7 40 0c 74 20 75 6e 	movl   $0x6e752074,0xc(%eax)
 80498a9:	c7 40 10 61 62 6c 65 	movl   $0x656c6261,0x10(%eax)
 80498b0:	c7 40 14 20 74 6f 20 	movl   $0x206f7420,0x14(%eax)
 80498b7:	c7 40 18 77 72 69 74 	movl   $0x74697277,0x18(%eax)
 80498be:	c7 40 1c 65 20 74 6f 	movl   $0x6f742065,0x1c(%eax)
 80498c5:	c7 40 20 20 74 68 65 	movl   $0x65687420,0x20(%eax)
 80498cc:	c7 40 24 20 73 65 72 	movl   $0x72657320,0x24(%eax)
 80498d3:	c7 40 28 76 65 72 00 	movl   $0x726576,0x28(%eax)
 80498da:	83 ec 0c             	sub    $0xc,%esp
 80498dd:	55                   	push   %ebp
 80498de:	e8 bd ef ff ff       	call   80488a0 <close@plt>
 80498e3:	83 c4 10             	add    $0x10,%esp
 80498e6:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 80498eb:	e9 9c 01 00 00       	jmp    8049a8c <submitr+0x697>
 80498f0:	8b 44 24 14          	mov    0x14(%esp),%eax
 80498f4:	c7 00 45 72 72 6f    	movl   $0x6f727245,(%eax)
 80498fa:	c7 40 04 72 3a 20 43 	movl   $0x43203a72,0x4(%eax)
 8049901:	c7 40 08 6c 69 65 6e 	movl   $0x6e65696c,0x8(%eax)
 8049908:	c7 40 0c 74 20 75 6e 	movl   $0x6e752074,0xc(%eax)
 804990f:	c7 40 10 61 62 6c 65 	movl   $0x656c6261,0x10(%eax)
 8049916:	c7 40 14 20 74 6f 20 	movl   $0x206f7420,0x14(%eax)
 804991d:	c7 40 18 72 65 61 64 	movl   $0x64616572,0x18(%eax)
 8049924:	c7 40 1c 20 66 69 72 	movl   $0x72696620,0x1c(%eax)
 804992b:	c7 40 20 73 74 20 68 	movl   $0x68207473,0x20(%eax)
 8049932:	c7 40 24 65 61 64 65 	movl   $0x65646165,0x24(%eax)
 8049939:	c7 40 28 72 20 66 72 	movl   $0x72662072,0x28(%eax)
 8049940:	c7 40 2c 6f 6d 20 73 	movl   $0x73206d6f,0x2c(%eax)
 8049947:	c7 40 30 65 72 76 65 	movl   $0x65767265,0x30(%eax)
 804994e:	66 c7 40 34 72 00    	movw   $0x72,0x34(%eax)
 8049954:	83 ec 0c             	sub    $0xc,%esp
 8049957:	55                   	push   %ebp
 8049958:	e8 43 ef ff ff       	call   80488a0 <close@plt>
 804995d:	83 c4 10             	add    $0x10,%esp
 8049960:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049965:	e9 22 01 00 00       	jmp    8049a8c <submitr+0x697>
 804996a:	8b 44 24 14          	mov    0x14(%esp),%eax
 804996e:	c7 00 45 72 72 6f    	movl   $0x6f727245,(%eax)
 8049974:	c7 40 04 72 3a 20 43 	movl   $0x43203a72,0x4(%eax)
 804997b:	c7 40 08 6c 69 65 6e 	movl   $0x6e65696c,0x8(%eax)
 8049982:	c7 40 0c 74 20 75 6e 	movl   $0x6e752074,0xc(%eax)
 8049989:	c7 40 10 61 62 6c 65 	movl   $0x656c6261,0x10(%eax)
 8049990:	c7 40 14 20 74 6f 20 	movl   $0x206f7420,0x14(%eax)
 8049997:	c7 40 18 72 65 61 64 	movl   $0x64616572,0x18(%eax)
 804999e:	c7 40 1c 20 68 65 61 	movl   $0x61656820,0x1c(%eax)
 80499a5:	c7 40 20 64 65 72 73 	movl   $0x73726564,0x20(%eax)
 80499ac:	c7 40 24 20 66 72 6f 	movl   $0x6f726620,0x24(%eax)
 80499b3:	c7 40 28 6d 20 73 65 	movl   $0x6573206d,0x28(%eax)
 80499ba:	c7 40 2c 72 76 65 72 	movl   $0x72657672,0x2c(%eax)
 80499c1:	c6 40 30 00          	movb   $0x0,0x30(%eax)
 80499c5:	83 ec 0c             	sub    $0xc,%esp
 80499c8:	55                   	push   %ebp
 80499c9:	e8 d2 ee ff ff       	call   80488a0 <close@plt>
 80499ce:	83 c4 10             	add    $0x10,%esp
 80499d1:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 80499d6:	e9 b1 00 00 00       	jmp    8049a8c <submitr+0x697>
 80499db:	85 c0                	test   %eax,%eax
 80499dd:	74 4b                	je     8049a2a <submitr+0x635>
 80499df:	b9 00 20 00 00       	mov    $0x2000,%ecx
 80499e4:	8d 94 24 4c 20 00 00 	lea    0x204c(%esp),%edx
 80499eb:	8d 44 24 40          	lea    0x40(%esp),%eax
 80499ef:	e8 50 f9 ff ff       	call   8049344 <rio_readlineb>
 80499f4:	85 c0                	test   %eax,%eax
 80499f6:	0f 8e 6e ff ff ff    	jle    804996a <submitr+0x575>
 80499fc:	0f b6 94 24 4c 20 00 	movzbl 0x204c(%esp),%edx
 8049a03:	00 
 8049a04:	b8 0d 00 00 00       	mov    $0xd,%eax
 8049a09:	29 d0                	sub    %edx,%eax
 8049a0b:	75 ce                	jne    80499db <submitr+0x5e6>
 8049a0d:	0f b6 94 24 4d 20 00 	movzbl 0x204d(%esp),%edx
 8049a14:	00 
 8049a15:	b8 0a 00 00 00       	mov    $0xa,%eax
 8049a1a:	29 d0                	sub    %edx,%eax
 8049a1c:	75 bd                	jne    80499db <submitr+0x5e6>
 8049a1e:	0f b6 84 24 4e 20 00 	movzbl 0x204e(%esp),%eax
 8049a25:	00 
 8049a26:	f7 d8                	neg    %eax
 8049a28:	eb b1                	jmp    80499db <submitr+0x5e6>
 8049a2a:	b9 00 20 00 00       	mov    $0x2000,%ecx
 8049a2f:	8d 94 24 4c 20 00 00 	lea    0x204c(%esp),%edx
 8049a36:	8d 44 24 40          	lea    0x40(%esp),%eax
 8049a3a:	e8 05 f9 ff ff       	call   8049344 <rio_readlineb>
 8049a3f:	85 c0                	test   %eax,%eax
 8049a41:	7e 68                	jle    8049aab <submitr+0x6b6>
 8049a43:	83 ec 08             	sub    $0x8,%esp
 8049a46:	8d 84 24 54 20 00 00 	lea    0x2054(%esp),%eax
 8049a4d:	50                   	push   %eax
 8049a4e:	8b 7c 24 20          	mov    0x20(%esp),%edi
 8049a52:	57                   	push   %edi
 8049a53:	e8 48 ed ff ff       	call   80487a0 <strcpy@plt>
 8049a58:	89 2c 24             	mov    %ebp,(%esp)
 8049a5b:	e8 40 ee ff ff       	call   80488a0 <close@plt>
 8049a60:	0f b6 17             	movzbl (%edi),%edx
 8049a63:	b8 4f 00 00 00       	mov    $0x4f,%eax
 8049a68:	83 c4 10             	add    $0x10,%esp
 8049a6b:	29 d0                	sub    %edx,%eax
 8049a6d:	75 13                	jne    8049a82 <submitr+0x68d>
 8049a6f:	0f b6 57 01          	movzbl 0x1(%edi),%edx
 8049a73:	b8 4b 00 00 00       	mov    $0x4b,%eax
 8049a78:	29 d0                	sub    %edx,%eax
 8049a7a:	75 06                	jne    8049a82 <submitr+0x68d>
 8049a7c:	0f b6 47 02          	movzbl 0x2(%edi),%eax
 8049a80:	f7 d8                	neg    %eax
 8049a82:	85 c0                	test   %eax,%eax
 8049a84:	0f 95 c0             	setne  %al
 8049a87:	0f b6 c0             	movzbl %al,%eax
 8049a8a:	f7 d8                	neg    %eax
 8049a8c:	8b bc 24 4c a0 00 00 	mov    0xa04c(%esp),%edi
 8049a93:	65 33 3d 14 00 00 00 	xor    %gs:0x14,%edi
 8049a9a:	0f 85 2a 01 00 00    	jne    8049bca <submitr+0x7d5>
 8049aa0:	81 c4 5c a0 00 00    	add    $0xa05c,%esp
 8049aa6:	5b                   	pop    %ebx
 8049aa7:	5e                   	pop    %esi
 8049aa8:	5f                   	pop    %edi
 8049aa9:	5d                   	pop    %ebp
 8049aaa:	c3                   	ret    
 8049aab:	8b 44 24 14          	mov    0x14(%esp),%eax
 8049aaf:	c7 00 45 72 72 6f    	movl   $0x6f727245,(%eax)
 8049ab5:	c7 40 04 72 3a 20 43 	movl   $0x43203a72,0x4(%eax)
 8049abc:	c7 40 08 6c 69 65 6e 	movl   $0x6e65696c,0x8(%eax)
 8049ac3:	c7 40 0c 74 20 75 6e 	movl   $0x6e752074,0xc(%eax)
 8049aca:	c7 40 10 61 62 6c 65 	movl   $0x656c6261,0x10(%eax)
 8049ad1:	c7 40 14 20 74 6f 20 	movl   $0x206f7420,0x14(%eax)
 8049ad8:	c7 40 18 72 65 61 64 	movl   $0x64616572,0x18(%eax)
 8049adf:	c7 40 1c 20 73 74 61 	movl   $0x61747320,0x1c(%eax)
 8049ae6:	c7 40 20 74 75 73 20 	movl   $0x20737574,0x20(%eax)
 8049aed:	c7 40 24 6d 65 73 73 	movl   $0x7373656d,0x24(%eax)
 8049af4:	c7 40 28 61 67 65 20 	movl   $0x20656761,0x28(%eax)
 8049afb:	c7 40 2c 66 72 6f 6d 	movl   $0x6d6f7266,0x2c(%eax)
 8049b02:	c7 40 30 20 73 65 72 	movl   $0x72657320,0x30(%eax)
 8049b09:	c7 40 34 76 65 72 00 	movl   $0x726576,0x34(%eax)
 8049b10:	83 ec 0c             	sub    $0xc,%esp
 8049b13:	55                   	push   %ebp
 8049b14:	e8 87 ed ff ff       	call   80488a0 <close@plt>
 8049b19:	83 c4 10             	add    $0x10,%esp
 8049b1c:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049b21:	e9 66 ff ff ff       	jmp    8049a8c <submitr+0x697>
 8049b26:	a1 c8 a2 04 08       	mov    0x804a2c8,%eax
 8049b2b:	8b 5c 24 14          	mov    0x14(%esp),%ebx
 8049b2f:	89 03                	mov    %eax,(%ebx)
 8049b31:	a1 07 a3 04 08       	mov    0x804a307,%eax
 8049b36:	89 43 3f             	mov    %eax,0x3f(%ebx)
 8049b39:	8d 7b 04             	lea    0x4(%ebx),%edi
 8049b3c:	83 e7 fc             	and    $0xfffffffc,%edi
 8049b3f:	29 fb                	sub    %edi,%ebx
 8049b41:	89 d8                	mov    %ebx,%eax
 8049b43:	be c8 a2 04 08       	mov    $0x804a2c8,%esi
 8049b48:	29 de                	sub    %ebx,%esi
 8049b4a:	83 c0 43             	add    $0x43,%eax
 8049b4d:	c1 e8 02             	shr    $0x2,%eax
 8049b50:	89 c1                	mov    %eax,%ecx
 8049b52:	f3 a5                	rep movsl %ds:(%esi),%es:(%edi)
 8049b54:	83 ec 0c             	sub    $0xc,%esp
 8049b57:	55                   	push   %ebp
 8049b58:	e8 43 ed ff ff       	call   80488a0 <close@plt>
 8049b5d:	83 c4 10             	add    $0x10,%esp
 8049b60:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049b65:	e9 22 ff ff ff       	jmp    8049a8c <submitr+0x697>
 8049b6a:	8d 84 24 4c 40 00 00 	lea    0x404c(%esp),%eax
 8049b71:	50                   	push   %eax
 8049b72:	ff 74 24 14          	pushl  0x14(%esp)
 8049b76:	ff 74 24 14          	pushl  0x14(%esp)
 8049b7a:	ff 74 24 14          	pushl  0x14(%esp)
 8049b7e:	68 0c a3 04 08       	push   $0x804a30c
 8049b83:	68 00 20 00 00       	push   $0x2000
 8049b88:	6a 01                	push   $0x1
 8049b8a:	8d bc 24 68 20 00 00 	lea    0x2068(%esp),%edi
 8049b91:	57                   	push   %edi
 8049b92:	e8 29 ed ff ff       	call   80488c0 <__sprintf_chk@plt>
 8049b97:	b8 00 00 00 00       	mov    $0x0,%eax
 8049b9c:	b9 ff ff ff ff       	mov    $0xffffffff,%ecx
 8049ba1:	f2 ae                	repnz scas %es:(%edi),%al
 8049ba3:	f7 d1                	not    %ecx
 8049ba5:	8d 41 ff             	lea    -0x1(%ecx),%eax
 8049ba8:	89 44 24 28          	mov    %eax,0x28(%esp)
 8049bac:	83 c4 20             	add    $0x20,%esp
 8049baf:	89 c3                	mov    %eax,%ebx
 8049bb1:	8d b4 24 4c 20 00 00 	lea    0x204c(%esp),%esi
 8049bb8:	bf 00 00 00 00       	mov    $0x0,%edi
 8049bbd:	85 c0                	test   %eax,%eax
 8049bbf:	0f 85 f5 fb ff ff    	jne    80497ba <submitr+0x3c5>
 8049bc5:	e9 1f fc ff ff       	jmp    80497e9 <submitr+0x3f4>
 8049bca:	e8 c1 eb ff ff       	call   8048790 <__stack_chk_fail@plt>

08049bcf <init_timeout>:
 8049bcf:	53                   	push   %ebx
 8049bd0:	83 ec 08             	sub    $0x8,%esp
 8049bd3:	8b 5c 24 10          	mov    0x10(%esp),%ebx
 8049bd7:	85 db                	test   %ebx,%ebx
 8049bd9:	74 24                	je     8049bff <init_timeout+0x30>
 8049bdb:	83 ec 08             	sub    $0x8,%esp
 8049bde:	68 21 93 04 08       	push   $0x8049321
 8049be3:	6a 0e                	push   $0xe
 8049be5:	e8 76 eb ff ff       	call   8048760 <signal@plt>
 8049bea:	85 db                	test   %ebx,%ebx
 8049bec:	b8 00 00 00 00       	mov    $0x0,%eax
 8049bf1:	0f 48 d8             	cmovs  %eax,%ebx
 8049bf4:	89 1c 24             	mov    %ebx,(%esp)
 8049bf7:	e8 84 eb ff ff       	call   8048780 <alarm@plt>
 8049bfc:	83 c4 10             	add    $0x10,%esp
 8049bff:	83 c4 08             	add    $0x8,%esp
 8049c02:	5b                   	pop    %ebx
 8049c03:	c3                   	ret    

08049c04 <init_driver>:
 8049c04:	57                   	push   %edi
 8049c05:	56                   	push   %esi
 8049c06:	53                   	push   %ebx
 8049c07:	83 ec 28             	sub    $0x28,%esp
 8049c0a:	8b 74 24 38          	mov    0x38(%esp),%esi
 8049c0e:	65 a1 14 00 00 00    	mov    %gs:0x14,%eax
 8049c14:	89 44 24 24          	mov    %eax,0x24(%esp)
 8049c18:	31 c0                	xor    %eax,%eax
 8049c1a:	6a 01                	push   $0x1
 8049c1c:	6a 0d                	push   $0xd
 8049c1e:	e8 3d eb ff ff       	call   8048760 <signal@plt>
 8049c23:	83 c4 08             	add    $0x8,%esp
 8049c26:	6a 01                	push   $0x1
 8049c28:	6a 1d                	push   $0x1d
 8049c2a:	e8 31 eb ff ff       	call   8048760 <signal@plt>
 8049c2f:	83 c4 08             	add    $0x8,%esp
 8049c32:	6a 01                	push   $0x1
 8049c34:	6a 1d                	push   $0x1d
 8049c36:	e8 25 eb ff ff       	call   8048760 <signal@plt>
 8049c3b:	83 c4 0c             	add    $0xc,%esp
 8049c3e:	6a 00                	push   $0x0
 8049c40:	6a 01                	push   $0x1
 8049c42:	6a 02                	push   $0x2
 8049c44:	e8 07 ec ff ff       	call   8048850 <socket@plt>
 8049c49:	83 c4 10             	add    $0x10,%esp
 8049c4c:	85 c0                	test   %eax,%eax
 8049c4e:	0f 88 a9 00 00 00    	js     8049cfd <init_driver+0xf9>
 8049c54:	89 c3                	mov    %eax,%ebx
 8049c56:	83 ec 0c             	sub    $0xc,%esp
 8049c59:	68 98 a3 04 08       	push   $0x804a398
 8049c5e:	e8 0d ec ff ff       	call   8048870 <gethostbyname@plt>
 8049c63:	83 c4 10             	add    $0x10,%esp
 8049c66:	85 c0                	test   %eax,%eax
 8049c68:	0f 84 da 00 00 00    	je     8049d48 <init_driver+0x144>
 8049c6e:	8d 7c 24 0c          	lea    0xc(%esp),%edi
 8049c72:	c7 44 24 0c 00 00 00 	movl   $0x0,0xc(%esp)
 8049c79:	00 
 8049c7a:	c7 44 24 10 00 00 00 	movl   $0x0,0x10(%esp)
 8049c81:	00 
 8049c82:	c7 44 24 14 00 00 00 	movl   $0x0,0x14(%esp)
 8049c89:	00 
 8049c8a:	c7 44 24 18 00 00 00 	movl   $0x0,0x18(%esp)
 8049c91:	00 
 8049c92:	66 c7 44 24 0c 02 00 	movw   $0x2,0xc(%esp)
 8049c99:	6a 0c                	push   $0xc
 8049c9b:	ff 70 0c             	pushl  0xc(%eax)
 8049c9e:	8b 40 10             	mov    0x10(%eax),%eax
 8049ca1:	ff 30                	pushl  (%eax)
 8049ca3:	8d 44 24 1c          	lea    0x1c(%esp),%eax
 8049ca7:	50                   	push   %eax
 8049ca8:	e8 23 eb ff ff       	call   80487d0 <__memmove_chk@plt>
 8049cad:	66 c7 44 24 1e 3b 6e 	movw   $0x6e3b,0x1e(%esp)
 8049cb4:	83 c4 0c             	add    $0xc,%esp
 8049cb7:	6a 10                	push   $0x10
 8049cb9:	57                   	push   %edi
 8049cba:	53                   	push   %ebx
 8049cbb:	e8 d0 eb ff ff       	call   8048890 <connect@plt>
 8049cc0:	83 c4 10             	add    $0x10,%esp
 8049cc3:	85 c0                	test   %eax,%eax
 8049cc5:	0f 88 e9 00 00 00    	js     8049db4 <init_driver+0x1b0>
 8049ccb:	83 ec 0c             	sub    $0xc,%esp
 8049cce:	53                   	push   %ebx
 8049ccf:	e8 cc eb ff ff       	call   80488a0 <close@plt>
 8049cd4:	66 c7 06 4f 4b       	movw   $0x4b4f,(%esi)
 8049cd9:	c6 46 02 00          	movb   $0x0,0x2(%esi)
 8049cdd:	83 c4 10             	add    $0x10,%esp
 8049ce0:	b8 00 00 00 00       	mov    $0x0,%eax
 8049ce5:	8b 54 24 1c          	mov    0x1c(%esp),%edx
 8049ce9:	65 33 15 14 00 00 00 	xor    %gs:0x14,%edx
 8049cf0:	0f 85 eb 00 00 00    	jne    8049de1 <init_driver+0x1dd>
 8049cf6:	83 c4 20             	add    $0x20,%esp
 8049cf9:	5b                   	pop    %ebx
 8049cfa:	5e                   	pop    %esi
 8049cfb:	5f                   	pop    %edi
 8049cfc:	c3                   	ret    
 8049cfd:	c7 06 45 72 72 6f    	movl   $0x6f727245,(%esi)
 8049d03:	c7 46 04 72 3a 20 43 	movl   $0x43203a72,0x4(%esi)
 8049d0a:	c7 46 08 6c 69 65 6e 	movl   $0x6e65696c,0x8(%esi)
 8049d11:	c7 46 0c 74 20 75 6e 	movl   $0x6e752074,0xc(%esi)
 8049d18:	c7 46 10 61 62 6c 65 	movl   $0x656c6261,0x10(%esi)
 8049d1f:	c7 46 14 20 74 6f 20 	movl   $0x206f7420,0x14(%esi)
 8049d26:	c7 46 18 63 72 65 61 	movl   $0x61657263,0x18(%esi)
 8049d2d:	c7 46 1c 74 65 20 73 	movl   $0x73206574,0x1c(%esi)
 8049d34:	c7 46 20 6f 63 6b 65 	movl   $0x656b636f,0x20(%esi)
 8049d3b:	66 c7 46 24 74 00    	movw   $0x74,0x24(%esi)
 8049d41:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049d46:	eb 9d                	jmp    8049ce5 <init_driver+0xe1>
 8049d48:	c7 06 45 72 72 6f    	movl   $0x6f727245,(%esi)
 8049d4e:	c7 46 04 72 3a 20 44 	movl   $0x44203a72,0x4(%esi)
 8049d55:	c7 46 08 4e 53 20 69 	movl   $0x6920534e,0x8(%esi)
 8049d5c:	c7 46 0c 73 20 75 6e 	movl   $0x6e752073,0xc(%esi)
 8049d63:	c7 46 10 61 62 6c 65 	movl   $0x656c6261,0x10(%esi)
 8049d6a:	c7 46 14 20 74 6f 20 	movl   $0x206f7420,0x14(%esi)
 8049d71:	c7 46 18 72 65 73 6f 	movl   $0x6f736572,0x18(%esi)
 8049d78:	c7 46 1c 6c 76 65 20 	movl   $0x2065766c,0x1c(%esi)
 8049d7f:	c7 46 20 73 65 72 76 	movl   $0x76726573,0x20(%esi)
 8049d86:	c7 46 24 65 72 20 61 	movl   $0x61207265,0x24(%esi)
 8049d8d:	c7 46 28 64 64 72 65 	movl   $0x65726464,0x28(%esi)
 8049d94:	66 c7 46 2c 73 73    	movw   $0x7373,0x2c(%esi)
 8049d9a:	c6 46 2e 00          	movb   $0x0,0x2e(%esi)
 8049d9e:	83 ec 0c             	sub    $0xc,%esp
 8049da1:	53                   	push   %ebx
 8049da2:	e8 f9 ea ff ff       	call   80488a0 <close@plt>
 8049da7:	83 c4 10             	add    $0x10,%esp
 8049daa:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049daf:	e9 31 ff ff ff       	jmp    8049ce5 <init_driver+0xe1>
 8049db4:	83 ec 0c             	sub    $0xc,%esp
 8049db7:	68 98 a3 04 08       	push   $0x804a398
 8049dbc:	68 58 a3 04 08       	push   $0x804a358
 8049dc1:	6a ff                	push   $0xffffffff
 8049dc3:	6a 01                	push   $0x1
 8049dc5:	56                   	push   %esi
 8049dc6:	e8 f5 ea ff ff       	call   80488c0 <__sprintf_chk@plt>
 8049dcb:	83 c4 14             	add    $0x14,%esp
 8049dce:	53                   	push   %ebx
 8049dcf:	e8 cc ea ff ff       	call   80488a0 <close@plt>
 8049dd4:	83 c4 10             	add    $0x10,%esp
 8049dd7:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049ddc:	e9 04 ff ff ff       	jmp    8049ce5 <init_driver+0xe1>
 8049de1:	e8 aa e9 ff ff       	call   8048790 <__stack_chk_fail@plt>

08049de6 <driver_post>:
 8049de6:	53                   	push   %ebx
 8049de7:	83 ec 08             	sub    $0x8,%esp
 8049dea:	8b 54 24 10          	mov    0x10(%esp),%edx
 8049dee:	8b 44 24 18          	mov    0x18(%esp),%eax
 8049df2:	8b 5c 24 1c          	mov    0x1c(%esp),%ebx
 8049df6:	85 c0                	test   %eax,%eax
 8049df8:	75 17                	jne    8049e11 <driver_post+0x2b>
 8049dfa:	85 d2                	test   %edx,%edx
 8049dfc:	74 05                	je     8049e03 <driver_post+0x1d>
 8049dfe:	80 3a 00             	cmpb   $0x0,(%edx)
 8049e01:	75 34                	jne    8049e37 <driver_post+0x51>
 8049e03:	66 c7 03 4f 4b       	movw   $0x4b4f,(%ebx)
 8049e08:	c6 43 02 00          	movb   $0x0,0x2(%ebx)
 8049e0c:	83 c4 08             	add    $0x8,%esp
 8049e0f:	5b                   	pop    %ebx
 8049e10:	c3                   	ret    
 8049e11:	83 ec 04             	sub    $0x4,%esp
 8049e14:	ff 74 24 18          	pushl  0x18(%esp)
 8049e18:	68 a6 a3 04 08       	push   $0x804a3a6
 8049e1d:	6a 01                	push   $0x1
 8049e1f:	e8 1c ea ff ff       	call   8048840 <__printf_chk@plt>
 8049e24:	66 c7 03 4f 4b       	movw   $0x4b4f,(%ebx)
 8049e29:	c6 43 02 00          	movb   $0x0,0x2(%ebx)
 8049e2d:	83 c4 10             	add    $0x10,%esp
 8049e30:	b8 00 00 00 00       	mov    $0x0,%eax
 8049e35:	eb d5                	jmp    8049e0c <driver_post+0x26>
 8049e37:	83 ec 04             	sub    $0x4,%esp
 8049e3a:	53                   	push   %ebx
 8049e3b:	ff 74 24 1c          	pushl  0x1c(%esp)
 8049e3f:	68 bd a3 04 08       	push   $0x804a3bd
 8049e44:	52                   	push   %edx
 8049e45:	68 c5 a3 04 08       	push   $0x804a3c5
 8049e4a:	68 6e 3b 00 00       	push   $0x3b6e
 8049e4f:	68 98 a3 04 08       	push   $0x804a398
 8049e54:	e8 9c f5 ff ff       	call   80493f5 <submitr>
 8049e59:	83 c4 20             	add    $0x20,%esp
 8049e5c:	eb ae                	jmp    8049e0c <driver_post+0x26>
 8049e5e:	66 90                	xchg   %ax,%ax

08049e60 <__libc_csu_init>:
 8049e60:	55                   	push   %ebp
 8049e61:	57                   	push   %edi
 8049e62:	56                   	push   %esi
 8049e63:	53                   	push   %ebx
 8049e64:	e8 a7 ea ff ff       	call   8048910 <__x86.get_pc_thunk.bx>
 8049e69:	81 c3 97 21 00 00    	add    $0x2197,%ebx
 8049e6f:	83 ec 0c             	sub    $0xc,%esp
 8049e72:	8b 6c 24 20          	mov    0x20(%esp),%ebp
 8049e76:	8d b3 0c ff ff ff    	lea    -0xf4(%ebx),%esi
 8049e7c:	e8 73 e8 ff ff       	call   80486f4 <_init>
 8049e81:	8d 83 08 ff ff ff    	lea    -0xf8(%ebx),%eax
 8049e87:	29 c6                	sub    %eax,%esi
 8049e89:	c1 fe 02             	sar    $0x2,%esi
 8049e8c:	85 f6                	test   %esi,%esi
 8049e8e:	74 25                	je     8049eb5 <__libc_csu_init+0x55>
 8049e90:	31 ff                	xor    %edi,%edi
 8049e92:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
 8049e98:	83 ec 04             	sub    $0x4,%esp
 8049e9b:	ff 74 24 2c          	pushl  0x2c(%esp)
 8049e9f:	ff 74 24 2c          	pushl  0x2c(%esp)
 8049ea3:	55                   	push   %ebp
 8049ea4:	ff 94 bb 08 ff ff ff 	call   *-0xf8(%ebx,%edi,4)
 8049eab:	83 c7 01             	add    $0x1,%edi
 8049eae:	83 c4 10             	add    $0x10,%esp
 8049eb1:	39 fe                	cmp    %edi,%esi
 8049eb3:	75 e3                	jne    8049e98 <__libc_csu_init+0x38>
 8049eb5:	83 c4 0c             	add    $0xc,%esp
 8049eb8:	5b                   	pop    %ebx
 8049eb9:	5e                   	pop    %esi
 8049eba:	5f                   	pop    %edi
 8049ebb:	5d                   	pop    %ebp
 8049ebc:	c3                   	ret    
 8049ebd:	8d 76 00             	lea    0x0(%esi),%esi

08049ec0 <__libc_csu_fini>:
 8049ec0:	f3 c3                	repz ret 

Disassembly of section .fini:

08049ec4 <_fini>:
 8049ec4:	53                   	push   %ebx
 8049ec5:	83 ec 08             	sub    $0x8,%esp
 8049ec8:	e8 43 ea ff ff       	call   8048910 <__x86.get_pc_thunk.bx>
 8049ecd:	81 c3 33 21 00 00    	add    $0x2133,%ebx
 8049ed3:	83 c4 08             	add    $0x8,%esp
 8049ed6:	5b                   	pop    %ebx
 8049ed7:	c3                   	ret    
