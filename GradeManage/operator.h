#pragma once


#include "GradeManage.h"

struct cmp_set_stu
{
	bool operator()(const Student& stu1,const Student& stu2) const//��������������const��ɳ�����
	{
		if (stu1.id.size() != 8 || stu2.id.size() != 8)
		{
			printf("��������\n");
			return false;
		}
		int stu1_id_int = stoi(stu1.id);
		int stu2_id_int = stoi(stu2.id);
		if (stu1_id_int < stu2_id_int)//�����еȺ�
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};
struct cmp_set_cou
{
	bool operator()(const Couse& cou1,const Couse& cou2)const
	{
		if (cou1.id.size() != 4 || cou2.id.size() != 4)
		{
			printf("��������\n");
			return false;
		}
		int cou1_int = stoi(cou1.id);
		int cou2_int = stoi(cou2.id);
		if (cou1_int < cou2_int)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};
set <Student,cmp_set_stu>stu_col;
set <Couse>cou_col;
map<Couse,CouseTable>cou_table_col;//�ж��ſεĳɼ���
set<StudentGrade>grade_table;

void Input_EnterStuInfo()
{
	Student s;	
	printf("��ʼ¼��ѧ����Ϣ:\n");	
	printf("ѧ��: "); cin >> s.id;
	printf("����: "); cin >> s.name;
	printf("�Ա�: "); cin >> s.sex;
	printf("����: "); cin >> s.age;
	stu_col.insert(s);
}
void Input_EnterCouInfo()
{
	Couse c;
	printf("��ʼ¼��γ���Ϣ:\n");
	printf("�γ̺�: "); cin >> c.id;
	printf("�γ���: "); cin >> c.name;
	printf("�γ�ѧ��: "); cin >> c.credit;
	cou_col.insert(c);
}
void Input_EnterStuGrade()
{
	string cou_id;
	string stu_id;
	CouseTable cou_table;
	printf("��ʼ¼��ѧ���ɼ�:\n");
	int op = 1;
	while (op)
	{
		printf("�γ̺�: "); cin >> cou_id;
		printf("ѧ��ѧ�ţ�"); cin >> stu_id;
		
		//���ݿγ̺ź�ѧ����ȷ���Ƿ���ڴ���
		Student stu_tmp;
		stu_tmp.id = stu_id;
		auto it_stu=stu_col.find(stu_tmp);
		Couse cou_tmp;
		cou_tmp.id = cou_id;
		auto it_cou = cou_col.find(cou_tmp);
		if (it_stu != stu_col.end() && it_cou != cou_col.end())
		{
			cout << "ѧ������" << endl;
			cou_table.cou = *it_cou;
			char gf; int score;
			printf("ѧ��������������Y����������N��"); cin >> gf;
			if (gf == 'Y')
			{
				cou_table.stu_form[*it_stu] = Normal;
				printf("������ѧ���ɼ���");
				 cin >> score;
				cou_table.stu_gra[*it_stu] = score;
			}
			else if (gf == 'N')
			{
				cou_table.stu_form[*it_stu] = notNormal;
				cou_table.stu_gra[*it_stu] = 0;
			}
			else
			{
				printf("����Ƿ�������¼��\n");
				return;
			}
			cou_table_col[*it_cou] = cou_table;
			//StudentGrade stugrade(*it_stu,make_pair(*it_cou,score),make_pair(*it_cou, cou_table.stu_form[*it_stu]));
			StudentGrade stugrade;
			stugrade.stu = *it_stu;
			stugrade.cou_gra[*it_cou] = score;
			stugrade.cou_form[*it_cou] = cou_table.stu_form[*it_stu];
			grade_table.insert(stugrade);
			printf("¼��ɹ�\n");
		}
		else
		{
			cout << "ѧ�������ڻ��߿γ̺�����" << endl;
		}
		printf("����¼����");
		printf("0. ֹͣ¼��  1. ����¼��\n");
		cin >> op;
	}
}
void Output()
{
	int op = 1;
	printf("0. �˳�  1. �鿴ĳѧ���ĳɼ�  2. �鿴ĳ�ſεĳɼ�\n");
	cin >> op;
	while(op)
	{
		if (op == 1)
		{
			string stu_id;
			printf("������ѧ��ѧ�ţ�"); cin >> stu_id;
			auto it = stu_col.find(Student(stu_id));
			if (it != stu_col.end())
			{
				auto it2 = grade_table.find(StudentGrade(*it));
				if (it2 != grade_table.end())
				{
					cout << *it2;
				}
				else
				{
					cout << "δ¼��ɼ�" << endl;
				}
				break;
			}
			else
			{
				cout << "ѧ��������" << endl;
			}
			
		}
		else if (op == 2)
		{
			string cou_id;
			printf("������γ̺ţ�"); cin >> cou_id;
			auto it = cou_col.find(Couse(cou_id));
			if (it != cou_col.end())
			{
				CouseTable tmp = cou_table_col[*it];
				cout << tmp;
			}
			else
			{
				cout << "�γ̲�����" << endl;
			}
			
		}
		else
		{
			printf("��������\n");
			break;
		}
	
		break;
	}
}

void Erase()
{
	int op = 1;
	printf("0. �˳�  1. ɾ��ĳѧ���ĳɼ�\n");
	cin >> op;
	while (op)
	{
		if (op == 1)
		{
			string stu_id;
			printf("������ѧ��ѧ�ţ�"); cin >> stu_id;
			auto it = stu_col.find(Student(stu_id));
			if (it != stu_col.end())
			{
				auto it2 = grade_table.find(StudentGrade(*it));
				if (it2 != grade_table.end())
				{
					grade_table.erase(it2);
					stu_col.erase(*it);
				}
				else
				{
					cout << "δ¼��ɼ�" << endl;
				}
				break;
			}
			else
			{
				cout << "ѧ��������" << endl;
			}
		}
		else
		{
			printf("��������\n");
		}

		break;
	}
}
void Update()
{
	Input_EnterStuGrade();
}

void menu()
{
	printf("***************************************\n");
	printf("**  1.¼��ѧ����Ϣ    2.���  ***\n");
	printf("********   3.¼��ɼ�   4. ɾ��   ******\n");
	printf("****   5.¼��γ���Ϣ  6.�޸ĳɼ�  ******\n");
	printf("**********        0.exit       ********\n");
	printf("***************************************\n");
	int op;
	printf("�����룺 "); cin >> op;
	while (op)
	{
		switch (op)
		{
		case 0:
			break;
		case 1:
			Input_EnterStuInfo();
			break;
		case 2:
			Output();
			break;
		case 3:
			Input_EnterStuGrade();
			break;
		case 4:
			Erase();
			break;
		case 5:
			Input_EnterCouInfo();
			break;
		case 6:
			Update();
			break;
		}
		printf("***************************************\n");
		printf("**  1.¼��ѧ����Ϣ    2.���  ***\n");
		printf("********   3.¼��ɼ�   4. ɾ��   ******\n");
		printf("****   5.¼��γ���Ϣ   6.�޸ĳɼ�  ******\n");
		printf("**********        0.exit       ********\n");
		printf("***************************************\n");
		cin >> op;
	}
	
}

