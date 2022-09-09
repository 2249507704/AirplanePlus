#include"game.h"
/*
*  第一个难点：游戏的整体框架怎么搭建
*  解决方法： 数据初始化、要显示的画面、与用户输入无关的更新、与用户输入有关的更新。
*/
int main()
{
	system("mode con cols=100 lines=30");
	welcometogame();
	startup(); //数据初始化  只需要一次
	while (1)
	{
		show();  //显示画面
		scoreandtips(); // 游戏提示
		updateWithoutInput();  //与用户输入无关的更新
		updateWithInput(); //与用户输入有关的更新
	}
	return 0;
}