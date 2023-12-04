#define _CRT_SECURE_NO_WARNINGS
#include "./system.h"
/**
 * @brief �����ڹ�ϣ���ж�Ӧ�±�
 * @param e �����Ԫ��
 * @return �±�ֵ
*/
static int GetIndex(const CourseInfo& e)
{
	return e.ID % HashLength;
}

/**
 * @brief �����ڹ�ϣ���ж�Ӧ�±�
 * @param e �����Ԫ��
 * @return �±�ֵ
*/
static int GetIndex(const StudentInfo& e)
{
	return e.ID % HashLength;
}

/**
 * @brief ȡϵͳѧ������
 * @return ѧ������
*/
int EduSystem::GetStudentNum()
{
	return StudentNum;
}

/**
 * @brief ȡϵͳ�γ�����
 * @return �γ�����
*/
int EduSystem::GetCourseNum()
{
	return CourseNum;
}

/**
 * @brief ��ʼ��ѧ������
 * @param in ������
 * @return ��ʼ��״̬
*/
Status EduSystem::InitStudentList(istream& in)
{
	StudentNum = 0;
	while (in.peek() != EOF) {
		StudentInfo tmp;
		char temp[20];
		in >> tmp.ID >> tmp.name >> temp >> tmp.major;
		if (strcmp(temp, "��") == 0)
			tmp.gender = 'M';
		else if (strcmp(temp, "Ů") == 0)
			tmp.gender = 'F';
		StudentList.TableInsert(tmp, &GetIndex);
		StudentNum++;
		in.get();
	}
	return OK;
}

/**
 * @brief ��ʼ���γ�����
 * @param in ������
 * @return ��ʼ��״̬
*/
Status EduSystem::InitCourseList(istream& in)
{
	CourseNum = 0;
	while (in.peek() != EOF) {
		CourseInfo tmp;
		in >> tmp.ID >> tmp.name >> tmp.credit >> tmp.venue;
		CourseList.TableInsert(tmp, &GetIndex);
		CourseNum++;
		in.get();
	}
	return OK;
}


/**
 * @brief ������ѧ����Ϣ
 * @param e ѧ����Ϣ
 * @return ����״̬
*/
Status EduSystem::InsertStudent(const StudentInfo& e)
{
	if (StudentList.IsInTable(e, &GetIndex))
		return ERROR;			//ѧ���ظ�
	return StudentList.TableInsert(e, &GetIndex);
}

/**
 * @brief �����¿γ���Ϣ
 * @param e �γ���Ϣ
 * @return ����״̬
*/
Status EduSystem::InsertCourse(const CourseInfo& e)
{
	if (CourseList.IsInTable(e, &GetIndex))
		return ERROR;			//�κ��ظ�
	return CourseList.TableInsert(e, &GetIndex);
}


/**
 * @brief ɾ��ѧ����Ϣ
 * @param e ɾ����ѧ����Ϣ
 * @return ɾ��״̬
*/
Status EduSystem::DeleteStudent(StudentInfo& e)
{
	return StudentList.TableDelete(e, &GetIndex);
}


/**
 * @brief ɾ���γ���Ϣ
 * @param e ɾ���Ŀγ���Ϣ
 * @return ɾ��״̬
*/
Status EduSystem::DeleteCourse(CourseInfo& e)
{
	return CourseList.TableDelete(e, &GetIndex);
}


/**
 * @brief ����ѧ����Ϣ
 * @param e ѧ����Ϣ(����ʱͨ��ѧ�Ų���, ����ʱ���ڴ�ӡ��Ϣ)
 * @param out �����
 * @return ����״̬
*/
Status EduSystem::SearchStudent(StudentInfo& e, ostringstream& out)
{
	if (!StudentList.IsInTable(e, &GetIndex))
		return ERROR;
	else {
		StudentList.TableSearch(e, &GetIndex);
		for (int i = 1; i <= e.courses.ListLength(); i++) {
			CourseInfo c;
			//�ҵ���Ӧ�Ŀκ�
			e.courses.GetElem(i, c.ID);
			//�Ҿ�����Ϣ
			int pst = CourseList.TableSearch(c, &GetIndex);
			//������ѡ�Ŀγ̱�ɾ����
			if (pst == OK) {
				out << "\t\t[�κ�]" << c.ID << "\t[����]" << c.name << "\t[ѧ��]" << c.credit << endl;
			}
		}
	}
	return OK;
}


/**
 * @brief ���ҿγ���Ϣ
 * @param e �γ���Ϣ(����ʱͨ���κŲ���, ����ʱ���ڴ�ӡ��Ϣ)
 * @param out �����
 * @return ����״̬
*/
Status EduSystem::SearchCourse(CourseInfo& e, ostringstream& out)
{
	if (!CourseList.IsInTable(e, &GetIndex))
		return ERROR;
	else {
		CourseList.TableSearch(e, &GetIndex);
		for (int i = 1; i <= e.students.ListLength(); i++) {
			StudentInfo s;
			//�ҵ���Ӧ�Ŀκ�
			e.students.GetElem(i, s.ID);
			//�Ҿ�����Ϣ
			int pst = StudentList.TableSearch(s, &GetIndex);
			//������ѡ�Ŀγ̱�ɾ����
			if (pst == OK) {
				out << "\t\t[ѧ��]" << s.ID << "\t[����]" << s.name << "\t[�Ա�]" << (s.gender == 'M' ? "��" : "Ů") << "\t[רҵ]" << s.major << endl;
			}
		}
	}

	return OK;
}


/**
 * @brief ѧ��ע���¿γ�
 * @param ec ѧ����Ϣ
 * @param es �γ���Ϣ
 * @return ע��״̬
*/
Status EduSystem::Register(CourseInfo& ec, StudentInfo& es)
{
	StudentInfo * studentp;
	CourseInfo * coursep;
	int ret1, ret2;
	ret1 = StudentList.LocateElem(es, studentp, &GetIndex);
	ret2 = CourseList.LocateElem(ec, coursep, &GetIndex);
	if (ret1 == ERROR)
		return NO_STUDENT;
	if (ret2 == ERROR)
		return NO_COURSE;
	if (studentp->courses.IsInList(coursep->ID))
		return ALREADY_REGISTER;
	studentp->courses.ListInsert(1, coursep->ID);
	coursep->students.ListInsert(1, studentp->ID);
	return OK;
}
