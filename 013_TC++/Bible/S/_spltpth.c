/*
_splitpath                  �� DOS    �� UNIX     �� Windows
                            �� ANSI C �� C++ only
�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w

�y�k:

      void _splitpath(const char *path,
                      char *drive, chart *dir,
                      char *name, char *ext);

�Ѽƻ���:

      const char *path;     ���Q���Ѫ�������|�C
      char *drive;          �ϺХN�X�C
      char *dir;            �ؿ��W�١C
      char *name;           �ɮצW�١C
      char *ext;            �����ɦW�C

�\��ѻ�:

      ����Ƨ�ҶǤJ������|���Ѧ��Ϻо��N�Xdrive �B�ؿ��W��
      dir �B�ɮצW��name�B�Ω����ɦWext �C�C�@�ӹ����x�s�U��
      �ѳ����Ŷ��ܤ֭n��_MAX_DRIVE�B_MAX_DIR�B_MAX_FILE�B ��
      _MAX_EXT�Ӧ줸��, �o�Ǳ`�ƬO�w�q����J��stdlib.h���C��
      �ѫ��x�s��drive �ҫ��V���Ŷ����Ϻо��N�X, �åB�[�W�@��
      ����':' , �Ҧp "A:" , dir �ҫ��V�����@�ؿ��W��, �O���b
      �������ϰ������r��, �Ҧp "\BORLAND\BIN\", ��name���x�s
      �ɮצW��, �ܩ�ext, ��ҫ��V�����e���H�y��'.'���_�I���r
      ��, �O�ɮת������ɦW, �Ҧp".EXE" �C

���J��:

      stdlib.h

�Ǧ^��:

      �L�C

�������:

      _fullpath, _makepath

�d��:

      ���ѨϥΪ̿�J�@���㪺�ɮפθ��|�W��, �A�Q��_splitpath
      ��ƱN�ҿ�J���ɮפθ��|�W�٤��Ѧ��Ϻо��N�X�B�ؿ����|
      �B�ɦW�B�Ω����ɦW, �A�N���G��ܩ�ù��W�C
*/
/* Program : _spltpth.c */

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

void main()
{
   char fullpath[_MAX_PATH];
   char drive[_MAX_DRIVE];
   char directory[_MAX_DIR];
   char filename[_MAX_FNAME];
   char extension[_MAX_EXT];

   clrscr();
   printf("Please enter a full path :\n=>");
   gets(fullpath);

   _splitpath(fullpath, drive, directory, filename, extension);

   printf("Disc drive     = %s\n", drive);
   printf("Directory      = %s\n", directory);
   printf("File name      = %s\n", filename);
   printf("File extension = %s\n", extension);

   printf("\nPress any key to continue...");
   getch();
}
