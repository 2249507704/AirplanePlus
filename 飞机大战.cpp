#include"game.h"
/*
*  ��һ���ѵ㣺��Ϸ����������ô�
*  ��������� ���ݳ�ʼ����Ҫ��ʾ�Ļ��桢���û������޹صĸ��¡����û������йصĸ��¡�
*/
int main()
{
	system("mode con cols=100 lines=30");
	welcometogame();
	startup(); //���ݳ�ʼ��  ֻ��Ҫһ��
	while (1)
	{
		show();  //��ʾ����
		scoreandtips(); // ��Ϸ��ʾ
		updateWithoutInput();  //���û������޹صĸ���
		updateWithInput(); //���û������йصĸ���
	}
	return 0;
}