/*
  --- 장애물 피하기 게임 ---
         기본 규칙
- 장애물에 충돌 했을 경우 게임 오버
- 장애물에 충돌할 때 까지 무한반복
- 1초당 1점 획둑
 */
/*
--- 현재 존재하는 문제점 ---

- 속도를 조절하면 값에 따라서 충돌 판정 범위에 들어가지 않아서
  게임이 제대로 진행되지 않는 경우가 발생함. --> 속도에 따른 판정 범위 개선이 필요함,
*/

#include <stdio.h>
#include <windows.h> // 윈도우 전용 라이브러리
#include <conio.h> // 윈도우 콘솔창 관리 라이브러리
#include <time.h>
#include <stdbool.h>

#define object1_y 18
#define obstacle_x 30
#define obstacle_y 18


void SetConsoleView() //콘솔창 설정
{
    system("mode con:cols=100 lines=25");
    system("title 2306_김지원_C-assignment.");
}

void GotoXY(int x, int y) //콘솔창 커서 이동
{
    COORD Pos;
    Pos.X = 2 * x;
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

int GetKeyDown() // 키보드 입력 인식 후 입력값 반환
{
    if (_kbhit() != 0)
    {
        return _getch();
    }
    return 0;
}

void object1(int obj_y)
{
    GotoXY(0, obj_y);
    printf("   *\n");
    printf("  ***\n");
    printf(" *****\n");
    printf("*******\n");
    printf(" *****\n");
}

void obstacle(int obs_x,int obs_y)
{
    GotoXY(obs_x, obs_y);
    printf("   \n");
    GotoXY(obs_x, obs_y+1);
    printf("   \n");
    GotoXY(obs_x, obs_y+2);
    printf("   \n");
    GotoXY(obs_x, obs_y+3);
    printf("   *\n");
    GotoXY(obs_x, obs_y+4);
    printf("   *\n");
}

void draw_backgrounds()
{
    GotoXY(0, 23);
    printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
    printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
}

bool collision(const int obs_x, const int obj_y)
{
    GotoXY(0, 0);
    printf("obs_x : %d, obj_y : %d", obs_x, obj_y); //적당한 값을 찾기 위해 출력함.
    if (obs_x <= 5 && obs_x >= 2 && obj_y > 15 )
    {
        return true;
    }
    return false;
}

void GameOver(const int score)
{
    system("cls");
    int x = 18;
    int y = 8;
    GotoXY(x, y);
    printf("===========================");
    GotoXY(x, y + 1);
    printf("======G A M E O V E R======");
    GotoXY(x, y + 2);
    printf("===========================");
    GotoXY(x, y + 5);
    printf("SCORE : %d", score);
    printf("\n\n\n\n\n\n\n\n\n");
    system("pause");
}


int main(void)
{
    printf("스페이스바를 눌러서 점프 합니다.");
    printf("\n\n\n\n\n\n\n\n\n");
    system("pause");
    int speed = 4;
    int score = 0;
    clock_t start, curr;    //점수 변수 초기화
    start = clock();        //시작시간 초기화
    bool obj_jump;
    SetConsoleView();
    int obj_y = object1_y;
    int obs_x = obstacle_x;
    int obs_y = obstacle_y;
    while (true)
    {
        curr = clock();            //현재시간 받아오기
        if (collision(obs_x, obj_y))
        {
            break;
        }
        if (GetKeyDown() == ' ')
        {
            obj_jump = true;
        }
        else
        {
            obj_jump = false;
        }
        if (obj_y <= obstacle_y - 16)
        {
            obj_jump = false;
        }
        if (obj_jump == true)
        {
            obj_y -= 8;
        }
        else
        {
            obj_y = object1_y;
        }
        if (obs_x > 2)
        {
            obs_x -= speed;
        }
        else
        {
            obs_x = obstacle_x;
        }
        
        if (((curr - start) / CLOCKS_PER_SEC) >= 1)    // 1초가 넘었을떄
        {
            score++;    //스코어 UP
            start = clock();    //시작시간 초기화
        }

        GotoXY(22, 0);
        printf("Score : %d ", score);
        system("cls");    //clear
        draw_backgrounds();
        object1(obj_y);
        obstacle(obs_x, obs_y);
        Sleep(100);
    }
  
    GameOver(score);
    
}
