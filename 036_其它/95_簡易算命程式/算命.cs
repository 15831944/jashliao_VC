/*http://www.7headlines.com/article/show/247091944*/
static void Main(string[] args)
{
	int y=0,m=0,d=0,t=0;
	int yw, mw, dw, tw, total;
	Console.Write("��J�ͦ~(����):");
	y = Convert.ToInt32(Console.ReadLine());
	Console.Write("��J�ͤ�(�¾�):");
	m = Convert.ToInt32(Console.ReadLine());
	Console.Write("��J�ͤ�(�¾�):");
	d = Convert.ToInt32(Console.ReadLine());
	Console.Write("��J�ͮ�(24��):");
	t = Convert.ToInt32(Console.ReadLine());
	yw = yearw(y);   //�ͦ~���
	mw = monthw(m);  //�ͤ���
	dw = dayw(d);  //�ͤ���
	tw = timew(t);  //�ͨ����
	total = yw+mw+dw+tw;
	fatecomments(total);  //�`��ƩM���y
}
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
	Console.WriteLine("�z���R�歫{0}��{1}��:", total/10,total%10);
	switch(total)
	{
		case 21:
			Console.WriteLine("�筹�b�i�X�~�������H");
			Console.WriteLine("�u�R�D�~�פj�� ���ͨa���ƭ��� �����U�{���f�� �ץ@�x�W�Ƥ���");
			break;
		case 22:
			Console.WriteLine("���~�ҸL���~�M�����H");
			Console.WriteLine("���H���N�W�D�� ���R���Ӧ�^�H �L�L�ڤڵL�פ� �צ~�����L����");
			break;
		case 23:
			Console.WriteLine("��������X�~�ϤH���R");
			Console.WriteLine("���R���Ӱ��ۻ� �D�ѧ@�ƨ����� �d��S�������\ �O�B�L�m�@���H");
			break;
		case 24:
			Console.WriteLine("�H�����h��X�a�D�����H");
			Console.WriteLine("���R���ӺָS�L ���x�x�W�`���� ���˰��׬ҵL�a �y��L�m�@�Ѻa");
			break;
		case 25:
			Console.WriteLine("�����ߤ����E�y���N���H");
			Console.WriteLine("���R���ӯ��~�L ���x��ץH�}�_ ���˰��צp�B�� �@�@�ԳҦۧ��");
			break;
		case 26:
			Console.WriteLine("�F����B���h��I�ҸL���H");
			Console.WriteLine("���ͦ�S�W���D �W����ѨƤ��� �����X���y���p �ߨӦ�S�۵L�~");
			break;
		case 27:
			Console.WriteLine("�W�s�X���o���i�Q��S���H");
			Console.WriteLine("�@�ͧ@�a�ְӶq ���a���v�@�D�i �W������Ű��h ���~�߷��`�L��");
			break;
		case 28:
			Console.WriteLine("�ۨ����H�~���Q���H");
			Console.WriteLine("�@�ͧ@�Ʀ��ƽ� ���v���~�b�ڤ� �Y���L�Ш֧�m �]�۲��{�G�T�q");
			break;
		case 29:
			Console.WriteLine("�~��ȰӦu�v�F�ܴ��z���H");
			Console.WriteLine("��~�B�������� �a���\�W�b�ᦨ �ݹL�|���~�i�W ���~��m�l���}");
			break;
		case 30:
			Console.WriteLine("�筹���l�W�ۨ��ߦ��a���R");
			Console.WriteLine("�ҳҸL�L�W���D �F����b���� �Y�l�ר��ԻP�� �Ѩӵy�i�K�~�T");
			break;
		case 31:
			Console.WriteLine("���h��I��Q���N�筹���Τ��H");
			Console.WriteLine("�����L�L�W���D ���o����a�i�� ��鶳�}����w ���~�筹���L�~");
			break;
		case 32:
			Console.WriteLine("�ʥ��L�H�ʨƺ�筹��Ѫ�Q���H");
			Console.WriteLine("��~�B�H������ �����]���p���y ��o���~�筹�� ���ɦW�Q�@����");
			break;
		case 33:
			Console.WriteLine("�筹�׺��I�Q�����N�����H");
			Console.WriteLine("���~���ƨ����� �ʭp�q�ҪP�O�� �b�@�ۦp�y���h ��ӹB��o����");
			break;
		case 34:
			Console.WriteLine("�]�B���l�D�o���U��S�I�Q���H");
			Console.WriteLine("���R�֮�G�p�� ���D������S�h �����X�a��o�� �״«��������");
			break;
		case 35:
			Console.WriteLine("���ָS��������L�ФJ�ت�I���H");
			Console.WriteLine("�ͥ��֬P���P�� ���~�ڰ�ı�ֶ� ��ƥͲP�y�u�� �ɨӦ筹�ӱq�e");
			break;
		case 36:
			Console.WriteLine("�W�s�����ĥ����z��S�p�����H");
			Console.WriteLine("�����ҸS�L���� �W�ۦ��a�֤��� �����֬P�`�өR ���g��h�ʯ릨");
			break;
		case 37:
			Console.WriteLine("�o���I�Q�~��p�����ֹؤ��H");
			Console.WriteLine("���R���Ƥ��� �̥S�֤O�۩t�� ���M���~���L�� �ӱo���h�ɱo��");
			break;
		case 38:
			Console.WriteLine("�]���׫p�y�٤��H");
			Console.WriteLine("�@�Ͱ��׳̲M�� ���J�d���m�W�� �ݬݦ~�N�T�Q�� �ŭm��h�����T");
			break;
		case 39:
			Console.WriteLine("�Q�W��Q���֦��S���H");
			Console.WriteLine("���R�ר��B���a �ҳҧ@�ƺɬҪ� �W�ߺܤO���a�p ��o���ɦb�ڤ�");
			break;
		case 40:
			Console.WriteLine("�I�Q��q�ͲP�����������R");
			Console.WriteLine("���ͦ�S�O���� ���ߤ��ۥD�i �e�������h���L ��ӥ��w�ɦw�d");
			break;
		case 41:
			Console.WriteLine("�|���Q�M�~���H��S���H");
			Console.WriteLine("���R���ӨƤ��P ���H��F���Z�e ���~�٦��p���� ����e�~�B���q");
			break;
		case 42:
			Console.WriteLine("�L�v��¾�I�Q�~�ध�H");
			Console.WriteLine("�o�e�h�B�B�e�h ��ΰ����ͤ��} �Y�Ϥ��~�R�B�� ���ɦW�Q�@����");
			break;
		case 43:
			Console.WriteLine("�]�L�p���դ⦨�a���H");
			Console.WriteLine("���H�ߩʳ��o�� �@�ưa����Q�H ��S�@�ͤѼƩw �����ҸL�O�צ�");
			break;
		case 44:
			Console.WriteLine("�n�Ǫ�Q�����]�S�I�p���H");
			Console.WriteLine("�ӨƥѤѲ��W�D �����ָS�ӫe�~ ��~�]�����p�N �ߴ��Y�M�K���~");
			break;
		case 45:
			Console.WriteLine("�ָS�׫p���I�B�Q���H");
			Console.WriteLine("�W�Q���ӳ��Y�L �e�~���W��b�i �R�����i�k�P�k ���ק߫��]���h");
			break;
		case 46:
			Console.WriteLine("�I�Q���l�ֹ��������R");
			Console.WriteLine("�F��n�_�ɬҹD �X�m���W��ı�� ��S�L���ѼƩw ���~�ߴ��@��P");
			break;
		case 47:
			Console.WriteLine("���x�S�p�Ƿ~�������H");
			Console.WriteLine("���R���ө����~ �d�a�l�Q�۩ɵM ���ͭ즳�ʷʺ� �i���]���p����");
			break;
		case 48:
			Console.WriteLine("�x���]�S�p�����H");
			Console.WriteLine("���~�B�D�Ҵ��� �Y�O�ζY�A���P �S�̤��ˬҵL�a �@���Ʒ~�ߦ~��");
			break;
		case 49:
			Console.WriteLine("�ʥ��믫�ܮw�]�S���R");
			Console.WriteLine("���R���Ӻ֤��� �ۦ��ۥ��U���x �q�ӴI�Q�H�˪� �ϱA�t���L�@��");
			break;
		case 50:
			Console.WriteLine("��Z�~����B�ײ����H");
			Console.WriteLine("���Q���W�פ�� ���~�ָS�]�h�D �ѨӬO���]�P�� ����e�f�ؤU��");
			break;
		case 51:
			Console.WriteLine("�S�p�x¾�]�S�a�شI�Q���R");
			Console.WriteLine("�@�@�a�بƨƳq �����ҸL�ۦ�q �̥S�����Ҧp�N �a�~���ɺָS��");
			break;
		case 52:
			Console.WriteLine("�x���L�v�I�Q���ؤ��H");
			Console.WriteLine("�@�@��q�ƨƯ� �����ҫ�۵M�� �v�ڪY�M�߬Ҧn �a�~�צ�ۺ٤�");
			break;
		case 53:
			Console.WriteLine("�C��Q�H���D������Q���H ");
			Console.WriteLine("������Ӯ�H�u ���a�o�F�b�䤤 �@�ͺָS�w�Ʃw �o�O�H���@�I��");
			break;
		case 54:
			Console.WriteLine("���i���ѫ��v�I�Q�]�S���R");
			Console.WriteLine("���R���ӫp�B�M �֮Ѻ����ݥ\�� �צ稬���۵Mí ���O�H�����֤H");
			break;
		case 55:
			Console.WriteLine("�K�~�x¾�]�S�ײ����H");
			Console.WriteLine("�������䪧�Q�W �֦~���ƶO�w�� �@�ºָS������ �I�Q�a���㤻��");
			break;
		case 56:
			Console.WriteLine("�C�~�x¾���ɺa�شI�Q");
			Console.WriteLine("�������§�q�q �@�ͺָS�εL�� ���ĭW�����|�� �]���u�uí�B��");
			break;
		case 57:
			Console.WriteLine("���~�x¾�峹������q���H");
			Console.WriteLine("�ָS�լոU�ƥ� �@�ͺaģ������ �W���®��H�ܷq �B�@�p�����J�K");
			break;
		case 58:
			Console.WriteLine("�x�S���ۤ~��ʪ��I�Q���H");
			Console.WriteLine("�ͥ��ָS�۵M�� �W�Q�ݥ��ֹذ� ���𴣦W���Q�� ���T���a����");
			break;
		case 59:
			Console.WriteLine("���~�x¾�]�S�p�����H");
			Console.WriteLine("�ӱ����槮�B�M ���w�]��§�q�q �ҲĤ��������� ���@������³�");
			break;
		case 60:
			Console.WriteLine("�|�~�x¾�a�غֹذ]�S���H");
			Console.WriteLine("�@�ª��]�ִ��W �㯪�a�v�ߤj�� �筹�w�M��Ψ� �ж�]�����׬�");
			break;
		case 61:
			Console.WriteLine("�k���x�x���p�v�`���H");
			Console.WriteLine("���@�¤����]�J �w���@�W�@�]�� �o���ѥI�g�Ѽ� ���㰪��جO�a");
			break;
		case 62:
			Console.WriteLine("�T�~�x¾���v�`���H");
			Console.WriteLine("���R�ͨӺ֤��a Ū�ѥ��w��˺a ���]���a�ӭ�� �I�Q�a�جҥi�P");
			break;
		case 63:
			Console.WriteLine("�����Ӧu�U��ʫJ���R");
			Console.WriteLine("�R�D���x�ָS�� �o�ӺֶQ���D�` �R�D����Ǫ��� �w������ѤU��");
			break;
		case 64:
			Console.WriteLine("�G�~�x¾�|�ѭ����R");
			Console.WriteLine("������v���i�� ���T���a������ �a�شI�Q�֤H�� �n�ɰ�����x��");
			break;
		case 65:
			Console.WriteLine("�x���v�·��j���ָS���H");
			Console.WriteLine("�ӱ����R�֤��� �w��w�����~�H ��¸�J�ٷL�I�Q ���n��ģ�|��D");
			break;
		case 66:
			Console.WriteLine("���J�t���A�ۤ��R");
			Console.WriteLine("����H���@�֤H ����n�ɺ���K �q�ӴI�Q�Ѥѩw ���C�����ָt�g");
			break;
		case 67:
			Console.WriteLine("�^�W�a�@�U��Ӵ¤��H");
			Console.WriteLine("���R�ͨӺ֦ۧ� �ж�a�~�̰��� ���ͦ�S�׬ը� �@�ͺa�ظU�Ƴq");
			break;
		case 68:
			Console.WriteLine("�ũM�I�Q�c�a���N���R");
			Console.WriteLine("�I�Q�ѤѤ����D �U���a�p�۵M�� �Q�~����e�f�� ���~�ڰ���W��");
			break;
		case 69:
			Console.WriteLine("�f������\�W��F���R");
			Console.WriteLine("�g�O�H����S�P �@�ʹI�Q���H�� �w�M�ָS�Ѥѩw �w�ɺa�عL�@��");
			break;
		case 70:
			Console.WriteLine("�v�O��Ʒ��~�W�y���R");
			Console.WriteLine("���R���Ӻ֤��� �����T�{�W�Ҥ� �@�ͤѩw��S�� �I�Q�a�إD�@��");
			break;
		case 71:
			Console.WriteLine("���D�j�Ӥj�~�զp�}�ˤ��R�]");
			Console.WriteLine("���R�ͨӤj���P ���J�N�ۦb�䤤 �@�ͦۦ��p���� �I�Q�a�خ��~��");
			break;
		case 72:
			Console.WriteLine("���D�u���ͫҤ����R�]");
			Console.WriteLine("���ߧA���ֳz!!");
			break;
		default: break;
		   
	}
}
static void Main(string[] args)
{
	int i, j;
	Console.Write("��J�ͦ~(����):");
	i = Convert.ToInt32(Console.ReadLine());
	j = chinese_animal(i);
	Console.WriteLine("{0}", j);
	output(j);

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
		case 1: Console.Write("�ͨv:��"); break;
		case 2: Console.Write("�ͨv:��"); break;
		case 3: Console.Write("�ͨv:��"); break;
		case 4: Console.Write("�ͨv:��"); break;
		case 5: Console.Write("�ͨv:�s"); break;
		case 6: Console.Write("�ͨv:�D"); break;
		case 7: Console.Write("�ͨv:��"); break;
		case 8: Console.Write("�ͨv:��"); break;
		case 9: Console.Write("�ͨv:�U"); break;
		case 10: Console.Write("�ͨv:��"); break;
		case 11: Console.Write("�ͨv:��"); break;
		case 12: Console.Write("�ͨv:��"); break;
	}
}