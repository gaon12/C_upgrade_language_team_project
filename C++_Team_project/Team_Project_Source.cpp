#include<iostream>
#include <string>
using namespace std;

#define NAME_SIZE 32
#define STUDENT_MAX 10
#define ADDRESS_SIZE 128
#define SUBJECT_SIZE 20

struct _tagStudent
{
    int iNumber;
    char strName[NAME_SIZE];
    char strSubject[SUBJECT_SIZE];
    char strAddress[ADDRESS_SIZE];
    int imonth;
    int idate;
    int iTime;
    int iClock;
};

enum MENU
{
    MENU_NONE,
    MENU_INSERT,
    MENU_DELETE,
    MENU_SEARCH,
    MENU_OUTPUT,
    MENU_EXIT
};


void main()
{

    _tagStudent tStudentArr[STUDENT_MAX] = {};
    char strName[NAME_SIZE] = {};
    int iStudentCount = 0;
    int iStdNumber = 1;


    while (true)
    {

        cout << "   --------<  자격증 시험 예약 프로그램 >--------- " << endl;
        cout << "  |                                               |" << endl;
        cout << "  |  1. 자격증 시험 예약하기                      |" << endl;
        cout << "  |  2. 자격증 시험 취소하기                      |" << endl;
        cout << "  |  3. 자격증 시험 수험생 탐색하기               |" << endl;
        cout << "  |  4. 자격증 시험 수험생 출력하기               |" << endl;
        cout << "  |  5. 종료하기                                  |" << endl;
        cout << "   ----------------------------------------------- " << endl;
        cout << "   메뉴를 입력하세요 :    ";


        int iMenu;
        cin >> iMenu;

        if (cin.fail())
        {
            cin.clear();

            continue;
        }




        if (iMenu == MENU_EXIT)
            break;

        switch (iMenu)
        {
        case MENU_INSERT:


            cout << " ==========자격증 시험 예약 입력 하세요.=============" << endl;

            if (iStudentCount == STUDENT_MAX)
                break;

            cout << "이름을 입력하세요 :";
            cin >> tStudentArr[iStudentCount].strName, NAME_SIZE;

            cin.ignore(1024, '\n');

            cout << "응시 종목을 입력하세요 :";
            cin.getline(tStudentArr[iStudentCount].strSubject, SUBJECT_SIZE);

            cout << "장소를 입력하세요 : ";
            cin.getline(tStudentArr[iStudentCount].strAddress, ADDRESS_SIZE);

            cout << "몇월을 입력을하세요 : ";
            cin >> tStudentArr[iStudentCount].imonth;

            cout << "몇일을 입력을하세요 : ";
            cin >> tStudentArr[iStudentCount].idate;

            cout << "시간을 입력하세요 : ";
            cin >> tStudentArr[iStudentCount].iTime;

            cout << "몇분을 입력하세요 : ";
            cin >> tStudentArr[iStudentCount].iClock;

            tStudentArr[iStudentCount].iNumber = iStdNumber;

            ++iStdNumber;
            ++iStudentCount;



            break;
        case MENU_DELETE:



            cout << "=======================삭제할 수험생 ==================" << endl;



            cin.ignore(1024, '\n');
            cout << "삭제할 수험생을 입력하세요 : ";
            cin.getline(strName, NAME_SIZE);

            for (int i = 0; i < iStudentCount; ++i)
            {
                if (strcmp(tStudentArr[i].strName, strName) == 0)
                {
                    for (int j = i; j < iStudentCount - 1; ++j)
                    {
                        tStudentArr[i] = tStudentArr[i + 1];
                    }
                    --iStudentCount;

                    cout << "삭제가 완료 되었습니다." << endl;
                    break;
                }
            }


            break;
        case MENU_SEARCH:


            cout << "=======================수험생 탐색 ==================" << endl;



            cin.ignore(1024, '\n');
            cout << "탐색할 수험생을 입력하세요 : ";
            cin.getline(strName, NAME_SIZE);

            for (int i = 0; i < iStudentCount; ++i)
            {
                if (strcmp(tStudentArr[i].strName, strName) == 0)
                {
                    cout << tStudentArr[i].iNumber << "번째 " << endl;
                    cout << "이름 : " << tStudentArr[i].strName << endl;
                    cout << "응시 종목 : " << tStudentArr[i].strSubject << endl;
                    cout << "2020년 " << tStudentArr[i].imonth << "월 " << tStudentArr[i].idate << "일 " << endl;
                    cout << tStudentArr[i].iTime << "시 " << tStudentArr[i].iClock << "분" << endl;
                    break;
                }
            }





            break;
        case MENU_OUTPUT:



            cout << "=============수험생출력 ============" << endl;

            for (int i = 0; i < iStudentCount; ++i)
            {
                cout << tStudentArr[i].iNumber << "번째 " << endl;
                cout << "이름 : " << tStudentArr[i].strName << endl;
                cout << "응시 종목 : " << tStudentArr[i].strSubject << endl;
                cout << "2020년 " << tStudentArr[i].imonth << "월 " << tStudentArr[i].idate << "일 " << endl;
                cout << tStudentArr[i].iTime << "시 " << tStudentArr[i].iClock << "분" << endl;
            }



            break;
        default:
            cout << "메뉴를 잘못 선택했습니다. " << endl;
            break;
        }


    }
}