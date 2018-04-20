/*
* Name: Mat
* Contributers:SilentCA YiYi Xia
*/
#ifndef __MAT_H
#define __MAT_H
typedef struct Mat
{
	unsigned char *rgb;//���ͼƬ��RGB���� 
	int width;//ͼ��Ŀ�� 
	int height;//ͼ��ĸ߶� 
}Mat;

//public: �����ʹ�� 
void MatInitial(Mat &p,int width,int height);//��ʼ��һ��ͼƬ ���룺ͼƬ�ṹ�������ͼƬ��ȣ�ͼƬ�߶� 
void MatRect(Mat &p,int start_x,int start_y,int end_x,int end_y,int r,int g,int b);//��ͼƬ�л��ƾ��� ���룺ͼƬ�ṹ����������ζԽ����ϵ�����A��x y���꣬B��x��y����  RGBͨ������ֵR��G��B 
void MatDraw(Mat p);//��ͼ������Ƭ�鿴��չʾ���� 
void MatOutput(Mat p,char* filename);//���ͼ���ļ������룺ͼƬ�ṹ�������ͼƬ�� 

//private: ��ò�Ҫ���� 
void MatShow(char* filename);//��ʾͼ��
#endif

