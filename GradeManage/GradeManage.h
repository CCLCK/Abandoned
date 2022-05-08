#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <assert.h>
#include <iomanip>
#include <set>
#include <unordered_set>//���򲻺ø� �ײ��ǹ�ϣ
using namespace std;


struct Couse
{
	string id="0000";//�ֶ��趨�γ̺�Ϊ4λ
	string name="xxxx";
	static int credit;
	friend ostream& operator<<(ostream& output,const Couse& c);
	Couse(){}
	Couse(string id2)
		:id(id2)
	{}
	bool operator<(const Couse& c) const
	{
		int id_int = stoi(this->id);
		int c_id_int = stoi(c.id);
		if (id_int < c_id_int)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};
int Couse::credit = 0;
ostream& operator<<(ostream& output, const  Couse& c)
{
	//cout << "    �γ̺�   " << "�γ���   " << "�γ�ѧ��   " << endl;
	cout<<setw(8) << c.id << setw(10)  << c.name << setw(8) << c.credit<<" ";
	return output;
}

struct Student
{
	Student(){}
	Student(string id2)
		:id(id2)
	{}
	size_t age = 0;
	string sex = "��";
	string name = "����";
	string id = "00000000";
	friend ostream& operator<<(ostream& output, const  Student& s) ;
	bool operator<(const Student& stu) const
	{
		if (this->id.size() > 8 || stu.id.size() > 8)
		{
			assert(false);
		}
		int stu1_id_int = stoi(this->id);
		int stu2_id_int = stoi(stu.id);
		if (stu1_id_int < stu2_id_int)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

};
ostream& operator<<(ostream& output, const Student& s)
{
	cout << setw(8) << s.id << setw(10) << s.name  <<setw(8) << s.sex << setw(8) << s.age<<" ";
	return output;
}

//bool operator<(const Student& stu1, const Student& stu2) //д�ɳ�Ա�����ͱ������const
//{
//	if (stu1.id.size() != 8 || stu2.id.size() != 8)
//	{
//		assert(false);
//	}
//	int stu1_id_int = stoi(stu1.id);
//	int stu2_id_int = stoi(stu2.id);
//	if (stu1_id_int <= stu2_id_int)//�Ⱥ���Ϊ�˲���
//	{
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}
enum Grade_form
{
	Normal,
	notNormal
};
class CouseTable//�γ̳ɼ���
{
public:
	friend ostream& operator<<(ostream& output, CouseTable& cou_table);
	Couse cou;//�γ�
	map<Student, int>stu_gra;//ѧ��+�ɼ�
	map<Student, Grade_form>stu_form;//ѧ��+���ſγ̵�״̬
};
ostream& operator<<(ostream& output, CouseTable& cou_table)
{
	cout << cou_table.cou<<endl;
	auto it = cou_table.stu_gra.begin();
	auto it2 = cou_table.stu_form.begin();
	while (it != cou_table.stu_gra.end())
	{
		cout << it->first.id << " " << it->first.name <<" " << it->second << " " << it2->second << endl;
		it++;
		it2++;
	}
	return output;
}
class StudentGrade
{
public:
	/*StudentGrade(const Student& stu2,const map<Couse, int>& cou_gra2,const map<Couse, Grade_form>&cou_form2)
		:stu(stu2)
		,cou_gra(cou_gra2)
		,cou_form(cou_form2)
	{}*/
	friend ostream& operator<<(ostream& output, const  StudentGrade& s);
	bool operator<(const StudentGrade& stugrade2) const 
	{
		int stu1 = stoi(stu.id);
		int stu2 = stoi(stugrade2.stu.id);
		if (stu1 < stu2)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	StudentGrade(){}
	StudentGrade(Student st2)
		:stu(st2)
	{}
	Student stu;
	map<Couse, int>cou_gra;//һ�ſ�һ���ɼ�
	map<Couse, Grade_form>cou_form;//ÿ�ſε�״̬
};
ostream& operator<<(ostream& output, const  StudentGrade& s)
{
	cout << s.stu << endl;;
	auto it1 = s.cou_gra.begin();
	auto it2 = s.cou_form.begin();
	while (it1 != s.cou_gra.end())
	{
		cout << it1->first<<"    ";
		cout << it1->second<<"   ";
		cout << it2->second<<endl;
		it1++;
		it2++;
	}
	return output;
}
class GradeTable
{
public:
	vector<StudentGrade>v;//���ѧ���ĳɼ�����
};





