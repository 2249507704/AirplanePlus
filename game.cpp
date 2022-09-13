#include"game.h"
//游戏初始化
int position_x, position_y;     //飞机位置
int bullit_x, bullit_y;         //子弹位置
int enemy_x[NUM], enemy_y[NUM]; // 多台敌人
int BulletWidth;                // 子弹宽度  在初始化函数里进行初始化
int EnemyMoveSpeed;             // 敌人移动速度

//int high, width; //画面大小
int score; //获得分数
int canvas[high][width] = {0};  //用二维数组记录游戏画面中对应的元素 并且给他初始化为0输出空格，1输出飞机 2输出子弹 3输出敌人
 // 把二维数组初始化为0
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
 * 文字颜色函数
 */
int color(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);    //更改文字颜色
	return 0;
}
void gotoxy(int x, int y)//光标移动到xy的位置  要用头文件windows.h
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

//解决光标闪烁的函数
void HideCursor()//隐藏光标 执行一次就行 放在初始化就行
{
	CONSOLE_CURSOR_INFO cursor_infor = { 1,0 }; //第二个值为0表示隐藏光标
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_infor);
}
//开始界面
void welcometogame() 
{
	int n;
	color(15);
	gotoxy(43, 10);
	printf("飞 机 大 战");
	color(11);
	gotoxy(25, 22);
	printf("1.开始游戏");
	gotoxy(45, 22);
	printf("2.游戏说明");
	gotoxy(65, 22);
	printf("3.退出游戏");
	gotoxy(40, 27);
	color(3);
	printf("请选择 1 2 3:");
	color(14);
	cin >> n;  //输入选项
	switch (n)
	{
	case 1:
		system("cls");
		show();
		break;
	case 2:
		explation();    //游戏说明函数
		break;
	case 3:
		exit(0);    //退出游戏
		break;
	default:
		color(12);
		gotoxy(40, 28);
		printf("请输入1-3之间的数!");
		_getch();  //输入任意键
		system("cls"); //清屏
		welcometogame(); // 再打开这个函数
	}
}
//游戏提示
void explation() 
{
	int i, j = 1;
	system("cls");
	color(10);
	gotoxy(44, 1);
	printf("游戏说明");
	color(2);
	for (i = 3; i <= 28; i++)  //输出上下边框===
	{
		for (j = 6; j <= 80; j++) //输出左右边框||
		{
			gotoxy(j, i);
			if (i == 3 || i == 28) printf("=");
			else if (j == 6 || j == 80) printf("||");
		}
	}
	color(3);
	gotoxy(20, 5);
	printf("1. W,A,S,D 分别控制飞机的上下左右移动");
	color(10);
	gotoxy(20, 8);
	printf("2. 按空格发射子弹，打中敌机即可得到一分");
	color(14);
	gotoxy(20, 11);
	printf("3.碰到敌机子弹死亡");
	color(11);
	gotoxy(20, 14);
	printf("4. ESC ：退出游戏");
	color(4);
	gotoxy(20, 17);
	printf("5. 玩的愉快！！！");
	color(7);
	gotoxy(20, 20);
	printf("/*****按任意键返回主页面*****/");
	_getch();        //按任意键返回主界面
	system("cls");
	welcometogame();
}
//游戏侧边提示
void scoreandtips() 
{
	gotoxy(50, 8);
	color(14);
	printf("游戏得分：%d ", score);
	gotoxy(50, 10);
	printf("用W A S D 分别控制飞机的移动");
	gotoxy(50, 12);
	printf("按下空格键即为发射炮弹");
	gotoxy(50, 14);
	printf("@ 的样子就是敌人的飞机");
	gotoxy(50, 16);
	printf("按下k 暂停游戏");
}
//初始化数据的函数
void startup()
{
	//飞机位置 初始化飞机位置  让飞机一开始在屏幕中间
	position_x = high / 2;
	position_y = width / 2;

	/*
	*  先把飞机画出来，剩下的有关飞机的所有操作都是在飞机位置上进行的
	*/

	//最后要输出二维数组 初始化飞机位置 
	canvas[position_x][position_y] = 1;

	//初始化敌人位置
	for (int k = 0; k < NUM; k++)
	{
		/* 如何让敌人随机出现 */
		enemy_x[k] = rand() % 3;
		enemy_y[k] = rand() % width; // 在0到width-1
		canvas[enemy_x[k]][enemy_y[k]] = 3; // 把出现的敌人位置赋值给3
	}

	//子弹位置
	/*bullit_x = -1;  // 一开始子弹会出现在顶端 为了避免 让他初始化为-1
	bullit_y = position_y;*/
	canvas[bullit_x][bullit_y] = 2;

	EnemyMoveSpeed = 10; // 初始化敌人移动速度

	BulletWidth = 0; // 初始化子弹宽度
	//初始分数
	score = 0;

	HideCursor();  //这个函数只需要执行一次  所以放在初始化就好
}

//在合适的位置找到飞机
void show()
{
	gotoxy(0, 0); //光标移动到原点位置，以下重画清屏
	//system("cls"); //清屏操作  这个清屏操作会一闪一闪 上边用一个gotoxy(int x,int y)的函数来代替

	for (int i = 0; i < high; i++)
	{
		for (int j = 0; j < width; j++)
		{
			// 遍历整个画面 在二维数组中遍历到对应的飞机的坐标后 将其赋值为1
			// 二维数组为1 输出飞机  为2 输出子弹  为3 画出敌人
			if (canvas[i][j] == 1)// 遍历空白位置 遍历到飞机的位置就打印出来
			{
				printf("*");  //输出飞机
			}
			else if (canvas[i][j] == 2)
			{
				printf("|"); //输出子弹
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

	printf("得分：%d\n", score);
}

//和输入无关的函数
void updateWithoutInput()
{
	//问题 加了延时后 飞机和敌人都变慢了 解决方法 加入 一个静态变量

	//让子弹向上移动
	for (int i = 0; i < high; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (canvas[i][j] == 2)
			{
				for (int k = 0; k < NUM; k++)
				{
					if ((i == enemy_x[k]) && (j == enemy_y[k])) // 子弹和敌人的坐标相等 击中敌人
					{
						score++; //加分
						if (score % 5 == 0 && EnemyMoveSpeed > 3) // 达到一定积分后敌机可以加速
						{
							EnemyMoveSpeed--;
						}
						if (score % 5 == 0) {
							// 达到一定积分后子弹变宽
							BulletWidth++;
							if (BulletWidth >= 5) {
								BulletWidth = 5;
							}
						}
						canvas[enemy_x[k]][enemy_y[k]] = 0;  //让敌人归零
						//随机再生敌人
						enemy_x[k] = 0;
						enemy_y[k] = rand() % width;
						canvas[enemy_x[k]][enemy_y[k]] = 3;  //显示再生的敌人
						
					}
				}
				canvas[i][j] = 0;  //清除打掉飞机的子弹  把当前值变为0 
				if (i > 0) // 当i= 0 就说明以及到最高点了 就不需要再网上移动了
					canvas[i - 1][j] = 2;  //把他上边一个设置为子弹
			}
		}
	}

	//改变敌人下落时间 
	/*
	*  加入了延时函数后出现了问题 就是敌人和飞机都变慢了
	*  因为在主函数中 与用户无关的更新和与用户有关的更新都在while循环里 当在用户无关更新中加入了延迟后
	*  输入有关的更新中的输入也会延迟 希望达到 输入可以瞬时输入，敌人慢慢下落
	*/
	static int speed = 0;  // 解决方法：每运行10次 敌人下落一次 用静态变量来控制
	if (speed < EnemyMoveSpeed)
	{
		speed++;
	}
	// 敌人跑出下边界 重新生成敌机 跑出下边界 score-1
	for (int k = 0; k < NUM; k++)
	{
		// 碰撞
		if ((enemy_x[k] == position_x) && (enemy_y[k] == position_y))
		{
			printf("\n游戏结束");
			Sleep(3000);
			system("pause");
			exit(0);
		}
		if (enemy_x[k] > high) //敌人跑出下边界 随机重新生成一个敌人 敌人的x大于屏幕的高度 就表示跑出去了
		{
			canvas[enemy_x[k]][enemy_y[k]] = 0; // 清除敌人
			enemy_x[k] = 0; //落完之后重新生成
			enemy_y[k] = rand() % width; // 让敌人随机产生  产生的范围 0到width-1；
			canvas[enemy_x[k]][enemy_y[k]] = 3; // 重新生成敌人

			score--; //跑出下边界 作为惩罚 减一分
		}
		// 敌机下落
		if (speed == EnemyMoveSpeed) {
			// 为了只减慢敌人下落速度 speed运行十次  敌人下落一次 用静态变量来单独控制敌人下落速度
	//敌人自动下落 因为是3个敌人
			for (int k = 0; k < NUM; k++)
			{
				canvas[enemy_x[k]][enemy_y[k]] = 0;
				enemy_x[k]++;
				speed = 0; // 做完之后让静态变量清0 
				canvas[enemy_x[k]][enemy_y[k]] = 3;
			}
		}
	}
}

//和输入有关的函数
void updateWithInput()
{
	char input;
	if (_kbhit()) // 当按键时执行
	{
		input = _getch(); //把输入的字符给input
		if (input == 'a')
		{
			canvas[position_x][position_y] = 0; // 把原来的值清空为0 不然会出现下边这种情况  ******
			position_y--; // 往左移动
			if (position_y < 0) {
				position_y = 0;
			}
			canvas[position_x][position_y] = 1; // 在新的位置打印飞机
		}
		if (input == 'd')
		{
			canvas[position_x][position_y] = 0;
			position_y++; // 往右移动
			if (position_y > width - 1) {
				position_y = width - 1;
			}
			canvas[position_x][position_y] = 1;
		}
		if (input == 'w')
		{
			canvas[position_x][position_y] = 0;
			position_x--; // 往上移动
			if (position_x < 0) {
				position_x = 0;
			}
			canvas[position_x][position_y] = 1;
		}
		if (input == 's')
		{
			canvas[position_x][position_y] = 0;
			position_x++; // 往下移动
			if (position_x > high - 1) {
				position_x = high - 1;
			}
			canvas[position_x][position_y] = 1;
		}
		if (input == ' ')
		{
			// 让子弹可以成长 添加左右边界
			int left, right;
			// 确定子弹的边界条件 这样子弹不会从这边到那边
			left = position_y - BulletWidth;
			if (left < 0) {
				left = 0;
			}
			right = position_y + BulletWidth;
			if (right > width - 1) {
				right = width - 1;
			}
			for (int x = left; x <= right; x++) {
				canvas[position_x - 1][x] = 2; // 这里不懂坐标是什么意思  就看下边
			}

			/*
			*  第二个难点：按完发射之后 子弹要往上跑 现在出现了问题 就是子弹只会上一下 就不动了
			*  解决方法： 子弹往上走是属于用户不需要的更新  在与用户无关的更新中将子弹的Bullitt_x--;
			*/
			//bullit_x = position_x - 1; // 子弹的x轴在飞机上边一点 就是position-1;
			//bullit_y = position_y; // 子弹的y轴和飞机的y轴一样
			//canvas[bullit_x][bullit_y] = 2; // 在这个点处画出子弹
		}
		if (input == 'k') {
			Pause();
		}


	}
}

void Pause()
{
	gotoxy(32, 10);
	printf("暂停游戏\n");
	gotoxy(30, 11);
	printf("你的分数为：%d\n", score);
	char temp;
	while (1) {
		while (1) {
			if (_kbhit()) { // _kbhit是检测有没有按键
				temp = _getch(); // 这个是用temp记录按的是什么 getch是一个不回显函数 自动读取 不用按回车
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
