void Bresenham_LineTo(CDC *pDC, int x1, int y1, int x2, int y2) //中点Bresenham算法
{
	float k = 1.0*(y2 - y1) / (x2 - x1); //斜率
	int flag = 0;  //是否沿y = x 翻转
	if (k > 1 || k < -1)
	{
		flag = 1;
		x1 ^= y1 ^= x1 ^= y1;
		x2 ^= y2 ^= x2 ^= y2;
		k = 1.0*(y2 - y1) / (x2 - x1);
	}
	float d = 0.5 - k; //初始值
	if (x1 > x2)
	{
		x1 ^= x2 ^= x1 ^= x2;
		y1 ^= y2 ^= y1 ^= y2;
	}
	while (x1 != x2)//主位移，每次都像素+1
	{
		if (k > 0 && d < 0)  //正向
				++y1, ++d;
		else if (k < 0 && d > 0)//负向
				--y1, --d;
		d -= k;
		++x1;
		if (flag) pDC->SetPixel(y1, x1, RGB(255, 0, 0)); //翻转像素点
		else pDC->SetPixel(x1, y1, RGB(255, 0, 0)); 
	}
}