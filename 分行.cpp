/*#include <iostream>
#include<Windows.h>
using namespace std;
#include "./gdal/gdal_priv.h"
#pragma comment(lib, "gdal_i.lib")

//��ÿһ������ں������
int fun(GDALDataset *poMulDS, GDALDataset *poPanDS, GDALDataset *poFusDS, float *bandR, float *bandG, float *bandB,
	float *bandI, float *bandH, float *bandS, float *bandP, int startX, int startY, int blockXlen, int blockYlen)
{
	poMulDS->GetRasterBand(1)->RasterIO(GF_Read, startX, startY, blockXlen, blockYlen,
		bandR, blockXlen, blockYlen, GDT_Float32, 0, 0);
	poMulDS->GetRasterBand(2)->RasterIO(GF_Read, startX, startY, blockXlen, blockYlen,
		bandG, blockXlen, blockYlen, GDT_Float32, 0, 0);
	poMulDS->GetRasterBand(3)->RasterIO(GF_Read, startX, startY, blockXlen, blockYlen,
		bandB, blockXlen, blockYlen, GDT_Float32, 0, 0);
	poPanDS->GetRasterBand(1)->RasterIO(GF_Read, startX, startY, blockXlen, blockYlen,
		bandP, blockXlen, blockYlen, GDT_Float32, 0, 0);

	for (int i = 0; i < blockXlen*blockYlen; i++)
	{
		bandH[i] = -sqrt(2.0f) / 6.0f*bandR[i] - sqrt(2.0f) / 6.0f*bandG[i] + sqrt(2.0f) / 3.0f*bandB[i];
		bandS[i] = 1.0f / sqrt(2.0f)*bandR[i] - 1 / sqrt(2.0f)*bandG[i];

		bandR[i] = bandP[i] - 1.0f / sqrt(2.0f)*bandH[i] + 1.0f / sqrt(2.0f)*bandS[i];
		bandG[i] = bandP[i] - 1.0f / sqrt(2.0f)*bandH[i] - 1.0f / sqrt(2.0f)*bandS[i];
		bandB[i] = bandP[i] + sqrt(2.0f)*bandH[i];
	}

	poFusDS->GetRasterBand(1)->RasterIO(GF_Write, startX, startY, blockXlen, blockYlen,
		bandR, blockXlen, blockYlen, GDT_Float32, 0, 0);
	poFusDS->GetRasterBand(2)->RasterIO(GF_Write, startX, startY, blockXlen, blockYlen,
		bandG, blockXlen, blockYlen, GDT_Float32, 0, 0);
	poFusDS->GetRasterBand(3)->RasterIO(GF_Write, startX, startY, blockXlen, blockYlen,
		bandB, blockXlen, blockYlen, GDT_Float32, 0, 0);
	cout << "startX:" << startX << endl;
	cout << "startY:" << startY << endl;
	return 0;
}

int main()
{
	DWORD start, stop;//��ʱ��
	start = GetTickCount();
	char* mulPath = "Mul_large.tif";//�����ͼ������
	char* panPath = "Pan_large.tif";//ȫɫͼ������
	char* fusPath = "Fus.tif";//���ͼ������

	GDALAllRegister();

	GDALDataset *poMulDS;//�����ͼ��
	GDALDataset	*poPanDS;//ȫɫͼ��
	GDALDataset* poFusDS;//���ͼ��
	int imgXlen, imgYlen;
	int blockYlen = 256;//��ĸ߶�
	int yNum;//y�������
	//int i;
	float *bandR, *bandG, *bandB;
	float *bandI, *bandH, *bandS;
	float *bandP;

	//���򿪡�ͼ��
	poMulDS = (GDALDataset*)GDALOpenShared(mulPath, GA_ReadOnly);
	poPanDS = (GDALDataset*)GDALOpenShared(panPath, GA_ReadOnly);

	//��ȡͼ��߶ȺͿ��
	imgXlen = poMulDS->GetRasterXSize();
	imgYlen = poMulDS->GetRasterYSize();

	//��ȡ������Ϣ
	yNum = imgYlen / blockYlen;

	//���򿪡����ͼ��
	poFusDS = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(
		fusPath, imgXlen, imgYlen, 3, GDT_Byte, NULL);

	printf(" ... ... image xlen : %d pixels ... ...\n", imgXlen);
	printf(" ... ... image ylen : %d pixles ... ...\n", imgYlen);
	printf(" ... ... Mul image band number : %d ...\n", poMulDS->GetRasterCount());
	printf(" ... ... Pan image band number : %d ...\n", poPanDS->GetRasterCount());

	//�����ַ�ռ�
	bandR = (float*)CPLMalloc(imgXlen*blockYlen * sizeof(float));
	bandG = (float*)CPLMalloc(imgXlen*blockYlen * sizeof(float));
	bandB = (float*)CPLMalloc(imgXlen*blockYlen * sizeof(float));
	bandP = (float*)CPLMalloc(imgXlen*blockYlen * sizeof(float));
	bandI = (float*)CPLMalloc(imgXlen*blockYlen * sizeof(float));
	bandH = (float*)CPLMalloc(imgXlen*blockYlen * sizeof(float));
	bandS = (float*)CPLMalloc(imgXlen*blockYlen * sizeof(float));

	//ͼ��ֿ���뻺�棬�ںϣ����
	for (int i = 0; i < yNum; i++)
	{
		//�����
		fun(poMulDS, poPanDS, poFusDS, bandR, bandG, bandB, bandI, bandH
			, bandS, bandP, 0, i * blockYlen, imgXlen,
			blockYlen);
	}
	//Y����Ƭ����
	if (yNum * blockYlen < imgYlen)
	{
		blockYlen = imgYlen - yNum * blockYlen;
		fun(poMulDS, poPanDS, poFusDS, bandR, bandG, bandB, bandI, bandH
			, bandS, bandP, 0, yNum * blockYlen, imgXlen,
			blockYlen);
	}
	blockYlen = 256;
	cout << "over" << endl;

	GDALClose(poMulDS);
	GDALClose(poPanDS);
	GDALClose(poFusDS);
	stop = GetTickCount();
	printf("��������ʱ��: %lld ms\n", stop - start);

	return 0;
}*/