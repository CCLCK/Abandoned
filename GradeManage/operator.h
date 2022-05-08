#pragma once


#include "GradeManage.h"

struct cmp_set_stu
{
	bool operator()(const Student& stu1,const Student& stu2) const//重载这个必须加上const变成常函数
	{
		if (stu1.id.size() != 8 || stu2.id.size() != 8)
		{
			printf("输入有误\n");
			return false;
		}
		int stu1_id_int = stoi(stu1.id);
		int stu2_id_int = stoi(stu2.id);
		if (stu1_id_int < stu2_id_int)//不能有等号
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
			printf("输入有误\n");
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
map<Couse,CouseTable>cou_table_col;//有多门课的成绩表
set<StudentGrade>grade_table;

void Input_EnterStuInfo()
{
	Student s;	
	printf("开始录入学生信息:\n");	
	printf("学号: "); cin >> s.id;
	printf("姓名: "); cin >> s.name;
	printf("性别: "); cin >> s.sex;
	printf("年龄: "); cin >> s.age;
	stu_col.insert(s);
}
void Input_EnterCouInfo()
{
	Couse c;
	printf("开始录入课程信息:\n");
	printf("课程号: "); cin >> c.id;
	printf("课程名: "); cin >> c.name;
	printf("课程学分: "); cin >> c.credit;
	cou_col.insert(c);
}
void Input_EnterStuGrade()
{
	string cou_id;
	string stu_id;
	CouseTable cou_table;
	printf("开始录入学生成绩:\n");
	int op = 1;
	while (op)
	{
		printf("课程号: "); cin >> cou_id;
		printf("学生学号："); cin >> stu_id;
		
		//根据课程号和学号来确定是否存在此人
		Student stu_tmp;
		stu_tmp.id = stu_id;
		auto it_stu=stu_col.find(stu_tmp);
		Couse cou_tmp;
		cou_tmp.id = cou_id;
		auto it_cou = cou_col.find(cou_tmp);
		if (it_stu != stu_col.end() && it_cou != cou_col.end())
		{
			cout << "学生存在" << endl;
			cou_table.cou = *it_cou;
			char gf; int score;
			printf("学生正常考试输入Y，否则输入N："); cin >> gf;
			if (gf == 'Y')
			{
				cou_table.stu_form[*it_stu] = Normal;
				printf("请输入学生成绩：");
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
				printf("输入非法，结束录入\n");
				return;
			}
			cou_table_col[*it_cou] = cou_table;
			//StudentGrade stugrade(*it_stu,make_pair(*it_cou,score),make_pair(*it_cou, cou_table.stu_form[*it_stu]));
			StudentGrade stugrade;
			stugrade.stu = *it_stu;
			stugrade.cou_gra[*it_cou] = score;
			stugrade.cou_form[*it_cou] = cou_table.stu_form[*it_stu];
			grade_table.insert(stugrade);
			printf("录入成功\n");
		}
		else
		{
			cout << "学生不存在或者课程号有误" << endl;
		}
		printf("继续录入吗？");
		printf("0. 停止录入  1. 继续录入\n");
		cin >> op;
	}
}
void Output()
{
	int op = 1;
	printf("0. 退出  1. 查看某学生的成绩  2. 查看某门课的成绩\n");
	cin >> op;
	while(op)
	{
		if (op == 1)
		{
			string stu_id;
			printf("请输入学生学号："); cin >> stu_id;
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
					cout << "未录入成绩" << endl;
				}
				break;
			}
			else
			{
				cout << "学生不存在" << endl;
			}
			
		}
		else if (op == 2)
		{
			string cou_id;
			printf("请输入课程号："); cin >> cou_id;
			auto it = cou_col.find(Couse(cou_id));
			if (it != cou_col.end())
			{
				CouseTable tmp = cou_table_col[*it];
				cout << tmp;
			}
			else
			{
				cout << "课程不存在" << endl;
			}
			
		}
		else
		{
			printf("输入有误\n");
			break;
		}
	
		break;
	}
}

void Erase()
{
	int op = 1;
	printf("0. 退出  1. 删除某学生的成绩\n");
	cin >> op;
	while (op)
	{
		if (op == 1)
		{
			string stu_id;
			printf("请输入学生学号："); cin >> stu_id;
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
					cout << "未录入成绩" << endl;
				}
				break;
			}
			else
			{
				cout << "学生不存在" << endl;
			}
		}
		else
		{
			printf("输入有误\n");
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
	printf("**  1.录入学生信息    2.输出  ***\n");
	printf("********   3.录入成绩   4. 删除   ******\n");
	printf("****   5.录入课程信息  6.修改成绩  ******\n");
	printf("**********        0.exit       ********\n");
	printf("***************************************\n");
	int op;
	printf("请输入： "); cin >> op;
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
		printf("**  1.录入学生信息    2.输出  ***\n");
		printf("********   3.录入成绩   4. 删除   ******\n");
		printf("****   5.录入课程信息   6.修改成绩  ******\n");
		printf("**********        0.exit       ********\n");
		printf("***************************************\n");
		cin >> op;
	}
	
}

