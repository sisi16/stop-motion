#include "opflow.h"

using namespace std;
using namespace cv;
using namespace cv::gpu;


opflow::opflow()
{
}

opflow::~opflow()
{
}

void opflow::createColorWheel()
{
    int RY = 15;
    int YG = 6;
    int GC = 4;
    int CB = 11;
    int BM = 13;
    int MR = 6;

    int i;

    for (i = 0; i < RY; i++) colorwheel.push_back(Scalar(255, 255*i/RY,	0));
    for (i = 0; i < YG; i++) colorwheel.push_back(Scalar(255-255*i/YG, 255, 0));
    for (i = 0; i < GC; i++) colorwheel.push_back(Scalar(0,	255, 255*i/GC));
    for (i = 0; i < CB; i++) colorwheel.push_back(Scalar(0, 255-255*i/CB, 255));
    for (i = 0; i < BM; i++) colorwheel.push_back(Scalar(255*i/BM, 0, 255));
    for (i = 0; i < MR; i++) colorwheel.push_back(Scalar(255, 0, 255-255*i/MR));
}

void opflow::motionToColor(Mat flow, Mat &coloredflow)
{
    coloredflow.create(flow.rows, flow.cols, CV_8UC3);

    if (colorwheel.empty())
        createColorWheel();

    // determine motion range:
    float maxrad = -1;

    // Find max flow to normalize fx and fy
    for (int i= 0; i < flow.rows; ++i)
    {
        for (int j = 0; j < flow.cols; ++j)
        {
            Vec2f flow_at_pixel = flow.at<Vec2f>(i, j);
            float fx = flow_at_pixel[0];
            float fy = flow_at_pixel[1];
            if ((fabs(fx) >  UNKNOWN_FLOW_THRESH) || (fabs(fy) >  UNKNOWN_FLOW_THRESH))
                continue;
            float rad = sqrt(fx * fx + fy * fy);
            maxrad = maxrad > rad ? maxrad : rad;
        }
    }

    for (int i= 0; i < flow.rows; ++i)
    {
        for (int j = 0; j < flow.cols; ++j)
        {
            uchar *data = coloredflow.data + coloredflow.step[0] * i + coloredflow.step[1] * j;
            Vec2f flow_at_pixel = flow.at<Vec2f>(i, j);

            float fx = flow_at_pixel[0] / maxrad;
			float fy = flow_at_pixel[1] / maxrad;
            if ((fabs(fx) >  UNKNOWN_FLOW_THRESH) || (fabs(fy) >  UNKNOWN_FLOW_THRESH))
            {
                data[0] = data[1] = data[2] = 0;
                continue;
            }
            float rad = sqrt(fx * fx + fy * fy);

            double angle = atan2(-fy, -fx) / CV_PI;
            double fk = (angle + 1.0) / 2.0 * (colorwheel.size()-1);
            int k0 = (int)fk;
            int k1 = (k0 + 1) % colorwheel.size();
            double f = fk - k0;
            //f = 0; // uncomment to see original color wheel

            for (int b = 0; b < 3; b++)
            {
                double col0 = colorwheel[k0][b] / 255.0;
                double col1 = colorwheel[k1][b] / 255.0;
                double col = (1 - f) * col0 + f * col1;
                if (rad <= 1)
                    col = 1 - rad * (1 - col); // increase saturation with radius
                else
                    col *= .75; // out of range
                data[2 - b] = (int)(255.0 * col);
            }
        }
    }
}

Mat opflow::calOpFlow(Mat currentframe, Mat nextframe)
{
	/*Mat currentgray, nextgray; //Mat flow;
	cvtColor(currentframe, currentgray, CV_BGR2GRAY);
    cvtColor(nextframe, nextgray, CV_BGR2GRAY);
	GpuMat g_currentframe(currentgray);
	GpuMat g_nextframe(nextgray);

	GpuMat g_flowx(currentframe.size(), CV_32FC1);
	GpuMat g_flowy(currentframe.size(), CV_32FC1);
	OpticalFlowDual_TVL1_GPU tvl1;

	//if (currentframe.data)//if (currentgray.data)
	tvl1(g_currentframe, g_nextframe, g_flowx, g_flowy);//calcOpticalFlowSF(currentframe, nextframe, flow, 3, 2, 4); calcOpticalFlowFarneback(currentgray, nextgray, flow, 0.5, 3, 15, 3, 5, 1.2, 0);
	Mat flowx(g_flowx);
	Mat flowy(g_flowy);
	vector<Mat> flow;
	flow.push_back(flowx);
	flow.push_back(flowy);
    
	return flow;*/

	Mat currentgray, nextgray, flow;
	cvtColor(currentframe, currentgray, CV_BGR2GRAY);
	cvtColor(nextframe, nextgray, CV_BGR2GRAY);
	Ptr<DenseOpticalFlow>tvl1 = createOptFlow_DualTVL1();
	tvl1->calc(currentgray, nextgray, flow);
	return flow;
}

bool opflow::isFlowCorrect(float u) 
{
	return !cvIsNaN(u) && (fabs(u) < UNKNOWN_FLOW_THRESH);
}

float opflow::calAvgOpFlow(Mat flow)
{
    /*float accrad = 0;
    int overflow_count = 0;
	Mat flowx = flow.at(0);
	Mat flowy = flow.at(1);

    for (int i= 0; i < flowx.rows; ++i)
    {
        for (int j = 0; j < flowx.cols; ++j)
        {
            //Vec2f flow_at_pixel = flow.at<Vec2f>(i, j);
			float fx = flowx.at<float>(i, j);//float fx = flow_at_pixel[0];
			float fy = flowy.at<float>(i, j);//float fy = flow_at_pixel[1];

			if (!isFlowCorrect(fx) || !isFlowCorrect(fy))
            {
                overflow_count++;
                continue;
            }			
            accrad += sqrt(fx * fx + fy * fy);
        }		
    }
    float avgflow = accrad / (flowx.rows * flowx.cols - overflow_count);
    return avgflow;*/

	float accrad = 0;
	int overflow_count = 0;
	int movingpixel_count = 0;
	for (int i = 0; i < flow.rows; ++i)
	{
		for (int j = 0; j < flow.cols; ++j)
		{
			Vec2f flow_at_pixel = flow.at<Vec2f>(i, j);
			float fx = flow_at_pixel[0];
			float fy = flow_at_pixel[1];

			if (!isFlowCorrect(fx) || !isFlowCorrect(fy))
			{
				overflow_count++;
				continue;
			}

			float rad = sqrt(fx * fx + fy * fy);
			accrad += rad;
			if (rad > 1) {
				//cout << "[" << i << "," << j << "]: " << rad << endl;
				movingpixel_count++;
			}
		}
	}
	//float avgflow = accrad / (flow.rows * flow.cols - overflow_count);
	float avgflow = movingpixel_count / float(flow.rows * flow.cols - overflow_count);
	return avgflow;
}

/* -------------------------------------------------------------------------
PatchMatch, using L2 distance between upright patches that translate only
------------------------------------------------------------------------- */
BITMAP3* opflow::toBITMAP(const uchar *img, int width, int height, int istep)
{
	BITMAP3 *bmp = new BITMAP3(width, height);
	int bi = 0;
	for (int yi = 0; yi < height; ++yi, img += istep)
	{
		const uchar *px = img;
		for (int xi = 0; xi < width; ++xi, px += 3, ++bi)
		{
			bmp->data[bi] = (px[0] << 16) | (px[1] << 8) | px[2];
		}
	}

	return bmp;
}

int patch_w = 5;//7;
int pm_iters = 9;//5;
int rs_max = INT_MAX;

int opflow::dist(BITMAP3 *a, BITMAP3 *b, int ax, int ay, int bx, int by, int diagonalDis, int cutoff) {
	float alpha = 5, beta = 8;
	double ansColor = 0, ansDis = 0, ans = 0;
	double dxx = ax - bx, dyy = ay - by;
	double dis = sqrt(dxx*dxx + dyy*dyy) / diagonalDis*100.0;
	ansDis = dis*patch_w*patch_w;

	for (int dy = 0; dy < patch_w; dy++) {
		int *arow = &(*a)[ay + dy][ax];
		int *brow = &(*b)[by + dy][bx];
		for (int dx = 0; dx < patch_w; dx++) {
			int ac = arow[dx];
			int bc = brow[dx];
			int dr = (ac & 255) - (bc & 255);
			int dg = ((ac >> 8) & 255) - ((bc >> 8) & 255);
			int db = (ac >> 16) - (bc >> 16);
			ansColor += sqrt((double)(dr*dr + dg*dg + db*db));//ans += dr*dr + dg*dg + db*db;
		}
		//if (ans >= cutoff) { return cutoff; }
	}

	ansColor = ansColor / 255.0*100.0;
	ans = ansColor*alpha + ansDis*beta;
	return ans;
}

void opflow::improve_guess(BITMAP3 *a, BITMAP3 *b, int ax, int ay, int &xbest, int &ybest, int &dbest, int bx, int by) {
	int d = dist(a, b, ax, ay, bx, by, dbest);
	if (d < dbest) {
		dbest = d;
		xbest = bx;
		ybest = by;
	}
}

vector<vector<Point>> opflow::patchMatch(Mat currentframe, Mat nextframe)
{
	/* Initialize with random nearest neighbor field (NNF). */
	BITMAP3 *a = toBITMAP(currentframe.data, currentframe.cols, currentframe.rows, currentframe.step);
	BITMAP3 *b = toBITMAP(nextframe.data, nextframe.cols, nextframe.rows, nextframe.step);

	BITMAP3 *ann = new BITMAP3(a->w, a->h);
	BITMAP3 *annd = new BITMAP3(a->w, a->h);
	Mat annMat = Mat(Size(a->w, a->h), CV_32FC2, Scalar(0, 0));

	int aew = a->w - patch_w + 1, aeh = a->h - patch_w + 1;       /* Effective width and height (possible upper left corners of patches). */
	int bew = b->w - patch_w + 1, beh = b->h - patch_w + 1;
	int diagonalDis = sqrt((double)(a->w*a->w + a->h*a->h));
	memset(ann->data, 0, sizeof(int)*a->w*a->h);
	memset(annd->data, 0, sizeof(int)*a->w*a->h);
	for (int ay = 0; ay < aeh; ay++) {
		for (int ax = 0; ax < aew; ax++) {
			int bx = rand() % bew;
			int by = rand() % beh;
			(*ann)[ay][ax] = XY_TO_INT(bx, by);
			(*annd)[ay][ax] = dist(a, b, ax, ay, bx, by, diagonalDis);
		}
	}
	for (int iter = 0; iter < pm_iters; iter++) {
		/* In each iteration, improve the NNF, by looping in scanline or reverse-scanline order. */
		int ystart = 0, yend = aeh, ychange = 1;
		int xstart = 0, xend = aew, xchange = 1;
		if (iter % 2 == 1) {
			xstart = xend - 1; xend = -1; xchange = -1;
			ystart = yend - 1; yend = -1; ychange = -1;
		}
		for (int ay = ystart; ay != yend; ay += ychange) {
			for (int ax = xstart; ax != xend; ax += xchange) {
				/* Current (best) guess. */
				int v = (*ann)[ay][ax];
				int xbest = INT_TO_X(v), ybest = INT_TO_Y(v);
				int dbest = (*annd)[ay][ax];

				/* Propagation: Improve current guess by trying instead correspondences from left and above (below and right on odd iterations). */
				if ((unsigned)(ax - xchange) < (unsigned)aew) {
					int vp = (*ann)[ay][ax - xchange];
					int xp = INT_TO_X(vp) + xchange, yp = INT_TO_Y(vp);
					if ((unsigned)xp < (unsigned)bew) {
						improve_guess(a, b, ax, ay, xbest, ybest, dbest, xp, yp);
					}
				}

				if ((unsigned)(ay - ychange) < (unsigned)aeh) {
					int vp = (*ann)[ay - ychange][ax];
					int xp = INT_TO_X(vp), yp = INT_TO_Y(vp) + ychange;
					if ((unsigned)yp < (unsigned)beh) {
						improve_guess(a, b, ax, ay, xbest, ybest, dbest, xp, yp);
					}
				}

				/* Random search: Improve current guess by searching in boxes of exponentially decreasing size around the current best guess. */
				int rs_start = rs_max;
				if (rs_start > MAX(b->w, b->h)) { rs_start = MAX(b->w, b->h); }
				for (int mag = rs_start; mag >= 1; mag /= 2) {
					/* Sampling window */
					int xmin = MAX(xbest - mag, 0), xmax = MIN(xbest + mag + 1, bew);
					int ymin = MAX(ybest - mag, 0), ymax = MIN(ybest + mag + 1, beh);
					int xp = xmin + rand() % (xmax - xmin);
					int yp = ymin + rand() % (ymax - ymin);
					improve_guess(a, b, ax, ay, xbest, ybest, dbest, xp, yp);
				}

				(*ann)[ay][ax] = XY_TO_INT(xbest, ybest);
				(*annd)[ay][ax] = dbest;
				int flowx = xbest - ax; int flowy = ybest - ay;
				annMat.at<Vec2f>(ay, ax) = Vec2f(flowx, flowy);
			}
		}
	}

	Mat maskSrc = Mat(Size(a->w, a->h), CV_8UC1, Scalar(0));
	Mat maskDst = Mat(Size(a->w, a->h), CV_8UC1, Scalar(0));
	inRange(annMat, Scalar(0, 0), Scalar(5, 3), maskSrc); //4.8, 2.7
	bitwise_not(maskSrc, maskDst);

	//Mat coloredMat;
	vector<vector<Point>> contours;
	vector<vector<Point>> filterContours;
	//vector<Vec4i> hierarchy;

	//motionToColor(annMat, coloredMat);
	//Mat temp = coloredMat;
	findContours(maskDst, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	for (int contourIdx = 0; contourIdx < contours.size(); contourIdx++)
	{
		if (contourArea(contours[contourIdx]) > 648) //(0.005*270*480)
			filterContours.push_back(contours[contourIdx]);
	}

	/*if (contours.size() > 2)
	{
		sort(contours.begin(), contours.end(), more_area);
		filterContours.push_back(contours[0]);
		filterContours.push_back(contours[1]);
		cout << contourArea(contours[0]) << " " << contourArea(contours[1]) << endl;
		//if (contourArea(contours[0])>1000) filterContours.push_back(contours[0]);
		//f (contourArea(contours[0])>1000) filterContours.push_back(contours[1]);
		//drawContours(frame, filterContours, -1, Scalar(0, 0, 255), 2);
	}*/
	//drawContours(coloredMat, filterContours, -1, Scalar(0, 0, 0), 1);
	//imshow("Mask", maskDst);
	//imshow("Color", coloredMat);

	return filterContours;
}