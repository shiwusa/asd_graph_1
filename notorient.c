
#include<windows.h>
#include<math.h>
#include <stdio.h>
#include <stdlib.h>

double** randmm(int rows, int cols)
{
    double** matrix = (double**)malloc(rows * sizeof(double*));

    for (int i = 0; i < rows; i++)
        matrix[i] = (double*)malloc(cols * sizeof(double));

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            matrix[i][j] =  2.0 / RAND_MAX * rand();
        }
    }

    return matrix;
}

double** mulmr(double num, double **mat, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            mat[i][j] = mat[i][j] * num;

            if(mat[i][j] > 1.0)
            {
                mat[i][j] = 1;
            } else mat[i][j] = 0;
        }
    }
    return mat;
}
//Создаём прототип функции окна, которая будет определена ниже
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//void arrow(float fi, int px,int py);

//объявляем строку-имя программы
char ProgName[]="Лабораторна робота 3";

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
    HWND hWnd;
    MSG lpMsg;

    WNDCLASS w; //создаём экземпляр структуры WNDCLASS

    w.lpszClassName=ProgName; //имя программы - объявлено выше
    w.hInstance=hInstance; //идентификатор текущего приложения
    w.lpfnWndProc=WndProc; //указатель на функцию окна
    w.hCursor=LoadCursor(NULL, IDC_ARROW); //загружаем курсор
    w.hIcon=0; //иконки у нас не будет пока
    w.lpszMenuName=0; //и меню пока не будет
    w.hbrBackground = LTGRAY_BRUSH; //WHITE_BRUSH;// цвет фона окна
    w.style=CS_HREDRAW|CS_VREDRAW; //стиль - перерисовываемое по х и по у
    w.cbClsExtra=0;
    w.cbWndExtra=0;

    if(!RegisterClass(&w))
        return 0;

   // HWND hWnd;
    //MSG lpMsg;

//Создадим окно в памяти, заполнив аргументы CreateWindow
    hWnd=CreateWindow(ProgName, //Имя программы
        "Лабораторна робота 3", //Заголовок окна
        WS_OVERLAPPEDWINDOW, //Стиль окна - перекрывающееся
        0, //положение окна на экране по х
        0, //положение по у
        1920, //ширина
        1080, //висота
        (HWND)NULL, //идентификатор родительского окна
        (HMENU)NULL, //идентификатор меню
        (HINSTANCE)hInstance, //идентификатор экземпляра программы
        (HINSTANCE)NULL); //отсутствие дополнительных параметров

//Выводим окно из памяти на экран
    ShowWindow(hWnd, nCmdShow);
//Обновим содержимое окна
 //   UpdateWindow(hWnd);

//Цикл одержання повідомлень

    while(GetMessage(&lpMsg, hWnd, 0, 0)) { //Получаем сообщение из очереди
            TranslateMessage(&lpMsg); //Преобразует сообщения клавиш в символы
            DispatchMessage(&lpMsg); //Передаёт сообщение соответствующей функции окна
        }
    return(lpMsg.wParam);
    }

//Функция окна
LRESULT CALLBACK WndProc(HWND hWnd, UINT messg,
                        WPARAM wParam, LPARAM lParam)
    {
    HDC hdc; //создаём контекст устройства
    PAINTSTRUCT ps; //создаём экземпляр структуры графического вывода

    void arrow(float fi, int px,int py){
            fi = 3.1416*(180.0 - fi)/180.0;
            int lx,ly,rx,ry; //px,py,
           // px=150; py=60;
            lx = px+15*cos(fi+0.3);
            rx = px+15*cos(fi-0.3);
            ly = py+15*sin(fi+0.3);
            ry = py+15*sin(fi-0.3);
            MoveToEx(hdc, lx, ly, NULL);
            LineTo(hdc, px, py);
            LineTo(hdc, rx, ry);
         //  return 0;
      }

//Цикл обработки сообщений
    switch(messg){
    //сообщение рисования
        case WM_PAINT :


            hdc=BeginPaint(hWnd, &ps);
            char *nn[11] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "a", "b"};
            int nx[11] = {};
            int ny[11] = {};
            int oneLen = 75;
            for ( int i = 0; i < 11; i++ ) {
                if ( i == 0 ) {
                    nx[i] = oneLen*6;
                    ny[i] = 800 - oneLen;
                }
                else if ( i < 3) {
                    nx[i] = nx[i-1] - oneLen*2;
                    ny[i] = ny[i-1];
                }
                else if ( i < 7 ) {
                    nx[i] = nx[i-1] + oneLen;
                    ny[i] = ny[i-1] - oneLen*2;
                }
                else {
                    nx[i] = nx[i-1] + oneLen;
                    ny[i] = ny[i-1] + oneLen*2;
                }
            }
            int dx = 16, dy = 16, dtx = 7;
            int i;
            HPEN BPen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
            HPEN KPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));


            srand(0315);
            double** T = randmm(11, 11);
            double coef = 1.0 - 1*0.02 - 5*0.005 - 0.25;
            double** A = mulmr(coef, T, 11, 11);

            double B[11][11] = {};

            for (int i = 0; i < 11; i++)
            {
                for (int j = 0; j < 11; j++)
                {
                    B[i][j] = A[i][j];

                }
            }
            printf("\nMirror Matrix:\n");
            for (int i = 0; i < 11; i++)
            {
                for (int j = 0; j < 11; j++)
                {
                    if ( A[i][j] == 1 ){
                        B[j][i] = A[i][j];
                    }
                    printf("%.0f ", B[i][j]);
                }
                printf("\n");
            }
            SelectObject(hdc, KPen);
            for (int i = 0; i < 11; i++)
            {
                for (int j = 0; j < 11; j++)
                {
                    if ( A[i][j] == 1 ) {
                        MoveToEx(hdc, nx[i], ny[i], NULL);
                        if ( i != ( j + 1 ) && j != ( i + 1 ) ) {
                           if ( ( i <= 2 || i == 10 ) && ny[i] == ny[j] ) {
                                if ( i == j && i != 10) {
                                    Arc(hdc, nx[j], ny[j], nx[j]-50, ny[j]-50, nx[j], ny[j], nx[j], ny[j]);
                                }
                                else if ( i == j && i == 10 ) {
                                    Arc(hdc, nx[j], ny[j], nx[j]+50, ny[j]-50, nx[j], ny[j], nx[j], ny[j]);

                                }
                                else if ( A[j][i] == 1 ) {
                                    if ( ( i - j ) < 0 ) {
                                        Arc(hdc, nx[j], ny[j]-40, nx[i], ny[i]+40, nx[i], ny[i], nx[j], ny[j]);

                                    }

                                }
                                else {
                                    Arc(hdc, nx[i], ny[i]-40, nx[j], ny[j]+40, nx[j], ny[j], nx[i], ny[i]);

                                }
                           }
                           else if ( ( i >= 2 && i < 7 ) && ( j >= 2 && j < 7 ) ) {
                                if ( i == j ) {
                                    Arc(hdc, nx[j], ny[j], nx[j]-50, ny[j]-50, nx[j], ny[j], nx[j], ny[j]);

                                }
                                else if ( A[j][i] != 1 ) {
                                    if( ( i-j ) == -2 || ( i-j ) == 2 ){
                                        Arc(hdc, nx[i]+10, ny[i]-110, nx[j]-50, ny[j]+40, nx[i], ny[i], nx[j], ny[j]);
                                    }
                                    else {
                                        Arc(hdc, nx[i]-100, ny[i]+75, nx[j]+100, ny[j]-70, nx[j], ny[j], nx[i], ny[i]);
                                    }
                                }
                           }
                            else if ( ( i >= 6 && i < 12 ) && ( j >= 6 && j < 12 ) ) {
                                if ( i == j ) {
                                    Arc(hdc, nx[j], ny[j], nx[j]+50, ny[j]-50, nx[j], ny[j], nx[j], ny[j]);
                                }
                                else if ( A[j][i] == 1 ) {
                                    switch ( i - j ) {
                                    case 2: case -2:
                                        Arc(hdc, nx[i]+100, ny[i]+15, nx[j]-30, ny[j]-80, nx[i], ny[i], nx[j], ny[j]);
                                        break;
                                    case -3:
                                        Arc(hdc, nx[i]-40, ny[i]-90, nx[j]+60, ny[j]+70, nx[j], ny[j], nx[i], ny[i]);
                                        break;
                                    case 4: case -4:
                                        Arc(hdc, nx[i]-50, ny[i]-70, nx[j]-50, ny[j], nx[j], ny[j], nx[i], ny[i]);
                                        break;
                                    }
                                }
                                else {
                                    switch ( i - j ) {
                                    case 2:
                                        Arc(hdc, nx[i]+100, ny[i]+15, nx[j]-30, ny[j]-80, nx[i], ny[i], nx[j], ny[j]);
                                        break;
                                    case -2:
                                        Arc(hdc, nx[j], ny[j]+200, nx[i]-100, ny[i]-10, nx[j], ny[j], nx[i], ny[i]);
                                        break;
                                    case 3: case -3:
                                        Arc(hdc, nx[i]-50, ny[i]-100, nx[j]+70, ny[j]+70, nx[j], ny[j], nx[i], ny[i]);
                                        break;
                                    }
                                }
                            //printf("\n%i\t%i\n",i,j);
                            }
                            else {
                                if ( A[j][i] == 1 ) {
                                    if ( ( i - j ) > 0 ) {
                                        LineTo(hdc, nx[j], ny[j]);
                                    }
                                }
                                else {
                                    LineTo(hdc, nx[j], ny[j]);
                                }//printf("\n%i\t%i\n",i,j);

                            }
                        }
                        else {
                            if ( A[j][i] == 1 ) {
                                if ( ( i - j ) > 0 ) {
                                        LineTo(hdc, nx[j], ny[j]);
                                    }
                            }
                            else {
                                LineTo(hdc, nx[j], ny[j]);
                            }
                        }
                    }
                }
            }
            SelectObject(hdc, BPen);
            for ( i = 0; i <= 10; i++ ){
              Ellipse ( hdc, nx[i]-dx, ny[i]-dy, nx[i]+dx, ny[i]+dy );
              TextOut ( hdc, nx[i]-dtx, ny[i]-dy/2, nn[i], 1 );
            }
            EndPaint(hWnd, &ps);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return(DefWindowProc(hWnd, messg, wParam, lParam));
    }
    return 0;
}
