#pragma once
#include <string>
#include <vector>
#include <list>
using namespace std;

struct GameConfig//��������� ����
{
	unsigned int W;
	unsigned int H;
	unsigned int N;
	unsigned int T;
	unsigned int E_max;
	unsigned int L_max;
	unsigned int V_max;
	unsigned int R_max;
	unsigned int dL;
	unsigned int dE_S;
	unsigned int dE_V;
	unsigned int dE_A;
	unsigned int dE_P;
	unsigned int dE;
	unsigned int N_E;
	unsigned int N_L;
	float RND_min;
	float RND_max;
	unsigned int K;
};

struct RobotInfo //�������������� ������
{
	string Name;
	string Author;
	unsigned int ID;
	int E;
	int L;
	int A;
	int P;
	int V;
	unsigned int x;
	unsigned int y;
	bool Alive;
	unsigned int TotalScore;
	unsigned int RoundScore;
	unsigned int TotalFrags;
	unsigned int RoundFrags;
};

#define MOVE			0
#define ATTACK			1
#define REDISTRIBUTION	2

//��������������� ������
class Action
{
protected:	
	unsigned int type;
public:
	virtual ~Action();
	unsigned int getType();
};
class Move : public Action
{
public:
	int dx;
	int dy;
	Move(int _dx, int _dy);
	~Move();
};
class Attack : public Action
{
public:
	unsigned int victimID;
	Attack(unsigned int _victimID);
	~Attack();
};
class Redistribution : public Action
{
public:
	unsigned int A;
	unsigned int P;
	unsigned int V;
	Redistribution(unsigned int _A, unsigned int _P, unsigned int _V);
	~Redistribution();
};

class RobotActions
{
	vector<Action*> m_Actions;

public:
	RobotActions(const RobotActions& from);
	RobotActions();
	~RobotActions();	
	void addActionMove(unsigned int x, unsigned int y);
	void addActionAttack(unsigned int victimID /*ID ���������� ������*/);
	void addActionRedistribution(unsigned int A, unsigned int P, unsigned int V);
	vector<Action*> getActions();
};

struct StepInfo //���������, ������������ ������
{
	vector<RobotInfo> robotsInfo;											//��������� ���� �������
	unsigned int stepNumber;												//����� ����
	GameConfig gameConfig;													//��������� ����
	unsigned int ID;														//ID ������
	list<pair<unsigned int/* x */, unsigned int/* y */>> chargingStations;	//������ ����������
	list<pair<unsigned int/* x */, unsigned int/* y */>> maintenance;		//������ ���. ������������
	list < pair<unsigned int/* ID */, RobotActions>> actionsList;			//���� �������� ������ ����������
	RobotActions* pRobotActions;											//��������� �� �����, ������� ������ ����� ������ (��� ��������� �������� �� ������� ����) ����������� �������
};