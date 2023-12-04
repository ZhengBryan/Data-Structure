#pragma once
#include <iostream>
#include <sstream>
#include <cstring>
#include "./hashtable.hpp"
#define HashLength 19997
#define NO_STUDENT 10
#define NO_COURSE 11
#define ALREADY_REGISTER 12
using namespace std;

struct CourseInfo;	//����������������

/* ѧ����Ϣ */
struct StudentInfo {
	long long ID;						//ѧ��
	char name[32];						//����
	char major[64];						//רҵ
	char gender;						//�Ա� F/M
	SqList<long long> courses;			//ѡ��(��κ�)
	/* ���ڲ���ѧ����Ϣ ѧ��ƥ�伴�� */
	bool operator==(const StudentInfo& that) const
	{
		return ID == that.ID;
	}
};

/* �γ���Ϣ */
struct CourseInfo {
	long long ID;						//�κ�
	char name[32];						//����
	float credit;						//ѧ��
	char venue[64];						//�Ͽεص�
	SqList<long long> students;			//��ѡѧ��(��ѧ��)
	/* ���ڲ��ҿγ���Ϣ �κ�ƥ�伴�� */
	bool operator==(const CourseInfo& that) const
	{
		return ID == that.ID;
	}
};

/* ѡ��ϵͳ */
class EduSystem {
	Hashtable<StudentInfo> StudentList;		//ѧ���б�
	Hashtable<CourseInfo> CourseList;		//�γ��б�
	int StudentNum, CourseNum;				//ѧ�����γ�����
public:
	//��ȡѧ������
	int GetStudentNum();		
	//��ȡ�γ�����
	int GetCourseNum();			
	//��ʼ��ѧ���б�
	Status InitStudentList(istream& in);
	//��ʼ���γ��б�
	Status InitCourseList(istream& in);	
	//����ѧ����Ϣ
	Status InsertStudent(const StudentInfo& e);		
	//����γ���Ϣ
	Status InsertCourse(const CourseInfo& e);
	//ɾ��ѧ����Ϣ
	Status DeleteStudent(StudentInfo& e);	
	//ɾ���γ���Ϣ
	Status DeleteCourse(CourseInfo& e);			
	//��ѯѧ����Ϣ
	Status SearchStudent(StudentInfo& e, ostringstream& out);	
	//��ѯ�γ���Ϣ
	Status SearchCourse(CourseInfo& e, ostringstream& out);			
	//ע��γ�
	Status Register(CourseInfo& ec, StudentInfo& es);				
};

