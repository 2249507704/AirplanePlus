#include"game.h"
//��Ϸ��ʼ��
int position_x, position_y;     //�ɻ�λ��
int bullit_x, bullit_y;         //�ӵ�λ��
int enemy_x[NUM], enemy_y[NUM]; // ��̨����
int BulletWidth;                // �ӵ����  �ڳ�ʼ����������г�ʼ��
int EnemyMoveSpeed;             // �����ƶ��ٶ�

//int high, width; //�����С
int score; //��÷���
int canvas[high][width] = {0};  //�ö�ά�����¼��Ϸ�����ж�Ӧ��Ԫ�� ���Ҹ�����ʼ��Ϊ0����ո�1����ɻ� 2����ӵ� 3�������
 // �Ѷ�ά�����ʼ��Ϊ0
/*
*  -----------
* |    |     |
* |    |     |
* |    |x    |
* |    |   y |
* |    $-----|
* ------------
* 
* 
*/
/**
 * ������ɫ����
 */
int color(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);    //����������ɫ
	return 0;
}
void gotoxy(int x, int y)//����ƶ���xy��λ��  Ҫ��ͷ�ļ�windows.h
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

//��������˸�ĺ���
void HideCursor()//���ع�� ִ��һ�ξ��� ���ڳ�ʼ������
{
	CONSOLE_CURSOR_INFO cursor_infor = { 1,0 }; //�ڶ���ֵΪ0��ʾ���ع��
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_infor);
}

void welcometogame() //��ʼ����
{
	int n;
	color(15);
	gotoxy(43, 10);
	printf("�� �� �� ս");
	color(11);
	gotoxy(25, 22);
	printf("1.��ʼ��Ϸ");
	gotoxy(45, 22);
	printf("2.��Ϸ˵��");
	gotoxy(65, 22);
	printf("3.�˳���Ϸ");
	gotoxy(40, 27);
	color(3);
	printf("��ѡ�� 1 2 3:");
	color(14);
	cin >> n;  //����ѡ��
	switch (n)
	{
	case 1:
		system("cls");
		show();
		break;
	case 2:
		explation();    //��Ϸ˵������
		break;
	case 3:
		exit(0);    //�˳���Ϸ
		break;
	default:
		color(12);
		gotoxy(40, 28);
		printf("������1-3֮�����!");
		_getch();  //���������
		system("cls"); //����
		welcometogame();
	}
}

void explation() //��Ϸ��ʾ 
{
	int i, j = 1;
	system("cls");
	color(10);
	gotoxy(44, 1);
	printf("��Ϸ˵��");
	color(2);
	for (i = 3; i <= 28; i++)  //������±߿�===
	{
		for (j = 6; j <= 80; j++) //������ұ߿�||
		{
			gotoxy(j, i);
			if (i == 3 || i == 28) printf("=");
			else if (j == 6 || j == 80) printf("||");
		}
	}
	color(3);
	gotoxy(20, 5);
	printf("1. W,A,S,D �ֱ���Ʒɻ������������ƶ�");
	color(10);
	gotoxy(20, 8);
	printf("2. ���ո����ӵ������ел����ɵõ�һ��");
	color(14);
	gotoxy(20, 11);
	printf("3.�����л��ӵ�����");
	color(11);
	gotoxy(20, 14);
	printf("4. ESC ���˳���Ϸ");
	color(4);
	gotoxy(20, 17);
	printf("5. �����죡����");
	color(7);
	gotoxy(20, 20);
	printf("/*****�������������ҳ��*****/");
	_getch();        //�����������������
	system("cls");
	welcometogame();
}

void scoreandtips()//��Ϸ�����ʾ 
{
	gotoxy(50, 8);
	color(14);
	printf("��Ϸ�÷֣�%d ", score);
	gotoxy(50, 10);
	printf("��W A S D �ֱ���Ʒɻ����ƶ�");
	gotoxy(50, 12);
	printf("���¿ո����Ϊ�����ڵ�");
	gotoxy(50, 14);
	printf("@ �����Ӿ��ǵ��˵ķɻ�");
	gotoxy(50, 16);
	printf("����k ��ͣ��Ϸ");
}
//��ʼ�����ݵĺ���
void startup()
{
	//�ɻ�λ�� ��ʼ���ɻ�λ��  �÷ɻ�һ��ʼ����Ļ�м�
	position_x = high / 2;
	position_y = width / 2;

	/*
	*  �Ȱѷɻ���������ʣ�µ��йطɻ������в��������ڷɻ�λ���Ͻ��е�
	*/

	//���Ҫ�����ά���� ��ʼ���ɻ�λ�� 
	canvas[position_x][position_y] = 1;

	//��ʼ������λ��
	for (int k = 0; k < NUM; k++)
	{
		/* ����õ���������� */
		enemy_x[k] = rand() % 3;
		enemy_y[k] = rand() % width; // ��0��width-1
		canvas[enemy_x[k]][enemy_y[k]] = 3; // �ѳ��ֵĵ���λ�ø�ֵ��3
	}

	//�ӵ�λ��
	/*bullit_x = -1;  // һ��ʼ�ӵ�������ڶ��� Ϊ�˱��� ������ʼ��Ϊ-1
	bullit_y = position_y;*/
	canvas[bullit_x][bullit_y] = 2;

	EnemyMoveSpeed = 10; // ��ʼ�������ƶ��ٶ�

	BulletWidth = 0; // ��ʼ���ӵ����
	//��ʼ����
	score = 0;

	HideCursor();  //�������ֻ��Ҫִ��һ��  ���Է��ڳ�ʼ���ͺ�
}

//�ں��ʵ�λ���ҵ��ɻ�
void show()
{
	gotoxy(0, 0); //����ƶ���ԭ��λ�ã������ػ�����
	//system("cls"); //��������  �������������һ��һ�� �ϱ���һ��gotoxy(int x,int y)�ĺ���������

	for (int i = 0; i < high; i++)
	{
		for (int j = 0; j < width; j++)
		{
			// ������������ �ڶ�ά�����б�������Ӧ�ķɻ�������� ���丳ֵΪ1
			// ��ά����Ϊ1 ����ɻ�  Ϊ2 ����ӵ�  Ϊ3 ��������
			if (canvas[i][j] == 1)// �����հ�λ�� �������ɻ���λ�þʹ�ӡ����
			{
				printf("*");  //����ɻ�
			}
			else if (canvas[i][j] == 2)
			{
				printf("|"); //����ӵ�
			}
			else if (canvas[i][j] == 3)
			{
				printf("@");
			}
			else
				printf(" ");
		}
		printf("\n");
	}

	printf("�÷֣�%d\n", score);
}

//�������޹صĺ���
void updateWithoutInput()
{
	//���� ������ʱ�� �ɻ��͵��˶������� ������� ���� һ����̬����

	//���ӵ������ƶ�
	for (int i = 0; i < high; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (canvas[i][j] == 2)
			{
				for (int k = 0; k < NUM; k++)
				{
					if ((i == enemy_x[k]) && (j == enemy_y[k])) // �ӵ��͵��˵�������� ���е���
					{
						score++; //�ӷ�
						if (score % 5 == 0 && EnemyMoveSpeed > 3) // �ﵽһ�����ֺ�л����Լ���
						{
							EnemyMoveSpeed--;
						}
						if (score % 5 == 0) {
							// �ﵽһ�����ֺ��ӵ����
							BulletWidth++;
							if (BulletWidth >= 5) {
								BulletWidth = 5;
							}
						}
						canvas[enemy_x[k]][enemy_y[k]] = 0;  //�õ��˹���
						//�����������
						enemy_x[k] = 0;
						enemy_y[k] = rand() % width;
						canvas[enemy_x[k]][enemy_y[k]] = 3;  //��ʾ�����ĵ���
						
					}
				}
				canvas[i][j] = 0;  //�������ɻ����ӵ�  �ѵ�ǰֵ��Ϊ0 
				if (i > 0) // ��i= 0 ��˵���Լ�����ߵ��� �Ͳ���Ҫ�������ƶ���
					canvas[i - 1][j] = 2;  //�����ϱ�һ������Ϊ�ӵ�
			}
		}
	}

	//�ı��������ʱ�� 
	/*
	*  ��������ʱ��������������� ���ǵ��˺ͷɻ���������
	*  ��Ϊ���������� ���û��޹صĸ��º����û��йصĸ��¶���whileѭ���� �����û��޹ظ����м������ӳٺ�
	*  �����йصĸ����е�����Ҳ���ӳ� ϣ���ﵽ �������˲ʱ���룬������������
	*/
	static int speed = 0;  // ���������ÿ����10�� ��������һ�� �þ�̬����������
	if (speed < EnemyMoveSpeed)
	{
		speed++;
	}
	// �����ܳ��±߽� �������ɵл� �ܳ��±߽� score-1
	for (int k = 0; k < NUM; k++)
	{
		// ��ײ
		if ((enemy_x[k] == position_x) && (enemy_y[k] == position_y))
		{
			printf("\n��Ϸ����");
			Sleep(3000);
			system("pause");
			exit(0);
		}
		if (enemy_x[k] > high) //�����ܳ��±߽� �����������һ������ ���˵�x������Ļ�ĸ߶� �ͱ�ʾ�ܳ�ȥ��
		{
			canvas[enemy_x[k]][enemy_y[k]] = 0; // �������
			enemy_x[k] = 0; //����֮����������
			enemy_y[k] = rand() % width; // �õ����������  �����ķ�Χ 0��width-1��
			canvas[enemy_x[k]][enemy_y[k]] = 3; // �������ɵ���

			score--; //�ܳ��±߽� ��Ϊ�ͷ� ��һ��
		}
		// �л�����
		if (speed == EnemyMoveSpeed) {
			// Ϊ��ֻ�������������ٶ� speed����ʮ��  ��������һ�� �þ�̬�������������Ƶ��������ٶ�
	//�����Զ����� ��Ϊ��3������
			for (int k = 0; k < NUM; k++)
			{
				canvas[enemy_x[k]][enemy_y[k]] = 0;
				enemy_x[k]++;
				speed = 0; // ����֮���þ�̬������0 
				canvas[enemy_x[k]][enemy_y[k]] = 3;
			}
		}
	}
}

//�������йصĺ���
void updateWithInput()
{
	char input;
	if (_kbhit()) // ������ʱִ��
	{
		input = _getch(); //��������ַ���input
		if (input == 'a')
		{
			canvas[position_x][position_y] = 0; // ��ԭ����ֵ���Ϊ0 ��Ȼ������±��������  ******
			position_y--; // �����ƶ�
			canvas[position_x][position_y] = 1; // ���µ�λ�ô�ӡ�ɻ�
		}
		if (input == 'd')
		{
			canvas[position_x][position_y] = 0;
			position_y++; // �����ƶ�
			canvas[position_x][position_y] = 1;
		}
		if (input == 'w')
		{
			canvas[position_x][position_y] = 0;
			position_x--; // �����ƶ�
			canvas[position_x][position_y] = 1;
		}
		if (input == 's')
		{
			canvas[position_x][position_y] = 0;
			position_x++; // �����ƶ�
			canvas[position_x][position_y] = 1;
		}
		if (input == ' ')
		{
			// ���ӵ����Գɳ� ������ұ߽�
			int left, right;
			// ȷ���ӵ��ı߽����� �����ӵ��������ߵ��Ǳ�
			left = position_y - BulletWidth;
			if (left < 0) {
				left = 0;
			}
			right = position_y + BulletWidth;
			if (right > width - 1) {
				right = width - 1;
			}
			for (int x = left; x <= right; x++) {
				canvas[position_x - 1][x] = 2; // ���ﲻ��������ʲô��˼  �Ϳ��±�
			}

			/*
			*  �ڶ����ѵ㣺���귢��֮�� �ӵ�Ҫ������ ���ڳ��������� �����ӵ�ֻ����һ�� �Ͳ�����
			*  ��������� �ӵ��������������û�����Ҫ�ĸ���  �����û��޹صĸ����н��ӵ���Bullitt_x--;
			*/
			//bullit_x = position_x - 1; // �ӵ���x���ڷɻ��ϱ�һ�� ����position-1;
			//bullit_y = position_y; // �ӵ���y��ͷɻ���y��һ��
			//canvas[bullit_x][bullit_y] = 2; // ������㴦�����ӵ�
		}
		if (input == 'k') {
			Pause();
		}


	}
}

void Pause()
{
	gotoxy(32, 10);
	printf("��ͣ��Ϸ\n");
	gotoxy(30, 11);
	printf("��ķ���Ϊ��%d\n", score);
	char temp;
	while (1) {
		while (1) {
			if (_kbhit()) { // _kbhit�Ǽ����û�а���
				temp = _getch(); // �������temp��¼������ʲô
				break;
			}
		}
		if (temp == 'k') {
			break;
		}
		gotoxy(35, 10);
		printf("     ");
		gotoxy(30, 11);
		printf("      ");
	}
}
