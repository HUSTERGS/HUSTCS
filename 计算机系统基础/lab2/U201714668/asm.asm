
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
 80488eb:	68 b0 9e 04 08       	push   $0x8049eb0
 80488f0:	68 50 9e 04 08       	push   $0x8049e50
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
 8048a04:	68 e8 9e 04 08       	push   $0x8049ee8
 8048a09:	ff 73 04             	pushl  0x4(%ebx)
 8048a0c:	e8 0f fe ff ff       	call   8048820 <fopen@plt>
 8048a11:	a3 d0 c3 04 08       	mov    %eax,0x804c3d0
 8048a16:	83 c4 10             	add    $0x10,%esp
 8048a19:	85 c0                	test   %eax,%eax
 8048a1b:	0f 84 e7 00 00 00    	je     8048b08 <main+0x12d>
 8048a21:	e8 4d 06 00 00       	call   8049073 <initialize_bomb>
 8048a26:	83 ec 0c             	sub    $0xc,%esp
 8048a29:	68 6c 9f 04 08       	push   $0x8049f6c
 8048a2e:	e8 8d fd ff ff       	call   80487c0 <puts@plt>
 8048a33:	c7 04 24 a8 9f 04 08 	movl   $0x8049fa8,(%esp)
 8048a3a:	e8 81 fd ff ff       	call   80487c0 <puts@plt>
 8048a3f:	e8 1f 07 00 00       	call   8049163 <read_line>
 8048a44:	89 04 24             	mov    %eax,(%esp)
 8048a47:	e8 f6 00 00 00       	call   8048b42 <phase_1>
 8048a4c:	e8 11 08 00 00       	call   8049262 <phase_defused>
 8048a51:	c7 04 24 d4 9f 04 08 	movl   $0x8049fd4,(%esp)
 8048a58:	e8 63 fd ff ff       	call   80487c0 <puts@plt>
 8048a5d:	e8 01 07 00 00       	call   8049163 <read_line>
 8048a62:	89 04 24             	mov    %eax,(%esp)
 8048a65:	e8 fb 00 00 00       	call   8048b65 <phase_2>
 8048a6a:	e8 f3 07 00 00       	call   8049262 <phase_defused>
 8048a6f:	c7 04 24 21 9f 04 08 	movl   $0x8049f21,(%esp)
 8048a76:	e8 45 fd ff ff       	call   80487c0 <puts@plt>
 8048a7b:	e8 e3 06 00 00       	call   8049163 <read_line>
 8048a80:	89 04 24             	mov    %eax,(%esp)
 8048a83:	e8 44 01 00 00       	call   8048bcc <phase_3>
 8048a88:	e8 d5 07 00 00       	call   8049262 <phase_defused>
 8048a8d:	c7 04 24 3f 9f 04 08 	movl   $0x8049f3f,(%esp)
 8048a94:	e8 27 fd ff ff       	call   80487c0 <puts@plt>
 8048a99:	e8 c5 06 00 00       	call   8049163 <read_line>
 8048a9e:	89 04 24             	mov    %eax,(%esp)
 8048aa1:	e8 30 02 00 00       	call   8048cd6 <phase_4>
 8048aa6:	e8 b7 07 00 00       	call   8049262 <phase_defused>
 8048aab:	c7 04 24 00 a0 04 08 	movl   $0x804a000,(%esp)
 8048ab2:	e8 09 fd ff ff       	call   80487c0 <puts@plt>
 8048ab7:	e8 a7 06 00 00       	call   8049163 <read_line>
 8048abc:	89 04 24             	mov    %eax,(%esp)
 8048abf:	e8 8b 02 00 00       	call   8048d4f <phase_5>
 8048ac4:	e8 99 07 00 00       	call   8049262 <phase_defused>
 8048ac9:	c7 04 24 4e 9f 04 08 	movl   $0x8049f4e,(%esp)
 8048ad0:	e8 eb fc ff ff       	call   80487c0 <puts@plt>
 8048ad5:	e8 89 06 00 00       	call   8049163 <read_line>
 8048ada:	89 04 24             	mov    %eax,(%esp)
 8048add:	e8 fc 02 00 00       	call   8048dde <phase_6>
 8048ae2:	e8 7b 07 00 00       	call   8049262 <phase_defused>
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
 8048b0d:	68 ea 9e 04 08       	push   $0x8049eea
 8048b12:	6a 01                	push   $0x1
 8048b14:	e8 27 fd ff ff       	call   8048840 <__printf_chk@plt>
 8048b19:	c7 04 24 08 00 00 00 	movl   $0x8,(%esp)
 8048b20:	e8 bb fc ff ff       	call   80487e0 <exit@plt>
 8048b25:	83 ec 04             	sub    $0x4,%esp
 8048b28:	ff 33                	pushl  (%ebx)
 8048b2a:	68 07 9f 04 08       	push   $0x8049f07
 8048b2f:	6a 01                	push   $0x1
 8048b31:	e8 0a fd ff ff       	call   8048840 <__printf_chk@plt>
 8048b36:	c7 04 24 08 00 00 00 	movl   $0x8,(%esp)
 8048b3d:	e8 9e fc ff ff       	call   80487e0 <exit@plt>

08048b42 <phase_1>:
 8048b42:	83 ec 14             	sub    $0x14,%esp
 8048b45:	68 24 a0 04 08       	push   $0x804a024
 8048b4a:	ff 74 24 1c          	pushl  0x1c(%esp)
 8048b4e:	e8 bb 04 00 00       	call   804900e <strings_not_equal>
 8048b53:	83 c4 10             	add    $0x10,%esp
 8048b56:	85 c0                	test   %eax,%eax
 8048b58:	75 04                	jne    8048b5e <phase_1+0x1c>
 8048b5a:	83 c4 0c             	add    $0xc,%esp
 8048b5d:	c3                   	ret    
 8048b5e:	e8 a0 05 00 00       	call   8049103 <explode_bomb>
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
 8048b7f:	e8 a4 05 00 00       	call   8049128 <read_six_numbers>
 8048b84:	83 c4 10             	add    $0x10,%esp
 8048b87:	83 7c 24 04 01       	cmpl   $0x1,0x4(%esp)
 8048b8c:	74 05                	je     8048b93 <phase_2+0x2e>
 8048b8e:	e8 70 05 00 00       	call   8049103 <explode_bomb>
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
 8048bad:	e8 51 05 00 00       	call   8049103 <explode_bomb>
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
 8048be5:	68 ef a1 04 08       	push   $0x804a1ef
 8048bea:	ff 74 24 2c          	pushl  0x2c(%esp)
 8048bee:	e8 1d fc ff ff       	call   8048810 <__isoc99_sscanf@plt>
 8048bf3:	83 c4 10             	add    $0x10,%esp
 8048bf6:	83 f8 01             	cmp    $0x1,%eax
 8048bf9:	7e 12                	jle    8048c0d <phase_3+0x41>
 8048bfb:	83 7c 24 04 07       	cmpl   $0x7,0x4(%esp)
 8048c00:	77 43                	ja     8048c45 <phase_3+0x79>
 8048c02:	8b 44 24 04          	mov    0x4(%esp),%eax
 8048c06:	ff 24 85 80 a0 04 08 	jmp    *0x804a080(,%eax,4)
 8048c0d:	e8 f1 04 00 00       	call   8049103 <explode_bomb>
 8048c12:	eb e7                	jmp    8048bfb <phase_3+0x2f>
 8048c14:	b8 2e 03 00 00       	mov    $0x32e,%eax
 8048c19:	eb 3b                	jmp    8048c56 <phase_3+0x8a>
 8048c1b:	b8 20 03 00 00       	mov    $0x320,%eax
 8048c20:	eb 34                	jmp    8048c56 <phase_3+0x8a>
 8048c22:	b8 6c 01 00 00       	mov    $0x16c,%eax
 8048c27:	eb 2d                	jmp    8048c56 <phase_3+0x8a>
 8048c29:	b8 d9 03 00 00       	mov    $0x3d9,%eax
 8048c2e:	eb 26                	jmp    8048c56 <phase_3+0x8a>
 8048c30:	b8 a5 02 00 00       	mov    $0x2a5,%eax
 8048c35:	eb 1f                	jmp    8048c56 <phase_3+0x8a>
 8048c37:	b8 38 02 00 00       	mov    $0x238,%eax
 8048c3c:	eb 18                	jmp    8048c56 <phase_3+0x8a>
 8048c3e:	b8 f8 01 00 00       	mov    $0x1f8,%eax
 8048c43:	eb 11                	jmp    8048c56 <phase_3+0x8a>
 8048c45:	e8 b9 04 00 00       	call   8049103 <explode_bomb>
 8048c4a:	b8 00 00 00 00       	mov    $0x0,%eax
 8048c4f:	eb 05                	jmp    8048c56 <phase_3+0x8a>
 8048c51:	b8 34 01 00 00       	mov    $0x134,%eax
 8048c56:	3b 44 24 08          	cmp    0x8(%esp),%eax
 8048c5a:	74 05                	je     8048c61 <phase_3+0x95>
 8048c5c:	e8 a2 04 00 00       	call   8049103 <explode_bomb>
 8048c61:	8b 44 24 0c          	mov    0xc(%esp),%eax
 8048c65:	65 33 05 14 00 00 00 	xor    %gs:0x14,%eax
 8048c6c:	75 04                	jne    8048c72 <phase_3+0xa6>
 8048c6e:	83 c4 1c             	add    $0x1c,%esp
 8048c71:	c3                   	ret    
 8048c72:	e8 19 fb ff ff       	call   8048790 <__stack_chk_fail@plt>

08048c77 <func4>:
 8048c77:	56                   	push   %esi
 8048c78:	53                   	push   %ebx
 8048c79:	83 ec 04             	sub    $0x4,%esp
 8048c7c:	8b 4c 24 10          	mov    0x10(%esp),%ecx
 8048c80:	8b 44 24 14          	mov    0x14(%esp),%eax
 8048c84:	8b 5c 24 18          	mov    0x18(%esp),%ebx
 8048c88:	89 de                	mov    %ebx,%esi
 8048c8a:	29 c6                	sub    %eax,%esi
 8048c8c:	89 f2                	mov    %esi,%edx
 8048c8e:	c1 ea 1f             	shr    $0x1f,%edx
 8048c91:	01 f2                	add    %esi,%edx
 8048c93:	d1 fa                	sar    %edx
 8048c95:	01 c2                	add    %eax,%edx
 8048c97:	39 ca                	cmp    %ecx,%edx
 8048c99:	7f 0f                	jg     8048caa <func4+0x33>
 8048c9b:	b8 00 00 00 00       	mov    $0x0,%eax
 8048ca0:	39 ca                	cmp    %ecx,%edx
 8048ca2:	7c 1b                	jl     8048cbf <func4+0x48>
 8048ca4:	83 c4 04             	add    $0x4,%esp
 8048ca7:	5b                   	pop    %ebx
 8048ca8:	5e                   	pop    %esi
 8048ca9:	c3                   	ret    
 8048caa:	83 ec 04             	sub    $0x4,%esp
 8048cad:	83 ea 01             	sub    $0x1,%edx
 8048cb0:	52                   	push   %edx
 8048cb1:	50                   	push   %eax
 8048cb2:	51                   	push   %ecx
 8048cb3:	e8 bf ff ff ff       	call   8048c77 <func4>
 8048cb8:	83 c4 10             	add    $0x10,%esp
 8048cbb:	01 c0                	add    %eax,%eax
 8048cbd:	eb e5                	jmp    8048ca4 <func4+0x2d>
 8048cbf:	83 ec 04             	sub    $0x4,%esp
 8048cc2:	53                   	push   %ebx
 8048cc3:	83 c2 01             	add    $0x1,%edx
 8048cc6:	52                   	push   %edx
 8048cc7:	51                   	push   %ecx
 8048cc8:	e8 aa ff ff ff       	call   8048c77 <func4>
 8048ccd:	83 c4 10             	add    $0x10,%esp
 8048cd0:	8d 44 00 01          	lea    0x1(%eax,%eax,1),%eax
 8048cd4:	eb ce                	jmp    8048ca4 <func4+0x2d>

08048cd6 <phase_4>:
 8048cd6:	83 ec 1c             	sub    $0x1c,%esp
 8048cd9:	65 a1 14 00 00 00    	mov    %gs:0x14,%eax
 8048cdf:	89 44 24 0c          	mov    %eax,0xc(%esp)
 8048ce3:	31 c0                	xor    %eax,%eax
 8048ce5:	8d 44 24 08          	lea    0x8(%esp),%eax
 8048ce9:	50                   	push   %eax
 8048cea:	8d 44 24 08          	lea    0x8(%esp),%eax
 8048cee:	50                   	push   %eax
 8048cef:	68 ef a1 04 08       	push   $0x804a1ef
 8048cf4:	ff 74 24 2c          	pushl  0x2c(%esp)
 8048cf8:	e8 13 fb ff ff       	call   8048810 <__isoc99_sscanf@plt>
 8048cfd:	83 c4 10             	add    $0x10,%esp
 8048d00:	83 f8 02             	cmp    $0x2,%eax
 8048d03:	74 33                	je     8048d38 <phase_4+0x62>
 8048d05:	e8 f9 03 00 00       	call   8049103 <explode_bomb>
 8048d0a:	83 ec 04             	sub    $0x4,%esp
 8048d0d:	6a 0e                	push   $0xe
 8048d0f:	6a 00                	push   $0x0
 8048d11:	ff 74 24 10          	pushl  0x10(%esp)
 8048d15:	e8 5d ff ff ff       	call   8048c77 <func4>
 8048d1a:	83 c4 10             	add    $0x10,%esp
 8048d1d:	83 f8 04             	cmp    $0x4,%eax
 8048d20:	74 1f                	je     8048d41 <phase_4+0x6b>
 8048d22:	e8 dc 03 00 00       	call   8049103 <explode_bomb>
 8048d27:	8b 44 24 0c          	mov    0xc(%esp),%eax
 8048d2b:	65 33 05 14 00 00 00 	xor    %gs:0x14,%eax
 8048d32:	75 16                	jne    8048d4a <phase_4+0x74>
 8048d34:	83 c4 1c             	add    $0x1c,%esp
 8048d37:	c3                   	ret    
 8048d38:	83 7c 24 04 0e       	cmpl   $0xe,0x4(%esp)
 8048d3d:	76 cb                	jbe    8048d0a <phase_4+0x34>
 8048d3f:	eb c4                	jmp    8048d05 <phase_4+0x2f>
 8048d41:	83 7c 24 08 04       	cmpl   $0x4,0x8(%esp)
 8048d46:	75 da                	jne    8048d22 <phase_4+0x4c>
 8048d48:	eb dd                	jmp    8048d27 <phase_4+0x51>
 8048d4a:	e8 41 fa ff ff       	call   8048790 <__stack_chk_fail@plt>

08048d4f <phase_5>:
 8048d4f:	83 ec 1c             	sub    $0x1c,%esp
 8048d52:	65 a1 14 00 00 00    	mov    %gs:0x14,%eax
 8048d58:	89 44 24 0c          	mov    %eax,0xc(%esp)
 8048d5c:	31 c0                	xor    %eax,%eax
 8048d5e:	8d 44 24 08          	lea    0x8(%esp),%eax
 8048d62:	50                   	push   %eax
 8048d63:	8d 44 24 08          	lea    0x8(%esp),%eax
 8048d67:	50                   	push   %eax
 8048d68:	68 ef a1 04 08       	push   $0x804a1ef
 8048d6d:	ff 74 24 2c          	pushl  0x2c(%esp)
 8048d71:	e8 9a fa ff ff       	call   8048810 <__isoc99_sscanf@plt>
 8048d76:	83 c4 10             	add    $0x10,%esp
 8048d79:	83 f8 01             	cmp    $0x1,%eax
 8048d7c:	7e 54                	jle    8048dd2 <phase_5+0x83>
 8048d7e:	8b 44 24 04          	mov    0x4(%esp),%eax
 8048d82:	83 e0 0f             	and    $0xf,%eax
 8048d85:	89 44 24 04          	mov    %eax,0x4(%esp)
 8048d89:	83 f8 0f             	cmp    $0xf,%eax
 8048d8c:	74 2e                	je     8048dbc <phase_5+0x6d>
 8048d8e:	b9 00 00 00 00       	mov    $0x0,%ecx
 8048d93:	ba 00 00 00 00       	mov    $0x0,%edx
 8048d98:	83 c2 01             	add    $0x1,%edx
 8048d9b:	8b 04 85 a0 a0 04 08 	mov    0x804a0a0(,%eax,4),%eax
 8048da2:	01 c1                	add    %eax,%ecx
 8048da4:	83 f8 0f             	cmp    $0xf,%eax
 8048da7:	75 ef                	jne    8048d98 <phase_5+0x49>
 8048da9:	c7 44 24 04 0f 00 00 	movl   $0xf,0x4(%esp)
 8048db0:	00 
 8048db1:	83 fa 0f             	cmp    $0xf,%edx
 8048db4:	75 06                	jne    8048dbc <phase_5+0x6d>
 8048db6:	3b 4c 24 08          	cmp    0x8(%esp),%ecx
 8048dba:	74 05                	je     8048dc1 <phase_5+0x72>
 8048dbc:	e8 42 03 00 00       	call   8049103 <explode_bomb>
 8048dc1:	8b 44 24 0c          	mov    0xc(%esp),%eax
 8048dc5:	65 33 05 14 00 00 00 	xor    %gs:0x14,%eax
 8048dcc:	75 0b                	jne    8048dd9 <phase_5+0x8a>
 8048dce:	83 c4 1c             	add    $0x1c,%esp
 8048dd1:	c3                   	ret    
 8048dd2:	e8 2c 03 00 00       	call   8049103 <explode_bomb>
 8048dd7:	eb a5                	jmp    8048d7e <phase_5+0x2f>
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
 8048df8:	e8 2b 03 00 00       	call   8049128 <read_six_numbers>
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
 8048e2f:	e8 cf 02 00 00       	call   8049103 <explode_bomb>
 8048e34:	eb d1                	jmp    8048e07 <phase_6+0x29>
 8048e36:	e8 c8 02 00 00       	call   8049103 <explode_bomb>
 8048e3b:	eb de                	jmp    8048e1b <phase_6+0x3d>
 8048e3d:	bb 00 00 00 00       	mov    $0x0,%ebx
 8048e42:	89 de                	mov    %ebx,%esi
 8048e44:	8b 4c 9c 0c          	mov    0xc(%esp,%ebx,4),%ecx
 8048e48:	b8 01 00 00 00       	mov    $0x1,%eax
 8048e4d:	ba 3c c1 04 08       	mov    $0x804c13c,%edx
 8048e52:	83 f9 01             	cmp    $0x1,%ecx
 8048e55:	7e 0a                	jle    8048e61 <phase_6+0x83>
 8048e57:	8b 52 08             	mov    0x8(%edx),%edx
 8048e5a:	83 c0 01             	add    $0x1,%eax
 8048e5d:	39 c8                	cmp    %ecx,%eax
 8048e5f:	75 f6                	jne    8048e57 <phase_6+0x79>
 8048e61:	89 54 b4 24          	mov    %edx,0x24(%esp,%esi,4)
 8048e65:	83 c3 01             	add    $0x1,%ebx
 8048e68:	83 fb 06             	cmp    $0x6,%ebx
 8048e6b:	75 d5                	jne    8048e42 <phase_6+0x64>
 8048e6d:	8b 5c 24 24          	mov    0x24(%esp),%ebx
 8048e71:	89 d9                	mov    %ebx,%ecx
 8048e73:	b8 01 00 00 00       	mov    $0x1,%eax
 8048e78:	8b 54 84 24          	mov    0x24(%esp,%eax,4),%edx
 8048e7c:	89 51 08             	mov    %edx,0x8(%ecx)
 8048e7f:	83 c0 01             	add    $0x1,%eax
 8048e82:	89 d1                	mov    %edx,%ecx
 8048e84:	83 f8 06             	cmp    $0x6,%eax
 8048e87:	75 ef                	jne    8048e78 <phase_6+0x9a>
 8048e89:	c7 42 08 00 00 00 00 	movl   $0x0,0x8(%edx)
 8048e90:	be 05 00 00 00       	mov    $0x5,%esi
 8048e95:	eb 08                	jmp    8048e9f <phase_6+0xc1>
 8048e97:	8b 5b 08             	mov    0x8(%ebx),%ebx
 8048e9a:	83 ee 01             	sub    $0x1,%esi
 8048e9d:	74 10                	je     8048eaf <phase_6+0xd1>
 8048e9f:	8b 43 08             	mov    0x8(%ebx),%eax
 8048ea2:	8b 00                	mov    (%eax),%eax
 8048ea4:	39 03                	cmp    %eax,(%ebx)
 8048ea6:	7e ef                	jle    8048e97 <phase_6+0xb9>
 8048ea8:	e8 56 02 00 00       	call   8049103 <explode_bomb>
 8048ead:	eb e8                	jmp    8048e97 <phase_6+0xb9>
 8048eaf:	8b 44 24 3c          	mov    0x3c(%esp),%eax
 8048eb3:	65 33 05 14 00 00 00 	xor    %gs:0x14,%eax
 8048eba:	75 06                	jne    8048ec2 <phase_6+0xe4>
 8048ebc:	83 c4 44             	add    $0x44,%esp
 8048ebf:	5b                   	pop    %ebx
 8048ec0:	5e                   	pop    %esi
 8048ec1:	c3                   	ret    
 8048ec2:	e8 c9 f8 ff ff       	call   8048790 <__stack_chk_fail@plt>

08048ec7 <fun7>:
 8048ec7:	53                   	push   %ebx
 8048ec8:	83 ec 08             	sub    $0x8,%esp
 8048ecb:	8b 54 24 10          	mov    0x10(%esp),%edx
 8048ecf:	8b 4c 24 14          	mov    0x14(%esp),%ecx
 8048ed3:	85 d2                	test   %edx,%edx
 8048ed5:	74 3a                	je     8048f11 <fun7+0x4a>
 8048ed7:	8b 1a                	mov    (%edx),%ebx
 8048ed9:	39 cb                	cmp    %ecx,%ebx
 8048edb:	7f 21                	jg     8048efe <fun7+0x37>
 8048edd:	b8 00 00 00 00       	mov    $0x0,%eax
 8048ee2:	39 cb                	cmp    %ecx,%ebx
 8048ee4:	74 13                	je     8048ef9 <fun7+0x32>
 8048ee6:	83 ec 08             	sub    $0x8,%esp
 8048ee9:	51                   	push   %ecx
 8048eea:	ff 72 08             	pushl  0x8(%edx)
 8048eed:	e8 d5 ff ff ff       	call   8048ec7 <fun7>
 8048ef2:	83 c4 10             	add    $0x10,%esp
 8048ef5:	8d 44 00 01          	lea    0x1(%eax,%eax,1),%eax
 8048ef9:	83 c4 08             	add    $0x8,%esp
 8048efc:	5b                   	pop    %ebx
 8048efd:	c3                   	ret    
 8048efe:	83 ec 08             	sub    $0x8,%esp
 8048f01:	51                   	push   %ecx
 8048f02:	ff 72 04             	pushl  0x4(%edx)
 8048f05:	e8 bd ff ff ff       	call   8048ec7 <fun7>
 8048f0a:	83 c4 10             	add    $0x10,%esp
 8048f0d:	01 c0                	add    %eax,%eax
 8048f0f:	eb e8                	jmp    8048ef9 <fun7+0x32>
 8048f11:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8048f16:	eb e1                	jmp    8048ef9 <fun7+0x32>

08048f18 <secret_phase>:
 8048f18:	53                   	push   %ebx
 8048f19:	83 ec 08             	sub    $0x8,%esp
 8048f1c:	e8 42 02 00 00       	call   8049163 <read_line>
 8048f21:	83 ec 04             	sub    $0x4,%esp
 8048f24:	6a 0a                	push   $0xa
 8048f26:	6a 00                	push   $0x0
 8048f28:	50                   	push   %eax
 8048f29:	e8 52 f9 ff ff       	call   8048880 <strtol@plt>
 8048f2e:	89 c3                	mov    %eax,%ebx
 8048f30:	8d 40 ff             	lea    -0x1(%eax),%eax
 8048f33:	83 c4 10             	add    $0x10,%esp
 8048f36:	3d e8 03 00 00       	cmp    $0x3e8,%eax
 8048f3b:	77 32                	ja     8048f6f <secret_phase+0x57>
 8048f3d:	83 ec 08             	sub    $0x8,%esp
 8048f40:	53                   	push   %ebx
 8048f41:	68 88 c0 04 08       	push   $0x804c088
 8048f46:	e8 7c ff ff ff       	call   8048ec7 <fun7>
 8048f4b:	83 c4 10             	add    $0x10,%esp
 8048f4e:	83 f8 06             	cmp    $0x6,%eax
 8048f51:	74 05                	je     8048f58 <secret_phase+0x40>
 8048f53:	e8 ab 01 00 00       	call   8049103 <explode_bomb>
 8048f58:	83 ec 0c             	sub    $0xc,%esp
 8048f5b:	68 58 a0 04 08       	push   $0x804a058
 8048f60:	e8 5b f8 ff ff       	call   80487c0 <puts@plt>
 8048f65:	e8 f8 02 00 00       	call   8049262 <phase_defused>
 8048f6a:	83 c4 18             	add    $0x18,%esp
 8048f6d:	5b                   	pop    %ebx
 8048f6e:	c3                   	ret    
 8048f6f:	e8 8f 01 00 00       	call   8049103 <explode_bomb>
 8048f74:	eb c7                	jmp    8048f3d <secret_phase+0x25>

08048f76 <sig_handler>:
 8048f76:	83 ec 18             	sub    $0x18,%esp
 8048f79:	68 e0 a0 04 08       	push   $0x804a0e0
 8048f7e:	e8 3d f8 ff ff       	call   80487c0 <puts@plt>
 8048f83:	c7 04 24 03 00 00 00 	movl   $0x3,(%esp)
 8048f8a:	e8 e1 f7 ff ff       	call   8048770 <sleep@plt>
 8048f8f:	83 c4 08             	add    $0x8,%esp
 8048f92:	68 a2 a1 04 08       	push   $0x804a1a2
 8048f97:	6a 01                	push   $0x1
 8048f99:	e8 a2 f8 ff ff       	call   8048840 <__printf_chk@plt>
 8048f9e:	83 c4 04             	add    $0x4,%esp
 8048fa1:	ff 35 c4 c3 04 08    	pushl  0x804c3c4
 8048fa7:	e8 94 f7 ff ff       	call   8048740 <fflush@plt>
 8048fac:	c7 04 24 01 00 00 00 	movl   $0x1,(%esp)
 8048fb3:	e8 b8 f7 ff ff       	call   8048770 <sleep@plt>
 8048fb8:	c7 04 24 aa a1 04 08 	movl   $0x804a1aa,(%esp)
 8048fbf:	e8 fc f7 ff ff       	call   80487c0 <puts@plt>
 8048fc4:	c7 04 24 10 00 00 00 	movl   $0x10,(%esp)
 8048fcb:	e8 10 f8 ff ff       	call   80487e0 <exit@plt>

08048fd0 <invalid_phase>:
 8048fd0:	83 ec 10             	sub    $0x10,%esp
 8048fd3:	ff 74 24 14          	pushl  0x14(%esp)
 8048fd7:	68 b2 a1 04 08       	push   $0x804a1b2
 8048fdc:	6a 01                	push   $0x1
 8048fde:	e8 5d f8 ff ff       	call   8048840 <__printf_chk@plt>
 8048fe3:	c7 04 24 08 00 00 00 	movl   $0x8,(%esp)
 8048fea:	e8 f1 f7 ff ff       	call   80487e0 <exit@plt>

08048fef <string_length>:
 8048fef:	8b 54 24 04          	mov    0x4(%esp),%edx
 8048ff3:	80 3a 00             	cmpb   $0x0,(%edx)
 8048ff6:	74 10                	je     8049008 <string_length+0x19>
 8048ff8:	b8 00 00 00 00       	mov    $0x0,%eax
 8048ffd:	83 c0 01             	add    $0x1,%eax
 8049000:	80 3c 02 00          	cmpb   $0x0,(%edx,%eax,1)
 8049004:	75 f7                	jne    8048ffd <string_length+0xe>
 8049006:	f3 c3                	repz ret 
 8049008:	b8 00 00 00 00       	mov    $0x0,%eax
 804900d:	c3                   	ret    

0804900e <strings_not_equal>:
 804900e:	57                   	push   %edi
 804900f:	56                   	push   %esi
 8049010:	53                   	push   %ebx
 8049011:	8b 5c 24 10          	mov    0x10(%esp),%ebx
 8049015:	8b 74 24 14          	mov    0x14(%esp),%esi
 8049019:	53                   	push   %ebx
 804901a:	e8 d0 ff ff ff       	call   8048fef <string_length>
 804901f:	89 c7                	mov    %eax,%edi
 8049021:	89 34 24             	mov    %esi,(%esp)
 8049024:	e8 c6 ff ff ff       	call   8048fef <string_length>
 8049029:	83 c4 04             	add    $0x4,%esp
 804902c:	ba 01 00 00 00       	mov    $0x1,%edx
 8049031:	39 c7                	cmp    %eax,%edi
 8049033:	74 06                	je     804903b <strings_not_equal+0x2d>
 8049035:	89 d0                	mov    %edx,%eax
 8049037:	5b                   	pop    %ebx
 8049038:	5e                   	pop    %esi
 8049039:	5f                   	pop    %edi
 804903a:	c3                   	ret    
 804903b:	0f b6 03             	movzbl (%ebx),%eax
 804903e:	84 c0                	test   %al,%al
 8049040:	74 23                	je     8049065 <strings_not_equal+0x57>
 8049042:	3a 06                	cmp    (%esi),%al
 8049044:	75 26                	jne    804906c <strings_not_equal+0x5e>
 8049046:	83 c3 01             	add    $0x1,%ebx
 8049049:	83 c6 01             	add    $0x1,%esi
 804904c:	0f b6 03             	movzbl (%ebx),%eax
 804904f:	84 c0                	test   %al,%al
 8049051:	74 0b                	je     804905e <strings_not_equal+0x50>
 8049053:	3a 06                	cmp    (%esi),%al
 8049055:	74 ef                	je     8049046 <strings_not_equal+0x38>
 8049057:	ba 01 00 00 00       	mov    $0x1,%edx
 804905c:	eb d7                	jmp    8049035 <strings_not_equal+0x27>
 804905e:	ba 00 00 00 00       	mov    $0x0,%edx
 8049063:	eb d0                	jmp    8049035 <strings_not_equal+0x27>
 8049065:	ba 00 00 00 00       	mov    $0x0,%edx
 804906a:	eb c9                	jmp    8049035 <strings_not_equal+0x27>
 804906c:	ba 01 00 00 00       	mov    $0x1,%edx
 8049071:	eb c2                	jmp    8049035 <strings_not_equal+0x27>

08049073 <initialize_bomb>:
 8049073:	83 ec 14             	sub    $0x14,%esp
 8049076:	68 76 8f 04 08       	push   $0x8048f76
 804907b:	6a 02                	push   $0x2
 804907d:	e8 de f6 ff ff       	call   8048760 <signal@plt>
 8049082:	83 c4 1c             	add    $0x1c,%esp
 8049085:	c3                   	ret    

08049086 <initialize_bomb_solve>:
 8049086:	f3 c3                	repz ret 

08049088 <blank_line>:
 8049088:	56                   	push   %esi
 8049089:	53                   	push   %ebx
 804908a:	83 ec 04             	sub    $0x4,%esp
 804908d:	8b 74 24 10          	mov    0x10(%esp),%esi
 8049091:	0f b6 1e             	movzbl (%esi),%ebx
 8049094:	84 db                	test   %bl,%bl
 8049096:	74 1b                	je     80490b3 <blank_line+0x2b>
 8049098:	e8 13 f8 ff ff       	call   80488b0 <__ctype_b_loc@plt>
 804909d:	83 c6 01             	add    $0x1,%esi
 80490a0:	0f be db             	movsbl %bl,%ebx
 80490a3:	8b 00                	mov    (%eax),%eax
 80490a5:	f6 44 58 01 20       	testb  $0x20,0x1(%eax,%ebx,2)
 80490aa:	75 e5                	jne    8049091 <blank_line+0x9>
 80490ac:	b8 00 00 00 00       	mov    $0x0,%eax
 80490b1:	eb 05                	jmp    80490b8 <blank_line+0x30>
 80490b3:	b8 01 00 00 00       	mov    $0x1,%eax
 80490b8:	83 c4 04             	add    $0x4,%esp
 80490bb:	5b                   	pop    %ebx
 80490bc:	5e                   	pop    %esi
 80490bd:	c3                   	ret    

080490be <skip>:
 80490be:	53                   	push   %ebx
 80490bf:	83 ec 08             	sub    $0x8,%esp
 80490c2:	83 ec 04             	sub    $0x4,%esp
 80490c5:	ff 35 d0 c3 04 08    	pushl  0x804c3d0
 80490cb:	6a 50                	push   $0x50
 80490cd:	a1 cc c3 04 08       	mov    0x804c3cc,%eax
 80490d2:	8d 04 80             	lea    (%eax,%eax,4),%eax
 80490d5:	c1 e0 04             	shl    $0x4,%eax
 80490d8:	05 e0 c3 04 08       	add    $0x804c3e0,%eax
 80490dd:	50                   	push   %eax
 80490de:	e8 6d f6 ff ff       	call   8048750 <fgets@plt>
 80490e3:	89 c3                	mov    %eax,%ebx
 80490e5:	83 c4 10             	add    $0x10,%esp
 80490e8:	85 c0                	test   %eax,%eax
 80490ea:	74 10                	je     80490fc <skip+0x3e>
 80490ec:	83 ec 0c             	sub    $0xc,%esp
 80490ef:	50                   	push   %eax
 80490f0:	e8 93 ff ff ff       	call   8049088 <blank_line>
 80490f5:	83 c4 10             	add    $0x10,%esp
 80490f8:	85 c0                	test   %eax,%eax
 80490fa:	75 c6                	jne    80490c2 <skip+0x4>
 80490fc:	89 d8                	mov    %ebx,%eax
 80490fe:	83 c4 08             	add    $0x8,%esp
 8049101:	5b                   	pop    %ebx
 8049102:	c3                   	ret    

08049103 <explode_bomb>:
 8049103:	83 ec 18             	sub    $0x18,%esp
 8049106:	68 c3 a1 04 08       	push   $0x804a1c3
 804910b:	e8 b0 f6 ff ff       	call   80487c0 <puts@plt>
 8049110:	c7 04 24 cc a1 04 08 	movl   $0x804a1cc,(%esp)
 8049117:	e8 a4 f6 ff ff       	call   80487c0 <puts@plt>
 804911c:	c7 04 24 08 00 00 00 	movl   $0x8,(%esp)
 8049123:	e8 b8 f6 ff ff       	call   80487e0 <exit@plt>

08049128 <read_six_numbers>:
 8049128:	83 ec 0c             	sub    $0xc,%esp
 804912b:	8b 44 24 14          	mov    0x14(%esp),%eax
 804912f:	8d 50 14             	lea    0x14(%eax),%edx
 8049132:	52                   	push   %edx
 8049133:	8d 50 10             	lea    0x10(%eax),%edx
 8049136:	52                   	push   %edx
 8049137:	8d 50 0c             	lea    0xc(%eax),%edx
 804913a:	52                   	push   %edx
 804913b:	8d 50 08             	lea    0x8(%eax),%edx
 804913e:	52                   	push   %edx
 804913f:	8d 50 04             	lea    0x4(%eax),%edx
 8049142:	52                   	push   %edx
 8049143:	50                   	push   %eax
 8049144:	68 e3 a1 04 08       	push   $0x804a1e3
 8049149:	ff 74 24 2c          	pushl  0x2c(%esp)
 804914d:	e8 be f6 ff ff       	call   8048810 <__isoc99_sscanf@plt>
 8049152:	83 c4 20             	add    $0x20,%esp
 8049155:	83 f8 05             	cmp    $0x5,%eax
 8049158:	7e 04                	jle    804915e <read_six_numbers+0x36>
 804915a:	83 c4 0c             	add    $0xc,%esp
 804915d:	c3                   	ret    
 804915e:	e8 a0 ff ff ff       	call   8049103 <explode_bomb>

08049163 <read_line>:
 8049163:	57                   	push   %edi
 8049164:	56                   	push   %esi
 8049165:	53                   	push   %ebx
 8049166:	e8 53 ff ff ff       	call   80490be <skip>
 804916b:	85 c0                	test   %eax,%eax
 804916d:	74 4b                	je     80491ba <read_line+0x57>
 804916f:	8b 15 cc c3 04 08    	mov    0x804c3cc,%edx
 8049175:	8d 1c 92             	lea    (%edx,%edx,4),%ebx
 8049178:	c1 e3 04             	shl    $0x4,%ebx
 804917b:	81 c3 e0 c3 04 08    	add    $0x804c3e0,%ebx
 8049181:	b8 00 00 00 00       	mov    $0x0,%eax
 8049186:	b9 ff ff ff ff       	mov    $0xffffffff,%ecx
 804918b:	89 df                	mov    %ebx,%edi
 804918d:	f2 ae                	repnz scas %es:(%edi),%al
 804918f:	f7 d1                	not    %ecx
 8049191:	83 e9 01             	sub    $0x1,%ecx
 8049194:	83 f9 4e             	cmp    $0x4e,%ecx
 8049197:	0f 8f 8d 00 00 00    	jg     804922a <read_line+0xc7>
 804919d:	8d 04 92             	lea    (%edx,%edx,4),%eax
 80491a0:	c1 e0 04             	shl    $0x4,%eax
 80491a3:	c6 84 01 df c3 04 08 	movb   $0x0,0x804c3df(%ecx,%eax,1)
 80491aa:	00 
 80491ab:	83 c2 01             	add    $0x1,%edx
 80491ae:	89 15 cc c3 04 08    	mov    %edx,0x804c3cc
 80491b4:	89 d8                	mov    %ebx,%eax
 80491b6:	5b                   	pop    %ebx
 80491b7:	5e                   	pop    %esi
 80491b8:	5f                   	pop    %edi
 80491b9:	c3                   	ret    
 80491ba:	a1 c0 c3 04 08       	mov    0x804c3c0,%eax
 80491bf:	39 05 d0 c3 04 08    	cmp    %eax,0x804c3d0
 80491c5:	74 40                	je     8049207 <read_line+0xa4>
 80491c7:	83 ec 0c             	sub    $0xc,%esp
 80491ca:	68 13 a2 04 08       	push   $0x804a213
 80491cf:	e8 dc f5 ff ff       	call   80487b0 <getenv@plt>
 80491d4:	83 c4 10             	add    $0x10,%esp
 80491d7:	85 c0                	test   %eax,%eax
 80491d9:	75 45                	jne    8049220 <read_line+0xbd>
 80491db:	a1 c0 c3 04 08       	mov    0x804c3c0,%eax
 80491e0:	a3 d0 c3 04 08       	mov    %eax,0x804c3d0
 80491e5:	e8 d4 fe ff ff       	call   80490be <skip>
 80491ea:	85 c0                	test   %eax,%eax
 80491ec:	75 81                	jne    804916f <read_line+0xc>
 80491ee:	83 ec 0c             	sub    $0xc,%esp
 80491f1:	68 f5 a1 04 08       	push   $0x804a1f5
 80491f6:	e8 c5 f5 ff ff       	call   80487c0 <puts@plt>
 80491fb:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
 8049202:	e8 d9 f5 ff ff       	call   80487e0 <exit@plt>
 8049207:	83 ec 0c             	sub    $0xc,%esp
 804920a:	68 f5 a1 04 08       	push   $0x804a1f5
 804920f:	e8 ac f5 ff ff       	call   80487c0 <puts@plt>
 8049214:	c7 04 24 08 00 00 00 	movl   $0x8,(%esp)
 804921b:	e8 c0 f5 ff ff       	call   80487e0 <exit@plt>
 8049220:	83 ec 0c             	sub    $0xc,%esp
 8049223:	6a 00                	push   $0x0
 8049225:	e8 b6 f5 ff ff       	call   80487e0 <exit@plt>
 804922a:	83 ec 0c             	sub    $0xc,%esp
 804922d:	68 1e a2 04 08       	push   $0x804a21e
 8049232:	e8 89 f5 ff ff       	call   80487c0 <puts@plt>
 8049237:	a1 cc c3 04 08       	mov    0x804c3cc,%eax
 804923c:	8d 50 01             	lea    0x1(%eax),%edx
 804923f:	89 15 cc c3 04 08    	mov    %edx,0x804c3cc
 8049245:	6b c0 50             	imul   $0x50,%eax,%eax
 8049248:	05 e0 c3 04 08       	add    $0x804c3e0,%eax
 804924d:	ba 39 a2 04 08       	mov    $0x804a239,%edx
 8049252:	b9 04 00 00 00       	mov    $0x4,%ecx
 8049257:	89 c7                	mov    %eax,%edi
 8049259:	89 d6                	mov    %edx,%esi
 804925b:	f3 a5                	rep movsl %ds:(%esi),%es:(%edi)
 804925d:	e8 a1 fe ff ff       	call   8049103 <explode_bomb>

08049262 <phase_defused>:
 8049262:	83 ec 6c             	sub    $0x6c,%esp
 8049265:	65 a1 14 00 00 00    	mov    %gs:0x14,%eax
 804926b:	89 44 24 5c          	mov    %eax,0x5c(%esp)
 804926f:	31 c0                	xor    %eax,%eax
 8049271:	83 3d cc c3 04 08 06 	cmpl   $0x6,0x804c3cc
 8049278:	74 11                	je     804928b <phase_defused+0x29>
 804927a:	8b 44 24 5c          	mov    0x5c(%esp),%eax
 804927e:	65 33 05 14 00 00 00 	xor    %gs:0x14,%eax
 8049285:	75 7b                	jne    8049302 <phase_defused+0xa0>
 8049287:	83 c4 6c             	add    $0x6c,%esp
 804928a:	c3                   	ret    
 804928b:	83 ec 0c             	sub    $0xc,%esp
 804928e:	8d 44 24 18          	lea    0x18(%esp),%eax
 8049292:	50                   	push   %eax
 8049293:	8d 44 24 18          	lea    0x18(%esp),%eax
 8049297:	50                   	push   %eax
 8049298:	8d 44 24 18          	lea    0x18(%esp),%eax
 804929c:	50                   	push   %eax
 804929d:	68 49 a2 04 08       	push   $0x804a249
 80492a2:	68 d0 c4 04 08       	push   $0x804c4d0
 80492a7:	e8 64 f5 ff ff       	call   8048810 <__isoc99_sscanf@plt>
 80492ac:	83 c4 20             	add    $0x20,%esp
 80492af:	83 f8 03             	cmp    $0x3,%eax
 80492b2:	74 12                	je     80492c6 <phase_defused+0x64>
 80492b4:	83 ec 0c             	sub    $0xc,%esp
 80492b7:	68 78 a1 04 08       	push   $0x804a178
 80492bc:	e8 ff f4 ff ff       	call   80487c0 <puts@plt>
 80492c1:	83 c4 10             	add    $0x10,%esp
 80492c4:	eb b4                	jmp    804927a <phase_defused+0x18>
 80492c6:	83 ec 08             	sub    $0x8,%esp
 80492c9:	68 52 a2 04 08       	push   $0x804a252
 80492ce:	8d 44 24 18          	lea    0x18(%esp),%eax
 80492d2:	50                   	push   %eax
 80492d3:	e8 36 fd ff ff       	call   804900e <strings_not_equal>
 80492d8:	83 c4 10             	add    $0x10,%esp
 80492db:	85 c0                	test   %eax,%eax
 80492dd:	75 d5                	jne    80492b4 <phase_defused+0x52>
 80492df:	83 ec 0c             	sub    $0xc,%esp
 80492e2:	68 18 a1 04 08       	push   $0x804a118
 80492e7:	e8 d4 f4 ff ff       	call   80487c0 <puts@plt>
 80492ec:	c7 04 24 40 a1 04 08 	movl   $0x804a140,(%esp)
 80492f3:	e8 c8 f4 ff ff       	call   80487c0 <puts@plt>
 80492f8:	e8 1b fc ff ff       	call   8048f18 <secret_phase>
 80492fd:	83 c4 10             	add    $0x10,%esp
 8049300:	eb b2                	jmp    80492b4 <phase_defused+0x52>
 8049302:	e8 89 f4 ff ff       	call   8048790 <__stack_chk_fail@plt>

08049307 <sigalrm_handler>:
 8049307:	83 ec 0c             	sub    $0xc,%esp
 804930a:	6a 00                	push   $0x0
 804930c:	68 a8 a2 04 08       	push   $0x804a2a8
 8049311:	6a 01                	push   $0x1
 8049313:	ff 35 a0 c3 04 08    	pushl  0x804c3a0
 8049319:	e8 42 f5 ff ff       	call   8048860 <__fprintf_chk@plt>
 804931e:	c7 04 24 01 00 00 00 	movl   $0x1,(%esp)
 8049325:	e8 b6 f4 ff ff       	call   80487e0 <exit@plt>

0804932a <rio_readlineb>:
 804932a:	55                   	push   %ebp
 804932b:	57                   	push   %edi
 804932c:	56                   	push   %esi
 804932d:	53                   	push   %ebx
 804932e:	83 ec 1c             	sub    $0x1c,%esp
 8049331:	83 f9 01             	cmp    $0x1,%ecx
 8049334:	76 79                	jbe    80493af <rio_readlineb+0x85>
 8049336:	89 d7                	mov    %edx,%edi
 8049338:	89 c3                	mov    %eax,%ebx
 804933a:	89 4c 24 0c          	mov    %ecx,0xc(%esp)
 804933e:	bd 01 00 00 00       	mov    $0x1,%ebp
 8049343:	8d 70 0c             	lea    0xc(%eax),%esi
 8049346:	eb 0a                	jmp    8049352 <rio_readlineb+0x28>
 8049348:	e8 e3 f4 ff ff       	call   8048830 <__errno_location@plt>
 804934d:	83 38 04             	cmpl   $0x4,(%eax)
 8049350:	75 66                	jne    80493b8 <rio_readlineb+0x8e>
 8049352:	8b 43 04             	mov    0x4(%ebx),%eax
 8049355:	85 c0                	test   %eax,%eax
 8049357:	7f 23                	jg     804937c <rio_readlineb+0x52>
 8049359:	83 ec 04             	sub    $0x4,%esp
 804935c:	68 00 20 00 00       	push   $0x2000
 8049361:	56                   	push   %esi
 8049362:	ff 33                	pushl  (%ebx)
 8049364:	e8 c7 f3 ff ff       	call   8048730 <read@plt>
 8049369:	89 43 04             	mov    %eax,0x4(%ebx)
 804936c:	83 c4 10             	add    $0x10,%esp
 804936f:	85 c0                	test   %eax,%eax
 8049371:	78 d5                	js     8049348 <rio_readlineb+0x1e>
 8049373:	85 c0                	test   %eax,%eax
 8049375:	74 48                	je     80493bf <rio_readlineb+0x95>
 8049377:	89 73 08             	mov    %esi,0x8(%ebx)
 804937a:	eb d6                	jmp    8049352 <rio_readlineb+0x28>
 804937c:	8b 4b 08             	mov    0x8(%ebx),%ecx
 804937f:	0f b6 11             	movzbl (%ecx),%edx
 8049382:	83 c1 01             	add    $0x1,%ecx
 8049385:	89 4b 08             	mov    %ecx,0x8(%ebx)
 8049388:	83 e8 01             	sub    $0x1,%eax
 804938b:	89 43 04             	mov    %eax,0x4(%ebx)
 804938e:	83 c7 01             	add    $0x1,%edi
 8049391:	88 57 ff             	mov    %dl,-0x1(%edi)
 8049394:	80 fa 0a             	cmp    $0xa,%dl
 8049397:	74 09                	je     80493a2 <rio_readlineb+0x78>
 8049399:	83 c5 01             	add    $0x1,%ebp
 804939c:	3b 6c 24 0c          	cmp    0xc(%esp),%ebp
 80493a0:	75 b0                	jne    8049352 <rio_readlineb+0x28>
 80493a2:	c6 07 00             	movb   $0x0,(%edi)
 80493a5:	89 e8                	mov    %ebp,%eax
 80493a7:	83 c4 1c             	add    $0x1c,%esp
 80493aa:	5b                   	pop    %ebx
 80493ab:	5e                   	pop    %esi
 80493ac:	5f                   	pop    %edi
 80493ad:	5d                   	pop    %ebp
 80493ae:	c3                   	ret    
 80493af:	89 d7                	mov    %edx,%edi
 80493b1:	bd 01 00 00 00       	mov    $0x1,%ebp
 80493b6:	eb ea                	jmp    80493a2 <rio_readlineb+0x78>
 80493b8:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 80493bd:	eb 05                	jmp    80493c4 <rio_readlineb+0x9a>
 80493bf:	b8 00 00 00 00       	mov    $0x0,%eax
 80493c4:	85 c0                	test   %eax,%eax
 80493c6:	75 0c                	jne    80493d4 <rio_readlineb+0xaa>
 80493c8:	83 fd 01             	cmp    $0x1,%ebp
 80493cb:	75 d5                	jne    80493a2 <rio_readlineb+0x78>
 80493cd:	bd 00 00 00 00       	mov    $0x0,%ebp
 80493d2:	eb d1                	jmp    80493a5 <rio_readlineb+0x7b>
 80493d4:	bd ff ff ff ff       	mov    $0xffffffff,%ebp
 80493d9:	eb ca                	jmp    80493a5 <rio_readlineb+0x7b>

080493db <submitr>:
 80493db:	55                   	push   %ebp
 80493dc:	57                   	push   %edi
 80493dd:	56                   	push   %esi
 80493de:	53                   	push   %ebx
 80493df:	81 ec 60 a0 00 00    	sub    $0xa060,%esp
 80493e5:	8b 9c 24 74 a0 00 00 	mov    0xa074(%esp),%ebx
 80493ec:	8b 84 24 7c a0 00 00 	mov    0xa07c(%esp),%eax
 80493f3:	89 44 24 0c          	mov    %eax,0xc(%esp)
 80493f7:	8b 84 24 80 a0 00 00 	mov    0xa080(%esp),%eax
 80493fe:	89 44 24 10          	mov    %eax,0x10(%esp)
 8049402:	8b 84 24 84 a0 00 00 	mov    0xa084(%esp),%eax
 8049409:	89 44 24 14          	mov    %eax,0x14(%esp)
 804940d:	8b b4 24 88 a0 00 00 	mov    0xa088(%esp),%esi
 8049414:	8b 84 24 8c a0 00 00 	mov    0xa08c(%esp),%eax
 804941b:	89 44 24 18          	mov    %eax,0x18(%esp)
 804941f:	65 a1 14 00 00 00    	mov    %gs:0x14,%eax
 8049425:	89 84 24 50 a0 00 00 	mov    %eax,0xa050(%esp)
 804942c:	31 c0                	xor    %eax,%eax
 804942e:	c7 44 24 30 00 00 00 	movl   $0x0,0x30(%esp)
 8049435:	00 
 8049436:	6a 00                	push   $0x0
 8049438:	6a 01                	push   $0x1
 804943a:	6a 02                	push   $0x2
 804943c:	e8 0f f4 ff ff       	call   8048850 <socket@plt>
 8049441:	83 c4 10             	add    $0x10,%esp
 8049444:	85 c0                	test   %eax,%eax
 8049446:	0f 88 04 01 00 00    	js     8049550 <submitr+0x175>
 804944c:	89 c5                	mov    %eax,%ebp
 804944e:	83 ec 0c             	sub    $0xc,%esp
 8049451:	53                   	push   %ebx
 8049452:	e8 19 f4 ff ff       	call   8048870 <gethostbyname@plt>
 8049457:	83 c4 10             	add    $0x10,%esp
 804945a:	85 c0                	test   %eax,%eax
 804945c:	0f 84 40 01 00 00    	je     80495a2 <submitr+0x1c7>
 8049462:	8d 5c 24 30          	lea    0x30(%esp),%ebx
 8049466:	c7 44 24 30 00 00 00 	movl   $0x0,0x30(%esp)
 804946d:	00 
 804946e:	c7 44 24 34 00 00 00 	movl   $0x0,0x34(%esp)
 8049475:	00 
 8049476:	c7 44 24 38 00 00 00 	movl   $0x0,0x38(%esp)
 804947d:	00 
 804947e:	c7 44 24 3c 00 00 00 	movl   $0x0,0x3c(%esp)
 8049485:	00 
 8049486:	66 c7 44 24 30 02 00 	movw   $0x2,0x30(%esp)
 804948d:	6a 0c                	push   $0xc
 804948f:	ff 70 0c             	pushl  0xc(%eax)
 8049492:	8b 40 10             	mov    0x10(%eax),%eax
 8049495:	ff 30                	pushl  (%eax)
 8049497:	8d 44 24 40          	lea    0x40(%esp),%eax
 804949b:	50                   	push   %eax
 804949c:	e8 2f f3 ff ff       	call   80487d0 <__memmove_chk@plt>
 80494a1:	0f b7 84 24 84 a0 00 	movzwl 0xa084(%esp),%eax
 80494a8:	00 
 80494a9:	66 c1 c8 08          	ror    $0x8,%ax
 80494ad:	66 89 44 24 42       	mov    %ax,0x42(%esp)
 80494b2:	83 c4 0c             	add    $0xc,%esp
 80494b5:	6a 10                	push   $0x10
 80494b7:	53                   	push   %ebx
 80494b8:	55                   	push   %ebp
 80494b9:	e8 d2 f3 ff ff       	call   8048890 <connect@plt>
 80494be:	83 c4 10             	add    $0x10,%esp
 80494c1:	85 c0                	test   %eax,%eax
 80494c3:	0f 88 49 01 00 00    	js     8049612 <submitr+0x237>
 80494c9:	ba ff ff ff ff       	mov    $0xffffffff,%edx
 80494ce:	b8 00 00 00 00       	mov    $0x0,%eax
 80494d3:	89 d1                	mov    %edx,%ecx
 80494d5:	89 f7                	mov    %esi,%edi
 80494d7:	f2 ae                	repnz scas %es:(%edi),%al
 80494d9:	89 cb                	mov    %ecx,%ebx
 80494db:	f7 d3                	not    %ebx
 80494dd:	89 d1                	mov    %edx,%ecx
 80494df:	8b 7c 24 08          	mov    0x8(%esp),%edi
 80494e3:	f2 ae                	repnz scas %es:(%edi),%al
 80494e5:	89 4c 24 18          	mov    %ecx,0x18(%esp)
 80494e9:	89 d1                	mov    %edx,%ecx
 80494eb:	8b 7c 24 0c          	mov    0xc(%esp),%edi
 80494ef:	f2 ae                	repnz scas %es:(%edi),%al
 80494f1:	89 cf                	mov    %ecx,%edi
 80494f3:	f7 d7                	not    %edi
 80494f5:	89 7c 24 1c          	mov    %edi,0x1c(%esp)
 80494f9:	89 d1                	mov    %edx,%ecx
 80494fb:	8b 7c 24 10          	mov    0x10(%esp),%edi
 80494ff:	f2 ae                	repnz scas %es:(%edi),%al
 8049501:	8b 54 24 1c          	mov    0x1c(%esp),%edx
 8049505:	2b 54 24 18          	sub    0x18(%esp),%edx
 8049509:	29 ca                	sub    %ecx,%edx
 804950b:	8d 44 5b fd          	lea    -0x3(%ebx,%ebx,2),%eax
 804950f:	8d 44 02 7b          	lea    0x7b(%edx,%eax,1),%eax
 8049513:	3d 00 20 00 00       	cmp    $0x2000,%eax
 8049518:	0f 87 56 01 00 00    	ja     8049674 <submitr+0x299>
 804951e:	8d 94 24 4c 40 00 00 	lea    0x404c(%esp),%edx
 8049525:	b9 00 08 00 00       	mov    $0x800,%ecx
 804952a:	b8 00 00 00 00       	mov    $0x0,%eax
 804952f:	89 d7                	mov    %edx,%edi
 8049531:	f3 ab                	rep stos %eax,%es:(%edi)
 8049533:	b9 ff ff ff ff       	mov    $0xffffffff,%ecx
 8049538:	89 f7                	mov    %esi,%edi
 804953a:	f2 ae                	repnz scas %es:(%edi),%al
 804953c:	f7 d1                	not    %ecx
 804953e:	89 cb                	mov    %ecx,%ebx
 8049540:	83 eb 01             	sub    $0x1,%ebx
 8049543:	0f 84 07 06 00 00    	je     8049b50 <submitr+0x775>
 8049549:	89 d7                	mov    %edx,%edi
 804954b:	e9 b0 01 00 00       	jmp    8049700 <submitr+0x325>
 8049550:	8b 44 24 14          	mov    0x14(%esp),%eax
 8049554:	c7 00 45 72 72 6f    	movl   $0x6f727245,(%eax)
 804955a:	c7 40 04 72 3a 20 43 	movl   $0x43203a72,0x4(%eax)
 8049561:	c7 40 08 6c 69 65 6e 	movl   $0x6e65696c,0x8(%eax)
 8049568:	c7 40 0c 74 20 75 6e 	movl   $0x6e752074,0xc(%eax)
 804956f:	c7 40 10 61 62 6c 65 	movl   $0x656c6261,0x10(%eax)
 8049576:	c7 40 14 20 74 6f 20 	movl   $0x206f7420,0x14(%eax)
 804957d:	c7 40 18 63 72 65 61 	movl   $0x61657263,0x18(%eax)
 8049584:	c7 40 1c 74 65 20 73 	movl   $0x73206574,0x1c(%eax)
 804958b:	c7 40 20 6f 63 6b 65 	movl   $0x656b636f,0x20(%eax)
 8049592:	66 c7 40 24 74 00    	movw   $0x74,0x24(%eax)
 8049598:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 804959d:	e9 d0 04 00 00       	jmp    8049a72 <submitr+0x697>
 80495a2:	8b 44 24 14          	mov    0x14(%esp),%eax
 80495a6:	c7 00 45 72 72 6f    	movl   $0x6f727245,(%eax)
 80495ac:	c7 40 04 72 3a 20 44 	movl   $0x44203a72,0x4(%eax)
 80495b3:	c7 40 08 4e 53 20 69 	movl   $0x6920534e,0x8(%eax)
 80495ba:	c7 40 0c 73 20 75 6e 	movl   $0x6e752073,0xc(%eax)
 80495c1:	c7 40 10 61 62 6c 65 	movl   $0x656c6261,0x10(%eax)
 80495c8:	c7 40 14 20 74 6f 20 	movl   $0x206f7420,0x14(%eax)
 80495cf:	c7 40 18 72 65 73 6f 	movl   $0x6f736572,0x18(%eax)
 80495d6:	c7 40 1c 6c 76 65 20 	movl   $0x2065766c,0x1c(%eax)
 80495dd:	c7 40 20 73 65 72 76 	movl   $0x76726573,0x20(%eax)
 80495e4:	c7 40 24 65 72 20 61 	movl   $0x61207265,0x24(%eax)
 80495eb:	c7 40 28 64 64 72 65 	movl   $0x65726464,0x28(%eax)
 80495f2:	66 c7 40 2c 73 73    	movw   $0x7373,0x2c(%eax)
 80495f8:	c6 40 2e 00          	movb   $0x0,0x2e(%eax)
 80495fc:	83 ec 0c             	sub    $0xc,%esp
 80495ff:	55                   	push   %ebp
 8049600:	e8 9b f2 ff ff       	call   80488a0 <close@plt>
 8049605:	83 c4 10             	add    $0x10,%esp
 8049608:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 804960d:	e9 60 04 00 00       	jmp    8049a72 <submitr+0x697>
 8049612:	8b 44 24 14          	mov    0x14(%esp),%eax
 8049616:	c7 00 45 72 72 6f    	movl   $0x6f727245,(%eax)
 804961c:	c7 40 04 72 3a 20 55 	movl   $0x55203a72,0x4(%eax)
 8049623:	c7 40 08 6e 61 62 6c 	movl   $0x6c62616e,0x8(%eax)
 804962a:	c7 40 0c 65 20 74 6f 	movl   $0x6f742065,0xc(%eax)
 8049631:	c7 40 10 20 63 6f 6e 	movl   $0x6e6f6320,0x10(%eax)
 8049638:	c7 40 14 6e 65 63 74 	movl   $0x7463656e,0x14(%eax)
 804963f:	c7 40 18 20 74 6f 20 	movl   $0x206f7420,0x18(%eax)
 8049646:	c7 40 1c 74 68 65 20 	movl   $0x20656874,0x1c(%eax)
 804964d:	c7 40 20 73 65 72 76 	movl   $0x76726573,0x20(%eax)
 8049654:	66 c7 40 24 65 72    	movw   $0x7265,0x24(%eax)
 804965a:	c6 40 26 00          	movb   $0x0,0x26(%eax)
 804965e:	83 ec 0c             	sub    $0xc,%esp
 8049661:	55                   	push   %ebp
 8049662:	e8 39 f2 ff ff       	call   80488a0 <close@plt>
 8049667:	83 c4 10             	add    $0x10,%esp
 804966a:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 804966f:	e9 fe 03 00 00       	jmp    8049a72 <submitr+0x697>
 8049674:	8b 44 24 14          	mov    0x14(%esp),%eax
 8049678:	c7 00 45 72 72 6f    	movl   $0x6f727245,(%eax)
 804967e:	c7 40 04 72 3a 20 52 	movl   $0x52203a72,0x4(%eax)
 8049685:	c7 40 08 65 73 75 6c 	movl   $0x6c757365,0x8(%eax)
 804968c:	c7 40 0c 74 20 73 74 	movl   $0x74732074,0xc(%eax)
 8049693:	c7 40 10 72 69 6e 67 	movl   $0x676e6972,0x10(%eax)
 804969a:	c7 40 14 20 74 6f 6f 	movl   $0x6f6f7420,0x14(%eax)
 80496a1:	c7 40 18 20 6c 61 72 	movl   $0x72616c20,0x18(%eax)
 80496a8:	c7 40 1c 67 65 2e 20 	movl   $0x202e6567,0x1c(%eax)
 80496af:	c7 40 20 49 6e 63 72 	movl   $0x72636e49,0x20(%eax)
 80496b6:	c7 40 24 65 61 73 65 	movl   $0x65736165,0x24(%eax)
 80496bd:	c7 40 28 20 53 55 42 	movl   $0x42555320,0x28(%eax)
 80496c4:	c7 40 2c 4d 49 54 52 	movl   $0x5254494d,0x2c(%eax)
 80496cb:	c7 40 30 5f 4d 41 58 	movl   $0x58414d5f,0x30(%eax)
 80496d2:	c7 40 34 42 55 46 00 	movl   $0x465542,0x34(%eax)
 80496d9:	83 ec 0c             	sub    $0xc,%esp
 80496dc:	55                   	push   %ebp
 80496dd:	e8 be f1 ff ff       	call   80488a0 <close@plt>
 80496e2:	83 c4 10             	add    $0x10,%esp
 80496e5:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 80496ea:	e9 83 03 00 00       	jmp    8049a72 <submitr+0x697>
 80496ef:	88 17                	mov    %dl,(%edi)
 80496f1:	8d 7f 01             	lea    0x1(%edi),%edi
 80496f4:	83 c6 01             	add    $0x1,%esi
 80496f7:	83 eb 01             	sub    $0x1,%ebx
 80496fa:	0f 84 50 04 00 00    	je     8049b50 <submitr+0x775>
 8049700:	0f b6 16             	movzbl (%esi),%edx
 8049703:	8d 4a d6             	lea    -0x2a(%edx),%ecx
 8049706:	b8 01 00 00 00       	mov    $0x1,%eax
 804970b:	80 f9 0f             	cmp    $0xf,%cl
 804970e:	77 0d                	ja     804971d <submitr+0x342>
 8049710:	b8 d9 ff 00 00       	mov    $0xffd9,%eax
 8049715:	d3 e8                	shr    %cl,%eax
 8049717:	83 f0 01             	xor    $0x1,%eax
 804971a:	83 e0 01             	and    $0x1,%eax
 804971d:	80 fa 5f             	cmp    $0x5f,%dl
 8049720:	74 cd                	je     80496ef <submitr+0x314>
 8049722:	84 c0                	test   %al,%al
 8049724:	74 c9                	je     80496ef <submitr+0x314>
 8049726:	89 d0                	mov    %edx,%eax
 8049728:	83 e0 df             	and    $0xffffffdf,%eax
 804972b:	83 e8 41             	sub    $0x41,%eax
 804972e:	3c 19                	cmp    $0x19,%al
 8049730:	76 bd                	jbe    80496ef <submitr+0x314>
 8049732:	80 fa 20             	cmp    $0x20,%dl
 8049735:	74 58                	je     804978f <submitr+0x3b4>
 8049737:	8d 42 e0             	lea    -0x20(%edx),%eax
 804973a:	3c 5f                	cmp    $0x5f,%al
 804973c:	76 09                	jbe    8049747 <submitr+0x36c>
 804973e:	80 fa 09             	cmp    $0x9,%dl
 8049741:	0f 85 c5 03 00 00    	jne    8049b0c <submitr+0x731>
 8049747:	83 ec 0c             	sub    $0xc,%esp
 804974a:	0f b6 d2             	movzbl %dl,%edx
 804974d:	52                   	push   %edx
 804974e:	68 b4 a3 04 08       	push   $0x804a3b4
 8049753:	6a 08                	push   $0x8
 8049755:	6a 01                	push   $0x1
 8049757:	8d 84 24 68 80 00 00 	lea    0x8068(%esp),%eax
 804975e:	50                   	push   %eax
 804975f:	e8 5c f1 ff ff       	call   80488c0 <__sprintf_chk@plt>
 8049764:	0f b6 84 24 6c 80 00 	movzbl 0x806c(%esp),%eax
 804976b:	00 
 804976c:	88 07                	mov    %al,(%edi)
 804976e:	0f b6 84 24 6d 80 00 	movzbl 0x806d(%esp),%eax
 8049775:	00 
 8049776:	88 47 01             	mov    %al,0x1(%edi)
 8049779:	0f b6 84 24 6e 80 00 	movzbl 0x806e(%esp),%eax
 8049780:	00 
 8049781:	88 47 02             	mov    %al,0x2(%edi)
 8049784:	83 c4 20             	add    $0x20,%esp
 8049787:	8d 7f 03             	lea    0x3(%edi),%edi
 804978a:	e9 65 ff ff ff       	jmp    80496f4 <submitr+0x319>
 804978f:	c6 07 2b             	movb   $0x2b,(%edi)
 8049792:	8d 7f 01             	lea    0x1(%edi),%edi
 8049795:	e9 5a ff ff ff       	jmp    80496f4 <submitr+0x319>
 804979a:	01 c6                	add    %eax,%esi
 804979c:	29 c3                	sub    %eax,%ebx
 804979e:	74 24                	je     80497c4 <submitr+0x3e9>
 80497a0:	83 ec 04             	sub    $0x4,%esp
 80497a3:	53                   	push   %ebx
 80497a4:	56                   	push   %esi
 80497a5:	55                   	push   %ebp
 80497a6:	e8 55 f0 ff ff       	call   8048800 <write@plt>
 80497ab:	83 c4 10             	add    $0x10,%esp
 80497ae:	85 c0                	test   %eax,%eax
 80497b0:	7f e8                	jg     804979a <submitr+0x3bf>
 80497b2:	e8 79 f0 ff ff       	call   8048830 <__errno_location@plt>
 80497b7:	83 38 04             	cmpl   $0x4,(%eax)
 80497ba:	0f 85 b0 00 00 00    	jne    8049870 <submitr+0x495>
 80497c0:	89 f8                	mov    %edi,%eax
 80497c2:	eb d6                	jmp    804979a <submitr+0x3bf>
 80497c4:	83 7c 24 08 00       	cmpl   $0x0,0x8(%esp)
 80497c9:	0f 88 a1 00 00 00    	js     8049870 <submitr+0x495>
 80497cf:	89 6c 24 40          	mov    %ebp,0x40(%esp)
 80497d3:	c7 44 24 44 00 00 00 	movl   $0x0,0x44(%esp)
 80497da:	00 
 80497db:	8d 44 24 4c          	lea    0x4c(%esp),%eax
 80497df:	89 44 24 48          	mov    %eax,0x48(%esp)
 80497e3:	b9 00 20 00 00       	mov    $0x2000,%ecx
 80497e8:	8d 94 24 4c 20 00 00 	lea    0x204c(%esp),%edx
 80497ef:	8d 44 24 40          	lea    0x40(%esp),%eax
 80497f3:	e8 32 fb ff ff       	call   804932a <rio_readlineb>
 80497f8:	85 c0                	test   %eax,%eax
 80497fa:	0f 8e d6 00 00 00    	jle    80498d6 <submitr+0x4fb>
 8049800:	83 ec 0c             	sub    $0xc,%esp
 8049803:	8d 84 24 58 80 00 00 	lea    0x8058(%esp),%eax
 804980a:	50                   	push   %eax
 804980b:	8d 44 24 3c          	lea    0x3c(%esp),%eax
 804980f:	50                   	push   %eax
 8049810:	8d 84 24 60 60 00 00 	lea    0x6060(%esp),%eax
 8049817:	50                   	push   %eax
 8049818:	68 bb a3 04 08       	push   $0x804a3bb
 804981d:	8d 84 24 68 20 00 00 	lea    0x2068(%esp),%eax
 8049824:	50                   	push   %eax
 8049825:	e8 e6 ef ff ff       	call   8048810 <__isoc99_sscanf@plt>
 804982a:	8b 44 24 4c          	mov    0x4c(%esp),%eax
 804982e:	83 c4 20             	add    $0x20,%esp
 8049831:	3d c8 00 00 00       	cmp    $0xc8,%eax
 8049836:	0f 84 a6 01 00 00    	je     80499e2 <submitr+0x607>
 804983c:	83 ec 08             	sub    $0x8,%esp
 804983f:	8d 94 24 54 80 00 00 	lea    0x8054(%esp),%edx
 8049846:	52                   	push   %edx
 8049847:	50                   	push   %eax
 8049848:	68 cc a2 04 08       	push   $0x804a2cc
 804984d:	6a ff                	push   $0xffffffff
 804984f:	6a 01                	push   $0x1
 8049851:	ff 74 24 30          	pushl  0x30(%esp)
 8049855:	e8 66 f0 ff ff       	call   80488c0 <__sprintf_chk@plt>
 804985a:	83 c4 14             	add    $0x14,%esp
 804985d:	55                   	push   %ebp
 804985e:	e8 3d f0 ff ff       	call   80488a0 <close@plt>
 8049863:	83 c4 10             	add    $0x10,%esp
 8049866:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 804986b:	e9 02 02 00 00       	jmp    8049a72 <submitr+0x697>
 8049870:	8b 44 24 14          	mov    0x14(%esp),%eax
 8049874:	c7 00 45 72 72 6f    	movl   $0x6f727245,(%eax)
 804987a:	c7 40 04 72 3a 20 43 	movl   $0x43203a72,0x4(%eax)
 8049881:	c7 40 08 6c 69 65 6e 	movl   $0x6e65696c,0x8(%eax)
 8049888:	c7 40 0c 74 20 75 6e 	movl   $0x6e752074,0xc(%eax)
 804988f:	c7 40 10 61 62 6c 65 	movl   $0x656c6261,0x10(%eax)
 8049896:	c7 40 14 20 74 6f 20 	movl   $0x206f7420,0x14(%eax)
 804989d:	c7 40 18 77 72 69 74 	movl   $0x74697277,0x18(%eax)
 80498a4:	c7 40 1c 65 20 74 6f 	movl   $0x6f742065,0x1c(%eax)
 80498ab:	c7 40 20 20 74 68 65 	movl   $0x65687420,0x20(%eax)
 80498b2:	c7 40 24 20 73 65 72 	movl   $0x72657320,0x24(%eax)
 80498b9:	c7 40 28 76 65 72 00 	movl   $0x726576,0x28(%eax)
 80498c0:	83 ec 0c             	sub    $0xc,%esp
 80498c3:	55                   	push   %ebp
 80498c4:	e8 d7 ef ff ff       	call   80488a0 <close@plt>
 80498c9:	83 c4 10             	add    $0x10,%esp
 80498cc:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 80498d1:	e9 9c 01 00 00       	jmp    8049a72 <submitr+0x697>
 80498d6:	8b 44 24 14          	mov    0x14(%esp),%eax
 80498da:	c7 00 45 72 72 6f    	movl   $0x6f727245,(%eax)
 80498e0:	c7 40 04 72 3a 20 43 	movl   $0x43203a72,0x4(%eax)
 80498e7:	c7 40 08 6c 69 65 6e 	movl   $0x6e65696c,0x8(%eax)
 80498ee:	c7 40 0c 74 20 75 6e 	movl   $0x6e752074,0xc(%eax)
 80498f5:	c7 40 10 61 62 6c 65 	movl   $0x656c6261,0x10(%eax)
 80498fc:	c7 40 14 20 74 6f 20 	movl   $0x206f7420,0x14(%eax)
 8049903:	c7 40 18 72 65 61 64 	movl   $0x64616572,0x18(%eax)
 804990a:	c7 40 1c 20 66 69 72 	movl   $0x72696620,0x1c(%eax)
 8049911:	c7 40 20 73 74 20 68 	movl   $0x68207473,0x20(%eax)
 8049918:	c7 40 24 65 61 64 65 	movl   $0x65646165,0x24(%eax)
 804991f:	c7 40 28 72 20 66 72 	movl   $0x72662072,0x28(%eax)
 8049926:	c7 40 2c 6f 6d 20 73 	movl   $0x73206d6f,0x2c(%eax)
 804992d:	c7 40 30 65 72 76 65 	movl   $0x65767265,0x30(%eax)
 8049934:	66 c7 40 34 72 00    	movw   $0x72,0x34(%eax)
 804993a:	83 ec 0c             	sub    $0xc,%esp
 804993d:	55                   	push   %ebp
 804993e:	e8 5d ef ff ff       	call   80488a0 <close@plt>
 8049943:	83 c4 10             	add    $0x10,%esp
 8049946:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 804994b:	e9 22 01 00 00       	jmp    8049a72 <submitr+0x697>
 8049950:	8b 44 24 14          	mov    0x14(%esp),%eax
 8049954:	c7 00 45 72 72 6f    	movl   $0x6f727245,(%eax)
 804995a:	c7 40 04 72 3a 20 43 	movl   $0x43203a72,0x4(%eax)
 8049961:	c7 40 08 6c 69 65 6e 	movl   $0x6e65696c,0x8(%eax)
 8049968:	c7 40 0c 74 20 75 6e 	movl   $0x6e752074,0xc(%eax)
 804996f:	c7 40 10 61 62 6c 65 	movl   $0x656c6261,0x10(%eax)
 8049976:	c7 40 14 20 74 6f 20 	movl   $0x206f7420,0x14(%eax)
 804997d:	c7 40 18 72 65 61 64 	movl   $0x64616572,0x18(%eax)
 8049984:	c7 40 1c 20 68 65 61 	movl   $0x61656820,0x1c(%eax)
 804998b:	c7 40 20 64 65 72 73 	movl   $0x73726564,0x20(%eax)
 8049992:	c7 40 24 20 66 72 6f 	movl   $0x6f726620,0x24(%eax)
 8049999:	c7 40 28 6d 20 73 65 	movl   $0x6573206d,0x28(%eax)
 80499a0:	c7 40 2c 72 76 65 72 	movl   $0x72657672,0x2c(%eax)
 80499a7:	c6 40 30 00          	movb   $0x0,0x30(%eax)
 80499ab:	83 ec 0c             	sub    $0xc,%esp
 80499ae:	55                   	push   %ebp
 80499af:	e8 ec ee ff ff       	call   80488a0 <close@plt>
 80499b4:	83 c4 10             	add    $0x10,%esp
 80499b7:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 80499bc:	e9 b1 00 00 00       	jmp    8049a72 <submitr+0x697>
 80499c1:	85 c0                	test   %eax,%eax
 80499c3:	74 4b                	je     8049a10 <submitr+0x635>
 80499c5:	b9 00 20 00 00       	mov    $0x2000,%ecx
 80499ca:	8d 94 24 4c 20 00 00 	lea    0x204c(%esp),%edx
 80499d1:	8d 44 24 40          	lea    0x40(%esp),%eax
 80499d5:	e8 50 f9 ff ff       	call   804932a <rio_readlineb>
 80499da:	85 c0                	test   %eax,%eax
 80499dc:	0f 8e 6e ff ff ff    	jle    8049950 <submitr+0x575>
 80499e2:	0f b6 94 24 4c 20 00 	movzbl 0x204c(%esp),%edx
 80499e9:	00 
 80499ea:	b8 0d 00 00 00       	mov    $0xd,%eax
 80499ef:	29 d0                	sub    %edx,%eax
 80499f1:	75 ce                	jne    80499c1 <submitr+0x5e6>
 80499f3:	0f b6 94 24 4d 20 00 	movzbl 0x204d(%esp),%edx
 80499fa:	00 
 80499fb:	b8 0a 00 00 00       	mov    $0xa,%eax
 8049a00:	29 d0                	sub    %edx,%eax
 8049a02:	75 bd                	jne    80499c1 <submitr+0x5e6>
 8049a04:	0f b6 84 24 4e 20 00 	movzbl 0x204e(%esp),%eax
 8049a0b:	00 
 8049a0c:	f7 d8                	neg    %eax
 8049a0e:	eb b1                	jmp    80499c1 <submitr+0x5e6>
 8049a10:	b9 00 20 00 00       	mov    $0x2000,%ecx
 8049a15:	8d 94 24 4c 20 00 00 	lea    0x204c(%esp),%edx
 8049a1c:	8d 44 24 40          	lea    0x40(%esp),%eax
 8049a20:	e8 05 f9 ff ff       	call   804932a <rio_readlineb>
 8049a25:	85 c0                	test   %eax,%eax
 8049a27:	7e 68                	jle    8049a91 <submitr+0x6b6>
 8049a29:	83 ec 08             	sub    $0x8,%esp
 8049a2c:	8d 84 24 54 20 00 00 	lea    0x2054(%esp),%eax
 8049a33:	50                   	push   %eax
 8049a34:	8b 7c 24 20          	mov    0x20(%esp),%edi
 8049a38:	57                   	push   %edi
 8049a39:	e8 62 ed ff ff       	call   80487a0 <strcpy@plt>
 8049a3e:	89 2c 24             	mov    %ebp,(%esp)
 8049a41:	e8 5a ee ff ff       	call   80488a0 <close@plt>
 8049a46:	0f b6 17             	movzbl (%edi),%edx
 8049a49:	b8 4f 00 00 00       	mov    $0x4f,%eax
 8049a4e:	83 c4 10             	add    $0x10,%esp
 8049a51:	29 d0                	sub    %edx,%eax
 8049a53:	75 13                	jne    8049a68 <submitr+0x68d>
 8049a55:	0f b6 57 01          	movzbl 0x1(%edi),%edx
 8049a59:	b8 4b 00 00 00       	mov    $0x4b,%eax
 8049a5e:	29 d0                	sub    %edx,%eax
 8049a60:	75 06                	jne    8049a68 <submitr+0x68d>
 8049a62:	0f b6 47 02          	movzbl 0x2(%edi),%eax
 8049a66:	f7 d8                	neg    %eax
 8049a68:	85 c0                	test   %eax,%eax
 8049a6a:	0f 95 c0             	setne  %al
 8049a6d:	0f b6 c0             	movzbl %al,%eax
 8049a70:	f7 d8                	neg    %eax
 8049a72:	8b bc 24 4c a0 00 00 	mov    0xa04c(%esp),%edi
 8049a79:	65 33 3d 14 00 00 00 	xor    %gs:0x14,%edi
 8049a80:	0f 85 2a 01 00 00    	jne    8049bb0 <submitr+0x7d5>
 8049a86:	81 c4 5c a0 00 00    	add    $0xa05c,%esp
 8049a8c:	5b                   	pop    %ebx
 8049a8d:	5e                   	pop    %esi
 8049a8e:	5f                   	pop    %edi
 8049a8f:	5d                   	pop    %ebp
 8049a90:	c3                   	ret    
 8049a91:	8b 44 24 14          	mov    0x14(%esp),%eax
 8049a95:	c7 00 45 72 72 6f    	movl   $0x6f727245,(%eax)
 8049a9b:	c7 40 04 72 3a 20 43 	movl   $0x43203a72,0x4(%eax)
 8049aa2:	c7 40 08 6c 69 65 6e 	movl   $0x6e65696c,0x8(%eax)
 8049aa9:	c7 40 0c 74 20 75 6e 	movl   $0x6e752074,0xc(%eax)
 8049ab0:	c7 40 10 61 62 6c 65 	movl   $0x656c6261,0x10(%eax)
 8049ab7:	c7 40 14 20 74 6f 20 	movl   $0x206f7420,0x14(%eax)
 8049abe:	c7 40 18 72 65 61 64 	movl   $0x64616572,0x18(%eax)
 8049ac5:	c7 40 1c 20 73 74 61 	movl   $0x61747320,0x1c(%eax)
 8049acc:	c7 40 20 74 75 73 20 	movl   $0x20737574,0x20(%eax)
 8049ad3:	c7 40 24 6d 65 73 73 	movl   $0x7373656d,0x24(%eax)
 8049ada:	c7 40 28 61 67 65 20 	movl   $0x20656761,0x28(%eax)
 8049ae1:	c7 40 2c 66 72 6f 6d 	movl   $0x6d6f7266,0x2c(%eax)
 8049ae8:	c7 40 30 20 73 65 72 	movl   $0x72657320,0x30(%eax)
 8049aef:	c7 40 34 76 65 72 00 	movl   $0x726576,0x34(%eax)
 8049af6:	83 ec 0c             	sub    $0xc,%esp
 8049af9:	55                   	push   %ebp
 8049afa:	e8 a1 ed ff ff       	call   80488a0 <close@plt>
 8049aff:	83 c4 10             	add    $0x10,%esp
 8049b02:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049b07:	e9 66 ff ff ff       	jmp    8049a72 <submitr+0x697>
 8049b0c:	a1 fc a2 04 08       	mov    0x804a2fc,%eax
 8049b11:	8b 5c 24 14          	mov    0x14(%esp),%ebx
 8049b15:	89 03                	mov    %eax,(%ebx)
 8049b17:	a1 3b a3 04 08       	mov    0x804a33b,%eax
 8049b1c:	89 43 3f             	mov    %eax,0x3f(%ebx)
 8049b1f:	8d 7b 04             	lea    0x4(%ebx),%edi
 8049b22:	83 e7 fc             	and    $0xfffffffc,%edi
 8049b25:	29 fb                	sub    %edi,%ebx
 8049b27:	89 d8                	mov    %ebx,%eax
 8049b29:	be fc a2 04 08       	mov    $0x804a2fc,%esi
 8049b2e:	29 de                	sub    %ebx,%esi
 8049b30:	83 c0 43             	add    $0x43,%eax
 8049b33:	c1 e8 02             	shr    $0x2,%eax
 8049b36:	89 c1                	mov    %eax,%ecx
 8049b38:	f3 a5                	rep movsl %ds:(%esi),%es:(%edi)
 8049b3a:	83 ec 0c             	sub    $0xc,%esp
 8049b3d:	55                   	push   %ebp
 8049b3e:	e8 5d ed ff ff       	call   80488a0 <close@plt>
 8049b43:	83 c4 10             	add    $0x10,%esp
 8049b46:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049b4b:	e9 22 ff ff ff       	jmp    8049a72 <submitr+0x697>
 8049b50:	8d 84 24 4c 40 00 00 	lea    0x404c(%esp),%eax
 8049b57:	50                   	push   %eax
 8049b58:	ff 74 24 14          	pushl  0x14(%esp)
 8049b5c:	ff 74 24 14          	pushl  0x14(%esp)
 8049b60:	ff 74 24 14          	pushl  0x14(%esp)
 8049b64:	68 40 a3 04 08       	push   $0x804a340
 8049b69:	68 00 20 00 00       	push   $0x2000
 8049b6e:	6a 01                	push   $0x1
 8049b70:	8d bc 24 68 20 00 00 	lea    0x2068(%esp),%edi
 8049b77:	57                   	push   %edi
 8049b78:	e8 43 ed ff ff       	call   80488c0 <__sprintf_chk@plt>
 8049b7d:	b8 00 00 00 00       	mov    $0x0,%eax
 8049b82:	b9 ff ff ff ff       	mov    $0xffffffff,%ecx
 8049b87:	f2 ae                	repnz scas %es:(%edi),%al
 8049b89:	f7 d1                	not    %ecx
 8049b8b:	8d 41 ff             	lea    -0x1(%ecx),%eax
 8049b8e:	89 44 24 28          	mov    %eax,0x28(%esp)
 8049b92:	83 c4 20             	add    $0x20,%esp
 8049b95:	89 c3                	mov    %eax,%ebx
 8049b97:	8d b4 24 4c 20 00 00 	lea    0x204c(%esp),%esi
 8049b9e:	bf 00 00 00 00       	mov    $0x0,%edi
 8049ba3:	85 c0                	test   %eax,%eax
 8049ba5:	0f 85 f5 fb ff ff    	jne    80497a0 <submitr+0x3c5>
 8049bab:	e9 1f fc ff ff       	jmp    80497cf <submitr+0x3f4>
 8049bb0:	e8 db eb ff ff       	call   8048790 <__stack_chk_fail@plt>

08049bb5 <init_timeout>:
 8049bb5:	53                   	push   %ebx
 8049bb6:	83 ec 08             	sub    $0x8,%esp
 8049bb9:	8b 5c 24 10          	mov    0x10(%esp),%ebx
 8049bbd:	85 db                	test   %ebx,%ebx
 8049bbf:	74 24                	je     8049be5 <init_timeout+0x30>
 8049bc1:	83 ec 08             	sub    $0x8,%esp
 8049bc4:	68 07 93 04 08       	push   $0x8049307
 8049bc9:	6a 0e                	push   $0xe
 8049bcb:	e8 90 eb ff ff       	call   8048760 <signal@plt>
 8049bd0:	85 db                	test   %ebx,%ebx
 8049bd2:	b8 00 00 00 00       	mov    $0x0,%eax
 8049bd7:	0f 48 d8             	cmovs  %eax,%ebx
 8049bda:	89 1c 24             	mov    %ebx,(%esp)
 8049bdd:	e8 9e eb ff ff       	call   8048780 <alarm@plt>
 8049be2:	83 c4 10             	add    $0x10,%esp
 8049be5:	83 c4 08             	add    $0x8,%esp
 8049be8:	5b                   	pop    %ebx
 8049be9:	c3                   	ret    

08049bea <init_driver>:
 8049bea:	57                   	push   %edi
 8049beb:	56                   	push   %esi
 8049bec:	53                   	push   %ebx
 8049bed:	83 ec 28             	sub    $0x28,%esp
 8049bf0:	8b 74 24 38          	mov    0x38(%esp),%esi
 8049bf4:	65 a1 14 00 00 00    	mov    %gs:0x14,%eax
 8049bfa:	89 44 24 24          	mov    %eax,0x24(%esp)
 8049bfe:	31 c0                	xor    %eax,%eax
 8049c00:	6a 01                	push   $0x1
 8049c02:	6a 0d                	push   $0xd
 8049c04:	e8 57 eb ff ff       	call   8048760 <signal@plt>
 8049c09:	83 c4 08             	add    $0x8,%esp
 8049c0c:	6a 01                	push   $0x1
 8049c0e:	6a 1d                	push   $0x1d
 8049c10:	e8 4b eb ff ff       	call   8048760 <signal@plt>
 8049c15:	83 c4 08             	add    $0x8,%esp
 8049c18:	6a 01                	push   $0x1
 8049c1a:	6a 1d                	push   $0x1d
 8049c1c:	e8 3f eb ff ff       	call   8048760 <signal@plt>
 8049c21:	83 c4 0c             	add    $0xc,%esp
 8049c24:	6a 00                	push   $0x0
 8049c26:	6a 01                	push   $0x1
 8049c28:	6a 02                	push   $0x2
 8049c2a:	e8 21 ec ff ff       	call   8048850 <socket@plt>
 8049c2f:	83 c4 10             	add    $0x10,%esp
 8049c32:	85 c0                	test   %eax,%eax
 8049c34:	0f 88 a9 00 00 00    	js     8049ce3 <init_driver+0xf9>
 8049c3a:	89 c3                	mov    %eax,%ebx
 8049c3c:	83 ec 0c             	sub    $0xc,%esp
 8049c3f:	68 cc a3 04 08       	push   $0x804a3cc
 8049c44:	e8 27 ec ff ff       	call   8048870 <gethostbyname@plt>
 8049c49:	83 c4 10             	add    $0x10,%esp
 8049c4c:	85 c0                	test   %eax,%eax
 8049c4e:	0f 84 da 00 00 00    	je     8049d2e <init_driver+0x144>
 8049c54:	8d 7c 24 0c          	lea    0xc(%esp),%edi
 8049c58:	c7 44 24 0c 00 00 00 	movl   $0x0,0xc(%esp)
 8049c5f:	00 
 8049c60:	c7 44 24 10 00 00 00 	movl   $0x0,0x10(%esp)
 8049c67:	00 
 8049c68:	c7 44 24 14 00 00 00 	movl   $0x0,0x14(%esp)
 8049c6f:	00 
 8049c70:	c7 44 24 18 00 00 00 	movl   $0x0,0x18(%esp)
 8049c77:	00 
 8049c78:	66 c7 44 24 0c 02 00 	movw   $0x2,0xc(%esp)
 8049c7f:	6a 0c                	push   $0xc
 8049c81:	ff 70 0c             	pushl  0xc(%eax)
 8049c84:	8b 40 10             	mov    0x10(%eax),%eax
 8049c87:	ff 30                	pushl  (%eax)
 8049c89:	8d 44 24 1c          	lea    0x1c(%esp),%eax
 8049c8d:	50                   	push   %eax
 8049c8e:	e8 3d eb ff ff       	call   80487d0 <__memmove_chk@plt>
 8049c93:	66 c7 44 24 1e 3b 6e 	movw   $0x6e3b,0x1e(%esp)
 8049c9a:	83 c4 0c             	add    $0xc,%esp
 8049c9d:	6a 10                	push   $0x10
 8049c9f:	57                   	push   %edi
 8049ca0:	53                   	push   %ebx
 8049ca1:	e8 ea eb ff ff       	call   8048890 <connect@plt>
 8049ca6:	83 c4 10             	add    $0x10,%esp
 8049ca9:	85 c0                	test   %eax,%eax
 8049cab:	0f 88 e9 00 00 00    	js     8049d9a <init_driver+0x1b0>
 8049cb1:	83 ec 0c             	sub    $0xc,%esp
 8049cb4:	53                   	push   %ebx
 8049cb5:	e8 e6 eb ff ff       	call   80488a0 <close@plt>
 8049cba:	66 c7 06 4f 4b       	movw   $0x4b4f,(%esi)
 8049cbf:	c6 46 02 00          	movb   $0x0,0x2(%esi)
 8049cc3:	83 c4 10             	add    $0x10,%esp
 8049cc6:	b8 00 00 00 00       	mov    $0x0,%eax
 8049ccb:	8b 54 24 1c          	mov    0x1c(%esp),%edx
 8049ccf:	65 33 15 14 00 00 00 	xor    %gs:0x14,%edx
 8049cd6:	0f 85 eb 00 00 00    	jne    8049dc7 <init_driver+0x1dd>
 8049cdc:	83 c4 20             	add    $0x20,%esp
 8049cdf:	5b                   	pop    %ebx
 8049ce0:	5e                   	pop    %esi
 8049ce1:	5f                   	pop    %edi
 8049ce2:	c3                   	ret    
 8049ce3:	c7 06 45 72 72 6f    	movl   $0x6f727245,(%esi)
 8049ce9:	c7 46 04 72 3a 20 43 	movl   $0x43203a72,0x4(%esi)
 8049cf0:	c7 46 08 6c 69 65 6e 	movl   $0x6e65696c,0x8(%esi)
 8049cf7:	c7 46 0c 74 20 75 6e 	movl   $0x6e752074,0xc(%esi)
 8049cfe:	c7 46 10 61 62 6c 65 	movl   $0x656c6261,0x10(%esi)
 8049d05:	c7 46 14 20 74 6f 20 	movl   $0x206f7420,0x14(%esi)
 8049d0c:	c7 46 18 63 72 65 61 	movl   $0x61657263,0x18(%esi)
 8049d13:	c7 46 1c 74 65 20 73 	movl   $0x73206574,0x1c(%esi)
 8049d1a:	c7 46 20 6f 63 6b 65 	movl   $0x656b636f,0x20(%esi)
 8049d21:	66 c7 46 24 74 00    	movw   $0x74,0x24(%esi)
 8049d27:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049d2c:	eb 9d                	jmp    8049ccb <init_driver+0xe1>
 8049d2e:	c7 06 45 72 72 6f    	movl   $0x6f727245,(%esi)
 8049d34:	c7 46 04 72 3a 20 44 	movl   $0x44203a72,0x4(%esi)
 8049d3b:	c7 46 08 4e 53 20 69 	movl   $0x6920534e,0x8(%esi)
 8049d42:	c7 46 0c 73 20 75 6e 	movl   $0x6e752073,0xc(%esi)
 8049d49:	c7 46 10 61 62 6c 65 	movl   $0x656c6261,0x10(%esi)
 8049d50:	c7 46 14 20 74 6f 20 	movl   $0x206f7420,0x14(%esi)
 8049d57:	c7 46 18 72 65 73 6f 	movl   $0x6f736572,0x18(%esi)
 8049d5e:	c7 46 1c 6c 76 65 20 	movl   $0x2065766c,0x1c(%esi)
 8049d65:	c7 46 20 73 65 72 76 	movl   $0x76726573,0x20(%esi)
 8049d6c:	c7 46 24 65 72 20 61 	movl   $0x61207265,0x24(%esi)
 8049d73:	c7 46 28 64 64 72 65 	movl   $0x65726464,0x28(%esi)
 8049d7a:	66 c7 46 2c 73 73    	movw   $0x7373,0x2c(%esi)
 8049d80:	c6 46 2e 00          	movb   $0x0,0x2e(%esi)
 8049d84:	83 ec 0c             	sub    $0xc,%esp
 8049d87:	53                   	push   %ebx
 8049d88:	e8 13 eb ff ff       	call   80488a0 <close@plt>
 8049d8d:	83 c4 10             	add    $0x10,%esp
 8049d90:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049d95:	e9 31 ff ff ff       	jmp    8049ccb <init_driver+0xe1>
 8049d9a:	83 ec 0c             	sub    $0xc,%esp
 8049d9d:	68 cc a3 04 08       	push   $0x804a3cc
 8049da2:	68 8c a3 04 08       	push   $0x804a38c
 8049da7:	6a ff                	push   $0xffffffff
 8049da9:	6a 01                	push   $0x1
 8049dab:	56                   	push   %esi
 8049dac:	e8 0f eb ff ff       	call   80488c0 <__sprintf_chk@plt>
 8049db1:	83 c4 14             	add    $0x14,%esp
 8049db4:	53                   	push   %ebx
 8049db5:	e8 e6 ea ff ff       	call   80488a0 <close@plt>
 8049dba:	83 c4 10             	add    $0x10,%esp
 8049dbd:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049dc2:	e9 04 ff ff ff       	jmp    8049ccb <init_driver+0xe1>
 8049dc7:	e8 c4 e9 ff ff       	call   8048790 <__stack_chk_fail@plt>

08049dcc <driver_post>:
 8049dcc:	53                   	push   %ebx
 8049dcd:	83 ec 08             	sub    $0x8,%esp
 8049dd0:	8b 54 24 10          	mov    0x10(%esp),%edx
 8049dd4:	8b 44 24 18          	mov    0x18(%esp),%eax
 8049dd8:	8b 5c 24 1c          	mov    0x1c(%esp),%ebx
 8049ddc:	85 c0                	test   %eax,%eax
 8049dde:	75 17                	jne    8049df7 <driver_post+0x2b>
 8049de0:	85 d2                	test   %edx,%edx
 8049de2:	74 05                	je     8049de9 <driver_post+0x1d>
 8049de4:	80 3a 00             	cmpb   $0x0,(%edx)
 8049de7:	75 34                	jne    8049e1d <driver_post+0x51>
 8049de9:	66 c7 03 4f 4b       	movw   $0x4b4f,(%ebx)
 8049dee:	c6 43 02 00          	movb   $0x0,0x2(%ebx)
 8049df2:	83 c4 08             	add    $0x8,%esp
 8049df5:	5b                   	pop    %ebx
 8049df6:	c3                   	ret    
 8049df7:	83 ec 04             	sub    $0x4,%esp
 8049dfa:	ff 74 24 18          	pushl  0x18(%esp)
 8049dfe:	68 da a3 04 08       	push   $0x804a3da
 8049e03:	6a 01                	push   $0x1
 8049e05:	e8 36 ea ff ff       	call   8048840 <__printf_chk@plt>
 8049e0a:	66 c7 03 4f 4b       	movw   $0x4b4f,(%ebx)
 8049e0f:	c6 43 02 00          	movb   $0x0,0x2(%ebx)
 8049e13:	83 c4 10             	add    $0x10,%esp
 8049e16:	b8 00 00 00 00       	mov    $0x0,%eax
 8049e1b:	eb d5                	jmp    8049df2 <driver_post+0x26>
 8049e1d:	83 ec 04             	sub    $0x4,%esp
 8049e20:	53                   	push   %ebx
 8049e21:	ff 74 24 1c          	pushl  0x1c(%esp)
 8049e25:	68 f1 a3 04 08       	push   $0x804a3f1
 8049e2a:	52                   	push   %edx
 8049e2b:	68 f9 a3 04 08       	push   $0x804a3f9
 8049e30:	68 6e 3b 00 00       	push   $0x3b6e
 8049e35:	68 cc a3 04 08       	push   $0x804a3cc
 8049e3a:	e8 9c f5 ff ff       	call   80493db <submitr>
 8049e3f:	83 c4 20             	add    $0x20,%esp
 8049e42:	eb ae                	jmp    8049df2 <driver_post+0x26>
 8049e44:	66 90                	xchg   %ax,%ax
 8049e46:	66 90                	xchg   %ax,%ax
 8049e48:	66 90                	xchg   %ax,%ax
 8049e4a:	66 90                	xchg   %ax,%ax
 8049e4c:	66 90                	xchg   %ax,%ax
 8049e4e:	66 90                	xchg   %ax,%ax

08049e50 <__libc_csu_init>:
 8049e50:	55                   	push   %ebp
 8049e51:	57                   	push   %edi
 8049e52:	56                   	push   %esi
 8049e53:	53                   	push   %ebx
 8049e54:	e8 b7 ea ff ff       	call   8048910 <__x86.get_pc_thunk.bx>
 8049e59:	81 c3 a7 21 00 00    	add    $0x21a7,%ebx
 8049e5f:	83 ec 0c             	sub    $0xc,%esp
 8049e62:	8b 6c 24 20          	mov    0x20(%esp),%ebp
 8049e66:	8d b3 0c ff ff ff    	lea    -0xf4(%ebx),%esi
 8049e6c:	e8 83 e8 ff ff       	call   80486f4 <_init>
 8049e71:	8d 83 08 ff ff ff    	lea    -0xf8(%ebx),%eax
 8049e77:	29 c6                	sub    %eax,%esi
 8049e79:	c1 fe 02             	sar    $0x2,%esi
 8049e7c:	85 f6                	test   %esi,%esi
 8049e7e:	74 25                	je     8049ea5 <__libc_csu_init+0x55>
 8049e80:	31 ff                	xor    %edi,%edi
 8049e82:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
 8049e88:	83 ec 04             	sub    $0x4,%esp
 8049e8b:	ff 74 24 2c          	pushl  0x2c(%esp)
 8049e8f:	ff 74 24 2c          	pushl  0x2c(%esp)
 8049e93:	55                   	push   %ebp
 8049e94:	ff 94 bb 08 ff ff ff 	call   *-0xf8(%ebx,%edi,4)
 8049e9b:	83 c7 01             	add    $0x1,%edi
 8049e9e:	83 c4 10             	add    $0x10,%esp
 8049ea1:	39 fe                	cmp    %edi,%esi
 8049ea3:	75 e3                	jne    8049e88 <__libc_csu_init+0x38>
 8049ea5:	83 c4 0c             	add    $0xc,%esp
 8049ea8:	5b                   	pop    %ebx
 8049ea9:	5e                   	pop    %esi
 8049eaa:	5f                   	pop    %edi
 8049eab:	5d                   	pop    %ebp
 8049eac:	c3                   	ret    
 8049ead:	8d 76 00             	lea    0x0(%esi),%esi

08049eb0 <__libc_csu_fini>:
 8049eb0:	f3 c3                	repz ret 

Disassembly of section .fini:

08049eb4 <_fini>:
 8049eb4:	53                   	push   %ebx
 8049eb5:	83 ec 08             	sub    $0x8,%esp
 8049eb8:	e8 53 ea ff ff       	call   8048910 <__x86.get_pc_thunk.bx>
 8049ebd:	81 c3 43 21 00 00    	add    $0x2143,%ebx
 8049ec3:	83 c4 08             	add    $0x8,%esp
 8049ec6:	5b                   	pop    %ebx
 8049ec7:	c3                   	ret    
