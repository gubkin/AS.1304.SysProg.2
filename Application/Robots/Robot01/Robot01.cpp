// Robot01.cpp: îïðåäåëÿåò ýêñïîðòèðîâàííûå ôóíêöèè äëÿ ïðèëîæåíèÿ DLL.
//

#include "stdafx.h"
#define Info _stepInfo

extern "C" __declspec(dllexport) void DoStep(StepInfo* _stepInfo)
{
	RobotInfo* myInfo;
	for (auto it = Info->robotsInfo.begin(); it != Info->robotsInfo.end(); ++it)
	{
		if (Info->ID == it->ID) {
			myInfo = new RobotInfo(*it);
			break;
		}
	}

	int me = myInfo->ID;
	int x = myInfo->x;
	int y = myInfo->y;
	int L = myInfo->L;
	int E = myInfo->E;

	Info->pRobotActions->addActionRedistribution(0.80*L - 1, 1, 0.20*L);

	for (std::list<pair<unsigned int, unsigned int>>::iterator it = Info->chargingStations.begin(); it != Info->chargingStations.end(); it++)
	{
		if (it->first == x && it->second == y && E < 0.95*Info->gameConfig.E_max)
		{
			Info->pRobotActions->addActionRedistribution(0, L, 0);
			return;
		}
	}
	for (std::list<pair<unsigned int, unsigned int>>::iterator it = Info->maintenance.begin(); it != Info->maintenance.end(); it++)
	{
		if (it->first == x && it->second == y && L < 0.80*Info->gameConfig.L_max)
		{
			Info->pRobotActions->addActionRedistribution(0, L, 0);
			return;
		}
	}

	if ((E < 0.9*Info->gameConfig.E_max) || (Info->stepNumber > 0.99 * Info->gameConfig.N))
	{
		int V = Info->gameConfig.V_max;
		if (V > L)
			V = L;
		Info->pRobotActions->addActionRedistribution(0, L - V + 1, V - 1);
		int eid = 0;
		int ex = Info->chargingStations.begin()->first;
		int ey = Info->chargingStations.begin()->second;
		double mindist = sqrt(pow(ex - x, 2) + pow(ey - y, 2));
		int mex = ex;
		int mey = ey;
		for (std::list<pair<unsigned int, unsigned int>>::iterator it = Info->chargingStations.begin(); it != Info->chargingStations.end(); it++)
		{
			ex = Info->chargingStations.begin()->first;
			ey = Info->chargingStations.begin()->second;
			double curdist = sqrt(pow(ex - x, 2) + pow(ey - y, 2));
			if (curdist < mindist)
			{
				mindist = curdist;
				mex = ex;
				mey = ey;
			}
		}

		double maxstep = myInfo->V*Info->gameConfig.V_max / Info->gameConfig.L_max*myInfo->E / Info->gameConfig.E_max;
		if (maxstep < mindist)
		{
			int dx, dy;
			dx = (mex - x)*maxstep / mindist;
			dy = (mey - y)*maxstep / mindist;
			Info->pRobotActions->addActionMove(dx, dy);
		}
		else
		{
			int dx, dy;
			dx = mex - x;
			dy = mey - y;
			Info->pRobotActions->addActionMove(dx, dy);
			Info->pRobotActions->addActionRedistribution(0, L, 0);
		}
	}

	else
	{
		if (L == Info->gameConfig.L_max)
		{

			int kill;

			Info->pRobotActions->addActionRedistribution(0.80*L - 1, 1, 0.20*L);
			int enx = 0;
			int eny = 0;
			int minx = 0;
			int miny = 0;
			double mindisttoen = Info->gameConfig.H;
			double distance = 0;
			double attack = Info->gameConfig.R_max*myInfo->V / Info->gameConfig.L_max*myInfo->E / Info->gameConfig.E_max;

			for (auto it = Info->robotsInfo.begin(); it != Info->robotsInfo.end(); ++it)
			{
				enx = it->x;
				eny = it->y;
				distance = sqrt(pow(enx - x, 2) + pow(eny - y, 2));
				if ((it->Alive) && (myInfo->Author != it->Author) && (2 * myInfo->A*myInfo->E / Info->gameConfig.E_max>it->P*it->E / Info->gameConfig.E_max))
				{
					if (distance < mindisttoen)
					{
						mindisttoen = distance;
						kill = it->ID;
						minx = enx;
						miny = eny;
					}
				}
			}

			if (attack>mindisttoen)
			{
				Info->pRobotActions->addActionAttack(kill);
			}

			else
			{
				double maxstep = myInfo->V*Info->gameConfig.V_max / Info->gameConfig.L_max*myInfo->E / Info->gameConfig.E_max;
				double curdist = sqrt(pow(minx - x, 2) + pow(miny - y, 2));
				int dx, dy;
				if (curdist > maxstep)
				{
					dx = (minx - x)*maxstep / distance;
					dy = (miny - y)*maxstep / distance;
				}

				else
				{
					dx = enx - x;
					dy = eny - y;
					if (enx > x)
						dx -= 1;
					else if (enx < x)
						dx += 1;
					else if (eny > y)
						dy -= 1;
					else dy += 1;
				}
				Info->pRobotActions->addActionMove(dx, dy);
			}
		}

		else
		{
			int V = Info->gameConfig.V_max;
			if (V > L)
				V = L;
			Info->pRobotActions->addActionRedistribution(0, L - V, V);

			int lx = Info->maintenance.begin()->first;
			int ly = Info->maintenance.begin()->second;
			int mlx = lx;
			int mly = ly;
			double mindist = sqrt(pow(lx - x, 2) + pow(ly - y, 2));

			for (std::list<pair<unsigned int, unsigned int>>::iterator it = Info->maintenance.begin(); it != Info->maintenance.end(); it++)
			{

				lx = it->first;
				ly = it->second;
				double curdist = sqrt(pow(lx - x, 2) + pow(ly - y, 2));
				if (curdist < mindist)
				{
					mindist = curdist;
					mlx = lx;
					mly = ly;
				}
			}


			double maxstep = myInfo->V*Info->gameConfig.V_max / Info->gameConfig.L_max*myInfo->E / Info->gameConfig.E_max;
			if (maxstep < mindist)
			{
				int dx, dy;
				dx = (mlx - x)*maxstep / mindist;
				dy = (mly - y)*maxstep / mindist;
				Info->pRobotActions->addActionMove(dx, dy);
			}
			else
			{
				int dx, dy;
				dx = mlx - x;
				dy = mly - y;
				Info->pRobotActions->addActionMove(dx, dy);
				Info->pRobotActions->addActionRedistribution(0, L, 0);
			}
		}
	}
	return;
}
