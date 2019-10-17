//  NOTIMP.CPP
//
//  Generates .ASM files for functions not implemented in windows,
//  along with linker response file (NOTIMP.RSP) which will pull
//  all the .OBJ files into a lib.
//
//  Usage:
//
//  NOTIMP < NOTIMP.LST
//
//  tasm *.asm
//
//  TLIB cwins @NOTIMP.RSP

#include <string.h>
#include <fstream.h>

int started = 0;
ofstream rsp( "notimp.rsp" );

char fileName[] = "notimpaa";
void nextName()
{
    if( ++fileName[7] > 'z' )
        {
        fileName[7] = 'a';
        fileName[6]++;
        }
}

void genProg( const char *func )
{
    char name[ 20 ];
    strcpy( name, fileName );
    strcat( name, ".asm" );
    cerr << func << endl;
    ofstream out( name );
    out << "_TEXT   segment" << endl;
    out << "        assume CS:_TEXT" << endl << endl;
    out << "extrn   " << func << "_Not_Windows" << endl << endl;
    out << "public  _" << func << endl;
    out << "_" << func << ":" << endl;
    out << "        call " << func << "_Not_Windows" << endl;
    out << "        ends" << endl;
    out << "        end" << endl;
    strcpy( name, fileName );
    if( started != 0 )
        rsp << " &" << endl;
    else
        started = 1;
    rsp << "+" << name;
    nextName();
}

int main()
{
    char name[ 128 ];
    cin >> name;
    while( !cin.eof() )
        {
        genProg( name );
        cin >> name;
        }
    return 0;
}


