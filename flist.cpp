// flist.cpp : 
//

#include "stdafx.h"
#include "main.h"
#include <io.h>

size_t list_in_dir( wchar_t *buffer, size_t len );
size_t list_recursive( wchar_t *buffer, size_t len, size_t init_len );


//----------------------------------------------------------------------
//! @brief  list files.
//! @param  pszDir	 [in] a target path.
//! @param  opt	     [in] options.
//! @return 
//----------------------------------------------------------------------
int flist( const wchar_t *pszDir )
{
	wchar_t buffer[260] = L"";


	wcscpy(buffer, pszDir);
	
	if ( opt()->recursive ) {
		list_recursive( buffer, wcslen(buffer), wcslen(buffer) ); 
	}
	else {
		list_in_dir( buffer, wcslen(buffer) );
	}

	return 0;
}

//----------------------------------------------------------------------
//! @brief  list files in a directory.
//! @param  buffer	 [in] a buffer, which is set a target path.
//! @param  len	     [in] length of a target path, in characters.
//! @return count of listed files.
//----------------------------------------------------------------------
size_t list_in_dir( wchar_t *buffer, size_t len )
{
	size_t file_count = 0;
	long lHandle = 0;
	struct _wfinddata_t tFiles = {0};

	wcscpy( buffer + len, L"\\*" );

	lHandle = _wfindfirst( buffer, &tFiles );
	if ( lHandle != -1L )
	{
		do {
			if ( wcscmp( tFiles.name, L"." ) == 0 ) continue;
			if ( wcscmp( tFiles.name, L".." ) == 0 ) continue;

			wcscpy( buffer + len + 1, tFiles.name );
			switch ( opt()->format )
			{
			case OUTPUT_NAMEONLY:	fputws( tFiles.name, stdout );				break;
			case OUTPUT_RELPATH:	fputws( buffer + len + 1, stdout );			break;
			default:				fputws( buffer, stdout );					break;
			}
			fputws( L"\n", stdout );
			file_count++;
		} while ( _wfindnext( lHandle, &tFiles ) == 0 );

		_findclose( lHandle );
	}
	
	return file_count;
}


//----------------------------------------------------------------------
//! @brief  list files recursively.
//! @param  buffer	 [in] a buffer, which is set a target path.
//! @param  len	     [in] length of a target path, in characters.
//! @param  init_len [in] initial length of a target path, in characters.
//! @return count of listed files.
//----------------------------------------------------------------------
size_t list_recursive( wchar_t *buffer, size_t len, size_t init_len )
{
	size_t file_count = 0;
	long lHandle = 0;
	struct _wfinddata_t tFiles = {0};
	size_t suffix_len = 0;

	wcscpy( buffer + len, L"\\*" );

	lHandle = _wfindfirst( buffer, &tFiles );
	if ( lHandle != -1L )
	{
		do {
			if ( wcscmp( tFiles.name, L"." ) == 0 ) continue;
			if ( wcscmp( tFiles.name, L".." ) == 0 ) continue;

			if ( tFiles.attrib & _A_SUBDIR ) 
			{
				/* find sub-directory */
				suffix_len = wcslen(tFiles.name);
				wcscpy( buffer + len + 1, tFiles.name );
				list_recursive( buffer, len + 1 + suffix_len, init_len );
			}
			else 
			{
				wcscpy( buffer + len + 1, tFiles.name );
				switch ( opt()->format )
				{
				case OUTPUT_NAMEONLY:	fputws( tFiles.name, stdout );				break;
				case OUTPUT_RELPATH:	fputws( buffer + init_len + 1, stdout );	break;
				default:				fputws( buffer, stdout );					break;
				}
				fputws( L"\n", stdout );
				file_count++;
			}
		} while ( _wfindnext( lHandle, &tFiles ) == 0 );

		_findclose( lHandle );
	}
	
	return file_count;
}
