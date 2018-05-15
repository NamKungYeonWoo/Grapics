// ------------------------------------------------------------------------------------------------
// Image class Implementation file
// ------------------------------------------------------------------------------------------------

#include <glut.h>
#include "ImageProc.h"
// ------------------------------------------------------------------------------------------------
// Convert to gray-scale
// ------------------------------------------------------------------------------------------------

void ImageProc::convertToGray()
{
	int  x, y;
	byte R, G, B;
	byte Gray;

	for (y = 0; y < m_iHeight; y++)
	{
		for (x = 0; x < m_iWidth; x++)
		{
			getPixel(x, y, R, G, B);

			Gray = xClip(0.299*R + 0.587*G + 0.114*B);

			setPixel(x, y, Gray, Gray, Gray);
		}
	}
}

void ImageProc::convertToSepia()
{
	int  x, y;
	byte R, G, B;
	byte dR,dG,dB;

	for (y = 0; y < m_iHeight; y++)
	{
		for (x = 0; x < m_iWidth; x++)
		{
			getPixel(x, y, R, G, B);

			dR = xClip(0.393*R + 0.769*G + 0.189*B);
			dG = xClip(0.349*R + 0.686*G + 0.168*B);
			dB = xClip(0.272*R + 0.534*G + 0.131*B);

			setPixel(x, y, dR, dG, dB);
		}
	}
}

void ImageProc::samplingBy2()
{
	int  x, y;
	byte R, G, B;
	byte* rgb = new byte[(m_iWidth*m_iHeight * 3)/4];
	for (y = 0; y < m_iHeight/2 ; y++)
	{
		for (x = 0; x < m_iWidth/2; x++)
		{
			
			getPixel(x*2, y*2, R, G, B);
			rgb[(y * (m_iWidth/2) * 3 + x * 3) + 0] = R;
			rgb[(y * (m_iWidth/2) * 3 + x * 3) + 1] = G;
			rgb[(y * (m_iWidth/2) * 3 + x * 3) + 2] = B;
		}
	}
	setRGB(rgb);
	m_iWidth /= 2;
	m_iHeight /= 2;
}

void ImageProc::quantization(int step)
{
	int  x, y, dx, dy;
	int i, j;
	int max = 256;
	if (step > 128)
		step = 128;
	int level=256/step;
	byte R, G, B,dR,dG,dB;
	for (y = 0; y < m_iHeight; y++)
	{
		for (x = 0; x < m_iWidth; x++)
		{
			getPixel(x, y, R, G, B);
			dR = R / step;
			dG = G / step;
			dB = B / step;
			dR = 255 * dR / (level - 1);
			dG = 255 * dG / (level - 1);
			dB = 255 * dB / (level - 1);
			setPixel(x, y, dR, dG, dB);
		}
	}
}