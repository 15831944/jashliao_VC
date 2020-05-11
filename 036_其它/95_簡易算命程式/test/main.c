#include <stdio.h>
#include <stdlib.h>
static int yearw(int y)
{
	int a = 0;
	y = (y - 12) % 60;
	switch (y)
	{
		case 1: a = 12; break;
		case 2: a = 9; break;
		case 3: a = 6; break;
		case 4: a = 7; break;
		case 5: a = 12; break;
		case 6: a = 5; break;
		case 7: a = 9; break;
		case 8: a = 8; break;
		case 9: a = 7; break;
		case 10: a = 8; break;
		case 11: a = 15; break;
		case 12: a = 9; break;
		case 13: a = 16; break;
		case 14: a = 8; break;
		case 15: a = 8; break;
		case 16: a = 19; break;
		case 17: a = 12; break;
		case 18: a = 6; break;
		case 19: a = 8; break;
		case 20: a = 7; break;
		case 21: a = 5; break;
		case 22: a = 15; break;
		case 23: a = 6; break;
		case 24: a = 16; break;
		case 25: a = 15; break;
		case 26: a = 7; break;
		case 27: a = 9; break;
		case 28: a = 12; break;
		case 29: a = 10; break;
		case 30: a = 7; break;
		case 31: a = 15; break;
		case 32: a = 6; break;
		case 33: a = 5; break;
		case 34: a = 14; break;
		case 35: a = 14; break;
		case 36: a = 9; break;
		case 37: a = 7; break;
		case 38: a = 7; break;
		case 39: a = 9; break;
		case 40: a = 12; break;
		case 41: a = 8; break;
		case 42: a = 7; break;
		case 43: a = 13; break;
		case 44: a = 5; break;
		case 45: a = 14; break;
		case 46: a = 5; break;
		case 47: a = 9; break;
		case 48: a = 17; break;
		case 49: a = 5; break;
		case 50: a = 7; break;
		case 51: a = 12; break;
		case 52: a = 8; break;
		case 53: a = 8; break;
		case 54: a = 6; break;
		case 55: a = 19; break;
		case 56: a = 6; break;
		case 57: a = 8; break;
		case 58: a = 16; break;
		case 59: a = 10; break;
		case 60: a = 7; break;
	}
    return (a);
}
static int monthw(int x)
{
	int y=0;
	switch (x)
	{
		case 1: y = 6; break;
		case 2: y = 7; break;
		case 3: y = 18; break;
		case 4: y = 9; break;
		case 5: y = 5; break;
		case 6: y = 16; break;
		case 7: y = 9; break;
		case 8: y = 15; break;
		case 9: y = 18; break;
		case 10: y = 8; break;
		case 11: y = 9; break;
		case 12: y = 5; break;

	}
	return (y);

}
static int timew(int a)
{
	int b=0;
	switch (a)
	{
		case 1: b = 16; break;
		case 2: b = 6; break;
		case 3: b = 7; break;
		case 4: b = 10; break;
		case 5: b = 9; break;
		case 6: b = 16; break;
		case 7: b = 10; break;
		case 8: b = 8; break;
		case 9: b = 8; break;
		case 10: b = 9; break;
		case 11: b = 6; break;
		case 12: b = 6; break;

	}
	return (b);

}
static int dayw(int j)
{
	int dayw=0;
	switch (j)
	{
		case 1: dayw=5; break;
		case 2: dayw=10; break;
		case 3: dayw=8; break;
		case 4: dayw=15; break;
		case 5: dayw=16; break;
		case 6: dayw=15; break;
		case 7: dayw=8 ; break;
		case 8: dayw=16; break;
		case 9: dayw=8; break;
		case 10: dayw=16; break;
		case 11: dayw=9; break;
		case 12: dayw=17; break;
		case 13: dayw=8; break;
		case 14: dayw=17; break;
		case 15: dayw=10; break;
		case 16: dayw=8; break;
		case 17: dayw=9; break;
		case 18: dayw=18; break;
		case 19: dayw=5; break;
		case 20: dayw=15; break;
		case 21: dayw=10; break;
		case 22: dayw=9; break;
		case 23: dayw=8; break;
		case 24: dayw=9; break;
		case 25: dayw=15; break;
		case 26: dayw=18; break;
		case 27: dayw=7; break;
		case 28: dayw=8; break;
		case 29: dayw=16; break;
		case 30: dayw=6; break;
	}
	return (dayw);
}
static void fatecomments(int total)
{
	printf("�z���R�歫 %d �� %d ��:\n", total/10,total%10);
	switch(total)
	{
		case 21:
			printf("�筹�b�i�X�~�������H\n");
			printf("�u�R�D�~�פj�� ���ͨa���ƭ��� �����U�{���f�� �ץ@�x�W�Ƥ���\n");
			break;
		case 22:
			printf("���~�ҸL���~�M�����H\n");
			printf("���H���N�W�D�� ���R���Ӧ�^�H �L�L�ڤڵL�פ� �צ~�����L����\n");
			break;
		case 23:
			printf("��������X�~�ϤH���R\n");
			printf("���R���Ӱ��ۻ� �D�ѧ@�ƨ����� �d��S�������\ �O�B�L�m�@���H\n");
			break;
		case 24:
			printf("�H�����h��X�a�D�����H\n");
			printf("���R���ӺָS�L ���x�x�W�`���� ���˰��׬ҵL�a �y��L�m�@�Ѻa\n");
			break;
		case 25:
			printf("�����ߤ����E�y���N���H\n");
			printf("���R���ӯ��~�L ���x��ץH�}�_ ���˰��צp�B�� �@�@�ԳҦۧ��\n");
			break;
		case 26:
			printf("�F����B���h��I�ҸL���H\n");
			printf("���ͦ�S�W���D �W����ѨƤ��� �����X���y���p �ߨӦ�S�۵L�~\n");
			break;
		case 27:
			printf("�W�s�X���o���i�Q��S���H\n");
			printf("�@�ͧ@�a�ְӶq ���a���v�@�D�i �W������Ű��h ���~�߷��`�L��\n");
			break;
		case 28:
			printf("�ۨ����H�~���Q���H\n");
			printf("�@�ͧ@�Ʀ��ƽ� ���v���~�b�ڤ� �Y���L�Ш֧�m �]�۲��{�G�T�q\n");
			break;
		case 29:
			printf("�~��ȰӦu�v�F�ܴ��z���H\n");
			printf("��~�B�������� �a���\�W�b�ᦨ �ݹL�|���~�i�W ���~��m�l���}\n");
			break;
		case 30:
			printf("�筹���l�W�ۨ��ߦ��a���R\n");
			printf("�ҳҸL�L�W���D �F����b���� �Y�l�ר��ԻP�� �Ѩӵy�i�K�~�T\n");
			break;
		case 31:
			printf("���h��I��Q���N�筹���Τ��H\n");
			printf("�����L�L�W���D ���o����a�i�� ��鶳�}����w ���~�筹���L�~\n");
			break;
		case 32:
			printf("�ʥ��L�H�ʨƺ�筹��Ѫ�Q���H\n");
			printf("��~�B�H������ �����]���p���y ��o���~�筹�� ���ɦW�Q�@����\n");
			break;
		case 33:
			printf("�筹�׺��I�Q�����N�����H\n");
			printf("���~���ƨ����� �ʭp�q�ҪP�O�� �b�@�ۦp�y���h ��ӹB��o����\n");
			break;
		case 34:
			printf("�]�B���l�D�o���U��S�I�Q���H\n");
			printf("���R�֮�G�p�� ���D������S�h �����X�a��o�� �״«��������\n");
			break;
		case 35:
			printf("���ָS��������L�ФJ�ت�I���H\n");
			printf("�ͥ��֬P���P�� ���~�ڰ�ı�ֶ� ��ƥͲP�y�u�� �ɨӦ筹�ӱq�e\n");
			break;
		case 36:
			printf("�W�s�����ĥ����z��S�p�����H\n");
			printf("�����ҸS�L���� �W�ۦ��a�֤��� �����֬P�`�өR ���g��h�ʯ릨\n");
			break;
		case 37:
			printf("�o���I�Q�~��p�����ֹؤ��H\n");
			printf("���R���Ƥ��� �̥S�֤O�۩t�� ���M���~���L�� �ӱo���h�ɱo��\n");
			break;
		case 38:
			printf("�]���׫p�y�٤��H\n");
			printf("�@�Ͱ��׳̲M�� ���J�d���m�W�� �ݬݦ~�N�T�Q�� �ŭm��h�����T\n");
			break;
		case 39:
			printf("�Q�W��Q���֦��S���H\n");
			printf("���R�ר��B���a �ҳҧ@�ƺɬҪ� �W�ߺܤO���a�p ��o���ɦb�ڤ�\n");
			break;
		case 40:
			printf("�I�Q��q�ͲP�����������R\n");
			printf("���ͦ�S�O���� ���ߤ��ۥD�i �e�������h���L ��ӥ��w�ɦw�d\n");
			break;
		case 41:
			printf("�|���Q�M�~���H��S���H\n");
			printf("���R���ӨƤ��P ���H��F���Z�e ���~�٦��p���� ����e�~�B���q\n");
			break;
		case 42:
			printf("�L�v��¾�I�Q�~�ध�H\n");
			printf("�o�e�h�B�B�e�h ��ΰ����ͤ��} �Y�Ϥ��~�R�B�� ���ɦW�Q�@����\n");
			break;
		case 43:
			printf("�]�L�p���դ⦨�a���H\n");
			printf("���H�ߩʳ��o�� �@�ưa����Q�H ��S�@�ͤѼƩw �����ҸL�O�צ�\n");
			break;
		case 44:
			printf("�n�Ǫ�Q�����]�S�I�p���H\n");
			printf("�ӨƥѤѲ��W�D �����ָS�ӫe�~ ��~�]�����p�N �ߴ��Y�M�K���~\n");
			break;
		case 45:
			printf("�ָS�׫p���I�B�Q���H\n");
			printf("�W�Q���ӳ��Y�L �e�~���W��b�i �R�����i�k�P�k ���ק߫��]���h\n");
			break;
		case 46:
			printf("�I�Q���l�ֹ��������R\n");
			printf("�F��n�_�ɬҹD �X�m���W��ı�� ��S�L���ѼƩw ���~�ߴ��@��P\n");
			break;
		case 47:
			printf("���x�S�p�Ƿ~�������H\n");
			printf("���R���ө����~ �d�a�l�Q�۩ɵM ���ͭ즳�ʷʺ� �i���]���p����\n");
			break;
		case 48:
			printf("�x���]�S�p�����H\n");
			printf("���~�B�D�Ҵ��� �Y�O�ζY�A���P �S�̤��ˬҵL�a �@���Ʒ~�ߦ~��\n");
			break;
		case 49:
			printf("�ʥ��믫�ܮw�]�S���R\n");
			printf("���R���Ӻ֤��� �ۦ��ۥ��U���x �q�ӴI�Q�H�˪� �ϱA�t���L�@��\n");
			break;
		case 50:
			printf("��Z�~����B�ײ����H\n");
			printf("���Q���W�פ�� ���~�ָS�]�h�D �ѨӬO���]�P�� ����e�f�ؤU��\n");
			break;
		case 51:
			printf("�S�p�x¾�]�S�a�شI�Q���R\n");
			printf("�@�@�a�بƨƳq �����ҸL�ۦ�q �̥S�����Ҧp�N �a�~���ɺָS��\n");
			break;
		case 52:
			printf("�x���L�v�I�Q���ؤ��H\n");
			printf("�@�@��q�ƨƯ� �����ҫ�۵M�� �v�ڪY�M�߬Ҧn �a�~�צ�ۺ٤�\n");
			break;
		case 53:
			printf("�C��Q�H���D������Q���H \n");
			printf("������Ӯ�H�u ���a�o�F�b�䤤 �@�ͺָS�w�Ʃw �o�O�H���@�I��\n");
			break;
		case 54:
			printf("���i���ѫ��v�I�Q�]�S���R\n");
			printf("���R���ӫp�B�M �֮Ѻ����ݥ\�� �צ稬���۵Mí ���O�H�����֤H\n");
			break;
		case 55:
			printf("�K�~�x¾�]�S�ײ����H\n");
			printf("�������䪧�Q�W �֦~���ƶO�w�� �@�ºָS������ �I�Q�a���㤻��\n");
			break;
		case 56:
			printf("�C�~�x¾���ɺa�شI�Q\n");
			printf("�������§�q�q �@�ͺָS�εL�� ���ĭW�����|�� �]���u�uí�B��\n");
			break;
		case 57:
			printf("���~�x¾�峹������q���H\n");
			printf("�ָS�լոU�ƥ� �@�ͺaģ������ �W���®��H�ܷq �B�@�p�����J�K\n");
			break;
		case 58:
			printf("�x�S���ۤ~��ʪ��I�Q���H\n");
			printf("�ͥ��ָS�۵M�� �W�Q�ݥ��ֹذ� ���𴣦W���Q�� ���T���a����\n");
			break;
		case 59:
			printf("���~�x¾�]�S�p�����H\n");
			printf("�ӱ����槮�B�M ���w�]��§�q�q �ҲĤ��������� ���@������³�\n");
			break;
		case 60:
			printf("�|�~�x¾�a�غֹذ]�S���H\n");
			printf("�@�ª��]�ִ��W �㯪�a�v�ߤj�� �筹�w�M��Ψ� �ж�]�����׬�\n");
			break;
		case 61:
			printf("�k���x�x���p�v�`���H\n");
			printf("���@�¤����]�J �w���@�W�@�]�� �o���ѥI�g�Ѽ� ���㰪��جO�a\n");
			break;
		case 62:
			printf("�T�~�x¾���v�`���H\n");
			printf("���R�ͨӺ֤��a Ū�ѥ��w��˺a ���]���a�ӭ�� �I�Q�a�جҥi�P\n");
			break;
		case 63:
			printf("�����Ӧu�U��ʫJ���R\n");
			printf("�R�D���x�ָS�� �o�ӺֶQ���D�` �R�D����Ǫ��� �w������ѤU��\n");
			break;
		case 64:
			printf("�G�~�x¾�|�ѭ����R\n");
			printf("������v���i�� ���T���a������ �a�شI�Q�֤H�� �n�ɰ�����x��\n");
			break;
		case 65:
			printf("�x���v�·��j���ָS���H\n");
			printf("�ӱ����R�֤��� �w��w�����~�H ��¸�J�ٷL�I�Q ���n��ģ�|��D\n");
			break;
		case 66:
			printf("���J�t���A�ۤ��R\n");
			printf("����H���@�֤H ����n�ɺ���K �q�ӴI�Q�Ѥѩw ���C�����ָt�g\n");
			break;
		case 67:
			printf("�^�W�a�@�U��Ӵ¤��H\n");
			printf("���R�ͨӺ֦ۧ� �ж�a�~�̰��� ���ͦ�S�׬ը� �@�ͺa�ظU�Ƴq\n");
			break;
		case 68:
			printf("�ũM�I�Q�c�a���N���R\n");
			printf("�I�Q�ѤѤ����D �U���a�p�۵M�� �Q�~����e�f�� ���~�ڰ���W��\n");
			break;
		case 69:
			printf("�f������\�W��F���R\n");
			printf("�g�O�H����S�P �@�ʹI�Q���H�� �w�M�ָS�Ѥѩw �w�ɺa�عL�@��\n");
			break;
		case 70:
			printf("�v�O��Ʒ��~�W�y���R\n");
			printf("���R���Ӻ֤��� �����T�{�W�Ҥ� �@�ͤѩw��S�� �I�Q�a�إD�@��\n");
			break;
		case 71:
			printf("���D�j�Ӥj�~�զp�}�ˤ��R�]\n");
			printf("���R�ͨӤj���P ���J�N�ۦb�䤤 �@�ͦۦ��p���� �I�Q�a�خ��~��\n");
			break;
		case 72:
			printf("���D�u���ͫҤ����R�]\n");
			printf("���ߧA���ֳz!!\n");
			break;
		default: break;

	}
}
static int chinese_animal(int w)
{

	w = (w < 0) ? w + 1 : w;
	w = w % 12;
	w = (w <= 0) ? w + 12 : w;
	//�]���l�Ƭ�0�A�ҥH�S���o�檺�ܡA�l�Ƭ�0�X����


	return (w);
}
static void output(int y)
{
	switch (y)
	{
		case 1: printf("�ͨv:��\n"); break;
		case 2: printf("�ͨv:��\n"); break;
		case 3: printf("�ͨv:��\n"); break;
		case 4: printf("�ͨv:��\n"); break;
		case 5: printf("�ͨv:�s\n"); break;
		case 6: printf("�ͨv:�D\n"); break;
		case 7: printf("�ͨv:��\n"); break;
		case 8: printf("�ͨv:��\n"); break;
		case 9: printf("�ͨv:�U\n"); break;
		case 10: printf("�ͨv:��\n"); break;
		case 11: printf("�ͨv:��\n"); break;
		case 12: printf("�ͨv:��\n"); break;
	}
}
int main()
{
    int y=0,m=0,d=0,t=0;
	int yw, mw, dw, tw, total;
    printf("Hello world!\n");
	printf("��J�ͦ~(����):\n");
	scanf("%d",&y);
	printf("��J�ͤ�(�¾�):\n");
	scanf("%d",&m);
	printf("��J�ͤ�(�¾�):\n");
	scanf("%d",&d);
	printf("��J�ͮ�(24��):\n");
	scanf("%d",&t);
	yw = yearw(y);   //�ͦ~���
	mw = monthw(m);  //�ͤ���
	dw = dayw(d);  //�ͤ���
	tw = timew(t);  //�ͨ����
	total = yw+mw+dw+tw;
	output(chinese_animal(y));
	fatecomments(total);  //�`��ƩM���y
    return 0;
}
