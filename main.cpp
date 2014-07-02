// main.cpp : コンソール アプリケーション用のエントリ ポイントの定義
//

#include "stdafx.h"
#include "main.h"

void usage(void);
bool parse_cmdline( int argc, wchar_t **argv, OPTION &opt );

/* global variables */
OPTION g_option = {0};

//--------------------------------------------------------------
// main
//--------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	int i = 0;
	int retval = -1;
	FILE *console = stderr;

	setlocale(LC_CTYPE, "japanese");

	/* parse */
	if ( !parse_cmdline(argc, argv, g_option) ) {
		goto EXIT;
	}

	if ( g_option.num < 1 ) {
		fwprintf(console, L"[ERROR] too few arguments.\n");
		goto EXIT;
	}
	
	/* main */
	retval = flist( g_option.argv[0] );
	
EXIT:
	if ( g_option.wait_key_input ) {
		fputws(L"--- press any key ---\n", stdout);
		getwc(stdin);
	}

	return retval;
}

//--------------------------------------------------------------
// show usage
//--------------------------------------------------------------
void usage(void)
{
	fwprintf(stderr, L"[ %s Version %s ]\n", MODULENAME_STRING, VERSION_STRING);
	fwprintf(stderr, L"list files and directories.\n");
	fwprintf(stderr, L"\n");
	fwprintf(stderr, L"Usage : %s [option...] <target dir>\n", MODULENAME_STRING);
	fwprintf(stderr, L"        -c              : CUI mode. \n");
	fwprintf(stderr, L"        -f<a|n|r>       : specify the file path format. \n");
	fwprintf(stderr, L"                            a : absolute path. \n");
	fwprintf(stderr, L"                            n : file name only. \n");
	fwprintf(stderr, L"                            r : relative path. \n");
	fwprintf(stderr, L"        -o              : do not list files recursively. \n");
	fwprintf(stderr, L"        <target dir>    : target directory path\n");
}

//--------------------------------------------------------------
// parse command line
//--------------------------------------------------------------
bool parse_cmdline( int argc, wchar_t **argv, OPTION &opt )
{
	bool ret = true;
	wchar_t *s = NULL;

	/* initialize */
	opt.wait_key_input = true;
	opt.recursive = true;
	opt.format = OUTPUT_ABSPATH;

	/* parse */
	while ( --argc > 0 ) {
		s = *++argv;
		if ( *s == L'-' || *s == L'/' ) {
			switch ( *++s )
			{
			case L'c':
				opt.wait_key_input = false;
				break;
			case L'f':
				switch ( *++s )
				{
				case L'a':	opt.format = OUTPUT_ABSPATH;	break;
				case L'r':	opt.format = OUTPUT_RELPATH;	break;
				case L'n':	opt.format = OUTPUT_NAMEONLY;	break;
				default:	ret = false;					break;
				}
				break;
			case L'o':
				opt.recursive = false;
				break;
			case L'h':
			case L'?':
				usage();
				ret = false;
				break;
			default:
				fwprintf(stderr, L"Unknown parameter : -%s\n", s);
				ret = false;
				break;
			}
		}
		else {
			opt.num = argc;
			opt.argv = argv;
			break;
		}
	}

	return ret;
}


