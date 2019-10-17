# Lists of object files for CLIB.MAK.  The list is split into four sections
# to avoid MAKE's 4096-character limit on rules.

# Included in all libs
# Statically linked in RTLDLL
OBJS1 =         \
    abs.obj     \
    alloca.obj  \
    atexit.obj  \
    bdosptr.obj \
    biosequ.obj \
    bios_equ.obj\
    chainint.obj\
    chdir.obj   \
    chdrive.obj \
    clearerr.obj\
    clock.obj   \
    country.obj \
    ctrlbrk.obj \
    ctype.obj   \
    ddvt.obj    \
    del.obj     \
    delf.obj    \
    divt.obj    \
    dosclose.obj\
    doscmd.obj  \
    doscmmit.obj\
    doscreat.obj\
    dosdfree.obj\
    dosenv.obj  \
    dosfattr.obj\
    dosfind.obj \
    dosfree.obj \
    dosgdate.obj\
    dosgdriv.obj\
    dosgftim.obj\
    doskeep.obj \
    doslock.obj \
    dosopen.obj \
    dosread.obj \
    dossdate.obj\
    dosseek.obj \
    dossetbl.obj\
    dossftim.obj\
    dostimu.obj \
    dosvect.obj \
    doswrite.obj\
    dup2.obj    \
    errormsg.obj\
    exit.obj    \
    fddvt.obj   \
    ffmalloc.obj\
    fgetpos.obj \
    files.obj   \
    files2.obj  \
    fmode.obj   \
    fpstklen.obj\
    fsetpos.obj \
    f_lxmul.obj \
    f_pcmp.obj  \
    f_scopy.obj \
    getcbrk.obj \
    getcurdi.obj\
    getdate.obj \
    getdisk.obj \
    getdta.obj

# Included in all libs
# Statically linked in RTLDLL
OBJS2 =         \
    getfat.obj  \
    getftime.obj\
    getpsp.obj  \
    getswit.obj \
    getvect.obj \
    getverf.obj \
    getw.obj    \
    heaplen.obj \
    h_ldiv.obj  \
    h_llsh.obj  \
    h_lrsh.obj  \
    h_lursh.obj \
    h_pada.obj  \
    h_padd.obj  \
    h_pina.obj  \
    h_psbh.obj  \
    h_psbp.obj  \
    h_spush.obj \
    inport.obj  \
    ioerror.obj \
    is.obj      \
    isatty.obj  \
    labs.obj    \
    longtoa.obj \
    lrotl.obj   \
    lrotr.obj   \
    lseek.obj   \
    mkdir.obj   \
    mkname.obj  \
    new.obj     \
    newf.obj    \
    n_lxmul.obj \
    n_pcmp.obj  \
    n_scopy.obj \
    outport.obj \
    parsfnm.obj \
    peek.obj    \
    poke.obj    \
    pureerr.obj \
    rand.obj    \
    reada.obj   \
    remove.obj  \
    rmdir.obj   \
    rmtmp.obj   \
    rotl.obj    \
    rotr.obj    \
    scanner.obj \
    scantol.obj \
    searchp.obj \
    segread.obj \
    setbuf.obj  \
    setdate.obj \
    setdta.obj  \
    setftime.obj\
    setupio.obj \
    sigdata.obj \
    sopen.obj   \
    srchpath.obj\
    stkavail.obj\
    stime.obj   \
    stklen.obj  \
    stpcpy.obj  \
    strcoll.obj

# Included in all libs
# Statically linked in RTLDLL
OBJS3 =         \
    strxfrm.obj \
    tell.obj    \
    tolower.obj \
    toupper.obj \
    umask.obj   \
    unlink.obj  \
    vapp.obj    \
    vappv.obj   \
    vdel.obj    \
    vdelf.obj   \
    vdeln.obj   \
    vnew.obj    \
    vnewf.obj   \
    vnewn.obj   \
    vnewv.obj   \
    vnewvf.obj  \
    vnewvn.obj  \
    vprinter.obj\
    vram.obj    \
    wild.obj    \
    wscroll.obj \
    xclose.obj  \
    zapctlz.obj \
    _stpcpy.obj \

# Included in DOS libs only
OBJS4 =         \
    assert.obj  \
    absread.obj \
    allocmem.obj\
    bioscom.obj \
    biosdisk.obj\
    bioskey.obj \
    biosprin.obj\
    bios_com.obj\
    bios_dsk.obj\
    bios_key.obj\
    bios_prn.obj\
    brk.obj     \
    calloc.obj  \
    cgets.obj   \
    clreol.obj  \
    clrscr.obj  \
    color.obj   \
    constrea.obj\
    coreleft.obj\
    cprintf.obj \
    cputs.obj   \
    crtinit.obj \
    cscanf.obj  \
    cursor.obj  \
    cvtfak.obj  \
    delay.obj   \
    dosalloc.obj\
    exec.obj    \
    execl.obj   \
    execle.obj  \
    execlp.obj  \
    execlpe.obj \
    execv.obj   \
    execve.obj  \
    execvp.obj  \
    execvpe.obj \
    farheap.obj \
    fbrk.obj    \
    fcalloc.obj \
    fcorelft.obj\
    fheapchk.obj\
    freemem.obj \
    getch.obj   \
    getpass.obj \
    gexit.obj   \
    gfreemem.obj\
    ggetmem.obj \
    gotoxy.obj  \
    gptext.obj  \
    gregistr.obj\
    hard.obj    \
    harderr.obj \
    insline.obj \
    int86.obj   \
    intdos.obj  \
    intr.obj    \
    ioctl.obj   \
    kbhit.obj   \
    keep.obj    \
    loadprog.obj\
    movetext.obj\
    nearheap.obj\
    nheapchk.obj\
    putch.obj   \
    randblk.obj \
    realcvt.obj \
    scantod.obj \
    screen.obj  \
    scroll.obj  \
    setargv.obj \
    setblock.obj\
    setenvp.obj \
    setjmp.obj  \
    signal.obj  \
    sleep.obj   \
    sound.obj   \
    spawn.obj   \
    spawnl.obj  \
    spawnle.obj \
    spawnlp.obj \
    spawnlpe.obj\
    spawnv.obj  \
    spawnve.obj \
    spawnvp.obj \
    spawnvpe.obj\
    stack.obj   \
    system.obj  \
    textmode.obj\
    vidinfo.obj \
    wherexy.obj \
    window.obj

# Included in all libs
# Dynamically linked in RTLDLL
OBJS5 =         \
    access.obj  \
    atol.obj    \
    bcd1.obj    \
    bcd2.obj    \
    bdos.obj    \
    bsearch.obj \
    castmptr.obj\
    chmod.obj   \
    chmoda.obj  \
    chsize.obj  \
    close.obj   \
    closea.obj  \
    closeall.obj\
    cplx1.obj   \
    cplx2.obj   \
    creat.obj   \
    creata.obj  \
    ctime.obj   \
    direct.obj  \
    dosext.obj  \
    eof.obj     \
    fclose.obj  \
    fdopen.obj  \
    fflush.obj  \
    fgets.obj   \
    findfirs.obj\
    flength.obj \
    flushall.obj\
    fnmerge.obj \
    fnsplit.obj \
    fopen.obj   \
    fprintf.obj \
    fputs.obj   \
    fread.obj   \
    freopen.obj \
    fscanf.obj  \
    fseek.obj   \
    fstat.obj   \
    ftime.obj   \
    fullpath.obj\
    fwrite.obj  \
    getc.obj    \
    getcwd.obj  \
    getdcwd.obj \
    getenv.obj  \
    gets.obj    \
    ldivt.obj   \
    locale.obj  \
    lock.obj    \
    locking.obj \
    lsearch.obj \
    ltoa1.obj   \
    makepath.obj\
    memccpy.obj \
    memchr.obj  \
    memcmp.obj  \
    memcpy.obj  \
    memicmp.obj \
    memset.obj  \
    mktemp.obj  \
    movedata.obj\
    movmem.obj  \
    multbyte.obj\
    open.obj    \
    opena.obj   \
    perror.obj  \
    printf.obj  \
    putc.obj    \
    putenv.obj  \
    puts.obj    \
    putw.obj    \
    qsort.obj   \
    read.obj    \
    readu.obj   \
    rename.obj  \
    rewind.obj  \
    scanf.obj   \
    setmode.obj \
    setvbuf.obj \
    splitpth.obj\
    sprintf.obj \
    sscanf.obj  \
    stat.obj    \
    strcat.obj  \
    strchr.obj  \
    strcmp.obj  \
    strcpy.obj  \
    strcspn.obj \
    strdate.obj \
    strdup.obj  \
    strerror.obj\
    stricmp.obj \
    strlen.obj  \
    strlwr.obj  \
    strncat.obj \
    strncmp.obj \
    strncpy.obj \
    strnicmp.obj\
    strnset.obj \
    strpbrk.obj \
    strrchr.obj \
    strrev.obj  \
    strset.obj  \
    strspn.obj  \
    strstr.obj  \
    strtok.obj  \
    strtol.obj  \
    strtoul.obj \
    strupr.obj  \
    swab.obj    \
    tempnam.obj \
    timecvt.obj \
    tmpfile.obj \
    tmpnam.obj  \
    tzset.obj   \
    ungetc.obj  \
    utime.obj   \
    vfprintf.obj\
    vfscanf.obj \
    vprintf.obj \
    vscanf.obj  \
    write.obj   \
    writea.obj  \
    writeu.obj  \
    xfclose.obj \
    xfflush.obj \
    _fsopen.obj

