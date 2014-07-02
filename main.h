#ifndef __MAIN_H__
#define __MAIN_H__

#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>

#define GET_ERROR_VAL( val )	((val) = -1 * __LINE__)


/*----------------------------------------*/
/* �v���O�������A�o�[�W����               */
/*----------------------------------------*/
#define MODULENAME_STRING	L"flist"
#define VERSION_STRING		L"0.01"


typedef enum {
	OUTPUT_ABSPATH = 0,
	OUTPUT_RELPATH,
	OUTPUT_NAMEONLY
} PATHFORMAT;

/*----------------------------------------*/
/* �R�}���h���C����͌��ʂ��i�[����\���� */
/*----------------------------------------*/
typedef struct tagOPTION {
	int			num;					/* number of input files */
	_TCHAR**	argv;					/* pointer to a file name array */
	bool		wait_key_input;			/* if true, wait key input */
	bool		recursive;				/* list files recursively */
	PATHFORMAT	format;					/* output path format */
} OPTION;

extern OPTION g_option;
inline OPTION *opt() { return &g_option; }

/*----------------------------------------*/
/* �֐��̃v���g�^�C�v�錾                 */
/*----------------------------------------*/
int flist( const wchar_t *pszDir );


#endif /* __MAIN_H__ */
