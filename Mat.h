/*
* Name: Mat
* Contributers:SilentCA YiYi Xia
*/
#ifndef __MAT_H
#define __MAT_H
typedef struct Mat
{
	unsigned char *rgb;//存放图片的RGB数据 
	int width;//图像的宽度 
	int height;//图像的高度 
}Mat;

//public: 供大家使用 
void MatInitial(Mat &p,int width,int height);//初始化一张图片 输入：图片结构体变量，图片宽度，图片高度 
void MatRect(Mat &p,int start_x,int start_y,int end_x,int end_y,int r,int g,int b);//在图片中绘制矩形 输入：图片结构体变量，矩形对角线上的两点A的x y坐标，B的x，y坐标  RGB通道的数值R、G、B 
void MatDraw(Mat p);//将图像用照片查看器展示出来 
void MatOutput(Mat p,char* filename);//输出图像文件，输入：图片结构体变量，图片名 

//private: 最好不要调用 
void MatShow(char* filename);//显示图像
#endif

