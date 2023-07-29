
farm.o：     文件格式 elf64-x86-64


Disassembly of section .init:

0000000000001000 <_init>:
    1000:	f3 0f 1e fa          	endbr64 
    1004:	48 83 ec 08          	sub    $0x8,%rsp
    1008:	48 8b 05 d9 2f 00 00 	mov    0x2fd9(%rip),%rax        # 3fe8 <__gmon_start__>
    100f:	48 85 c0             	test   %rax,%rax
    1012:	74 02                	je     1016 <_init+0x16>
    1014:	ff d0                	callq  *%rax
    1016:	48 83 c4 08          	add    $0x8,%rsp
    101a:	c3                   	retq   

Disassembly of section .plt:

0000000000001020 <.plt>:
    1020:	ff 35 a2 2f 00 00    	pushq  0x2fa2(%rip)        # 3fc8 <_GLOBAL_OFFSET_TABLE_+0x8>
    1026:	f2 ff 25 a3 2f 00 00 	bnd jmpq *0x2fa3(%rip)        # 3fd0 <_GLOBAL_OFFSET_TABLE_+0x10>
    102d:	0f 1f 00             	nopl   (%rax)

Disassembly of section .plt.got:

0000000000001030 <__cxa_finalize@plt>:
    1030:	f3 0f 1e fa          	endbr64 
    1034:	f2 ff 25 bd 2f 00 00 	bnd jmpq *0x2fbd(%rip)        # 3ff8 <__cxa_finalize@GLIBC_2.2.5>
    103b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

Disassembly of section .text:

0000000000001040 <_start>:
    1040:	f3 0f 1e fa          	endbr64 
    1044:	31 ed                	xor    %ebp,%ebp
    1046:	49 89 d1             	mov    %rdx,%r9
    1049:	5e                   	pop    %rsi
    104a:	48 89 e2             	mov    %rsp,%rdx
    104d:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
    1051:	50                   	push   %rax
    1052:	54                   	push   %rsp
    1053:	4c 8d 05 d6 04 00 00 	lea    0x4d6(%rip),%r8        # 1530 <__libc_csu_fini>
    105a:	48 8d 0d 5f 04 00 00 	lea    0x45f(%rip),%rcx        # 14c0 <__libc_csu_init>
    1061:	48 8d 3d c1 00 00 00 	lea    0xc1(%rip),%rdi        # 1129 <main>
    1068:	ff 15 72 2f 00 00    	callq  *0x2f72(%rip)        # 3fe0 <__libc_start_main@GLIBC_2.2.5>
    106e:	f4                   	hlt    
    106f:	90                   	nop

0000000000001070 <deregister_tm_clones>:
    1070:	48 8d 3d 99 2f 00 00 	lea    0x2f99(%rip),%rdi        # 4010 <__TMC_END__>
    1077:	48 8d 05 92 2f 00 00 	lea    0x2f92(%rip),%rax        # 4010 <__TMC_END__>
    107e:	48 39 f8             	cmp    %rdi,%rax
    1081:	74 15                	je     1098 <deregister_tm_clones+0x28>
    1083:	48 8b 05 4e 2f 00 00 	mov    0x2f4e(%rip),%rax        # 3fd8 <_ITM_deregisterTMCloneTable>
    108a:	48 85 c0             	test   %rax,%rax
    108d:	74 09                	je     1098 <deregister_tm_clones+0x28>
    108f:	ff e0                	jmpq   *%rax
    1091:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
    1098:	c3                   	retq   
    1099:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

00000000000010a0 <register_tm_clones>:
    10a0:	48 8d 3d 69 2f 00 00 	lea    0x2f69(%rip),%rdi        # 4010 <__TMC_END__>
    10a7:	48 8d 35 62 2f 00 00 	lea    0x2f62(%rip),%rsi        # 4010 <__TMC_END__>
    10ae:	48 29 fe             	sub    %rdi,%rsi
    10b1:	48 89 f0             	mov    %rsi,%rax
    10b4:	48 c1 ee 3f          	shr    $0x3f,%rsi
    10b8:	48 c1 f8 03          	sar    $0x3,%rax
    10bc:	48 01 c6             	add    %rax,%rsi
    10bf:	48 d1 fe             	sar    %rsi
    10c2:	74 14                	je     10d8 <register_tm_clones+0x38>
    10c4:	48 8b 05 25 2f 00 00 	mov    0x2f25(%rip),%rax        # 3ff0 <_ITM_registerTMCloneTable>
    10cb:	48 85 c0             	test   %rax,%rax
    10ce:	74 08                	je     10d8 <register_tm_clones+0x38>
    10d0:	ff e0                	jmpq   *%rax
    10d2:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
    10d8:	c3                   	retq   
    10d9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

00000000000010e0 <__do_global_dtors_aux>:
    10e0:	f3 0f 1e fa          	endbr64 
    10e4:	80 3d 25 2f 00 00 00 	cmpb   $0x0,0x2f25(%rip)        # 4010 <__TMC_END__>
    10eb:	75 2b                	jne    1118 <__do_global_dtors_aux+0x38>
    10ed:	55                   	push   %rbp
    10ee:	48 83 3d 02 2f 00 00 	cmpq   $0x0,0x2f02(%rip)        # 3ff8 <__cxa_finalize@GLIBC_2.2.5>
    10f5:	00 
    10f6:	48 89 e5             	mov    %rsp,%rbp
    10f9:	74 0c                	je     1107 <__do_global_dtors_aux+0x27>
    10fb:	48 8b 3d 06 2f 00 00 	mov    0x2f06(%rip),%rdi        # 4008 <__dso_handle>
    1102:	e8 29 ff ff ff       	callq  1030 <__cxa_finalize@plt>
    1107:	e8 64 ff ff ff       	callq  1070 <deregister_tm_clones>
    110c:	c6 05 fd 2e 00 00 01 	movb   $0x1,0x2efd(%rip)        # 4010 <__TMC_END__>
    1113:	5d                   	pop    %rbp
    1114:	c3                   	retq   
    1115:	0f 1f 00             	nopl   (%rax)
    1118:	c3                   	retq   
    1119:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001120 <frame_dummy>:
    1120:	f3 0f 1e fa          	endbr64 
    1124:	e9 77 ff ff ff       	jmpq   10a0 <register_tm_clones>

0000000000001129 <main>:
    1129:	f3 0f 1e fa          	endbr64 
    112d:	55                   	push   %rbp
    112e:	48 89 e5             	mov    %rsp,%rbp
    1131:	b8 00 00 00 00       	mov    $0x0,%eax
    1136:	5d                   	pop    %rbp
    1137:	c3                   	retq   

0000000000001138 <start_farm>:
    1138:	f3 0f 1e fa          	endbr64 
    113c:	55                   	push   %rbp
    113d:	48 89 e5             	mov    %rsp,%rbp
    1140:	b8 01 00 00 00       	mov    $0x1,%eax
    1145:	5d                   	pop    %rbp
    1146:	c3                   	retq   

0000000000001147 <getval_142>:
    1147:	f3 0f 1e fa          	endbr64 
    114b:	55                   	push   %rbp
    114c:	48 89 e5             	mov    %rsp,%rbp
    114f:	b8 fb 78 90 90       	mov    $0x909078fb,%eax
    1154:	5d                   	pop    %rbp
    1155:	c3                   	retq   

0000000000001156 <addval_273>:
    1156:	f3 0f 1e fa          	endbr64 
    115a:	55                   	push   %rbp
    115b:	48 89 e5             	mov    %rsp,%rbp
    115e:	89 7d fc             	mov    %edi,-0x4(%rbp)
    1161:	8b 45 fc             	mov    -0x4(%rbp),%eax
    1164:	2d b8 76 38 3c       	sub    $0x3c3876b8,%eax
    1169:	5d                   	pop    %rbp
    116a:	c3                   	retq   

000000000000116b <addval_219>:
    116b:	f3 0f 1e fa          	endbr64 
    116f:	55                   	push   %rbp
    1170:	48 89 e5             	mov    %rsp,%rbp
    1173:	89 7d fc             	mov    %edi,-0x4(%rbp)
    1176:	8b 45 fc             	mov    -0x4(%rbp),%eax
    1179:	2d af 8c a7 6f       	sub    $0x6fa78caf,%eax
    117e:	5d                   	pop    %rbp
    117f:	c3                   	retq   

0000000000001180 <setval_237>:
    1180:	f3 0f 1e fa          	endbr64 
    1184:	55                   	push   %rbp
    1185:	48 89 e5             	mov    %rsp,%rbp
    1188:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    118c:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    1190:	c7 00 48 89 c7 c7    	movl   $0xc7c78948,(%rax)
    1196:	90                   	nop
    1197:	5d                   	pop    %rbp
    1198:	c3                   	retq   

0000000000001199 <setval_424>:
    1199:	f3 0f 1e fa          	endbr64 
    119d:	55                   	push   %rbp
    119e:	48 89 e5             	mov    %rsp,%rbp
    11a1:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    11a5:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    11a9:	c7 00 54 c2 58 92    	movl   $0x9258c254,(%rax)
    11af:	90                   	nop
    11b0:	5d                   	pop    %rbp
    11b1:	c3                   	retq   

00000000000011b2 <setval_470>:
    11b2:	f3 0f 1e fa          	endbr64 
    11b6:	55                   	push   %rbp
    11b7:	48 89 e5             	mov    %rsp,%rbp
    11ba:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    11be:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    11c2:	c7 00 63 48 8d c7    	movl   $0xc78d4863,(%rax)
    11c8:	90                   	nop
    11c9:	5d                   	pop    %rbp
    11ca:	c3                   	retq   

00000000000011cb <setval_426>:
    11cb:	f3 0f 1e fa          	endbr64 
    11cf:	55                   	push   %rbp
    11d0:	48 89 e5             	mov    %rsp,%rbp
    11d3:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    11d7:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    11db:	c7 00 48 89 c7 90    	movl   $0x90c78948,(%rax)
    11e1:	90                   	nop
    11e2:	5d                   	pop    %rbp
    11e3:	c3                   	retq   

00000000000011e4 <getval_280>:
    11e4:	f3 0f 1e fa          	endbr64 
    11e8:	55                   	push   %rbp
    11e9:	48 89 e5             	mov    %rsp,%rbp
    11ec:	b8 29 58 90 c3       	mov    $0xc3905829,%eax
    11f1:	5d                   	pop    %rbp
    11f2:	c3                   	retq   

00000000000011f3 <mid_farm>:
    11f3:	f3 0f 1e fa          	endbr64 
    11f7:	55                   	push   %rbp
    11f8:	48 89 e5             	mov    %rsp,%rbp
    11fb:	b8 01 00 00 00       	mov    $0x1,%eax
    1200:	5d                   	pop    %rbp
    1201:	c3                   	retq   

0000000000001202 <add_xy>:
    1202:	f3 0f 1e fa          	endbr64 
    1206:	55                   	push   %rbp
    1207:	48 89 e5             	mov    %rsp,%rbp
    120a:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    120e:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
    1212:	48 8b 55 f8          	mov    -0x8(%rbp),%rdx
    1216:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
    121a:	48 01 d0             	add    %rdx,%rax
    121d:	5d                   	pop    %rbp
    121e:	c3                   	retq   

000000000000121f <getval_481>:
    121f:	f3 0f 1e fa          	endbr64 
    1223:	55                   	push   %rbp
    1224:	48 89 e5             	mov    %rsp,%rbp
    1227:	b8 5c 89 c2 90       	mov    $0x90c2895c,%eax
    122c:	5d                   	pop    %rbp
    122d:	c3                   	retq   

000000000000122e <setval_296>:
    122e:	f3 0f 1e fa          	endbr64 
    1232:	55                   	push   %rbp
    1233:	48 89 e5             	mov    %rsp,%rbp
    1236:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    123a:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    123e:	c7 00 99 d1 90 90    	movl   $0x9090d199,(%rax)
    1244:	90                   	nop
    1245:	5d                   	pop    %rbp
    1246:	c3                   	retq   

0000000000001247 <addval_113>:
    1247:	f3 0f 1e fa          	endbr64 
    124b:	55                   	push   %rbp
    124c:	48 89 e5             	mov    %rsp,%rbp
    124f:	89 7d fc             	mov    %edi,-0x4(%rbp)
    1252:	8b 45 fc             	mov    -0x4(%rbp),%eax
    1255:	2d 77 31 87 36       	sub    $0x36873177,%eax
    125a:	5d                   	pop    %rbp
    125b:	c3                   	retq   

000000000000125c <addval_490>:
    125c:	f3 0f 1e fa          	endbr64 
    1260:	55                   	push   %rbp
    1261:	48 89 e5             	mov    %rsp,%rbp
    1264:	89 7d fc             	mov    %edi,-0x4(%rbp)
    1267:	8b 45 fc             	mov    -0x4(%rbp),%eax
    126a:	2d 73 2e df 24       	sub    $0x24df2e73,%eax
    126f:	5d                   	pop    %rbp
    1270:	c3                   	retq   

0000000000001271 <getval_226>:
    1271:	f3 0f 1e fa          	endbr64 
    1275:	55                   	push   %rbp
    1276:	48 89 e5             	mov    %rsp,%rbp
    1279:	b8 89 d1 48 c0       	mov    $0xc048d189,%eax
    127e:	5d                   	pop    %rbp
    127f:	c3                   	retq   

0000000000001280 <setval_384>:
    1280:	f3 0f 1e fa          	endbr64 
    1284:	55                   	push   %rbp
    1285:	48 89 e5             	mov    %rsp,%rbp
    1288:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    128c:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    1290:	c7 00 81 d1 84 c0    	movl   $0xc084d181,(%rax)
    1296:	90                   	nop
    1297:	5d                   	pop    %rbp
    1298:	c3                   	retq   

0000000000001299 <addval_190>:
    1299:	f3 0f 1e fa          	endbr64 
    129d:	55                   	push   %rbp
    129e:	48 89 e5             	mov    %rsp,%rbp
    12a1:	89 7d fc             	mov    %edi,-0x4(%rbp)
    12a4:	8b 45 fc             	mov    -0x4(%rbp),%eax
    12a7:	2d bf b7 76 1f       	sub    $0x1f76b7bf,%eax
    12ac:	5d                   	pop    %rbp
    12ad:	c3                   	retq   

00000000000012ae <setval_276>:
    12ae:	f3 0f 1e fa          	endbr64 
    12b2:	55                   	push   %rbp
    12b3:	48 89 e5             	mov    %rsp,%rbp
    12b6:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    12ba:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    12be:	c7 00 88 c2 08 c9    	movl   $0xc908c288,(%rax)
    12c4:	90                   	nop
    12c5:	5d                   	pop    %rbp
    12c6:	c3                   	retq   

00000000000012c7 <addval_436>:
    12c7:	f3 0f 1e fa          	endbr64 
    12cb:	55                   	push   %rbp
    12cc:	48 89 e5             	mov    %rsp,%rbp
    12cf:	89 7d fc             	mov    %edi,-0x4(%rbp)
    12d2:	8b 45 fc             	mov    -0x4(%rbp),%eax
    12d5:	2d 77 31 6f 6f       	sub    $0x6f6f3177,%eax
    12da:	5d                   	pop    %rbp
    12db:	c3                   	retq   

00000000000012dc <getval_345>:
    12dc:	f3 0f 1e fa          	endbr64 
    12e0:	55                   	push   %rbp
    12e1:	48 89 e5             	mov    %rsp,%rbp
    12e4:	b8 48 89 e0 c1       	mov    $0xc1e08948,%eax
    12e9:	5d                   	pop    %rbp
    12ea:	c3                   	retq   

00000000000012eb <addval_479>:
    12eb:	f3 0f 1e fa          	endbr64 
    12ef:	55                   	push   %rbp
    12f0:	48 89 e5             	mov    %rsp,%rbp
    12f3:	89 7d fc             	mov    %edi,-0x4(%rbp)
    12f6:	8b 45 fc             	mov    -0x4(%rbp),%eax
    12f9:	2d 77 3d ff 36       	sub    $0x36ff3d77,%eax
    12fe:	5d                   	pop    %rbp
    12ff:	c3                   	retq   

0000000000001300 <addval_187>:
    1300:	f3 0f 1e fa          	endbr64 
    1304:	55                   	push   %rbp
    1305:	48 89 e5             	mov    %rsp,%rbp
    1308:	89 7d fc             	mov    %edi,-0x4(%rbp)
    130b:	8b 45 fc             	mov    -0x4(%rbp),%eax
    130e:	2d 77 31 c7 3f       	sub    $0x3fc73177,%eax
    1313:	5d                   	pop    %rbp
    1314:	c3                   	retq   

0000000000001315 <setval_248>:
    1315:	f3 0f 1e fa          	endbr64 
    1319:	55                   	push   %rbp
    131a:	48 89 e5             	mov    %rsp,%rbp
    131d:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    1321:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    1325:	c7 00 81 ce 08 db    	movl   $0xdb08ce81,(%rax)
    132b:	90                   	nop
    132c:	5d                   	pop    %rbp
    132d:	c3                   	retq   

000000000000132e <getval_159>:
    132e:	f3 0f 1e fa          	endbr64 
    1332:	55                   	push   %rbp
    1333:	48 89 e5             	mov    %rsp,%rbp
    1336:	b8 89 d1 38 c9       	mov    $0xc938d189,%eax
    133b:	5d                   	pop    %rbp
    133c:	c3                   	retq   

000000000000133d <addval_110>:
    133d:	f3 0f 1e fa          	endbr64 
    1341:	55                   	push   %rbp
    1342:	48 89 e5             	mov    %rsp,%rbp
    1345:	89 7d fc             	mov    %edi,-0x4(%rbp)
    1348:	8b 45 fc             	mov    -0x4(%rbp),%eax
    134b:	2d 38 76 1f 3c       	sub    $0x3c1f7638,%eax
    1350:	5d                   	pop    %rbp
    1351:	c3                   	retq   

0000000000001352 <addval_487>:
    1352:	f3 0f 1e fa          	endbr64 
    1356:	55                   	push   %rbp
    1357:	48 89 e5             	mov    %rsp,%rbp
    135a:	89 7d fc             	mov    %edi,-0x4(%rbp)
    135d:	8b 45 fc             	mov    -0x4(%rbp),%eax
    1360:	2d 77 3d 7b 3f       	sub    $0x3f7b3d77,%eax
    1365:	5d                   	pop    %rbp
    1366:	c3                   	retq   

0000000000001367 <addval_201>:
    1367:	f3 0f 1e fa          	endbr64 
    136b:	55                   	push   %rbp
    136c:	48 89 e5             	mov    %rsp,%rbp
    136f:	89 7d fc             	mov    %edi,-0x4(%rbp)
    1372:	8b 45 fc             	mov    -0x4(%rbp),%eax
    1375:	2d b8 76 1f 38       	sub    $0x381f76b8,%eax
    137a:	5d                   	pop    %rbp
    137b:	c3                   	retq   

000000000000137c <getval_272>:
    137c:	f3 0f 1e fa          	endbr64 
    1380:	55                   	push   %rbp
    1381:	48 89 e5             	mov    %rsp,%rbp
    1384:	b8 99 d1 08 d2       	mov    $0xd208d199,%eax
    1389:	5d                   	pop    %rbp
    138a:	c3                   	retq   

000000000000138b <getval_155>:
    138b:	f3 0f 1e fa          	endbr64 
    138f:	55                   	push   %rbp
    1390:	48 89 e5             	mov    %rsp,%rbp
    1393:	b8 89 c2 c4 c9       	mov    $0xc9c4c289,%eax
    1398:	5d                   	pop    %rbp
    1399:	c3                   	retq   

000000000000139a <setval_299>:
    139a:	f3 0f 1e fa          	endbr64 
    139e:	55                   	push   %rbp
    139f:	48 89 e5             	mov    %rsp,%rbp
    13a2:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    13a6:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    13aa:	c7 00 48 89 e0 91    	movl   $0x91e08948,(%rax)
    13b0:	90                   	nop
    13b1:	5d                   	pop    %rbp
    13b2:	c3                   	retq   

00000000000013b3 <addval_404>:
    13b3:	f3 0f 1e fa          	endbr64 
    13b7:	55                   	push   %rbp
    13b8:	48 89 e5             	mov    %rsp,%rbp
    13bb:	89 7d fc             	mov    %edi,-0x4(%rbp)
    13be:	8b 45 fc             	mov    -0x4(%rbp),%eax
    13c1:	2d 77 31 6d 3c       	sub    $0x3c6d3177,%eax
    13c6:	5d                   	pop    %rbp
    13c7:	c3                   	retq   

00000000000013c8 <getval_311>:
    13c8:	f3 0f 1e fa          	endbr64 
    13cc:	55                   	push   %rbp
    13cd:	48 89 e5             	mov    %rsp,%rbp
    13d0:	b8 89 d1 08 db       	mov    $0xdb08d189,%eax
    13d5:	5d                   	pop    %rbp
    13d6:	c3                   	retq   

00000000000013d7 <setval_167>:
    13d7:	f3 0f 1e fa          	endbr64 
    13db:	55                   	push   %rbp
    13dc:	48 89 e5             	mov    %rsp,%rbp
    13df:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    13e3:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    13e7:	c7 00 89 d1 91 c3    	movl   $0xc391d189,(%rax)
    13ed:	90                   	nop
    13ee:	5d                   	pop    %rbp
    13ef:	c3                   	retq   

00000000000013f0 <setval_328>:
    13f0:	f3 0f 1e fa          	endbr64 
    13f4:	55                   	push   %rbp
    13f5:	48 89 e5             	mov    %rsp,%rbp
    13f8:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    13fc:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    1400:	c7 00 81 c2 38 d2    	movl   $0xd238c281,(%rax)
    1406:	90                   	nop
    1407:	5d                   	pop    %rbp
    1408:	c3                   	retq   

0000000000001409 <setval_450>:
    1409:	f3 0f 1e fa          	endbr64 
    140d:	55                   	push   %rbp
    140e:	48 89 e5             	mov    %rsp,%rbp
    1411:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    1415:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    1419:	c7 00 09 ce 08 c9    	movl   $0xc908ce09,(%rax)
    141f:	90                   	nop
    1420:	5d                   	pop    %rbp
    1421:	c3                   	retq   

0000000000001422 <addval_358>:
    1422:	f3 0f 1e fa          	endbr64 
    1426:	55                   	push   %rbp
    1427:	48 89 e5             	mov    %rsp,%rbp
    142a:	89 7d fc             	mov    %edi,-0x4(%rbp)
    142d:	8b 45 fc             	mov    -0x4(%rbp),%eax
    1430:	2d f8 76 1f 6f       	sub    $0x6f1f76f8,%eax
    1435:	5d                   	pop    %rbp
    1436:	c3                   	retq   

0000000000001437 <addval_124>:
    1437:	f3 0f 1e fa          	endbr64 
    143b:	55                   	push   %rbp
    143c:	48 89 e5             	mov    %rsp,%rbp
    143f:	89 7d fc             	mov    %edi,-0x4(%rbp)
    1442:	8b 45 fc             	mov    -0x4(%rbp),%eax
    1445:	05 89 c2 c7 3c       	add    $0x3cc7c289,%eax
    144a:	5d                   	pop    %rbp
    144b:	c3                   	retq   

000000000000144c <getval_169>:
    144c:	f3 0f 1e fa          	endbr64 
    1450:	55                   	push   %rbp
    1451:	48 89 e5             	mov    %rsp,%rbp
    1454:	b8 88 ce 20 c0       	mov    $0xc020ce88,%eax
    1459:	5d                   	pop    %rbp
    145a:	c3                   	retq   

000000000000145b <setval_181>:
    145b:	f3 0f 1e fa          	endbr64 
    145f:	55                   	push   %rbp
    1460:	48 89 e5             	mov    %rsp,%rbp
    1463:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    1467:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    146b:	c7 00 48 89 e0 c2    	movl   $0xc2e08948,(%rax)
    1471:	90                   	nop
    1472:	5d                   	pop    %rbp
    1473:	c3                   	retq   

0000000000001474 <addval_184>:
    1474:	f3 0f 1e fa          	endbr64 
    1478:	55                   	push   %rbp
    1479:	48 89 e5             	mov    %rsp,%rbp
    147c:	89 7d fc             	mov    %edi,-0x4(%rbp)
    147f:	8b 45 fc             	mov    -0x4(%rbp),%eax
    1482:	2d 77 3d 9f 2d       	sub    $0x2d9f3d77,%eax
    1487:	5d                   	pop    %rbp
    1488:	c3                   	retq   

0000000000001489 <getval_472>:
    1489:	f3 0f 1e fa          	endbr64 
    148d:	55                   	push   %rbp
    148e:	48 89 e5             	mov    %rsp,%rbp
    1491:	b8 8d ce 20 d2       	mov    $0xd220ce8d,%eax
    1496:	5d                   	pop    %rbp
    1497:	c3                   	retq   

0000000000001498 <setval_350>:
    1498:	f3 0f 1e fa          	endbr64 
    149c:	55                   	push   %rbp
    149d:	48 89 e5             	mov    %rsp,%rbp
    14a0:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    14a4:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    14a8:	c7 00 48 89 e0 90    	movl   $0x90e08948,(%rax)
    14ae:	90                   	nop
    14af:	5d                   	pop    %rbp
    14b0:	c3                   	retq   

00000000000014b1 <end_farm>:
    14b1:	f3 0f 1e fa          	endbr64 
    14b5:	55                   	push   %rbp
    14b6:	48 89 e5             	mov    %rsp,%rbp
    14b9:	b8 01 00 00 00       	mov    $0x1,%eax
    14be:	5d                   	pop    %rbp
    14bf:	c3                   	retq   

00000000000014c0 <__libc_csu_init>:
    14c0:	f3 0f 1e fa          	endbr64 
    14c4:	41 57                	push   %r15
    14c6:	4c 8d 3d 23 29 00 00 	lea    0x2923(%rip),%r15        # 3df0 <__frame_dummy_init_array_entry>
    14cd:	41 56                	push   %r14
    14cf:	49 89 d6             	mov    %rdx,%r14
    14d2:	41 55                	push   %r13
    14d4:	49 89 f5             	mov    %rsi,%r13
    14d7:	41 54                	push   %r12
    14d9:	41 89 fc             	mov    %edi,%r12d
    14dc:	55                   	push   %rbp
    14dd:	48 8d 2d 14 29 00 00 	lea    0x2914(%rip),%rbp        # 3df8 <__do_global_dtors_aux_fini_array_entry>
    14e4:	53                   	push   %rbx
    14e5:	4c 29 fd             	sub    %r15,%rbp
    14e8:	48 83 ec 08          	sub    $0x8,%rsp
    14ec:	e8 0f fb ff ff       	callq  1000 <_init>
    14f1:	48 c1 fd 03          	sar    $0x3,%rbp
    14f5:	74 1f                	je     1516 <__libc_csu_init+0x56>
    14f7:	31 db                	xor    %ebx,%ebx
    14f9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
    1500:	4c 89 f2             	mov    %r14,%rdx
    1503:	4c 89 ee             	mov    %r13,%rsi
    1506:	44 89 e7             	mov    %r12d,%edi
    1509:	41 ff 14 df          	callq  *(%r15,%rbx,8)
    150d:	48 83 c3 01          	add    $0x1,%rbx
    1511:	48 39 dd             	cmp    %rbx,%rbp
    1514:	75 ea                	jne    1500 <__libc_csu_init+0x40>
    1516:	48 83 c4 08          	add    $0x8,%rsp
    151a:	5b                   	pop    %rbx
    151b:	5d                   	pop    %rbp
    151c:	41 5c                	pop    %r12
    151e:	41 5d                	pop    %r13
    1520:	41 5e                	pop    %r14
    1522:	41 5f                	pop    %r15
    1524:	c3                   	retq   
    1525:	66 66 2e 0f 1f 84 00 	data16 nopw %cs:0x0(%rax,%rax,1)
    152c:	00 00 00 00 

0000000000001530 <__libc_csu_fini>:
    1530:	f3 0f 1e fa          	endbr64 
    1534:	c3                   	retq   

Disassembly of section .fini:

0000000000001538 <_fini>:
    1538:	f3 0f 1e fa          	endbr64 
    153c:	48 83 ec 08          	sub    $0x8,%rsp
    1540:	48 83 c4 08          	add    $0x8,%rsp
    1544:	c3                   	retq   
